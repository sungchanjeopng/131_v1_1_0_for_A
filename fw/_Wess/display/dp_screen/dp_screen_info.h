//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_SCREEN_INFO_H___
#define ___DP_SCREEN_INFO_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "screen_info.h"
#include "dp_screen_front.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Basic
//------------------------------------------------------------------------------------------------------------------------------
// Sector Side
enum {
	DpPRM_SC_LEFT = 0,
	DpPRM_SC_RIGH,
	// Number Max
	DpINF_SC_NUM
};


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position
//------------------------------------------------------------------------------------------------------------------------------
// Saperate Horisontal Line
#define ScINF_LIN_X0		(80)
#define ScPRM_LIN_X1		(435)
#define ScPRM_LIN_Y0		(130)
#define ScPRM_LIN_LN		(280)
#define ScPRM_LIN_HT		(50)

// Function List
#define ScPRM_ST_X0_TTL		(40)
#define ScPRM_ST_X0_VAL		(ScPRM_ST_X0_TTL + 160 +50)
#define ScPRM_ST_X0_UNT		(ScPRM_ST_X0_VAL + 80)
#define ScPRM_ST_X1_TTL		(420)
#define ScPRM_ST_X1_VAL		(ScPRM_ST_X1_TTL + 160 +50)
#define ScPRM_ST_X1_UNT		(ScPRM_ST_X1_VAL + 90)

#define ScINF_ST_Y0_TTL		(130)
#define ScPRM_ST_Y0_VAL		(ScINF_ST_Y0_TTL - 5)
#define ScPRM_ST_Y0_UNT		(ScINF_ST_Y0_TTL)

// Seclection Box
#define DpPRM_SBX_L0_SB_X0		(ScPRM_ST_X0_TTL - 5)
#define DpPRM_SBX_L0_SB_X1		(ScPRM_ST_X1_TTL - 5)
#define DpPRM_SBX_L0_SB_Y0		(ScINF_ST_Y0_TTL - 3)
#define DpPRM_SBX_Lx_SB_WD		(150)
#define DpPRM_SBX_Lx_SB_HT		(30)

#define ScPRM_ST_X0_CH		(DpFRT_LVL_CHNL_X0)
#define ScPRM_ST_X1_CH		(DpFRT_LVL_CHNL_X1)
#define ScPRM_ST_Y0_CH		(DpFRT_LVL_CHNL_Y0)

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Selection Box
typedef struct {
	U16 aX0[ScINF_OPT_NUM];
	U16 aY0[ScINF_OPT_NUM];
	U16 aWd[ScINF_OPT_NUM];
	U16 aHt[ScINF_OPT_NUM];

} DpPRM_SBX;

// Local Struct
typedef struct {
	DpPRM_SBX sbx;		// Selection Box
	I08 pStr[32];
	I08 pStr2[32];
} DpPRM_LS;


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
// L3
extern void DpIF2_ValUpdat(U08 fDp);
extern void DpIF2_ValIntro(void);
// L1
extern void DpIF1_LstUpdat(void);
extern void DpIF1_LstIntro(void);
// L0
extern void DpIF0_FncStdBy(void);
extern void DpIF0_FncIntro(void);
// Basic
extern void DpINF_InitVari(void);



#endif // ___DP_SCREEN_INFO_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

