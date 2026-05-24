//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___BSP_DEMUX_H___
#define ___BSP_DEMUX_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
	DMX_CMD_RD_0 = 0x00,
	DMX_CMD_RD_1,
	DMX_CMD_WR_0,
	DMX_CMD_WR_1,
	DMX_CMD_CF_0 = 0x06,		// Config
	DMX_CMD_CF_1 = 0x07,
};

enum {
	DMX_INP_MBR_ENTER = 0,
	DMX_INP_MBR_RIGHT,
	DMX_INP_MBR_LEFT_,
	DMX_INP_MBR_BACK_,
	DMX_INP_MBR_RSV_0,
	DMX_INP_MBR_RSV_1,
	DMX_INP_MBR_RSV_2,

	DMX_INP_EXT_IN_1,
	DMX_INP_EXT_IN_2,

	DMX_INP_NUMB,
};

enum {
	DMX_OUT_LCD_DISP = 0,
	DMX_OUT_LCD_BL,
	
	DMX_OUT_RX_Con_0,
	DMX_OUT_RX_Con_1,
	DMX_OUT_SEL_CH,
	DMX_OUT_CS_CURRENT,

	DMX_OUT_RELAY_4,
	DMX_OUT_RELAY_3,
	DMX_OUT_RELAY_2,
	DMX_OUT_RELAY_1,

	DMX_OUT_RF_RESETIN,
	DMX_OUT_CLEAN,

	DMX_OUT_NUMB,
};

enum {
	DMX0_P0_MSK_MBR_ENTER = 0,
	DMX0_P0_MSK_MBR_RIGHT,
	DMX0_P0_MSK_MBR_LEFT_,
	DMX0_P0_MSK_MBR_BACK_,
	DMX0_P0_MSK_MBR_RSV_0,
	DMX0_P0_MSK_MBR_RSV_1,
	DMX0_P0_MSK_MBR_RSV_2,
	DMX0_P0_MSK_MBR_NC__0,

	DMX0_P0_MAX,
};

enum {
	DMX0_P1_MSK_LCD_DISP = 0,
	DMX0_P1_MSK_LCD_BL_CTRL,
	DMX0_P1_MSK_NC_0,
	DMX0_P1_MSK_NC_1,
	DMX0_P1_MSK_NC_2,
	DMX0_P1_MSK_NC_3,
	DMX0_P1_MSK_NC_4,
	DMX0_P1_MSK_NC_5,

	DMX0_P1_MAX,
};

enum {
	DMX1_P0_MSK_RX_Con_0 = 0,
	DMX1_P0_MSK_RX_Con_1,
	DMX1_P0_MSK_SEL_CH,
	DMX1_P0_MSK_CS_CURRENT,
	DMX1_P0_MSK_NC___1,
	DMX1_P0_MSK_NC___2,
	DMX1_P0_MSK_NC___3,

	DMX1_P0_MAX,
};

enum {
	DMX1_P1_MSK_RELAY_4 = 0,
	DMX1_P1_MSK_RELAY_3,
	DMX1_P1_MSK_RELAY_2,
	DMX1_P1_MSK_RELAY_1,
	DMX1_P1_MSK_RF_RESETIN,
	DMX1_P1_MSK_CLEAN,
	DMX1_P1_MSK_EXT_IN_1,
	DMX1_P1_MSK_EXT_IN_2,

	DMX1_P1_MAX,
};

#if 1
#define DMX_MSK_MBR_ENTER			((U08)0x01)
#define DMX_MSK_MBR_RIGHT			((U08)0x02)
#define DMX_MSK_MBR_LEFT_			((U08)0x04)
#define DMX_MSK_MBR_BACK_			((U08)0x08)
#define DMX_MSK_MBR_RSV_0			((U08)0x10)
#define DMX_MSK_MBR_RSV_1			((U08)0x20)
#define DMX_MSK_MBR_RSV_2			((U08)0x40)

#define DMX_MSK_EXT_IN_1			((U08)0x40)
#define DMX_MSK_EXT_IN_2			((U08)0x80)
#endif
#define DMX_SLV_ADDR_0	((U08)0x42)
#define DMX_SLV_ADDR_1	((U08)0x44)

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	U08 out_0;			// DMX 0 - Output Port 1
	U08 out_1;			// DMX 1 - Output Port 1
} DMX_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 DMX_GetIo(U08 idx);
// Set
extern void DMX_SetIo(U08 idx, U08 out);
// Operation
extern void DMX_InitMain(void);
extern void DMX_ProcMain(void);



#endif // ___BSP_DEMUX_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

