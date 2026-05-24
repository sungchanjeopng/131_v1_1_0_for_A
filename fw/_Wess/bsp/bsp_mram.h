//--------------------------------------------------------------------
//
//  Copyright (C) 2020, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of
//  WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement
//  with WESS-Global Co.,LTD
//
//  $Id: templet_format.h 1 2020-07-13 12:00:00Z eddie $
//  $Date: 2020-07-13 12:00:00 +0900 $
//  $Author: eddie $
//  $Rev: 1.0 $
//
//--------------------------------------------------------------------

#ifndef ___RAM_MR25H40_H___
#define ___RAM_MR25H40_H___


//--------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------
#include "app_sys.h"


//--------------------------------------------------------------------
//  Constant definitions
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  Type definitions
//--------------------------------------------------------------------
typedef enum {
    MRAM_CMD_WRSR  = 0x01,  // Write Status Register Command
    MRAM_CMD_WRITE = 0x02,  // Write Command
    MRAM_CMD_READ  = 0x03,  // Reset Write Enable Latch Command
    MRAM_CMD_WRDI  = 0x04,  // Set Write Enable Latch Command
    MRAM_CMD_RDSR  = 0x05,  // Read Status Register Command
    MRAM_CMD_WREN  = 0x06,  // Write Status Register Command
} MRAM_CMD;


//--------------------------------------------------------------------
//  Macros
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  Prototypes of the functions
//--------------------------------------------------------------------
extern void MRAM_WriteByte(U32 addr, U08 data);
extern void MRAM_WriteWord(U32 addr, U16 data);
extern void MRAM_WriteLong(U32 addr, U32 data);
extern void MRAM_WriteBulk(U32 addr, U08* buf, U08 cnt);
extern void MRAM_Write_3Byte(U32 addr, U32 data);

extern U08  MRAM_ReadByte(U32 addr);
extern U16  MRAM_ReadWord(U32 addr);
extern U32  MRAM_ReadLong(U32 addr);
extern void MRAM_ReadBulk(U32 addr, U08* buf, U08 cnt);

//--------------------------------------------------------------------
//  Extern global variables
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//  Extern Prototypes of the APIs
//--------------------------------------------------------------------



#endif // ___RAM_MR25H40_H___

// EOF

