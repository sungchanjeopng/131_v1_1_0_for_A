//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DISP_SCREEN_FRONT_H___
#define ___DISP_SCREEN_FRONT_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "app_main.h"
#include "bsp_rtc.h"
#include "screen_front.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Position
//------------------------------------------------------------------------------------------------------------------------------
// Level - Title
#define DpFRT_LVL_TITL_X0		(40)
#define DpFRT_LVL_TITL_Y0		(72)
#define DpFRT_LVL_TITL_WD		(188)		// width
#define DpFRT_LVL_TITL_HT		(60)		// Height

#define DpFRT_LINE_X0		(30)
#define DpFRT_LINE_X1		(410)
#define DpFRT_LINE_Y0		(110)
#define DpFRT_LINE_Y1		(236)
#define DpFRT_LINE_Y1		(236)
#define DpFRT_LINE_Y2		(362)

#define DpFRT_LINE_SINGLE_X0 (550)

#define DpFRT_LINE_WD		(360)		// width
#define DpFRT_LINE_HT		(60)		// Height

// Level - Value
#if 0
#define DpFRT_LVL_VALU_X10		(110)
#define DpFRT_LVL_VALU_X01		(DpFRT_LVL_VALU_X10+40)
#define DpFRT_LVL_VALU_X0p		(DpFRT_LVL_VALU_X01+40)
#define DpFRT_LVL_VALU_Xp1		(DpFRT_LVL_VALU_X0p+20)
#define DpFRT_LVL_VALU_Xp2		(DpFRT_LVL_VALU_Xp1+40)
#endif
#define DpFRT_LVL_VALU_X0		(35)
#define DpFRT_LVL_VALU_Y0		(130)
#define DpFRT_LVL_VALU_Y1		(230)

#define DpFRT_LVL_VALU_SINGLE_Y0		(130)
#define DpFRT_LVL_VALU_SINGLE_Y1		(260)

#define DpFRT_SUB_VALU_X0		(35)
#define DpFRT_SUB_VALU_Y0		(256)
#define DpFRT_SUB_VALU_Y1		(372)

// Level - Unit
#define DpFRT_LVL_UNIT_X0		(DpFRT_LVL_VALU_X0+210)
#define DpFRT_LVL_UNIT_Y0		(DpFRT_LVL_VALU_Y0)
#define DpFRT_LVL_UNIT_WD		(100)		// width
#define DpFRT_LVL_UNIT_HT		(105)		// Height

// Level - Channel
#define DpFRT_LVL_CHNL_X0		(150)
#define DpFRT_LVL_CHNL_X1		(530)

#define DpFRT_LVL_CHNL_Y0		(DpFRT_LVL_TITL_Y0)
#define DpFRT_LVL_CHNL_WD		(100)		// width
#define DpFRT_LVL_CHNL_HT		(20)		// Height

// Box - Boundary
#define DpFRT_BX_BDR_X0			(30)
#define DpFRT_BX_BDR_Y0			(250)
#if 1
#define DpFRT_BX_BDR_WD			(380)
#else
#define DpFRT_BX_BDR_WD			(480)
#endif
#define DpFRT_BX_BDR_HT			(100)
// Box L0 - Level
#define DpFRT_BX_LV_IC_X0		(DpFRT_BX_BDR_X0+40)		// Icon
#define DpFRT_BX_LV_TL_X0		(DpFRT_BX_BDR_X0+65)		// Title
#define DpFRT_BX_LV_VL_X0		(DpFRT_BX_BDR_X0+230)		// Value
#if 1
#define DpFRT_BX_LV_UN_X0		(DpFRT_BX_BDR_X0+320)		// Unit
#else
#define DpFRT_BX_LV_UN_X0		(DpFRT_BX_BDR_X0+330)		// Unit
#endif
#define DpFRT_BX_LV_TL_WD		(100)						// Width
#define DpFRT_BX_LV_TL_HT		(40)						// Height
#define DpFRT_BX_LEVEL_Y0		(DpFRT_BX_BDR_Y0+20)		// Title
// Box L1 - Current Title
#define DpFRT_BX_CR_IC_X0		(DpFRT_BX_LV_IC_X0)
#define DpFRT_BX_CR_TL_X0		(DpFRT_BX_LV_TL_X0)
#define DpFRT_BX_CR_VL_X0		(DpFRT_BX_LV_VL_X0)			// Value
#define DpFRT_BX_CR_UN_X0		(DpFRT_BX_LV_UN_X0)			// Unit
#define DpFRT_BX_CURRT_Y0		(DpFRT_BX_LEVEL_Y0+DpFRT_BX_LV_TL_HT)
// Box L2 - Time
#define DpFRT_BX_RTC_T_X0		(DpFRT_BX_BDR_X0+15)
#define DpFRT_BX_RTC_T_Y0		(DpFRT_BX_BDR_Y0+DpFRT_BX_BDR_HT+3)

// Tank - Boundary
#define DpFRT_TK_BDR_X0			(550)
#define DpFRT_TK_BDR_Y0			(85)
#define DpFRT_TK_BDR_WD			(221)
#if 1
#define DpFRT_TK_BDR_HT			(258)
#else
#define DpFRT_TK_BDR_HT			(250)
#endif
// Tank - Temparature - Value
#define DpFRT_TPRT_VL_X0		(DpFRT_TK_BDR_X0+165)
#define DpFRT_TPRT_VL_Y0		(DpFRT_TK_BDR_Y0-20)
// Tank - Sensor Depth - Title
#define DpFRT_S_DEP_TL_X0		(DpFRT_TK_BDR_X0-110)
#define DpFRT_S_DEP_TL_Y0		(DpFRT_TK_BDR_Y0)
// Tank - Sensor Depth - Value
#define DpFRT_S_DEP_VL_X0		(DpFRT_TK_BDR_X0-85)
#define DpFRT_S_DEP_VL_Y0		(DpFRT_S_DEP_TL_Y0+30)
// Tank - Sensor Depth - Unit
#define DpFRT_S_DEP_UN_X0		(DpFRT_S_DEP_VL_X0+55)
#define DpFRT_S_DEP_UN_Y0		(DpFRT_S_DEP_VL_Y0)
// Tank - Deadzone - Title
#define DpFRT_DEADZ_TL_X0		(DpFRT_S_DEP_TL_X0)
#define DpFRT_DEADZ_TL_Y0		(DpFRT_S_DEP_TL_Y0+70)
// Tank - Deadzone - Value
#define DpFRT_DEADZ_VL_X0		(DpFRT_S_DEP_VL_X0)
#define DpFRT_DEADZ_VL_Y0		(DpFRT_DEADZ_TL_Y0+30)
#if 1
// Tank - Field Structure Location - Title
#define DpFRT_FS_BOX_XO			(DpFRT_S_DEP_TL_X0-15)
#define DpFRT_FS_BOX_Y0			(DpFRT_DEADZ_TL_Y0+60)
#define DpFRT_FS_BOX_WD			(120)						// Width
#define DpFRT_FS_BOX_HT			(160)						// Height
#define DpFRT_FS_LOC_TL_X0		(DpFRT_S_DEP_TL_X0)
#define DpFRT_FS_LOC_TL_Y0		(DpFRT_DEADZ_TL_Y0+70)
// Tank - Field Structure Location - Value
#define DpFRT_FS_LOC_VL_X0		(DpFRT_FS_LOC_TL_X0+25)
#define DpFRT_FS_LOC_VL_Y0		(DpFRT_FS_LOC_TL_Y0+22)
// Tank - Field Structure Direction - Title
#define DpFRT_FS_DIR_TL_X0		(DpFRT_FS_LOC_TL_X0)
#define DpFRT_FS_DIR_TL_Y0		(DpFRT_FS_LOC_TL_Y0+50)
// Tank - Field Structure Direction - Value
#define DpFRT_FS_DIR_VL_X0		(DpFRT_FS_LOC_TL_X0+25)
#define DpFRT_FS_DIR_VL_Y0		(DpFRT_FS_DIR_TL_Y0+22)
// Tank - Field Structure Velocity - Title
#define DpFRT_FS_VEL_TL_X0		(DpFRT_FS_LOC_TL_X0)
#define DpFRT_FS_VEL_TL_Y0		(DpFRT_FS_DIR_TL_Y0+50)
// Tank - Field Structure Velocity - Value
#define DpFRT_FS_VEL_VL_X0		(DpFRT_FS_LOC_TL_X0+25)
#define DpFRT_FS_VEL_VL_Y0		(DpFRT_FS_VEL_TL_Y0+22)
// Tank - Field Structure Velocity - Unit
#define DpFRT_FS_VEL_UN_X0		(DpFRT_FS_VEL_VL_X0+40)
#define DpFRT_FS_VEL_UN_Y0		(DpFRT_FS_VEL_VL_Y0)
#endif
// Tank - Deadzone - Unit
#define DpFRT_DEADZ_UN_X0		(DpFRT_DEADZ_VL_X0+55)
#define DpFRT_DEADZ_UN_Y0		(DpFRT_DEADZ_VL_Y0)
// Tank - Tank Depth - Title
#define DpFRT_T_DEP_TL_X0		(DpFRT_TK_BDR_X0+5)
#define DpFRT_T_DEP_TL_Y0		(DpFRT_TK_BDR_Y0+DpFRT_TK_BDR_HT+7)
// Tank - Tank Depth - Value
#define DpFRT_T_DEP_VL_X0		(DpFRT_T_DEP_TL_X0+120)
#define DpFRT_T_DEP_VL_Y0		(DpFRT_T_DEP_TL_Y0)
// Tank - Tank Depth - Unit
#define DpFRT_T_DEP_UN_X0		(DpFRT_T_DEP_VL_X0+60)
#define DpFRT_T_DEP_UN_Y0		(DpFRT_T_DEP_TL_Y0)


// Function Indix - FieldA
enum {
	// Page 0
	ScFRT_FID_A_F00_DIRE=0,
	ScFRT_FID_A_F01_VELO,
	ScFRT_FID_A_F02_POSI,
	// Number Max (FieldA)
	ScFRT_FID_A_NUM,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Selection Box
typedef struct {
#if 0
	U16 aX0[ScFRT_FNC_NUMB+1];
	U16 aY0[ScFRT_FNC_NUMB+1];
	U16 aWd[ScFRT_FNC_NUMB+1];
	U16 aHt[ScFRT_FNC_NUMB+1];
#endif
} DpFRT_SBX;

typedef struct {
	DpFRT_SBX sbx;		// Selection Box
	RTC_TM time;		// Box - Time

	U16 level;
	U16 bx_lv;			// Box - level
	U08 unit;			// Box - Unit
	U16 curr;			// Box - Current
	U16 tprt;			// Tank - Temperature

} DpFRT_LS;


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
extern void DpFR2_ValUpdat(void);
extern void DpFR2_ValIntro(void);
// L1
extern void DpFR1_LstUpdat(void);
extern void DpFR1_LstIntro(void);
// L0
extern void DpFR0_FncStdBy(void);
extern void DpFR0_FncIntro(void);
// Basic
extern void DpFRT_InitVari(void);



#endif // ___DISP_SCREEN_FRONT_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

