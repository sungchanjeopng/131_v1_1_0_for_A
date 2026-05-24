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
#include "dp_screen_main.h"
#include "dp_screen_echo.h"
// screen
#include "screen_main.h"
#include "screen_echo.h"
// menu
#include "menu_engineer.h"
// self
#include "screen_eco0_func.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL0F_LS lScEc0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event - Key Action
//------------------------------------------------------------------------------------------------------------------------------
void ScEc0Evt_KeyMenu(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC0] Goto Menu");
	INPU_ClrKeyEvt(evt);

	lScEc0.stt = SCRN_S0_INTRO;
	APP_SetMode(APP_MD1_MENU);
}

void ScEc0Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC0] Goto ScHYB");
	INPU_ClrKeyEvt(evt);

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:	SCRN_SetPage(SCRN_P1_HYBRID);	break;
		case ScECO_TYPE_AVG:	ScECH_SetType(ScECO_TYPE_REAL);	break;
		default:				break;
	}
	lScEc0.stt = SCRN_S0_INTRO;
}

void ScEc0Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC0] Goto ScINF");
	INPU_ClrKeyEvt(evt);

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:	ScECH_SetType(ScECO_TYPE_AVG);	break;
		case ScECO_TYPE_AVG:	SCRN_SetPage(SCRN_P3_INFO);		break;
		default:				break;
	}

	lScEc0.stt = SCRN_S0_INTRO;
}

void ScEc0Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC0] Goto L2");
	INPU_ClrKeyEvt(evt);

	switch(evt)
	{
		case KEY_EVT_LONG:
			break;
	}

	lScEc0.stt = SCRN_S0_INTRO;
	ScECH_SetLayer(SCRN_L1_LIST);
}

void ScEc0Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC0] EVT (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScEc0.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScEc0Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	ScECH_InitMain();
	DpEC0_FncIntro();
	DpSCR_UpdtBttn(SCRN_L0_FUNC);

	lScEc0.stt = SCRN_S1_STDBY;
}

void ScEc0Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScEC0] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScEC0] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScEC0] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScEC0] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScEC0] Key - LONG");			break;
		default:
			DpEC0_FncStdBy(0);
			if(lScEc0.fSb)
				return;
			lScEc0.fSb = _F_T;

			DpSTR_DebugExp(0, 1, "[ScEC0] Key - Pending");
			return;
	}

	lScEc0.stt = SCRN_S2_DTT_E;
	lScEc0.fSb = _F_F;
}

void ScEc0Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScEc0Evt_KeyMenu(evt);			break;
				case KEY_IDX_PREV:		ScEc0Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScEc0Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScEc0Evt_KeyEnter(evt);			break;
				default:				ScEc0Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScEC0] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScEC0] Evt - Default");		break;
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
void ScEC0_InitFunc(void)
{
	lScEc0.stt = SCRN_S0_INTRO;
	lScEc0.fSb = _F_F;
}

void ScEC0_ProcFunc(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScEc0.stt)
	{
		case SCRN_S0_INTRO:		ScEc0Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScEc0Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScEc0Stt_S2DttEv(evt, key); 		break;
		default:				lScEc0.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

