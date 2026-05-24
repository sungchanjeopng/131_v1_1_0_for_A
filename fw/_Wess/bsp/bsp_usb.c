//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2026, WESS-Global Inc., All Rights Reserved.
//------------------------------------------------------------------------------------------------------------------------------
//
//  C1D-330 A USB Host BSP — state machine for USB MSC + FatFs mount/unmount
//
//  Architecture:
//    - MX_FATFS_Init() and MX_USB_HOST_Init() are called by Core/Src/main.c.
//    - MX_USB_HOST_Process() is called every main-loop iteration for fast enumeration.
//    - BspUsb_Proc() runs only the mount/unmount state machine and is called every 500 ms.
//
//------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "fatfs.h"
#include "bsp_rtc.h"
#include "usbh_core.h"
#include "bsp_usb.h"

extern USBH_HandleTypeDef hUsbHostFS;

//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
static volatile U08 s_EventFlags;
static U08 s_Status;
static U08 s_Error;
static U32 s_FreeKB;

typedef U08 (*BSP_USB_EXPORT_KEEP_FN)(I08 *filenameBuf, U16 filenameBufSize);
typedef U16 (*BSP_USB_OTA_KEEP_FN)(const I08 *filename);

extern U08 DaSAV_UsbExportCsv(I08 *filenameBuf, U16 filenameBufSize);
extern U08 LCD_SaveBmpUsb(I08 *filenameBuf, U16 filenameBufSize);
extern U16 ota_usb_program_file(const I08 *filename);

static volatile BSP_USB_EXPORT_KEEP_FN s_KeepTrendExport;
static volatile BSP_USB_EXPORT_KEEP_FN s_KeepLcdCapture;
static volatile BSP_USB_OTA_KEEP_FN s_KeepUsbOta;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions
//------------------------------------------------------------------------------------------------------------------------------
static void BspUsb_TryMount(void)
{
    FRESULT fr;
    DWORD freeClusters;
    FATFS *fs;

    // Force immediate mount (opt=1) so unsupported formats fail here.
    fr = f_mount(&USBHFatFS, (const TCHAR *)USBHPath, 1);
    if(fr != FR_OK)
    {
        s_Status = BspUsb_ST_ERROR;
        s_Error  = BspUsb_ERR_MOUNT_FAIL;
        return;
    }

    fr = f_getfree((const TCHAR *)USBHPath, &freeClusters, &fs);
    if(fr != FR_OK)
    {
        f_mount(NULL, (const TCHAR *)USBHPath, 0);
        s_Status = BspUsb_ST_ERROR;
        s_Error  = BspUsb_ERR_MOUNT_FAIL;
        return;
    }

    s_FreeKB = (U32)(((uint64_t)freeClusters * (uint64_t)fs->csize * 512ULL) / 1024ULL);
    if(s_FreeKB < BspUsb_MIN_FREE_KB)
    {
        f_mount(NULL, (const TCHAR *)USBHPath, 0);
        s_Status = BspUsb_ST_ERROR;
        s_Error  = BspUsb_ERR_DISK_FULL;
        return;
    }

    s_Status = BspUsb_ST_MOUNTED;
    s_Error  = BspUsb_ERR_NONE;
}

static void BspUsb_Unmount(void)
{
    f_mount(NULL, (const TCHAR *)USBHPath, 0);
    s_Status = BspUsb_ST_DISCONNECTED;
    s_Error  = BspUsb_ERR_NONE;
    s_FreeKB = 0;
}

static U08 BspUsb_FileSetError(BSP_USB_FILE *ctx, U08 err)
{
    if(ctx != NULL)
    {
        if(ctx->error == BspUsb_FILE_OK)
            ctx->error = err;
        return ctx->error;
    }

    return err;
}

static void BspUsb_LinkFeatureBackends(void)
{
    // These USB application backends are intentionally callable APIs. Keep them
    // linked even before a final product UI/menu action is assigned to each one.
    s_KeepTrendExport = DaSAV_UsbExportCsv;
    s_KeepLcdCapture  = LCD_SaveBmpUsb;
    s_KeepUsbOta      = ota_usb_program_file;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs
//------------------------------------------------------------------------------------------------------------------------------
void BspUsb_InitMain(void)
{
    s_Status     = BspUsb_ST_DISCONNECTED;
    s_Error      = BspUsb_ERR_NONE;
    s_EventFlags = 0;
    s_FreeKB     = 0;
    BspUsb_LinkFeatureBackends();
}

void BspUsb_SetEvent(U08 evt)
{
    s_EventFlags |= evt;
}

void BspUsb_Proc(void)
{
    U08 flags = s_EventFlags;
    s_EventFlags = 0;

    // Once mounted/error, only a true physical disconnect resets the state.
    if((s_Status == BspUsb_ST_MOUNTED) || (s_Status == BspUsb_ST_ERROR))
    {
        if(flags & BspUsb_EVT_DISCONNECTED)
        {
            if(!USBH_IsPortEnabled(&hUsbHostFS))
            {
                if(s_Status == BspUsb_ST_MOUNTED)
                    BspUsb_Unmount();
                else
                {
                    s_Status = BspUsb_ST_DISCONNECTED;
                    s_Error  = BspUsb_ERR_NONE;
                    s_FreeKB = 0;
                }
            }
        }
        return;
    }

    if(flags == 0) return;

    if(flags & BspUsb_EVT_DISCONNECTED)
    {
        s_Status = BspUsb_ST_DISCONNECTED;
        s_Error  = BspUsb_ERR_NONE;
        s_FreeKB = 0;
        return;
    }

    if((flags & BspUsb_EVT_CONNECTED) && (s_Status == BspUsb_ST_DISCONNECTED))
    {
        s_Status = BspUsb_ST_CONNECTED;
    }

    if((flags & BspUsb_EVT_CLASS_READY) && (s_Status == BspUsb_ST_CONNECTED))
    {
        BspUsb_TryMount();
    }
}

U08 BspUsb_GetStatus(void) { return s_Status; }
U08 BspUsb_GetError(void)  { return s_Error; }
U08 BspUsb_IsMounted(void) { return (s_Status == BspUsb_ST_MOUNTED) ? TRUE : FALSE; }
U32 BspUsb_GetFreeKB(void) { return s_FreeKB; }

void BspUsb_RefreshFree(void)
{
    DWORD freeClusters;
    FATFS *fs;

    if(s_Status != BspUsb_ST_MOUNTED) return;

    if(f_getfree((const TCHAR *)USBHPath, &freeClusters, &fs) == FR_OK)
    {
        s_FreeKB = (U32)(((uint64_t)freeClusters * (uint64_t)fs->csize * 512ULL) / 1024ULL);
    }
}

void BspUsb_MakeFilename(I08 *buf, U16 bufSize, const I08 *prefix, const I08 *ext)
{
    RTC_TM tm;
    const I08 *useExt = (ext != NULL) ? ext : "";

    if((buf == NULL) || (bufSize == 0))
        return;

    tm = RTC_GetTime();
    snprintf(buf, bufSize, "%s_%04u%02u%02u_%02u%02u%02u%s",
             (prefix != NULL) ? prefix : "USB",
             (U16)(2000U + tm.year), tm.month, tm.day,
             tm.hours, tm.minutes, tm.seconds,
             useExt);
}

U08 BspUsb_FileOpenUnique(BSP_USB_FILE *ctx, const I08 *filename)
{
    FRESULT fr;

    if((ctx == NULL) || (filename == NULL) || (filename[0] == '\0'))
        return BspUsb_FILE_INVALID_PARAM;

    memset(ctx, 0, sizeof(BSP_USB_FILE));

    if(!BspUsb_IsMounted())
        return BspUsb_FILE_NO_USB;

    BspUsb_RefreshFree();
    if(BspUsb_GetFreeKB() < BspUsb_MIN_FREE_KB)
        return BspUsb_FILE_DISK_FULL;

    strncpy(ctx->name, filename, BspUsb_FILENAME_MAX - 1U);
    ctx->name[BspUsb_FILENAME_MAX - 1U] = '\0';

    fr = f_open(&ctx->fil, ctx->name, FA_WRITE | FA_CREATE_NEW);
    if(fr == FR_EXIST)
    {
        I08 base[BspUsb_FILENAME_MAX];
        I08 ext[16] = "";
        I08 *dot;
        U08 idx;

        strncpy(base, ctx->name, sizeof(base) - 1U);
        base[sizeof(base) - 1U] = '\0';

        dot = strrchr(base, '.');
        if(dot != NULL)
        {
            strncpy(ext, dot, sizeof(ext) - 1U);
            ext[sizeof(ext) - 1U] = '\0';
            *dot = '\0';
        }

        for(idx = 1U; idx <= 99U; idx++)
        {
            snprintf(ctx->name, BspUsb_FILENAME_MAX, "%s_%02u%s", base, idx, ext);
            fr = f_open(&ctx->fil, ctx->name, FA_WRITE | FA_CREATE_NEW);
            if(fr != FR_EXIST)
                break;
        }
    }

    if(fr != FR_OK)
        return BspUsb_FILE_OPEN_FAIL;

    ctx->open  = TRUE;
    ctx->error = BspUsb_FILE_OK;
    return BspUsb_FILE_OK;
}

U08 BspUsb_FileWrite(BSP_USB_FILE *ctx, const void *data, U32 len)
{
    UINT bw;
    FRESULT fr;

    if((ctx == NULL) || (ctx->open == FALSE) || ((data == NULL) && (len != 0U)))
        return BspUsb_FILE_INVALID_PARAM;

    if(ctx->error != BspUsb_FILE_OK)
        return ctx->error;

    if(len == 0U)
        return BspUsb_FILE_OK;

    fr = f_write(&ctx->fil, data, (UINT)len, &bw);
    if((fr != FR_OK) || ((U32)bw != len))
        return BspUsb_FileSetError(ctx, BspUsb_FILE_WRITE_FAIL);

    return ctx->error;
}

U08 BspUsb_FileWriteLine(BSP_USB_FILE *ctx, const I08 *line)
{
    if((ctx == NULL) || (line == NULL))
        return BspUsb_FILE_INVALID_PARAM;

    if(BspUsb_FileWrite(ctx, line, (U32)strlen(line)) != BspUsb_FILE_OK)
        return ctx->error;

    return BspUsb_FileWrite(ctx, "\r\n", 2U);
}

U08 BspUsb_FilePrintf(BSP_USB_FILE *ctx, const I08 *fmt, ...)
{
    I08 line[256];
    va_list ap;
    int len;

    if((ctx == NULL) || (fmt == NULL))
        return BspUsb_FILE_INVALID_PARAM;

    va_start(ap, fmt);
    len = vsnprintf(line, sizeof(line), fmt, ap);
    va_end(ap);

    if(len <= 0)
        return ctx->error;

    if((U32)len >= sizeof(line))
        len = sizeof(line) - 1;

    return BspUsb_FileWrite(ctx, line, (U32)len);
}

U08 BspUsb_FileClose(BSP_USB_FILE *ctx)
{
    FRESULT fr;

    if(ctx == NULL)
        return BspUsb_FILE_INVALID_PARAM;

    if(ctx->open == FALSE)
        return ctx->error;

    fr = f_sync(&ctx->fil);
    if((fr != FR_OK) && (ctx->error == BspUsb_FILE_OK))
        ctx->error = BspUsb_FILE_CLOSE_FAIL;

    fr = f_close(&ctx->fil);
    if((fr != FR_OK) && (ctx->error == BspUsb_FILE_OK))
        ctx->error = BspUsb_FILE_CLOSE_FAIL;

    ctx->open = FALSE;

    if(ctx->error == BspUsb_FILE_OK)
        BspUsb_RefreshFree();

    return ctx->error;
}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------
