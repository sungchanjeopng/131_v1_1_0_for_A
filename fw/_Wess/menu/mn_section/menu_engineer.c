//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-01-20 12:00:00 +0900 $ (From 2020-07-13)
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// bsp
#include "bsp_ram.h"
#include "bsp_demux.h"
// app
#include "app_main.h"
// menu
#include "menu_main.h"
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// measure
#include "measure_calc.h"
// self
#include "menu_engineer.h"

#include "data_save.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnEGN_LS lMnEgn;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
S32 MnEGN_PrGet_Item(U08 itm)
{
	S32 val = MENU_VAL_INVALID;
	
	switch(itm)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:			val = lMnEgn.mPr.thr_sync;					break;
		case MnEGN_OPT_CH1_PROFILE:				val = lMnEgn.mPr.prof[APP_CH_1];			break;
		case MnEGN_OPT_CH1_TVG:					val = lMnEgn.mPr.tvg[APP_CH_1];				break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:	val = lMnEgn.mPr.window_time[APP_CH_1];		break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:		val = lMnEgn.mPr.window_range[APP_CH_1];	break;
		case MnEGN_OPT_CH2_PROFILE:				val = lMnEgn.mPr.prof[APP_CH_2];			break;
		case MnEGN_OPT_CH2_TVG:					val = lMnEgn.mPr.tvg[APP_CH_2];				break;
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:	val = lMnEgn.mPr.window_time[APP_CH_2];		break;
		case MnEGN_OPT_CH2_WINDOW_RANGE:		val = lMnEgn.mPr.window_range[APP_CH_2];	break;
		case MnEGN_OPT_MSR:						val = lMnEgn.mPr.msr;						break;
		default:																			break;
	}

	return val;
}

S32 MnEGN_PrGet_CH_Item(U08 ch,U08 itm)
{
	S32 val = MENU_VAL_INVALID;

	switch(itm)
	{
		case MnEGN_OPT_SINGLE_THRESHOLD_SYNC:		val = lMnEgn.mPr.thr_sync;			break;
		case MnEGN_OPT_SINGLE_PROFILE:				val = lMnEgn.mPr.prof[ch];			break;	
		case MnEGN_OPT_SINGLE_TVG:					val = lMnEgn.mPr.tvg[ch];			break;
		case MnEGN_OPT_SINGLE_WINDOW_RESET_TIME:	val = lMnEgn.mPr.window_time[ch];	break;
		case MnEGN_OPT_SINGLE_WINDOW_RANGE:			val = lMnEgn.mPr.window_range[ch];	break;
		case MnEGN_OPT_MSR:							val = lMnEgn.mPr.msr;				break;
		default:
			break;
	}

	return val;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
void MnEGN_PrSet_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:			lMnEgn.mPr.thr_sync = val;				break;
		case MnEGN_OPT_CH1_PROFILE:				lMnEgn.mPr.prof[APP_CH_1]= val;			CalPrc_ResetFlag(APP_CH_1);	break;
		case MnEGN_OPT_CH1_TVG:					lMnEgn.mPr.tvg[APP_CH_1]= val;			break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:	lMnEgn.mPr.window_time[APP_CH_1]= val;	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:		lMnEgn.mPr.window_range[APP_CH_1]= val;	 	break;
		case MnEGN_OPT_CH2_PROFILE:				lMnEgn.mPr.prof[APP_CH_2]= val;			CalPrc_ResetFlag(APP_CH_2);	break;
		case MnEGN_OPT_CH2_TVG:					lMnEgn.mPr.tvg[APP_CH_2]= val;			 break;
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:	lMnEgn.mPr.window_time[APP_CH_2]= val;	 break;
		case MnEGN_OPT_CH2_WINDOW_RANGE:		lMnEgn.mPr.window_range[APP_CH_2]= val;	 break;
		case MnEGN_OPT_MSR:					
			if(lMnEgn.mPr.msr!=val)		
				DaSAV_DeleteData();			
			lMnEgn.mPr.msr= val;
			break;
		default:																		break;
	}

	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:			MRM_WrByte(_mTHR_SYNC, lMnEgn.mPr.thr_sync);						break;
		case MnEGN_OPT_CH1_PROFILE:				MRM_WrByte(_mCH1_PROF, lMnEgn.mPr.prof[APP_CH_1]);					break;
		case MnEGN_OPT_CH1_TVG:					MRM_WrByte(_mCH1_TVG, lMnEgn.mPr.tvg[APP_CH_1]);					break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:	MRM_WrWord(_mCH1_WINDOW_TIME_L, lMnEgn.mPr.window_time[APP_CH_1]);	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:		MRM_WrWord(_mCH1_WINDOW_RANGE_L, lMnEgn.mPr.window_range[APP_CH_1]);break;
		case MnEGN_OPT_CH2_PROFILE:				MRM_WrByte(_mCH2_PROF, lMnEgn.mPr.prof[APP_CH_2]);					break;
		case MnEGN_OPT_CH2_TVG:					MRM_WrByte(_mCH2_TVG, lMnEgn.mPr.tvg[APP_CH_2]);					break;
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:	MRM_WrWord(_mCH2_WINDOW_TIME_L, lMnEgn.mPr.window_time[APP_CH_2]);	break;
		case MnEGN_OPT_CH2_WINDOW_RANGE:		MRM_WrWord(_mCH2_WINDOW_RANGE_L, lMnEgn.mPr.window_range[APP_CH_2]);break;
		case MnEGN_OPT_MSR:						MRM_WrByte(_mSTRU_ON_OFF, lMnEgn.mPr.msr);							break;
		default:																									break;
	}
}


void MnEGN_PrSet_Ch_Value(U08 ch,U08 iIt,S32 val)
{

	if(ch == APP_CH_1)
	{
		switch(iIt)
		{
			case MnEGN_OPT_SINGLE_THRESHOLD_SYNC:		MnEGN_PrSet_Value(MnEGN_OPT_THRESHOLD_SYNC,val);	break;
			case MnEGN_OPT_SINGLE_PROFILE:				MnEGN_PrSet_Value(MnEGN_OPT_CH1_PROFILE,val);	break;
			case MnEGN_OPT_SINGLE_TVG:					MnEGN_PrSet_Value(MnEGN_OPT_CH1_TVG,val);	break;
			case MnEGN_OPT_SINGLE_WINDOW_RESET_TIME:	MnEGN_PrSet_Value(MnEGN_OPT_CH1_WINDOW_RESET_TIME,val);	break;
			case MnEGN_OPT_SINGLE_WINDOW_RANGE:			MnEGN_PrSet_Value(MnEGN_OPT_CH1_WINDOW_RANGE,val);	break;
			case MnEGN_OPT_SINGLE_MSR:					MnEGN_PrSet_Value(MnEGN_OPT_THRESHOLD_SYNC,val);	break;
		}
	}
	else if(ch == APP_CH_2)
	{
		switch(iIt)
		{
			case MnEGN_OPT_SINGLE_THRESHOLD_SYNC:		MnEGN_PrSet_Value(MnEGN_OPT_THRESHOLD_SYNC,val);	break;
			case MnEGN_OPT_SINGLE_PROFILE:				MnEGN_PrSet_Value(MnEGN_OPT_CH2_PROFILE,val);	break;
			case MnEGN_OPT_SINGLE_TVG:					MnEGN_PrSet_Value(MnEGN_OPT_CH2_TVG,val);	break;
			case MnEGN_OPT_SINGLE_WINDOW_RESET_TIME:	MnEGN_PrSet_Value(MnEGN_OPT_CH2_WINDOW_RESET_TIME,val);	break;
			case MnEGN_OPT_SINGLE_WINDOW_RANGE:			MnEGN_PrSet_Value(MnEGN_OPT_CH2_WINDOW_RANGE,val);	break;
			case MnEGN_OPT_SINGLE_MSR:					MnEGN_PrSet_Value(MnEGN_OPT_THRESHOLD_SYNC,val);	break;
		}
	}
}




void MnEGN_PrRst_Factory(void)
{
	MRM_WrByte(_mTHR_SYNC, MnEGN_THRESHOLD_SYNC_DFT);
	MRM_WrByte(_mCH1_PROF, MnEGN_PROFILE_DEF);
	MRM_WrByte(_mCH1_TVG,  MnEGN_TVG_DEF);
	MRM_WrWord(_mCH1_WINDOW_TIME_L, MnEGN_WINDOW_RESET_TIME_DEF);
	MRM_WrWord(_mCH1_WINDOW_RANGE_L, MnEGN_WINDOW_RANGE_DEF);
	MRM_WrByte(_mCH2_PROF, MnEGN_PROFILE_DEF);
	MRM_WrByte(_mCH2_TVG,  MnEGN_TVG_DEF);
	MRM_WrWord(_mCH2_WINDOW_TIME_L, MnEGN_WINDOW_RESET_TIME_DEF);
	MRM_WrWord(_mCH2_WINDOW_RANGE_L, MnEGN_WINDOW_RANGE_DEF);
	MRM_WrByte(_mSTRU_ON_OFF, MnEGN_MSR_DEF);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnEGN_GetLayer(void)			{	return lMnEgn.lyr;		}
// Set
void MnEGN_SetLayer(U08 lyr)		{	lMnEgn.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnEGN_PrInitMain(void)
{
	U08 i;
	
	lMnEgn.mPr.thr_sync 				= MRM_RdByte(_mTHR_SYNC);
	lMnEgn.mPr.prof[APP_CH_1] 			= MRM_RdByte(_mCH1_PROF);
	lMnEgn.mPr.tvg[APP_CH_1]  			= MRM_RdByte(_mCH1_TVG);
	lMnEgn.mPr.window_time[APP_CH_1]  	= MRM_RdWord(_mCH1_WINDOW_TIME_L);
	lMnEgn.mPr.window_range[APP_CH_1]   = MRM_RdWord(_mCH1_WINDOW_RANGE_L);
	lMnEgn.mPr.prof[APP_CH_2] 			= MRM_RdByte(_mCH2_PROF);
	lMnEgn.mPr.tvg[APP_CH_2]  			= MRM_RdByte(_mCH2_TVG);
	lMnEgn.mPr.window_time[APP_CH_2]  	= MRM_RdWord(_mCH2_WINDOW_TIME_L);
	lMnEgn.mPr.window_range[APP_CH_2]   = MRM_RdWord(_mCH2_WINDOW_RANGE_L);
	lMnEgn.mPr.msr						= MRM_RdByte(_mSTRU_ON_OFF);
	
	if(lMnEgn.mPr.thr_sync > MnEGN_THRESHOLD_SYNC_MAX)	lMnEgn.mPr.thr_sync = MnEGN_THRESHOLD_SYNC_DFT;

	for(i=0; i<APP_CH_NUM; i++)
	{
		if(lMnEgn.mPr.prof[i] > MnEGN_PROFILE_MAX)							lMnEgn.mPr.prof[i] = MnEGN_PROFILE_DEF;
		if(lMnEgn.mPr.tvg[i]  > MnEGN_TVG_MAX)								lMnEgn.mPr.tvg[i] = MnEGN_TVG_DEF;
		if(lMnEgn.mPr.window_time[i]  > MnEGN_WINDOW_RESET_TIME_MAX)		lMnEgn.mPr.window_time[i] = MnEGN_WINDOW_RESET_TIME_DEF;
		if(lMnEgn.mPr.window_range[i] > MnEGN_WINDOW_RANGE_MAX)				lMnEgn.mPr.window_range[i] = MnEGN_WINDOW_RANGE_DEF;
	}

	if(lMnEgn.mPr.msr > MnEGN_MSR_MAX)	lMnEgn.mPr.msr = MnEGN_MSR_DEF;
}

void MnEGN_InitMain(void)
{
	lMnEgn.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnEGN_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

