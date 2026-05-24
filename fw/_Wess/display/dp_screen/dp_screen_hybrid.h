//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DISP_screen_hybrid_H___
#define ___DISP_screen_hybrid_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "bsp_rtc.h"
#include "screen_hybrid.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position
//------------------------------------------------------------------------------------------------------------------------------
// Level - Title
#define Dphyb_LVL_TITL_X0		(82)
#define Dphyb_LVL_TITL_Y0		(72)
#define Dphyb_LVL_TITL_WD		(188)		// width
#define Dphyb_LVL_TITL_HT		(60)		// Height

// Level - Value
#if 0
#define Dphyb_LVL_VALU_X10		(110)
#define Dphyb_LVL_VALU_X01		(Dphyb_LVL_VALU_X10+40)
#define Dphyb_LVL_VALU_X0p		(Dphyb_LVL_VALU_X01+40)
#define Dphyb_LVL_VALU_Xp1		(Dphyb_LVL_VALU_X0p+20)
#define Dphyb_LVL_VALU_Xp2		(Dphyb_LVL_VALU_Xp1+40)
#endif
#define Dphyb_LVL_VALU_X0		(230)
#define Dphyb_LVL_VALU_X1		(630)
#define Dphyb_LVL_VALU_Y0		(180)
#define Dphyb_LVL_VALU_Y1		(300)

// Level - Unit
#define Dphyb_LVL_UNIT_X0		(Dphyb_LVL_VALU_X0+210)
#define Dphyb_LVL_UNIT_Y0		(Dphyb_LVL_VALU_Y0)
#define Dphyb_LVL_UNIT_WD		(100)		// width
#define Dphyb_LVL_UNIT_HT		(105)		// Height

// Level - Channel
#define Dphyb_LVL_CHNL_X0		(Dphyb_LVL_TITL_X0+240)
#define Dphyb_LVL_CHNL_Y0		(Dphyb_LVL_TITL_Y0+8)
#define Dphyb_LVL_CHNL_WD		(70)		// width
#define Dphyb_LVL_CHNL_HT		(36)		// Height

// Box - Boundary
#define Dphyb_BX_BDR_X0			(30)
#define Dphyb_BX_BDR_Y0			(250)
#if 1
#define Dphyb_BX_BDR_WD			(380)
#else
#define Dphyb_BX_BDR_WD			(480)
#endif
#define Dphyb_BX_BDR_HT			(100)
// Box L0 - Level
#define Dphyb_BX_LV_IC_X0		(Dphyb_BX_BDR_X0+40)		// Icon
#define Dphyb_BX_LV_TL_X0		(Dphyb_BX_BDR_X0+65)		// Title
#define Dphyb_BX_LV_VL_X0		(Dphyb_BX_BDR_X0+230)		// Value
#if 1
#define Dphyb_BX_LV_UN_X0		(Dphyb_BX_BDR_X0+320)		// Unit
#else
#define Dphyb_BX_LV_UN_X0		(Dphyb_BX_BDR_X0+330)		// Unit
#endif
#define Dphyb_BX_LV_TL_WD		(100)						// Width
#define Dphyb_BX_LV_TL_HT		(40)						// Height
#define Dphyb_BX_LEVEL_Y0		(Dphyb_BX_BDR_Y0+20)		// Title
// Box L1 - Current Title
#define Dphyb_BX_CR_IC_X0		(Dphyb_BX_LV_IC_X0)
#define Dphyb_BX_CR_TL_X0		(Dphyb_BX_LV_TL_X0)
#define Dphyb_BX_CR_VL_X0		(Dphyb_BX_LV_VL_X0)			// Value
#define Dphyb_BX_CR_UN_X0		(Dphyb_BX_LV_UN_X0)			// Unit
#define Dphyb_BX_CURRT_Y0		(Dphyb_BX_LEVEL_Y0+Dphyb_BX_LV_TL_HT)
// Box L2 - Time
#define Dphyb_BX_RTC_T_X0		(Dphyb_BX_BDR_X0+15)
#define Dphyb_BX_RTC_T_Y0		(Dphyb_BX_BDR_Y0+Dphyb_BX_BDR_HT+3)

// Tank - Boundary
#define Dphyb_TK_BDR_X0			(60)
#define Dphyb_TK_BDR_X1			(460)
#define Dphyb_TK_BDR_Y0			(125)
#define Dphyb_TK_BDR_WD			(100)
#if 1
#define Dphyb_TK_BDR_HT			(240)
#else
#define Dphyb_TK_BDR_HT			(250)
#endif
// Tank - Temparature - Value
#define Dphyb_TPRT_VL_X0		(Dphyb_TK_BDR_X0)
#define Dphyb_TPRT_VL_X1		(Dphyb_TK_BDR_X1)
#define Dphyb_TPRT_VL_Y0		(Dphyb_TK_BDR_Y0-20)
// Tank - Sensor Depth - Title
#define Dphyb_S_DEP_TL_X0		(Dphyb_TK_BDR_X0-110)
#define Dphyb_S_DEP_TL_Y0		(Dphyb_TK_BDR_Y0)
// Tank - Sensor Depth - Value
#define Dphyb_S_DEP_VL_X0		(Dphyb_TK_BDR_X0-85)
#define Dphyb_S_DEP_VL_Y0		(Dphyb_S_DEP_TL_Y0+30)
// Tank - Sensor Depth - Unit
#define Dphyb_S_DEP_UN_X0		(Dphyb_S_DEP_VL_X0+55)
#define Dphyb_S_DEP_UN_Y0		(Dphyb_S_DEP_VL_Y0)
// Tank - Deadzone - Title
#define Dphyb_DEADZ_TL_X0		(Dphyb_S_DEP_TL_X0)
#define Dphyb_DEADZ_TL_Y0		(Dphyb_S_DEP_TL_Y0+70)
// Tank - Deadzone - Value
#define Dphyb_DEADZ_VL_X0		(Dphyb_S_DEP_VL_X0)
#define Dphyb_DEADZ_VL_Y0		(Dphyb_DEADZ_TL_Y0+30)
#if 1
// Tank - Field Structure Location - Title
#define Dphyb_FS_BOX_XO			(Dphyb_S_DEP_TL_X0-15)
#define Dphyb_FS_BOX_Y0			(Dphyb_DEADZ_TL_Y0+60)
#define Dphyb_FS_BOX_WD			(120)						// Width
#define Dphyb_FS_BOX_HT			(160)						// Height
#define Dphyb_FS_LOC_TL_X0		(Dphyb_S_DEP_TL_X0)
#define Dphyb_FS_LOC_TL_Y0		(Dphyb_DEADZ_TL_Y0+70)
// Tank - Field Structure Location - Value
#define Dphyb_FS_LOC_VL_X0		(Dphyb_FS_LOC_TL_X0+25)
#define Dphyb_FS_LOC_VL_Y0		(Dphyb_FS_LOC_TL_Y0+22)
// Tank - Field Structure Direction - Title
#define Dphyb_FS_DIR_TL_X0		(Dphyb_FS_LOC_TL_X0)
#define Dphyb_FS_DIR_TL_Y0		(Dphyb_FS_LOC_TL_Y0+50)
// Tank - Field Structure Direction - Value
#define Dphyb_FS_DIR_VL_X0		(Dphyb_FS_LOC_TL_X0+25)
#define Dphyb_FS_DIR_VL_Y0		(Dphyb_FS_DIR_TL_Y0+22)
// Tank - Field Structure Velocity - Title
#define Dphyb_FS_VEL_TL_X0		(Dphyb_FS_LOC_TL_X0)
#define Dphyb_FS_VEL_TL_Y0		(Dphyb_FS_DIR_TL_Y0+50)
// Tank - Field Structure Velocity - Value
#define Dphyb_FS_VEL_VL_X0		(Dphyb_FS_LOC_TL_X0+25)
#define Dphyb_FS_VEL_VL_Y0		(Dphyb_FS_VEL_TL_Y0+22)
// Tank - Field Structure Velocity - Unit
#define Dphyb_FS_VEL_UN_X0		(Dphyb_FS_VEL_VL_X0+40)
#define Dphyb_FS_VEL_UN_Y0		(Dphyb_FS_VEL_VL_Y0)
#endif
// Tank - Deadzone - Unit
#define Dphyb_DEADZ_UN_X0		(Dphyb_DEADZ_VL_X0+55)
#define Dphyb_DEADZ_UN_Y0		(Dphyb_DEADZ_VL_Y0)
// Tank - Tank Depth - Title
#define Dphyb_T_DEP_TL_X0		(Dphyb_TK_BDR_X0+5)
#define Dphyb_T_DEP_TL_Y0		(Dphyb_TK_BDR_Y0+Dphyb_TK_BDR_HT+7)
// Tank - Tank Depth - Value
#define Dphyb_T_DEP_VL_X0		(Dphyb_T_DEP_TL_X0+120)
#define Dphyb_T_DEP_VL_Y0		(Dphyb_T_DEP_TL_Y0)
// Tank - Tank Depth - Unit
#define Dphyb_T_DEP_UN_X0		(Dphyb_T_DEP_VL_X0+60)
#define Dphyb_T_DEP_UN_Y0		(Dphyb_T_DEP_TL_Y0)


// Function Indix - FieldA
enum {
	// Page 0
	ScHYB_FID_A_F00_DIRE=0,
	ScHYB_FID_A_F01_VELO,
	ScHYB_FID_A_F02_POSI,
	// Number Max (FieldA)
	ScHYB_FID_A_NUM,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Selection Box
typedef struct {
#if 0
	U16 aX0[ScHYB_FNC_NUMB+1];
	U16 aY0[ScHYB_FNC_NUMB+1];
	U16 aWd[ScHYB_FNC_NUMB+1];
	U16 aHt[ScHYB_FNC_NUMB+1];
#endif
} Dphyb_SBX;

typedef struct {
	Dphyb_SBX sbx;		// Selection Box
	RTC_TM time;		// Box - Time

	U16 level;
	U16 bx_lv;			// Box - level
	U08 unit;			// Box - Unit
	U16 curr;			// Box - Current
	U16 tprt;			// Tank - Temperature

} Dphyb_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// L2
extern void DpHY2_ValUpdat(void);
extern void DpHY2_ValIntro(void);
// L1
extern void DpHY1_LstUpdat(void);
extern void DpHY1_LstIntro(void);
// L0
extern void DpHY0_FncStdBy(void);
extern void DpHY0_FncIntro(void);
// Basic
extern void Dphyb_InitVari(void);



#endif // ___DISP_screen_hybrid_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

