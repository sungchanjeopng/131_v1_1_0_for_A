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
// menu - section
#include "menu_main.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_data.h"
#include "menu_system.h"
#include "menu_engineer.h"
#include "menu_factory.h"
#include "menu_test.h"
// menu - layrer
#include "menu_lyr1_sub_sct.h"
// self
#include "menu_lyr2_item.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnLY2_LS lMnLy2;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event - Key Action
//------------------------------------------------------------------------------------------------------------------------------

void MnLy2Evt_KeyEnterOutput(void)
{
	#if 1
	U08 iSc = MENU_GetSection();
	U08 iSb = MnLY1_GetSection();

	switch(iSc)
	{
		case MENU_SC0_MEAS:
			switch(iSb)
			{
				case MnMSR_SUB_BASE:
					lMnLy2.stt = MENU_S3_ENTER;		break;
				case MnMSR_SUB_CAL:
					lMnLy2.stt = MENU_S3_ENTER;		break;
				default:
					break;
			}
			break;
		case MENU_SC1_OUTP:
			switch(iSb)
			{
				case MnOUT_SUB_RELAY:
					lMnLy2.stt = MENU_S3_ENTER; 	break;
				//Not Yet
				case MnOUT_SUB_CURRENT:
					lMnLy2.stt = MENU_S3_ENTER; 	break;
				case MnOUT_SUB_CLEAN:
					lMnLy2.stt = MENU_S3_ENTER; 	break;			
				case MnOUT_SUB_ERROR:
					lMnLy2.stt = MENU_S3_ENTER; 	break;
				default:
					break;
			}			
			break;
		case MENU_SC2_DATA:
			switch(iSb)
			{
				//Not Yet
				case MnDAT_SUB_SAVE:
					lMnLy2.stt = MENU_S3_ENTER;		break;
				case MnDAT_SUB_COMM:
					lMnLy2.stt = MENU_S3_ENTER; 	break;
				default:
					break;
			}			
			break;
		// Not Use L1
		case MENU_SC3_SYST:
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:
			break;
	}
	#else
	switch(MnLY1_GetSection())
	{
		case MnOUT_S01_RELAY:
			switch(lMnLy2.iIt)
			{
				case MnOS1_I01_ACT:
				case MnOS1_I02_STOP:
				case MnOS1_I03_TEST:		lMnLy2.stt = MENU_S3_ENTER;		break;
				default:					break;
			}
			break;
		case MnOUT_S02_PCD:					break;
		//Not Yet
		case MnOUT_S00_CURRENT:
			switch(lMnLy2.iIt)
			{
			// Not Yet
				case MnOS0_I00_SET_04mA:
				case MnOS0_I01_SET_20mA:
				case MnOS0_I04_OUT_04mA:
				default:					break;
			}
			break;
		case MnOUT_S03_ERROR:				break;
		default:							break;
	}
	#endif
}

void MnLy2Evt_KeyFunc(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY2] FUNC - Goto Section");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:
		// Not Use L1
		case MENU_SC3_SYST:		MENU_SetLayer(MENU_L1_SUB_SCT);		break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:				MENU_SetLayer(MENU_L0_SECTION);		break;
	}

	lMnLy2.iIt = 0;
	lMnLy2.stt = MENU_S0_INTRO;
}

void MnLy2Evt_KeyPrev(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY2] PREV - Up");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	if(lMnLy2.iIt == lMnLy2.min)		lMnLy2.iIt = lMnLy2.max - 1;
	else								lMnLy2.iIt -= 1;

	lMnLy2.stt = MENU_S1_STDBY;
	DpM2_UpdatItm();
}

void MnLy2Evt_KeyNext(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY2] NEXT - Down");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	if(++lMnLy2.iIt >= lMnLy2.max)
		lMnLy2.iIt = lMnLy2.min;

	lMnLy2.stt = MENU_S1_STDBY;
	DpM2_UpdatItm();
}

void MnLy2Evt_KeyEnter(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY2] ENTER L2 (Item)");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy2.stt = MENU_S1_STDBY;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:
			MnLy2Evt_KeyEnterOutput();			
			break;

		case MENU_SC3_SYST:
			lMnLy2.stt = MENU_S3_ENTER; 	break;
		case MENU_SC4_EGNR:
			lMnLy2.stt = MENU_S3_ENTER;		break;
			break;
		case MENU_SC5_FCTR:
			if((lMnLy2.iIt==MnFTR_I14_VERSION) &&(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL))
				return;
			else if((lMnLy2.iIt==MnFTR_OPT_SINGLE_VERSION) &&(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE))
				return;
			lMnLy2.stt = MENU_S3_ENTER;		break;
		case MENU_SC6_TEST:
			lMnLy2.stt = MENU_S3_ENTER;		break;
			break;			
		default:							break;
	}

	if(lMnLy2.stt == MENU_S3_ENTER)
		MENU_SetLayer(MENU_L3_VALUE);
}

void MnLy2Evt_KeyInvalid(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY2] Invalid Key");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy2.stt = MENU_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void MnLy2Stt_S0Intro(void)
{
	INPU_ClrKeyEvt(KEY_EVT_NONE);
	MnLY2_InitItem();

	DpM2_IntroItm();
	lMnLy2.stt = MENU_S1_STDBY;
}

void MnLy2Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[MnLY2] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[MnLY2] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[MnLY2] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[MnLY2] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[MnLY2] Key - LONG");			break;
		default:
			if(!lMnLy2.fSb)
			{
				DpSTR_DebugExp(0, 1, "[MnLY2] STBY - Pending");
				lMnLy2.fSb = _F_T;
			}
			return;
	}

	lMnLy2.stt = MENU_S2_DTT_E;
}

void MnLy2Stt_S2DetEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		MnLy2Evt_KeyFunc();			break;
				case KEY_IDX_PREV:		MnLy2Evt_KeyPrev();			break;
				case KEY_IDX_NEXT:		MnLy2Evt_KeyNext();			break;
				case KEY_IDX_ENTER:		MnLy2Evt_KeyEnter();		break;
				default:				MnLy2Evt_KeyInvalid();		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[MnLY2] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[MnLY2] Evt - Invalid");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MnLY2_GetIdxItem(void)				{	return lMnLy2.iIt;		}
// Set
void MnLY2_SetIdxItem(U08 iIt)			{ 	lMnLy2.iIt = iIt;		}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnLY2_InitItem(void)
{
	lMnLy2.stt = MENU_S0_INTRO;
	lMnLy2.fSb = _F_F;


	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(MENU_GetSection())
		{
			case MENU_SC0_MEAS:
				switch(MnLY1_GetSection())
				{
					case MnMSR_SUB_BASE: 		lMnLy2.min = MnMS0_OPT_MIN; 	lMnLy2.max = MnMS0_OPT_NUM; 	break;
					case MnMSR_SUB_CAL:			lMnLy2.min = MnMS1_OPT_MIN; 	lMnLy2.max = MnMS1_OPT_NUM; 	break;
				}
				break;
			case MENU_SC1_OUTP:
				switch(MnLY1_GetSection())
				{
					case MnOUT_SUB_CURRENT:		lMnLy2.min = MnOS0_OPT_MIN; 	lMnLy2.max = MnOS0_OPT_NUM;		break;
					case MnOUT_SUB_RELAY:		lMnLy2.min = MnOS1_OPT_MIN; 	lMnLy2.max = MnOS1_OPT_NUM;		break;
					case MnOUT_SUB_CLEAN:		lMnLy2.min = MnOS2_OPT_MIN; 	lMnLy2.max = MnOS2_OPT_NUM;		break;
					case MnOUT_SUB_ERROR:		lMnLy2.min = MnOS3_OPT_MIN; 	lMnLy2.max = MnOS3_OPT_NUM;		break;
				}
				break;
			case MENU_SC2_DATA:
				switch(MnLY1_GetSection())
				{
					case MnDAT_SUB_SAVE:		lMnLy2.min = MnDS0_OPT_MIN; 		lMnLy2.max = MnDS0_OPT_NUM; 		break;
					case MnDAT_SUB_COMM:		
						if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
						{
							lMnLy2.min = MnDS1_OPT_MIN; 		
							lMnLy2.max = MnDS1_OPT_NUM;
						}
						if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
						{
							lMnLy2.min = MnDS1_OPT_MIN; 		
							lMnLy2.max = MnDS1_OPT_RF_NUM;
						}						
						break;
				}
				break;
			case MENU_SC3_SYST:
				switch(MnLY1_GetSection())
				{
					case MnSYS_SUB_BASE:		lMnLy2.min = MnSY0_OPT_MIN; 	lMnLy2.max = MnSY0_OPT_NUM; 	break;
					case MnSYS_SUB_ALARM:		lMnLy2.min = MnSY1_OPT_MIN; 	lMnLy2.max = MnSY1_OPT_NUM; 	break;
				}
				break;
			case MENU_SC4_EGNR:					lMnLy2.min = MnEGN_OPT_MIN;		lMnLy2.max = MnEGN_OPT_NUM;		break;
			case MENU_SC5_FCTR:					lMnLy2.min = MnFTR_ITM_I00;		lMnLy2.max = MnFTR_ITM_NUM;		break;
			case MENU_SC6_TEST:					lMnLy2.min = MnTST_OPT_MIN;		lMnLy2.max = MnTST_OPT_NUM;		break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(MENU_GetSection())
		{
			case MENU_SC0_MEAS:
				switch(MnLY1_GetSection())
				{
					case MnMSR_SUB_BASE:		lMnLy2.min = MnMS0_OPT_SIGNLE_MIN; 	lMnLy2.max = MnMS0_OPT_SINGLE_NUM; 	break;
					case MnMSR_SUB_CAL: 		lMnLy2.min = MnMS1_OPT_SINGLE_MIN; 	lMnLy2.max = MnMS1_OPT_SINGLE_NUM; 	break;
				}
				break;
			case MENU_SC1_OUTP:
				switch(MnLY1_GetSection())
				{
					case MnOUT_SUB_CURRENT: 	lMnLy2.min = MnOS0_OPT_SINGLE_MIN; 	lMnLy2.max = MnOS0_OPT_SINGLE_NUM; 	break;
					case MnOUT_SUB_RELAY:		lMnLy2.min = MnOS1_OPT_MIN; 		lMnLy2.max = MnOS1_OPT_NUM; 		break;
					case MnOUT_SUB_CLEAN:		lMnLy2.min = MnOS2_OPT_MIN; 		lMnLy2.max = MnOS2_OPT_NUM; 		break;
					case MnOUT_SUB_ERROR:		lMnLy2.min = MnOS3_OPT_MIN; 		lMnLy2.max = MnOS3_OPT_NUM; 		break;
				}
				break;
			case MENU_SC2_DATA:
				switch(MnLY1_GetSection())
				{
					case MnDAT_SUB_SAVE:		lMnLy2.min = MnDS0_OPT_MIN; 		lMnLy2.max = MnDS0_OPT_NUM; 		break;
					case MnDAT_SUB_COMM:		
						if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_MDB)
						{
							lMnLy2.min = MnDS1_OPT_MIN; 		
							lMnLy2.max = MnDS1_OPT_NUM;
						}
						if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)==MnDS1_TYPE_RF)
						{
							lMnLy2.min = MnDS1_OPT_MIN; 		
							lMnLy2.max = MnDS1_OPT_RF_SINGLE_MAX+1;
						}						
						break;
				}
				break;
			case MENU_SC3_SYST:
				switch(MnLY1_GetSection())
				{
					case MnSYS_SUB_BASE:		lMnLy2.min = MnSY0_OPT_SINGLE_MIN; 	lMnLy2.max = MnSY0_OPT_SINGLE_NUM; 	break;
					case MnSYS_SUB_ALARM:		lMnLy2.min = MnSY1_OPT_MIN; 		lMnLy2.max = MnSY1_OPT_NUM; 		break;
				}
				break;
			case MENU_SC4_EGNR: 				lMnLy2.min = MnEGN_OPT_MIN; 		lMnLy2.max = MnEGN_OPT_NUM; 		break;
			case MENU_SC5_FCTR: 				lMnLy2.min = MnFTR_OPT_SINGLE_MIN; 	lMnLy2.max = MnFTR_OPT_SINGLE_NUM; 		break;
			case MENU_SC6_TEST: 				lMnLy2.min = MnTST_OPT_MIN; 		lMnLy2.max = MnTST_OPT_NUM; 		break;
		}
	}
}

void MnLY2_ProcItem(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lMnLy2.stt)
	{
		case MENU_S0_INTRO:		MnLy2Stt_S0Intro();					break;
		case MENU_S1_STDBY:		MnLy2Stt_S1StdBy(evt);				break;
		case MENU_S2_DTT_E:		MnLy2Stt_S2DetEv(evt, key);			break;
		default:				lMnLy2.stt = MENU_S0_INTRO;			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

