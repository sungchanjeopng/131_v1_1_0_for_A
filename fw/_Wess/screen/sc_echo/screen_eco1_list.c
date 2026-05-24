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
#include "dp_screen_echo.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_echo.h"
// self
#include "screen_eco1_list.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL1L_LS lScEc1;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScEc1Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEc1] EXIT (L0)");
	INPU_ClrKeyEvt(evt);

	lScEc1.stt = SCRN_S0_INTRO;
	ScECH_SetLayer(SCRN_L0_FUNC);
}

void ScEc1Evt_KeyPrev(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEc1] PREV (Item--)");
	INPU_ClrKeyEvt(evt);
	U08 type = MnFTR_PrGet_SsChn();

	if(type == MnFTR_SS_DUAL)
	{
		switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:
				if(lScEc1.iFn == ScECO_REAL_SEL_MIN)		lScEc1.iFn = ScECO_REAL_SEL_MAX;
				else										lScEc1.iFn -= 1;
				break;
			case ScECO_TYPE_AVG:
				if(lScEc1.iFn == ScECO_AVG_SEL_MIN)			lScEc1.iFn = ScECO_AVG_SEL_MAX;
				else										lScEc1.iFn -= 1;
				break;
			default:			
				break;
		}
	}
	else if (type == MnFTR_SS_SINGLE)
	{
		switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:
				if(lScEc1.iFn <= ScECO_REAL_SEL_MIN+1) 		lScEc1.iFn = ScECO_REAL_SEL_MAX;
				else										lScEc1.iFn -= 1;
				break;
			case ScECO_TYPE_AVG:
				if(lScEc1.iFn <= ScECO_AVG_SEL_MIN+1) 		lScEc1.iFn = ScECO_AVG_SEL_MAX;
				else										lScEc1.iFn -= 1;
				break;
			default:			
				break;
		}
	}
	
	lScEc1.stt = SCRN_S1_STDBY;
	DpEC1_LstUpdat();
}

void ScEc1Evt_KeyNext(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEc1] NEXT (Item++)");
	INPU_ClrKeyEvt(evt);

	U08 type = MnFTR_PrGet_SsChn();

	if(type == MnFTR_SS_DUAL)
	{
		switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:		if(++lScEc1.iFn >  ScECO_REAL_SEL_MAX)		lScEc1.iFn = ScECO_REAL_SEL_MIN;	break;
			case ScECO_TYPE_AVG:		if(++lScEc1.iFn >  ScECO_AVG_SEL_MAX)		lScEc1.iFn = ScECO_AVG_SEL_MIN;		break;
		}
	}
	else if (type == MnFTR_SS_SINGLE)
	{
		switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:		if(++lScEc1.iFn >  ScECO_REAL_SEL_MAX)		lScEc1.iFn = ScECO_REAL_SEL_MIN+1;	break;
			case ScECO_TYPE_AVG:		if(++lScEc1.iFn >  ScECO_AVG_SEL_MAX)		lScEc1.iFn = ScECO_AVG_SEL_MIN+1; 	break;
		}
	}
	
	lScEc1.stt = SCRN_S1_STDBY;
	DpEC1_LstUpdat();
}

void ScEc1Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEc1] ENTER (L2)");
	INPU_ClrKeyEvt(evt);
	
	switch(lScEc1.iFn)
	{	// Page #1
		case ScECO_REAL_CH_SEL:		
			ScECH_PrSet_Value(!ScECH_PrGet_Chnnl());
			lScEc1.stt = SCRN_S0_INTRO;
			break;
		default:					
			lScEc1.stt = SCRN_S0_INTRO; 	
			ScECH_SetLayer(SCRN_L2_VALU);		
			break;
	}
	
}
void ScEc1Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEc1] Key (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScEc1.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScEc1Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	DpEC0_FncIntro();
	DpEC1_LstIntro();
	DpSCR_UpdtBttn(SCRN_L1_LIST);
	ScECH_SetSave(ScECO_SAVE_OFF);
	
	lScEc1.stt = SCRN_S1_STDBY;
}

void ScEc1Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScEc1] Key (PUSH)");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScEc1] Key (DTT_L)");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScEc1] Key (SHORT)");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScEc1] Key (REPEAT)");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScEc1] Key (LONG)");			break;
		default:
			DpEC0_FncStdBy(0);

			if(lScEc1.fSb)
				return;
			lScEc1.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScEc1] STBY - Pending");
			return;
	}

	lScEc1.stt = SCRN_S2_DTT_E;
	lScEc1.fSb = _F_F;
}

void ScEc1Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_DTT_L:
			if(key==(KEY_IDX_PREV|KEY_IDX_NEXT))
			{
				if(lScEc1.iFn==ScECO_REAL_CH_SEL)
				{
					ScECH_SetSave(ScECO_SAVE_ON);
					DpEC0_FncStdBy(0);
				}	
			}
			INPU_ClrKeyEvt(KEY_EVT_NONE);
			lScEc1.stt = SCRN_S1_STDBY;
			break;	
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			ScECH_SetSave(ScECO_SAVE_OFF);
			switch(key)
			{
				case KEY_IDX_MENU:			ScEc1Evt_KeyFunc(evt);					break;
				case KEY_IDX_PREV:			ScEc1Evt_KeyPrev(evt);					break;
				case KEY_IDX_NEXT:			ScEc1Evt_KeyNext(evt);					break;
				case KEY_IDX_ENTER:			ScEc1Evt_KeyEnter(evt);					break;
				default:					ScEc1Evt_KeyInvalid(evt);				break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScEc1] Evt (NONE)");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScEc1] Evt (Invalid)");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScEC1_GetIdxFunc(void)		{	return lScEc1.iFn;				}
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScEC1_InitList(void)
{
	U08 type = MnFTR_PrGet_SsChn();

	if(type == MnFTR_SS_DUAL)
		lScEc1.iFn = ScECO_REAL_CH_SEL;
	else if(type == MnFTR_SS_SINGLE)
		lScEc1.iFn = ScECO_REAL_CH_SEL+1;

	lScEc1.stt = SCRN_S0_INTRO;
	lScEc1.fSb = _F_F;
	ScECH_SetSave(ScECO_SAVE_OFF);
}

void ScEC1_ProcList(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScEc1.stt)
	{
		case SCRN_S0_INTRO:		ScEc1Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScEc1Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScEc1Stt_S2DttEv(evt, key);			break;
		default:				lScEc1.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

