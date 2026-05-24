//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_MENU_DATA_H___
#define ___DP_MENU_DATA_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "menu_data.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
#if 1
	I08 sSct[MnDAT_SUB_NUM][16];		// Sub-Section
	I08 sIt0[MnDS0_OPT_NUM][16];		// SAVE : Item
	I08 sVl0[MnDS0_OPT_NUM][16];		// SAVE : Value
	I08 sIt1[16][16];		// COMM : Item
	I08 sVl1[16][16];		// COMM : Value

	I08 pStr[64];
#else
	I08 sItm[MnDAT_ITM_NUM][16];
	I08 sVal[MnDAT_ITM_NUM][16];
	I08 sTtl[32];
#endif
	U08 sav_prg;
} DpDAT_LS;


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
#if 1
extern I08* DpDAT_GetAddrSct(U08 idx);
extern I08* DpDAT_GetAddrIt0(U08 idx);
extern I08* DpDAT_GetAddrVl0(U08 idx);
extern I08* DpDAT_GetAddrIt1(U08 idx);
extern I08* DpDAT_GetAddrVl1(U08 idx);

// Addition
extern void DpDAT_AddUpdat(void);
extern void DpDAT_AddIntro(void);
// Pop-Up
extern void DpDAT_PopUpdat(void);
extern void DpDAT_PopIntro(void);
// Basic
extern void DpDAT_InitVari(void);
extern void DpDT1_StrSbSct(void);
extern void DpDAT_StrCntts(U08 idx);
#else
extern I08* DpDAT_GetAddrItm(U08 idx);
extern I08* DpDAT_GetAddrVal(U08 idx);
// Addition
extern void DpDAT_AddUpdat(void);
extern void DpDAT_AddIntro(void);
// Pop-Up
extern void DpDAT_PopUpdat(void);
extern void DpDAT_PopIntro(void);
// Basic
extern void DpDAT_InitVari(void);
extern void DpDT2_StrCntts(void);
#endif

#endif // ___DP_MENU_DATA_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

