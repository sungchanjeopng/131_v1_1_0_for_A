//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___INPUT_KEY_H___
#define ___INPUT_KEY_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#define KEY_CNT_CHK_LONG   	20   	// 1sec (50ms*20)
#define KEY_CNT_CHK_RPT   	2   	// 200ms (50ms*4)

enum {
	KEY_ACT_HIGH = 0,
	KEY_ACT_LOW,

	KEY_ACT_MAX
};

enum {
	KEY_SCAN_IDLE = 0,
	KEY_SCAN_PUSHED,
	KEY_SCAN_RELEAS,
	KEY_SCAN_DISABL,

	KEY_SCAN_MAX
};

enum {
	KEY_STT_IDLE = 0,
	KEY_STT_PUSH,
	KEY_STT_RELE,		// Release
	KEY_STT_DISA,		// Disable

	KEY_STT_MAX
};

enum {
    KEY_IDX_NONE  = 0x00,
    KEY_IDX_MENU  = 0x01,
    KEY_IDX_PREV  = 0x02,
    KEY_IDX_NEXT  = 0x04,
    KEY_IDX_ENTER = 0x08,
	// Not Use
    KEY_IDX_PROG  = 0x10,
    KEY_IDX_SET   = 0x20,
    KEY_IDX_EXIT  = 0x40,
	// Test
    KEY_IDX_T1    = 0x100,		// Test-#1
    KEY_IDX_T2    = 0x200,		// Test-#2
};

enum {
	KEY_EVT_NONE   = 0x00,
	KEY_EVT_PUSH   = 0x01,
	KEY_EVT_SHORT  = 0x02,
	KEY_EVT_DMY_0  = 0x04,
	KEY_EVT_DMY_1  = 0x08,
	KEY_EVT_DTT_L  = 0x10,
	KEY_EVT_LONG   = 0x20,
	KEY_EVT_REPEAT = 0x40,
	KEY_EVT_DMY_2  = 0x80,
};

enum {
	KEY_BIT_BACK = 0,
	KEY_BIT_LEFT,
	KEY_BIT_RIGHT,
	KEY_BIT_ENTER,
	KEY_BIT_PROG,
	KEY_BIT_SET,
	KEY_BIT_EXIT,
};

enum {
	KEY_BIT_PRESS = 0,
	KEY_BIT_SHORT,
	KEY_BIT_DMY_0,
	KEY_BIT_DMY_1,
	KEY_BIT_PRS_L,
	KEY_BIT_LONG,
	KEY_BIT_REPEAT,
	KEY_BIT_DMY_2,
};


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef union {
	struct
	{
		U08 dft:1;
		U08 rls:1;
		U08 psh:1;
		U08 none:1;
		U08 _rsv:4;
	} b;
	U08 byte;

} KEY_FLG;

typedef	struct {
	KEY_FLG fDp;

	U08 act;		// Active Status (High or Low)
	U08 idx;		// Index
	U08 evt;		// Event
	U16 rpt;		// Repeat Counter

	U08 cHld;		// Holding Time Count (Long Event - Long Press, Long Click)
	U08 cRpt;		// Repeat Waiting Time Count (Double Click Event)

} KEY_LV;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------
#define _InKEY_RD_INP(REG)		(U08)((~REG)&0x0f)          // Read Input Pins


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
extern U08 InKEY_GetIdx(void);
extern U08 InKEY_GetEvt(void);
extern U16 InKEY_GetCtRpt(void);
extern U08 InKEY_GetFgNone(void);
// Set Local Variables
extern void InKEY_ClrEvt(U08 evt);
// Operation
extern void InKEY_InitMain(U08 act);
extern void InKEY_ProcMain(void);



#endif // ___INPUT_KEY_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

