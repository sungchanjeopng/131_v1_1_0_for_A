//--------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//--------------------------------------------------------------------------------------------------

#ifndef ___BSP_OTA_H___
#define ___BSP_OTA_H___

#include <stdbool.h>
#include <stdint.h>
#include "app_sys.h"

enum {
	OTA_DBG_IDLE = 0,
	OTA_DBG_RX = 1,
	OTA_DBG_FAIL = 2,
	OTA_DBG_OK = 3,
	OTA_DBG_LEN_FAIL = 4,
	OTA_DBG_CRC_FAIL = 5,
	OTA_DBG_ERASE_FAIL = 6,
	OTA_DBG_WRITE_FAIL = 7,
	OTA_DBG_BKP_OK = 8,
	OTA_DBG_VERIFY = 9,
	OTA_DBG_CRC_OK = 10,
	OTA_DBG_ERASE_OK = 11,
	OTA_DBG_WRITE_OK = 12,
	OTA_DBG_APP_OK = 13,
	OTA_DBG_USB_FILE_FAIL = 14,
	OTA_DBG_USB_VECTOR_FAIL = 15,
	OTA_DBG_USB_VERIFY_FAIL = 16
};

// BLE OTA result codes (matches Android OtaUploader.OTA_RESULT_*)
#define OTA_RESULT_OK          ((U16)0x0001)
#define OTA_RESULT_TOO_SHORT   ((U16)0x0002)
#define OTA_RESULT_CRC_FAIL    ((U16)0x0003)
#define OTA_RESULT_ERASE_FAIL  ((U16)0x0004)
#define OTA_RESULT_WRITE_FAIL  ((U16)0x0005)
#define OTA_RESULT_TIMEOUT     ((U16)0x0006)
#define OTA_RESULT_FILE_FAIL   ((U16)0x0007)
#define OTA_RESULT_VECTOR_FAIL ((U16)0x0008)
#define OTA_RESULT_VERIFY_FAIL ((U16)0x0009)

extern U08 *SDRAM_aEco_ota;

extern void ota_init(void);
extern void ota_dbg_status_set(U08 code, bool persist);
extern U08 ota_dbg_status_get(void);
extern void ota_on_rx_byte(U08 data);
extern void ota_end_session(void);
extern void ota_start_session(void);
extern U32 lota_get_cnt(void);
extern void flash_unlock_all(void);
extern void flash_lock_all(void);
extern bool flash_erase_ota_all(void);
extern U16 ota_usb_program_file(const I08 *filename);
extern U16 ota_promain(void);

#endif // ___BSP_OTA_H___