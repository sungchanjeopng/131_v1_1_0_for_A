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
#include "dp_screen_front.h"
#include "dp_screen_main.h"
// screen
#include "screen_main.h"
#include "screen_front.h"
// menu
#include "menu_engineer.h"
// self
#include "screen_frt0_func.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL0F_LS lScFr0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Event Action
//------------------------------------------------------------------------------------------------------------------------------
void ScFr0Evt_KeyMenu(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR0] Goto MENU");
	INPU_ClrKeyEvt(evt);

	lScFr0.stt = SCRN_S0_INTRO;
	APP_SetMode(APP_MD1_MENU);
}

void ScFr0Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR0] Goto ScINF");
	INPU_ClrKeyEvt(evt);

	lScFr0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P4_TREND);
}

void ScFr0Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR0] Goto ScECO");
	INPU_ClrKeyEvt(evt);

	lScFr0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P1_HYBRID);

	
}

void ScFr0Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR0] Goto L1");
	INPU_ClrKeyEvt(evt);

	lScFr0.stt = SCRN_S0_INTRO;
	ScFRT_SetLayer(SCRN_L1_LIST);
}

void ScFr0Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR0] EVT (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScFr0.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Manchine
//------------------------------------------------------------------------------------------------------------------------------
void ScFr0Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	ScFRT_InitMain();
	DpFR0_FncIntro();
	DpSCR_UpdtBttn(SCRN_L0_FUNC);

	lScFr0.stt = SCRN_S1_STDBY;
}

void ScFr0Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScFR0] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScFR0] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScFR0] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScFR0] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScFR0] Key - LONG");			break;
		default:
			DpFR0_FncStdBy();

			if(lScFr0.fSb)
				return;
			lScFr0.fSb = _F_T;

			DpSTR_DebugExp(0, 1, "[ScFR0] STBY - Pending");
			return;
	}

	lScFr0.stt = SCRN_S2_DTT_E;
	lScFr0.fSb = _F_F;
}

void ScFr0Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScFr0Evt_KeyMenu(evt);			break;
				case KEY_IDX_PREV:		ScFr0Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScFr0Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScFr0Evt_KeyInvalid(evt);		break;
				default:				ScFr0Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScFR0] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScFR0] Evt - Default");		break;
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
void ScFR0_InitFunc(void)
{
	lScFr0.stt = SCRN_S0_INTRO;
	lScFr0.fSb = _F_F;
}

void ScFR0_ProcFunc(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScFr0.stt)
	{
		case SCRN_S0_INTRO:		ScFr0Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScFr0Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScFr0Stt_S2DttEv(evt, key); 		break;
		default:				lScFr0.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

