//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___DISP_COLOR_H___
#define ___DISP_COLOR_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Color - Standard			//   T -   R   G   B
//------------------------------------------------------------------------------------------------------------------------------
// Black & White
#define _cSD_BLACK			((U32)0xff000000)		// 255 -   0   0   0

#define _cSD_WHITE			((U32)0xffFFFFFF)		// 255 - 255 255 255
// Gray
#define _cSD_LIGHTGRAY		((U32)0xff939393)
#define _cSD_GRAY			((U32)0xff808080)
#define _cSD_DARKGRAY		((U32)0xff404040)
#define _cSD_LIGHTBLACK		((U32)0xff202020)
// RGB - 1 Color (0xFF)
#define _cSD_RED			((U32)0xffFF0000)
#define _cSD_GREEN			((U32)0xff00FF00)
#define _cSD_BLUE			((U32)0xff0000FF)
// RGB - 1 Color (0x80)
#define _cSD_DARKRED		((U32)0xff800000)
#define _cSD_DARKGREEN		((U32)0xff008000)
#define _cSD_DARKBLUE		((U32)0xff000080)
// RGB - Mixed 2 Color (0xFF)
#define _sSD_BLACKBLUE		((U32)0xff333656)
#define _cSD_YELLOW			((U32)0xffFFFF00)
#define _cSD_MAGENTA		((U32)0xffFF00FF)
#define _cSD_CYAN			((U32)0xff00FFFF)
// RGB - Mixed 2 Color (0x80)
#define _cSD_DARKYELLOW		((U32)0xff808000)
#define _cSD_DARKMAGENTA	((U32)0xff800080)
#define _cSD_DARKCYAN		((U32)0xff008080)
// RGB - Mixed 3 Color (0xFF(1) & 0x80(2))
#define _cSD_LIGHTRED		((U32)0xffFF8080)
#define _cSD_LIGHTGREEN		((U32)0xff80FF80)
#define _cSD_LIGHTBLUE		((U32)0xff8080FF)
// RGB - Mixed 3 Color (0xFF(2) & 0x80(1))
#define _cSD_LIGHTYELLOW	((U32)0xffFFFF80)
#define _cSD_LIGHTMAGENTA	((U32)0xffFF80FF)
#define _cSD_LIGHTCYAN		((U32)0xff80FFFF)
// RGB - Mixed 3 Color (0xFF & Other)
#define _cSD_OCHER			((U32)0xff897A57)
#define _cSD_ORANGE			((U32)0xffFFA500)
#define _cSD_BROWN			((U32)0xffA52A2A)
// Transparent
#define _cSD_TRANSPARENT	(_cSD_BLACK)


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Color - User Config.		//   T -   R   G   B
//------------------------------------------------------------------------------------------------------------------------------
// Background
#define _cBGD_SCRN			((U32)0xff161816)		// 255 -  22  24  22
// Title Bar
#define _cTTB_BG_MID		((U32)0xff2A2A2A)		// 255 -  42  42  42
//#define _cTTB_FG_ICON		((U32)0xffC1C1C1)		// 255 - 193 193 193
#define _cTTB_FG_ICON		(_cSD_DARKGRAY)
#define _cTTB_FG_PRDT		((U32)0xff5C60F7)		// 255 -  92  96 247
#define _cTTB_ST_TITLE		((U32)0xffC1C1C1)		// 255 - 193 193 193
#define _cTTB_ST_PRDT		(_cTTB_FG_PRDT)
#define _cTTB_ST_CALIB		((U32)0xffE1A1E1)		// Custom
// Button
#define _cBTN_BG_HIDE		(_cBGD_SCRN)
#define _cBTN_BG_DISA		(_cSD_LIGHTBLACK)
#define _cBTN_BG_PEND		((U32)0xff47D747)		// 255 -  71  71  71
#define _cBTN_FG_SELE		((U32)0xff40D040)		// 255 -  64 208  64
#define _cBTN_FG_PEND		((U32)0xffC4C8C9)		// 255 - 196 200 201
#define _cBTN_ST_IDLE		(_cBTN_FG_PEND)
#define _cBTN_ST_ACTV		(_cBTN_FG_SELE)
#define _cBTN_ST_DISA		(_cSD_DARKGRAY)
#define _cBTN_BX_SELE		((U32)0xff01B075)		// 255 -   1 176 117
// Status Zone
#define _cSTT_ST_MAIN		((U32)0xff00FFA9)		// 255 -   0 255 169
#define _cSTT_ST_SUB0		((U32)0xff00FF30)		// 255 -   0 255  48


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Color - Screen			//   T -   R   G   B
//------------------------------------------------------------------------------------------------------------------------------
#define _cLight_level		((U32)0xffFFEDCD) 
#define _cHeavy_level		(_cSD_ORANGE) 
#define _cTprt				((U32)0xff6DADFC)
#define _cCH				((U32)0xff606060)
// Screen / Hybrid
#define _chyb_LN_H00		((U32)0xff0F100F)       // 255 -  15  16  15
#define _chyb_LN_H01		((U32)0xff141514)       // 255 -  20  21  20
#define _chyb_LN_H02		((U32)0xff202220)       // 255 -  32  34  32
#define _chyb_LVL_ICON		((U32)0xffFF9C00)		// 255 - 255 156   0
#define _chyb_LVL_T_IDLE	((U32)0xffDE8803)		// 255 - 222 136   3
#define _chyb_LVL_T_SELE	(_cBTN_BX_SELE)
#define _chyb_LVL_VAL		(_chyb_LVL_ICON)
#define _chyb_FG_SENS		((U32)0xff9D9D9D)		// 255 - 157 157 157
#define _chyb_WAT_65_100	((U32)0xff0070C0)
#define _chyb_WAT_58_65		((U32)0xff0077C6)
#define _chyb_WAT_37_58		((U32)0xff328CD8)
#define _chyb_WAT_26_37		((U32)0xff4697E6)
#define _chyb_WAT_17_26		((U32)0xff56ADEF)
#define _chyb_WAT_08_17		((U32)0xff65A9F8)
#define _chyb_WAT_00_08		((U32)0xff73B0FF)

#define _chyb_WAT_END		((U32)0xff73B0FF)       // 255 - 115 176 255
#if 1
#define _chyb_SLG_BSS		((U32)0xff5C4D19)       // 255 -  59  48   8
#define _chyb_SLG_TRANS		((U32)0x80bca378)       // 128 -  59  48   8
#else 
#define _chyb_SLG_BSS		((U32)0xffAA9D85)       // 255 -  59  48   8
#define _chyb_SLG_TRANS		((U32)0x00AA9D85)       // 128 -  59  48   8

#endif
#define _chyb_BOX_STR		((U32)0xff7FFFD4)		// 255 - 127 255 212
#define _chyb_BOX_ICN_BG	((U32)0xff526662)		// 255 -  82 102  98
#define _chyb_BOX_ICN_FG	((U32)0xff72D1B2)		// 255 - 124 209 178
#define _chyb_TANK_VAL		((U32)0xffC8C0C0)
// Screen / Echo
#define _cECO_LVL_TITL		((U32)0xffD08204)		// 255 - 208 130   4
#define _cECO_LVL_VALU		(_chyb_LVL_VAL)
#define _cECO_GRP_BDR		((U32)0xff6E6E6E)		// 255 - 110 110 110
#define _cECO_AMP_STD		((U32)0xffB2B2B2)		// 255 - 178 178 178
#define _cECO_BOX_TITL		(_cSD_LIGHTGRAY)
#define _cECO_BOX_VALU		(_cSD_WHITE)
#define _cECO_LN_V_SLDG		((U32)0xCC02F1AB)		// 255 -   2 241 171
#define _cECO_LN_V_DDZN		((U32)0xff1B4050)		// Custom
#define _cECO_LN_V_DZ_L		((U32)0xff208070)		// Custom
#define _cECO_LN_H_CNTR		((U32)0xff696969)		// 255 - 105 105 105
#define _cECO_LN_H_TRHD		((U32)0xff7E87FF)		// 255 - 126 135 255
#define _cECO_LN_H_ASF_		(_cECO_LVL_VALU)
#define _cECO_LN_H_D_WD		(_cMNU_SEL_SCT)
// Screen / Calib
#define _cCLB_LVL_TITL		(_cECO_LVL_TITL)
#define _cCLB_LVL_VALU		(_cECO_LVL_VALU)
#define _cCLB_GRP_BDR		(_cECO_GRP_BDR)
#define _cCLB_STR_GAIN		(_cTTB_ST_CALIB)
#define _cCLB_BOX_VALU		(_cSD_WHITE)
#define _cCLB_LN_H_CNTR		(_cECO_LN_H_CNTR)
#define _cCLB_GAIN_CIRC		(_cSD_LIGHTMAGENTA)
#define _cCLB_GAIN_LINE		(_cSD_MAGENTA)
// Screen / Information
#define _cINF_BOX_BG		(_cTTB_BG_MID)
#define _cINF_LIN_V			((U32)0xff101018)		// Custom
#define _cINF_LIN_H			((U32)0xff40404F)		// Custom
#define _cINF_ST_TITLE		(_chyb_TANK_VAL)
#define _cINF_ST_VALUE		((U32)0xffC8C0C0)		// Custom
#define _cINF_ITEM_BG		((U32)0xff20D020)		// Custom
// Screen / Trend
#define _cTrend_line		((U32)0xff606060)


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Color - Menu				//   T -   R   G   B
//------------------------------------------------------------------------------------------------------------------------------
#define _cMNU_BOX_BG		(_cTTB_BG_MID)
#define _cMNU_SEL_SCT		((U32)0xff23A176)		// 255 -  67 193 150
#define _cMNU_SEL_SUB		((U32)0xff33B186)		// 255 -  67 193 150
#define _cMNU_SEL_ITM		((U32)0xff43C196)		// Custom
#define _cMNU_STR_SEL		(_cSD_DARKGRAY)
#define _cMNU_STR_IDLE		(_cTTB_ST_TITLE)
#define _cMNU_STR_TBD		(_cSD_DARKGRAY)


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Color - Pop-up				//   T -   R   G   B
//------------------------------------------------------------------------------------------------------------------------------
#define _cPOP_BG_UPP		((U32)0xff9C9994)		// 255 - 156 153 148
#define _cPOP_BG_WND		((U32)0xff494949)		// 255 -  73  73  73
#define _cPOP_BG_LN_0		((U32)0xff353536)		// 255 -  53  53  54
#define _cPOP_BG_LN_1		((U32)0xff565656)		// 255 -  86  86  86
#define _cPOP_ST_TIT		(_cSD_WHITE)			// 255 -  86  86  86
#define _cPOP_ST_OLD		(_cSD_YELLOW)			// 255 -  86  86  86
#define _cPOP_ST_VAL_SEL	(_cSD_WHITE)			// 255 -  86  86  86
#define _cPOP_ST_VAL_IDL	((U32)0xffBBBBBB)		// 255 - 187 187 187
#define _cPOP_ST_EXP		(_cSD_DARKYELLOW)		// 255 - 187 187 187
#define _cPOP_ST_MAX		((U32)0xffFF6D6D)		// 255 - 255 109 109
#define _cPOP_ST_MIN		((U32)0xff2CA8FF)		// 255 -  44 168 255


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions - Gradation	//   T -   R   G   B
//------------------------------------------------------------------------------------------------------------------------------
// Title Bar (15 x 4 = 60)
enum {
	_cTTB_BG_G00 = ((U32)0xff313131),	// 255 -  49  49  49
	_cTTB_BG_G01 = ((U32)0xff303030),
	_cTTB_BG_G02 = ((U32)0xff2F2F2F),
	_cTTB_BG_G03 = ((U32)0xff2E2E2E),
	_cTTB_BG_G04 = ((U32)0xff2D2D2E),
	_cTTB_BG_G05 = ((U32)0xff2C2C2C),
	_cTTB_BG_G06 = ((U32)0xff2B2B2B),
	_cTTB_BG_G07 = ((U32)0xff2A2A2A),	// 255 -  42  42  42
	_cTTB_BG_G08 = ((U32)0xff292929),
	_cTTB_BG_G09 = ((U32)0xff282828),
	_cTTB_BG_G10 = ((U32)0xff272727),
	_cTTB_BG_G11 = ((U32)0xff262626),
	_cTTB_BG_G12 = ((U32)0xff252525),
	_cTTB_BG_G13 = ((U32)0xff242424),
	_cTTB_BG_G14 = ((U32)0xff232323),	// 255 -  35  35  35
};

// Button (14 x 4 = 56)
enum {
	_cBTN_BG_G00 = ((U32)0xff47D747),
	_cBTN_BG_G01 = ((U32)0xff464646),
	_cBTN_BG_G02 = ((U32)0xff444444),
	_cBTN_BG_G03 = ((U32)0xff424242),
	_cBTN_BG_G04 = ((U32)0xff404040),
	_cBTN_BG_G05 = ((U32)0xff3E3E3E),
	_cBTN_BG_G06 = ((U32)0xff3C3C3C),
	_cBTN_BG_G07 = ((U32)0xff3A3A3A),
	_cBTN_BG_G08 = ((U32)0xff383838),
	_cBTN_BG_G09 = ((U32)0xff363636),
	_cBTN_BG_G10 = ((U32)0xff343434),
	_cBTN_BG_G11 = ((U32)0xff323232),
	_cBTN_BG_G12 = ((U32)0xff303030),
	_cBTN_BG_G13 = ((U32)0xff2E2E2E),
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
//  Extern global APIs
//------------------------------------------------------------------------------------------------------------------------------
// Get Local Variables
// Set Local Variables
// Operation


#endif // ___DISP_COLOR_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

