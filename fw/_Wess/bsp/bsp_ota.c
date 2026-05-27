//--------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//--------------------------------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>

#include "bsp_ota.h"
#include "bsp_usb.h"
#include "fatfs.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_flash_ex.h"

#define FLASH_BANK2_BASE   (0x08100000u)
#define BANK_SIZE          (0x00100000u)
#define OTA_APP_BASE_ADDR  (0x08008000u)
#define OTA_APP_END_ADDR   (0x08100000u)
#define OTA_BOOT_BASE_ADDR (0x08000000u)
#define OTA_APP_OFFSET     (OTA_APP_BASE_ADDR - OTA_BOOT_BASE_ADDR)   // 0x8000: bootloader region size
#define OTA_SRAM_START     (0x20000000u)
#define OTA_SRAM_END       (0x20080000u)
#define OTA_BASE_ADDR      FLASH_BANK2_BASE
#define OTA_MAX_SIZE       (BANK_SIZE - 0x00001000u)
#define OTA_BANK           FLASH_BANK_1
#define OTA_SECTOR_FIRST   FLASH_SECTOR_8
#define OTA_SECTOR_COUNT   4u
#define BKP_MAGIC_NUMBER   0x12345678u

#define OTA_SDRAM_ADDR     (0xD0700000u)
#define OTA_SDRAM_SIZE     (0x00100000u)
#define OTA_DBG_BKP_REG    RTC_BKP_DR12

typedef struct {
	U08 active;
	U08 overflow;
	U32 cnt;
} OTA_LS;

static OTA_LS lOta;
static U08 g_ota_dbg_status = OTA_DBG_IDLE;

U08 *SDRAM_aEco_ota = (U08 *)OTA_SDRAM_ADDR;

extern RTC_HandleTypeDef hrtc;

static void ota_dbg_backup_access_enable(void)
{
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
}

U32 lota_get_cnt(void)
{
	return lOta.cnt;
}

static U08 ota_dbg_status_sanitize(U08 code)
{
	return (code <= OTA_DBG_USB_VERIFY_FAIL) ? code : OTA_DBG_IDLE;
}

static U08 ota_dbg_status_load(void)
{
	ota_dbg_backup_access_enable();
	return ota_dbg_status_sanitize((U08)HAL_RTCEx_BKUPRead(&hrtc, OTA_DBG_BKP_REG));
}

void ota_dbg_status_set(U08 code, bool persist)
{
	g_ota_dbg_status = ota_dbg_status_sanitize(code);

	if (persist != false)
	{
		ota_dbg_backup_access_enable();
		HAL_RTCEx_BKUPWrite(&hrtc, OTA_DBG_BKP_REG, g_ota_dbg_status);
	}
}

U08 ota_dbg_status_get(void)
{
	return g_ota_dbg_status;
}

static uint32_t crc32_step(uint32_t crc, uint8_t data)
{
	crc ^= data;
	for (int i = 0; i < 8; i++) {
		crc = (crc & 1u) ? (0xEDB88320u ^ (crc >> 1)) : (crc >> 1);
	}
	return crc;
}

static uint32_t crc32_final(uint32_t crc)
{
	return crc ^ 0xFFFFFFFFu;
}

void flash_unlock_all(void)
{
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(
		  FLASH_FLAG_EOP
		| FLASH_FLAG_OPERR
		| FLASH_FLAG_WRPERR
		| FLASH_FLAG_PGAERR
		| FLASH_FLAG_PGPERR
		| FLASH_FLAG_ERSERR);
}

void flash_lock_all(void)
{
	HAL_FLASH_Lock();
}

static HAL_StatusTypeDef FLASH_WaitForever(void)
{
	while (__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) != RESET) {}

	{
		uint32_t errFlags =
			  FLASH_FLAG_WRPERR
			| FLASH_FLAG_PGAERR
			| FLASH_FLAG_PGPERR
			| FLASH_FLAG_ERSERR
			| FLASH_FLAG_OPERR;

		if (__HAL_FLASH_GET_FLAG(errFlags) != RESET)
		{
			__HAL_FLASH_CLEAR_FLAG(errFlags);
			return HAL_ERROR;
		}
	}

	if (__HAL_FLASH_GET_FLAG(FLASH_FLAG_EOP) != RESET)
	{
		__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP);
	}

	return HAL_OK;
}

static void OTA_FlashEraseSector(uint32_t sector, uint8_t voltageRange)
{
	uint32_t tmp_psize = 0U;

	assert_param(IS_FLASH_SECTOR(sector));
	assert_param(IS_VOLTAGERANGE(voltageRange));

	if (voltageRange == FLASH_VOLTAGE_RANGE_1) {
		tmp_psize = FLASH_PSIZE_BYTE;
	} else if (voltageRange == FLASH_VOLTAGE_RANGE_2) {
		tmp_psize = FLASH_PSIZE_HALF_WORD;
	} else if (voltageRange == FLASH_VOLTAGE_RANGE_3) {
		tmp_psize = FLASH_PSIZE_WORD;
	} else {
		tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
	}

	CLEAR_BIT(FLASH->CR, FLASH_CR_PSIZE);
	FLASH->CR |= tmp_psize;

	FLASH->CR &= ~FLASH_CR_SNB;
	FLASH->CR |= FLASH_CR_SER | (sector << POSITION_VAL(FLASH_CR_SNB));
	FLASH->CR |= FLASH_CR_STRT;
}

static HAL_StatusTypeDef OTA_FLASHEx_Erase(FLASH_EraseInitTypeDef *eraseInit, uint32_t *sectorError)
{
	HAL_StatusTypeDef status = HAL_ERROR;

	if (eraseInit->TypeErase != FLASH_TYPEERASE_SECTORS) {
		return HAL_ERROR;
	}

	assert_param(IS_FLASH_SECTOR(eraseInit->Sector));
	assert_param(IS_FLASH_NBSECTORS(eraseInit->NbSectors));

	status = FLASH_WaitForever();
	if (status != HAL_OK) {
		return status;
	}

	*sectorError = 0xFFFFFFFFU;

	for (uint32_t index = eraseInit->Sector;
		 index < (eraseInit->Sector + eraseInit->NbSectors);
		 index++)
	{
		OTA_FlashEraseSector(index, (uint8_t)eraseInit->VoltageRange);
		status = FLASH_WaitForever();

		CLEAR_BIT(FLASH->CR, (FLASH_CR_SER | FLASH_CR_SNB));

		if (status != HAL_OK) {
			*sectorError = index;
			break;
		}
	}

	return status;
}

bool flash_erase_ota_all(void)
{
	FLASH_EraseInitTypeDef eraseInit = {0};
	uint32_t sectorError = 0;

	for (uint32_t sector = 0; sector < OTA_SECTOR_COUNT; sector++)
	{
		eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
		eraseInit.Banks = OTA_BANK;
		eraseInit.Sector = OTA_SECTOR_FIRST + sector;
		eraseInit.NbSectors = 1;
		eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

		if (OTA_FLASHEx_Erase(&eraseInit, &sectorError) != HAL_OK) {
			return false;
		}
	}

	return true;
}

static bool flash_program_bytes(uint32_t addr, const uint8_t *src, uint32_t size)
{
	uint8_t wordBytes[4];
	uint32_t index = 0;

	while (index < size)
	{
		uint32_t remain = size - index;
		uint32_t chunk = (remain >= 4u) ? 4u : remain;
		uint32_t word;

		memset(wordBytes, 0xFF, sizeof(wordBytes));
		memcpy(wordBytes, &src[index], chunk);

		word =  (uint32_t)wordBytes[0]
			  | ((uint32_t)wordBytes[1] << 8)
			  | ((uint32_t)wordBytes[2] << 16)
			  | ((uint32_t)wordBytes[3] << 24);

		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, word) != HAL_OK) {
			return false;
		}

		addr += 4u;
		index += chunk;
	}

	return true;
}

static uint32_t ota_read_le32(const uint8_t *p)
{
	return  (uint32_t)p[0]
		  | ((uint32_t)p[1] << 8)
		  | ((uint32_t)p[2] << 16)
		  | ((uint32_t)p[3] << 24);
}

// True if the 8-byte vector at p is a valid Cortex-M reset vector:
//   SP in RAM [OTA_SRAM_START, OTA_SRAM_END]  (upper bound inclusive: initial SP may
//   equal the top of RAM, e.g. 0x20080000), Reset handler in [flashLo, flashHi) and odd (Thumb).
static bool ota_vec_ok(const uint8_t *p, uint32_t flashLo, uint32_t flashHi)
{
	uint32_t sp    = ota_read_le32(&p[0]);
	uint32_t reset = ota_read_le32(&p[4]);

	if ((sp < OTA_SRAM_START) || (sp > OTA_SRAM_END))  return false;
	if ((reset < flashLo) || (reset >= flashHi))       return false;
	if ((reset & 0x1u) == 0u)                          return false;   // Thumb
	return true;
}

// Resolve the app payload to stage from a USB image, returning the body pointer + length.
// Accepts BOTH:
//   - full image  (bootloader@0x08000000 + app@0x08008000): strips the first 0x8000 (bootloader),
//     stages only the app body. The bootloader copies it back to 0x08008000.
//   - app-only image (app@0x08008000): staged as-is.
static bool ota_resolve_app(const uint8_t *image, uint32_t size,
                            const uint8_t **pBody, uint32_t *pLen)
{
	if ((image == NULL) || (size < 8u) || (size > OTA_MAX_SIZE)) {
		return false;
	}

	// Full image: valid bootloader vector at 0, valid app vector at 0x8000.
	if ((size > OTA_APP_OFFSET)
	    && ota_vec_ok(image, OTA_BOOT_BASE_ADDR, OTA_APP_BASE_ADDR)
	    && ota_vec_ok(image + OTA_APP_OFFSET, OTA_APP_BASE_ADDR, OTA_APP_END_ADDR)) {
		*pBody = image + OTA_APP_OFFSET;
		*pLen  = size - OTA_APP_OFFSET;
		return true;
	}

	// App-only image: valid app vector at 0.
	if (ota_vec_ok(image, OTA_APP_BASE_ADDR, OTA_APP_END_ADDR)) {
		*pBody = image;
		*pLen  = size;
		return true;
	}

	return false;
}

static bool flash_verify_bytes(uint32_t addr, const uint8_t *src, uint32_t size)
{
	const uint8_t *dst = (const uint8_t *)addr;
	for (uint32_t i = 0; i < size; i++) {
		if (dst[i] != src[i]) {
			return false;
		}
	}
	return true;
}

static void ota_fail(U08 reason)
{
	ota_dbg_status_set(reason, true);
}

static U16 ota_process_from_sdram(void)
{
	uint32_t total = lOta.cnt;
	uint32_t body_len;
	uint32_t crc = 0xFFFFFFFFu;
	uint32_t expect;
	uint8_t *crcBytes;

	if (lOta.overflow != FALSE || total < 4u || total > (OTA_MAX_SIZE + 4u)) {
		ota_fail(OTA_DBG_LEN_FAIL);
		return OTA_RESULT_TOO_SHORT;
	}

	body_len = total - 4u;
	if (body_len == 0u || body_len > OTA_MAX_SIZE) {
		ota_fail(OTA_DBG_LEN_FAIL);
		return OTA_RESULT_TOO_SHORT;
	}

	ota_dbg_status_set(OTA_DBG_VERIFY, true);
	for (uint32_t i = 0; i < body_len; i++) {
		crc = crc32_step(crc, SDRAM_aEco_ota[i]);
	}
	crc = crc32_final(crc);

	crcBytes = &SDRAM_aEco_ota[body_len];
	expect =  (uint32_t)crcBytes[0]
			| ((uint32_t)crcBytes[1] << 8)
			| ((uint32_t)crcBytes[2] << 16)
			| ((uint32_t)crcBytes[3] << 24);

	if (crc != expect) {
		ota_fail(OTA_DBG_CRC_FAIL);
		return OTA_RESULT_CRC_FAIL;
	}
	ota_dbg_status_set(OTA_DBG_CRC_OK, true);

	flash_unlock_all();
	if (!flash_erase_ota_all()) {
		flash_lock_all();
		ota_fail(OTA_DBG_ERASE_FAIL);
		return OTA_RESULT_ERASE_FAIL;
	}
	ota_dbg_status_set(OTA_DBG_ERASE_OK, true);

	if (!flash_program_bytes(OTA_BASE_ADDR, SDRAM_aEco_ota, body_len)) {
		flash_lock_all();
		ota_fail(OTA_DBG_WRITE_FAIL);
		return OTA_RESULT_WRITE_FAIL;
	}
	ota_dbg_status_set(OTA_DBG_WRITE_OK, true);

	flash_lock_all();

	ota_dbg_backup_access_enable();
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR10, BKP_MAGIC_NUMBER);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR11, body_len);

	ota_dbg_status_set(OTA_DBG_BKP_OK, true);
	return OTA_RESULT_OK;
}

void ota_init(void)
{
	U08 last_status = ota_dbg_status_load();

	lOta.active = FALSE;
	lOta.overflow = FALSE;
	lOta.cnt = 0u;
	g_ota_dbg_status = last_status;

	if (last_status == OTA_DBG_BKP_OK)
	{
		ota_dbg_status_set(OTA_DBG_APP_OK, true);
	}
}

void ota_start_session(void)
{
	lOta.active = TRUE;
	lOta.overflow = FALSE;
	lOta.cnt = 0u;
	ota_dbg_status_set(OTA_DBG_RX, true);
}

void ota_end_session(void)
{
	lOta.active = FALSE;
}

void ota_on_rx_byte(U08 data)
{
	if (lOta.active == FALSE) {
		return;
	}

	if (lOta.cnt >= OTA_SDRAM_SIZE) {
		lOta.overflow = TRUE;
		lOta.active = FALSE;
		ota_dbg_status_set(OTA_DBG_LEN_FAIL, true);
		return;
	}

	SDRAM_aEco_ota[lOta.cnt++] = data;
}

//--------------------------------------------------------------------------------------------------
//  USB firmware file browser
//--------------------------------------------------------------------------------------------------
static char ota_to_lower(char c)
{
	return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c;
}

static U08 ota_str_contains_ci(const I08 *hay, const I08 *needle)
{
	const I08 *h;
	const I08 *n;

	if (!hay || !needle)
		return 0;

	for (; *hay; hay++)
	{
		h = hay;
		n = needle;
		while (*n && ota_to_lower(*h) == ota_to_lower(*n)) { h++; n++; }
		if (*n == 0)
			return 1;
	}
	return 0;
}

static U08 ota_name_is_c1d_bin(const I08 *name)
{
	const I08 *dot = strrchr(name, '.');

	if (!dot)
		return 0;
	if (ota_to_lower(dot[1]) != 'b' || ota_to_lower(dot[2]) != 'i'
		|| ota_to_lower(dot[3]) != 'n' || dot[4] != 0)
		return 0;

	return ota_str_contains_ci(name, "c1d-330");
}

static void ota_join_path(I08 *out, U16 outSize, const I08 *dir, const I08 *name)
{
	U16 len = (U16)strlen((const char *)dir);

	if (len > 0 && dir[len - 1] == '/')
		snprintf((char *)out, outSize, "%s%s", dir, name);
	else
		snprintf((char *)out, outSize, "%s/%s", dir, name);
}

U08 ota_usb_browse(const I08 *dirPath, OTA_USB_FILE *list, U08 maxCount)
{
	DIR dir;
	FILINFO fno;
	FRESULT fr;
	U08 count = 0;
	OTA_USB_FILE *p;

	if (BspUsb_IsMounted() == FALSE)
		return 0;

	// Pass 1: c1d-330 .bin files in this directory
	fr = f_opendir(&dir, (const TCHAR *)dirPath);
	if (fr != FR_OK)
		return 0;

	while (count < maxCount)
	{
		fr = f_readdir(&dir, &fno);
		if (fr != FR_OK || fno.fname[0] == 0) break;
		if (fno.fattrib & AM_DIR) continue;
		if (fno.fattrib & (AM_HID | AM_SYS)) continue;		// skip hidden/system files
		if (!ota_name_is_c1d_bin(fno.fname)) continue;
		if (fno.fsize == 0 || (U32)fno.fsize > OTA_MAX_SIZE) continue;

		p = &list[count];
		ota_join_path(p->path, OTA_USB_PATH_MAX, dirPath, fno.fname);
		snprintf((char *)p->name, OTA_USB_NAME_MAX, "%.*s", OTA_USB_NAME_MAX - 1, fno.fname);
		p->size  = (U32)fno.fsize;
		p->fdate = fno.fdate;
		p->isDir = 0;
		count++;
	}
	f_closedir(&dir);

	// Pass 2: sub-folders (so the user can navigate into them)
	fr = f_opendir(&dir, (const TCHAR *)dirPath);
	if (fr != FR_OK)
		return count;

	while (count < maxCount)
	{
		fr = f_readdir(&dir, &fno);
		if (fr != FR_OK || fno.fname[0] == 0) break;
		if (!(fno.fattrib & AM_DIR)) continue;
		if (fno.fattrib & (AM_HID | AM_SYS)) continue;		// skip "System Volume Information" etc.
		if (fno.fname[0] == '.') continue;

		p = &list[count];
		ota_join_path(p->path, OTA_USB_PATH_MAX, dirPath, fno.fname);
		snprintf((char *)p->name, OTA_USB_NAME_MAX, "[%.40s]", fno.fname);
		p->size  = 0;
		p->fdate = fno.fdate;
		p->isDir = 1;
		count++;
	}
	f_closedir(&dir);

	return count;
}

U16 ota_usb_program_file(const I08 *filename)
{
	FIL file;
	FRESULT fr;
	UINT br;
	uint32_t total = 0u;
	uint32_t expectedSize;
	const I08 *useName = filename;

	if ((useName == NULL) || (useName[0] == '\0')) {
		useName = "c1d-330.bin";
	}

	lOta.active = FALSE;
	lOta.overflow = FALSE;
	lOta.cnt = 0u;

	if (BspUsb_IsMounted() == FALSE) {
		ota_fail(OTA_DBG_USB_FILE_FAIL);
		return OTA_RESULT_FILE_FAIL;
	}

	fr = f_open(&file, (const TCHAR *)useName, FA_READ);
	if (fr != FR_OK) {
		ota_fail(OTA_DBG_USB_FILE_FAIL);
		return OTA_RESULT_FILE_FAIL;
	}

	expectedSize = (uint32_t)f_size(&file);
	if ((expectedSize < 8u) || (expectedSize > OTA_MAX_SIZE)) {
		f_close(&file);
		ota_fail(OTA_DBG_LEN_FAIL);
		return OTA_RESULT_TOO_SHORT;
	}

	while (total < OTA_MAX_SIZE)
	{
		fr = f_read(&file, &SDRAM_aEco_ota[total], 4096u, &br);
		if (fr != FR_OK) {
			f_close(&file);
			ota_fail(OTA_DBG_USB_FILE_FAIL);
			return OTA_RESULT_FILE_FAIL;
		}
		if (br == 0u) {
			break;
		}
		total += (uint32_t)br;
	}

	fr = f_close(&file);
	if (fr != FR_OK) {
		ota_fail(OTA_DBG_USB_FILE_FAIL);
		return OTA_RESULT_FILE_FAIL;
	}

	if ((total != expectedSize) || (total > OTA_MAX_SIZE)) {
		ota_fail(OTA_DBG_LEN_FAIL);
		return OTA_RESULT_TOO_SHORT;
	}

	lOta.cnt = total;
	ota_dbg_status_set(OTA_DBG_VERIFY, true);

	// Accept a full (boot+app) image or an app-only image; for a full image the
	// bootloader portion is stripped here so only the app body is staged.
	const uint8_t *body = SDRAM_aEco_ota;
	uint32_t       bodyLen = total;
	if (!ota_resolve_app(SDRAM_aEco_ota, total, &body, &bodyLen)) {
		ota_fail(OTA_DBG_USB_VECTOR_FAIL);
		return OTA_RESULT_VECTOR_FAIL;
	}

	flash_unlock_all();
	if (!flash_erase_ota_all()) {
		flash_lock_all();
		ota_fail(OTA_DBG_ERASE_FAIL);
		return OTA_RESULT_ERASE_FAIL;
	}
	ota_dbg_status_set(OTA_DBG_ERASE_OK, true);

	if (!flash_program_bytes(OTA_BASE_ADDR, body, bodyLen)) {
		flash_lock_all();
		ota_fail(OTA_DBG_WRITE_FAIL);
		return OTA_RESULT_WRITE_FAIL;
	}
	flash_lock_all();
	ota_dbg_status_set(OTA_DBG_WRITE_OK, true);

	if (!flash_verify_bytes(OTA_BASE_ADDR, body, bodyLen)) {
		ota_fail(OTA_DBG_USB_VERIFY_FAIL);
		return OTA_RESULT_VERIFY_FAIL;
	}

	ota_dbg_backup_access_enable();
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR10, BKP_MAGIC_NUMBER);
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR11, bodyLen);

	ota_dbg_status_set(OTA_DBG_BKP_OK, true);
	return OTA_RESULT_OK;
}

U16 ota_promain(void)
{
	if (lOta.overflow != FALSE) {
		ota_fail(OTA_DBG_LEN_FAIL);
		return OTA_RESULT_TOO_SHORT;
	}

	if (lOta.cnt < 7u) {
		ota_fail(OTA_DBG_LEN_FAIL);
		return OTA_RESULT_TOO_SHORT;
	}

	lOta.cnt -= 7u;
	return ota_process_from_sdram();
}