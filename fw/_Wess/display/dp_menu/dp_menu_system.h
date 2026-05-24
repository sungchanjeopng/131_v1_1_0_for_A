//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_MENU_SYSTEM_H___
#define ___DP_MENU_SYSTEM_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "menu_system.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	I08 sSct[MnSYS_SUB_NUM][32];
	I08 sIt0[MnSY0_OPT_NUM][32];
	I08 sVa0[MnSY0_OPT_NUM][32];
	I08 sIt1[MnSY1_OPT_NUM][32];
	I08 sVa1[MnSY1_OPT_NUM][32];
	I08 pStr[64];

	I08 sTim[MnSYS_TIM_NUM][8];
	I08 sSel_site[MnSYS_SITE_SEL_NUM][8];

} DpSYS_LS;


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
extern I08* DpSYS_GetAddrSct(U08 idx);		
extern I08* DpSYS_GetAddrIt0(U08 idx);
extern I08* DpSYS_GetAddrVa0(U08 idx);
extern I08* DpSYS_GetAddrIt1(U08 idx);
extern I08* DpSYS_GetAddrVa1(U08 idx);

// Additional
extern void DpSYS_AddUpdat(void);
extern void DpSYS_AddIntro(void);
// Pop-Up
extern void DpSYS_BasePopUpdat(void);
extern void DpSYS_BasePopIntro(void);
extern void DpSYS_AlarmPopUpdat(void);
extern void DpSYS_AlarmPopIntro(void);
extern void DpSYS_PopIntro(void);
extern void DpSYS_PopUpdat(void);
extern void DpSy2Val_TimeUpdat(void);
extern void DpSy2Val_TimeIntro(void);

// Basic
extern void DpSYS_InitVari(void);
extern void DpSY1_StrSbSct(void);
extern void DpSY2_StrCntts(U08 sub);




#endif // ___DP_MENU_SYSTEM_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

