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
#include "dp_screen_hybrid.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_echo.h"
// menu
#include "menu_engineer.h"
// self
#include "screen_hyb0_func.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL0F_LS lScHY0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Event Action
//------------------------------------------------------------------------------------------------------------------------------
void ScHY0Evt_KeyMenu(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY0] Goto MENU");
	INPU_ClrKeyEvt(evt);

	lScHY0.stt = SCRN_S0_INTRO;
	APP_SetMode(APP_MD1_MENU);
}

void ScHY0Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY0] Goto ScINF");
	INPU_ClrKeyEvt(evt);

	lScHY0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P0_FRONT);
}

void ScHY0Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY0] Goto ScECO");
	INPU_ClrKeyEvt(evt);

	lScHY0.stt = SCRN_S0_INTRO;

	SCRN_SetPage(SCRN_P2_ECHO);
	ScECH_SetType(ScECO_TYPE_REAL);
	
}

void ScHY0Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY0] Goto L1");
	INPU_ClrKeyEvt(evt);

	lScHY0.stt = SCRN_S0_INTRO;
	ScHYB_SetLayer(SCRN_L1_LIST);
}

void ScHY0Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY0] EVT (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScHY0.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Manchine
//------------------------------------------------------------------------------------------------------------------------------
void ScHY0Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	ScHYB_InitMain();
	DpHY0_FncIntro();

	lScHY0.stt = SCRN_S1_STDBY;
}

void ScHY0Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScHY0] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScHY0] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScHY0] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScHY0] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScHY0] Key - LONG");			break;
		default:
			DpHY0_FncStdBy();

			if(lScHY0.fSb)
				return;
			lScHY0.fSb = _F_T;

			DpSTR_DebugExp(0, 1, "[ScHY0] STBY - Pending");
			return;
	}

	lScHY0.stt = SCRN_S2_DTT_E;
	lScHY0.fSb = _F_F;
}

void ScHY0Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScHY0Evt_KeyMenu(evt);			break;
				case KEY_IDX_PREV:		ScHY0Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScHY0Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScHY0Evt_KeyInvalid(evt);		break;
				default:				ScHY0Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScHY0] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScHY0] Evt - Default");		break;
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
void ScHY0_InitFunc(void)
{
	lScHY0.stt = SCRN_S0_INTRO;
	lScHY0.fSb = _F_F;
}

void ScHY0_ProcFunc(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScHY0.stt)
	{
		case SCRN_S0_INTRO:		ScHY0Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScHY0Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScHY0Stt_S2DttEv(evt, key); 		break;
		default:				lScHY0.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

