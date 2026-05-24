//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DP_SCREEN_CALIB_H___
#define ___DP_SCREEN_CALIB_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "screen_calib.h"
#include "dp_screen_echo.h"
#include "measure_calc.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Basic
//------------------------------------------------------------------------------------------------------------------------------
// Box - Function Page
enum {
	DpCLB_PG_0 = 0,
	DpCLB_PG_1,
	DpCLB_PG_2,
	DpCLB_PG_NUM
};

// Page
#define ScCLB_FNC_PAGE			(5)


enum {
	DpCLB_GAIN_LOW = 0,
	DpCLB_GAIN_HIGH,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position
//------------------------------------------------------------------------------------------------------------------------------
// Graph
#define DpCLB_GRP_X0			(DpECO_GRP_X0 + 10)
#define DpCLB_GRP_Y0			(DpECO_GRP_Y0)
#define DpCLB_GRP_WD			(DpECO_GRP_WD)
#define DpCLB_GRP_WD_CURSOR		(DpECO_GRP_WD/6)
#define DpCLB_GRP_WD_CURSOR_10	(DpECO_GRP_WD-DpECO_GRP_WD_CURSOR)

#define DpCLB_GRP_HT			(225)
#define DpCLB_GAIN_100			(DpECO_TRHD_100)
#define DpCLB_GAIN_000			(DpECO_TRHD_050)
#define DpCLB_GAIN_P01			(DpECO_TRHD_000)
#define DpCLB_GAIN_HT			(DpECO_GRP_HT-8)

// Graph
#define DpCLB_TVG_DIS_X0		(DpECO_GRP_WD/TVG_IDX_MAX)

// Box - Feagure
#define DpCLB_BOX_FG_X0			(DpECO_BOX_FG_X0)
#define DpCLB_BOX_FG_Y0			(DpECO_BOX_FG_Y0)
#define DpCLB_BOX_FG_WD			(DpECO_BOX_FG_WD + 5)
#define DpCLB_BOX_FG_HT			(DpECO_BOX_FG_HT)
// Box - Page Bar
#define DpCLB_BOX_PB_X0			(DpECO_BOX_PB_X0)
#define DpCLB_BOX_PB_Y0			(DpECO_BOX_PB_Y0)
#define DpCLB_BOX_PB_Y1			(DpECO_BOX_PB_Y1)
#define DpCLB_BOX_PB_Y2			(DpECO_BOX_PB_Y2)
#define DpCLB_BOX_PB_WD			(DpECO_BOX_PB_WD)
#define DpCLB_BOX_PB_HT			(DpECO_BOX_PB_HT)
// Box - Title
#define DpCLB_BOX_Lx_TL_HT		(DpECO_BOX_Lx_TL_HT)
#define DpCLB_BOX_L0_TL_X0		(DpECO_BOX_L0_TL_X0)			// Threshold
#define DpCLB_BOX_L0_TL_Y0		(DpECO_BOX_L0_TL_Y0)
// Box - Value
#define DpCLB_BOX_L0_VL_X0		(DpECO_BOX_L0_VL_X0)			// Threshold
#define DpCLB_BOX_L0_VL_Y0		(DpCLB_BOX_L0_TL_Y0)
// Box - Seclection Box
#define DpCLB_BOX_L0_SB_X0		(DpECO_BOX_L0_SB_X0)			// Threshold
#define DpCLB_BOX_L0_SB_Y0		(DpECO_BOX_L0_SB_Y0)
#define DpCLB_BOX_Lx_SB_WD		(DpECO_BOX_Lx_SB_WD)
#define DpCLB_BOX_Lx_SB_HT		(DpCLB_BOX_Lx_TL_HT)

// Level - Title
#define DpCLB_LVL_TITL_X0		(DpECO_LVL_TITL_X0)
#define DpCLB_LVL_TITL_Y0		(100)
#define DpCLB_LVL_TITL_Y1		(250-10)

// Level - Unit
#define DpCLB_LVL_UNIT_X0		(DpECO_LVL_UNIT_X0)
#define DpCLB_LVL_UNIT_Y0		(DpECO_LVL_UNIT_Y0)
// Level - Channel
#define DpCLB_LVL_CH_X0			(DpECO_LVL_CH_X0)
#define DpCLB_LVL_CH_Y0			(DpECO_LVL_CH_Y0 -5)
#define DpCLB_LVL_CH_WD			(DpECO_LVL_CH_WD)
#define DpCLB_LVL_CH_HT			(DpECO_LVL_CH_HT)
// Level - Value
#define DpCLB_LVL_VAL_X0		(DpECO_LVL_VALU_X0)
#define DpCLB_LVL_VAL_Y0		(DpCLB_LVL_TITL_Y0+30)
#define DpCLB_LVL_VAL_Y1		(DpCLB_LVL_TITL_Y1+30)

#define DpCLB_LVL_VAL_WD		(DpECO_LVL_VALU_WD)
#define DpCLB_LVL_VAL_HT		(DpECO_LVL_VALU_HT)

#if 0
// Level - Unit
#define DpECO_ASF_TITL_X0		(700)
#define DpECO_ASF_TITL_Y0		(200)
#define DpECO_ASF_TITL_WD		(80)		// width
#define DpECO_ASF_TITL_HT		(40)		// Height

// Threshold - Title
#define DpECO_THRHD_TITL_X0		(700)
#define DpECO_THRHD_TITL_Y0		(150)
#define DpECO_THRHD_TITL_WD		(80)		// width
#define DpECO_THRHD_TITL_HT		(40)		// Height
#endif


//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Selection Box
typedef struct {
	U16 aX0[ScCLB_OPT_NUM];
	U16 aY0[ScCLB_OPT_NUM];
	U16 aWd[ScCLB_OPT_NUM];
	U16 aHt[ScCLB_OPT_NUM];
} DpCLB_SBX;

// Local Struct
typedef struct {
	DpCLB_SBX sbx;		// Selection Box
	I08 pStr[2][16];
	U16 max[MsCAL_THR_TYPE_NUM];
	U16 min[MsCAL_THR_TYPE_NUM];

	U32 time;
	U08 flag;
} DpCLB_LS;


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
extern void DpClbLvl_StrChnnl(void);
// Set Local Variables
extern void DpCLB_Set_Trend_flag(U08 flag);
// L2
extern void DpCB2_ValUpdat(U08 fClr);
extern void DpCB2_ValIntro(void);
// L1
extern void DpCB1_LstUpdat(void);
extern void DpCB1_LstIntro(void);
// L0
extern void DpCB0_FncStdBy(U08 range);
extern void DpCB0_FncIntro(void);
// Basic
extern void DpCLB_InitVari(void);



#endif // ___DP_SCREEN_CALIB_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

