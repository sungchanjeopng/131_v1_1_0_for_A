//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___SCREEN_MAIN_H___
#define ___SCREEN_MAIN_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Layer
enum {
	SCRN_L0_FUNC = 0,		// Function
	SCRN_L1_LIST,			// List
	SCRN_L2_VALU,			// Value
	// Number Max
	SCRN_LYR_NUM,
};

// Status
enum {
	SCRN_S0_INTRO = 0,		// Intro
	SCRN_S1_STDBY,			// Stand-By
	SCRN_S2_DTT_E,			// Detect Event
	// Number Max
	SCRN_STT_NUM,
};

// Page
enum {
	SCRN_P0_FRONT 	= 0,
	SCRN_P1_HYBRID,			// Hybrid
	SCRN_P2_ECHO, 	  		// Echo Graph
	SCRN_P3_INFO,   		// Parameters
	SCRN_P4_TREND, 	  		// Calibration
	// Number Max
	SCRN_PAG_NUM,
};

enum {
	SCRN_L2_UPDN_IDLE=0,
	SCRN_L2_UPDN_DIG,
	SCRN_L2_UPDN_DIG_VALUE,
};

enum {
	SCRN_L2_SEL_STEP0=0,
	SCRN_L2_SEL_STEP1,

	SCRN_L2_SEL_STEP_MAX
};
//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Local Struct
typedef struct {
	U08 page;				// Page
} SCRN_LS;

// Layer-0 (Function)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag: Stand-By Status Run

	U32 time;
	U08 flag;
} ScL0F_LS;

// Layer-1 (List)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag: Stand-By Status Run

	U08 iFn;				// Index: Function List

} ScL1L_LS;

// Layer-2 (Value)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag - Stand-By

	S32 min;
	S32 max;
	S32 val;				// Value

	U08 updn_mod;
	S32 updn_dig;

	U08 sel_setp;
} ScL2V_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
extern U08 SCRN_GetPage(void);
// Set Local Variables
extern void SCRN_SetPage(U08 idx);
// Operation
extern void SCRN_InitMain(void);
extern void SCRN_FtrReset(void);
extern void SCRN_ProcMain(void);



#endif // ___SCREEN_MAIN_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

