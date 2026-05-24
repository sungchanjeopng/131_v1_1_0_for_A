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
#include "dp_screen_info.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_info.h"
// self
#include "screen_inf1_list.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL1L_LS lScIf1;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScPr1Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScPR1] Goto (L0)");
	INPU_ClrKeyEvt(evt);

	DpIF0_FncIntro();
	lScIf1.stt = SCRN_S0_INTRO;
	ScINF_SetLayer(SCRN_L0_FUNC);
}

void ScPr1Evt_KeyPrev(U08 evt)
{
#if 1
	DpSTR_DebugExp(1, 1, "[ScPR1] PREV (None)");
	INPU_ClrKeyEvt(evt);

#else
	DpSTR_DebugExp(1, 1, "[ScPR1] PREV (List--)");
	INPU_ClrKeyEvt(evt);

	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:
			if(lScIf1.iFn <= ScINF_L00_TX_WAVE)		lScIf1.iFn = ScINF_LST_NUM - 1;
			else									lScIf1.iFn -= 1;
			break;

		case MnFTR_SS_DUAL:
			if(lScIf1.iFn <= ScINF_L00_TX_WAVE)		lScIf1.iFn = ScINF_LST_NUM;
			else									lScIf1.iFn -= 1;
			break;
	}

	DpIF1_LstUpdat();
#endif
	lScIf1.stt = SCRN_S1_STDBY;
}

void ScPr1Evt_KeyNext(U08 evt)
{
#if 1
	DpSTR_DebugExp(1, 1, "[ScPR1] NEXT (None)");
	INPU_ClrKeyEvt(evt);

#else
	DpSTR_DebugExp(1, 1, "[ScPR1] NEXT (List++)");
	INPU_ClrKeyEvt(evt);

	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:	if(++lScIf1.iFn >=  ScINF_LST_NUM)			lScIf1.iFn = ScINF_L00_TX_WAVE;		break;
		case MnFTR_SS_DUAL:		if(++lScIf1.iFn >= (ScINF_LST_NUM+1))		lScIf1.iFn = ScINF_L00_TX_WAVE;		break;
	}
	
	DpIF1_LstUpdat();
#endif
	lScIf1.stt = SCRN_S1_STDBY;
}

void ScPr1Evt_KeyEnter(U08 evt)
{
#if 0
	DpSTR_DebugExp(1, 1, "[ScPR1] Goto L2");
	INPU_ClrKeyEvt(evt);

	switch(lScIf1.iFn)
	{ 
		case ScINF_OPT_NUM:
			ScINF_PrSet_Value(!ScINF_PrGet_Chnnl());
			DpIF0_FncIntro();
			lScIf1.stt = SCRN_S0_INTRO;
			ScINF_SetLayer(SCRN_L0_FUNC);
			break;

		case ScINF_F01_TX_WAVE:
		default:
			lScIf1.stt = SCRN_S1_STDBY;
			break;
	}
#endif
}

void ScPr1Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScPR1] Key - Invalid");
	INPU_ClrKeyEvt(evt);

	lScIf1.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScPr1Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	DpIF1_LstIntro();

	lScIf1.stt = SCRN_S1_STDBY;

	lScIf1.iFn = ScINF_OPT_MIN;
}

void ScPr1Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScPR1] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScPR1] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScPR1] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScPR1] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScPR1] Key - LONG");			break;
		default:
			DpIF0_FncStdBy();

			if(lScIf1.fSb)
				return;
			lScIf1.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScPR1] STBY - Pending");
			return;
	}

	lScIf1.stt = SCRN_S2_DTT_E;
	lScIf1.fSb = _F_F;
}

void ScPr1Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScPr1Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScPr1Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScPr1Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScPr1Evt_KeyEnter(evt);			break;
				default:				ScPr1Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScPR1] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScPR1] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScIF1_GetIdxFunc(void)		{	return lScIf1.iFn;				}
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScIF1_InitList(void)
{
	lScIf1.stt = SCRN_S0_INTRO;
	lScIf1.iFn = ScINF_OPT_MIN;
	lScIf1.fSb = _F_F;
}

void ScIF1_ProcList(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScIf1.stt)
	{
		case SCRN_S0_INTRO:		ScPr1Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScPr1Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScPr1Stt_S2DttEv(evt, key);			break;
		default:				lScIf1.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

