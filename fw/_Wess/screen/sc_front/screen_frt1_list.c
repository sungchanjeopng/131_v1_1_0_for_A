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
// function
#include "input_main.h"
#include "input_key.h"
// display
#include "disp_string.h"
// disp - screen
#include "dp_screen_front.h"
#include "dp_screen_main.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
// self
#include "screen_frt1_list.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL1L_LS lScFr1;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScFr1Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR1] FUNC - Goto L1");
	INPU_ClrKeyEvt(evt);

	lScFr1.stt = SCRN_S0_INTRO;
	ScFRT_SetLayer(SCRN_L0_FUNC);
}

void ScFr1Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR1] PREV - Move Index");
	INPU_ClrKeyEvt(evt);
	
	lScFr1.stt = SCRN_S1_STDBY;
	DpFR1_LstUpdat();

}

void ScFr1Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR1] NEXT - Move Index");
	INPU_ClrKeyEvt(evt);

	lScFr1.stt = SCRN_S1_STDBY;
	DpFR1_LstUpdat();
}

void ScFr1Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR1] ENTER - Goto L3");
	INPU_ClrKeyEvt(evt);

	lScFr1.stt = SCRN_S0_INTRO;
	ScFRT_SetLayer(SCRN_L2_VALU);
}

void ScFr1Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScFR1] Key - Invalid");
	INPU_ClrKeyEvt(evt);

	lScFr1.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScFr1Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	DpFR1_LstIntro();
	DpSCR_UpdtBttn(SCRN_L1_LIST);

	lScFr1.stt = SCRN_S1_STDBY;
}

void ScFr1Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScFR1] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScFR1] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScFR1] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScFR1] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScFR1] Key - LONG");			break;
		default:
			DpFR0_FncStdBy();

			if(lScFr1.fSb)
				return;
			lScFr1.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScFR1] STBY - Pending");
			return;
	}

	lScFr1.stt = SCRN_S2_DTT_E;
	lScFr1.fSb = _F_F;
}

void ScFr1Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScFr1Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScFr1Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScFr1Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScFr1Evt_KeyEnter(evt);			break;
				default:				ScFr1Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScFR1] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScFR1] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScFR1_GetIdxFunc(void)		{	return lScFr1.iFn;				}
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScFR1_InitList(void)
{
	lScFr1.stt = SCRN_S0_INTRO;
	lScFr1.fSb = _F_F;
	lScFr1.iFn = 0;
}

void ScFR1_ProcList(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScFr1.stt)
	{
		case SCRN_S0_INTRO:		ScFr1Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScFr1Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScFr1Stt_S2DttEv(evt, key);			break;
		default:				lScFr1.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

