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
// self
#include "bsp_rtc.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
RTC_TM  lTim;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void RTC_InitMain(void)
{
	//
}

void RTC_SetTime(RTC_TM dateTime)
{
    RTC_DateTypeDef rtc_date;
    RTC_TimeTypeDef rtc_time;

    rtc_date.Year  	 = dateTime.year;
    rtc_date.Month 	 = dateTime.month;
    rtc_date.WeekDay = 0;
    rtc_date.Date  	 = dateTime.day;

    rtc_time.Hours   = dateTime.hours;
    rtc_time.Minutes = dateTime.minutes;
    rtc_time.Seconds = dateTime.seconds;
    rtc_time.TimeFormat = RTC_HOURFORMAT_24;
    rtc_time.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ;
    rtc_time.StoreOperation = RTC_STOREOPERATION_RESET;

    if(HAL_RTC_SetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN) != HAL_OK)
        Error_Handler();

    if(HAL_RTC_SetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN) != HAL_OK)
        Error_Handler();

    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);
}

RTC_TM RTC_GetTime(void)
{
	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;

	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	lTim.year  = rtc_date.Year;
	lTim.month = rtc_date.Month;
	lTim.day   = rtc_date.Date;
	lTim.hours = rtc_time.Hours;
	lTim.minutes = rtc_time.Minutes;
	lTim.seconds = rtc_time.Seconds;

    return lTim;
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

