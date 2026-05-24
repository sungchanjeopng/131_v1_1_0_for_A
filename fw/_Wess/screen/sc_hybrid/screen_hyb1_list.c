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
#include "dp_screen_hybrid.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
// self
#include "screen_hyb1_list.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL1L_LS lScHY1;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScHY1Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY1] FUNC - Goto L1");
	INPU_ClrKeyEvt(evt);

	lScHY1.stt = SCRN_S0_INTRO;
	ScHYB_SetLayer(SCRN_L0_FUNC);
}

void ScHY1Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY1] PREV - Move Index");
	INPU_ClrKeyEvt(evt);

#if 0
	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:
			if(lScHY1.iFn == ScHYB_F00_LEVEL)			lScHY1.iFn = ScHYB_FNC_NUMB - 1;
			else										lScHY1.iFn -= 1;
			break;
	
		case MnFTR_SS_DUAL:
			if(lScHY1.iFn == ScHYB_F00_LEVEL)			lScHY1.iFn = ScHYB_FNC_NUMB;
			else										lScHY1.iFn -= 1;
			break;
	}
#endif
	lScHY1.stt = SCRN_S1_STDBY;
	DpHY1_LstUpdat();
}

void ScHY1Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY1] NEXT - Move Index");
	INPU_ClrKeyEvt(evt);

#if 0
	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:		if(++lScHY1.iFn >=  ScHYB_FNC_NUMB)			lScHY1.iFn = ScHYB_F00_LEVEL;		break;
		case MnFTR_SS_DUAL:			if(++lScHY1.iFn >= (ScHYB_FNC_NUMB+1))		lScHY1.iFn = ScHYB_F00_LEVEL;		break;
	}
#endif
	lScHY1.stt = SCRN_S1_STDBY;
	DpHY1_LstUpdat();
}

void ScHY1Evt_KeyEnter(U08 evt)
{
#if 0
	switch(lScHY1.iFn)
	{
		case ScHYB_FNC_NUMB:	
			DpSTR_DebugExp(1, 1, "[ScHY1] ENTER - Goto L3");
			INPU_ClrKeyEvt(evt);
			ScHYB_PrSet_Value(ScHYB_FNC_NUMB,!ScHYB_PrGet_Chnnl());
			lScHY1.stt = SCRN_S0_INTRO;
			DpHY0_FncIntro();
			DpHY1_LstUpdat();			
			return;
		default:				break;
	}

	DpSTR_DebugExp(1, 1, "[ScHY1] ENTER - Goto L3");
	INPU_ClrKeyEvt(evt);

	lScHY1.stt = SCRN_S0_INTRO;
	ScHYB_SetLayer(SCRN_L2_VALU);
#endif
}

void ScHY1Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScHY1] Key - Invalid");
	INPU_ClrKeyEvt(evt);

	lScHY1.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScHY1Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	DpHY1_LstIntro();

	lScHY1.stt = SCRN_S1_STDBY;
}

void ScHY1Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScHY1] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScHY1] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScHY1] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScHY1] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScHY1] Key - LONG");			break;
		default:
			DpHY0_FncStdBy();

			if(lScHY1.fSb)
				return;
			lScHY1.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScHY1] STBY - Pending");
			return;
	}

	lScHY1.stt = SCRN_S2_DTT_E;
	lScHY1.fSb = _F_F;
}

void ScHY1Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScHY1Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScHY1Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScHY1Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScHY1Evt_KeyInvalid(evt);		break;
				default:				ScHY1Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScHY1] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScHY1] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScHY1_GetIdxFunc(void)		{	return lScHY1.iFn;				}
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScHY1_InitList(void)
{
	lScHY1.stt = SCRN_S0_INTRO;
	lScHY1.fSb = _F_F;
	lScHY1.iFn = 0;
}

void ScHY1_ProcList(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScHY1.stt)
	{
		case SCRN_S0_INTRO:		ScHY1Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScHY1Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScHY1Stt_S2DttEv(evt, key);			break;
		default:				lScHY1.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

