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
// data
#include "data_save.h"
// self
#include "menu_measure.h"
// screen
#include "screen_main.h"
// measure
#include "measure_calc.h"
#include "measure_cal1_field0.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnMSR_LS lMnMsr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
S32  MnMSR_Get_Unit(void)	{	return lMnMsr.mBasePr.unit;		}

S32 MnMSR_BaseGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnMS0_OPT_UNIT:					val = lMnMsr.mBasePr.unit;						break;
		case MnMS0_OPT_CH1_OPERATION:			val = lMnMsr.mBasePr.operation[MnMSR_CH_0];		break;
		case MnMS0_OPT_CH1_EMPTY:				val = lMnMsr.mBasePr.empty[MnMSR_CH_0];			break;		
		case MnMS0_OPT_CH1_DEADZONE:			val = lMnMsr.mBasePr.deadzone[MnMSR_CH_0];		break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		val = lMnMsr.mBasePr.measure_cycle[MnMSR_CH_0];	break;
		case MnMS0_OPT_CH1_MEASURE_RESET:		val = MENU_CHK_NO;								break;
		case MnMS0_OPT_CH2_OPERATION:			val = lMnMsr.mBasePr.operation[MnMSR_CH_1];		break;	
		case MnMS0_OPT_CH2_EMPTY:				val = lMnMsr.mBasePr.empty[MnMSR_CH_1];			break;
		case MnMS0_OPT_CH2_DEADZONE:			val = lMnMsr.mBasePr.deadzone[MnMSR_CH_1];		break;
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		val = lMnMsr.mBasePr.measure_cycle[MnMSR_CH_1];	break;
		case MnMS0_OPT_CH2_MEASURE_RESET:		val = MENU_CHK_NO;								break;
		default:								break;
	}
	
	return val;
}

S32 MnMSR_BaseGet_Ch_Value(U08 ch,U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnMS0_OPT_SINGLE_UNIT:				val = lMnMsr.mBasePr.unit;				break;
		case MnMS0_OPT_SINGLE_OPERATION:		val = lMnMsr.mBasePr.operation[ch];		break;
		case MnMS0_OPT_SINGLE_EMPTY:			val = lMnMsr.mBasePr.empty[ch];			break;		
		case MnMS0_OPT_SINGLE_DEADZONE:			val = lMnMsr.mBasePr.deadzone[ch];		break;
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:	val = lMnMsr.mBasePr.measure_cycle[ch];	break;
		case MnMS0_OPT_SINGLE_MEASURE_RESET:	val = MENU_CHK_NO;						break;
		default:								break;
	}
	
	return val;	

}

S32 MnMSR_CalGet_Ch_Value(U08 ch,U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnMS1_OPT_SINGLE_FREQ:			val = lMnMsr.mCalPr.freq[ch];				break;
		case MnMS1_OPT_SINGLE_ECHO_AMP:		val = lMnMsr.mCalPr.echo_amp[ch];			break;
		case MnMS1_OPT_SINGLE_THR_LIGHT:	val = lMnMsr.mCalPr.thr_light_mod[ch];		break;
		case MnMS1_OPT_SINGLE_THR_HEAVY:	val = lMnMsr.mCalPr.thr_heavy_mod[ch];		break;
		case MnMS1_OPT_SINGLE_ASF_HEAVY:	val = lMnMsr.mCalPr.asf[ch][MsCAL_THR_HEAVY];	break;
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	val = lMnMsr.mCalPr.asf[ch][MsCAL_THR_LIGHT];	break;
		case MnMS1_OPT_SINGLE_DAMPING:		val = lMnMsr.mCalPr.damp[ch];				break;
		case MnMS1_OPT_SINGLE_OFFSET:		val = lMnMsr.mCalPr.offset[ch];				break;
		default:							break;
	}

	return val;
}

S32 MnMSR_CalGet_Value(U08 iIt)
{
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case MnMS1_OPT_CH1_FREQ:			val = lMnMsr.mCalPr.freq[MnMSR_CH_0];				break;
		case MnMS1_OPT_CH1_ECHO_AMP:		val = lMnMsr.mCalPr.echo_amp[MnMSR_CH_0];			break;
		case MnMS1_OPT_CH1_THR_LIGHT:		val = lMnMsr.mCalPr.thr_light_mod[MnMSR_CH_0];		break;
		case MnMS1_OPT_CH1_THR_HEAVY:		val = lMnMsr.mCalPr.thr_heavy_mod[MnMSR_CH_0];		break;
		case MnMS1_OPT_CH1_ASF_HEAVY:		val = lMnMsr.mCalPr.asf[MnMSR_CH_0][MsCAL_THR_HEAVY];		break;
		case MnMS1_OPT_CH1_ASF_LIGHT:		val = lMnMsr.mCalPr.asf[MnMSR_CH_0][MsCAL_THR_LIGHT];		break;		
		case MnMS1_OPT_CH1_DAMPING:			val = lMnMsr.mCalPr.damp[MnMSR_CH_0];				break;
		case MnMS1_OPT_CH1_OFFSET:			val = lMnMsr.mCalPr.offset[MnMSR_CH_0];				break;
		case MnMS1_OPT_CH2_FREQ:			val = lMnMsr.mCalPr.freq[MnMSR_CH_1];				break;
		case MnMS1_OPT_CH2_ECHO_AMP:		val = lMnMsr.mCalPr.echo_amp[MnMSR_CH_1];			break;
		case MnMS1_OPT_CH2_THR_LIGHT:		val = lMnMsr.mCalPr.thr_light_mod[MnMSR_CH_1];		break;
		case MnMS1_OPT_CH2_THR_HEAVY:		val = lMnMsr.mCalPr.thr_heavy_mod[MnMSR_CH_1];		break;
		case MnMS1_OPT_CH2_ASF_HEAVY:		val = lMnMsr.mCalPr.asf[MnMSR_CH_1][MsCAL_THR_HEAVY];	break;
		case MnMS1_OPT_CH2_ASF_LIGHT:		val = lMnMsr.mCalPr.asf[MnMSR_CH_1][MsCAL_THR_LIGHT];	break;
		case MnMS1_OPT_CH2_DAMPING:			val = lMnMsr.mCalPr.damp[MnMSR_CH_1];				break;
		case MnMS1_OPT_CH2_OFFSET:			val = lMnMsr.mCalPr.offset[MnMSR_CH_1];				break;
		default:							break;
	}

	return val;
}


S32 MnMSR_Get_Threshold_Value(U08 sel)
{
	S32 val = MENU_VAL_INVALID;

	switch(sel)
	{
		case MnMS1_OPT_CH1_THR_LIGHT:		val = lMnMsr.mCalPr.thr_val[MnMSR_CH_0][MsCAL_THR_LIGHT];		break;
		case MnMS1_OPT_CH1_THR_HEAVY:		val = lMnMsr.mCalPr.thr_val[MnMSR_CH_0][MsCAL_THR_HEAVY];		break;
		case MnMS1_OPT_CH2_THR_LIGHT:		val = lMnMsr.mCalPr.thr_val[MnMSR_CH_1][MsCAL_THR_LIGHT];		break;
		case MnMS1_OPT_CH2_THR_HEAVY:		val = lMnMsr.mCalPr.thr_val[MnMSR_CH_1][MsCAL_THR_HEAVY];		break;		
		default:							break;
	}


	return val;
}

S32 MnMSR_Get_Threshold_Ch_Value(U08 ch, U08 sel)
{
	S32 val = MENU_VAL_INVALID;


	switch(sel)
	{
		case MnMS1_OPT_SINGLE_THR_LIGHT:	val = lMnMsr.mCalPr.thr_val[ch][MsCAL_THR_LIGHT];		break;
		case MnMS1_OPT_SINGLE_THR_HEAVY:	val = lMnMsr.mCalPr.thr_val[ch][MsCAL_THR_HEAVY];		break;		
		default:							break;
	}

	return val;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
void MnMSR_BaseSet_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnMS0_OPT_UNIT:					lMnMsr.mBasePr.unit = val;						break;
		case MnMS0_OPT_CH1_OPERATION:			lMnMsr.mBasePr.operation[APP_CH_1] = val;		break;
		case MnMS0_OPT_CH1_EMPTY:				lMnMsr.mBasePr.empty[APP_CH_1] = val;			CalPrc_ResetFlag(APP_CH_1);	break;		
		case MnMS0_OPT_CH1_DEADZONE:			lMnMsr.mBasePr.deadzone[APP_CH_1] = val;		CalPrc_ResetFlag(APP_CH_1);	break;	
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		lMnMsr.mBasePr.measure_cycle[APP_CH_1] = val;	 break;	
		case MnMS0_OPT_CH1_MEASURE_RESET:
			switch(MnLY3_GetValue())
			{
				case MENU_CHK_YES:				CalPrc_ResetFlag(APP_CH_1); break;
				case MENU_CHK_NO:
				default:													break;
			}
			break;
		case MnMS0_OPT_CH2_OPERATION:			lMnMsr.mBasePr.operation[APP_CH_2] = val;		break;	
		case MnMS0_OPT_CH2_EMPTY:				lMnMsr.mBasePr.empty[APP_CH_2] = val;			CalPrc_ResetFlag(APP_CH_2);	break;	
		case MnMS0_OPT_CH2_DEADZONE:			lMnMsr.mBasePr.deadzone[APP_CH_2] = val;		CalPrc_ResetFlag(APP_CH_2);	break;	
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		lMnMsr.mBasePr.measure_cycle[APP_CH_2] = val;	break;	
		case MnMS0_OPT_CH2_MEASURE_RESET:
			switch(MnLY3_GetValue())
			{
				case MENU_CHK_YES:				CalPrc_ResetFlag(APP_CH_2);	break;
				case MENU_CHK_NO:
				default:						break;
			}
			break;
		default:								
			break;
	}	

	switch(iIt)
	{
		case MnMS0_OPT_UNIT:					MRM_WrByte(_mUNIT, lMnMsr.mBasePr.unit);								break;
		case MnMS0_OPT_CH1_OPERATION:			MRM_WrByte(_mCH1_OPERATION, lMnMsr.mBasePr.operation[APP_CH_1]);		break;
		case MnMS0_OPT_CH1_EMPTY:				MRM_WrWord(_mCH1_EMPTY_L, lMnMsr.mBasePr.empty[APP_CH_1]);				break;	
		case MnMS0_OPT_CH1_DEADZONE:			MRM_WrWord(_mCH1_DEADZONE_L, lMnMsr.mBasePr.deadzone[APP_CH_1]);		break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		MRM_WrByte(_mCH1_MSR_CYC, lMnMsr.mBasePr.measure_cycle[APP_CH_1]);		break;
		case MnMS0_OPT_CH1_MEASURE_RESET:		break;
		case MnMS0_OPT_CH2_OPERATION:			MRM_WrByte(_mCH2_OPERATION, lMnMsr.mBasePr.operation[APP_CH_2]);		break;	
		case MnMS0_OPT_CH2_EMPTY:				MRM_WrWord(_mCH2_EMPTY_L, lMnMsr.mBasePr.empty[APP_CH_2]);				break;	
		case MnMS0_OPT_CH2_DEADZONE:			MRM_WrWord(_mCH2_DEADZONE_L, lMnMsr.mBasePr.deadzone[APP_CH_2]);		break;
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		MRM_WrByte(_mCH2_MSR_CYC, lMnMsr.mBasePr.measure_cycle[APP_CH_2]);		break;
		case MnMS0_OPT_CH2_MEASURE_RESET:		break;
		default:								
			break;
	}	

}


void MnMSR_BaseSet_Ch_Value(U08 ch,U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnMS0_OPT_SINGLE_UNIT:					lMnMsr.mBasePr.unit = val;						break;
		case MnMS0_OPT_SINGLE_OPERATION:			lMnMsr.mBasePr.operation[ch] = val;		break;
		case MnMS0_OPT_SINGLE_EMPTY:				lMnMsr.mBasePr.empty[ch] = val;			CalPrc_ResetFlag(ch);	break;		
		case MnMS0_OPT_SINGLE_DEADZONE:				lMnMsr.mBasePr.deadzone[ch] = val;		CalPrc_ResetFlag(ch);	break;	
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		lMnMsr.mBasePr.measure_cycle[ch] = val;	 break;	
		case MnMS0_OPT_SINGLE_MEASURE_RESET:
			switch(MnLY3_GetValue())
			{
				case MENU_CHK_YES:					CalPrc_ResetFlag(ch); break;
				case MENU_CHK_NO:
				default:												  break;
			}
			break;
		default:								
			break;
	}	

	if(ch==APP_CH_1)
	{
		switch(iIt)
		{
			case MnMS0_OPT_SINGLE_UNIT:					MRM_WrByte(_mUNIT, lMnMsr.mBasePr.unit);								break;
			case MnMS0_OPT_SINGLE_OPERATION:			MRM_WrByte(_mCH1_OPERATION, lMnMsr.mBasePr.operation[APP_CH_1]);		break;
			case MnMS0_OPT_SINGLE_EMPTY:				MRM_WrWord(_mCH1_EMPTY_L, lMnMsr.mBasePr.empty[APP_CH_1]);				break;	
			case MnMS0_OPT_SINGLE_DEADZONE:				MRM_WrWord(_mCH1_DEADZONE_L, lMnMsr.mBasePr.deadzone[APP_CH_1]);		break;
			case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		MRM_WrByte(_mCH1_MSR_CYC, lMnMsr.mBasePr.measure_cycle[APP_CH_1]);		break;
			case MnMS0_OPT_SINGLE_MEASURE_RESET:		break;			
			default:								
				break;
		}	
	}
	else if(ch==APP_CH_2)
	{
		switch(iIt)
		{
			case MnMS0_OPT_SINGLE_UNIT:					MRM_WrByte(_mUNIT, lMnMsr.mBasePr.unit);								break;
			case MnMS0_OPT_SINGLE_OPERATION:			MRM_WrByte(_mCH2_OPERATION, lMnMsr.mBasePr.operation[APP_CH_2]);		break;
			case MnMS0_OPT_SINGLE_EMPTY:				MRM_WrWord(_mCH2_EMPTY_L, lMnMsr.mBasePr.empty[APP_CH_2]);				break;	
			case MnMS0_OPT_SINGLE_DEADZONE:				MRM_WrWord(_mCH2_DEADZONE_L, lMnMsr.mBasePr.deadzone[APP_CH_2]);		break;
			case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		MRM_WrByte(_mCH2_MSR_CYC, lMnMsr.mBasePr.measure_cycle[APP_CH_2]);		break;
			case MnMS0_OPT_SINGLE_MEASURE_RESET:		break;			
			default:								
				break;
		}	
	}

}



void MnMSR_CalSet_Value(U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnMS1_OPT_CH1_FREQ:			lMnMsr.mCalPr.freq[APP_CH_1] = val;				break;
		case MnMS1_OPT_CH1_ECHO_AMP:		lMnMsr.mCalPr.echo_amp[APP_CH_1] = val;			break;
		case MnMS1_OPT_CH1_THR_LIGHT:		lMnMsr.mCalPr.thr_light_mod[APP_CH_1] = val;	break;
		case MnMS1_OPT_CH1_THR_HEAVY:		lMnMsr.mCalPr.thr_heavy_mod[APP_CH_1] = val;	break;
		case MnMS1_OPT_CH1_ASF_HEAVY:		lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_HEAVY] = val;				 break;
		case MnMS1_OPT_CH1_ASF_LIGHT:		lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_LIGHT] = val;				 	break;
		case MnMS1_OPT_CH1_DAMPING:			lMnMsr.mCalPr.damp[APP_CH_1] = val;				break;
		case MnMS1_OPT_CH1_OFFSET:			lMnMsr.mCalPr.offset[APP_CH_1] = val;			break;
		case MnMS1_OPT_CH2_FREQ:			lMnMsr.mCalPr.freq[APP_CH_2] = val;				break;
		case MnMS1_OPT_CH2_ECHO_AMP:		lMnMsr.mCalPr.echo_amp[APP_CH_2] = val;			break;
		case MnMS1_OPT_CH2_THR_LIGHT:		lMnMsr.mCalPr.thr_light_mod[APP_CH_2] = val;	break;
		case MnMS1_OPT_CH2_THR_HEAVY:		lMnMsr.mCalPr.thr_heavy_mod[APP_CH_2] = val;	break;
		case MnMS1_OPT_CH2_ASF_HEAVY:		lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_HEAVY] = val;				 break;
		case MnMS1_OPT_CH2_ASF_LIGHT:		lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_LIGHT] = val;				 break;
		case MnMS1_OPT_CH2_DAMPING:			lMnMsr.mCalPr.damp[APP_CH_2] = val;				break;
		case MnMS1_OPT_CH2_OFFSET:			lMnMsr.mCalPr.offset[APP_CH_2] = val;			break;
		default:							break;
	}

	switch(iIt)
	{
		case MnMS1_OPT_CH1_FREQ:			MRM_WrByte(_mCH1_FREQ, lMnMsr.mCalPr.freq[APP_CH_1]);							break;
		case MnMS1_OPT_CH1_ECHO_AMP:		MRM_WrByte(_mCH1_ECHO_AMP, lMnMsr.mCalPr.echo_amp[APP_CH_1]);					break;
		case MnMS1_OPT_CH1_THR_LIGHT:		MRM_WrByte(_mCH1_THR_LIGHT_MODE, lMnMsr.mCalPr.thr_light_mod[APP_CH_1]);		break;
		case MnMS1_OPT_CH1_THR_HEAVY:		MRM_WrByte(_mCH1_THR_HEAVY_MODE, lMnMsr.mCalPr.thr_heavy_mod[APP_CH_1]);		break;
		case MnMS1_OPT_CH1_ASF_LIGHT:		MRM_WrWord(_mCH1_ASF_LIGHT_L, lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_LIGHT]);	break;
		case MnMS1_OPT_CH1_ASF_HEAVY:		MRM_WrWord(_mCH1_ASF_HEAVY_L, lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_HEAVY]);	break;		
		case MnMS1_OPT_CH1_DAMPING:			MRM_WrWord(_mCH1_DAMP_L, lMnMsr.mCalPr.damp[APP_CH_1]);							break;
		case MnMS1_OPT_CH1_OFFSET:			MRM_WrWord(_mCH1_OFFSET_L, lMnMsr.mCalPr.offset[APP_CH_1]);						break;
		case MnMS1_OPT_CH2_FREQ:			MRM_WrByte(_mCH2_FREQ, lMnMsr.mCalPr.freq[APP_CH_2]);							break;
		case MnMS1_OPT_CH2_ECHO_AMP:		MRM_WrByte(_mCH2_ECHO_AMP, lMnMsr.mCalPr.echo_amp[APP_CH_2]);					break;
		case MnMS1_OPT_CH2_THR_LIGHT:		MRM_WrByte(_mCH2_THR_LIGHT_MODE, lMnMsr.mCalPr.thr_light_mod[APP_CH_2]);		break;
		case MnMS1_OPT_CH2_THR_HEAVY:		MRM_WrByte(_mCH2_THR_HEAVY_MODE, lMnMsr.mCalPr.thr_heavy_mod[APP_CH_2]);		break;
		case MnMS1_OPT_CH2_ASF_LIGHT:		MRM_WrWord(_mCH2_ASF_LIGHT_L, lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_LIGHT]);	break;
		case MnMS1_OPT_CH2_ASF_HEAVY:		MRM_WrWord(_mCH2_ASF_HEAVY_L, lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_HEAVY]);	break;	
		case MnMS1_OPT_CH2_DAMPING:			MRM_WrWord(_mCH2_DAMP_L, lMnMsr.mCalPr.damp[APP_CH_2]);							break;
		case MnMS1_OPT_CH2_OFFSET:			MRM_WrWord(_mCH2_OFFSET_L, lMnMsr.mCalPr.offset[APP_CH_2]);						break;
		default:							break;
	}	
}

void MnMSR_CalSet_Ch_Value(U08 ch, U08 iIt, S32 val)
{
	switch(iIt)
	{
		case MnMS1_OPT_SINGLE_FREQ:			lMnMsr.mCalPr.freq[ch] = val;				 break;
		case MnMS1_OPT_SINGLE_ECHO_AMP:		lMnMsr.mCalPr.echo_amp[ch] = val;			 break;
		case MnMS1_OPT_SINGLE_THR_LIGHT:	lMnMsr.mCalPr.thr_light_mod[ch] = val;		break;
		case MnMS1_OPT_SINGLE_THR_HEAVY:	lMnMsr.mCalPr.thr_heavy_mod[ch] = val;		break;
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	lMnMsr.mCalPr.asf[ch][MsCAL_THR_LIGHT]= val; 		break;
		case MnMS1_OPT_SINGLE_ASF_HEAVY:	lMnMsr.mCalPr.asf[ch][MsCAL_THR_HEAVY]= val; 		break;		
		case MnMS1_OPT_SINGLE_DAMPING:		lMnMsr.mCalPr.damp[ch]			= val;		break;
		case MnMS1_OPT_SINGLE_OFFSET:		lMnMsr.mCalPr.offset[ch]		= val; 		break;
		default:							break;
	}

	switch(ch)
	{
		case APP_CH_1:
			switch(iIt)
			{
				case MnMS1_OPT_SINGLE_FREQ:			MRM_WrByte(_mCH1_FREQ, lMnMsr.mCalPr.freq[ch]);							break;
				case MnMS1_OPT_SINGLE_ECHO_AMP:		MRM_WrByte(_mCH1_ECHO_AMP, lMnMsr.mCalPr.echo_amp[ch]);					break;
				case MnMS1_OPT_SINGLE_THR_LIGHT:	MRM_WrByte(_mCH1_THR_LIGHT_MODE, lMnMsr.mCalPr.thr_light_mod[ch]);		break;
				case MnMS1_OPT_SINGLE_THR_HEAVY:	MRM_WrByte(_mCH1_THR_HEAVY_MODE, lMnMsr.mCalPr.thr_heavy_mod[ch]);		break;
				case MnMS1_OPT_SINGLE_ASF_LIGHT:	MRM_WrWord(_mCH1_ASF_LIGHT_L, lMnMsr.mCalPr.asf[ch][MsCAL_THR_LIGHT]);	break;
				case MnMS1_OPT_SINGLE_ASF_HEAVY:	MRM_WrWord(_mCH1_ASF_HEAVY_L, lMnMsr.mCalPr.asf[ch][MsCAL_THR_HEAVY]);	break;				
				case MnMS1_OPT_SINGLE_DAMPING:		MRM_WrWord(_mCH1_DAMP_L, lMnMsr.mCalPr.damp[ch]);						break;
				case MnMS1_OPT_SINGLE_OFFSET:		MRM_WrWord(_mCH1_OFFSET_L, lMnMsr.mCalPr.offset[ch]);					break;
				default:
					break;
			}
			break;
		case APP_CH_2:
			switch(iIt)
			{
				case MnMS1_OPT_SINGLE_FREQ: 		MRM_WrByte(_mCH2_FREQ, lMnMsr.mCalPr.freq[ch]); 						break;
				case MnMS1_OPT_SINGLE_ECHO_AMP: 	MRM_WrByte(_mCH2_ECHO_AMP, lMnMsr.mCalPr.echo_amp[ch]); 				break;
				case MnMS1_OPT_SINGLE_THR_LIGHT:	MRM_WrByte(_mCH2_THR_LIGHT_MODE, lMnMsr.mCalPr.thr_light_mod[ch]);		break;
				case MnMS1_OPT_SINGLE_THR_HEAVY:	MRM_WrByte(_mCH2_THR_HEAVY_MODE, lMnMsr.mCalPr.thr_heavy_mod[ch]);		break;
				case MnMS1_OPT_SINGLE_ASF_LIGHT:	MRM_WrWord(_mCH2_ASF_LIGHT_L, lMnMsr.mCalPr.asf[ch][MsCAL_THR_LIGHT]);	break;
				case MnMS1_OPT_SINGLE_ASF_HEAVY:	MRM_WrWord(_mCH2_ASF_HEAVY_L, lMnMsr.mCalPr.asf[ch][MsCAL_THR_HEAVY]);	break;
				case MnMS1_OPT_SINGLE_DAMPING:		MRM_WrWord(_mCH2_DAMP_L, lMnMsr.mCalPr.damp[ch]);						break;
				case MnMS1_OPT_SINGLE_OFFSET:		MRM_WrWord(_mCH2_OFFSET_L, lMnMsr.mCalPr.offset[ch]);					break;
				default:
					break;
			}
			break;
		default:	
			break;
	}
	
}




void MnMSR_Set_Threshold_Ch_Value(U08 ch,U08 sel, S32 val)
{
	switch(sel)
	{
		case MnMS1_OPT_SINGLE_THR_LIGHT:		lMnMsr.mCalPr.thr_val[ch][MsCAL_THR_LIGHT]  = val;	break;
		case MnMS1_OPT_SINGLE_THR_HEAVY:		lMnMsr.mCalPr.thr_val[ch][MsCAL_THR_HEAVY]  = val;	break;		
		default:								break;
	}

	switch(ch)
	{
		case APP_CH_1:
			switch(sel)
			{
				case MnMS1_OPT_SINGLE_THR_LIGHT:		MRM_WrWord(_mCH1_THR_LIGHT_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_LIGHT]);	break;
				case MnMS1_OPT_SINGLE_THR_HEAVY:		MRM_WrWord(_mCH1_THR_HEAVY_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_HEAVY]);	break;	
				default:								break;
			}			
			break;
		case APP_CH_2:
			switch(sel)
			{
				case MnMS1_OPT_SINGLE_THR_LIGHT:		MRM_WrWord(_mCH2_THR_LIGHT_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_LIGHT]);	break;
				case MnMS1_OPT_SINGLE_THR_HEAVY:		MRM_WrWord(_mCH2_THR_HEAVY_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_HEAVY]);	break;	
				default:								break;
			}			
			break;			
		default:			break;
	}

	CalPrc_Threshold_Value(ch);
}

void MnMSR_Set_Threshold_Value(U08 sel, S32 val)
{
	switch(sel)
	{
		case MnMS1_OPT_CH1_THR_LIGHT:		lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_LIGHT]  = val;	break;
		case MnMS1_OPT_CH1_THR_HEAVY:		lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_HEAVY]  = val;	break;	
		case MnMS1_OPT_CH2_THR_LIGHT:		lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_LIGHT]  = val;	break;
		case MnMS1_OPT_CH2_THR_HEAVY:		lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_HEAVY]  = val;	break;	
		default:							break;
	}

	switch(sel)
	{
		case MnMS1_OPT_CH1_THR_LIGHT:		MRM_WrWord(_mCH1_THR_LIGHT_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_LIGHT]);	break;
		case MnMS1_OPT_CH1_THR_HEAVY:		MRM_WrWord(_mCH1_THR_HEAVY_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_HEAVY]);	break;
		case MnMS1_OPT_CH2_THR_LIGHT:		MRM_WrWord(_mCH2_THR_LIGHT_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_LIGHT]);	break;
		case MnMS1_OPT_CH2_THR_HEAVY:		MRM_WrWord(_mCH2_THR_HEAVY_VAL_L, lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_HEAVY]);	break;
		default:							break;
	}

	switch(sel)
	{
		case MnMS1_OPT_CH1_THR_LIGHT:		break;
		case MnMS1_OPT_CH1_THR_HEAVY:		CalPrc_Threshold_Value(APP_CH_1);	break;	
		case MnMS1_OPT_CH2_THR_LIGHT:		break;
		case MnMS1_OPT_CH2_THR_HEAVY:		CalPrc_Threshold_Value(APP_CH_2);	break;	
		default:							break;
	}

}
#if 0
void MnMSR_PrSet_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{	// Page #0
		case MnMSR_I00_CPT_CYC:		lMnMsr.mPr.cpt_cyc   = val;		break;
		case MnMSR_I01_CPT_TYP:		lMnMsr.mPr.cpt_mtd   = val;		break;
		case MnMSR_I02_REFILT:		lMnMsr.mPr.re_ftr    = val;		break;
		case MnMSR_I03_PRM_RST:										break;
		case MnMSR_I04_fMSR_EN:		lMnMsr.mPr.fRun	     = val;		break;
		default:													break;
	}

	switch(iIt)
	{	// Page #0
		case MnMSR_I00_CPT_CYC:		MRM_WrWord(_mMnMSR_CH0_THR_MOD, lMnMsr.mPr.cpt_cyc);		break;
		case MnMSR_I03_PRM_RST:		break;
		case MnMSR_I04_fMSR_EN:		MRM_WrByte(_mMnMSR_fEN, lMnMsr.mPr.fRun);				break;
		// Not Yet
		case MnMSR_I01_CPT_TYP:		MRM_WrWord(_mMnMSR_CPT_MTD_L, lMnMsr.mPr.cpt_mtd);		break;
		case MnMSR_I02_REFILT:		MRM_WrWord(_mMnMSR_RE_FTR_L, lMnMsr.mPr.re_ftr);		break;
		default:					break;
	}
}
#endif

void MnMSR_PrRst_Factory(void)
{	
	// Sub-Seciton #0 (Base)
	MRM_WrByte(_mUNIT,	MnMS0_UNIT_DEF);
	MRM_WrByte(_mCH1_OPERATION,	MnMS0_OPERATION_DEF);
	MRM_WrByte(_mCH2_OPERATION,	MnMS0_OPERATION_DEF);
	MRM_WrWord(_mCH1_EMPTY_L,   MnMS0_EMPTY_DEF);
	MRM_WrWord(_mCH2_EMPTY_L,   MnMS0_EMPTY_DEF);	
	MRM_WrWord(_mCH1_DEADZONE_L,   MnMS0_DEADZONE_DEF);
	MRM_WrWord(_mCH2_DEADZONE_L,   MnMS0_DEADZONE_DEF);
	MRM_WrByte(_mCH1_MSR_CYC,	MnMS0_MSR_CYC_DEF);
	MRM_WrByte(_mCH2_MSR_CYC,	MnMS0_MSR_CYC_DEF);


	// Sub-Section (Calibration)
	MRM_WrByte(_mCH1_FREQ,	MnMS1_FREQ_DEF);
	MRM_WrByte(_mCH2_FREQ,	MnMS1_FREQ_DEF);	
	MRM_WrByte(_mCH1_ECHO_AMP,	MnMS1_ECHO_AMP_DEF);
	MRM_WrByte(_mCH2_ECHO_AMP,	MnMS1_ECHO_AMP_DEF);	
	MRM_WrByte(_mCH1_THR_HEAVY_MODE,	MnMS1_THRESHOLD_DEF);
	MRM_WrByte(_mCH2_THR_HEAVY_MODE,	MnMS1_THRESHOLD_DEF);		
	MRM_WrByte(_mCH1_THR_LIGHT_MODE,	MnMS1_THRESHOLD_DEF);
	MRM_WrByte(_mCH2_THR_LIGHT_MODE,	MnMS1_THRESHOLD_DEF);		
	MRM_WrWord(_mCH1_ASF_LIGHT_L,	MnMS1_ASF_DEF);
	MRM_WrWord(_mCH2_ASF_LIGHT_L,	MnMS1_ASF_DEF);	
	MRM_WrWord(_mCH1_ASF_HEAVY_L,	MnMS1_ASF_DEF);
	MRM_WrWord(_mCH2_ASF_HEAVY_L,	MnMS1_ASF_DEF);		
	MRM_WrWord(_mCH1_DAMP_L,	MnMS1_DAMPING_DEF);
	MRM_WrWord(_mCH2_DAMP_L,	MnMS1_DAMPING_DEF);	
	MRM_WrWord(_mCH1_OFFSET_L,	MnMS1_OFFSET_DEF);
	MRM_WrWord(_mCH2_OFFSET_L,	MnMS1_OFFSET_DEF);		

	MRM_WrWord(_mCH1_THR_LIGHT_VAL_L,	MnMS1_THR_VAL_AUTO_DEF);	
	MRM_WrWord(_mCH1_THR_HEAVY_VAL_L,	MnMS1_THR_VAL_AUTO_DEF);	
	MRM_WrWord(_mCH2_THR_LIGHT_VAL_L,	MnMS1_THR_VAL_AUTO_DEF);	
	MRM_WrWord(_mCH2_THR_HEAVY_VAL_L,	MnMS1_THR_VAL_AUTO_DEF);	
}	


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnMSR_GetLayer(void)			{	return lMnMsr.lyr;		}
// Set
void MnMSR_SetLayer(U08 lyr)		{	lMnMsr.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnMSR_PrInitMain(void)
{
	// Read Parameters
	lMnMsr.mBasePr.unit	= MRM_RdByte(_mUNIT);
	lMnMsr.mBasePr.operation[APP_CH_1]	= MRM_RdByte(_mCH1_OPERATION);
	lMnMsr.mBasePr.operation[APP_CH_2]	= MRM_RdByte(_mCH2_OPERATION);
	lMnMsr.mBasePr.empty[APP_CH_1]	= MRM_RdWord(_mCH1_EMPTY_L);
	lMnMsr.mBasePr.empty[APP_CH_2]	= MRM_RdWord(_mCH2_EMPTY_L);
	lMnMsr.mBasePr.deadzone[APP_CH_1]	= MRM_RdWord(_mCH1_DEADZONE_L);
	lMnMsr.mBasePr.deadzone[APP_CH_2]	= MRM_RdWord(_mCH2_DEADZONE_L);
	lMnMsr.mBasePr.measure_cycle[APP_CH_1]	= MRM_RdByte(_mCH1_MSR_CYC);
	lMnMsr.mBasePr.measure_cycle[APP_CH_2]	= MRM_RdByte(_mCH2_MSR_CYC);

	if(lMnMsr.mBasePr.unit	> MnMS0_UNIT_MAX)							lMnMsr.mBasePr.unit = MnMS0_UNIT_DEF;
	if(lMnMsr.mBasePr.operation[APP_CH_1]	> MnMS0_OPERATION_MAX)		lMnMsr.mBasePr.operation[APP_CH_1] = MnMS0_OPERATION_DEF;
	if(lMnMsr.mBasePr.operation[APP_CH_2]	> MnMS0_OPERATION_MAX)		lMnMsr.mBasePr.operation[APP_CH_2] = MnMS0_OPERATION_DEF;
	if(lMnMsr.mBasePr.empty[APP_CH_1]		> MnMS0_EMPTY_MAX)			lMnMsr.mBasePr.empty[APP_CH_1] = MnMS0_EMPTY_DEF;
	if(lMnMsr.mBasePr.empty[APP_CH_2]		> MnMS0_EMPTY_MAX)			lMnMsr.mBasePr.empty[APP_CH_2] = MnMS0_EMPTY_DEF;
	if(lMnMsr.mBasePr.deadzone[APP_CH_1]	> MnMS0_DEADZONE_MAX)		lMnMsr.mBasePr.deadzone[APP_CH_1] = MnMS0_DEADZONE_DEF;
	if(lMnMsr.mBasePr.deadzone[APP_CH_2]	> MnMS0_DEADZONE_MAX)		lMnMsr.mBasePr.deadzone[APP_CH_2] = MnMS0_DEADZONE_DEF;
	if(lMnMsr.mBasePr.measure_cycle[APP_CH_1]	> MnMS0_MSR_CYC_MAX)	lMnMsr.mBasePr.measure_cycle[APP_CH_1] = MnMS0_MSR_CYC_DEF;
	if(lMnMsr.mBasePr.measure_cycle[APP_CH_2]	> MnMS0_MSR_CYC_MAX)	lMnMsr.mBasePr.measure_cycle[APP_CH_2] = MnMS0_MSR_CYC_DEF;

	lMnMsr.mCalPr.freq[APP_CH_1]			= MRM_RdByte(_mCH1_FREQ);
	lMnMsr.mCalPr.freq[APP_CH_2]			= MRM_RdByte(_mCH2_FREQ);
	lMnMsr.mCalPr.echo_amp[APP_CH_1]		= MRM_RdByte(_mCH1_ECHO_AMP);
	lMnMsr.mCalPr.echo_amp[APP_CH_2]		= MRM_RdByte(_mCH2_ECHO_AMP);	
	lMnMsr.mCalPr.thr_heavy_mod[APP_CH_1]	= MRM_RdByte(_mCH1_THR_HEAVY_MODE);
	lMnMsr.mCalPr.thr_heavy_mod[APP_CH_2]	= MRM_RdByte(_mCH2_THR_HEAVY_MODE);
	lMnMsr.mCalPr.thr_light_mod[APP_CH_1]	= MRM_RdByte(_mCH1_THR_LIGHT_MODE);
	lMnMsr.mCalPr.thr_light_mod[APP_CH_2]	= MRM_RdByte(_mCH2_THR_LIGHT_MODE);
	lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_LIGHT]				= MRM_RdWord(_mCH1_ASF_LIGHT_L);
	lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_LIGHT]				= MRM_RdWord(_mCH2_ASF_LIGHT_L);
	lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_HEAVY]				= MRM_RdWord(_mCH1_ASF_HEAVY_L);
	lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_HEAVY]				= MRM_RdWord(_mCH2_ASF_HEAVY_L);	
	lMnMsr.mCalPr.damp[APP_CH_1]			= MRM_RdWord(_mCH1_DAMP_L);
	lMnMsr.mCalPr.damp[APP_CH_2]			= MRM_RdWord(_mCH2_DAMP_L);
	lMnMsr.mCalPr.offset[APP_CH_1]			= MRM_RdWord(_mCH1_OFFSET_L);
	lMnMsr.mCalPr.offset[APP_CH_2]			= MRM_RdWord(_mCH2_OFFSET_L);
	
	lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_LIGHT] 		= MRM_RdWord(_mCH1_THR_LIGHT_VAL_L);
	lMnMsr.mCalPr.thr_val[APP_CH_1][MsCAL_THR_HEAVY] 		= MRM_RdWord(_mCH1_THR_HEAVY_VAL_L);
	lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_LIGHT] 		= MRM_RdWord(_mCH2_THR_LIGHT_VAL_L);
	lMnMsr.mCalPr.thr_val[APP_CH_2][MsCAL_THR_HEAVY] 		= MRM_RdWord(_mCH2_THR_HEAVY_VAL_L);

	if(lMnMsr.mCalPr.freq[APP_CH_1]	> MnMS1_FREQ_MAX)				lMnMsr.mCalPr.freq[APP_CH_1] = MnMS1_FREQ_DEF;
	if(lMnMsr.mCalPr.freq[APP_CH_2]	> MnMS1_FREQ_MAX)				lMnMsr.mCalPr.freq[APP_CH_2] = MnMS1_FREQ_DEF;
	
	if(lMnMsr.mCalPr.echo_amp[APP_CH_1]	> MnMS1_ECHO_AMP_MAX)			lMnMsr.mCalPr.echo_amp[APP_CH_1] = MnMS1_ECHO_AMP_DEF;
	if(lMnMsr.mCalPr.echo_amp[APP_CH_2]	> MnMS1_ECHO_AMP_MAX)			lMnMsr.mCalPr.echo_amp[APP_CH_2] = MnMS1_ECHO_AMP_DEF;
	
	if(lMnMsr.mCalPr.thr_heavy_mod[APP_CH_1]	> MnMS1_THRESHOLD_MAX)		lMnMsr.mCalPr.thr_heavy_mod[APP_CH_1] = MnMS1_THRESHOLD_DEF;
	if(lMnMsr.mCalPr.thr_heavy_mod[APP_CH_2]	> MnMS1_THRESHOLD_MAX)		lMnMsr.mCalPr.thr_heavy_mod[APP_CH_2] = MnMS1_THRESHOLD_DEF;
	if(lMnMsr.mCalPr.thr_light_mod[APP_CH_1]	> MnMS1_THRESHOLD_MAX)		lMnMsr.mCalPr.thr_light_mod[APP_CH_1] = MnMS1_THRESHOLD_DEF;
	if(lMnMsr.mCalPr.thr_light_mod[APP_CH_2]	> MnMS1_THRESHOLD_MAX)		lMnMsr.mCalPr.thr_light_mod[APP_CH_2] = MnMS1_THRESHOLD_DEF;
	
	if(lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_LIGHT]	> MnMS1_ASF_MAX)		lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_LIGHT] = MnMS1_ASF_DEF;
	if(lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_LIGHT]	> MnMS1_ASF_MAX)		lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_LIGHT] = MnMS1_ASF_DEF;
	if(lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_HEAVY]	> MnMS1_ASF_MAX)		lMnMsr.mCalPr.asf[APP_CH_1][MsCAL_THR_HEAVY] = MnMS1_ASF_DEF;
	if(lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_HEAVY]	> MnMS1_ASF_MAX)		lMnMsr.mCalPr.asf[APP_CH_2][MsCAL_THR_HEAVY] = MnMS1_ASF_DEF;	
	
	if(lMnMsr.mCalPr.damp[APP_CH_1]	> MnMS1_DAMPING_MAX)				lMnMsr.mCalPr.damp[APP_CH_1] = MnMS1_DAMPING_DEF;
	if(lMnMsr.mCalPr.damp[APP_CH_2]	> MnMS1_DAMPING_MAX)				lMnMsr.mCalPr.damp[APP_CH_2] = MnMS1_DAMPING_DEF;
	
	if(lMnMsr.mCalPr.offset[APP_CH_1]	> MnMS1_OFFSET_MAX)			lMnMsr.mCalPr.offset[APP_CH_1] = MnMS1_OFFSET_DEF;
	if(lMnMsr.mCalPr.offset[APP_CH_2]	> MnMS1_OFFSET_MAX)			lMnMsr.mCalPr.offset[APP_CH_2] = MnMS1_OFFSET_DEF;
	if(lMnMsr.mCalPr.offset[APP_CH_1]	< MnMS1_OFFSET_MIN)			lMnMsr.mCalPr.offset[APP_CH_1] = MnMS1_OFFSET_DEF;
	if(lMnMsr.mCalPr.offset[APP_CH_2]	< MnMS1_OFFSET_MIN)			lMnMsr.mCalPr.offset[APP_CH_2] = MnMS1_OFFSET_DEF;

	for(U08 i = 0; i<APP_CH_NUM; i++)
	{
		switch(lMnMsr.mCalPr.thr_light_mod[i])
		{
			case MnMS1_THRESHOLD_AUTO:		
				if(lMnMsr.mCalPr.thr_val[i][MsCAL_THR_LIGHT] > MnMS1_THR_VAL_AUTO_MAX)	
				lMnMsr.mCalPr.thr_val[i][MsCAL_THR_LIGHT]= MnMS1_THR_VAL_AUTO_DEF;
				break;
			case MnMS1_THRESHOLD_MANUAL:
				if(lMnMsr.mCalPr.thr_val[i][MsCAL_THR_LIGHT] > MnMS1_THR_VAL_MANUAL_MAX)	
				lMnMsr.mCalPr.thr_val[i][MsCAL_THR_LIGHT]= MnMS1_THR_VAL_MANUAL_DEF;
				break;			
			default:						break;
		}
		
		switch(lMnMsr.mCalPr.thr_heavy_mod[i])
		{
			case MnMS1_THRESHOLD_AUTO:		
				if(lMnMsr.mCalPr.thr_val[i][MsCAL_THR_HEAVY] > MnMS1_THR_VAL_AUTO_MAX)	
				lMnMsr.mCalPr.thr_val[i][MsCAL_THR_HEAVY]= MnMS1_THR_VAL_AUTO_DEF;
				break;
			case MnMS1_THRESHOLD_MANUAL:
				if(lMnMsr.mCalPr.thr_val[i][MsCAL_THR_HEAVY] > MnMS1_THR_VAL_MANUAL_MAX)	
				lMnMsr.mCalPr.thr_val[i][MsCAL_THR_HEAVY]= MnMS1_THR_VAL_MANUAL_DEF;
				break;			
			default:						break;
		}
	}
	
}

void MnMSR_InitMain(void)
{
	lMnMsr.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnMSR_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

