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
#include "app_sys.h"
#include "app_main.h"
// bsp
#include "bsp_timer.h"
// input
#include "input_main.h"
#include "input_key.h"
// display
#include "disp_string.h"
#include "disp_titlebar.h"
#include "disp_main.h"
// disp - menu
#include "dp_menu_main.h"
#include "dp_menu_measure.h"
#include "dp_menu_output.h"
#include "dp_menu_data.h"
#include "dp_menu_system.h"
#include "dp_menu_engineer.h"
#include "dp_menu_factory.h"
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
#include "menu_lyr3_value.h"
// self
#include "menu_lyr4_addition.h"
// function
#include "data_save.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnLY4_LS lMnLy4;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Action (Event)
//------------------------------------------------------------------------------------------------------------------------------
void MnLy3Act_PrevSys(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(MnLY2_GetIdxItem())
		{
			case MnSYS_OPT_TIME:
				switch(MnLY3_GetValue())
				{
					case MnSYS_T00_YY:
						if(lMnLy4.val == 0) 	lMnLy4.val = 99;
						else					lMnLy4.val -= 1;
						break;
					case MnSYS_T01_MM:		if(--lMnLy4.val <= 0)		lMnLy4.val = 12;			break;
					case MnSYS_T02_DD:		if(--lMnLy4.val <= 0)		lMnLy4.val = 31;			break;
					case MnSYS_T03_HH:
						if(lMnLy4.val == 0) 	lMnLy4.val = 23;
						else					lMnLy4.val -= 1;
						break;
					case MnSYS_T04_MN:
						if(lMnLy4.val == 0) 	lMnLy4.val = 59;
						else					lMnLy4.val -= 1;
						break;
				}
				break;
			case MnSYS_OPT_CH1_SITE_NAME:
				break;				
			case MnSYS_OPT_CH2_SITE_NAME:
				break;		
			default:
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(MnLY2_GetIdxItem())
		{
			case MnSYS_OPT_SINGLE_TIME:
				switch(MnLY3_GetValue())
				{
					case MnSYS_T00_YY:
						if(lMnLy4.val == 0) 	lMnLy4.val = 99;
						else					lMnLy4.val -= 1;
						break;
					case MnSYS_T01_MM:		if(--lMnLy4.val <= 0)		lMnLy4.val = 12;			break;
					case MnSYS_T02_DD:		if(--lMnLy4.val <= 0)		lMnLy4.val = 31;			break;
					case MnSYS_T03_HH:
						if(lMnLy4.val == 0) 	lMnLy4.val = 23;
						else					lMnLy4.val -= 1;
						break;
					case MnSYS_T04_MN:
						if(lMnLy4.val == 0) 	lMnLy4.val = 59;
						else					lMnLy4.val -= 1;
						break;
				}
				break;
			case MnSYS_OPT_SINGLE_SITE_NAME:
				break;				
			default:
				break;
		}
	}
}

void MnLy3Act_NextSys(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(MnLY2_GetIdxItem())
		{
			case MnSYS_OPT_TIME:
				switch(MnLY3_GetValue())
				{
					case MnSYS_T00_YY:		if(++lMnLy4.val > 99)		lMnLy4.val = 0;			break;
					case MnSYS_T01_MM:		if(++lMnLy4.val > 12)		lMnLy4.val = 1;			break;
					case MnSYS_T02_DD:		if(++lMnLy4.val > 31)		lMnLy4.val = 1;			break;
					case MnSYS_T03_HH:		if(++lMnLy4.val > 23)		lMnLy4.val = 0;			break;
					case MnSYS_T04_MN:		if(++lMnLy4.val > 59)		lMnLy4.val = 0;			break;
				}
				break;
			case MnSYS_OPT_CH1_SITE_NAME:
				break;			
			case MnSYS_OPT_CH2_SITE_NAME:
				break;
			default:
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(MnLY2_GetIdxItem())
		{
			case MnSYS_OPT_SINGLE_TIME:
				switch(MnLY3_GetValue())
				{
					case MnSYS_T00_YY:		if(++lMnLy4.val > 99)		lMnLy4.val = 0; 		break;
					case MnSYS_T01_MM:		if(++lMnLy4.val > 12)		lMnLy4.val = 1; 		break;
					case MnSYS_T02_DD:		if(++lMnLy4.val > 31)		lMnLy4.val = 1; 		break;
					case MnSYS_T03_HH:		if(++lMnLy4.val > 23)		lMnLy4.val = 0; 		break;
					case MnSYS_T04_MN:		if(++lMnLy4.val > 59)		lMnLy4.val = 0; 		break;
				}
				break;
			case MnSYS_OPT_SINGLE_SITE_NAME:
				break;			
			default:
				break;
		}
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event (Key)
//------------------------------------------------------------------------------------------------------------------------------
void MnLy4Evt_KeyFunc(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY4] Goto L1 (ITEM)");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(MENU_GetSection())
	{
		case MENU_SC2_DATA:
			if(MnLY2_GetIdxItem()==MnDS0_OPT_DOWNLOAD)
				DaSav_SetDumfEn(_F_F);
			break;
		case MENU_SC6_TEST:
			if(MnLY2_GetIdxItem()==MnTST_OPT_DEMO_MODE)
				DaSav_SetDumfEn(_F_F);
			break;			
		default:
			break;
	}

	MnLY4_GotoLyr2();

}

void MnLy4Evt_KeyPrev(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY4] Value--");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			switch(MnLY1_GetSection())
			{
				case MnMSR_SUB_CAL:
					switch(MnLY3_GetValue())
					{
						case MnMS1_THRESHOLD_MANUAL:
							lMnLy4.val-= 1;
							if(lMnLy4.val < MnMS1_THR_VAL_MANUAL_MIN)	lMnLy4.val = MnMS1_THR_VAL_MANUAL_MAX;	
							break;
						case MnMS1_THRESHOLD_AUTO:
							lMnLy4.val-= 5;
							if(lMnLy4.val < MnMS1_THR_VAL_AUTO_MIN)	lMnLy4.val = MnMS1_THR_VAL_AUTO_MAX;	
							break;
						default:
							break;
					}
					DpMSRCal_PopAddupdat();
					break;
				default:
					break;
			}
			break;
		case MENU_SC2_DATA:	
			switch(MnLY2_GetIdxItem())
			{
				case MnDS0_OPT_DOWNLOAD:
					DpSTR_DebugExp(1, 1, "[MnLY3] Goto L1 (ITEM)");
					INPU_ClrKeyEvt(KEY_EVT_NONE);
					MnLY3_GotoLyr2();
					break;
				default:
					break;
			}
		default:					break;
	}

	lMnLy4.stt = MENU_S1_STDBY;
}

void MnLy4Evt_KeyNext(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY4] Value++");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			switch(MnLY1_GetSection())
			{
				case MnMSR_SUB_CAL:
					switch(MnLY3_GetValue())
					{
						case MnMS1_THRESHOLD_MANUAL:
							lMnLy4.val+= 1;
							if(lMnLy4.val > MnMS1_THR_VAL_MANUAL_MAX)	lMnLy4.val = MnMS1_THR_VAL_MANUAL_MIN;
							break;
						case MnMS1_THRESHOLD_AUTO:
							lMnLy4.val+= 5;
							if(lMnLy4.val > MnMS1_THR_VAL_AUTO_MAX)	lMnLy4.val = MnMS1_THR_VAL_AUTO_MIN;
							break;
						default:
							break;
					}
					DpMSRCal_PopAddupdat();
					break;
				default:
					break;
			}
			break;
		default:					break;
	}

	lMnLy4.stt = MENU_S1_STDBY;
}

void MnLy4Evt_KeyEnter(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY4] ENTER");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			switch(MnLY1_GetSection())
			{
				case MnMSR_SUB_CAL:
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
					{
						MnMSR_CalSet_Value(MnLY2_GetIdxItem(), MnLY3_GetValue());	
						MnMSR_Set_Threshold_Value(MnLY2_GetIdxItem(), lMnLy4.val);	
					}
					else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
					{
						MnMSR_CalSet_Ch_Value(APP_CH_1,MnLY2_GetIdxItem(), MnLY3_GetValue());
						MnMSR_Set_Threshold_Ch_Value(APP_CH_1,MnLY2_GetIdxItem(), lMnLy4.val);	
					}
					MnLY4_GotoLyr2();	
					break;
				default:			break;
			}
			break;
		default:					break;
	}

	lMnLy4.stt = MENU_S0_INTRO;
}

void MnLy4Evt_KeyInvalid(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY4] Invalid (Key)");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy4.stt = MENU_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void MnLy4Stt_S0Intro(void)
{
	RTC_TM rtc;
	U08 sub = MnLY1_GetSection();
	U08 opt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	lMnLy4.per=1;
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(MENU_GetSection())
		{
			case MENU_SC0_MEAS:
				switch(sub)
				{
					case MnMSR_SUB_BASE:	break;
					case MnMSR_SUB_CAL:
						switch(opt)
						{
							case MnMS1_OPT_CH1_THR_LIGHT:	
							case MnMS1_OPT_CH1_THR_HEAVY:
							case MnMS1_OPT_CH2_THR_LIGHT:
							case MnMS1_OPT_CH2_THR_HEAVY:
								if(val!= MnMSR_CalGet_Value(opt))	
								{
									switch(val)
									{
										case MnMS1_THRESHOLD_AUTO:		lMnLy4.val= MnMS1_THR_VAL_AUTO_DEF;		break;
										case MnMS1_THRESHOLD_MANUAL:	lMnLy4.val= MnMS1_THR_VAL_MANUAL_DEF;	break;
										default:						break;
									}
								}
								else	
									lMnLy4.val = MnMSR_Get_Threshold_Value(opt);
								break;
							default:					
								break;
						}
						break;
					default:
						break;
				}
				break;
			case MENU_SC3_SYST:
				rtc = MnSYS_PrGet_Rtc();

				switch(opt)
				{
					case MnSYS_OPT_TIME:
						switch(val)
						{
							case MnSYS_T00_YY:		lMnLy4.val = rtc.year;			break;
							case MnSYS_T01_MM:		lMnLy4.val = rtc.month; 		break;
							case MnSYS_T02_DD:		lMnLy4.val = rtc.day;			break;
							case MnSYS_T03_HH:		lMnLy4.val = rtc.hours; 		break;
							case MnSYS_T04_MN:		lMnLy4.val = rtc.minutes;		break;
						}
						break;
					case MnSYS_OPT_CH1_SITE_NAME:
						break;					
					case MnSYS_OPT_CH2_SITE_NAME:
						break;
				}
				break;
			case MENU_SC2_DATA:
				switch(MnLY2_GetIdxItem())
				{
					case MnDS0_OPT_DOWNLOAD:
						#if 0
						DpDAT_AddIntro();
						DpDAT_AddUpdat();
						#endif
						break;
					default:
						break;
				}
			default:
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{	
		switch(MENU_GetSection())
		{
			case MENU_SC0_MEAS:
				switch(sub)
				{
					case MnMSR_SUB_BASE:	break;
					case MnMSR_SUB_CAL:
						switch(opt)
						{
							case MnMS1_OPT_SINGLE_THR_LIGHT:	
							case MnMS1_OPT_SINGLE_THR_HEAVY:
								if(val!= MnMSR_CalGet_Ch_Value(APP_CH_1,opt))	
								{
									switch(val)
									{
										case MnMS1_THRESHOLD_AUTO:		lMnLy4.val= MnMS1_THR_VAL_AUTO_DEF; 	break;
										case MnMS1_THRESHOLD_MANUAL:	lMnLy4.val= MnMS1_THR_VAL_MANUAL_DEF;	break;
										default:						break;
									}
								}
								else	
									lMnLy4.val = MnMSR_Get_Threshold_Ch_Value(APP_CH_1,opt);
								break;
							default:					
								break;
						}
						break;
					default:
						break;
				}
				break;
			case MENU_SC2_DATA:
				switch(MnLY2_GetIdxItem())
				{
					case MnDS0_OPT_DOWNLOAD:
					#if 0
						DpDAT_AddIntro();
						DpDAT_AddUpdat();
					#endif
						break;
					default:
						break;
				}
			default:
				break;
		}
	}
	
	DpM4_AddIntro();
	lMnLy4.stt = MENU_S1_STDBY;
}

void MnLy4Stt_S1StdBy(U08 evt)
{

	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[MnLY4] Key (PUSH)");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[MnLY4] Key (DTT_L)");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[MnLY4] Key (SHORT)");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[MnLY4] Key (REPEAT)");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[MnLY4] Key (LONG)");			break;
		default:
			DpM0_StdBySct();

			if(!lMnLy4.fSb)
			{
				DpSTR_DebugExp(0, 1, "[MnLY4] STBY (Pending)");
				lMnLy4.fSb = _F_T;
			}
			switch(MENU_GetSection())
			{
				case MENU_SC2_DATA:
					if(MnLY2_GetIdxItem()==MnDS0_OPT_DOWNLOAD)
					{
						DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_T);

						DpDAT_AddUpdat();
						DISP_ProcFlipFrm(); 
						DpDAT_AddUpdat();
						while(DaSAV_DumpProgress(&lMnLy4.per) != SAV_DOWN_OK)
						{
							INPU_ProcMain();
						}
					}
					break;
				case MENU_SC6_TEST:
					if(MnLY2_GetIdxItem()==MnTST_OPT_DEMO_MODE)
					{
						DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_T);

						if(MnTST_PrGet_Value(MnTST_OPT_DEMO_MODE)==0)
						{
							DpDAT_AddUpdat();
							DISP_ProcFlipFrm(); 
							DpDAT_AddUpdat();
							while(DaSAV_DumpProgress_Save_380(&lMnLy4.per) != SAV_DOWN_OK)
							{
								INPU_ProcMain();
							}
						}

						if(MnTST_PrGet_Value(MnTST_OPT_DEMO_MODE)==1)
						{
							DpDAT_AddUpdat();
							DISP_ProcFlipFrm(); 
							DpDAT_AddUpdat();
							while(DaSAV_DumpProgress_Save_160(&lMnLy4.per) != SAV_DOWN_OK)
							{
								INPU_ProcMain();
							}
						}
					}
					break;					
				default:
					break;
			}
			return;
	}

	lMnLy4.stt = MENU_S2_DTT_E;
	lMnLy4.fSb = _F_F;
}

void MnLy4Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			MnLy4Evt_KeyFunc();				break;
				case KEY_IDX_PREV:			MnLy4Evt_KeyPrev();				break;
				case KEY_IDX_NEXT:			MnLy4Evt_KeyNext();				break;
				case KEY_IDX_ENTER:			MnLy4Evt_KeyEnter();			break;
				default:					MnLy4Evt_KeyInvalid();			break;
			}
			break;

		case KEY_EVT_NONE:			DpSTR_DebugExp(1, 1, "[MnLY4] Evt (NONE)");			break;
		default:					DpSTR_DebugExp(1, 1, "[MnLY4] Evt (Default)");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
S32 MnLY4_GetValue(void)		 {	return lMnLy4.val;			}
U08 MnLy4_GetPercent(void)	 	 {	return lMnLy4.per;			}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void MnLY4_InitAddition(void)
{
	lMnLy4.stt = MENU_S0_INTRO;
	lMnLy4.fSb = _F_F;
	lMnLy4.val = 0;
	lMnLy4.val2 = 0;
}

void MnLY4_GotoLyr2(void)
{
	U08 iSc = MENU_GetSection();
	
	lMnLy4.stt = MENU_S0_INTRO;

	DpM0_IntroSct();

	switch(iSc)
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:			DpM1_IntroSub();				break;
		case MENU_SC3_SYST:
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		default:
			break;
	}
	
	DpM2_IntroItm();
	MENU_SetLayer(MENU_L2_ITEM);
}

void MnLY4_ProcAddition(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lMnLy4.stt)
	{
		case MENU_S0_INTRO:			MnLy4Stt_S0Intro();					break;
		case MENU_S1_STDBY:			MnLy4Stt_S1StdBy(evt);				break;
		case MENU_S2_DTT_E:			MnLy4Stt_S2DttEv(evt, key);			break;
		default:					lMnLy4.stt = MENU_S0_INTRO;			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

