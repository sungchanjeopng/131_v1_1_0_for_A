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
// input
#include "input_main.h"
#include "input_key.h"
// display
#include "disp_string.h"
// disp - menu
#include "dp_menu_main.h"
#include "dp_menu_measure.h"
#include "dp_menu_output.h"
#include "dp_menu_data.h"
#include "dp_menu_system.h"
#include "dp_menu_engineer.h"
#include "dp_menu_factory.h"
// menu
#include "menu_main.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_data.h"
#include "menu_system.h"
#include "menu_engineer.h"
#include "menu_factory.h"
#include "menu_test.h"
#include "menu_main.h"
// self
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MnLY0_LS lMnLy0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local Functions - Event - Key Action
//------------------------------------------------------------------------------------------------------------------------------
void MnLy0Evt_KeyFunc(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY0] Goto SCREEN");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy0.stt = MENU_S0_INTRO;
	MENU_ExitMain();
}

void MnLy0Evt_KeyPrev(void)
{
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy0.stt = MENU_S0_INTRO;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (MEAR) - Goto Sc3 (SYST)");
			switch(MENU_GetFgHiddn())
			{
				case MENU_HIDDEN_IDLE:	MENU_SetSection(MENU_SC3_SYST);	break;
				case MENU_HIDDEN_ENGR:	MENU_SetSection(MENU_SC4_EGNR);	break;
				case MENU_HIDDEN_FCTR:	MENU_SetSection(MENU_SC6_TEST);	break;
			}
			break;
		case MENU_SC1_OUTP:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (OUTP) - Goto Sc0 (MEAS)");
			MENU_SetSection(MENU_SC0_MEAS);
			break;

		case MENU_SC2_DATA:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (DATA) - Goto Sc1 (OUTP)");
			MENU_SetSection(MENU_SC1_OUTP);
			break;

		case MENU_SC3_SYST:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (SYST) - Goto Sc2 (DATA)");
			MENU_SetSection(MENU_SC2_DATA);
			break;

		case MENU_SC4_EGNR:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (EGNR) - Goto Sc3 (SYST)");
			MENU_SetSection(MENU_SC3_SYST);
			break;

		case MENU_SC5_FCTR:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (FCTR) - Goto Sc4 (EGNR)");
			MENU_SetSection(MENU_SC4_EGNR);
			break;
		case MENU_SC6_TEST:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (TSET) - Goto Sc4 (EGNR)");
			MENU_SetSection(MENU_SC5_FCTR);
			break;
		default:
			DpSTR_DebugExp(1, 1, "[MnLY0] PREV (Invalid)");
			lMnLy0.stt = MENU_S1_STDBY;
			break;
	}
}

void MnLy0Evt_KeyNext(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY0] NEXT - Goto MnDAT");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy0.stt = MENU_S0_INTRO;

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (MEAR) - Goto Sc1 (OUTP)");
			MENU_SetSection(MENU_SC1_OUTP);
			break;

		case MENU_SC1_OUTP:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (OUTP) - Goto Sc2 (DATA)");
			MENU_SetSection(MENU_SC2_DATA);
			break;

		case MENU_SC2_DATA:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (DATA) - Goto Sc3 (SYST)");
			MENU_SetSection(MENU_SC3_SYST);
			break;

		case MENU_SC3_SYST:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (DATA) - Goto Sc0 (MEAS)");
			switch(MENU_GetFgHiddn())
			{
				case MENU_HIDDEN_IDLE:	MENU_SetSection(MENU_SC0_MEAS);	break;
				case MENU_HIDDEN_ENGR:	MENU_SetSection(MENU_SC4_EGNR);	break;
				case MENU_HIDDEN_FCTR:	MENU_SetSection(MENU_SC4_EGNR);	break;
			}
			break;
		case MENU_SC4_EGNR:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (EGNR) - Goto Sc5 (FCTR)");
			switch(MENU_GetFgHiddn())
			{
				case MENU_HIDDEN_IDLE:	MENU_SetSection(MENU_SC0_MEAS);	break;
				case MENU_HIDDEN_ENGR:	MENU_SetSection(MENU_SC0_MEAS);	break;
				case MENU_HIDDEN_FCTR:	MENU_SetSection(MENU_SC5_FCTR);	break;
			}
			break;
		case MENU_SC5_FCTR:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (FCTR) - Goto Sc0 (MEAS)");
			MENU_SetSection(MENU_SC6_TEST);
			break;
		case MENU_SC6_TEST:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (TEST) - Goto Sc0 (MEAS)");
			MENU_SetSection(MENU_SC0_MEAS);
			break;
		default:
			DpSTR_DebugExp(1, 1, "[MnLY0] NEXT (Invalid)");
			lMnLy0.stt = MENU_S1_STDBY;
			break;
	}
}

void MnLy0Evt_KeyEnter(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY0] ENTER - Goto Ly1");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:		MENU_SetLayer(MENU_L1_SUB_SCT);		break;
		case MENU_SC3_SYST:		MnLY1_SetSection(MnSYS_SUB_BASE); MENU_SetLayer(MENU_L2_ITEM);	break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:				MENU_SetLayer(MENU_L2_ITEM);		break;
	}

	lMnLy0.stt = MENU_S0_INTRO;
	MnLY2_SetIdxItem(0);
}

void MnLy0Evt_HidMnEn(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY0] SFK - Hidden Menu");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	MENU_SetFgHiddn(MENU_HIDDEN_ENGR);


	DpM0_IntroSct();
	lMnLy0.stt = MENU_S1_STDBY;
}

void MnLy0Evt_HidMnFa(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY0] SFK - Hidden Menu");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	MENU_SetFgHiddn(MENU_HIDDEN_FCTR);

	DpM0_IntroSct();
	lMnLy0.stt = MENU_S1_STDBY;
}



void MnLy0Evt_KeyInvalid(void)
{
	DpSTR_DebugExp(1, 1, "[MnLY0] Event (Key Invalid)");
	INPU_ClrKeyEvt(KEY_EVT_NONE);

	lMnLy0.stt = MENU_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void MnLy0Stt_S0Intro(void)
{
	INPU_ClrKeyEvt(KEY_EVT_NONE);
	MENU_InitSect(MENU_GetSection());
	DpM0_IntroSct();

	lMnLy0.stt = MENU_S1_STDBY;
}

void MnLy0Stt_S1StdBy(U08 evt)
{

	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[MnLY0] Key - PUSH");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[MnLY0] Key - DTT_L");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[MnLY0] Key - SHORT");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[MnLY0] Key - REPEAT");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[MnLY0] Key - LONG");			break;
		default:
			DpM0_StdBySct();

			if(!lMnLy0.fSb)
			{
				DpSTR_DebugExp(0, 1, "[MnLY0] STBY - Pending");
				lMnLy0.fSb = _F_T;
			}
			return;
	}

	lMnLy0.stt = MENU_S2_DTT_E;
	lMnLy0.fSb = _F_F;
}

void MnLy0Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_DTT_L:
			if(key==(KEY_IDX_PREV|KEY_IDX_MENU))
			{
				switch(MENU_GetSection())
				{
					case MENU_SC3_SYST: 
						MENU_SetSection(MENU_SC4_EGNR);
						MnLy0Evt_HidMnEn();		
						break;
					case MENU_SC0_MEAS: 	
						MENU_SetSection(MENU_SC5_FCTR);
						MnLy0Evt_HidMnFa(); 	
						break;
				}			
			}
			break;
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			MnLy0Evt_KeyFunc();				break;
				case KEY_IDX_PREV:			MnLy0Evt_KeyPrev();				break;
				case KEY_IDX_NEXT:			MnLy0Evt_KeyNext();				break;
				case KEY_IDX_ENTER:			MnLy0Evt_KeyEnter();			break;
				default:					MnLy0Evt_KeyInvalid();			break;
			}
			break;

		case KEY_EVT_NONE:			DpSTR_DebugExp(1, 1, "[MnLY0] Evt - NONE");			break;
		default:					DpSTR_DebugExp(1, 1, "[MnLY0] Evt - Invalid");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MnLY0_InitSection(void)
{
	lMnLy0.stt = MENU_S0_INTRO;
	lMnLy0.fSb = _F_F;
}

void MnLY0_ProcSection(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lMnLy0.stt)
	{
		case MENU_S0_INTRO:			MnLy0Stt_S0Intro();				break;
		case MENU_S1_STDBY:			MnLy0Stt_S1StdBy(evt);			break;
		case MENU_S2_DTT_E:			MnLy0Stt_S2DttEv(evt, key);		break;
		default:					lMnLy0.stt = MENU_S0_INTRO;		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

