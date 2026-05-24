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

	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:		val = lMnOut.mRlyPr.assign;					break;
		case MnOS1_OPT_ACT:			val = lMnOut.mRlyPr.act;					break;
		case MnOS1_OPT_STOP:     	val = lMnOut.mRlyPr.stop;					break;
		case MnOS1_OPT_TEST:		OuRLY_SetTestfEn(TRUE);			val=0;		break;
		default:					break;
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

S32 MnOUT_PrGet_Value(U08 iSb, U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iSb)
	{
		case MnOUT_SUB_CURRENT:		val = MnOUT_CurPrGet_Value(iIt);		break;
		case MnOUT_SUB_RELAY:		val = MnOUT_RlyPrGet_Value(iIt);		break;
		case MnOUT_SUB_CLEAN:     	val = MnOUT_PcdPrGet_Value(iIt);		break;
		case MnOUT_SUB_ERROR:		val = MnOUT_ErrPrGet_Value(iIt);		break;
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
	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:		lMnOut.mRlyPr.assign = val;							break;
		case MnOS1_OPT_ACT:			lMnOut.mRlyPr.act  	 = val;							break;
		case MnOS1_OPT_STOP:   		lMnOut.mRlyPr.stop 	 = val;							break;
		case MnOS1_OPT_TEST:		break;
		default:					return;
	}

	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:	MRM_WrByte(_mRELAY_ASSIGN,  lMnOut.mRlyPr.assign);	break;
		case MnOS1_OPT_ACT:		MRM_WrWord(_mRELAY_ACT_L,	lMnOut.mRlyPr.act);		break;
		case MnOS1_OPT_STOP:    MRM_WrWord(_mRELAY_STOP_L,  lMnOut.mRlyPr.stop);	break;
		default:				break;
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

void MnOUT_PrRst_Factory(void)
{
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
	MRM_WrByte(_mRELAY_ASSIGN,     MnOS1_ASSIGN_DEF);
	MRM_WrWord(_mRELAY_ACT_L,      MnOS1_ACT_DEF);
	MRM_WrWord(_mRELAY_STOP_L,     MnOS1_STOP_DEF);
	// Sub-Section #2 (PCD)
	MRM_WrByte(_mCLEAN_MODE,     MnOS2_MODE_DEF);
	MRM_WrWord(_mCLEAN_INTV_L, 	 MnOS2_INTV_DEF);
	MRM_WrWord(_mCLEAN_TERM_L,   MnOS2_TERM_DEF);
	// Sub-Section #3 (Error)
	MRM_WrWord(_mERROR_DELAY_L,   MnOS3_ERR_DELAY_DEF);
	MRM_WrByte(_mERROR_OUTPUT,    MnOS3_ERR_OUTPUT_DEF);
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
	lMnOut.mRlyPr.assign 	= MRM_RdByte(_mRELAY_ASSIGN);
	lMnOut.mRlyPr.act 	 	= MRM_RdWord(_mRELAY_ACT_L);
	lMnOut.mRlyPr.stop 	 	= MRM_RdWord(_mRELAY_STOP_L);
	lMnOut.mRlyPr.test 	 	= MnOS1_TEST_DEF;						
	// Sub-Section #2 (PCD)
	lMnOut.mPcdPr.mode 		= MRM_RdByte(_mCLEAN_MODE);
	lMnOut.mPcdPr.clr_intv 	= MRM_RdWord(_mCLEAN_INTV_L);
	lMnOut.mPcdPr.clr_oper 	= MRM_RdWord(_mCLEAN_TERM_L);
	// Sub-Section #3 (Error)
	lMnOut.mErrPr.hold 		= MRM_RdWord(_mERROR_DELAY_L);
	lMnOut.mErrPr.outp 		= MRM_RdByte(_mERROR_OUTPUT);

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
	if(lMnOut.mRlyPr.assign   > MnOS1_ASSIGN_MAX)			lMnOut.mRlyPr.assign 	= MnOS1_ASSIGN_DEF;
	if(lMnOut.mRlyPr.act 	  > MnOS1_ACT_MAX)				lMnOut.mRlyPr.act 		= MnOS1_ACT_DEF;
	if(lMnOut.mRlyPr.stop 	  > MnOS1_STOP_MAX)				lMnOut.mRlyPr.stop 		= MnOS1_STOP_DEF;
	if(lMnOut.mRlyPr.test 	  > MnOS1_TEST_MAX)				lMnOut.mRlyPr.stop 		= MnOS1_TEST_DEF;
	// Sub-Section #2 (PCD)
	if(lMnOut.mPcdPr.mode > MnOS2_MODE_MAX)					lMnOut.mPcdPr.mode 	= MnOS2_MODE_DEF;	
	if(lMnOut.mPcdPr.clr_intv > MnOS2_INTV_MAX)				lMnOut.mPcdPr.clr_intv 	= MnOS2_INTV_DEF;
	if(lMnOut.mPcdPr.clr_oper > MnOS2_TERM_MAX)				lMnOut.mPcdPr.clr_oper 	= MnOS2_TERM_DEF;
	// Sub-Section #3 (Error)
	if(lMnOut.mErrPr.hold 	  > MnOS3_ERR_DELAY_MAX)		lMnOut.mErrPr.hold 		= MnOS3_ERR_DELAY_DEF;
	if(lMnOut.mErrPr.outp 	  > MnOS3_ERR_OUTPUT_MAX)		lMnOut.mErrPr.outp 		= MnOS3_ERR_OUTPUT_DEF;

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

