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
#include "bsp_ram.h"
// app
#include "app_main.h"
// menu
#include "menu_main.h"
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// self
#include "menu_output.h"
// function
#include "output_relay.h"
#include "output_current.h"
#include "output_pcd.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnOUT_LS lMnOut;

static const U32 lMnOut_RlyAssignAddr[MnOUT_RLY_NUM] = {
	_mRELAY_ASSIGN,
	_mRELAY2_ASSIGN,
	_mRELAY3_ASSIGN,
	_mRELAY4_ASSIGN,
};

static const U32 lMnOut_RlyActAddr[MnOUT_RLY_NUM] = {
	_mRELAY_ACT_L,
	_mRELAY2_ACT_L,
	_mRELAY3_ACT_L,
	_mRELAY4_ACT_L,
};

static const U32 lMnOut_RlyStopAddr[MnOUT_RLY_NUM] = {
	_mRELAY_STOP_L,
	_mRELAY2_STOP_L,
	_mRELAY3_STOP_L,
	_mRELAY4_STOP_L,
};

static const U32 lMnOut_ExtEnableAddr[MnOS4_EXT_INPUT_NUM] = {
	_mEXT_IN1_ENABLE,
	_mEXT_IN2_ENABLE,
};

static const U32 lMnOut_ExtTargetAddr[MnOS4_EXT_INPUT_NUM] = {
	_mEXT_IN1_TARGET,
	_mEXT_IN2_TARGET,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//-----------------------------------------------------------------------------------------------------------------------------
S32 MnOUT_CurPrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:		val = lMnOut.mCurPr.assign[MnOUT_CH_0];			break;
		case MnOS0_OPT_CH1_SET_04mA:	val = lMnOut.mCurPr.set_4ma[MnOUT_CH_0];		break;
		case MnOS0_OPT_CH1_SET_20mA:    val = lMnOut.mCurPr.set_20ma[MnOUT_CH_0];		break;
		case MnOS0_OPT_CH1_TRM_12mA:	val = (S32)lMnOut.mCurPr.trm_12ma[MnOUT_CH_0];	break;
		case MnOS0_OPT_CH1_TRM_20mA:	val = (S32)lMnOut.mCurPr.trm_20ma[MnOUT_CH_0];	break;	
		case MnOS0_OPT_CH2_ASSIGN:		val = lMnOut.mCurPr.assign[MnOUT_CH_1];			break;
		case MnOS0_OPT_CH2_SET_04mA:	val = lMnOut.mCurPr.set_4ma[MnOUT_CH_1];		break;
		case MnOS0_OPT_CH2_SET_20mA:    val = lMnOut.mCurPr.set_20ma[MnOUT_CH_1];		break;
		case MnOS0_OPT_CH2_TRM_12mA:	val = (S32)lMnOut.mCurPr.trm_12ma[MnOUT_CH_1];	break;
		case MnOS0_OPT_CH2_TRM_20mA:	val = (S32)lMnOut.mCurPr.trm_20ma[MnOUT_CH_1];	break;
		default:																		break;
	}

	return val;
}

S32 MnOUT_CurPrGet_CH_Value(U08 ch,U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnOS0_OPT_SINGLE_ASSIGN:		val = lMnOut.mCurPr.assign[ch];			break;
		case MnOS0_OPT_SINGLE_SET_04mA:		val = lMnOut.mCurPr.set_4ma[ch];		break;
		case MnOS0_OPT_SINGLE_SET_20mA:     val = lMnOut.mCurPr.set_20ma[ch];		break;
		case MnOS0_OPT_SINGLE_TRM_12mA:	    val = (S32)lMnOut.mCurPr.trm_12ma[ch];	break;
		case MnOS0_OPT_SINGLE_TRM_20mA:		val = (S32)lMnOut.mCurPr.trm_20ma[ch];	break;	
		default:																	break;
	}

	return val;
}


S32 MnOUT_RlyPrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;
	U08 rly = MnOS1_OPT_RLY_IDX(iIt);

	if(iIt >= MnOS1_OPT_NUM)	return val;
	if(iIt == MnOS1_OPT_TEST)
	{
		OuRLY_SetTestfEn(TRUE);
		return 0;
	}
	if(rly >= MnOUT_RLY_NUM)	return val;

	switch(MnOS1_OPT_RLY_ITEM(iIt))
	{
		case MnOS1_RLY_ITEM_ASSIGN:	val = lMnOut.mRlyPr.assign[rly];	break;
		case MnOS1_RLY_ITEM_ACT:		val = lMnOut.mRlyPr.act[rly];		break;
		case MnOS1_RLY_ITEM_STOP:		val = lMnOut.mRlyPr.stop[rly];		break;
		default:						break;
	}

	return val;
}

S32 MnOUT_PcdPrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnOS2_OPT_MODE:		val = lMnOut.mPcdPr.mode;		break;
		case MnOS2_OPT_INTV:		val = lMnOut.mPcdPr.clr_intv;	break;
		case MnOS2_OPT_TERM:    	val = lMnOut.mPcdPr.clr_oper;	break;
		default:					break;
	}
	
	return val;
}

S32 MnOUT_ErrPrGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:	val = lMnOut.mErrPr.hold;		break;
		case MnOS3_OPT_ERR_OUTP:	val = lMnOut.mErrPr.outp;		break;
		default:					break;
	}

	return val;
}

S32 MnOUT_ExtPrGet_Value(U08 iIt)
{
	U08 ext;

	switch(iIt)
	{
		case MnOS4_OPT_EXT1:	ext = MnOS4_EXT_INPUT_1;	break;
		case MnOS4_OPT_EXT2:	ext = MnOS4_EXT_INPUT_2;	break;
		default:				return MENU_VAL_INVALID;
	}

	if(lMnOut.mExtPr.enable[ext] != MnOS4_ENABLE_ON)
		return MnOS4_VALUE_OFF;

	switch(lMnOut.mExtPr.target[ext])
	{
		case MnOS4_TARGET_CH1:	return MnOS4_VALUE_CH1;
		case MnOS4_TARGET_CH2:	return MnOS4_VALUE_CH2;
		default:				return MENU_VAL_INVALID;
	}
}

S32 MnOUT_PrGet_Value(U08 iSb, U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iSb)
	{
		case MnOUT_SUB_CURRENT:		val = MnOUT_CurPrGet_Value(iIt);		break;
		case MnOUT_SUB_RELAY:		val = MnOUT_RlyPrGet_Value(iIt);		break;
		case MnOUT_SUB_CLEAN:     	val = MnOUT_PcdPrGet_Value(iIt);		break;
		case MnOUT_SUB_ERROR:		val = MnOUT_ErrPrGet_Value(iIt);		break;
		case MnOUT_SUB_EXT_INPUT:	val = MnOUT_ExtPrGet_Value(iIt);		break;
		default:					break;
	}
	
	return val;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
void MnOUT_CurPrSet_Value(U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:		lMnOut.mCurPr.assign[MnOUT_CH_0] 	= val;		break;
		case MnOS0_OPT_CH1_SET_04mA:	lMnOut.mCurPr.set_4ma[MnOUT_CH_0] 	= val;		break;
		case MnOS0_OPT_CH1_SET_20mA:    lMnOut.mCurPr.set_20ma[MnOUT_CH_0]	= val;		break;
		case MnOS0_OPT_CH1_TRM_12mA:	lMnOut.mCurPr.trm_12ma[MnOUT_CH_0] 	= (S08)val;	break;
		case MnOS0_OPT_CH1_TRM_20mA:	lMnOut.mCurPr.trm_20ma[MnOUT_CH_0] 	= (S08)val;	break;
		case MnOS0_OPT_CH1_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_0,OuCUR_TYPE_MSR);	break;
		case MnOS0_OPT_CH2_ASSIGN:		lMnOut.mCurPr.assign[MnOUT_CH_1] 	= val;		break;
		case MnOS0_OPT_CH2_SET_04mA:	lMnOut.mCurPr.set_4ma[MnOUT_CH_1] 	= val;		break;
		case MnOS0_OPT_CH2_SET_20mA:    lMnOut.mCurPr.set_20ma[MnOUT_CH_1]	= val;		break;
		case MnOS0_OPT_CH2_TRM_12mA:	lMnOut.mCurPr.trm_12ma[MnOUT_CH_1] 	= (S08)val;	break;
		case MnOS0_OPT_CH2_TRM_20mA:	lMnOut.mCurPr.trm_20ma[MnOUT_CH_1] 	= (S08)val;	break;
		case MnOS0_OPT_CH2_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_1,OuCUR_TYPE_MSR);	break;
		default:					break;
	}

	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:		MRM_WrByte(_mCH1_CURRENT_ASSIGN,    lMnOut.mCurPr.assign[MnOUT_CH_0]);		break;
		case MnOS0_OPT_CH1_SET_04mA:	MRM_WrWord(_mCH1_SET_4MA_L,			lMnOut.mCurPr.set_4ma[MnOUT_CH_0]);		break;
		case MnOS0_OPT_CH1_SET_20mA:    MRM_WrWord(_mCH1_SET_20MA_L,	lMnOut.mCurPr.set_20ma[MnOUT_CH_0]);	break;
		case MnOS0_OPT_CH1_TRM_12mA:	MRM_WrByte(_mCH1_TRIM_12MA_L,    lMnOut.mCurPr.trm_12ma[MnOUT_CH_0]);	break;
		case MnOS0_OPT_CH1_TRM_20mA:	MRM_WrByte(_mCH1_TRIM_20MA_L,    lMnOut.mCurPr.trm_20ma[MnOUT_CH_0]);	break;
		case MnOS0_OPT_CH2_ASSIGN:		MRM_WrByte(_mCH2_CURRENT_ASSIGN,      lMnOut.mCurPr.assign[MnOUT_CH_1]);		break;
		case MnOS0_OPT_CH2_SET_04mA:	MRM_WrWord(_mCH2_SET_4MA_L,	lMnOut.mCurPr.set_4ma[MnOUT_CH_1]);		break;
		case MnOS0_OPT_CH2_SET_20mA:    MRM_WrWord(_mCH2_SET_20MA_L,	lMnOut.mCurPr.set_20ma[MnOUT_CH_1]);	break;
		case MnOS0_OPT_CH2_TRM_12mA:	MRM_WrByte(_mCH2_TRIM_12MA_L,    lMnOut.mCurPr.trm_12ma[MnOUT_CH_1]);	break;
		case MnOS0_OPT_CH2_TRM_20mA:	MRM_WrByte(_mCH2_TRIM_20MA_L,    lMnOut.mCurPr.trm_20ma[MnOUT_CH_1]);	break;
		default:					break;
	}
}

void MnOUT_CurPrSet_Ch_Value(U08 ch,U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnOS0_OPT_SINGLE_ASSIGN:		lMnOut.mCurPr.assign[ch] 	= val;		break;
		case MnOS0_OPT_SINGLE_SET_04mA:	lMnOut.mCurPr.set_4ma[ch] 	= val;		break;
		case MnOS0_OPT_SINGLE_SET_20mA:    lMnOut.mCurPr.set_20ma[ch]	= val;		break;
		case MnOS0_OPT_SINGLE_TRM_12mA:	lMnOut.mCurPr.trm_12ma[ch] 	= (S08)val;	break;
		case MnOS0_OPT_SINGLE_TRM_20mA:	lMnOut.mCurPr.trm_20ma[ch] 	= (S08)val;	break;
		case MnOS0_OPT_SINGLE_OUT_04mA:	OuCUR_SetOutp_Type(ch,OuCUR_TYPE_MSR);	break;
		default:					break;
	}


	if(ch==APP_CH_1)
	{
		switch(iIt)
		{
			case MnOS0_OPT_SINGLE_ASSIGN:	MRM_WrByte(_mCH1_CURRENT_ASSIGN,    lMnOut.mCurPr.assign[ch]);		break;
			case MnOS0_OPT_SINGLE_SET_04mA:	MRM_WrWord(_mCH1_SET_4MA_L,			lMnOut.mCurPr.set_4ma[ch]);		break;
			case MnOS0_OPT_SINGLE_SET_20mA: MRM_WrWord(_mCH1_SET_20MA_L,	lMnOut.mCurPr.set_20ma[ch]);	break;
			case MnOS0_OPT_SINGLE_TRM_12mA:	MRM_WrByte(_mCH1_TRIM_12MA_L,    lMnOut.mCurPr.trm_12ma[ch]);	break;
			case MnOS0_OPT_SINGLE_TRM_20mA:	MRM_WrByte(_mCH1_TRIM_20MA_L,    lMnOut.mCurPr.trm_20ma[ch]);	break;
			default:						break;
		}
	}
	else if(ch ==APP_CH_2)
	{
		switch(iIt)
		{
			case MnOS0_OPT_SINGLE_ASSIGN:	MRM_WrByte(_mCH2_CURRENT_ASSIGN,	lMnOut.mCurPr.assign[ch]);		break;
			case MnOS0_OPT_SINGLE_SET_04mA: MRM_WrWord(_mCH2_SET_4MA_L, 		lMnOut.mCurPr.set_4ma[ch]); 	break;
			case MnOS0_OPT_SINGLE_SET_20mA: MRM_WrWord(_mCH2_SET_20MA_L,	lMnOut.mCurPr.set_20ma[ch]);	break;
			case MnOS0_OPT_SINGLE_TRM_12mA: MRM_WrByte(_mCH2_TRIM_12MA_L,	 lMnOut.mCurPr.trm_12ma[ch]);	break;
			case MnOS0_OPT_SINGLE_TRM_20mA: MRM_WrByte(_mCH2_TRIM_20MA_L,	 lMnOut.mCurPr.trm_20ma[ch]);	break;
			default:						break;
		}
	}
}

void MnOUT_RlyPrSet_Value(U08 iIt, S32 val)
{
	U08 rly = MnOS1_OPT_RLY_IDX(iIt);

	if(iIt >= MnOS1_OPT_NUM)	return;
	if(rly >= MnOUT_RLY_NUM)	return;

	switch(MnOS1_OPT_RLY_ITEM(iIt))
	{
		case MnOS1_RLY_ITEM_ASSIGN:	lMnOut.mRlyPr.assign[rly] = (U08)val;	break;
		case MnOS1_RLY_ITEM_ACT:		lMnOut.mRlyPr.act[rly]    = (U16)val;	break;
		case MnOS1_RLY_ITEM_STOP:		lMnOut.mRlyPr.stop[rly]   = (U16)val;	break;
		default:						return;
	}

	switch(MnOS1_OPT_RLY_ITEM(iIt))
	{
		case MnOS1_RLY_ITEM_ASSIGN:	MRM_WrByte(lMnOut_RlyAssignAddr[rly], lMnOut.mRlyPr.assign[rly]);	break;
		case MnOS1_RLY_ITEM_ACT:		MRM_WrWord(lMnOut_RlyActAddr[rly],    lMnOut.mRlyPr.act[rly]);	break;
		case MnOS1_RLY_ITEM_STOP:		MRM_WrWord(lMnOut_RlyStopAddr[rly],   lMnOut.mRlyPr.stop[rly]);	break;
		default:						break;
	}
}

void MnOUT_PcdPrSet_Value(U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnOS2_OPT_MODE:	lMnOut.mPcdPr.mode 	= val;	break;
		case MnOS2_OPT_INTV:	lMnOut.mPcdPr.clr_intv 	= val;	break;
		case MnOS2_OPT_TERM:    lMnOut.mPcdPr.clr_oper 	= val;	break;
		default:					break;
	}

	switch(iIt)
	{
		case MnOS2_OPT_MODE:	MRM_WrByte(_mCLEAN_MODE,	lMnOut.mPcdPr.mode);	break;
		case MnOS2_OPT_INTV:	MRM_WrWord(_mCLEAN_INTV_L,	lMnOut.mPcdPr.clr_intv);	break;
		case MnOS2_OPT_TERM:    MRM_WrWord(_mCLEAN_TERM_L,  	lMnOut.mPcdPr.clr_oper);	break;
		default:					break;
	}
}

void MnOUT_ErrPrSet_Value(U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:	lMnOut.mErrPr.hold = val;	break;
		case MnOS3_OPT_ERR_OUTP:	lMnOut.mErrPr.outp = val;	break;
		default:					break;
	}

	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:	MRM_WrWord(_mERROR_DELAY_L,  lMnOut.mErrPr.hold);	break;
		case MnOS3_OPT_ERR_OUTP:	MRM_WrByte(_mERROR_OUTPUT,	lMnOut.mErrPr.outp);	break;
		default:					break;
	}
}

void MnOUT_ExtPrSet_Value(U08 iIt, S32 val)
{
	U08 ext;

	switch(iIt)
	{
		case MnOS4_OPT_EXT1:	ext = MnOS4_EXT_INPUT_1;	break;
		case MnOS4_OPT_EXT2:	ext = MnOS4_EXT_INPUT_2;	break;
		default:				return;
	}

	switch(val)
	{
		case MnOS4_VALUE_OFF:
			lMnOut.mExtPr.enable[ext] = MnOS4_ENABLE_OFF;
			break;
		case MnOS4_VALUE_CH1:
			lMnOut.mExtPr.enable[ext] = MnOS4_ENABLE_ON;
			lMnOut.mExtPr.target[ext] = MnOS4_TARGET_CH1;
			break;
		case MnOS4_VALUE_CH2:
			lMnOut.mExtPr.enable[ext] = MnOS4_ENABLE_ON;
			lMnOut.mExtPr.target[ext] = MnOS4_TARGET_CH2;
			break;
		default:
			return;
	}

	MRM_WrByte(lMnOut_ExtEnableAddr[ext], lMnOut.mExtPr.enable[ext]);
	MRM_WrByte(lMnOut_ExtTargetAddr[ext], lMnOut.mExtPr.target[ext]);
}

void MnOUT_PrRst_Factory(void)
{
	U08 rly;
	U08 ext;
	// Sub-Section #0 (Current)
	MRM_WrByte(_mCH1_CURRENT_ASSIGN,     MnOS0_ASSGIN_DEF);
	MRM_WrByte(_mCH2_CURRENT_ASSIGN,     MnOS0_ASSGIN_DEF);
	MRM_WrWord(_mCH1_SET_4MA_L, MnOS0_SET_4MA_DEF);
	MRM_WrWord(_mCH2_SET_4MA_L, MnOS0_SET_4MA_DEF);
	MRM_WrWord(_mCH1_SET_20MA_L, MnOS0_SET_20MA_DEF);
	MRM_WrWord(_mCH2_SET_20MA_L, MnOS0_SET_20MA_DEF);
	MRM_WrByte(_mCH1_TRIM_12MA_L,   MnOS0_TRIM_DEF);
	MRM_WrByte(_mCH2_TRIM_12MA_L,   MnOS0_TRIM_DEF);
	MRM_WrByte(_mCH1_TRIM_20MA_L,   MnOS0_TRIM_DEF);
	MRM_WrByte(_mCH2_TRIM_20MA_L,   MnOS0_TRIM_DEF);

	// Sub-Section #1 (Relay)
	for(rly=0; rly<MnOUT_RLY_NUM; rly++)
	{
		MRM_WrByte(lMnOut_RlyAssignAddr[rly], MnOS1_ASSIGN_DEF);
		MRM_WrWord(lMnOut_RlyActAddr[rly],    MnOS1_ACT_DEF);
		MRM_WrWord(lMnOut_RlyStopAddr[rly],   MnOS1_STOP_DEF);
	}
	// Sub-Section #2 (PCD)
	MRM_WrByte(_mCLEAN_MODE,     MnOS2_MODE_DEF);
	MRM_WrWord(_mCLEAN_INTV_L, 	 MnOS2_INTV_DEF);
	MRM_WrWord(_mCLEAN_TERM_L,   MnOS2_TERM_DEF);
	// Sub-Section #3 (Error)
	MRM_WrWord(_mERROR_DELAY_L,   MnOS3_ERR_DELAY_DEF);
	MRM_WrByte(_mERROR_OUTPUT,    MnOS3_ERR_OUTPUT_DEF);
	// Sub-Section #4 (External Input)
	for(ext=0; ext<MnOS4_EXT_INPUT_NUM; ext++)
	{
		MRM_WrByte(lMnOut_ExtEnableAddr[ext], MnOS4_ENABLE_DEF);
		MRM_WrByte(lMnOut_ExtTargetAddr[ext], MnOS4_TARGET_DEF);
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnOUT_GetLayer(void)			{	return lMnOut.lyr;		}
// Set
void MnOUT_SetLayer(U08 lyr)		{	lMnOut.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void MnOUT_PrInitMain(void)
{
	U08 rly;
	U08 ext;

	// Read Parameters
	// Sub-Section #0 (Current)
	lMnOut.mCurPr.assign[APP_CH_1] 	= MRM_RdByte(_mCH1_CURRENT_ASSIGN);
	lMnOut.mCurPr.assign[APP_CH_2] 	= MRM_RdByte(_mCH2_CURRENT_ASSIGN);
	lMnOut.mCurPr.set_4ma[APP_CH_1] 	= MRM_RdWord(_mCH1_SET_4MA_L);
	lMnOut.mCurPr.set_20ma[APP_CH_1] 	= MRM_RdWord(_mCH1_SET_20MA_L);
	lMnOut.mCurPr.set_4ma[APP_CH_2] 	= MRM_RdWord(_mCH2_SET_4MA_L);
	lMnOut.mCurPr.set_20ma[APP_CH_2] 	= MRM_RdWord(_mCH2_SET_20MA_L);
	lMnOut.mCurPr.trm_12ma[APP_CH_1] 	= (S08)MRM_RdByte(_mCH1_TRIM_12MA_L);
	lMnOut.mCurPr.trm_20ma[APP_CH_1] 	= (S08)MRM_RdByte(_mCH1_TRIM_20MA_L);
	lMnOut.mCurPr.trm_12ma[APP_CH_2] 	= (S08)MRM_RdByte(_mCH2_TRIM_12MA_L);
	lMnOut.mCurPr.trm_20ma[APP_CH_2] 	= (S08)MRM_RdByte(_mCH2_TRIM_20MA_L);
	// Sub-Section #1 (Relay)
	for(rly=0; rly<MnOUT_RLY_NUM; rly++)
	{
		lMnOut.mRlyPr.assign[rly] = MRM_RdByte(lMnOut_RlyAssignAddr[rly]);
		lMnOut.mRlyPr.act[rly]    = MRM_RdWord(lMnOut_RlyActAddr[rly]);
		lMnOut.mRlyPr.stop[rly]   = MRM_RdWord(lMnOut_RlyStopAddr[rly]);
	}
	// Sub-Section #2 (PCD)
	lMnOut.mPcdPr.mode 		= MRM_RdByte(_mCLEAN_MODE);
	lMnOut.mPcdPr.clr_intv 	= MRM_RdWord(_mCLEAN_INTV_L);
	lMnOut.mPcdPr.clr_oper 	= MRM_RdWord(_mCLEAN_TERM_L);
	// Sub-Section #3 (Error)
	lMnOut.mErrPr.hold 		= MRM_RdWord(_mERROR_DELAY_L);
	lMnOut.mErrPr.outp 		= MRM_RdByte(_mERROR_OUTPUT);
	// Sub-Section #4 (External Input)
	for(ext=0; ext<MnOS4_EXT_INPUT_NUM; ext++)
	{
		lMnOut.mExtPr.enable[ext] = MRM_RdByte(lMnOut_ExtEnableAddr[ext]);
		lMnOut.mExtPr.target[ext] = MRM_RdByte(lMnOut_ExtTargetAddr[ext]);
	}

	// Check Parameters
	// Sub-Section #0 (Current)
	if(lMnOut.mCurPr.assign[APP_CH_1]  > MnOS0_ASSIGN_MAX)			lMnOut.mCurPr.assign[APP_CH_1] 	= MnOS0_ASSGIN_DEF;
	if(lMnOut.mCurPr.assign[APP_CH_2]  > MnOS0_ASSIGN_MAX)			lMnOut.mCurPr.assign[APP_CH_2] 	= MnOS0_ASSGIN_DEF;
	if(lMnOut.mCurPr.set_4ma[APP_CH_1]  > MnOS0_SET_MA_MAX)			lMnOut.mCurPr.set_4ma[APP_CH_1] 	= MnOS0_SET_4MA_DEF;
	if(lMnOut.mCurPr.set_4ma[APP_CH_2]  > MnOS0_SET_MA_MAX)			lMnOut.mCurPr.set_4ma[APP_CH_2] 	= MnOS0_SET_4MA_DEF;
	if(lMnOut.mCurPr.set_20ma[APP_CH_1] > MnOS0_SET_MA_MAX)			lMnOut.mCurPr.set_20ma[APP_CH_1] 	= MnOS0_SET_20MA_DEF;
	if(lMnOut.mCurPr.set_20ma[APP_CH_2] > MnOS0_SET_MA_MAX)			lMnOut.mCurPr.set_20ma[APP_CH_2] 	= MnOS0_SET_20MA_DEF;
	if(lMnOut.mCurPr.trm_12ma[APP_CH_1]  < MnOS0_TRIM_MIN)			lMnOut.mCurPr.trm_12ma[APP_CH_1] 	= MnOS0_TRIM_DEF;
	if(lMnOut.mCurPr.trm_12ma[APP_CH_2]  > MnOS0_TRIM_MAX)			lMnOut.mCurPr.trm_12ma[APP_CH_2] 	= MnOS0_TRIM_DEF;
	if(lMnOut.mCurPr.trm_20ma[APP_CH_1] < MnOS0_TRIM_MIN)			lMnOut.mCurPr.trm_20ma[APP_CH_1] 	= MnOS0_TRIM_DEF;
	if(lMnOut.mCurPr.trm_20ma[APP_CH_2] > MnOS0_TRIM_MAX)			lMnOut.mCurPr.trm_20ma[APP_CH_2] 	= MnOS0_TRIM_DEF;

	// Sub-Section #1 (Relay)
	for(rly=0; rly<MnOUT_RLY_NUM; rly++)
	{
		if(lMnOut.mRlyPr.assign[rly] > MnOS1_ASSIGN_MAX)	lMnOut.mRlyPr.assign[rly] = MnOS1_ASSIGN_DEF;
		if(lMnOut.mRlyPr.act[rly]    > MnOS1_ACT_MAX)	lMnOut.mRlyPr.act[rly]    = MnOS1_ACT_DEF;
		if(lMnOut.mRlyPr.stop[rly]   > MnOS1_STOP_MAX)	lMnOut.mRlyPr.stop[rly]   = MnOS1_STOP_DEF;
	}
	// Sub-Section #2 (PCD)
	if(lMnOut.mPcdPr.mode > MnOS2_MODE_MAX)					lMnOut.mPcdPr.mode 	= MnOS2_MODE_DEF;	
	if(lMnOut.mPcdPr.clr_intv > MnOS2_INTV_MAX)				lMnOut.mPcdPr.clr_intv 	= MnOS2_INTV_DEF;
	if(lMnOut.mPcdPr.clr_oper > MnOS2_TERM_MAX)				lMnOut.mPcdPr.clr_oper 	= MnOS2_TERM_DEF;
	// Sub-Section #3 (Error)
	if(lMnOut.mErrPr.hold 	  > MnOS3_ERR_DELAY_MAX)		lMnOut.mErrPr.hold 		= MnOS3_ERR_DELAY_DEF;
	if(lMnOut.mErrPr.outp 	  > MnOS3_ERR_OUTPUT_MAX)		lMnOut.mErrPr.outp 		= MnOS3_ERR_OUTPUT_DEF;
	// Sub-Section #4 (External Input)
	for(ext=0; ext<MnOS4_EXT_INPUT_NUM; ext++)
	{
		if(lMnOut.mExtPr.enable[ext] > MnOS4_ENABLE_MAX)	lMnOut.mExtPr.enable[ext] = MnOS4_ENABLE_DEF;
		if(lMnOut.mExtPr.target[ext] > MnOS4_TARGET_MAX)	lMnOut.mExtPr.target[ext] = MnOS4_TARGET_DEF;
	}

}

void MnOUT_InitMain(void)
{
	lMnOut.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnOUT_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

