//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_SCREEN_ECHO_H___
#define ___DP_SCREEN_ECHO_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "app_main.h"
#include "screen_echo.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Basic
//------------------------------------------------------------------------------------------------------------------------------
// Box - Function Page
enum {
	DpECO_PG_0 = 0,
	DpECO_PG_1,
	DpECO_PG_2,
	DpECO_PG_NUM
};


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position (Graph)
//------------------------------------------------------------------------------------------------------------------------------
#define DpECO_GRP_X0			(40)
#define DpECO_GRP_Y0			(100)
#if 1
#define DpECO_GRP_WD			(517)
#define DpECO_GRP_WD_CURSOR		(DpECO_GRP_WD/11)
#define DpECO_GRP_WD_CURSOR_10	(DpECO_GRP_WD_CURSOR*10)

#else
#define DpECO_GRP_WD			(510)
#endif
#define DpECO_GRP_HT			(256)
#define DpECO_TRHD_100			(DpECO_GRP_Y0 + 2)
#define DpECO_TRHD_050			(DpECO_GRP_Y0 + (DpECO_GRP_HT / 2))
#define DpECO_TRHD_000			(DpECO_GRP_Y0 + DpECO_GRP_HT - 2)


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position (Level)
//------------------------------------------------------------------------------------------------------------------------------
// Title
#define DpECO_LVL_TITL_X0		(DpECO_GRP_X0 + DpECO_GRP_WD + 25)
#define DpECO_LVL_TITL_Y0		(DpECO_GRP_Y0 - 15)
// Channel
#define DpECO_LVL_CH_X0			(DpECO_LVL_TITL_X0 + 150)
#define DpECO_LVL_CH_Y0			(DpECO_LVL_TITL_Y0 + 3)
#define DpECO_LVL_CH_WD			(58)
#define DpECO_LVL_CH_HT			(32)
// Value
#define DpECO_LVL_VALU_X0		(DpECO_LVL_TITL_X0 + 50)
#define DpECO_LVL_VALU_Y0		(DpECO_LVL_TITL_Y0 + 30)
#define DpECO_LVL_VALU_WD		(110)
#define DpECO_LVL_VALU_HT		(40)
// Unit
#define DpECO_LVL_UNIT_X0		(DpECO_LVL_VALU_X0 + 115)
#define DpECO_LVL_UNIT_Y0		(DpECO_LVL_VALU_Y0)


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position (Box)
//------------------------------------------------------------------------------------------------------------------------------
// Feagure
#define DpECO_BOX_FG_X0			(DpECO_GRP_X0 + DpECO_GRP_WD + 24)
#define DpECO_BOX_FG_Y0			(190)
#define DpECO_BOX_FG_WD			(210)
#define DpECO_BOX_FG_HT			(180)
// Layer
#define DpECO_LYR_TITL_X0		(DpECO_BOX_FG_X0 + 10)
#define DpECO_LYR_TITL_Y0		(DpECO_BOX_FG_Y0 - 27)
#define DpECO_LYR_VALU_X0		(DpECO_LYR_TITL_X0 + 130)
#define DpECO_LYR_VALU_Y0		(DpECO_LYR_TITL_Y0)
// Page Bar
#define DpECO_BOX_PB_X0			(DpECO_BOX_FG_X0 + DpECO_BOX_FG_WD - 14)
#define DpECO_BOX_PB_Y0			(DpECO_BOX_FG_Y0 + 10)
#define DpECO_BOX_PB_Y1			(DpECO_BOX_PB_Y0 + 50)
#define DpECO_BOX_PB_Y2			(DpECO_BOX_PB_Y1 + 50)
#define DpECO_BOX_PB_WD			(6)
#define DpECO_BOX_PB_HT			(45)
// Title
#define DpECO_BOX_Lx_TL_HT		(30)
#define DpECO_BOX_L0_TL_X0		(DpECO_BOX_FG_X0 + 13)			// Threshold
#define DpECO_BOX_L0_TL_Y0		(DpECO_BOX_FG_Y0 + 13)
// Value
#define DpECO_BOX_L0_VL_X0		(DpECO_BOX_L0_TL_X0 + 135)		// Threshold
#define DpECO_BOX_L0_VL_Y0		(DpECO_BOX_L0_TL_Y0)
// Seclection Box
#define DpECO_BOX_L0_SB_X0		(DpECO_BOX_L0_TL_X0 - 5)		// Threshold
#define DpECO_BOX_L0_SB_Y0		(DpECO_BOX_L0_TL_Y0 - 3)
#define DpECO_BOX_Lx_SB_WD		(135)
#define DpECO_BOX_Lx_SB_HT		(25)
// Unit
#define DpECO_ASF_TITL_X0		(700)
#define DpECO_ASF_TITL_Y0		(200)
#define DpECO_ASF_TITL_WD		(80)		// width
#define DpECO_ASF_TITL_HT		(40)		// Height

// Threshold - Title
#define DpECO_THRHD_TITL_X0		(700)
#define DpECO_THRHD_TITL_Y0		(150)
#define DpECO_THRHD_TITL_WD		(80)		// width
#define DpECO_THRHD_TITL_HT		(40)		// Height


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Selection Box
typedef struct {
	U16 aX0[16];
	U16 aY0[16];
	U16 aWd[16];
	U16 aHt[16];

} DpECO_SBX;

// Local Struct
typedef struct {
	DpECO_SBX sbx;		// Selection Box
	I08 pStr[2][16];
	I08 str_list[16];
	U16 asf_r[APP_CH_NUM];
	U16 asf_h[APP_CH_NUM];
	U16 asf_x[APP_CH_NUM];
} DpECO_LS;


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
// L2
extern void DpEC2_ValUpdat(void);
extern void DpEC2_ValIntro(void);
// L1
extern void DpEC1_LstUpdat(void);
extern void DpEC1_LstIntro(void);
// L0
extern void DpEC0_FncStdBy(U08 range);
extern void DpEC0_FncIntro(void);
// Basic
extern void DpECO_InitVari(void);
// Graph
extern void DpEcoGrp_FgrTrhdTria(U08 iCh, U32 thd, U16 i);
extern void DpEcoGrp_DrawLive(U08 range);


#endif // ___DP_SCREEN_ECHO_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

