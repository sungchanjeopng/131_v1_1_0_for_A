//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------

#ifndef ___MENU_SYSTEM_H___
#define ___MENU_SYSTEM_H___

//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
#include "app_sys.h"
#include "app_main.h"
#include "bsp_rtc.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Constant definitions
//------------------------------------------------------------------------------------------------------------------------------
enum {
	MnSYS_SUB_BASE = 0,
	MnSYS_SUB_ALARM,
	// Number Max
	MnSYS_SUB_NUM,
};

#define MnSYS_SUB_MAX	(MnSYS_SUB_NUM-1)
#define MnSYS_SUB_MIN	(MnSYS_SUB_BASE)

enum {
	MnSYS_OPT_PASSCODE =0,
	MnSYS_OPT_LANG,
	MnSYS_OPT_TIME,
	MnSYS_OPT_RTN_TIM,
	MnSYS_OPT_CH1_SITE_NAME,
	MnSYS_OPT_CH2_SITE_NAME,
	MnSYS_OPT_FTR_RST,
	MnSYS_OPT_FW_UPDATE_USB,

	MnSY0_OPT_NUM,
};

#define MnSY0_OPT_MIN		(MnSYS_OPT_PASSCODE)
#define MnSY0_OPT_MAX		(MnSY0_OPT_NUM-1)

enum {
	MnSYS_OPT_SINGLE_PASSCODE =0,
	MnSYS_OPT_SINGLE_LANG,
	MnSYS_OPT_SINGLE_TIME,
	MnSYS_OPT_SINGLE_RTN_TIM,
	MnSYS_OPT_SINGLE_SITE_NAME,
	MnSYS_OPT_SINGLE_FTR_RST,
	MnSYS_OPT_SINGLE_FW_UPDATE_USB,

	MnSY0_OPT_SINGLE_NUM,
};

#define MnSY0_OPT_SINGLE_MIN		(MnSYS_OPT_SINGLE_PASSCODE)
#define MnSY0_OPT_SINGLE_MAX		(MnSY0_OPT_SINGLE_NUM-1)

#define MnSYS_PASSCODE_MIN	(0)
#define MnSYS_PASSCODE_MAX	(9999)
#define MnSYS_PASSCODE_DEF	(0)

// Languege
enum {
	MnSYS_LANG_ENG = 0,
	MnSYS_LANG_KOR,
	// Number Max
	MnSYS_LANG_NUM,
}; 


#define MnSYS_LANG_MIN	(MnSYS_LANG_ENG)
#define MnSYS_LANG_MAX	(MnSYS_LANG_NUM-1)
#define MnSYS_LANG_DEF	(MnSYS_LANG_ENG)


enum {
	MnSYS_SITE_SEL_HI = 0,
	MnSYS_SITE_SEL_LO_10,
	MnSYS_SITE_SEL_LO_1,
	// Number Max
	MnSYS_SITE_SEL_NUM,
};


#define MnSYS_SITE_NAME_HI_MIN	(65)
#define MnSYS_SITE_NAME_HI_MAX	(90)
#define MnSYS_SITE_NAME_HI_DEF	(65)

#define MnSYS_SITE_NAME_LO_MIN	(1)
#define MnSYS_SITE_NAME_LO_MAX	(99)
#define MnSYS_SITE_NAME_LO_DEF	(1)

#define MnSYS_SITE_NAME_MIN	(6501)
#define MnSYS_SITE_NAME_MAX	(9099)
#define MnSYS_SITE_NAME_DEF	(6501)

#if 0
// Item Index
enum {
	MnSYS_I00_TIME = 0,
	MnSYS_I01_RTN_TIM,		// Screen Return Time
	MnSYS_I02_FTR_RST,
	MnSYS_I03_LANG,
	// Number Max
	MnSYS_ITM_NUM,
};
#define MnSYS_ITM_I00		(MnSYS_I00_TIME)
#endif

// RTC Time
enum {
	MnSYS_T00_YY = 0,
	MnSYS_T01_MM,
	MnSYS_T02_DD,
	MnSYS_T03_HH,
	MnSYS_T04_MN,
	// Number Max
	MnSYS_TIM_NUM,
};

#define MnSYS_TIME_MIN	(MnSYS_T00_YY)
#define MnSYS_TIME_MAX	(MnSYS_TIM_NUM-1)


// Screen Return Time
enum {
	MnSYS_RTN_TIM_DISABLE = 0,
	MnSYS_RTN_TIM_MIN_05,
	MnSYS_RTN_TIM_MIN_10,
	MnSYS_RTN_TIM_MIN_30,
	// Number Max
	MnSYS_RTN_TIM_NUM,
};

#define MnSYS_RTN_TIM_MIN	(MnSYS_RTN_TIM_DISABLE)
#define MnSYS_RTN_TIM_MAX	(MnSYS_RTN_TIM_NUM-1)
#define MnSYS_RTN_TIM_DEF	(MnSYS_RTN_TIM_DISABLE)


// Factory Reset
enum {
	MnSYS_FTR_RST_NO_ = 0,
	MnSYS_FTR_RST_YES,
	// Number Max
	MnSYS_FTR_RST_NUM,
};

#define MnSYS_FTR_RST_MIN	(MnSYS_FTR_RST_NO_)
#define MnSYS_FTR_RST_MAX	(MnSYS_FTR_RST_NUM-1)

enum {
	MnSYS_OPT_ALARM_TIMER =0,
	MnSYS_OPT_ALARM_RESET,

	MnSY1_OPT_NUM,
};

#define MnSY1_OPT_MIN		(MnSYS_OPT_ALARM_TIMER)
#define MnSY1_OPT_MAX		(MnSY1_OPT_NUM-1)

enum {
	MnSYS_ALARM_TIMER_OFF = 0,
	MnSYS_ALARM_TIMER_1M,
	MnSYS_ALARM_TIMER_3M,
	MnSYS_ALARM_TIMER_6M,
	MnSYS_ALARM_TIMER_12M,
	// Number Max
	MnSYS_ALARM_TIMER_NUM,
};


#define MnSYS_ALARM_TIMER_MIN		(MnSYS_ALARM_TIMER_OFF)
#define MnSYS_ALARM_TIMER_MAX		(MnSYS_ALARM_TIMER_NUM-1)
#define MnSYS_ALARM_TIMER_DEF		(MnSYS_ALARM_TIMER_OFF)

enum {
	MnSYS_ALARM_RESET_OFF = 0,
	MnSYS_ALARM_RESET_ON,
	// Number Max
	MnSYS_ALARM_RESET_NUM,
};

#define MnSYS_ALARM_RESET_MIN		(MnSYS_ALARM_RESET_OFF)
#define MnSYS_ALARM_RESET_MAX		(MnSYS_ALARM_RESET_NUM-1)

//------------------------------------------------------------------------------------------------------------------------------
//  Type definitions
//------------------------------------------------------------------------------------------------------------------------------
// Memory Parameter
typedef struct {
	U08 rtn_tim;			// Screen Return Time
	U08 lang;
	U16 passcode;
	U16 site_name[APP_CH_NUM];
	U08 site_name_HI[APP_CH_NUM];
	U08 site_name_LO[APP_CH_NUM];

	U08 alarm_timer;
	U08 alarm_reset;
} MnSYS_mPR;

// Local Struct
typedef struct {
	MnSYS_mPR mPr;
	RTC_TM rtc;

	U08 lyr;				// Layer Index

} MnSYS_LS;


//------------------------------------------------------------------------------------------------------------------------------
//  Macros
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
extern RTC_TM MnSYS_PrGet_Rtc(void);
extern S32    MnSYS_PrGetBase_Item(U08 itm);
extern S32 MnSYS_PrGet_site_name_hi(U08 ch);
extern S32 MnSYS_PrGet_site_name_lo(U08 ch);
extern S32 MnSYS_PrGet_site_name(U08 ch);
extern S32 MnSYS_PrGetAlarm_Item(U08 itm);
extern S32 MnSYS_PrGetBase_Ch_Item(U08 itm);


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
extern void MnSYS_PrSet_Time(RTC_TM rtc);
extern void MnSYS_PrSetBase_Value(U08 iIt,S32 val);
extern void MnSYS_PrSetBase_Ch_Value(U08 iIt,S32 val);
extern void MnSYS_PrRst_Factory(void);
extern void MnSYS_PrSetAlarm_Value(S32 val);

//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Varables
//------------------------------------------------------------------------------------------------------------------------------
// Get
extern U08 MnSYS_GetLayer(void);
// Set
extern void MnSYS_SetLayer(U08 lyr);


//------------------------------------------------------------------------------------------------------------------------------
//  Extern global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
extern void MnSYS_PrInitMain(void);
extern void MnSYS_InitMain(void);



#endif // ___MENU_SYSTEM_H___
//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

