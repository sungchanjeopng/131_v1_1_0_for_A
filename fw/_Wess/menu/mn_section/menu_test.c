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
#include "menu_test.h"

#include "menu_data.h"
#include "data_save.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnTST_LS lMnTst;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
S32 MnTST_PrGet_Value(U08 itm)
{
	S32 val = MENU_VAL_INVALID;
	
	switch(itm)
	{
		case MnTST_OPT_HW_RX_AMP:				val = lMnTst.mPr.hw_rx_amp;				break;
		case MnTST_OPT_CH1_SMOOTH_NO:			val = lMnTst.mPr.smooth_num[APP_CH_1];	break;
		case MnTST_OPT_CH1_SMOOTH_RANGE:		val = lMnTst.mPr.smooth_range[APP_CH_1];	break;
		case MnTST_OPT_CH1_THR_RANGE:			val = lMnTst.mPr.thr_range[APP_CH_1];	break;
		case MnTST_OPT_CH1_THR_MIN:				val = lMnTst.mPr.thr_min[APP_CH_1];	break;
		case MnTST_OPT_CH1_PULSE_NO:			val = lMnTst.mPr.pulse_num[APP_CH_1];	break;
		case MnTST_OPT_CH1_ECHO_AMP_B:			val = lMnTst.mPr.echo_amp_b[APP_CH_1];	break;
		case MnTST_OPT_CH2_SMOOTH_NO:			val = lMnTst.mPr.smooth_num[APP_CH_2];	break;
		case MnTST_OPT_CH2_SMOOTH_RANGE:		val = lMnTst.mPr.smooth_range[APP_CH_2];	break;
		case MnTST_OPT_CH2_THR_RANGE:			val = lMnTst.mPr.thr_range[APP_CH_2];	break;
		case MnTST_OPT_CH2_THR_MIN:				val = lMnTst.mPr.thr_min[APP_CH_2];	break;
		case MnTST_OPT_CH2_PULSE_NO:			val = lMnTst.mPr.pulse_num[APP_CH_2];	break;
		case MnTST_OPT_CH2_ECHO_AMP_B:			val = lMnTst.mPr.echo_amp_b[APP_CH_2];	break;
		case MnTST_OPT_FILTER_RANGE:			val = lMnTst.mPr.judge_heigh_in;				break;
		case MnTST_OPT_FILTER_TIME:				val = lMnTst.mPr.judge_time;					break;
		case MnTST_OPT_SENSOR_DISTANCE:			val = lMnTst.mPr.sensor_distance;				break;
		case MnTST_OPT_DEMO_MODE:				val = lMnTst.mPr.demo_mode;				break;
		case MnTST_OPT_DEBUG_MODE:				val = lMnTst.mPr.debug_mode;				break;
		case MnTST_OPT_CH1_HEAVY_HOLD:			val = lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_HEAVY];	break;
		case MnTST_OPT_CH1_LIGHT_HOLD:			val = lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_LIGHT];	break;
		case MnTST_OPT_CH2_HEAVY_HOLD:			val = lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_HEAVY];	break;
		case MnTST_OPT_CH2_LIGHT_HOLD:			val = lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_LIGHT];	break;
		default:
			break;
	}

	return val;


#if 0
	switch(itm)
	{
		case MnTST_OPT_HW_RX_AMP:
		case MnTST_OPT_CH1_SMOOTH_NO:
		case MnTST_OPT_CH1_SMOOTH_RANGE:
		case MnTST_OPT_CH1_THR_RANGE:
		case MnTST_OPT_CH1_THR_MIN:
		case MnTST_OPT_CH1_PULSE_NO:
		case MnTST_OPT_CH1_ECHO_AMP_B:
		case MnTST_OPT_CH2_SMOOTH_NO:
		case MnTST_OPT_CH2_SMOOTH_RANGE:
		case MnTST_OPT_CH2_THR_RANGE:
		case MnTST_OPT_CH2_THR_MIN:
		case MnTST_OPT_CH2_PULSE_NO:
		case MnTST_OPT_CH2_ECHO_AMP_B:		
		case MnTST_OPT_FILTER_RANGE:
		case MnTST_OPT_JUDGE_HEIGHT_OUT:
		case MnTST_OPT_FILTER_TIME:
		case MnTST_OPT_SENSOR_DISTANCE:
		case MnTST_OPT_DEMO_MODE:
		case MnTST_OPT_DEBUG_MODE:
		case MnTST_OPT_CLEAN_MODE:
		default:
			break;
	}

#endif	
}

S32 MnTST_PrGet_CH_Value(U08 ch,U08 itm)
{
	S32 val = MENU_VAL_INVALID;

	switch(itm)
	{
		case MnTST_OPT_SINGLE_HW_RX_AMP:				val = lMnTst.mPr.hw_rx_amp;					break;
		case MnTST_OPT_SINGLE_SMOOTH_NO:			val = lMnTst.mPr.smooth_num[ch];			break;
		case MnTST_OPT_SINGLE_SMOOTH_RANGE:		val = lMnTst.mPr.smooth_range[ch];			break;
		case MnTST_OPT_SINGLE_THR_RANGE:			val = lMnTst.mPr.thr_range[ch];				break;
		case MnTST_OPT_SINGLE_THR_MIN:				val = lMnTst.mPr.thr_min[ch];				break;
		case MnTST_OPT_SINGLE_PULSE_NO:			val = lMnTst.mPr.pulse_num[ch];				break;
		case MnTST_OPT_SINGLE_ECHO_AMP_B:			val = lMnTst.mPr.echo_amp_b[ch];			break;
		case MnTST_OPT_SINGLE_FILTER_RANGE:			val = lMnTst.mPr.judge_heigh_in;			break;
		case MnTST_OPT_SINGLE_FILTER_TIME:				val = lMnTst.mPr.judge_time;				break;
		case MnTST_OPT_SINGLE_SENSOR_DISTANCE:			val = lMnTst.mPr.sensor_distance;			break;
		case MnTST_OPT_SINGLE_DEMO_MODE:				val = lMnTst.mPr.demo_mode;					break;
		case MnTST_OPT_SINGLE_DEBUG_MODE:				val = lMnTst.mPr.debug_mode;				break;
		case MnTST_OPT_SINGLE_HEAVY_HOLD:				val = lMnTst.mPr.hold_value[ch][MsCAL_THR_HEAVY];	break;
		case MnTST_OPT_SINGLE_LIGHT_HOLD:				val = lMnTst.mPr.hold_value[ch][MsCAL_THR_LIGHT];	break;					
		default:
			break;
	}


	return val;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
void MnTST_PrSet_Value(S32 val)
{
	U08 iIt = MnLY2_GetIdxItem();

	switch(iIt)
	{
		case MnTST_OPT_HW_RX_AMP:				lMnTst.mPr.hw_rx_amp = val;				break;
		case MnTST_OPT_CH1_SMOOTH_NO:			lMnTst.mPr.smooth_num[APP_CH_1]= val;	 break;
		case MnTST_OPT_CH1_SMOOTH_RANGE:		lMnTst.mPr.smooth_range[APP_CH_1]= val;	 	break;
		case MnTST_OPT_CH1_THR_RANGE:			lMnTst.mPr.thr_range[APP_CH_1]= val;	 	break;
		case MnTST_OPT_CH1_THR_MIN:				lMnTst.mPr.thr_min[APP_CH_1]= val;		 	break;
		case MnTST_OPT_CH1_PULSE_NO:			lMnTst.mPr.pulse_num[APP_CH_1]= val;	 	break;
		case MnTST_OPT_CH1_ECHO_AMP_B:			lMnTst.mPr.echo_amp_b[APP_CH_1]= val;	 	break;
		case MnTST_OPT_CH2_SMOOTH_NO:			lMnTst.mPr.smooth_num[APP_CH_2]= val;	 	break;
		case MnTST_OPT_CH2_SMOOTH_RANGE:		lMnTst.mPr.smooth_range[APP_CH_2]= val;	 	break;
		case MnTST_OPT_CH2_THR_RANGE:			lMnTst.mPr.thr_range[APP_CH_2]= val;	 	break;
		case MnTST_OPT_CH2_THR_MIN:				lMnTst.mPr.thr_min[APP_CH_2]= val;		 	break;
		case MnTST_OPT_CH2_PULSE_NO:			lMnTst.mPr.pulse_num[APP_CH_2]= val;	 	break;
		case MnTST_OPT_CH2_ECHO_AMP_B:			lMnTst.mPr.echo_amp_b[APP_CH_2]= val;	 	break;
		case MnTST_OPT_FILTER_RANGE:			lMnTst.mPr.judge_heigh_in= val;						break;
		case MnTST_OPT_FILTER_TIME:				lMnTst.mPr.judge_time= val;							break;	
		case MnTST_OPT_SENSOR_DISTANCE:			lMnTst.mPr.sensor_distance= val;					break;
		case MnTST_OPT_DEMO_MODE:				
			lMnTst.mPr.demo_mode= val;							
			DaSAV_DumpInit();
			MnDAT_Set_f_save(FALSE);
			break;
		case MnTST_OPT_DEBUG_MODE:				lMnTst.mPr.debug_mode= val;							break;
		case MnTST_OPT_CH1_HEAVY_HOLD:			lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_HEAVY]= val;	break;
		case MnTST_OPT_CH1_LIGHT_HOLD:			lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_LIGHT]= val;	break;
		case MnTST_OPT_CH2_HEAVY_HOLD:			lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_HEAVY]= val;	break;
		case MnTST_OPT_CH2_LIGHT_HOLD:			lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_LIGHT]= val;	break;
		default:
			break;
	}

	


	switch(iIt)
	{
		case MnTST_OPT_HW_RX_AMP:				MRM_WrByte(_mHW_RX_AMP, lMnTst.mPr.hw_rx_amp);	break;
		case MnTST_OPT_CH1_SMOOTH_NO:			MRM_WrByte(_mCH1_SMOOTH_NUM, lMnTst.mPr.smooth_num[APP_CH_1]);	break;
		case MnTST_OPT_CH1_SMOOTH_RANGE:		MRM_WrByte(_mCH1_SMOOTH_RANGE, lMnTst.mPr.smooth_range[APP_CH_1]);	break;
		case MnTST_OPT_CH1_THR_RANGE:			MRM_WrWord(_mCH1_THR_RANGE_L, lMnTst.mPr.thr_range[APP_CH_1]);	break;
		case MnTST_OPT_CH1_THR_MIN:				MRM_WrWord(_mCH1_THR_MIN_L, lMnTst.mPr.thr_min[APP_CH_1]);	break;
		case MnTST_OPT_CH1_PULSE_NO:			MRM_WrWord(_mCH1_PULSE_NUM_L, lMnTst.mPr.pulse_num[APP_CH_1]);	break;
		case MnTST_OPT_CH1_ECHO_AMP_B:			MRM_WrWord(_mCH1_ECHO_AMP_B_L, lMnTst.mPr.echo_amp_b[APP_CH_1]);	break;
		case MnTST_OPT_CH2_SMOOTH_NO:			MRM_WrByte(_mCH2_SMOOTH_NUM, lMnTst.mPr.smooth_num[APP_CH_2]);	break;
		case MnTST_OPT_CH2_SMOOTH_RANGE:		MRM_WrByte(_mCH2_SMOOTH_RANGE, lMnTst.mPr.smooth_range[APP_CH_2]);	break;
		case MnTST_OPT_CH2_THR_RANGE:			MRM_WrWord(_mCH2_THR_RANGE_L, lMnTst.mPr.thr_range[APP_CH_2]);	break;
		case MnTST_OPT_CH2_THR_MIN: 			MRM_WrWord(_mCH2_THR_MIN_L, lMnTst.mPr.thr_min[APP_CH_2]);	break;
		case MnTST_OPT_CH2_PULSE_NO:			MRM_WrWord(_mCH2_PULSE_NUM_L, lMnTst.mPr.pulse_num[APP_CH_2]);	break;
		case MnTST_OPT_CH2_ECHO_AMP_B:			MRM_WrWord(_mCH2_ECHO_AMP_B_L, lMnTst.mPr.echo_amp_b[APP_CH_2]);	break;
		case MnTST_OPT_FILTER_RANGE:			MRM_WrWord(_mFILTER_RANGE_L, lMnTst.mPr.judge_heigh_in);	break;
		case MnTST_OPT_FILTER_TIME:				MRM_WrWord(_mFILTER_TIME_L, lMnTst.mPr.judge_time);	break;
		case MnTST_OPT_SENSOR_DISTANCE:			MRM_WrWord(_mSENSOR_DISTANCE_L, lMnTst.mPr.sensor_distance);	break;
		case MnTST_OPT_DEMO_MODE:				MRM_WrByte(_mDEMO_MODE, lMnTst.mPr.demo_mode);	break;
		case MnTST_OPT_DEBUG_MODE:				MRM_WrByte(_mDEBUG_MODE, lMnTst.mPr.debug_mode);	break;
		case MnTST_OPT_CH1_HEAVY_HOLD:			MRM_WrWord(_mCH1_HOLD_HEAVY_VAL_L, lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_HEAVY]);	break;
		case MnTST_OPT_CH1_LIGHT_HOLD:			MRM_WrWord(_mCH1_HOLD_LIGHT_VAL_L, lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_LIGHT]);	break;
		case MnTST_OPT_CH2_HEAVY_HOLD:			MRM_WrWord(_mCH2_HOLD_HEAVY_VAL_L,lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_HEAVY]);	break;
		case MnTST_OPT_CH2_LIGHT_HOLD:			MRM_WrWord(_mCH2_HOLD_LIGHT_VAL_L, lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_LIGHT]);	break;
		default:	
			break;
	}
}

#if 0
void MnEGN_PrSet_CH_Value(U08 ch,S32 val)
{
	U08 iIt = MnLY2_GetIdxItem();

	switch(iIt)
	{
		case MnTST_OPT_SINGLE_HW_RX_AMP:				lMnTst.mPr.hw_rx_amp = val;				break;
		case MnTST_OPT_SINGLE_SMOOTH_NO:				lMnTst.mPr.smooth_num[ch]= val;				break;
		case MnTST_OPT_SINGLE_SMOOTH_RANGE:				lMnTst.mPr.smooth_range[ch]= val;				break;
		case MnTST_OPT_SINGLE_THR_RANGE:				lMnTst.mPr.thr_range[ch]= val;				break;
		case MnTST_OPT_SINGLE_THR_MIN:					lMnTst.mPr.thr_min[ch]= val;				break;
		case MnTST_OPT_SINGLE_PULSE_NO:					lMnTst.mPr.pulse_num[ch]= val;				break;
		case MnTST_OPT_SINGLE_ECHO_AMP_B:				lMnTst.mPr.echo_amp_b[ch]= val;				break;
		case MnTST_OPT_SINGLE_FILTER_RANGE:				lMnTst.mPr.judge_heigh_in= val;				break;
		case MnTST_OPT_SINGLE_HEIGHT_OUT:				lMnTst.mPr.judge_heigh_out= val;				break;
		case MnTST_OPT_SINGLE_FILTER_TIME:				lMnTst.mPr.judge_time= val;				break;
		case MnTST_OPT_SINGLE_SENSOR_DISTANCE:			lMnTst.mPr.sensor_distance= val;				break;
		case MnTST_OPT_SINGLE_DEMO_MODE:				lMnTst.mPr.demo_mode= val;				break;
		case MnTST_OPT_SINGLE_DEBUG_MODE:				lMnTst.mPr.debug_mode= val;				break;
		default:
			break;
	}


	switch(iIt)
	{
		case MnTST_OPT_SINGLE_HW_RX_AMP:				MRM_WrByte(_mHW_RX_AMP, lMnTst.mPr.hw_rx_amp);	break;
		case MnTST_OPT_SINGLE_SMOOTH_NO:			MRM_WrByte(_mCH1_SMOOTH_NUM, lMnTst.mPr.smooth_num[APP_CH_1]);	break;
		case MnTST_OPT_CH1_SMOOTH_RANGE:		MRM_WrByte(_mCH1_SMOOTH_RANGE, lMnTst.mPr.smooth_range[APP_CH_1]);	break;
		case MnTST_OPT_CH1_THR_RANGE:			MRM_WrWord(_mCH1_THR_RANGE_L, lMnTst.mPr.thr_range[APP_CH_1]);	break;
		case MnTST_OPT_CH1_THR_MIN:				MRM_WrWord(_mCH1_THR_MIN_L, lMnTst.mPr.thr_min[APP_CH_1]);	break;
		case MnTST_OPT_CH1_PULSE_NO:			MRM_WrWord(_mCH1_PULSE_NUM_L, lMnTst.mPr.pulse_num[APP_CH_1]);	break;
		case MnTST_OPT_CH1_ECHO_AMP_B:			MRM_WrWord(_mCH1_ECHO_AMP_B_L, lMnTst.mPr.echo_amp_b[APP_CH_1]);	break;
		case MnTST_OPT_CH2_SMOOTH_NO:			MRM_WrByte(_mCH2_SMOOTH_NUM, lMnTst.mPr.smooth_num[APP_CH_2]);	break;
		case MnTST_OPT_CH2_SMOOTH_RANGE:		MRM_WrByte(_mCH2_SMOOTH_RANGE, lMnTst.mPr.smooth_range[APP_CH_2]);	break;
		case MnTST_OPT_CH2_THR_RANGE:			MRM_WrWord(_mCH2_THR_RANGE_L, lMnTst.mPr.thr_range[APP_CH_2]);	break;
		case MnTST_OPT_CH2_THR_MIN: 			MRM_WrWord(_mCH2_THR_MIN_L, lMnTst.mPr.thr_min[APP_CH_2]);	break;
		case MnTST_OPT_CH2_PULSE_NO:			MRM_WrWord(_mCH2_PULSE_NUM_L, lMnTst.mPr.pulse_num[APP_CH_2]);	break;
		case MnTST_OPT_CH2_ECHO_AMP_B:			MRM_WrWord(_mCH2_ECHO_AMP_B_L, lMnTst.mPr.echo_amp_b[APP_CH_2]);	break;
		case MnTST_OPT_FILTER_RANGE:			MRM_WrWord(_mFILTER_RANGE_L, lMnTst.mPr.judge_heigh_in);	break;
		case MnTST_OPT_JUDGE_HEIGHT_OUT:		MRM_WrWord(_mJUDGE_HEIGHT_OUT_L, lMnTst.mPr.judge_heigh_out);	break;
		case MnTST_OPT_FILTER_TIME:				MRM_WrWord(_mFILTER_TIME_L, lMnTst.mPr.judge_time);	break;
		case MnTST_OPT_SENSOR_DISTANCE:			MRM_WrWord(_mSENSOR_DISTANCE_L, lMnTst.mPr.sensor_distance);	break;
		case MnTST_OPT_DEMO_MODE:				MRM_WrByte(_mDEMO_MODE, lMnTst.mPr.demo_mode);	break;
		case MnTST_OPT_DEBUG_MODE:				MRM_WrByte(_mDEBUG_MODE, lMnTst.mPr.debug_mode);	break;
		default:
			break;
	}
}
#endif




void MnTST_PrRst_Factory(void)
{
	MRM_WrByte(_mHW_RX_AMP,MnTST_HW_RX_AMP_DEF);
	MRM_WrByte(_mCH1_SMOOTH_NUM, MnTST_SMOOTH_NO_DEF);
	MRM_WrByte(_mCH1_SMOOTH_RANGE, MnTST_SMOOTH_RANGE_DEF);
	MRM_WrWord(_mCH1_THR_RANGE_L, MnTST_THR_RANGE_DEF);
	MRM_WrWord(_mCH1_THR_MIN_L, MnTST_THR_MIN_DEF);
	MRM_WrWord(_mCH1_PULSE_NUM_L, MnTST_PULSE_NO_DEF);
	MRM_WrWord(_mCH1_ECHO_AMP_B_L, MnTST_ECHO_AMP_B_DEF);
	MRM_WrByte(_mCH2_SMOOTH_NUM, MnTST_SMOOTH_NO_DEF);
	MRM_WrByte(_mCH2_SMOOTH_RANGE, MnTST_SMOOTH_RANGE_DEF);
	MRM_WrWord(_mCH2_THR_RANGE_L, MnTST_THR_RANGE_DEF);
	MRM_WrWord(_mCH2_THR_MIN_L, MnTST_THR_MIN_DEF);
	MRM_WrWord(_mCH2_PULSE_NUM_L, MnTST_PULSE_NO_DEF);
	MRM_WrWord(_mCH2_ECHO_AMP_B_L, MnTST_ECHO_AMP_B_DEF);
	MRM_WrWord(_mFILTER_RANGE_L, MnTST_FILTER_RANGE_DEF);
	MRM_WrWord(_mFILTER_TIME_L, MnTST_FILTER_TIME_DEF);
	MRM_WrWord(_mSENSOR_DISTANCE_L, MnTST_SENSOR_DISTANCE_DEF);
	MRM_WrByte(_mDEMO_MODE, MnTST_DEMO_MODE_DEF);
	MRM_WrByte(_mDEBUG_MODE, MnTST_DEBUG_MODE_DEF);

	MRM_WrWord(_mCH1_HOLD_HEAVY_VAL_L, MnTST_HOLD_VALUE_DEF);
	MRM_WrWord(_mCH1_HOLD_LIGHT_VAL_L, MnTST_HOLD_VALUE_DEF);
	MRM_WrWord(_mCH2_HOLD_HEAVY_VAL_L, MnTST_HOLD_VALUE_DEF);
	MRM_WrWord(_mCH2_HOLD_LIGHT_VAL_L, MnTST_HOLD_VALUE_DEF);

}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnTST_GetLayer(void)			{	return lMnTst.lyr;		}
// Set
void MnTST_SetLayer(U08 lyr)		{	lMnTst.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnTST_PrInitMain(void)
{
	U08 i;

	lMnTst.mPr.hw_rx_amp					= MRM_RdByte(_mHW_RX_AMP);
	lMnTst.mPr.smooth_num[APP_CH_1]			= MRM_RdByte(_mCH1_SMOOTH_NUM);
	lMnTst.mPr.smooth_range[APP_CH_1]		= MRM_RdByte(_mCH1_SMOOTH_RANGE);
	lMnTst.mPr.thr_range[APP_CH_1]			= MRM_RdWord(_mCH1_THR_RANGE_L);
	lMnTst.mPr.thr_min[APP_CH_1]			= MRM_RdWord(_mCH1_THR_MIN_L);
	lMnTst.mPr.pulse_num[APP_CH_1]			= MRM_RdWord(_mCH1_PULSE_NUM_L);
	lMnTst.mPr.echo_amp_b[APP_CH_1]			= MRM_RdWord(_mCH1_ECHO_AMP_B_L);
	lMnTst.mPr.smooth_num[APP_CH_2]			= MRM_RdByte(_mCH2_SMOOTH_NUM);
	lMnTst.mPr.smooth_range[APP_CH_2]		= MRM_RdByte(_mCH2_SMOOTH_RANGE);
	lMnTst.mPr.thr_range[APP_CH_2]			= MRM_RdWord(_mCH2_THR_RANGE_L);
	lMnTst.mPr.thr_min[APP_CH_2]			= MRM_RdWord(_mCH2_THR_MIN_L);
	lMnTst.mPr.pulse_num[APP_CH_2]			= MRM_RdWord(_mCH2_PULSE_NUM_L);
	lMnTst.mPr.echo_amp_b[APP_CH_2]			= MRM_RdWord(_mCH2_ECHO_AMP_B_L);
	lMnTst.mPr.judge_heigh_in				= MRM_RdWord(_mFILTER_RANGE_L);
	lMnTst.mPr.judge_time					= MRM_RdWord(_mFILTER_TIME_L);
	lMnTst.mPr.sensor_distance				= MRM_RdWord(_mSENSOR_DISTANCE_L);
	lMnTst.mPr.demo_mode					= MRM_RdByte(_mDEMO_MODE);
	lMnTst.mPr.debug_mode					= MRM_RdByte(_mDEBUG_MODE);	
	lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_HEAVY]	= MRM_RdWord(_mCH1_HOLD_HEAVY_VAL_L);
	lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_HEAVY]	= MRM_RdWord(_mCH2_HOLD_HEAVY_VAL_L);
	lMnTst.mPr.hold_value[APP_CH_1][MsCAL_THR_LIGHT]	= MRM_RdWord(_mCH1_HOLD_LIGHT_VAL_L);
	lMnTst.mPr.hold_value[APP_CH_2][MsCAL_THR_LIGHT]	= MRM_RdWord(_mCH2_HOLD_LIGHT_VAL_L);


	if(lMnTst.mPr.hw_rx_amp > MnTST_HW_RX_AMP_MAX)		lMnTst.mPr.hw_rx_amp = MnTST_HW_RX_AMP_DEF;

	for(i=0; i<APP_CH_NUM; i++)
	{
		if(lMnTst.mPr.smooth_num[i] > MnTST_SMOOTH_NO_MAX)		lMnTst.mPr.smooth_num[i] = MnTST_SMOOTH_NO_DEF;
		if(lMnTst.mPr.smooth_range[i] > MnTST_SMOOTH_RANGE_MAX)	lMnTst.mPr.smooth_range[i] = MnTST_SMOOTH_RANGE_DEF;
		if(lMnTst.mPr.thr_range[i] > MnTST_THR_RANGE_MAX)		lMnTst.mPr.thr_range[i] = MnTST_THR_RANGE_DEF;
		if(lMnTst.mPr.thr_min[i] > MnTST_THR_MIN_MAX)			lMnTst.mPr.thr_min[i] = MnTST_THR_MIN_DEF;
		if(lMnTst.mPr.pulse_num[i] > MnTST_PULSE_NO_MAX)		lMnTst.mPr.pulse_num[i] = MnTST_PULSE_NO_DEF;
		if(lMnTst.mPr.echo_amp_b[i] > MnTST_ECHO_AMP_B_MAX)		lMnTst.mPr.echo_amp_b[i] = MnTST_ECHO_AMP_B_DEF;
		if(lMnTst.mPr.hold_value[i][MsCAL_THR_LIGHT] > MnTST_HOLD_VALUE_MAX)		
			lMnTst.mPr.hold_value[i][MsCAL_THR_LIGHT] = MnTST_HOLD_VALUE_DEF;
		if(lMnTst.mPr.hold_value[i][MsCAL_THR_HEAVY] > MnTST_HOLD_VALUE_MAX) 	
			lMnTst.mPr.hold_value[i][MsCAL_THR_HEAVY]  = MnTST_HOLD_VALUE_DEF;


	}


	if(lMnTst.mPr.judge_heigh_in > MnTST_FILTER_RANGE_MAX)		lMnTst.mPr.judge_heigh_in = MnTST_FILTER_RANGE_DEF;
	if(lMnTst.mPr.judge_time > MnTST_FILTER_TIME_MAX)				lMnTst.mPr.judge_time = MnTST_FILTER_TIME_DEF;
	if(lMnTst.mPr.sensor_distance > MnTST_SENSOR_DISTANCE_MAX)		lMnTst.mPr.sensor_distance = MnTST_SENSOR_DISTANCE_DEF;
	if(lMnTst.mPr.demo_mode  > MnTST_DEMO_MODE_MAX)					lMnTst.mPr.demo_mode = MnTST_DEMO_MODE_DEF;
	if(lMnTst.mPr.debug_mode > MnTST_DEBUG_MODE_MAX)				lMnTst.mPr.debug_mode = MnTST_DEBUG_MODE_DEF;
	
}

void MnTST_InitMain(void)
{
	lMnTst.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnTST_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

