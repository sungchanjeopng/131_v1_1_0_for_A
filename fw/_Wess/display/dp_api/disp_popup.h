//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DISP_POPUP_H___
#define ___DISP_POPUP_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
#define DpPOP_BGD_X0		(100)
#define DpPOP_BGD_Y0		(100)
#define DpPOP_BGD_WD		(600)

#define DpPOP_LN0_X0		(DpPOP_BGD_X0)				// 100
#define DpPOP_LN0_Y0		(DpPOP_BGD_Y0 + 70)			// 170
#define DpPOP_LN0_WD		(DpPOP_BGD_WD)				// 600
#define DpPOP_LN1_X0		(DpPOP_LN0_X0 + 50)			// 100 + 50
#define DpPOP_LN1_Y0		(DpPOP_LN0_Y0 + 60)			// 170 + 60
#define DpPOP_LN1_WD		(DpPOP_LN0_WD - 100)		// 500
#define DpPOP_LN2_X0		(DpPOP_LN1_X0)				// 150
#define DpPOP_LN2_Y0		(DpPOP_LN1_Y0 + 60)			// 230 + 60
#define DpPOP_LN2_WD		(DpPOP_LN1_WD)				// 500

#define DpPOP_TIT_X0		(130)
#define DpPOP_TIT_Y0		(110)

#define DpPOP_OLD_X0		(560)
#define DpPOP_OLD_Y0		(127)

#define DpPOP_UNT_X0		(DpPOP_OLD_X0 + 70)

#define DpPOP_CTT_YG		(60)
#define DpPOP_CT1_X0		(180)
#define DpPOP_CT1_Y0		(190)
#define DpPOP_CT2_X0		(DpPOP_CT1_X0)
#define DpPOP_CT2_Y0		(DpPOP_CT1_Y0 + DpPOP_CTT_YG)

#define DpPOP_MIN_X0		(490)
#define DpPOP_MIN_Y0		(175)
#define DpPOP_MAX_X0		(DpPOP_MIN_X0)
#define DpPOP_MAX_Y0		(DpPOP_MIN_Y0 + 27)
#define DpPOP_EXP_X0		(160)
#define DpPOP_EXP_Y0		(310)

// MENU - System - Time
#define DpPOP_TM_X0_YY		(DpPOP_CT1_X0 + 50)
#define DpPOP_TM_X0_MM		(DpPOP_TM_X0_YY + 80)
#define DpPOP_TM_X0_DD		(DpPOP_TM_X0_MM + 80)
#define DpPOP_TM_X0_HH		(DpPOP_TM_X0_DD + 80)
#define DpPOP_TM_X0_MN		(DpPOP_TM_X0_HH + 80)

#define DpPOP_TM_VL_X0		(DpPOP_CT2_X0+30)
#define DpPOP_TM_VL_Y0		(DpPOP_CT2_Y0-15)


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
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
// Set Local Variables
// Update
extern void DpPOP_UdtTitle(I08* pStr);
extern void DpPOP_UdtOldVl(I08* pStr);
extern void DpPOP_UdtExpla(I08* pStr);
extern void DpPOP_UdtRange(S32 min, S32 max);
extern void DpPOP_UdtRangeMin(I08* pStr);
extern void DpPOP_UdtRangeMax(I08* pStr);
extern void DpPOP_UdtValue(U08 ln, U08 fSel, I08* pStr);
// Basic
extern void DpPOP_InitMain(void);
extern void DpPOP_DrwIntro(void);

/* Trend Download / BLE OTA progress popups (stubs) */
extern void DpPOP_DrwDLoadStart(void);
extern void DpPOP_DrwDLoadProgress(U16 done, U16 total);
extern void DpPOP_DrwDLoadEnd(void);
extern void DpPOP_DrwOtaStart(void);
extern void DpPOP_DrwOtaProgress(U32 rxBytes, U32 totalBytes);
extern void DpPOP_DrwOtaStatus(const I08 *msg);
extern void DpPOP_DrwOtaResult(U16 result);
extern void DpPOP_DrwOtaEnd(void);


#endif // ___DISP_POPUP_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

