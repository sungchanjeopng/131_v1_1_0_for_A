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
#include "dp_screen_calib.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_echo.h"
#include "screen_calib.h"
#include "screen_clb1_list.h"
// self
#include "screen_clb2_value.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL2V_LS lScCb2;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScCb2Evt_KeyFunc(U08 evt)
{
#if 0
	U08 iFn = ScCB1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[ScCB2] Goto L1");
	INPU_ClrKeyEvt(evt);

	switch(iFn)
	{
		case ScCLB_F06_TVG_CUSTOM:
			switch(lScCb2.sel_setp)
			{
				case SCRN_L2_SEL_STEP0: 	break;
				case SCRN_L2_SEL_STEP1:		lScCb2.sel_setp = SCRN_L2_SEL_STEP0;	lScCb2.stt = SCRN_S0_INTRO; return;
				default:					break;
			}
			break;
		default:							break;
	}	


	lScCb2.stt = SCRN_S0_INTRO;
	DpCB2_ValUpdat(_F_T);
	ScCLB_SetLayer(SCRN_L1_LIST);
#endif
}

void ScCb2Evt_KeyPrev(U08 evt)
{
#if 0
	DpSTR_DebugExp(1, 1, "[ScCB2] PREV (Value--)");
	INPU_ClrKeyEvt(evt);

	DpCB2_ValUpdat(_F_T);

	switch(ScCB1_GetIdxFunc())
	{
		case ScCLB_F00_FREQ:		if(--lScCb2.val < ScCLB_FREQ_MIN)		lScCb2.val = ScCLB_FREQ_MAX;			break;
		case ScCLB_F01_TX_WAV:		if(--lScCb2.val < ScCLB_TX_WAV_MIN)		lScCb2.val = ScCLB_TX_WAV_MAX;			break;
		case ScCLB_F02_RX_GAIN:		if(--lScCb2.val < ScCLB_RX_GAIN_MIN)	lScCb2.val = ScCLB_RX_GAIN_MAX;			break;
		case ScCLB_F03_RX_TRANS:	lScCb2.val-=ScCLB_RX_TRANS_CNT;			if(lScCb2.val < ScCLB_RX_TRANS_MIN)	lScCb2.val = ScCLB_RX_TRANS_MAX;		break;
		case ScCLB_F04_RX_AMP:		if(--lScCb2.val < ScCLB_RX_AMP_MIN)		lScCb2.val = ScCLB_RX_AMP_MAX;			break;
		case ScCLB_F05_TVG_fEN:		if(--lScCb2.val < ScCLB_TVG_MIN)		lScCb2.val = ScCLB_TVG_MAX;				break;
		case ScCLB_F06_TVG_CUSTOM:	
			switch(lScCb2.sel_setp)
			{
				case SCRN_L2_SEL_STEP0:	if(--lScCb2.val < ScCLB_TVG_X_AXIS_MIN) lScCb2.val = ScCLB_TVG_X_AXIS_MAX;				break;
				case SCRN_L2_SEL_STEP1:	if(--lScCb2.val < ScCLB_TVG_Y_VALUE_MIN) lScCb2.val = ScCLB_TVG_Y_VALUE_MAX;			break;
				default:				break;
			}
			break;
		// Not Define
		default:					lScCb2.val = MENU_VAL_INVALID;			break;
	}
	
	DpCB2_ValUpdat(_F_F);
	lScCb2.stt = SCRN_S1_STDBY;
#endif
}

void ScCb2Evt_KeyNext(U08 evt)
{
#if 0
	DpSTR_DebugExp(1, 1, "[ScCB2] NEXT (Value++)");
	INPU_ClrKeyEvt(evt);

	DpCB2_ValUpdat(_F_T);

	switch(ScCB1_GetIdxFunc())
	{	// TVG (OFF & ON)
		case ScCLB_F00_FREQ:		if(++lScCb2.val >  ScCLB_FREQ_MAX)			lScCb2.val = ScCLB_FREQ_MIN;					break;
		case ScCLB_F01_TX_WAV:		if(++lScCb2.val >  ScCLB_TX_WAV_MAX)		lScCb2.val = ScCLB_TX_WAV_MIN;					break;
		case ScCLB_F02_RX_GAIN:		if(++lScCb2.val > ScCLB_RX_GAIN_MAX)		lScCb2.val = ScCLB_RX_GAIN_MIN;					break;
		case ScCLB_F03_RX_TRANS:	lScCb2.val+=ScCLB_RX_TRANS_CNT;				if(lScCb2.val > ScCLB_RX_TRANS_MAX)	lScCb2.val = ScCLB_RX_TRANS_MIN;		break;
		case ScCLB_F04_RX_AMP:		if(++lScCb2.val > ScCLB_RX_AMP_MAX)			lScCb2.val = ScCLB_RX_AMP_MIN;					break;
		case ScCLB_F05_TVG_fEN:		if(++lScCb2.val > ScCLB_TVG_MAX)			lScCb2.val = ScCLB_TVG_MIN;						break;
		case ScCLB_F06_TVG_CUSTOM:
			switch(lScCb2.sel_setp)
			{
				case SCRN_L2_SEL_STEP0:	if(++lScCb2.val > ScCLB_TVG_X_AXIS_MAX) 	lScCb2.val = ScCLB_TVG_X_AXIS_MIN;				break;
				case SCRN_L2_SEL_STEP1:	if(++lScCb2.val > ScCLB_TVG_Y_VALUE_MAX) 	lScCb2.val = ScCLB_TVG_Y_VALUE_MIN;				break;
				default:				break;
			}
			break;
		// Not Define
		default:					lScCb2.val = MENU_VAL_INVALID;			break;
	}

	DpCB2_ValUpdat(_F_F);
	lScCb2.stt = SCRN_S1_STDBY;
#endif
}

void ScCb2Evt_KeyEnter(U08 evt)
{
#if 0
	U08 iFn = ScCB1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[ScCB2] ENTER (Save)");
	INPU_ClrKeyEvt(evt);

	ScCLB_PrSet_Value(lScCb2.val);
	
	switch(iFn)
	{
		case ScCLB_F06_TVG_CUSTOM:
			switch(lScCb2.sel_setp)
			{
				case SCRN_L2_SEL_STEP0: 	lScCb2.sel_setp = SCRN_L2_SEL_STEP1;	lScCb2.stt = SCRN_S0_INTRO;	return;
				case SCRN_L2_SEL_STEP1:		lScCb2.sel_setp = SCRN_L2_SEL_STEP0;	lScCb2.stt = SCRN_S0_INTRO;	return;
				default:					break;
			}
			break;
		default:							break;
	}	
	
	ScCLB_SetLayer(SCRN_L1_LIST);

	DpCB2_ValUpdat(_F_T);
	lScCb2.stt = SCRN_S0_INTRO;
#endif
}

void ScCb2Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScCB2] Key (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScCb2.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScCb2Stt_S0Intro(U08 evt)
{
#if 0
	U08 iCh = ScECH_PrGet_Chnnl();
	U08 iFn = ScCB1_GetIdxFunc();

	INPU_ClrKeyEvt(evt);

	switch(iFn)
	{
		case ScCLB_F00_FREQ:
		case ScCLB_F01_TX_WAV:
		case ScCLB_F02_RX_GAIN:	
		case ScCLB_F03_RX_TRANS:			
		case ScCLB_F04_RX_AMP:
		case ScCLB_F05_TVG_fEN:
		case ScCLB_F06_TVG_CUSTOM:		lScCb2.val = (S32)ScCLB_PrGet_Value(iCh, iFn);		break;
		default:						lScCb2.val = MENU_VAL_INVALID;						break;
	}

	DpCB2_ValIntro();
	DpSCR_UpdtBttn(SCRN_L2_VALU);
	lScCb2.stt = SCRN_S1_STDBY;
#endif
}

void ScCb2Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[ScCB2] Key - PUSH");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[ScCB2] Key - DTT_L");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[ScCB2] Key - SHORT");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[ScCB2] Key - REPEAT");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[ScCB2] Key - LONG");			break;
		default:
			DpCB0_FncStdBy(0);

			if(lScCb2.fSb)
				return;
			lScCb2.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScCB2] STBY - Pending");
			return;
	}

	lScCb2.stt = SCRN_S2_DTT_E;
	lScCb2.fSb = _F_F;
}

void ScCb2Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			ScCb2Evt_KeyFunc(evt);					break;
				case KEY_IDX_PREV:			ScCb2Evt_KeyPrev(evt);					break;
				case KEY_IDX_NEXT:			ScCb2Evt_KeyNext(evt);					break;
				case KEY_IDX_ENTER:			ScCb2Evt_KeyEnter(evt);					break;
				default:					ScCb2Evt_KeyInvalid(evt);				break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScCB2] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScCB2] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
S32 ScCB2_GetValue(void)			{	return lScCb2.val;		}
U08 ScCB2_GetSelStep(void)			{	return lScCb2.sel_setp;	}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScCB2_InitValu(void)
{
	lScCb2.stt = SCRN_S0_INTRO;
	lScCb2.fSb = _F_F;
	lScCb2.val = 0;
	lScCb2.sel_setp = SCRN_L2_SEL_STEP0;
}

void ScCB2_ProcValu(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScCb2.stt)
	{
		case SCRN_S0_INTRO:		ScCb2Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScCb2Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScCb2Stt_S2DttEv(evt, key);			break;
		default:				lScCb2.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

