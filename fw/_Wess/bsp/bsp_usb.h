//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2026, WESS-Global Inc., All Rights Reserved.
//------------------------------------------------------------------------------------------------------------------------------
//
//  C1D-330 A USB Host BSP — USB MSC + FatFs mount state machine
//
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___BSP_USB_H___
#define ___BSP_USB_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "fatfs.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
    BspUsb_ST_DISCONNECTED = 0,     // USB not connected
    BspUsb_ST_CONNECTED,            // Connected, enumeration in progress
    BspUsb_ST_MOUNTED,              // FatFs mounted, file I/O ready
    BspUsb_ST_ERROR,                // Mount failure or I/O error
};

enum {
    BspUsb_ERR_NONE = 0,
    BspUsb_ERR_MOUNT_FAIL,          // f_mount() failed (unsupported format, etc.)
    BspUsb_ERR_DISK_FULL,           // Free space is below BspUsb_MIN_FREE_KB
};

enum {
    BspUsb_FILE_OK = 0,
    BspUsb_FILE_NO_USB,
    BspUsb_FILE_DISK_FULL,
    BspUsb_FILE_OPEN_FAIL,
    BspUsb_FILE_WRITE_FAIL,
    BspUsb_FILE_READ_FAIL,
    BspUsb_FILE_CLOSE_FAIL,
    BspUsb_FILE_INVALID_PARAM,
};

// Event bit flags (ORed in USBH callback, consumed in BspUsb_Proc)
#define BspUsb_EVT_CONNECTED    (0x01U)
#define BspUsb_EVT_CLASS_READY  (0x02U)
#define BspUsb_EVT_DISCONNECTED (0x04U)

// Shared free-space threshold
#define BspUsb_MIN_FREE_KB      (1024U)         // 1 MB minimum
#define BspUsb_FILENAME_MAX     (64U)

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
    FIL fil;
    I08 name[BspUsb_FILENAME_MAX];
    U08 open;
    U08 error;
} BSP_USB_FILE;

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
extern void BspUsb_InitMain(void);
extern void BspUsb_Proc(void);              // State machine only (MX_USB_HOST_Process is called from main loop)
extern void BspUsb_SetEvent(U08 evt);       // Called from USBH_UserProcess callback
extern U08  BspUsb_GetStatus(void);
extern U08  BspUsb_GetError(void);
extern U08  BspUsb_IsMounted(void);
extern U32  BspUsb_GetFreeKB(void);
extern void BspUsb_RefreshFree(void);
extern void BspUsb_MakeFilename(I08 *buf, U16 bufSize, const I08 *prefix, const I08 *ext);
extern U08  BspUsb_FileOpenUnique(BSP_USB_FILE *ctx, const I08 *filename);
extern U08  BspUsb_FileWrite(BSP_USB_FILE *ctx, const void *data, U32 len);
extern U08  BspUsb_FileWriteLine(BSP_USB_FILE *ctx, const I08 *line);
extern U08  BspUsb_FilePrintf(BSP_USB_FILE *ctx, const I08 *fmt, ...);
extern U08  BspUsb_FileClose(BSP_USB_FILE *ctx);

#endif // ___BSP_USB_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------
