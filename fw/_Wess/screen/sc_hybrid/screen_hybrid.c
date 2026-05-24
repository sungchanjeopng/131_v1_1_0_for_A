//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// bsp
#include "bsp_adc.h"
#include "bsp_ram.h"
// function
#include "input_main.h"
#include "input_key.h"
// display
#include "disp_string.h"
// disp - screen
#include "dp_screen_hybrid.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_hyb0_func.h"
#include "screen_hyb1_list.h"
#include "screen_hyb2_value.h"
// self
#include "screen_hybrid.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScHYB_LS lScHYB;


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters
//------------------------------------------------------------------------------------------------------------------------------
#if 0
U08 ScHYB_PrGet_LvTyp(void)			{	return lScHYB.mPr.level;			}
U08 ScHYB_PrGet_Unit_(void)			{	return lScHYB.mPr.unit_;			}
U08 ScHYB_PrGet_Chnnl(void)			{	return lScHYB.mPr.chnnl;			}
#endif
S32 ScHYB_PrGet_Value(U08 ch, U08 fnc)
{
#if 0
	switch(fnc)
	{
		case ScHYB_F00_LEVEL:		return lScHYB.mPr.level;
		case ScHYB_F01_UNIT_:		return lScHYB.mPr.unit_;
		case ScHYB_F02_S_DEP:		return lScHYB.mPr.sen_d[ch];
		case ScHYB_F03_DEADZ:		return lScHYB.mPr.deadz[ch];
		case ScHYB_F04_T_DEP:		return lScHYB.mPr.t_dep[ch];
		// Dual Sensor
		case ScHYB_FNC_NUMB:		return lScHYB.mPr.chnnl;
		default:					break;
	}

	return MENU_VAL_INVALID;
#endif
}

void ScHYB_PrSet_Value(U08 iFn, S32 val)
{
#if 0
	U08 iCh = lScHYB.mPr.chnnl;
	U32 ad_ss_dp[ScHYB_CH_NUMB] = {_mScHYB_S0_DEP_L, _mScHYB_S1_DEP_L};
	U32 ad_tk_dp[ScHYB_CH_NUMB] = {_mScHYB_T0_DEP_L, _mScHYB_T1_DEP_L};
	U32 ad_deadz[ScHYB_CH_NUMB] = {_mScHYB_DEADZ0_L, _mScHYB_DEADZ1_L};

	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		lScHYB.mPr.level = (U08)val;			break;
		case ScHYB_F01_UNIT_:		lScHYB.mPr.unit_ = (U08)val;			break;
		case ScHYB_F02_S_DEP:		lScHYB.mPr.sen_d[iCh] = (U16)val;		break;
		case ScHYB_F03_DEADZ:		lScHYB.mPr.deadz[iCh] = (U16)val;		break;
		case ScHYB_F04_T_DEP:		lScHYB.mPr.t_dep[iCh] = (U16)val;		break;
		// Dual Sensor
		case ScHYB_FNC_NUMB:		lScHYB.mPr.chnnl = (U08)val;			break;
	}

	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		MRM_WrByte(_mScHYB_LEVEL, lScHYB.mPr.level); 			break;
		case ScHYB_F01_UNIT_:		MRM_WrByte(_mScHYB_UNIT_, lScHYB.mPr.unit_); 			break;
		case ScHYB_F02_S_DEP:		MRM_WrWord(ad_ss_dp[iCh], lScHYB.mPr.sen_d[iCh]);		break;
		case ScHYB_F03_DEADZ:		MRM_WrWord(ad_deadz[iCh], lScHYB.mPr.deadz[iCh]);		break;
		case ScHYB_F04_T_DEP:		MRM_WrWord(ad_tk_dp[iCh], lScHYB.mPr.t_dep[iCh]);		break;
		// Dual Sensor
		case ScHYB_FNC_NUMB:		MRM_WrByte(_mScHYB_CHNNL, lScHYB.mPr.chnnl);			break;
	}
#endif
}

void ScHYB_PrRst_Factory(void)
{
#if 0
	MRM_WrByte(_mScHYB_CHNNL,    ScHYB_CH_0);
	MRM_WrByte(_mScHYB_LEVEL,    ScHYB_LVL_SLDG);
	MRM_WrByte(_mScHYB_UNIT_,    ScHYB_UNIT_METER);
	MRM_WrWord(_mScHYB_S0_DEP_L, ScHYB_SS_DEP_DEF);
	MRM_WrWord(_mScHYB_S1_DEP_L, ScHYB_SS_DEP_DEF);
	MRM_WrWord(_mScHYB_DEADZ0_L, ScHYB_DEADZ_DEF);
	MRM_WrWord(_mScHYB_DEADZ1_L, ScHYB_DEADZ_DEF);
	MRM_WrWord(_mScHYB_T0_DEP_L, ScHYB_TK_DEP_DEF);
	MRM_WrWord(_mScHYB_T1_DEP_L, ScHYB_TK_DEP_DEF);
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Set Variables
//------------------------------------------------------------------------------------------------------------------------------
void ScHYB_SetLayer(U08 lyr)		{	lScHYB.lyr = lyr;					}



//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScHYB_PrInitMain(void)
{
#if 0
	//	Read Parameters
	lScHYB.mPr.chnnl = MRM_RdByte(_mScHYB_CHNNL);
	lScHYB.mPr.level = MRM_RdByte(_mScHYB_LEVEL);
	lScHYB.mPr.unit_ = MRM_RdByte(_mScHYB_UNIT_);
	lScHYB.mPr.sen_d[ScHYB_CH_0] = MRM_RdWord(_mScHYB_S0_DEP_L);
	lScHYB.mPr.sen_d[ScHYB_CH_1] = MRM_RdWord(_mScHYB_S1_DEP_L);
	lScHYB.mPr.deadz[ScHYB_CH_0] = MRM_RdWord(_mScHYB_DEADZ0_L);
	lScHYB.mPr.deadz[ScHYB_CH_1] = MRM_RdWord(_mScHYB_DEADZ1_L);
	lScHYB.mPr.t_dep[ScHYB_CH_0] = MRM_RdWord(_mScHYB_T0_DEP_L);
	lScHYB.mPr.t_dep[ScHYB_CH_1] = MRM_RdWord(_mScHYB_T1_DEP_L);

	//	Check Parameters
	if(lScHYB.mPr.chnnl >= ScHYB_CH_NUMB)					lScHYB.mPr.chnnl = ScHYB_CH_0;
	if(lScHYB.mPr.level >= ScHYB_LVL_NUMB)					lScHYB.mPr.level = ScHYB_LVL_SLDG;
	if(lScHYB.mPr.unit_ >= ScHYB_UNIT_NUMB)					lScHYB.mPr.unit_ = ScHYB_UNIT_METER;
	if(lScHYB.mPr.sen_d[ScHYB_CH_0] < ScHYB_SS_DEP_MIN)		lScHYB.mPr.sen_d[ScHYB_CH_0] = ScHYB_SS_DEP_DEF;
	if(lScHYB.mPr.sen_d[ScHYB_CH_0] > ScHYB_SS_DEP_MAX)		lScHYB.mPr.sen_d[ScHYB_CH_0] = ScHYB_SS_DEP_DEF;
	if(lScHYB.mPr.sen_d[ScHYB_CH_1] < ScHYB_SS_DEP_MIN)		lScHYB.mPr.sen_d[ScHYB_CH_1] = ScHYB_SS_DEP_DEF;
	if(lScHYB.mPr.sen_d[ScHYB_CH_1] > ScHYB_SS_DEP_MAX)		lScHYB.mPr.sen_d[ScHYB_CH_1] = ScHYB_SS_DEP_DEF;
	if(lScHYB.mPr.deadz[ScHYB_CH_0] < ScHYB_DEADZ_MIN)		lScHYB.mPr.deadz[ScHYB_CH_0] = ScHYB_DEADZ_DEF;
	if(lScHYB.mPr.deadz[ScHYB_CH_0] > ScHYB_DEADZ_MAX)		lScHYB.mPr.deadz[ScHYB_CH_0] = ScHYB_DEADZ_DEF;
	if(lScHYB.mPr.deadz[ScHYB_CH_1] < ScHYB_DEADZ_MIN)		lScHYB.mPr.deadz[ScHYB_CH_1] = ScHYB_DEADZ_DEF;
	if(lScHYB.mPr.deadz[ScHYB_CH_1] > ScHYB_DEADZ_MAX)		lScHYB.mPr.deadz[ScHYB_CH_1] = ScHYB_DEADZ_DEF;
	if(lScHYB.mPr.t_dep[ScHYB_CH_0] < ScHYB_TK_DEP_MIN)		lScHYB.mPr.t_dep[ScHYB_CH_0] = ScHYB_TK_DEP_DEF;
	if(lScHYB.mPr.t_dep[ScHYB_CH_0] > ScHYB_TK_DEP_MAX)		lScHYB.mPr.t_dep[ScHYB_CH_0] = ScHYB_TK_DEP_DEF;
	if(lScHYB.mPr.t_dep[ScHYB_CH_1] < ScHYB_TK_DEP_MIN)		lScHYB.mPr.t_dep[ScHYB_CH_1] = ScHYB_TK_DEP_DEF;
	if(lScHYB.mPr.t_dep[ScHYB_CH_1] > ScHYB_TK_DEP_MAX)		lScHYB.mPr.t_dep[ScHYB_CH_1] = ScHYB_TK_DEP_DEF;

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE)
	{
		lScHYB.mPr.chnnl = ScHYB_CH_0;
		MRM_WrByte(_mScHYB_CHNNL, lScHYB.mPr.chnnl);
	}
#endif
}

void ScHYB_InitMain(void)
{
	lScHYB.lyr = SCRN_L0_FUNC;

	ScHY0_InitFunc();
	ScHY1_InitList();
	ScHY2_InitValu();

	ScHYB_PrInitMain();
}

void ScHYB_ProcMain(void)
{
	switch(lScHYB.lyr)
	{
		case SCRN_L0_FUNC:		ScHY0_ProcFunc();			break;
		case SCRN_L1_LIST:		ScHY1_ProcList();			break;
		case SCRN_L2_VALU:		ScHY2_ProcValu();			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

