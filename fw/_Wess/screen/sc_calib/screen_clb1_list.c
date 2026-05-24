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
#include "disp_color.h"
#include "disp_string.h"
#include "disp_titlebar.h"
// disp - screen
#include "dp_screen_echo.h"
#include "dp_screen_calib.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
// self
#include "screen_clb1_list.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL1L_LS lScCl1;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScCl1Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEc1] EXIT (L0)");
	INPU_ClrKeyEvt(evt);

	lScCl1.stt = SCRN_S0_INTRO;
	ScCLB_SetLayer(SCRN_L0_FUNC);

}

void ScCl1Evt_KeyPrev(U08 evt)
{
	DpCLB_Set_Trend_flag(_F_T);

#if 0
	if(lScCl1.iFn == ScCLB_ITM_I00) 		lScCl1.iFn = ScCLB_FNC_NUM - 1;
	else									lScCl1.iFn -= 1;
#endif
	DpSTR_DebugExp(1, 1, "[ScCL1] PREV (Item--)");
	DpCB1_LstUpdat();

	INPU_ClrKeyEvt(evt);
	lScCl1.stt = SCRN_S1_STDBY;
}

void ScCl1Evt_KeyNext(U08 evt)
{
	DpCLB_Set_Trend_flag(_F_T);

#if 0
	if(++lScCl1.iFn >=	ScCLB_FNC_NUM)
		lScCl1.iFn = ScCLB_ITM_I00;
#endif
	DpSTR_DebugExp(1, 1, "[ScCL1] NEXT (Item++)");
	DpCB1_LstUpdat();

	INPU_ClrKeyEvt(evt);
	lScCl1.stt = SCRN_S1_STDBY;
}

void ScCl1Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScCL1] ENTER (L2)");
#if 0
	switch(lScCl1.iFn)
	{
		case ScCLB_F00_FREQ:
		case ScCLB_F01_TX_WAV:
		case ScCLB_F02_RX_GAIN:	
		case ScCLB_F03_RX_TRANS:		
		case ScCLB_F04_RX_AMP:
		case ScCLB_F05_TVG_fEN:		
		case ScCLB_F06_TVG_CUSTOM:	lScCl1.stt = SCRN_S0_INTRO; 	ScCLB_SetLayer(SCRN_L2_VALU);		break;
		default:					lScCl1.stt = SCRN_S1_STDBY; 	break;
	}
#endif

	ScCLB_SetCh(!ScCLB_GetCh());

	DpCLB_Set_Trend_flag(_F_T);


	DpClbLvl_StrChnnl();

	//DpCB1_LstUpdat();

	INPU_ClrKeyEvt(evt);

	lScCl1.stt = SCRN_S1_STDBY;

}

void ScCl1Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScCL1] Key (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScCl1.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScCl1Stt_S0Intro(U08 evt)
{
	INPU_ClrKeyEvt(evt);
	DpCB1_LstIntro();

	lScCl1.stt = SCRN_S1_STDBY;
}

void ScCl1Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScCL1] Key (PUSH)");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScCL1] Key (DTT_L)");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScCL1] Key (SHORT)");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScCL1] Key (REPEAT)");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScCL1] Key (LONG)");			break;
		default:
			DpCB0_FncStdBy(0);

			if(lScCl1.fSb)
				return;
			lScCl1.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScCL1] STBY - Pending");
			return;
	}

	lScCl1.stt = SCRN_S2_DTT_E;
	lScCl1.fSb = _F_F;
}

void ScCl1Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			ScCl1Evt_KeyFunc(evt);					break;
				case KEY_IDX_PREV:			ScCl1Evt_KeyPrev(evt);					break;
				case KEY_IDX_NEXT:			ScCl1Evt_KeyNext(evt);					break;
				case KEY_IDX_ENTER:			ScCl1Evt_KeyEnter(evt);					break;
				default:					ScCl1Evt_KeyInvalid(evt);				break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScCL1] Evt (NONE)");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScCL1] Evt (Invalid)");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScCB1_GetIdxFunc(void)			{	return lScCl1.iFn;				}
// Set
void ScCB1_SetIdxFunc(U08 iFn)		{	lScCl1.iFn = iFn;				}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScCB1_InitList(void)
{
	lScCl1.stt = SCRN_S0_INTRO;
	lScCl1.fSb = _F_F;
	lScCl1.iFn = ScCLB_OPT_NUM;
}

void ScCB1_ProcList(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScCl1.stt)
	{
		case SCRN_S0_INTRO:		ScCl1Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScCl1Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScCl1Stt_S2DttEv(evt, key);			break;
		default:				lScCl1.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

