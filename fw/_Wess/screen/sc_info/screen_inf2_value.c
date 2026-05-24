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
#include "dp_screen_main.h"
#include "dp_screen_info.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_info.h"
#include "screen_inf1_list.h"
// self
#include "screen_inf2_value.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL2V_LS lScIf2;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScIf2Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScPR2] Goto L2");
	INPU_ClrKeyEvt(evt);

	DpIF0_FncIntro();
	lScIf2.stt = SCRN_S0_INTRO;
	ScINF_SetLayer(SCRN_L1_LIST);
}

void ScIf2Evt_KeyPrev(U08 evt)
{
#if 0
	U08 iFn = ScIF1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[ScPR2] PREV - Dec. Value");
	INPU_ClrKeyEvt(evt);
	DpIF2_ValUpdat(_F_F);

	switch(iFn)
	{
		case ScINF_F01_TX_WAVE:		if(lScIf2.val <= ScPRM_TX_CYC_SEC01)	lScIf2.val = ScPRM_TX_CYC_NUMB - 1;		break;
		case ScINF_LST_NUM:			lScIf2.val ^= 1;						break;
	}

	DpIF2_ValUpdat(_F_T);
	lScIf2.stt = SCRN_S1_STDBY;
#endif
}

void ScIf2Evt_KeyNext(U08 evt)
{
#if 0
	U08 iFn = ScIF1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[ScPR2] NEXT - Inc. Value");
	INPU_ClrKeyEvt(evt);
	DpIF2_ValUpdat(_F_F);

	switch(iFn)
	{
		case ScINF_F01_TX_WAVE:		if(++lScIf2.val >= ScPRM_TX_CYC_NUMB)	lScIf2.val = ScPRM_TX_CYC_SEC01;		break;
		case ScINF_LST_NUM:			lScIf2.val ^= 1;						break;
	}

	DpIF2_ValUpdat(_F_T);
	lScIf2.stt = SCRN_S1_STDBY;
#endif
}

void ScIf2Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScPR2] ENTER - Save");
	INPU_ClrKeyEvt(evt);

	ScINF_PrSet_Value(lScIf2.val);

	DpIF0_FncIntro();
	lScIf2.stt = SCRN_S0_INTRO;
	ScINF_SetLayer(SCRN_L1_LIST);
}

void ScIf2Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScPR2] Key - Invalid");
	INPU_ClrKeyEvt(evt);

	lScIf2.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScIf2Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);

	DpIF2_ValIntro();
	DpSCR_UpdtBttn(SCRN_L2_VALU);
	lScIf2.stt = SCRN_S1_STDBY;
}

void ScIf2Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScPR2] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScPR2] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScPR2] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScPR2] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScPR2] Key - LONG");			break;
		default:
			if(lScIf2.fSb)
				return;
			lScIf2.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScPR2] STBY - Pending");
			return;
	}

	lScIf2.stt = SCRN_S2_DTT_E;
	lScIf2.fSb = _F_F;
}

void ScIf2Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScIf2Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScIf2Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScIf2Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScIf2Evt_KeyEnter(evt);			break;
				default:				ScIf2Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScPR2] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScPR2] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
S32 ScIF2_GetValue(void)			{	return lScIf2.val;		}

// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScIF2_InitValu(void)
{
	lScIf2.stt = SCRN_S0_INTRO;
	lScIf2.fSb = _F_F;
	lScIf2.val = 0;
}

void ScIF2_ProcValu(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScIf2.stt)
	{
		case SCRN_S0_INTRO:		ScIf2Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScIf2Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScIf2Stt_S2DttEv(evt, key);			break;
		default:				lScIf2.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

