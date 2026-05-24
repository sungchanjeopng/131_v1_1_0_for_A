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
// app
#include "app_main.h"
// input
#include "input_main.h"
#include "input_key.h"
// display
#include "disp_string.h"
// disp - menu
#include "dp_menu_main.h"
#include "dp_menu_measure.h"
#include "dp_menu_output.h"
#include "dp_menu_data.h"
#include "dp_menu_system.h"
#include "dp_menu_engineer.h"
#include "dp_menu_factory.h"
// screen
#include "screen_main.h"
// menu - section
#include "menu_main.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_data.h"
#include "menu_system.h"
#include "menu_engineer.h"
#include "menu_factory.h"
#include "menu_test.h"
// menu - layer
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
// self
#include "menu_lyr3_value.h"
// function
#include "output_relay.h"
#include "output_current.h"
#include "output_pcd.h"
#include "disp_titlebar.h"
#include "disp_color.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnLY3_LS lMnLy3;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Intro (Section)
//------------------------------------------------------------------------------------------------------------------------------
void MnL3Itr_Sc0Meas(U08 iSb, U08 iIt)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iSb)
		{
			case MnMSR_SUB_BASE:		
				lMnLy3.val = MnMSR_BaseGet_Value(iIt);
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnMS0_OPT_UNIT: 					lMnLy3.min = MnMS0_UNIT_MIN;		lMnLy3.max = MnMS0_UNIT_MAX;			break;
					case MnMS0_OPT_CH1_OPERATION: 			
					case MnMS0_OPT_CH2_OPERATION:			lMnLy3.min = MnMS0_OPERATION_MIN;	lMnLy3.max = MnMS0_OPERATION_MAX;		break;
					case MnMS0_OPT_CH1_EMPTY:				
					case MnMS0_OPT_CH2_EMPTY:				lMnLy3.min = MnMS0_EMPTY_MIN;		lMnLy3.max = MnMS0_EMPTY_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS0_OPT_CH1_DEADZONE: 			
					case MnMS0_OPT_CH2_DEADZONE:			lMnLy3.min = MnMS0_DEADZONE_MIN;	lMnLy3.max = MnMS0_DEADZONE_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS0_OPT_CH1_MEASURE_CYCLE: 		
					case MnMS0_OPT_CH2_MEASURE_CYCLE:		lMnLy3.min = MnMS0_MSR_CYC_MIN;		lMnLy3.max = MnMS0_MSR_CYC_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS0_OPT_CH1_MEASURE_RESET:		
					case MnMS0_OPT_CH2_MEASURE_RESET:		lMnLy3.min = MnMS0_MSR_RESET_MIN;	lMnLy3.max = MnMS0_MSR_RESET_MAX;		break;			
					default:																											break;
				}
				break;
			case MnMSR_SUB_CAL:		
				lMnLy3.val = MnMSR_CalGet_Value(iIt);
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnMS1_OPT_CH1_FREQ:			
					case MnMS1_OPT_CH2_FREQ:				lMnLy3.min = MnMS1_FREQ_MIN;		lMnLy3.max = MnMS1_FREQ_MAX;			break;
					case MnMS1_OPT_CH1_ECHO_AMP:
					case MnMS1_OPT_CH2_ECHO_AMP:			lMnLy3.min = MnMS1_ECHO_AMP_MIN;	lMnLy3.max = MnMS1_ECHO_AMP_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS1_OPT_CH1_THR_HEAVY:
					case MnMS1_OPT_CH2_THR_HEAVY:
					case MnMS1_OPT_CH1_THR_LIGHT:
					case MnMS1_OPT_CH2_THR_LIGHT:			lMnLy3.min = MnMS1_THRESHOLD_MIN;	lMnLy3.max = MnMS1_THRESHOLD_MAX;		break;
					case MnMS1_OPT_CH1_ASF_LIGHT:
					case MnMS1_OPT_CH1_ASF_HEAVY:					
					case MnMS1_OPT_CH2_ASF_LIGHT:
					case MnMS1_OPT_CH2_ASF_HEAVY:			lMnLy3.min = MnMS1_ASF_MIN;			lMnLy3.max = MnMS1_ASF_MAX;				lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS1_OPT_CH1_DAMPING:
					case MnMS1_OPT_CH2_DAMPING:				lMnLy3.min = MnMS1_DAMPING_MIN;		lMnLy3.max = MnMS1_DAMPING_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS1_OPT_CH1_OFFSET:
					case MnMS1_OPT_CH2_OFFSET:				lMnLy3.min = MnMS1_OFFSET_MIN;		lMnLy3.max = MnMS1_OFFSET_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				}
				break;
			default:										lMnLy3.val = MENU_VAL_INVALID;				break;
		}	
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iSb)
		{
			case MnMSR_SUB_BASE:		
				lMnLy3.val = MnMSR_BaseGet_Ch_Value(APP_CH_1,iIt);
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnMS0_OPT_SINGLE_UNIT: 				lMnLy3.min = MnMS0_UNIT_MIN;		lMnLy3.max = MnMS0_UNIT_MAX;			break;			
					case MnMS0_OPT_SINGLE_OPERATION:			lMnLy3.min = MnMS0_OPERATION_MIN;	lMnLy3.max = MnMS0_OPERATION_MAX;		break;		
					case MnMS0_OPT_SINGLE_EMPTY:				lMnLy3.min = MnMS0_EMPTY_MIN;		lMnLy3.max = MnMS0_EMPTY_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;		
					case MnMS0_OPT_SINGLE_DEADZONE:				lMnLy3.min = MnMS0_DEADZONE_MIN;	lMnLy3.max = MnMS0_DEADZONE_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break; 		
					case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		lMnLy3.min = MnMS0_MSR_CYC_MIN;		lMnLy3.max = MnMS0_MSR_CYC_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS0_OPT_SINGLE_MEASURE_RESET:		lMnLy3.min = MnMS0_MSR_RESET_MIN;	lMnLy3.max = MnMS0_MSR_RESET_MAX;		break;			
					default:																												break;
				}
				break;
			case MnMSR_SUB_CAL:		
				lMnLy3.val = MnMSR_CalGet_Ch_Value(APP_CH_1,iIt);
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{		
					case MnMS1_OPT_SINGLE_FREQ:					lMnLy3.min = MnMS1_FREQ_MIN;		lMnLy3.max = MnMS1_FREQ_MAX;			break;
					case MnMS1_OPT_SINGLE_ECHO_AMP:				lMnLy3.min = MnMS1_ECHO_AMP_MIN;	lMnLy3.max = MnMS1_ECHO_AMP_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS1_OPT_SINGLE_THR_HEAVY:
					case MnMS1_OPT_SINGLE_THR_LIGHT:			lMnLy3.min = MnMS1_THRESHOLD_MIN;	lMnLy3.max = MnMS1_THRESHOLD_MAX;		break;					
					case MnMS1_OPT_SINGLE_ASF_LIGHT:
					case MnMS1_OPT_SINGLE_ASF_HEAVY:			lMnLy3.min = MnMS1_ASF_MIN;			lMnLy3.max = MnMS1_ASF_MAX;				lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS1_OPT_SINGLE_DAMPING:				lMnLy3.min = MnMS1_DAMPING_MIN;		lMnLy3.max = MnMS1_DAMPING_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnMS1_OPT_SINGLE_OFFSET:				lMnLy3.min = MnMS1_OFFSET_MIN;		lMnLy3.max = MnMS1_OFFSET_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				}
				break;
			default:										lMnLy3.val = MENU_VAL_INVALID;				break;
		}			
	}
}

void MnL3Itr_Sc1Outp(U08 iSb, U08 iIt)
{
	switch(iSb)
	{
		case MnOUT_SUB_CURRENT:		
			if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
			{
				lMnLy3.val = MnOUT_CurPrGet_Value(iIt);		
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnOS0_OPT_CH1_ASSIGN:		
					case MnOS0_OPT_CH2_ASSIGN:		lMnLy3.min = MnOS0_ASSIGN_MIN;	lMnLy3.max = MnOS0_ASSIGN_MAX;		break;
					case MnOS0_OPT_CH1_SET_04mA:	
					case MnOS0_OPT_CH2_SET_04mA:
					case MnOS0_OPT_CH1_SET_20mA:
					case MnOS0_OPT_CH2_SET_20mA:	lMnLy3.min = MnOS0_SET_MA_MIN;	lMnLy3.max = MnOS0_SET_MA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnOS0_OPT_CH1_TRM_12mA:
					case MnOS0_OPT_CH1_TRM_20mA:	lMnLy3.min = MnOS0_TRIM_MIN;	lMnLy3.max = MnOS0_TRIM_MAX;		
													lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	OuCUR_SetOutp_Type(MnOUT_CH_0, OuCUR_TYPE_CHK);	break;
					case MnOS0_OPT_CH1_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_0, OuCUR_TYPE_CHK);						break;
					case MnOS0_OPT_CH2_TRM_12mA:
					case MnOS0_OPT_CH2_TRM_20mA:	lMnLy3.min = MnOS0_TRIM_MIN;	lMnLy3.max = MnOS0_TRIM_MAX;		
													lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	OuCUR_SetOutp_Type(MnOUT_CH_1, OuCUR_TYPE_CHK);	break;
					case MnOS0_OPT_CH2_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_1, OuCUR_TYPE_CHK);						break;
					default:																							break;
				}
			}
			else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
			{
				lMnLy3.val = MnOUT_CurPrGet_CH_Value(APP_CH_1,iIt);		
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;	
				switch(iIt)
				{
					case MnOS0_OPT_SINGLE_ASSIGN:	lMnLy3.min = MnOS0_ASSIGN_MIN;	lMnLy3.max = MnOS0_ASSIGN_MAX;		break;
					case MnOS0_OPT_SINGLE_SET_04mA:
					case MnOS0_OPT_SINGLE_SET_20mA:	lMnLy3.min = MnOS0_SET_MA_MIN;	lMnLy3.max = MnOS0_SET_MA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
					case MnOS0_OPT_SINGLE_TRM_12mA:
					case MnOS0_OPT_SINGLE_TRM_20mA:	lMnLy3.min = MnOS0_TRIM_MIN;	lMnLy3.max = MnOS0_TRIM_MAX;	
													lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	OuCUR_SetOutp_Type(MnOUT_CH_0, OuCUR_TYPE_CHK);	break;					
					case MnOS0_OPT_SINGLE_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_0, OuCUR_TYPE_CHK);						break;
				}
			}
			break;
		case MnOUT_SUB_RELAY:	
			lMnLy3.val = MnOUT_RlyPrGet_Value(iIt);
			if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
			switch(iIt)
			{
				case MnOS1_OPT_ASSIGN:	
					lMnLy3.min = MnOS1_ASSIGN_MIN; 	
					lMnLy3.max = MnOS1_ASSIGN_MAX;	
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
						lMnLy3.max = MnOS1_ASSIGN_CH1_HEAVY;	
					break;
				case MnOS1_OPT_ACT:			lMnLy3.min = MnOS1_ACT_MIN;		lMnLy3.max = MnOS1_ACT_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				case MnOS1_OPT_STOP:		lMnLy3.min = MnOS1_STOP_MIN;	lMnLy3.max = MnOS1_STOP_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				case MnOS1_OPT_TEST:		lMnLy3.min = MnOS1_TEST_MIN;	lMnLy3.max = MnOS1_TEST_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				default:																						break;
			}
			break;
		case MnOUT_SUB_CLEAN:			
			lMnLy3.val = MnOUT_PcdPrGet_Value(iIt);
			if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
			switch(iIt)
			{
				case MnOS2_OPT_MODE:		lMnLy3.min = MnOS2_MODE_MIN;	lMnLy3.max = MnOS2_MODE_MAX;		break;
				case MnOS2_OPT_INTV:		lMnLy3.min = MnOS2_INTV_MIN;	lMnLy3.max = MnOS2_INTV_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				case MnOS2_OPT_TERM:		lMnLy3.min = MnOS2_TERM_MIN;	lMnLy3.max = MnOS2_TERM_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				default:																						break;
			}
			break;
		case MnOUT_SUB_ERROR:		
			lMnLy3.val = MnOUT_ErrPrGet_Value(iIt);	
			if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
			switch(iIt)
			{
				case MnOS3_OPT_ERR_DELAY:	lMnLy3.min = MnOS3_ERR_DELAY_MIN;		lMnLy3.max = MnOS3_ERR_DELAY_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
				case MnOS3_OPT_ERR_OUTP:	lMnLy3.min = MnOS3_ERR_OUTPUT_MIN;		lMnLy3.max = MnOS3_ERR_OUTPUT_MAX;			break;
				default:																										break;
			}
			break;
		default:					lMnLy3.val = MENU_VAL_INVALID;				break;
	}	
}

void MnL3Itr_Sc2Data(U08 iSb, U08 iIt)
{
	switch(iSb)
	{
		case MnDAT_SUB_SAVE:		lMnLy3.val = MnDAT_SavPrGet_Value(iIt);		break;
		case MnDAT_SUB_COMM:		lMnLy3.val = MnDAT_ComPrGet_Value(iIt);		break;
		default:					lMnLy3.val = MENU_VAL_INVALID;				break;
	}	
}

void MnL3Itr_Sc3Syst(U08 iSb, U08 iIt)
{
	RTC_TM rtc;

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iSb)
		{
			case MnSYS_SUB_BASE:
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnSYS_OPT_PASSCODE:		
						lMnLy3.min = MnSYS_PASSCODE_MIN;		
						lMnLy3.max = MnSYS_PASSCODE_MAX;			
						lMnLy3.val = MnSYS_PrGetBase_Item(iIt);
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG; 		
						break;
					case MnSYS_OPT_LANG:			
						lMnLy3.min = MnSYS_LANG_MIN;			
						lMnLy3.max = MnSYS_LANG_MAX;		
						lMnLy3.val = MnSYS_PrGetBase_Item(iIt);
						break;
					case MnSYS_OPT_TIME:
						rtc = MnSYS_PrGet_Rtc();
						lMnLy3.time[MnSYS_T00_YY] = rtc.year;
						lMnLy3.time[MnSYS_T01_MM] = rtc.month;
						lMnLy3.time[MnSYS_T02_DD] = rtc.day;
						lMnLy3.time[MnSYS_T03_HH] = rtc.hours;
						lMnLy3.time[MnSYS_T04_MN] = rtc.minutes;		
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
						break;
					case MnSYS_OPT_RTN_TIM: 		
						lMnLy3.min = MnSYS_RTN_TIM_MIN; 		
						lMnLy3.max = MnSYS_RTN_TIM_MAX; 		
						lMnLy3.val = MnSYS_PrGetBase_Item(iIt); 
						break;
					case MnSYS_OPT_CH1_SITE_NAME:		
						lMnLy3.val = MnSYS_PrGet_site_name(APP_CH_1);
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
						break;
					case MnSYS_OPT_CH2_SITE_NAME:	
						lMnLy3.val = MnSYS_PrGet_site_name(APP_CH_2);		
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
						break;
					case MnSYS_OPT_FTR_RST: 		
						lMnLy3.val = MENU_CHK_NO;				
						break;
					// Not Yet
					default:						
						lMnLy3.val = MENU_VAL_INVALID;			
						break;
				}
				break;
			case MnSYS_SUB_ALARM:
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnSYS_OPT_ALARM_TIMER:		
						lMnLy3.min = MnSYS_ALARM_TIMER_MIN;		
						lMnLy3.max = MnSYS_ALARM_TIMER_MAX;			
						lMnLy3.val = MnSYS_PrGetAlarm_Item(iIt);		
						break;
					case MnSYS_OPT_ALARM_RESET:			
						lMnLy3.min = MnSYS_ALARM_RESET_MIN;			
						lMnLy3.max = MnSYS_ALARM_RESET_MAX;		
						lMnLy3.val = MnSYS_PrGetAlarm_Item(iIt);
						break;
				}
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iSb)
		{
			case MnSYS_SUB_BASE:
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnSYS_OPT_SINGLE_PASSCODE:		
						lMnLy3.min = MnSYS_PASSCODE_MIN;		
						lMnLy3.max = MnSYS_PASSCODE_MAX;			
						lMnLy3.val = MnSYS_PrGetBase_Item(iIt);
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG; 		
						break;
					case MnSYS_OPT_SINGLE_LANG:			
						lMnLy3.min = MnSYS_LANG_MIN;			
						lMnLy3.max = MnSYS_LANG_MAX;		
						lMnLy3.val = MnSYS_PrGetBase_Item(iIt);
						break;
					case MnSYS_OPT_SINGLE_TIME:
						rtc = MnSYS_PrGet_Rtc();
						lMnLy3.time[MnSYS_T00_YY] = rtc.year;
						lMnLy3.time[MnSYS_T01_MM] = rtc.month;
						lMnLy3.time[MnSYS_T02_DD] = rtc.day;
						lMnLy3.time[MnSYS_T03_HH] = rtc.hours;
						lMnLy3.time[MnSYS_T04_MN] = rtc.minutes;		
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
						break;
					case MnSYS_OPT_SINGLE_RTN_TIM: 		
						lMnLy3.min = MnSYS_RTN_TIM_MIN; 		
						lMnLy3.max = MnSYS_RTN_TIM_MAX; 		
						lMnLy3.val = MnSYS_PrGetBase_Item(iIt); 
						break;
					case MnSYS_OPT_SINGLE_SITE_NAME:		
						lMnLy3.val = MnSYS_PrGet_site_name(APP_CH_1);
						lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
						break;
					case MnSYS_OPT_SINGLE_FTR_RST: 		
						lMnLy3.val = MENU_CHK_NO;				
						break;
					// Not Yet
					default:						
						lMnLy3.val = MENU_VAL_INVALID;			
						break;
				}
				break;
			case MnSYS_SUB_ALARM:
				if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
				switch(iIt)
				{
					case MnSYS_OPT_ALARM_TIMER: 	
						lMnLy3.min = MnSYS_ALARM_TIMER_MIN; 	
						lMnLy3.max = MnSYS_ALARM_TIMER_MAX; 		
						lMnLy3.val = MnSYS_PrGetAlarm_Item(iIt);		
						break;
					case MnSYS_OPT_ALARM_RESET: 		
						lMnLy3.min = MnSYS_ALARM_RESET_MIN; 		
						lMnLy3.max = MnSYS_ALARM_RESET_MAX; 	
						lMnLy3.val = MnSYS_PrGetAlarm_Item(iIt);
						break;
				}
				break;
		}
	}
}

void MnL3Itr_Sc4Engi(U08 iIt)
{
	lMnLy3.val = MnEGN_PrGet_Item(iIt);
	if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)
		return;

	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:			
			lMnLy3.min = MnEGN_THRESHOLD_SYNC_MIN;	
			lMnLy3.max = MnEGN_THRESHOLD_SYNC_MAX;	
			break;
		case MnEGN_OPT_CH1_PROFILE:		
		case MnEGN_OPT_CH2_PROFILE:
			lMnLy3.min = MnEGN_PROFILE_MIN;	
			lMnLy3.max = MnEGN_PROFILE_MAX;	
			if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;

			break;
		case MnEGN_OPT_CH1_TVG:
		case MnEGN_OPT_CH2_TVG:	
			lMnLy3.min = MnEGN_TVG_MIN;	
			lMnLy3.max = MnEGN_TVG_MAX;	
			break;			
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:	
			lMnLy3.min = MnEGN_WINDOW_RESET_TIME_MIN;	
			lMnLy3.max = MnEGN_WINDOW_RESET_TIME_MAX;	
			if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;

			break;		
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:	
			lMnLy3.min = MnEGN_WINDOW_RANGE_MIN;	
			lMnLy3.max = MnEGN_WINDOW_RANGE_MAX;	
			if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)	break;
			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;

			break;						
		case MnEGN_OPT_MSR:
			lMnLy3.min = MnEGN_MSR_MIN;	
			lMnLy3.max = MnEGN_MSR_MAX;	
			break;					
		// Not Yet
		default:						lMnLy3.val = MENU_VAL_INVALID; 			break;
	}
}

void MnL3Itr_Sc5Fact(U08 iIt)
{
	RTC_TM rtc;



	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		lMnLy3.val = MnFTR_PrGet_Value(iIt);
		if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)
			return;

		switch(iIt)
		{
			case MnFTR_I00_SS_CH:			lMnLy3.min = MnFTR_CH_MIN;	lMnLy3.max = MnFTR_CH_MAX;	break;
			case MnFTR_I01_CH0_04mA:		OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnFTR_CFG_04mA_MIN;	lMnLy3.max = MnFTR_CFG_04mA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I02_CH0_20mA:		OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnFTR_CFG_20mA_MIN;	lMnLy3.max = MnFTR_CFG_20mA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I03_CH1_04mA:		OuCUR_SetOutp_Type(APP_CH_2,OuCUR_TYPE_CHK);	lMnLy3.min = MnFTR_CFG_04mA_MIN;	lMnLy3.max = MnFTR_CFG_04mA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I04_CH1_20mA:		OuCUR_SetOutp_Type(APP_CH_2,OuCUR_TYPE_CHK);	lMnLy3.min = MnFTR_CFG_20mA_MIN;	lMnLy3.max = MnFTR_CFG_20mA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I05_CH1_TRIM_12MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnOS0_TRIM_MIN;		lMnLy3.max = MnOS0_TRIM_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I06_CH1_TRIM_20MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnOS0_TRIM_MIN;		lMnLy3.max = MnOS0_TRIM_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I07_CH1_OUTPUT_4MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	break;
			case MnFTR_I08_CH2_TRIM_12MA:	OuCUR_SetOutp_Type(APP_CH_2,OuCUR_TYPE_CHK);	lMnLy3.min = MnOS0_TRIM_MIN;		lMnLy3.max = MnOS0_TRIM_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I09_CH2_TRIM_20MA:	OuCUR_SetOutp_Type(APP_CH_2,OuCUR_TYPE_CHK);	lMnLy3.min = MnOS0_TRIM_MIN;		lMnLy3.max = MnOS0_TRIM_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	break;
			case MnFTR_I10_CH2_OUTPUT_4MA:	OuCUR_SetOutp_Type(APP_CH_2,OuCUR_TYPE_CHK);	break;		
			case MnFTR_I11_RELAY_TEST:		lMnLy3.min = MnOS1_TEST_MIN;	lMnLy3.max = MnOS1_TEST_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG;		OuRLY_SetTestfEn(TRUE);	break;
			case MnFTR_I12_LANG:			lMnLy3.min = MnSYS_LANG_MIN;	lMnLy3.max = MnSYS_LANG_MAX;		break;
			case MnFTR_I13_TIME:
				rtc = MnSYS_PrGet_Rtc();
				lMnLy3.time[MnSYS_T00_YY] = rtc.year;
				lMnLy3.time[MnSYS_T01_MM] = rtc.month;
				lMnLy3.time[MnSYS_T02_DD] = rtc.day;
				lMnLy3.time[MnSYS_T03_HH] = rtc.hours;
				lMnLy3.time[MnSYS_T04_MN] = rtc.minutes;		
				lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
				break;
			case MnFTR_I14_VERSION:
				break;
			case MnFTR_I15_CLEAN_TEST:		OuCUR_SetPCD_fRun(PCD_TEST);	break;
			default:																	
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		lMnLy3.val = MnFTR_PrGet_CH_Value(APP_CH_1,iIt);
		if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)
			return;

		switch(iIt)
		{
			case MnFTR_OPT_SINGLE_SS_CH:		lMnLy3.min = MnFTR_CH_MIN;	lMnLy3.max = MnFTR_CH_MAX;	break;
			case MnFTR_OPT_SINGLE_04mA:			OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnFTR_CFG_04mA_MIN;	lMnLy3.max = MnFTR_CFG_04mA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
			case MnFTR_OPT_SINGLE_20mA:			OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnFTR_CFG_20mA_MIN;	lMnLy3.max = MnFTR_CFG_20mA_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
			case MnFTR_OPT_SINGLE_TRIM_12MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnOS0_TRIM_MIN;		lMnLy3.max = MnOS0_TRIM_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
			case MnFTR_OPT_SINGLE_TRIM_20MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	lMnLy3.min = MnOS0_TRIM_MIN;		lMnLy3.max = MnOS0_TRIM_MAX;			lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
			case MnFTR_OPT_SINGLE_OUTPUT_4MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_CHK);	break;
			case MnFTR_OPT_SINGLE_RELAY_TEST:	lMnLy3.min = MnOS1_TEST_MIN;	lMnLy3.max = MnOS1_TEST_MAX;		lMnLy3.updn_mod = MENU_V3_UPDN_DIG; 	OuRLY_SetTestfEn(TRUE); break;
			case MnFTR_OPT_SINGLE_LANG:			lMnLy3.min = MnSYS_LANG_MIN;	lMnLy3.max = MnSYS_LANG_MAX;		break;
			case MnFTR_OPT_SINGLE_TIME:
				rtc = MnSYS_PrGet_Rtc();
				lMnLy3.time[MnSYS_T00_YY] = rtc.year;
				lMnLy3.time[MnSYS_T01_MM] = rtc.month;
				lMnLy3.time[MnSYS_T02_DD] = rtc.day;
				lMnLy3.time[MnSYS_T03_HH] = rtc.hours;
				lMnLy3.time[MnSYS_T04_MN] = rtc.minutes;		
				lMnLy3.updn_mod = MENU_V3_UPDN_DIG;
				break;
			case MnFTR_OPT_SINGLE_VERSION:
				break;
			case MnFTR_OPT_SINGLE_CLEAN_TEST:		OuCUR_SetPCD_fRun(PCD_TEST);	break;
			default:																	
				break;
		}
	}
		

}


void MnL3Itr_Sc6Test(U08 iIt)
{
	lMnLy3.val = MnTST_PrGet_Value(iIt);
	if(lMnLy3.updn_mod == MENU_V3_UPDN_DIG_VALUE)
		return;

	switch(iIt)
	{
		case MnTST_OPT_HW_RX_AMP:			lMnLy3.min = MnTST_HW_RX_AMP_MIN;	lMnLy3.max = MnTST_HW_RX_AMP_MAX;	break;
		case MnTST_OPT_CH1_SMOOTH_NO:		
		case MnTST_OPT_CH2_SMOOTH_NO:		lMnLy3.min = MnTST_SMOOTH_NO_MIN;	lMnLy3.max = MnTST_SMOOTH_NO_MAX;	break;
		case MnTST_OPT_CH1_SMOOTH_RANGE:	
		case MnTST_OPT_CH2_SMOOTH_RANGE:	lMnLy3.min = MnTST_SMOOTH_RANGE_MIN;	lMnLy3.max = MnTST_SMOOTH_RANGE_MAX;	break;
		case MnTST_OPT_CH1_THR_RANGE:		
		case MnTST_OPT_CH2_THR_RANGE:		lMnLy3.min = MnTST_THR_RANGE_MIN;	lMnLy3.max = MnTST_THR_RANGE_MAX;	lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
		case MnTST_OPT_CH1_THR_MIN:			
		case MnTST_OPT_CH2_THR_MIN:			lMnLy3.min = MnTST_THR_MIN_MIN;	lMnLy3.max = MnTST_THR_MIN_MAX;	lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
		case MnTST_OPT_CH1_PULSE_NO:		
		case MnTST_OPT_CH2_PULSE_NO:		lMnLy3.min = MnTST_PULSE_NO_MIN;	lMnLy3.max = MnTST_PULSE_NO_MAX; 	break;
		case MnTST_OPT_CH1_ECHO_AMP_B:		
		case MnTST_OPT_CH2_ECHO_AMP_B:		lMnLy3.min = MnTST_ECHO_AMP_B_MIN;	lMnLy3.max = MnTST_ECHO_AMP_B_MAX;	lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
		case MnTST_OPT_FILTER_RANGE:		lMnLy3.min = MnTST_FILTER_RANGE_MIN;	lMnLy3.max = MnTST_FILTER_RANGE_MAX; lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
		case MnTST_OPT_FILTER_TIME:			lMnLy3.min = MnTST_FILTER_TIME_MIN;	lMnLy3.max = MnTST_FILTER_TIME_MAX;	lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
		case MnTST_OPT_SENSOR_DISTANCE:		lMnLy3.min = MnTST_SENSOR_DISTANCE_MIN;	lMnLy3.max = MnTST_SENSOR_DISTANCE_MAX;	lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;											
		case MnTST_OPT_DEMO_MODE:			lMnLy3.min = MnTST_DEMO_MODE_MIN;	lMnLy3.max = MnTST_DEMO_MODE_MAX;	break;
		case MnTST_OPT_DEBUG_MODE:			lMnLy3.min = MnTST_DEBUG_MODE_MIN;	lMnLy3.max = MnTST_DEBUG_MODE_MAX;	break;
		case MnTST_OPT_CH1_HEAVY_HOLD:
		case MnTST_OPT_CH1_LIGHT_HOLD:
		case MnTST_OPT_CH2_HEAVY_HOLD:
		case MnTST_OPT_CH2_LIGHT_HOLD:		lMnLy3.min = MnTST_HOLD_VALUE_MIN;	lMnLy3.max = MnTST_HOLD_VALUE_MAX;	lMnLy3.updn_mod = MENU_V3_UPDN_DIG; break;
		default:
			break;
	}
}



//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Direction Key (Value)
//------------------------------------------------------------------------------------------------------------------------------
void MnL3Val_UpDn(U08 key, S32 min, S32 max)
{
	S32 dig_min = 0;
	S32 dig_max = log10(max);

	switch(lMnLy3.updn_mod)
	{
		case MENU_V3_UPDN_IDLE:
			switch(key)
			{
				case KEY_IDX_PREV:
					if(--lMnLy3.val < min)		lMnLy3.val = max;
					break;
				case KEY_IDX_NEXT:
					if(++lMnLy3.val > max)		lMnLy3.val = min;
					break;
				default:
					break;
			}
			break;
		case MENU_V3_UPDN_DIG:
			switch(key)
			{
				case KEY_IDX_PREV:
					if(++lMnLy3.updn_dig > dig_max) 	lMnLy3.updn_dig = dig_min;
					break;
				case KEY_IDX_NEXT:
					if(--lMnLy3.updn_dig < dig_min) 	lMnLy3.updn_dig = dig_max;
					break;
				default:
					break;
			}
			break;
		case MENU_V3_UPDN_DIG_VALUE:
			switch(key)
			{
				case KEY_IDX_PREV:
					switch(lMnLy3.updn_dig)
					{
						case 4:	if((lMnLy3.val<10000) && (lMnLy3.val>0)) lMnLy3.val*=-1;	else lMnLy3.val-=10000;	break;
						case 3:	if((lMnLy3.val<1000) && (lMnLy3.val>0)) lMnLy3.val*=-1;	else lMnLy3.val-=1000;	break;
						case 2:	if((lMnLy3.val<100) && (lMnLy3.val>0)) lMnLy3.val*=-1;	else lMnLy3.val-=100;	break;
						case 1:	if((lMnLy3.val<10) && (lMnLy3.val>0)) lMnLy3.val*=-1;	else lMnLy3.val-=10;		break;
						case 0:	lMnLy3.val-=1;		break;
						default:	break;				
					}
					if(lMnLy3.val<min)	lMnLy3.val= min;
					break;
				case KEY_IDX_NEXT:
					switch(lMnLy3.updn_dig)
					{
						case 4:	if((lMnLy3.val>-10000) && (lMnLy3.val<0)) lMnLy3.val*=-1;	else lMnLy3.val+=10000;	break;
						case 3:	if((lMnLy3.val>-1000) && (lMnLy3.val<0)) lMnLy3.val*=-1;	else lMnLy3.val+=1000;	break;
						case 2:	if((lMnLy3.val>-100) && (lMnLy3.val<0)) lMnLy3.val*=-1;		else lMnLy3.val+=100;	break;
						case 1:	if((lMnLy3.val>-10) && (lMnLy3.val<0)) lMnLy3.val*=-1;		else lMnLy3.val+=10;		break;
						case 0: lMnLy3.val+=1;		break;
						default:	break;				
					}	
					if(lMnLy3.val>max)	lMnLy3.val= max;
					break;
				default:	break;
			}
			break;
		default:	break;
	}
}


void MnL2Val_Sc0Meas(U08 iSb, U08 iIt, U08 key)
{
	MnL3Val_UpDn(key,lMnLy3.min,lMnLy3.max);

}


void MnL2Val_Sc1Outp(U08 iSb, U08 iIt, U08 key)
{
	MnL3Val_UpDn(key,lMnLy3.min,lMnLy3.max);
}

void MnL2Val_Sc2Data(U08 iSb, U08 iIt, U08 key)
{	

	switch(iSb)
	{
		case MnDAT_SUB_SAVE:
			switch(iIt)
			{
				case MnDS0_OPT_INTERVAL:			MnL3Val_UpDn(key, MnDS0_INTV_MIN, MnDS0_INTV_MAX);			break;
				case MnDS0_OPT_DOWNLOAD:		
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)	
						MnL3Val_UpDn(key, MnDS0_DOWN_MIN, MnDS0_DOWN_MAX);		
					else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
						MnL3Val_UpDn(key, MnDS0_DOWN_MIN, MnDS0_DOWN_SINGLE_MAX);	
					break;
				case MnDS0_OPT_DELETE:				MnL3Val_UpDn(key, MnDS0_DELETE_MIN, MnDS0_DELETE_MAX);		break;
				case MnDS0_OPT_DISPLAY_TERM:		MnL3Val_UpDn(key, MnDS0_DISPLAY_TERM_MIN, MnDS0_DISPLAY_TERM_MAX);	break;
				default:							lMnLy3.val = MENU_VAL_INVALID; 										break;
			}
			break;
		case MnDAT_SUB_COMM:
			if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
			{
				switch(iIt)
				{
					case MnDS1_OPT_TYPE:			MnL3Val_UpDn(key, MnDS1_TYPE_MIN,  MnDS1_TYPE_MAX);				break;
					case MnDS1_OPT_BAUD:			MnL3Val_UpDn(key, MnDS1_BAUDRATE_MIN, MnDS1_BAUDRATE_MAX);		break;
					case MnDS1_OPT_ADDR:			MnL3Val_UpDn(key, MnDS1_ADDRESS_MIN,  MnDS1_ADDRESS_MAX);		break;
					default:						lMnLy3.val = MENU_VAL_INVALID; 									break;
				}
			}
			if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
			{
				switch(iIt)
				{
					case MnDS1_OPT_RF_TYPE:			MnL3Val_UpDn(key, MnDS1_TYPE_MIN,  MnDS1_TYPE_MAX);				break;
					case MnDS1_OPT_RF_CH1_ASSIGN:	MnL3Val_UpDn(key, MnDS1_ASSIGN_MIN, MnDS1_ASSIGN_MAX);			break;
					case MnDS1_OPT_RF_CH1_ADDRESS:	MnL3Val_UpDn(key, MnDS1_RF_ADDRESS_MIN, MnDS1_RF_ADDRESS_MAX);	break;
					case MnDS1_OPT_RF_CH2_ASSIGN:	MnL3Val_UpDn(key, MnDS1_ASSIGN_MIN, MnDS1_ASSIGN_MAX);			break;
					case MnDS1_OPT_RF_CH2_ADDRESS:	MnL3Val_UpDn(key, MnDS1_RF_ADDRESS_MIN, MnDS1_RF_ADDRESS_MAX);	break;
					default:						lMnLy3.val = MENU_VAL_INVALID; 									break;
				}
			}			
			break;	
		default:								lMnLy3.val = MENU_VAL_INVALID; 			return;
	}
}

void MnL2Val_Sc3Syst(U08 sub, U08 iIt, U08 key)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(sub)
		{
			case MnSYS_SUB_BASE:
				switch(iIt)
				{
					case MnSYS_OPT_PASSCODE:				MnL3Val_UpDn(key, MnSYS_PASSCODE_MIN,  MnSYS_PASSCODE_MAX);		break;
					case MnSYS_OPT_LANG:					MnL3Val_UpDn(key, MnSYS_LANG_MIN,  MnSYS_LANG_MAX);				break;
					case MnSYS_OPT_TIME:
						switch(key)
						{
							case KEY_IDX_PREV:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_T00_YY)		lMnLy3.updn_dig = MnSYS_TIM_NUM - 1;
										else									lMnLy3.updn_dig -= 1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_T00_YY:
												if(lMnLy3.time[MnSYS_T00_YY] == 0) 	lMnLy3.time[MnSYS_T00_YY] = 99;
												else								lMnLy3.time[MnSYS_T00_YY] -= 1;
												break;
											case MnSYS_T01_MM:		if(--lMnLy3.time[MnSYS_T01_MM] <= 0)		lMnLy3.time[MnSYS_T01_MM] = 12;			break;
											case MnSYS_T02_DD:		if(--lMnLy3.time[MnSYS_T02_DD] <= 0)		lMnLy3.time[MnSYS_T02_DD] = 31;			break;
											case MnSYS_T03_HH:
												if(lMnLy3.time[MnSYS_T03_HH]  == 0) 	lMnLy3.time[MnSYS_T03_HH] = 23;
												else									lMnLy3.time[MnSYS_T03_HH] -= 1;
												break;
											case MnSYS_T04_MN:
												if(lMnLy3.time[MnSYS_T04_MN]== 0) 	lMnLy3.time[MnSYS_T04_MN] = 59;
												else								lMnLy3.time[MnSYS_T04_MN] -= 1;
												break;
											default:
												break;
										}
										break;
									default:
										break;
								}
								break;
							case KEY_IDX_NEXT:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: 
										break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_T04_MN)		lMnLy3.updn_dig = MnSYS_T00_YY;
										else									lMnLy3.updn_dig += 1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_T00_YY:		if(++lMnLy3.time[MnSYS_T00_YY] > 99)		lMnLy3.time[MnSYS_T00_YY] = 0; 		break;
											case MnSYS_T01_MM:		if(++lMnLy3.time[MnSYS_T01_MM] > 12)		lMnLy3.time[MnSYS_T01_MM] = 1; 		break;
											case MnSYS_T02_DD:		if(++lMnLy3.time[MnSYS_T02_DD] > 31)		lMnLy3.time[MnSYS_T02_DD] = 1; 		break;
											case MnSYS_T03_HH:		if(++lMnLy3.time[MnSYS_T03_HH] > 23)		lMnLy3.time[MnSYS_T03_HH] = 0; 		break;
											case MnSYS_T04_MN:		if(++lMnLy3.time[MnSYS_T04_MN] > 59)		lMnLy3.time[MnSYS_T04_MN] = 0; 		break;
										}
										break;
								}
								break;
							default:
								lMnLy3.val = MENU_VAL_INVALID;
								break;
						}
						break;
					case MnSYS_OPT_RTN_TIM:			MnL3Val_UpDn(key, MnSYS_RTN_TIM_MIN,  MnSYS_RTN_TIM_MIN);		break;
					case MnSYS_OPT_CH1_SITE_NAME:
					case MnSYS_OPT_CH2_SITE_NAME:
						switch(key)
						{
							case KEY_IDX_PREV:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE:	break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_SITE_SEL_HI)	lMnLy3.updn_dig = MnSYS_SITE_SEL_NUM-1;
										else										lMnLy3.updn_dig -=1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_SITE_SEL_HI: 	lMnLy3.val-=100;	break;
											case MnSYS_SITE_SEL_LO_10:	lMnLy3.val-=10;	break;									
											case MnSYS_SITE_SEL_LO_1:	lMnLy3.val-=1;	break;
											default:
												break;
										}
										if(lMnLy3.val <= MnSYS_SITE_NAME_MIN)		
											lMnLy3.val = MnSYS_SITE_NAME_MIN;
										break;
									default:	break;
								}
								break;
							case KEY_IDX_NEXT:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_SITE_SEL_LO_1)	lMnLy3.updn_dig = MnSYS_SITE_SEL_HI;
										else										lMnLy3.updn_dig +=1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_SITE_SEL_HI: 	lMnLy3.val+=100; break;
											case MnSYS_SITE_SEL_LO_10:	lMnLy3.val+=10; break;									
											case MnSYS_SITE_SEL_LO_1:	lMnLy3.val+=1;	break;
											default:
												break;
										}
										if(lMnLy3.val >= MnSYS_SITE_NAME_MAX)		
											lMnLy3.val = MnSYS_SITE_NAME_MAX;
										break;
									default:	break;
								}
								break;
							default:
								break;
						}
						break;
					case MnSYS_OPT_FTR_RST: 		lMnLy3.val ^= 1;						break;
					// Not Yet
					default:						lMnLy3.val = MENU_VAL_INVALID; 			break;
				}
				break;
			case MnSYS_SUB_ALARM:
				MnL3Val_UpDn(key, lMnLy3.min, lMnLy3.max);
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(sub)
		{
			case MnSYS_SUB_BASE:
				switch(iIt)
				{
					case MnSYS_OPT_SINGLE_PASSCODE:				MnL3Val_UpDn(key, MnSYS_PASSCODE_MIN,  MnSYS_PASSCODE_MAX); 	break;
					case MnSYS_OPT_SINGLE_LANG:					MnL3Val_UpDn(key, MnSYS_LANG_MIN,  MnSYS_LANG_MAX); 			break;
					case MnSYS_OPT_SINGLE_TIME:
						switch(key)
						{
							case KEY_IDX_PREV:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_T00_YY) 	lMnLy3.updn_dig = MnSYS_TIM_NUM - 1;
										else									lMnLy3.updn_dig -= 1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_T00_YY:
												if(lMnLy3.time[MnSYS_T00_YY] == 0)	lMnLy3.time[MnSYS_T00_YY] = 99;
												else								lMnLy3.time[MnSYS_T00_YY] -= 1;
												break;
											case MnSYS_T01_MM:		if(--lMnLy3.time[MnSYS_T01_MM] <= 0)		lMnLy3.time[MnSYS_T01_MM] = 12; 		break;
											case MnSYS_T02_DD:		if(--lMnLy3.time[MnSYS_T02_DD] <= 0)		lMnLy3.time[MnSYS_T02_DD] = 31; 		break;
											case MnSYS_T03_HH:
												if(lMnLy3.time[MnSYS_T03_HH]  == 0) 	lMnLy3.time[MnSYS_T03_HH] = 23;
												else									lMnLy3.time[MnSYS_T03_HH] -= 1;
												break;
											case MnSYS_T04_MN:
												if(lMnLy3.time[MnSYS_T04_MN]== 0)	lMnLy3.time[MnSYS_T04_MN] = 59;
												else								lMnLy3.time[MnSYS_T04_MN] -= 1;
												break;
											default:
												break;
										}
										break;
									default:
										break;
								}
								break;
							case KEY_IDX_NEXT:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: 
										break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_T04_MN) 	lMnLy3.updn_dig = MnSYS_T00_YY;
										else									lMnLy3.updn_dig += 1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_T00_YY:		if(++lMnLy3.time[MnSYS_T00_YY] > 99)		lMnLy3.time[MnSYS_T00_YY] = 0;		break;
											case MnSYS_T01_MM:		if(++lMnLy3.time[MnSYS_T01_MM] > 12)		lMnLy3.time[MnSYS_T01_MM] = 1;		break;
											case MnSYS_T02_DD:		if(++lMnLy3.time[MnSYS_T02_DD] > 31)		lMnLy3.time[MnSYS_T02_DD] = 1;		break;
											case MnSYS_T03_HH:		if(++lMnLy3.time[MnSYS_T03_HH] > 23)		lMnLy3.time[MnSYS_T03_HH] = 0;		break;
											case MnSYS_T04_MN:		if(++lMnLy3.time[MnSYS_T04_MN] > 59)		lMnLy3.time[MnSYS_T04_MN] = 0;		break;
										}
										break;
								}
								break;
							default:
								lMnLy3.val = MENU_VAL_INVALID;
								break;
						}
						break;
					case MnSYS_OPT_SINGLE_RTN_TIM: 		MnL3Val_UpDn(key, MnSYS_RTN_TIM_MIN,  MnSYS_RTN_TIM_MAX);		break;
					case MnSYS_OPT_SINGLE_SITE_NAME:
						switch(key)
						{
							case KEY_IDX_PREV:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_SITE_SEL_HI)	lMnLy3.updn_dig = MnSYS_SITE_SEL_NUM-1;
										else										lMnLy3.updn_dig -=1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_SITE_SEL_HI: 	lMnLy3.val-=100;	break;
											case MnSYS_SITE_SEL_LO_10:	lMnLy3.val-=10; break;									
											case MnSYS_SITE_SEL_LO_1:	lMnLy3.val-=1;	break;
											default:
												break;
										}
										if(lMnLy3.val <= MnSYS_SITE_NAME_MIN)		
											lMnLy3.val = MnSYS_SITE_NAME_MIN;
										break;
									default:	break;
								}
								break;
							case KEY_IDX_NEXT:
								switch(lMnLy3.updn_mod)
								{
									case MENU_V3_UPDN_IDLE: break;
									case MENU_V3_UPDN_DIG:
										if(lMnLy3.updn_dig == MnSYS_SITE_SEL_LO_1)	lMnLy3.updn_dig = MnSYS_SITE_SEL_HI;
										else										lMnLy3.updn_dig +=1;
										break;
									case MENU_V3_UPDN_DIG_VALUE:
										switch(lMnLy3.updn_dig)
										{
											case MnSYS_SITE_SEL_HI: 	lMnLy3.val+=100; break;
											case MnSYS_SITE_SEL_LO_10:	lMnLy3.val+=10; break;									
											case MnSYS_SITE_SEL_LO_1:	lMnLy3.val+=1;	break;
											default:
												break;
										}
										if(lMnLy3.val >= MnSYS_SITE_NAME_MAX)		
											lMnLy3.val = MnSYS_SITE_NAME_MAX;
										break;
									default:	break;
								}
								break;
							default:
								break;
						}
						break;
					case MnSYS_OPT_SINGLE_FTR_RST: 		lMnLy3.val ^= 1;						break;
					// Not Yet
					default:						lMnLy3.val = MENU_VAL_INVALID;			break;
				}
				break;
			case MnSYS_SUB_ALARM:
				MnL3Val_UpDn(key, lMnLy3.min, lMnLy3.max);
				break;
		}
	}
}

void MnL2Val_Sc4Engi(U08 iIt, U08 key)
{
	MnL3Val_UpDn(key,lMnLy3.min,lMnLy3.max);

	#if 0
	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:			MnL3Val_UpDn(key, MnEGN_THRESHOLD_SYNC_MIN, MnEGN_THRESHOLD_SYNC_MAX);	break;
		case MnEGN_OPT_CH1_PROFILE:
		case MnEGN_OPT_CH2_PROFILE:				MnL3Val_UpDn(key, MnEGN_PROFILE_MIN, MnEGN_PROFILE_MAX);	break;
		case MnEGN_OPT_CH1_TVG:					
		case MnEGN_OPT_CH2_TVG:					MnL3Val_UpDn(key, MnEGN_TVG_MIN, MnEGN_TVG_MAX);	break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:	MnL3Val_UpDn(key, MnEGN_WINDOW_RESET_TIME_MIN, MnEGN_WINDOW_RESET_TIME_MAX);	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:		MnL3Val_UpDn(key, MnEGN_WINDOW_RANGE_MIN, MnEGN_WINDOW_RANGE_MAX);	break;
		case MnEGN_OPT_MSR:						MnL3Val_UpDn(key, MnEGN_MSR_MIN, MnEGN_MSR_MAX);	break;
		default:	break;
	}
	#endif
}

void MnL2Val_Sc5Fact(U08 iIt, U08 key)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		if(iIt!=MnFTR_I13_TIME)
		{
			MnL3Val_UpDn(key,lMnLy3.min,lMnLy3.max);
			return;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		if(iIt!=MnFTR_OPT_SINGLE_TIME)
		{
			MnL3Val_UpDn(key,lMnLy3.min,lMnLy3.max);
			return;
		}
	}

		

	switch(key)
	{
		case KEY_IDX_PREV:
			switch(lMnLy3.updn_mod)
			{
				case MENU_V3_UPDN_IDLE: break;
				case MENU_V3_UPDN_DIG:
					if(lMnLy3.updn_dig == MnSYS_T00_YY) 	lMnLy3.updn_dig = MnSYS_TIM_NUM - 1;
					else									lMnLy3.updn_dig -= 1;
					break;
				case MENU_V3_UPDN_DIG_VALUE:
					switch(lMnLy3.updn_dig)
					{
						case MnSYS_T00_YY:
							if(lMnLy3.time[MnSYS_T00_YY] == 0)	lMnLy3.time[MnSYS_T00_YY] = 99;
							else								lMnLy3.time[MnSYS_T00_YY] -= 1;
							break;
						case MnSYS_T01_MM:		if(--lMnLy3.time[MnSYS_T01_MM] <= 0)		lMnLy3.time[MnSYS_T01_MM] = 12; 		break;
						case MnSYS_T02_DD:		if(--lMnLy3.time[MnSYS_T02_DD] <= 0)		lMnLy3.time[MnSYS_T02_DD] = 31; 		break;
						case MnSYS_T03_HH:
							if(lMnLy3.time[MnSYS_T03_HH]  == 0) 	lMnLy3.time[MnSYS_T03_HH] = 23;
							else									lMnLy3.time[MnSYS_T03_HH] -= 1;
							break;
						case MnSYS_T04_MN:
							if(lMnLy3.time[MnSYS_T04_MN]== 0)	lMnLy3.time[MnSYS_T04_MN] = 59;
							else								lMnLy3.time[MnSYS_T04_MN] -= 1;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
			break;
		case KEY_IDX_NEXT:
			switch(lMnLy3.updn_mod)
			{
				case MENU_V3_UPDN_IDLE: 
					break;
				case MENU_V3_UPDN_DIG:
					if(lMnLy3.updn_dig == MnSYS_T04_MN) 	lMnLy3.updn_dig = MnSYS_T00_YY;
					else									lMnLy3.updn_dig += 1;
					break;
				case MENU_V3_UPDN_DIG_VALUE:
					switch(lMnLy3.updn_dig)
					{
						case MnSYS_T00_YY:		if(++lMnLy3.time[MnSYS_T00_YY] > 99)		lMnLy3.time[MnSYS_T00_YY] = 0;		break;
						case MnSYS_T01_MM:		if(++lMnLy3.time[MnSYS_T01_MM] > 12)		lMnLy3.time[MnSYS_T01_MM] = 1;		break;
						case MnSYS_T02_DD:		if(++lMnLy3.time[MnSYS_T02_DD] > 31)		lMnLy3.time[MnSYS_T02_DD] = 1;		break;
						case MnSYS_T03_HH:		if(++lMnLy3.time[MnSYS_T03_HH] > 23)		lMnLy3.time[MnSYS_T03_HH] = 0;		break;
						case MnSYS_T04_MN:		if(++lMnLy3.time[MnSYS_T04_MN] > 59)		lMnLy3.time[MnSYS_T04_MN] = 0;		break;
					}
					break;
			}
			break;
		default:
			lMnLy3.val = MENU_VAL_INVALID;
			break;
	}

}



void MnL2Val_Sc6Test(U08 iIt, U08 key)
{
	if((iIt==MnTST_OPT_CH1_PULSE_NO) || (iIt==MnTST_OPT_CH2_PULSE_NO))
	{
		if(key == KEY_IDX_PREV)
		{
			lMnLy3.val-=10;
			if(lMnLy3.val<=lMnLy3.min)	lMnLy3.val = lMnLy3.min;
		}	

		if(key == KEY_IDX_NEXT)
		{
			lMnLy3.val+=10;
			if(lMnLy3.val>=lMnLy3.max)	lMnLy3.val = lMnLy3.max;
		}			
	}
	else
		MnL3Val_UpDn(key, lMnLy3.min, lMnLy3.max);

}

//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Action
//------------------------------------------------------------------------------------------------------------------------------
void MnLy3Act_GotoLyr4(void)
{
	lMnLy3.stt = MENU_S0_INTRO;
	MENU_SetLayer(MENU_L4_ADDITION);
}

void MnLy2Act_EnterMsr(void)
{
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iSb)
		{
			case MnMSR_SUB_BASE:			
				MnMSR_BaseSet_Value(iIt, lMnLy3.val);
				
				switch(iIt)
				{
					case MnMS0_OPT_UNIT:					MnLY3_GotoLyr2();	break;
					case MnMS0_OPT_CH1_OPERATION:		
					case MnMS0_OPT_CH2_OPERATION:			MnLY3_GotoLyr2();	break;
					case MnMS0_OPT_CH1_EMPTY:				
					case MnMS0_OPT_CH2_EMPTY:				break;		
					case MnMS0_OPT_CH1_DEADZONE:		
					case MnMS0_OPT_CH2_DEADZONE:			break;	
					case MnMS0_OPT_CH1_MEASURE_CYCLE:		
					case MnMS0_OPT_CH2_MEASURE_CYCLE:		break;	
					case MnMS0_OPT_CH1_MEASURE_RESET:
					case MnMS0_OPT_CH2_MEASURE_RESET:	
						switch(lMnLy3.val)
						{
							case MENU_CHK_YES:				MnLY3_GotoLyr2();	break;
							case MENU_CHK_NO:
							default:						MnLY3_GotoLyr2();		break;
						}
						break;
					default:								
						break;
				}			
				break;
			case MnMSR_SUB_CAL:	
			
				switch(iIt)
				{
					case MnMS1_OPT_CH1_FREQ:			
					case MnMS1_OPT_CH2_FREQ:			MnMSR_CalSet_Value(iIt, lMnLy3.val);	MnLY3_GotoLyr2();	break;
					case MnMS1_OPT_CH1_ECHO_AMP:		
					case MnMS1_OPT_CH2_ECHO_AMP:		MnMSR_CalSet_Value(iIt, lMnLy3.val);					break;
					case MnMS1_OPT_CH1_THR_LIGHT:		
					case MnMS1_OPT_CH2_THR_LIGHT:		MnLy3Act_GotoLyr4();	return;
					case MnMS1_OPT_CH1_THR_HEAVY:		
					case MnMS1_OPT_CH2_THR_HEAVY:		MnLy3Act_GotoLyr4();	return;
					case MnMS1_OPT_CH1_ASF_LIGHT:		
					case MnMS1_OPT_CH1_ASF_HEAVY:		
					case MnMS1_OPT_CH2_ASF_LIGHT:		
					case MnMS1_OPT_CH2_ASF_HEAVY:		MnMSR_CalSet_Value(iIt, lMnLy3.val);	break;
					case MnMS1_OPT_CH1_DAMPING:			
					case MnMS1_OPT_CH2_DAMPING:			MnMSR_CalSet_Value(iIt, lMnLy3.val);	break;
					case MnMS1_OPT_CH1_OFFSET:			
					case MnMS1_OPT_CH2_OFFSET:			MnMSR_CalSet_Value(iIt, lMnLy3.val);	break;
					default:							break;
				} 
				break;
			default:					break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iSb)
		{
			case MnMSR_SUB_BASE:			
				MnMSR_BaseSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);
				
				switch(iIt)
				{
					case MnMS0_OPT_SINGLE_UNIT:					MnLY3_GotoLyr2();	break;
					case MnMS0_OPT_SINGLE_OPERATION:			MnLY3_GotoLyr2();	break;
					case MnMS0_OPT_SINGLE_EMPTY:				break;		
					case MnMS0_OPT_SINGLE_DEADZONE:				break;	
					case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		break;	
					case MnMS0_OPT_SINGLE_MEASURE_RESET:
						switch(lMnLy3.val)
						{
							case MENU_CHK_YES:				MnLY3_GotoLyr2();	break;
							case MENU_CHK_NO:
							default:						MnLY3_GotoLyr2();		break;
						}
						break;
					default:								
						break;
				}			
				break;
			case MnMSR_SUB_CAL: 
			
				switch(iIt)
				{
					case MnMS1_OPT_SINGLE_FREQ:				MnMSR_CalSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);	MnLY3_GotoLyr2();	break;
					case MnMS1_OPT_SINGLE_ECHO_AMP:			MnMSR_CalSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);					break;
					case MnMS1_OPT_SINGLE_THR_LIGHT:		MnLy3Act_GotoLyr4();	return;
					case MnMS1_OPT_SINGLE_THR_HEAVY:		MnLy3Act_GotoLyr4();	return;
					case MnMS1_OPT_SINGLE_ASF_LIGHT:		
					case MnMS1_OPT_SINGLE_ASF_HEAVY:		MnMSR_CalSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);	break;
					case MnMS1_OPT_SINGLE_DAMPING: 			MnMSR_CalSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);	break;
					case MnMS1_OPT_SINGLE_OFFSET:			MnMSR_CalSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);	break;
					default:							break;
				} 
				break;
			default:					break;
		}
	}
}

void MnLy2Act_EnterOut(void)
{
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();

#if 1
	switch(iSb)
	{	
		case MnOUT_SUB_CURRENT:		
			if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
			{
				MnOUT_CurPrSet_Value(iIt, lMnLy3.val);	
				switch(iIt)
				{
					case MnOS0_OPT_CH1_ASSIGN:		MnLY3_GotoLyr2();	break;
					case MnOS0_OPT_CH1_SET_04mA:	break;
					case MnOS0_OPT_CH1_SET_20mA:	break;
					case MnOS0_OPT_CH1_TRM_12mA:	break;
					case MnOS0_OPT_CH1_TRM_20mA:	break;
					case MnOS0_OPT_CH1_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_0,OuCUR_TYPE_MSR);	MnLY3_GotoLyr2();	break;
					case MnOS0_OPT_CH2_ASSIGN:		MnLY3_GotoLyr2();	break;
					case MnOS0_OPT_CH2_SET_04mA:	break;
					case MnOS0_OPT_CH2_SET_20mA:	break;
					case MnOS0_OPT_CH2_TRM_12mA:	break;
					case MnOS0_OPT_CH2_TRM_20mA:	break;
					case MnOS0_OPT_CH2_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_0,OuCUR_TYPE_MSR);	MnLY3_GotoLyr2();	break;
					default:					break;
				}
			}
			else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
			{
				MnOUT_CurPrSet_Ch_Value(APP_CH_1,iIt, lMnLy3.val);	
				switch(iIt)
				{
					case MnOS0_OPT_SINGLE_ASSIGN:	MnLY3_GotoLyr2();	break;
					case MnOS0_OPT_SINGLE_SET_04mA:	break;
					case MnOS0_OPT_SINGLE_SET_20mA:	break;
					case MnOS0_OPT_SINGLE_TRM_12mA:	break;
					case MnOS0_OPT_SINGLE_TRM_20mA:	break;
					case MnOS0_OPT_SINGLE_OUT_04mA:	OuCUR_SetOutp_Type(MnOUT_CH_0,OuCUR_TYPE_MSR);	MnLY3_GotoLyr2();	break;
					default:
						break;
				}
			}
			break;
		case MnOUT_SUB_RELAY:	
			MnOUT_RlyPrSet_Value(iIt, lMnLy3.val);
			switch(iIt)
			{
				case MnOS1_OPT_ASSIGN:		MnLY3_GotoLyr2();	break;
				case MnOS1_OPT_ACT: 		break;
				case MnOS1_OPT_STOP:		break;
				case MnOS1_OPT_TEST:		break;
				default:					return;
			}
			break;
		case MnOUT_SUB_CLEAN:	
			MnOUT_PcdPrSet_Value(iIt, lMnLy3.val);
			switch(iIt)
			{
				case MnOS2_OPT_MODE:		MnLY3_GotoLyr2();	break;
				case MnOS2_OPT_INTV:		break;
				case MnOS2_OPT_TERM:		break;
				default:					break;
			}
			break;	
		case MnOUT_SUB_ERROR:	
			MnOUT_ErrPrSet_Value(iIt, lMnLy3.val);	
			switch(iIt)
			{
				case MnOS3_OPT_ERR_DELAY:	break;
				case MnOS3_OPT_ERR_OUTP:	MnLY3_GotoLyr2();	break;
				default:					break;
			}
			break;
		default:
			break;
	}
#else
	switch(iSb)
	{	
		case MnOUT_S00_CURRENT:
		case MnOUT_S01_RELAY:
		case MnOUT_S02_PCD:		
		case MnOUT_S03_ERROR:	MnOUT_PrSet_Value(iSb, iIt, lMnLy3.val);	MnLY3_GotoLyr2();	break;
		default:				MnLY3_GotoLyr2();		break;
	}
#endif
}

void MnLy2Act_EnterDat(void)
{
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();

	switch(iSb)
	{	
		case MnDAT_SUB_SAVE:		MnDAT_SavPrSet_Value(iIt, lMnLy3.val);						break;
		case MnDAT_SUB_COMM:		MnDAT_ComPrSet_Value(iIt, lMnLy3.val);	MnLY3_GotoLyr2();	break;
		default:					MnLY3_GotoLyr2();		break;
	}
}

void MnLy2Act_EnterSys(void)
{
	RTC_TM rtc;
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iSb)
		{
			case MnSYS_SUB_BASE:
				switch(iIt)
				{
					case MnSYS_OPT_PASSCODE:		MnSYS_PrSetBase_Value(iIt,lMnLy3.val);	break;
					case MnSYS_OPT_LANG:			MnSYS_PrSetBase_Value(iIt,lMnLy3.val);	MnLY3_GotoLyr2();			break;
					case MnSYS_OPT_RTN_TIM:			MnSYS_PrSetBase_Value(iIt,lMnLy3.val);	MnLY3_GotoLyr2();			break;
					case MnSYS_OPT_FTR_RST:
						switch(lMnLy3.val)
						{
							case MENU_CHK_YES:		APP_FtrReset();					MnLY3_GotoLyr2();		break;
							case MENU_CHK_NO:
							default:												MnLY3_GotoLyr2();			break;
						}
						break;
					case MnSYS_OPT_TIME:						
						rtc.year = lMnLy3.time[MnSYS_T00_YY];
						rtc.month = lMnLy3.time[MnSYS_T01_MM];
						rtc.day = lMnLy3.time[MnSYS_T02_DD];
						rtc.hours = lMnLy3.time[MnSYS_T03_HH];
						rtc.minutes = lMnLy3.time[MnSYS_T04_MN];	
						MnSYS_PrSet_Time(rtc);
						break;
					case MnSYS_OPT_CH1_SITE_NAME:	
					case MnSYS_OPT_CH2_SITE_NAME:	
						MnSYS_PrSetBase_Value(iIt,lMnLy3.val);	
						break;
					default:						MnLY3_GotoLyr2();				break;
				}
				break;
			case MnSYS_SUB_ALARM:
				MnSYS_PrSetAlarm_Value(lMnLy3.val);	
				MnLY3_GotoLyr2();
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iSb)
		{
			case MnSYS_SUB_BASE:
				switch(iIt)
				{
					case MnSYS_OPT_SINGLE_PASSCODE:		MnSYS_PrSetBase_Ch_Value(iIt,lMnLy3.val);	break;
					case MnSYS_OPT_SINGLE_LANG:			MnSYS_PrSetBase_Ch_Value(iIt,lMnLy3.val);	MnLY3_GotoLyr2();			break;
					case MnSYS_OPT_SINGLE_RTN_TIM: 		MnSYS_PrSetBase_Ch_Value(iIt,lMnLy3.val);	MnLY3_GotoLyr2();			break;
					case MnSYS_OPT_SINGLE_FTR_RST:
						switch(lMnLy3.val)
						{
							case MENU_CHK_YES:		APP_FtrReset(); 				MnLY3_GotoLyr2();		break;
							case MENU_CHK_NO:
							default:												MnLY3_GotoLyr2();			break;
						}
						break;
					case MnSYS_OPT_SINGLE_TIME:						
						rtc.year = lMnLy3.time[MnSYS_T00_YY];
						rtc.month = lMnLy3.time[MnSYS_T01_MM];
						rtc.day = lMnLy3.time[MnSYS_T02_DD];
						rtc.hours = lMnLy3.time[MnSYS_T03_HH];
						rtc.minutes = lMnLy3.time[MnSYS_T04_MN];	
						MnSYS_PrSet_Time(rtc);
						break;
					case MnSYS_OPT_SINGLE_SITE_NAME:
						MnSYS_PrSetBase_Ch_Value(iIt,lMnLy3.val);	
						DpTTB_UdtIntro(TEXT_LIST_MENU, 330, _cTTB_ST_TITLE);
						break;
					default:						MnLY3_GotoLyr2();				break;
				}
				break;
			case MnSYS_SUB_ALARM:
				MnSYS_PrSetAlarm_Value(lMnLy3.val); 
				MnLY3_GotoLyr2();
				break;
		}
	}
}

void MnLy2Act_EnterEgn(void)
{
	U08 iIt = MnLY2_GetIdxItem();

	MnEGN_PrSet_Value(iIt,lMnLy3.val);


	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:			MnLY3_GotoLyr2();	break;
		case MnEGN_OPT_CH1_PROFILE:				break;
		case MnEGN_OPT_CH1_TVG:					MnLY3_GotoLyr2();	break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:		break;
		case MnEGN_OPT_CH2_PROFILE:				break;
		case MnEGN_OPT_CH2_TVG:					MnLY3_GotoLyr2();	break;
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:	break;
		case MnEGN_OPT_CH2_WINDOW_RANGE:		break;
		case MnEGN_OPT_MSR:						MnLY3_GotoLyr2();	break;
		default:								break;
	}			
}

void MnLy2Act_EnterFtr(void)
{
	RTC_TM rtc;

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		MnFTR_PrSet_Value(lMnLy3.val);
		switch(MnLY2_GetIdxItem())
		{
			case MnFTR_I00_SS_CH:			MnLY3_GotoLyr2();			break;
			case MnFTR_I01_CH0_04mA:		break;
			case MnFTR_I02_CH0_20mA:		break;
			case MnFTR_I03_CH1_04mA:		break;
			case MnFTR_I04_CH1_20mA:		break;
			case MnFTR_I05_CH1_TRIM_12MA:
			case MnFTR_I06_CH1_TRIM_20MA:	break;
			case MnFTR_I07_CH1_OUTPUT_4MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_MSR);	MnLY3_GotoLyr2();	break;
			case MnFTR_I08_CH2_TRIM_12MA:
			case MnFTR_I09_CH2_TRIM_20MA:	break;
			case MnFTR_I10_CH2_OUTPUT_4MA:	OuCUR_SetOutp_Type(APP_CH_2,OuCUR_TYPE_MSR);	MnLY3_GotoLyr2();	break;	
			case MnFTR_I11_RELAY_TEST:		break;
			case MnFTR_I12_LANG:			MnLY3_GotoLyr2();	break;
			case MnFTR_I13_TIME:
				rtc.year = lMnLy3.time[MnSYS_T00_YY];
				rtc.month = lMnLy3.time[MnSYS_T01_MM];
				rtc.day = lMnLy3.time[MnSYS_T02_DD];
				rtc.hours = lMnLy3.time[MnSYS_T03_HH];
				rtc.minutes = lMnLy3.time[MnSYS_T04_MN];	
				MnSYS_PrSet_Time(rtc);
				break;
			case MnFTR_I14_VERSION:			MnLY3_GotoLyr2();	break;	
			case MnFTR_I15_CLEAN_TEST:		OuCUR_SetPCD_fRun(PCD_OFF);	MnLY3_GotoLyr2();	break;	
			default:														
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		MnFTR_PrSet_CH_Value(APP_CH_1,lMnLy3.val);
		switch(MnLY2_GetIdxItem())
		{
			case MnFTR_OPT_SINGLE_SS_CH:		MnLY3_GotoLyr2();			break;
			case MnFTR_OPT_SINGLE_04mA:			break;
			case MnFTR_OPT_SINGLE_20mA:			break;
			case MnFTR_OPT_SINGLE_TRIM_12MA:
			case MnFTR_OPT_SINGLE_TRIM_20MA:	break;
			case MnFTR_OPT_SINGLE_OUTPUT_4MA:	OuCUR_SetOutp_Type(APP_CH_1,OuCUR_TYPE_MSR);	MnLY3_GotoLyr2();	break;
			case MnFTR_OPT_SINGLE_RELAY_TEST:	break;
			case MnFTR_OPT_SINGLE_LANG:			MnLY3_GotoLyr2();	break;
			case MnFTR_OPT_SINGLE_TIME:
				rtc.year = lMnLy3.time[MnSYS_T00_YY];
				rtc.month = lMnLy3.time[MnSYS_T01_MM];
				rtc.day = lMnLy3.time[MnSYS_T02_DD];
				rtc.hours = lMnLy3.time[MnSYS_T03_HH];
				rtc.minutes = lMnLy3.time[MnSYS_T04_MN];	
				MnSYS_PrSet_Time(rtc);
				break;
			case MnFTR_OPT_SINGLE_VERSION: 		MnLY3_GotoLyr2();	break;	
			case MnFTR_OPT_SINGLE_CLEAN_TEST:		OuCUR_SetPCD_fRun(PCD_OFF); MnLY3_GotoLyr2();	break;	
			default:														
				break;
		}
	}
}


void MnLy2Act_EnterTst(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	MnTST_PrSet_Value(lMnLy3.val);

	switch(iIt)
	{
		case MnTST_OPT_HW_RX_AMP:				MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH1_SMOOTH_NO:			MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH1_SMOOTH_RANGE:		MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH1_THR_RANGE:			break;
		case MnTST_OPT_CH1_THR_MIN:				break;
		case MnTST_OPT_CH1_PULSE_NO:			MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH1_ECHO_AMP_B:			break;
		case MnTST_OPT_CH2_SMOOTH_NO:			MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH2_SMOOTH_RANGE:		MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH2_THR_RANGE:			break;
		case MnTST_OPT_CH2_THR_MIN:				break;
		case MnTST_OPT_CH2_PULSE_NO:			MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH2_ECHO_AMP_B:			break;
		case MnTST_OPT_FILTER_RANGE:			break;
		case MnTST_OPT_FILTER_TIME:				break;
		case MnTST_OPT_SENSOR_DISTANCE:			break;
		case MnTST_OPT_DEMO_MODE:				MnLy3Act_GotoLyr4();break;
		case MnTST_OPT_DEBUG_MODE:				MnLY3_GotoLyr2();	break;
		case MnTST_OPT_CH1_HEAVY_HOLD:
		case MnTST_OPT_CH1_LIGHT_HOLD:
		case MnTST_OPT_CH2_HEAVY_HOLD:
		case MnTST_OPT_CH2_LIGHT_HOLD:			break;
		default:
			break;
	}		
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event - Key Action
//------------------------------------------------------------------------------------------------------------------------------
void MnLy3Evt_KeyFunc(void)
{	
	// Relay Test

	if(OuCUR_GetPCD_fRun()==PCD_TEST)
		OuCUR_SetPCD_fRun(PCD_OFF);

	switch(lMnLy3.updn_mod)
	{
		case MENU_V3_UPDN_IDLE:
		case MENU_V3_UPDN_DIG:
			if(OuRLY_GetTestfEn())
				OuRLY_SetTestfEn(FALSE);
			if(OuCUR_GetOutp_Type(MnFTR_CH_0)!=OuCUR_TYPE_MSR)
				OuCUR_SetOutp_Type(MnOUT_CH_0,OuCUR_TYPE_MSR);
			if(OuCUR_GetOutp_Type(MnFTR_CH_1)!=OuCUR_TYPE_MSR)
				OuCUR_SetOutp_Type(MnOUT_CH_1,OuCUR_TYPE_MSR);
			break;
		case MENU_V3_UPDN_DIG_VALUE:
			break;		
	}
	
	DpSTR_DebugExp(1, 1, "[MnLY3] Goto L1 (ITEM)");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(lMnLy3.updn_mod)
	{
		case MENU_V3_UPDN_IDLE:
		case MENU_V3_UPDN_DIG:
			MnLY3_InitValue();
			break;
		case MENU_V3_UPDN_DIG_VALUE:
			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	
			lMnLy3.stt = MENU_S0_INTRO;
			DpMN_UpdtBttn(MENU_L3_VALUE);
			DpM3_UpdatPop();	
			return;			
	}


	MnLY3_GotoLyr2();
}

void MnLy3Evt_KeyEnter(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY3] ENTER");
	INPU_ClrKeyEvt(KEY_EVT_NONE);


	switch(lMnLy3.updn_mod)
	{
		case MENU_V3_UPDN_IDLE:
			if(OuRLY_GetTestfEn())
				OuRLY_SetTestfEn(FALSE);
			if(OuCUR_GetOutp_Type(MnFTR_CH_0)!=OuCUR_TYPE_MSR)
				OuCUR_SetOutp_Type(MnOUT_CH_0,OuCUR_TYPE_MSR);
			if(OuCUR_GetOutp_Type(MnFTR_CH_1)!=OuCUR_TYPE_MSR)
				OuCUR_SetOutp_Type(MnOUT_CH_1,OuCUR_TYPE_MSR);
			break;
		case MENU_V3_UPDN_DIG:
		case MENU_V3_UPDN_DIG_VALUE:
			break;		
	}



	switch(lMnLy3.updn_mod)
	{
		case MENU_V3_UPDN_DIG:
			lMnLy3.updn_mod = MENU_V3_UPDN_DIG_VALUE;	
			lMnLy3.stt = MENU_S1_STDBY; 		
			DpMN_UpdtBttn(MENU_L3_VALUE);
			DpM3_UpdatPop();		
			break;
		case MENU_V3_UPDN_DIG_VALUE:
			lMnLy3.updn_mod = MENU_V3_UPDN_DIG;	
			lMnLy3.stt = MENU_S0_INTRO; 		
			DpMN_UpdtBttn(MENU_L3_VALUE);
			DpM3_UpdatPop();		
			break;			
	}


	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:			MnLy2Act_EnterMsr();				break;
		case MENU_SC1_OUTP:			MnLy2Act_EnterOut();				break;
		case MENU_SC2_DATA:			MnLy2Act_EnterDat();				break;
		case MENU_SC3_SYST:			MnLy2Act_EnterSys();				break;
		case MENU_SC4_EGNR:			MnLy2Act_EnterEgn();				break;
		case MENU_SC5_FCTR:			MnLy2Act_EnterFtr();				break;
		case MENU_SC6_TEST:			MnLy2Act_EnterTst();				break;
		default:					break;
	}


	if(MENU_GetLayer()==MENU_L4_ADDITION)
		return;

	if(lMnLy3.updn_mod == MENU_V3_UPDN_IDLE)
		MnLY3_InitValue();

}

void MnLy3Evt_KeyUpDn(U08 key)
{
	U08 iSc = MENU_GetSection();
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();
	U08 evt = INPU_GetKeyEvt();

	DpSTR_DebugExp(1, 1, "[MnLY3] Value");
	INPU_ClrKeyEvt(evt);

	switch(iSc)
	{
		case MENU_SC0_MEAS:			MnL2Val_Sc0Meas(iSb, iIt, key);		break;
		case MENU_SC1_OUTP:			MnL2Val_Sc1Outp(iSb, iIt, key);		break;
		case MENU_SC2_DATA:			MnL2Val_Sc2Data(iSb, iIt, key);		break;
		case MENU_SC3_SYST:			MnL2Val_Sc3Syst(iSb, iIt, key);		break;
		case MENU_SC4_EGNR:			MnL2Val_Sc4Engi(iIt, key);			break;
		case MENU_SC5_FCTR:			MnL2Val_Sc5Fact(iIt, key);			break;
		case MENU_SC6_TEST:			MnL2Val_Sc6Test(iIt, key);			break;
		default:					lMnLy3.val = MENU_VAL_INVALID; 		break;
	}

	lMnLy3.stt = MENU_S1_STDBY;
	DpM3_UpdatPop();
}

void MnLy3Evt_KeyInvalid(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY3] Invalid Key");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy3.stt = MENU_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void MnLy3Stt_St0Intro(void)
{
	U08 iSc = MENU_GetSection();
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem(); 
	
	INPU_ClrKeyEvt(KEY_EVT_NONE);
	lMnLy3.updn_mod = MENU_V3_UPDN_IDLE;

	switch(iSc)
	{
		case MENU_SC0_MEAS:			MnL3Itr_Sc0Meas(iSb, iIt);			break;
		case MENU_SC1_OUTP:			MnL3Itr_Sc1Outp(iSb, iIt);			break;
		case MENU_SC2_DATA:			MnL3Itr_Sc2Data(iSb, iIt);			break;
		case MENU_SC3_SYST:			MnL3Itr_Sc3Syst(iSb,iIt);				break;
		case MENU_SC4_EGNR:			MnL3Itr_Sc4Engi(iIt);				break;
		case MENU_SC5_FCTR:			MnL3Itr_Sc5Fact(iIt);				break;
		case MENU_SC6_TEST:			MnL3Itr_Sc6Test(iIt);				break;
		default:					lMnLy3.val = MENU_VAL_INVALID; 		break;
	}

	DpM3_IntroPop();
	lMnLy3.stt = MENU_S1_STDBY;
}

void MnLy3Stt_St1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[MnLY3] Key (PUSH)");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[MnLY3] Key (DTT_L)");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[MnLY3] Key (SHORT)");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[MnLY3] Key (REPEAT)");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[MnLY3] Key (LONG)");			break;
		default:
			DpM0_StdBySct();

			if(!lMnLy3.fSb)
			{
				DpSTR_DebugExp(0, 1, "[MnLY3] STBY - Pending");
				lMnLy3.fSb = _F_T;
			}
			return;
	}

	lMnLy3.stt = MENU_S2_DTT_E;
	lMnLy3.fSb = _F_F;
}

void MnLy3Stt_St2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			MnLy3Evt_KeyFunc();				break;
				case KEY_IDX_PREV:			MnLy3Evt_KeyUpDn(key);			break;
				case KEY_IDX_NEXT:			MnLy3Evt_KeyUpDn(key);			break;
				case KEY_IDX_ENTER:			MnLy3Evt_KeyEnter();			break;
				default:					MnLy3Evt_KeyInvalid();			break;
			}
			break;

		case KEY_EVT_NONE:			DpSTR_DebugExp(1, 1, "[MnLY3] Evt (NONE)");			break;
		default:					DpSTR_DebugExp(1, 1, "[MnLY3] Evt (Invalid)");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
S32 MnLY3_GetValue(void)					{	return lMnLy3.val;				}
S32 MnLY3_GetMax(void)						{	return lMnLy3.max;				}
S32 MnLY3_GetMin(void)						{	return lMnLy3.min;				}
U08 MnLY3_GetUpdnMod(void)					{	return lMnLy3.updn_mod;			}
S32 MnLY3_GetUpdnDig(void)					{	return lMnLy3.updn_dig;			}
U08 MnLY3_GetTime(U08 sel)					{	return lMnLy3.time[sel];		}

// Set
void MnLY3_SetUpdnMod(U08 sel)			{	lMnLy3.updn_mod = sel;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnLY3_InitValue(void)
{
	lMnLy3.stt = MENU_S0_INTRO;
	lMnLy3.fSb = _F_F;

	lMnLy3.min = 0;
	lMnLy3.max = 0;
	lMnLy3.val = 0;

	lMnLy3.updn_mod = MENU_V3_UPDN_IDLE;
	lMnLy3.updn_dig = 0;
}

void MnLY3_GotoLyr2(void)
{
	U08 iSc = MENU_GetSection();
	
	lMnLy3.stt = MENU_S0_INTRO;

	DpM0_IntroSct();

	switch(iSc)
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:
		case MENU_SC3_SYST:			DpM1_IntroSub();				break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:
			break;
	}
	
	DpM2_IntroItm();
	MENU_SetLayer(MENU_L2_ITEM);
}

void MnLY3_ProcValue(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lMnLy3.stt)
	{
		case MENU_S0_INTRO:			MnLy3Stt_St0Intro();				break;
		case MENU_S1_STDBY:			MnLy3Stt_St1StdBy(evt);				break;
		case MENU_S2_DTT_E:			MnLy3Stt_St2DttEv(evt, key);		break;
		default:					lMnLy3.stt = MENU_S0_INTRO;			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

