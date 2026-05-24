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
// disp - screen
#include "dp_screen_info.h"
// menu
#include "menu_factory.h"
#include "menu_engineer.h"
// screen
#include "screen_main.h"
#include "screen_info.h"
#include "screen_echo.h"
// self
#include "screen_inf0_func.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL0F_LS lScIf0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Event Action
//------------------------------------------------------------------------------------------------------------------------------
void ScIf0Evt_KeyMenu(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScIF0] Goto MENU");
	INPU_ClrKeyEvt(evt);

	lScIf0.stt = SCRN_S0_INTRO;
	APP_SetMode(APP_MD1_MENU);
}

void ScIf0Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScIF0] Goto ScECO");
	INPU_ClrKeyEvt(evt);

	lScIf0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P2_ECHO);
	ScECH_SetType(ScECO_TYPE_AVG);

}

void ScIf0Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScIF0] Goto ScHYB");
	INPU_ClrKeyEvt(evt);

	lScIf0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P4_TREND);
}

void ScIf0Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScIF0] Not Work");
	INPU_ClrKeyEvt(evt);

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL)
	{
		lScIf0.stt = SCRN_S0_INTRO;
		ScINF_SetLayer(SCRN_L1_LIST);
	}
	else	lScIf0.stt = SCRN_S0_INTRO;
}

void ScIf0Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScIF0] EVT (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScIf0.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Manchine
//------------------------------------------------------------------------------------------------------------------------------
void ScIf0Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	ScINF_InitMain();
	DpIF0_FncIntro();

	lScIf0.stt = SCRN_S1_STDBY;
}

void ScIf0Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScIF0] Key (PUSH)");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScIF0] Key (DTT_L)");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScIF0] Key (SHORT)");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScIF0] Key (REPEAT)");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScIF0] Key (LONG)");			break;
		default:
			DpIF0_FncStdBy();

			if(lScIf0.fSb)
				return;
			lScIf0.fSb = _F_T;

			DpSTR_DebugExp(0, 1, "[ScHY1] STBY (Pending)");
			return;
	}

	lScIf0.stt = SCRN_S2_DTT_E;
	lScIf0.fSb = _F_F;
}

void ScIf0Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			ScIf0Evt_KeyMenu(evt);					break;
				case KEY_IDX_PREV:			ScIf0Evt_KeyPrev(evt);					break;
				case KEY_IDX_NEXT:			ScIf0Evt_KeyNext(evt);					break;
				case KEY_IDX_ENTER:			ScIf0Evt_KeyInvalid(evt);				break;
				default:					ScIf0Evt_KeyInvalid(evt);				break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScIF0] Evt (NONE)");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScIF0] Evt (Invalid)");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScIF0_InitFunc(void)
{
	lScIf0.stt = SCRN_S0_INTRO;
	lScIf0.fSb = _F_F;
}

void ScIF0_ProcFunc(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScIf0.stt)
	{
		case SCRN_S0_INTRO:		ScIf0Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScIf0Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScIf0Stt_S2DttEv(evt, key); 		break;
		default:				lScIf0.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

