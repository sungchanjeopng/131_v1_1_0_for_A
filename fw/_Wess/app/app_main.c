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
#include "bsp_rtc.h"
#include "bsp_uart.h"
#include "Bsp_timer.h"
#include "bsp_ota.h"
#include "bsp_usb.h"
// app
#include "app_status.h"
#include "app_boot.h"
#include "app_schd1sec.h"
// function - input
#include "input_main.h"
#include "input_key.h"
// function - data
#include "data_main.h"
#include "data_save.h"
#include "data_commu.h"
// measure
#include "measure_temperature.h"
#include "measure_main.h"
#include "output_main.h"
// screen
#include "screen_main.h"
// menu
#include "menu_main.h"
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_engineer.h"
#include "measure_cal1_field0.h"
#include "stm32f7xx_hal_gpio.h"
// display
#include "disp_main.h"
#include "disp_string.h"
#include "disp_color.h"
#include "disp_figure.h"
// self
#include "app_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
APP_LS lApp;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - RTC
//------------------------------------------------------------------------------------------------------------------------------
void ApRtc_FtrRst(void)
{
	lApp.tm.year  = 20;
	lApp.tm.month = 7;
	lApp.tm.day   = 13;
	lApp.tm.hours = 8;
	lApp.tm.minutes = 14;
	lApp.tm.seconds = 5;
	RTC_SetTime(lApp.tm);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Mode Proccessor
//------------------------------------------------------------------------------------------------------------------------------
void ApRun_ProcMode(void)
{
	switch(lApp.mode)
	{
		case APP_MD0_SCRN:		SCRN_ProcMain();					break;
		case APP_MD1_MENU:		MENU_ProcMain();					break;
		default:				lApp.mode = APP_MD0_SCRN;			break;
	}

	lApp.fRun = TRUE;
}

void ApRun_MsrStart(U08 iCh, U08 fClr)
{
	if((iCh == APP_CH_2) && (MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE))
		return;

	// Measure - Sensor Tx PWM & Rx ADC
	MsSEN_ProcMain(iCh);
	// Timer Enable
	TMR_HalEnable(_F_T, fClr);
}

void ApRun_FieldStart(U08 iCh, U08 fClr)
{
	if((iCh == APP_CH_2) && (MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE))
		return;

	// Measure - Sensor Tx PWM & Rx ADC
	MsSEN_FieldProcMain(iCh);
	// Timer Enable
	TMR_HalEnable(_F_T, fClr);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Task
//------------------------------------------------------------------------------------------------------------------------------
void ApTsk_ProcT0(void)
{	
	ApRun_MsrStart(APP_CH_1, _F_F);
	MsTPR_ProcCalc(APP_CH_1);
	
	MsCAL_CheckWeak(APP_CH_1);
	
	ApSCD_Proc1Sec(APP_CH_1);
	
	CalPrc_SttCheck(APP_CH_1);
}

void ApTsk_ProcT1(void)
{	
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		ApRun_MsrStart(APP_CH_2, _F_F);
		MsTPR_ProcCalc(APP_CH_2);

		MsCAL_CheckWeak(APP_CH_2);

		ApSCD_Proc1Sec(APP_CH_2);	

		CalPrc_SttCheck(APP_CH_2);

	}
}

void ApTsk_ProcT2(void)
{
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		ApRun_FieldStart(APP_CH_1, _F_F);
		ApSCD_ProcFieldA1Sec(APP_CH_1);
	}
}

void ApTsk_ProcT3(void)
{
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		ApRun_FieldStart(APP_CH_2, _F_F);
		ApSCD_ProcFieldA1Sec(APP_CH_2);
	}

	ApSCD_Intv(APP_CH_1);
	ApSCD_Intv(APP_CH_2);
}

void ApTsk_ProcT4(void)
{
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		MsCal1_ProcDetect(APP_CH_1);
		MsCal1_ProcDetect(APP_CH_2);

		MsCal1_Hunting_Proc();

		MsCal1_ProcJudge();
		MsCal1_CalcResult();
		MsCalPrc_DualParam();	
	}
}

void ApTsk_ProcT5(void)
{

}

void ApTsk_ProcT6(void)
{

}

void ApTsk_ProcT7(void)
{

}

void ApTsk_ProcT8(void)
{
}

void ApTsk_ProcT9(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Scheduler
//------------------------------------------------------------------------------------------------------------------------------
void AppRun_010ms(void)
{

}

void AppRun_050ms(void)
{
	INPU_ProcMain();
}

void AppRun_100ms(void)
{
	switch(gTmr.c.c100ms)
	{
		case	APP_SC0_START:		ApTsk_ProcT0();			break;
		case	APP_SC1_:			ApTsk_ProcT1();			break;
		case	APP_SC2_:			ApTsk_ProcT2();			break;
		case	APP_SC3_:			ApTsk_ProcT3();			break;
		case	APP_SC4_:			ApTsk_ProcT4();			break;
		case	APP_SC5_S1_MEAS:	break;
		case	APP_SC6_:			break;
		case	APP_SC7_:			break;
		case	APP_SC8_:			break;
		case	APP_SC9_:			break;
		case	APP_SCD_NUM:		break;
	}

	gTmr.c.c100ms++;

	DaCOM_ProcMain();

	if((gTmr.c.c100ms%2) == 0)
	{
		ApRun_ProcMode();
		DISP_ProcFlipFrm();	
	}
	DaCOM_ProcMain();


	if(gTmr.f.b.f100ms_01sec==TRUE)
	{
		if(gTmr.c.c100ms >= APP_SC5_S1_MEAS)
		{
			gTmr.c.c100ms = APP_SC0_START;
			gTmr.f.b.f100ms_01sec= FALSE;
		}
	}
}

void AppRun_200ms(void)
{
	

}

void AppRun_500ms(void)
{
	ApSTT_ProcMain();
	BspUsb_Proc();
}

void AppRun_01sec(void)
{
	DaSAV_ProcSave();
	DaMdb_ProcMain();
	OUTP_ProcMain();
	Scd1Sec_ScrnRtnTime();
}

void AppRun_Every(void)
{
	RTC_TM rtc = RTC_GetTime();

	if(lApp.tm.seconds == rtc.seconds)
		return;
	lApp.tm = rtc;
	if(++gTmr.c.c01sec>0xfffffff0)
		gTmr.c.c01sec = 0;
	U64 cyc = MsCAL1_Getrst_cyc();
	
	gTmr.c.timer1[APP_CH_1]++;
	gTmr.c.timer1[APP_CH_2]++;

	cyc++;
	MsCAL1_Setrst_cyc(cyc);
	
	TMR_HalEnable(_F_T, _F_F);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Processor
//------------------------------------------------------------------------------------------------------------------------------
void AppProc_Boot(void)
{
	lApp.fRun = TRUE;
	INPU_ProcMain();

	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();


	if(BOOT_ProcMain()==BOOT_ST02_DONE)
	{		
		switch(evt)
		{
			case KEY_EVT_PUSH: 
			case KEY_EVT_DTT_L: 
			case KEY_EVT_SHORT: 
			case KEY_EVT_REPEAT: 
			case KEY_EVT_LONG: 					
				if(key==(KEY_IDX_PREV|KEY_IDX_MENU|KEY_IDX_NEXT))
					APP_FtrReset();				
				break;
			default:
				break;
		}
		
		HAL_Delay(1000);   /* BLE 모듈 부팅 대기 */
		ota_init();        /* BLE OTA 모듈 초기화 (FLASH/RTC 백업레지스터 등) */
		DaBT_InItMain();   /* BLE BoT-nLE521 초기화 (AT 명령) */

		lApp.proc = APP_PR1_RUN_;
		lApp.mode = APP_MD0_SCRN;
	}

	lApp.fRun = FALSE;
}

void AppProc_Run(void)
{
	AppRun_Every();
	DaMdb_ProcMain();
	DaBT_ProcMain();   /* BLE BoT-nLE521 메인 처리 */

	if(gTmr.f.b.f010ms)		{	gTmr.f.b.f010ms = FALSE;	AppRun_010ms();		}
	if(gTmr.f.b.f050ms)		{	gTmr.f.b.f050ms = FALSE;	AppRun_050ms();		}
	if(gTmr.f.b.f100ms)		{	gTmr.f.b.f100ms = FALSE;	AppRun_100ms();		}
	if(gTmr.f.b.f500ms)		{	gTmr.f.b.f500ms = FALSE;	AppRun_500ms();		}
	if(gTmr.f.b.f01sec)		{	gTmr.f.b.f01sec = FALSE;	AppRun_01sec();		}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - RTC Time
//------------------------------------------------------------------------------------------------------------------------------
// Get
RTC_TM APP_RtcGetTime(void)			{	return RTC_GetTime();			}
// Set
void APP_RtcSetTime(RTC_TM tm)		{	RTC_SetTime(tm);				}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 APP_GetMode(void)			{	return lApp.mode;			}
U08 APP_GetFgRun(void)			{	return lApp.fRun;			}
// Set
void APP_SetMode(U08 mode)		{	lApp.mode = mode;			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void APP_InitMain(void)
{
	lApp.proc = APP_PR0_BOOT;
	lApp.mode = APP_MD0_SCRN;

	lApp.fRun = FALSE;
	lApp.tm.seconds = 0;

	ApSTT_InitMain();

	INPU_InitMain();
	MnFTR_InitMain(); 
	OUTP_InitMain();
	DATA_InitMain();
	DaSAV_InitVari();
	DISP_InitMain();
	SCRN_InitMain();
	MENU_InitMain();
	MEAS_InitMain();
	DAC_InitVari();
	DaCOM_InitMain();

	ApSCD_Init1Sec(APP_CH_1);
	ApSCD_Init1Sec(APP_CH_2);

}

void APP_FtrReset(void)
{
	ApRtc_FtrRst();

	SCRN_FtrReset();
	MENU_PrRst_Factory();
	CalPrc_ResetFlag(APP_CH_1);
	CalPrc_ResetFlag(APP_CH_2);
	DaSAV_DeleteData();
}

void APP_LoopMain(void)
{
	switch(lApp.proc)
	{
		case APP_PR0_BOOT:		AppProc_Boot();					break;
		case APP_PR1_RUN_:		AppProc_Run();					break;
		default:				lApp.proc = APP_PR0_BOOT;		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

