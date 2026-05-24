//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_MENU_OUTPUT_H___
#define ___DP_MENU_OUTPUT_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "menu_output.h"
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	I08 sSct[MnOUT_SUB_NUM][32];		// Sub-Section
	I08 sIt0[MnOS0_OPT_NUM][32];		// MnOUT_S00_CURRENT: Item
	I08 sVl0[MnOS0_OPT_NUM][32];		// MnOUT_S00_CURRENT: Value
	I08 sIt1[MnOS1_OPT_NUM][32];		// MnOUT_S01_RELAY:   Item
	I08 sVl1[MnOS1_OPT_NUM][32];		// MnOUT_S01_RELAY:   Value
	I08 sIt2[MnOS2_OPT_NUM][32];		// MnOUT_S02_PCD:     Item
	I08 sVl2[MnOS2_OPT_NUM][32];		// MnOUT_S02_PCD:     Value
	I08 sIt3[MnOS3_OPT_NUM][32];		// MnOUT_S03_ERROR:   Item
	I08 sVl3[MnOS3_OPT_NUM][32];		// MnOUT_S03_ERROR:   Value
	#if 0
	I08 sIt4[MnOS4_ITM_NUM][16];		// MnOUT_S04_COMM:    Item
	I08 sVl4[MnOS4_ITM_NUM][16];		// MnOUT_S04_COMM:    Value
	#endif
	I08 pStr[64];

} DpOUT_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set) Variables
extern I08* DpOUT_GetAddrSct(U08 idx);
extern I08* DpOUT_GetAddrIt0(U08 idx);
extern I08* DpOUT_GetAddrVl0(U08 idx);
extern I08* DpOUT_GetAddrIt1(U08 idx);
extern I08* DpOUT_GetAddrVl1(U08 idx);
extern I08* DpOUT_GetAddrIt2(U08 idx);
extern I08* DpOUT_GetAddrVl2(U08 idx);
extern I08* DpOUT_GetAddrIt3(U08 idx);
extern I08* DpOUT_GetAddrVl3(U08 idx);
#if 0
extern I08* DpOUT_GetAddrIt4(U08 idx);
extern I08* DpOUT_GetAddrVl4(U08 idx);
#endif
// Addition
extern void DpOUT_AddUpdat(void);
extern void DpOUT_AddIntro(void);
// Pop-Up
extern void DpOUT_PopUpdat(void);
extern void DpOUT_PopIntro(void);
// Basic
extern void DpOUT_InitVari(void);
extern void DpOT1_StrSbSct(void);
extern void DpOUT_StrCntts(void);



#endif // ___DP_MENU_OUTPUT_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

