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
#include "disp_string.h"
// self
#include "menu_system.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnSYS_LS lMnSys;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
// Get
RTC_TM MnSYS_PrGet_Rtc(void)			{	return lMnSys.rtc;				}
S32 MnSYS_PrGet_site_name_hi(U08 ch)	{	return lMnSys.mPr.site_name_HI[ch];	}
S32 MnSYS_PrGet_site_name_lo(U08 ch)	{	return lMnSys.mPr.site_name_LO[ch];	}
S32 MnSYS_PrGet_site_name(U08 ch)	{	return lMnSys.mPr.site_name[ch];	}


S32 MnSYS_PrGetBase_Item(U08 itm)
{
	switch(itm)
	{
		case MnSYS_OPT_PASSCODE:		return lMnSys.mPr.passcode;
		case MnSYS_OPT_LANG:			return lMnSys.mPr.lang;			
		case MnSYS_OPT_TIME:			break;
		case MnSYS_OPT_RTN_TIM:			return lMnSys.mPr.rtn_tim;
		case MnSYS_OPT_CH1_SITE_NAME:
		case MnSYS_OPT_CH2_SITE_NAME:	break;
		case MnSYS_OPT_FTR_RST:			break;	
		default:						break;
	}

	return MENU_VAL_INVALID;
}

S32 MnSYS_PrGetBase_Ch_Item(U08 itm)
{
	switch(itm)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		return lMnSys.mPr.passcode;
		case MnSYS_OPT_SINGLE_LANG:			return lMnSys.mPr.lang;			
		case MnSYS_OPT_SINGLE_TIME:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:		return lMnSys.mPr.rtn_tim;
		case MnSYS_OPT_SINGLE_SITE_NAME:
		case MnSYS_OPT_SINGLE_FTR_RST:		break;	
		default:							break;
	}

	return MENU_VAL_INVALID;
}

S32 MnSYS_PrGetAlarm_Item(U08 itm)
{
	switch(itm)
	{
		case MnSYS_OPT_ALARM_TIMER:		return lMnSys.mPr.alarm_timer;
		case MnSYS_OPT_ALARM_RESET:		return MnSYS_ALARM_RESET_OFF;			
		default:						break;
	}

	return MENU_VAL_INVALID;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set & Save
//------------------------------------------------------------------------------------------------------------------------------
void MnSYS_PrSet_Time(RTC_TM rtc)
{
	lMnSys.rtc = rtc;

	APP_RtcSetTime(lMnSys.rtc);	
}

void MnSYS_PrSetBase_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnSYS_OPT_PASSCODE:		lMnSys.mPr.passcode = val;		break;
		case MnSYS_OPT_LANG:			lMnSys.mPr.lang = val;			DpSTR_InitMain();	break;
		case MnSYS_OPT_TIME:			break;
		case MnSYS_OPT_RTN_TIM:			lMnSys.mPr.rtn_tim = val;		break;
		case MnSYS_OPT_CH1_SITE_NAME:	lMnSys.mPr.site_name[APP_CH_1] =  val;	break;
		case MnSYS_OPT_CH2_SITE_NAME:	lMnSys.mPr.site_name[APP_CH_2] =  val;	break;			
		default:
			break;
	}

	switch(iIt)
	{
		case MnSYS_OPT_PASSCODE:		MRM_WrWord(_mPASSCODE_L, lMnSys.mPr.passcode);		break;
		case MnSYS_OPT_LANG:			MRM_WrByte(_mLANG, lMnSys.mPr.lang);				break;
		case MnSYS_OPT_TIME:			break;
		case MnSYS_OPT_RTN_TIM:			MRM_WrByte(_mRTN_TIM, lMnSys.mPr.rtn_tim);			break;
		case MnSYS_OPT_CH1_SITE_NAME:	MRM_WrWord(_mCH1_SITE_NAME_L,  lMnSys.mPr.site_name[APP_CH_1]);	break;
		case MnSYS_OPT_CH2_SITE_NAME:	MRM_WrWord(_mCH2_SITE_NAME_L,  lMnSys.mPr.site_name[APP_CH_2]);	break;
	}
}

void MnSYS_PrSetBase_Ch_Value(U08 iIt,S32 val)
{
	switch(iIt)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		lMnSys.mPr.passcode = val;		break;
		case MnSYS_OPT_SINGLE_LANG:			lMnSys.mPr.lang = val;			break;
		case MnSYS_OPT_SINGLE_TIME:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:			lMnSys.mPr.rtn_tim = val;		break;
		case MnSYS_OPT_SINGLE_SITE_NAME:	lMnSys.mPr.site_name[APP_CH_1] =  val;	break;		
		default:
			break;
	}

	switch(iIt)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		MRM_WrWord(_mPASSCODE_L, lMnSys.mPr.passcode);		break;
		case MnSYS_OPT_SINGLE_LANG:			MRM_WrByte(_mLANG, lMnSys.mPr.lang);				break;
		case MnSYS_OPT_SINGLE_TIME:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:		MRM_WrByte(_mRTN_TIM, lMnSys.mPr.rtn_tim);			break;
		case MnSYS_OPT_SINGLE_SITE_NAME:	MRM_WrWord(_mCH1_SITE_NAME_L,  lMnSys.mPr.site_name[APP_CH_1]);	break;	
	}
}

void MnSYS_PrSetAlarm_Value(S32 val)
{
	U08 iIt = MnLY2_GetIdxItem();

	switch(iIt)
	{
		case MnSYS_OPT_ALARM_TIMER:		lMnSys.mPr.alarm_timer = val;		break;
		case MnSYS_OPT_ALARM_RESET:		lMnSys.mPr.alarm_reset = MnSYS_ALARM_RESET_ON;		break;		
		default:
			break;
	}

	switch(iIt)
	{
		case MnSYS_OPT_ALARM_TIMER:		MRM_WrByte(_mALARM_TIMER, lMnSys.mPr.alarm_timer);		break;
		case MnSYS_OPT_ALARM_RESET:		break;
	}
}

void MnSYS_PrRst_Factory(void)
{
	MRM_WrWord(_mPASSCODE_L, MnSYS_PASSCODE_DEF);
	MRM_WrByte(_mLANG, MnSYS_LANG_DEF);

	MRM_WrByte(_mRTN_TIM, MnSYS_RTN_TIM_DEF);
	MRM_WrWord(_mCH1_SITE_NAME_L, MnSYS_SITE_NAME_DEF);	
	MRM_WrWord(_mCH2_SITE_NAME_L, MnSYS_SITE_NAME_DEF);	

	MRM_WrByte(_mALARM_TIMER, MnSYS_ALARM_TIMER_DEF);


}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnSYS_GetLayer(void)			{	return lMnSys.lyr;		}
// Set
void MnSYS_SetLayer(U08 lyr)		{	lMnSys.lyr = lyr;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnSYS_PrInitMain(void)
{
	lMnSys.mPr.passcode = MRM_RdWord(_mPASSCODE_L);
	lMnSys.mPr.lang = MRM_RdByte(_mLANG);
	lMnSys.mPr.rtn_tim = MRM_RdByte(_mRTN_TIM);
	lMnSys.mPr.site_name[APP_CH_1] = MRM_RdWord(_mCH1_SITE_NAME_L);
	lMnSys.mPr.site_name[APP_CH_2] = MRM_RdWord(_mCH2_SITE_NAME_L);	

	lMnSys.rtc = APP_RtcGetTime();
	lMnSys.mPr.alarm_timer = MRM_RdByte(_mALARM_TIMER);

	// Check Parameters
	if(lMnSys.mPr.passcode > MnSYS_PASSCODE_MAX)						lMnSys.mPr.passcode = MnSYS_PASSCODE_DEF;
	if(lMnSys.mPr.lang > MnSYS_LANG_MAX)								lMnSys.mPr.lang = MnSYS_LANG_DEF;
	if(lMnSys.mPr.rtn_tim > MnSYS_RTN_TIM_MAX)							lMnSys.mPr.rtn_tim = MnSYS_RTN_TIM_DEF;
	if(lMnSys.mPr.site_name[APP_CH_1] < MnSYS_SITE_NAME_MIN)			lMnSys.mPr.site_name[APP_CH_1] = MnSYS_SITE_NAME_DEF;
	if(lMnSys.mPr.site_name[APP_CH_2] < MnSYS_SITE_NAME_MIN)			lMnSys.mPr.site_name[APP_CH_2] = MnSYS_SITE_NAME_DEF;
	if(lMnSys.mPr.site_name[APP_CH_1] > MnSYS_SITE_NAME_MAX)			lMnSys.mPr.site_name[APP_CH_1] = MnSYS_SITE_NAME_DEF;
	if(lMnSys.mPr.site_name[APP_CH_2] > MnSYS_SITE_NAME_MAX)			lMnSys.mPr.site_name[APP_CH_2] = MnSYS_SITE_NAME_DEF;

	if(lMnSys.mPr.alarm_timer > MnSYS_ALARM_TIMER_MAX)					lMnSys.mPr.alarm_timer= MnSYS_ALARM_TIMER_DEF;


	DpSTR_InitMain();

}

void MnSYS_InitMain(void)
{
	lMnSys.lyr = MENU_L0_SECTION;

	MnLY0_InitSection();
	MnLY1_InitSubSct();
	MnLY2_InitItem();
	MnLY3_InitValue();
	MnLY4_InitAddition();

	MnSYS_PrInitMain();
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

