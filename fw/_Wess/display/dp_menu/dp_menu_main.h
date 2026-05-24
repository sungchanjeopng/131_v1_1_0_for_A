//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_MENU_MAIN_H___
#define ___DP_MENU_MAIN_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position
//------------------------------------------------------------------------------------------------------------------------------
// Box
#define DpMNU_BOX_WID				(230)
#define DpMNU_BOX_ITM_WID			(230+60)
#define DpMNU_BOX_VAL_WID			(230-60)
#define DpMNU_BOX_HEI				(282)
#define DpMNU_BOX_X0_SCT			(20)
#define DpMNU_BOX_X0_ITM			(DpMNU_BOX_X0_SCT + DpMNU_BOX_WID + 30)
#define DpMNU_BOX_X0_VAL			(DpMNU_BOX_X0_ITM + DpMNU_BOX_WID + 30)
#define DpMNU_BOX_Y0				(80)
// String
#define DpMNU_STR_X0_SCT			(DpMNU_BOX_X0_SCT + 20)
#define DpMNU_STR_X0_ITM			(DpMNU_BOX_X0_ITM + 20)
#define DpMNU_STR_X0_VAL			(DpMNU_BOX_X0_VAL + 20 + 60)
#define DpMNU_STR_Y0				(DpMNU_BOX_Y0 + 20)
#define DpMNU_STR_YG				(42)						// Gab
// Page Bar (Item)
#define DpMSR_ITM_PG_BAR_X0			(DpMNU_BOX_X0_ITM + DpMNU_BOX_WID - 14)
#define DpMSR_ITM_PG_BAR_Y0			(DpMNU_BOX_Y0 + 10)
#define DpMSR_ITM_PG_BAR_Y1			(DpMNU_BOX_Y0 + 120)
#define DpMSR_ITM_PG_BAR_WD			(6)
#define DpMSR_ITM_PG_BAR_HT			(120)


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Common
//------------------------------------------------------------------------------------------------------------------------------
#define DpMNU_ITM_PAGE			(6)

// Box - Function Page
enum {
	DpMNU_PG_0 = 0,
	DpMNU_PG_1,  
	DpMNU_PG_2,
	DpMNU_PG_3,
	DpMNU_PG_4,
	DpMNU_PG_5,
	// Number Max
	DpMNU_PG_NUM
};


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Layer
//------------------------------------------------------------------------------------------------------------------------------
// L4 - Addition
extern void DpM4_AddUpdat(void);
extern void DpM4_AddIntro(void);
// L3 - Value
extern void DpM3_UpdatPop(void);
extern void DpM3_IntroPop(void);
// L2 - Item
extern void DpM2_UpdatItm(void);
extern void DpM2_IntroItm(void);
// L1 - Sub-Section
extern void DpM1_UpdatSub(void);
extern void DpM1_IntroSub(void);
// L0 - Section
extern void DpM0_StdBySct(void);
extern void DpM0_IntroSct(void);
// Basic
extern void DpMN_InitMain(void);
extern void DpMN_UpdtBttn(U08 lyr);

extern void DpMn_PopUpdat(void);
extern void DpMn_PopIntro(void);
#endif // ___DP_MENU_MAIN_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

