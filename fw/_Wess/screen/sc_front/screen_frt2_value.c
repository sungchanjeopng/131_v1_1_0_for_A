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
#include "dp_screen_front.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_front.h"
#include "screen_frt1_list.h"
// self
#include "screen_frt2_value.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL2V_LS lScFr2;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScFr2Evt_UpDn(U08 key, S32 min, S32 max)
{
	S32 old = 0;
	S32 dig_min = 0;
	S32 dig_max = log10(max);

	switch(lScFr2.updn_mod)
	{
		case SCRN_L2_UPDN_IDLE:
			switch(key)
			{
				case KEY_IDX_PREV:
					if(--lScFr2.val < min)		lScFr2.val = max;
					break;
				case KEY_IDX_NEXT:
					if(++lScFr2.val > max)		lScFr2.val = min;
					break;
				default:
					break;
			}
			break;
		case SCRN_L2_UPDN_DIG:
			switch(key)
			{
				case KEY_IDX_PREV:
					if(++lScFr2.updn_dig > dig_max) 	lScFr2.updn_dig = dig_min;
					break;
				case KEY_IDX_NEXT:
					if(--lScFr2.updn_dig < dig_min) 	lScFr2.updn_dig = dig_max;
					break;
				default:
					break;
			}
			break;
		case SCRN_L2_UPDN_DIG_VALUE:
			old = lScFr2.val;
			switch(key)
			{
				case KEY_IDX_PREV:
					switch(lScFr2.updn_dig)
					{
						case 4:	lScFr2.val-=10000;	break;
						case 3:	lScFr2.val-=1000;	break;
						case 2:	lScFr2.val-=100;	break;
						case 1:	lScFr2.val-=10;		break;
						case 0:	lScFr2.val-=1;		break;
						default:	break;				
					}
					if(lScFr2.val<min)	lScFr2.val= old;
					break;
				case KEY_IDX_NEXT:
					switch(lScFr2.updn_dig)
					{
						case 4:	lScFr2.val+=10000;	break;
						case 3:	lScFr2.val+=1000;	break;
						case 2:	lScFr2.val+=100;	break;
						case 1:	lScFr2.val+=10;		break;
						case 0: lScFr2.val+=1;		break;
						default:	break;				
					}	
					if(lScFr2.val>max)	lScFr2.val= old;
										break;
				default:	break;
			}
			if(lScFr2.val < min)		lScFr2.val = min;
			if(lScFr2.val > max)		lScFr2.val = max;
			break;
		default:	break;


	}

}

void ScFr2Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[FrVAL] FUNC - Goto L2");
	INPU_ClrKeyEvt(evt);

	DpFR0_FncIntro();
	lScFr2.stt = SCRN_S0_INTRO;
	ScFRT_SetLayer(SCRN_L1_LIST);
}

void ScFr2Evt_KeyPrev(U08 evt)
{
#if 0
	U08 iFn = ScFR1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[FrVAL] PREV - Value--");
	INPU_ClrKeyEvt(evt);

#if 0
	switch(iFn)
	{
		case ScFRT_F00_CH:		lScFr2.val ^= 1;	break;
		default:				break;
	}
#endif
	DpFR2_ValUpdat();
	lScFr2.stt = SCRN_S1_STDBY;
#endif
}

void ScFr2Evt_KeyNext(U08 evt)
{
#if 0
	U08 iFn = ScFR1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[FrVAL] NEXT - Value++");
	INPU_ClrKeyEvt(evt);
#if 0
	switch(iFn)
	{
		case ScFRT_F00_CH:		lScFr2.val ^= 1;	break;
		default:				break;
	}
#endif
	DpFR2_ValUpdat();
	lScFr2.stt = SCRN_S1_STDBY;
#endif
}

void ScFr2Evt_KeyEnter(U08 evt)
{
#if 0
	U08 iFn = ScFR1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[FrVAL] ENTER - Save");
	INPU_ClrKeyEvt(evt);

#if 0
	switch(iFn)
	{
		case ScFRT_F00_CH:		ScHYB_PrSet_Value(ScHYB_FNC_NUMB,lScFr2.val);	break;
		default:				break;
	}
#endif
	DpFR0_FncIntro();
	lScFr2.stt = SCRN_S0_INTRO;
	ScFRT_SetLayer(SCRN_L1_LIST);
#endif
}

void ScFr2Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[FrVAL] Key - Invalid");
	INPU_ClrKeyEvt(evt);

	lScFr2.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScFr2Stt_S0Intro(U08 evt)
{

	INPU_ClrKeyEvt(evt);
	DpSCR_UpdtBttn(SCRN_L2_VALU);

#if 0
	switch(iFn)
	{
		case ScFRT_F00_CH:			lScFr2.val = (S32)ScHYB_PrGet_Chnnl(); 		break;
		// Dual Sensor
		default:					break;
	}
#endif
	DpFR2_ValIntro();
	DpSCR_UpdtBttn(SCRN_L2_VALU);
	lScFr2.stt = SCRN_S1_STDBY;
}

void ScFr2Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[FrVAL] Key - PUSH");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[FrVAL] Key - DTT_L");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[FrVAL] Key - SHORT");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[FrVAL] Key - REPEAT");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[FrVAL] Key - LONG");			break;
		default:
			if(lScFr2.fSb)
				return;
			lScFr2.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[FrVAL] STBY - Pending");
			return;
	}

	lScFr2.stt = SCRN_S2_DTT_E;
	lScFr2.fSb = _F_F;
}

void ScFr2Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScFr2Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScFr2Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScFr2Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScFr2Evt_KeyEnter(evt);			break;
				default:				ScFr2Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[FrVAL] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[FrVAL] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
S32 ScFR2_GetValue(void)					{	return lScFr2.val;				}
S32 ScFR2_GetMax(void)						{	return lScFr2.max;				}
S32 ScFR2_GetMin(void)						{	return lScFr2.min;				}
U08 ScFR2_GetUpdnMod(void)					{	return lScFr2.updn_mod;			}
S32 ScFR2_GetUpdnDig(void)					{	return lScFr2.updn_dig;			}

// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScFR2_InitValu(void)
{
	lScFr2.stt = SCRN_S0_INTRO;
	lScFr2.fSb = _F_F;
	
	lScFr2.min = 0;
	lScFr2.max = 0;
	lScFr2.val = 0;

	lScFr2.updn_mod = SCRN_L2_UPDN_IDLE;
	lScFr2.updn_dig = 0;

}

void ScFR2_ProcValu(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScFr2.stt)
	{
		case SCRN_S0_INTRO:		ScFr2Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScFr2Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScFr2Stt_S2DttEv(evt, key);			break;
		default:				lScFr2.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

