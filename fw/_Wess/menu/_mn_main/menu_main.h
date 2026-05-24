//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_MAIN_H___
#define ___MENU_MAIN_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//	Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
// Layer
enum {
	MENU_L0_SECTION = 0,
	MENU_L1_SUB_SCT,
	MENU_L2_ITEM,
	MENU_L3_VALUE,
	MENU_L4_ADDITION,
	// Number Max
	MENU_LYR_NUM,
};

// Satatus
enum {
	MENU_S0_INTRO = 0,		// Intro
	MENU_S1_STDBY,			// Stand-By
	MENU_S2_DTT_E,			// Detect Event
	MENU_S3_ENTER,			// Next Layer
	// Number Max
	MENU_STT_NUM,
};

// Section
enum {
	MENU_SC0_MEAS = 0,		// Measurement
	MENU_SC1_OUTP,
	MENU_SC2_DATA,
	MENU_SC3_SYST,
	// Hidden Menu
	MENU_SC4_EGNR,
	MENU_SC5_FCTR,
	MENU_SC6_TEST,
	// Number Max
	MENU_SCN_NUM,
};

// Check
enum {
	MENU_CHK_NO = 0,
	MENU_CHK_YES,
	// Number Max
	MENU_CHK_NUM,
};

// Activation
enum {
	MENU_ATV_OFF = 0,
	MENU_ATV_ON,
	// Number Max
	MENU_ATV_NUM,
};

#define MENU_VAL_INVALID		(0xffffffff)

enum {
	MENU_HIDDEN_IDLE = 0,
	MENU_HIDDEN_ENGR,
	MENU_HIDDEN_FCTR,

	MENU_HIDDEN_NUM,
};
//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Local Struct
typedef struct {
	U08 lyr;				// Layer
	U08 sct;				// Section
	S16 pass_mode;
	U08 pass;
	S32 pass_val;
	S32 pass_dig;
	U08 step;
	// Flag - Display
	U08 fHd; 				// Hidden Menu
	U08 fTt;				// Title
	U08 fSb;

} MENU_LS;

// Section
typedef struct {
	U08 lyr;				// layer

} MnSCT_LS;

// Layer-0 (Section)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag: Stand-By Status Run

} MnL0S_LS;

// Layer-1 (Item)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag: Stand-By

	U08 iIt;				// Index: Item

} MnL1I_LS;

// Layer-2 (Value)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag: Stand-By

	S32 val;				// Index: Item

} MnL2V_LS;

// Layer-3 (Addition)
typedef struct {
	U08 stt;				// Status
	U08 fSb;				// Flag: Stand-By

	S32 val;				// Index: Item

} MnL3A_LS;

enum {
	PASS_UPDN_DIG = 0,
	PASS_UPDN_DIG_VALUE,

};
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
extern U08 MENU_GetLayer(void);
extern U08 MENU_GetSection(void);
extern U08 MENU_GetFgHiddn(void);
extern S32 MENU_GetPassMode(void)      ;
extern S32 MENU_GetPassdig(void);
extern S32 MENU_GetPassVal(void)      ;

// Set Local Variables
extern void MENU_SetLayer(U08 lyr);
extern void MENU_SetSection(U08 idx);
extern void MENU_SetFgHiddn(U08 fHd);
// Parameters
extern void MENU_PrRst_Factory(void);
// Operation
extern void MENU_InitSect(U08 Sel);
extern void MENU_InitMain(void);
extern void MENU_ExitMain(void);
extern void MENU_ProcMain(void);



#endif // ___MENU_MAIN_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

