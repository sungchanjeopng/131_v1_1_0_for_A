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
#include "disp_color.h"
#include "disp_string.h"
#include "disp_titlebar.h"
// disp - screen
#include "dp_screen_echo.h"
#include "dp_screen_calib.h"
// screen
#include "screen_main.h"
#include "screen_calib.h"
// menu
#include "menu_factory.h"
// self
#include "screen_clb0_func.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL0F_LS lScCl0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event - Key Action
//------------------------------------------------------------------------------------------------------------------------------
void ScCl0Evt_KeyFunc(U08 evt)
{
	DpCLB_Set_Trend_flag(_F_T);
	DpSTR_DebugExp(1, 1, "[ScCL0] Goto Menu");
	INPU_ClrKeyEvt(evt);

	lScCl0.stt = SCRN_S0_INTRO;
	APP_SetMode(APP_MD1_MENU);

}

void ScCl0Evt_KeyPrev(U08 evt)
{
	DpCLB_Set_Trend_flag(_F_T);

	DpSTR_DebugExp(1, 1, "[ScCL0] Goto ScHYB");
	INPU_ClrKeyEvt(evt);

	lScCl0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P3_INFO);

}

void ScCl0Evt_KeyNext(U08 evt)
{
	DpCLB_Set_Trend_flag(_F_T);

	DpSTR_DebugExp(1, 1, "[ScCL0] Goto ScPRM");
	INPU_ClrKeyEvt(evt);

	lScCl0.stt = SCRN_S0_INTRO;
	SCRN_SetPage(SCRN_P0_FRONT);

}

void ScCl0Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScCL0] Goto MENU");
	INPU_ClrKeyEvt(evt);
	U08 type = MnFTR_PrGet_SsChn();

	if(type == MnFTR_SS_SINGLE)	
		return;

	ScCLB_SetCh(!ScCLB_GetCh());

	DpCLB_Set_Trend_flag(_F_T);


	DpClbLvl_StrChnnl();

	lScCl0.stt = SCRN_S0_INTRO;

	//ScCLB_SetLayer(SCRN_L1_LIST);	
}

void ScCl0Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScCL0] Evt (Invalid)");
	INPU_ClrKeyEvt(evt);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScCl0Stt_S0Intro(U08 evt)
{
	ScCLB_InitMain();

	DpCB0_FncIntro();

	INPU_ClrKeyEvt(evt);
	lScCl0.stt = SCRN_S1_STDBY;
}

void ScCl0Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScCL0] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScCL0] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScCL0] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScCL0] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScCL0] Key - LONG");			break;
		default:
			DpCB0_FncStdBy(0);
			if(lScCl0.fSb)
				return;
			lScCl0.fSb = _F_T;

			DpSTR_DebugExp(0, 1, "[ScCL0] Key - Pending");
			return;
	}

	lScCl0.stt = SCRN_S2_DTT_E;
	lScCl0.fSb = _F_F;
}

void ScCl0Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScCl0Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScCl0Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScCl0Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScCl0Evt_KeyEnter(evt);			break;
				default:				ScCl0Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScCL0] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScCL0] Evt - Default");		break;
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
void ScCB0_InitFunc(void)
{
	lScCl0.stt = SCRN_S0_INTRO;
	lScCl0.fSb = _F_F;
}

void ScCB0_ProcFunc(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScCl0.stt)
	{
		case SCRN_S0_INTRO:		ScCl0Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScCl0Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScCl0Stt_S2DttEv(evt, key); 		break;
		default:				lScCl0.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

