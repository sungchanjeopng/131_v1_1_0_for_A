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
#include "disp_color.h"
#include "disp_string.h"
#include "disp_titlebar.h"
// disp - menu
#include "dp_menu_main.h"
#include "dp_menu_measure.h"
#include "dp_menu_output.h"
#include "dp_menu_data.h"
#include "dp_menu_system.h"
#include "dp_menu_engineer.h"
#include "dp_menu_factory.h"
// menu
#include "menu_main.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_data.h"
#include "menu_system.h"
#include "menu_engineer.h"
#include "menu_factory.h"
#include "menu_test.h"
// self
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnLY1_LS lMnLy1;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event - Key Action
//------------------------------------------------------------------------------------------------------------------------------
void MnLy1SubEvt_KeyFunc(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY1] Goto SCREEN");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy1.stt = MENU_S0_INTRO;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:
		// Not Use
		case MENU_SC3_SYST:			MENU_SetLayer(MENU_L0_SECTION);			break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:					return;
	}

	DpTTB_UdtIntro(TEXT_LIST_MENU, 330, _cTTB_ST_TITLE);
}

void MnLy1SubEvt_KeyPrev(void)
{
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy1.stt = MENU_S1_STDBY;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			DpSTR_DebugExp(1, 1, "[MnLY1] PREV (sct--)");
			if(lMnLy1.sct == MnMSR_SUB_MIN)		lMnLy1.sct = MnMSR_SUB_NUM - 1;
			else								lMnLy1.sct -= 1;
			break;			
		case MENU_SC1_OUTP:
			DpSTR_DebugExp(1, 1, "[MnLY1] PREV (sct--)");
			if(lMnLy1.sct == MnOUT_SUB_MIN)		lMnLy1.sct = MnOUT_SUB_NUM - 1;
			else								lMnLy1.sct -= 1;
			break;
		case MENU_SC2_DATA:
			DpSTR_DebugExp(1, 1, "[MnLY1] PREV (sct--)");
			if(lMnLy1.sct == MnDAT_SUB_MIN) 	lMnLy1.sct = MnDAT_SUB_NUM - 1;
			else								lMnLy1.sct -= 1;
			break;
		// Not Use
		case MENU_SC3_SYST:
			DpSTR_DebugExp(1, 1, "[MnLY1] PREV (sct--)");
			if(lMnLy1.sct == MnSYS_SUB_MIN) 	lMnLy1.sct = MnSYS_SUB_NUM - 1;
			else								lMnLy1.sct -= 1;
			break;
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:
			DpSTR_DebugExp(1, 1, "[MnLY1] PREV (Invalid)");
			lMnLy1.stt = MENU_S1_STDBY;
			return;
	}
	DpM1_UpdatSub();
}

void MnLy1SubEvt_KeyNext(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY1] NEXT - Goto MnDAT");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy1.stt = MENU_S1_STDBY;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			DpSTR_DebugExp(1, 1, "[MnLY1] NEXT (sct++)");
			if(++lMnLy1.sct >= MnMSR_SUB_NUM)		lMnLy1.sct = MnMSR_SUB_MIN;
			break;			
		case MENU_SC1_OUTP:
			DpSTR_DebugExp(1, 1, "[MnLY1] NEXT (sct++)");
			if(++lMnLy1.sct >= MnOUT_SUB_NUM)		lMnLy1.sct = MnOUT_SUB_MIN;
			break;
		case MENU_SC2_DATA:
			DpSTR_DebugExp(1, 1, "[MnLY1] NEXT (sct++)");
			if(++lMnLy1.sct >= MnDAT_SUB_NUM)		lMnLy1.sct = MnDAT_SUB_MIN;
			break;
		// Not Use
		case MENU_SC3_SYST:
			DpSTR_DebugExp(1, 1, "[MnLY1] NEXT (sct++)");
			if(++lMnLy1.sct >= MnSYS_SUB_NUM)		lMnLy1.sct = MnSYS_SUB_MIN;
			break;
		// Not Use
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:
			DpSTR_DebugExp(1, 1, "[MnLY1] NEXT (Invalid)");
			lMnLy1.stt = MENU_S1_STDBY;
			return;
	}

	DpM1_UpdatSub();
}

void MnLy1SubEvt_KeyEnter(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY1] ENTER - Goto Ly1");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy1.stt = MENU_S0_INTRO;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:
		// Not Use
		case MENU_SC3_SYST:		MENU_SetLayer(MENU_L2_ITEM);		break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		default:				lMnLy1.stt = MENU_S1_STDBY;			break;
	}

	DpM1_UpdatSub();
	MnLY2_SetIdxItem(0);
}

void MnLy1SubEvt_HidMnEn(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY1] SFK - Hidden Menu");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	if(!MENU_GetFgHiddn())
		MENU_SetFgHiddn(_F_T);

	DpM0_IntroSct();
	lMnLy1.stt = MENU_S1_STDBY;
}

void MnLy1SubEvt_KeyInvalid(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY1] Event (Key Invalid)");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy1.stt = MENU_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void MnLy1Sst_S0Intro(void)
{
	INPU_ClrKeyEvt(KEY_EVT_NONE);
	MENU_InitSect(MENU_GetSection());
	DpM1_IntroSub();

	lMnLy1.stt = MENU_S1_STDBY;
}

void MnLy1Sst_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[MnLY1] Key - PUSH");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[MnLY1] Key - DTT_L");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[MnLY1] Key - SHORT");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[MnLY1] Key - REPEAT");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[MnLY1] Key - LONG");			break;
		default:
			DpM0_StdBySct();

			if(!lMnLy1.fSb)
			{
				DpSTR_DebugExp(0, 1, "[MnLY1] STBY - Pending");
				lMnLy1.fSb = _F_T;
			}
			return;
	}

	lMnLy1.stt = MENU_S2_DTT_E;
	lMnLy1.fSb = _F_F;
}

void MnLy1Sst_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_DTT_L:
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			MnLy1SubEvt_KeyFunc();				break;
				case KEY_IDX_PREV:			MnLy1SubEvt_KeyPrev();				break;
				case KEY_IDX_NEXT:			MnLy1SubEvt_KeyNext();				break;
				case KEY_IDX_ENTER:			MnLy1SubEvt_KeyEnter();				break;
				default:					MnLy1SubEvt_KeyInvalid();			break;
			}
			break;

		case KEY_EVT_NONE:			DpSTR_DebugExp(1, 1, "[MnLY1] Evt - NONE");			break;
		default:					DpSTR_DebugExp(1, 1, "[MnLY1] Evt - Invalid");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get / Set
U08 MnLY1_GetSection(void)			{	return lMnLy1.sct;			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnLY1_InitSubSct(void)
{
	lMnLy1.stt = MENU_S0_INTRO;
	lMnLy1.sct = MnOUT_SUB_MIN;
	lMnLy1.fSb = _F_F;
}

void MnLY1_ProcSubSct(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lMnLy1.stt)
	{
		case MENU_S0_INTRO:			MnLy1Sst_S0Intro();					break;
		case MENU_S1_STDBY:			MnLy1Sst_S1StdBy(evt);				break;
		case MENU_S2_DTT_E:			MnLy1Sst_S2DttEv(evt, key);			break;
		default:					lMnLy1.stt = MENU_S0_INTRO;			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

