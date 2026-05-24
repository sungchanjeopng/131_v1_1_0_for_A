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
#include "dp_screen_hybrid.h"
// menu
#include "menu_factory.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_hyb1_list.h"
// self
#include "screen_hyb2_value.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL2V_LS lScHY2;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
#if 0
void ScHY2Evt_UpDn(U08 key, S32 min, S32 max)
{
	S32 dig_min = 0;
	S32 dig_max = log10(max);

	switch(lScHY2.updn_mod)
	{
		case SCRN_L2_UPDN_IDLE:
			switch(key)
			{
				case KEY_IDX_PREV:
					if(--lScHY2.val < min)		lScHY2.val = max;
					break;
				case KEY_IDX_NEXT:
					if(++lScHY2.val > max)		lScHY2.val = min;
					break;
				default:
					break;
			}
			break;
		case SCRN_L2_UPDN_DIG:
			switch(key)
			{
				case KEY_IDX_PREV:
					if(++lScHY2.updn_dig > dig_max) 	lScHY2.updn_dig = dig_min;
					break;
				case KEY_IDX_NEXT:
					if(--lScHY2.updn_dig < dig_min) 	lScHY2.updn_dig = dig_max;
					break;
				default:
					break;
			}
			break;
		case SCRN_L2_UPDN_DIG_VALUE:
			switch(key)
			{
				case KEY_IDX_PREV:
					switch(lScHY2.updn_dig)
					{
						case 4:	lScHY2.val-=10000;	break;
						case 3:	lScHY2.val-=1000;	break;
						case 2:	lScHY2.val-=100;	break;
						case 1:	lScHY2.val-=10;		break;
						case 0:	lScHY2.val-=1;		break;
						default:	break;				
					}
					if(lScHY2.val<min)	lScHY2.val= min;
					break;
				case KEY_IDX_NEXT:
					switch(lScHY2.updn_dig)
					{
						case 4:	lScHY2.val+=10000;	break;
						case 3:	lScHY2.val+=1000;	break;
						case 2:	lScHY2.val+=100;	break;
						case 1:	lScHY2.val+=10;		break;
						case 0: lScHY2.val+=1;		break;
						default:	break;				
					}	
					if(lScHY2.val>max)	lScHY2.val= max;
					break;
				default:	break;
			}
			break;
		default:	break;


	}

}

void ScHY2Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[HYVAL] FUNC - Goto L2");
	INPU_ClrKeyEvt(evt);

	if(lScHY2.updn_mod == SCRN_L2_UPDN_DIG_VALUE)
	{
		lScHY2.updn_mod = SCRN_L2_UPDN_DIG;	
		lScHY2.stt = SCRN_S1_STDBY;
		DpSCR_UpdtBttn(SCRN_L2_VALU);
		DpHY2_ValUpdat();
		return;
	}

	DpHY0_FncIntro();
	lScHY2.stt = SCRN_S0_INTRO;
	ScHYB_SetLayer(SCRN_L1_LIST);
}

void ScHY2Evt_KeyPrev(U08 evt)
{
	U08 iFn = ScHY1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[HYVAL] PREV - Value--");
	INPU_ClrKeyEvt(evt);

	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		ScHY2Evt_UpDn(KEY_IDX_PREV,ScHYB_LVL_MIN,ScHYB_LVL_MAX);					break;
		case ScHYB_F01_UNIT_:		ScHY2Evt_UpDn(KEY_IDX_PREV,ScHYB_UNIT_MIN,ScHYB_UNIT_MAX);					break;
		case ScHYB_F02_S_DEP:		ScHY2Evt_UpDn(KEY_IDX_PREV,ScHYB_SS_DEP_MIN,ScHYB_SS_DEP_MAX);				break;
		case ScHYB_F03_DEADZ:		ScHY2Evt_UpDn(KEY_IDX_PREV,ScHYB_DEADZ_MIN,ScHYB_DEADZ_MAX);				break;
		case ScHYB_F04_T_DEP:		ScHY2Evt_UpDn(KEY_IDX_PREV,ScHYB_TK_DEP_MIN,ScHYB_TK_DEP_MAX);				break;
		case ScHYB_FNC_NUMB:		lScHY2.val ^= 1;															break;
	}

	DpHY2_ValUpdat();
	lScHY2.stt = SCRN_S1_STDBY;
}

void ScHY2Evt_KeyNext(U08 evt)
{
	U08 iFn = ScHY1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[HYVAL] NEXT - Value++");
	INPU_ClrKeyEvt(evt);
	
	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		ScHY2Evt_UpDn(KEY_IDX_NEXT,ScHYB_LVL_MIN,ScHYB_LVL_MAX);					break;
		case ScHYB_F01_UNIT_:		ScHY2Evt_UpDn(KEY_IDX_NEXT,ScHYB_UNIT_MIN,ScHYB_UNIT_MAX);					break;
		case ScHYB_F02_S_DEP:		ScHY2Evt_UpDn(KEY_IDX_NEXT,ScHYB_SS_DEP_MIN,ScHYB_SS_DEP_MAX);				break;
		case ScHYB_F03_DEADZ:		ScHY2Evt_UpDn(KEY_IDX_NEXT,ScHYB_DEADZ_MIN,ScHYB_DEADZ_MAX);				break;
		case ScHYB_F04_T_DEP:		ScHY2Evt_UpDn(KEY_IDX_NEXT,ScHYB_TK_DEP_MIN,ScHYB_TK_DEP_MAX);				break;
		case ScHYB_FNC_NUMB:		lScHY2.val ^= 1;															break;
	}


	DpHY2_ValUpdat();
	lScHY2.stt = SCRN_S1_STDBY;
}

void ScHY2Evt_KeyEnter(U08 evt)
{
	U08 iFn = ScHY1_GetIdxFunc();

	DpSTR_DebugExp(1, 1, "[HYVAL] ENTER - Save");
	INPU_ClrKeyEvt(evt);

	if(lScHY2.updn_mod==SCRN_L2_UPDN_DIG)
	{
		lScHY2.updn_mod = SCRN_L2_UPDN_DIG_VALUE;	
		lScHY2.stt = SCRN_S1_STDBY; 		
		DpSCR_UpdtBttn(SCRN_L2_VALU);
		DpHY2_ValUpdat();
		return;
	}

	ScHYB_PrSet_Value(iFn,lScHY2.val);

	DpHY0_FncIntro();
	lScHY2.stt = SCRN_S0_INTRO;
	ScHYB_SetLayer(SCRN_L1_LIST);
}

void ScHY2Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[HYVAL] Key - Invalid");
	INPU_ClrKeyEvt(evt);

	lScHY2.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScHY2Stt_S0Intro(U08 evt)
{
	U08 iCh = ScHYB_PrGet_Chnnl();
	U08 iFn = ScHY1_GetIdxFunc();

	INPU_ClrKeyEvt(evt);
	lScHY2.updn_mod = SCRN_L2_UPDN_IDLE;

	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		lScHY2.val = (S32)ScHYB_PrGet_LvTyp(); 		break;
		case ScHYB_F01_UNIT_:		lScHY2.val = (S32)ScHYB_PrGet_Unit_(); 		break;
		case ScHYB_F02_S_DEP:		lScHY2.val = ScHYB_PrGet_Value(iCh, iFn);	lScHY2.min = ScHYB_SS_DEP_MIN;	lScHY2.max = ScHYB_SS_DEP_MAX;	break;
		case ScHYB_F03_DEADZ:		lScHY2.val = ScHYB_PrGet_Value(iCh, iFn);	lScHY2.min = ScHYB_DEADZ_MIN;	lScHY2.max = ScHYB_DEADZ_MAX;	lScHY2.updn_mod = SCRN_L2_UPDN_DIG;	break;
		case ScHYB_F04_T_DEP:		lScHY2.val = ScHYB_PrGet_Value(iCh, iFn);	lScHY2.min = ScHYB_TK_DEP_MIN;	lScHY2.max = ScHYB_TK_DEP_MAX;	lScHY2.updn_mod = SCRN_L2_UPDN_DIG;	break;
		// Dual Sensor
		case ScHYB_FNC_NUMB:		lScHY2.val = (S32)ScHYB_PrGet_Chnnl(); 		break;
	}

	DpHY2_ValIntro();
	DpSCR_UpdtBttn(SCRN_L2_VALU);
	lScHY2.stt = SCRN_S1_STDBY;
}

void ScHY2Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:			DpSTR_DebugExp(0, 1, "[HYVAL] Key - PUSH");			break;
		case KEY_EVT_DTT_L:			DpSTR_DebugExp(0, 1, "[HYVAL] Key - DTT_L");		break;
		case KEY_EVT_SHORT:			DpSTR_DebugExp(0, 1, "[HYVAL] Key - SHORT");		break;
		case KEY_EVT_REPEAT:		DpSTR_DebugExp(0, 1, "[HYVAL] Key - REPEAT");		break;
		case KEY_EVT_LONG:			DpSTR_DebugExp(0, 1, "[HYVAL] Key - LONG");			break;
		default:
			if(lScHY2.fSb)
				return;
			lScHY2.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[HYVAL] STBY - Pending");
			return;
	}

	lScHY2.stt = SCRN_S2_DTT_E;
	lScHY2.fSb = _F_F;
}

void ScHY2Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:		ScHY2Evt_KeyFunc(evt);			break;
				case KEY_IDX_PREV:		ScHY2Evt_KeyPrev(evt);			break;
				case KEY_IDX_NEXT:		ScHY2Evt_KeyNext(evt);			break;
				case KEY_IDX_ENTER:		ScHY2Evt_KeyEnter(evt);			break;
				default:				ScHY2Evt_KeyInvalid(evt);		break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[HYVAL] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[HYVAL] Evt - Default");		break;
	}
}

#endif

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
S32 ScHY2_GetValue(void)					{	return lScHY2.val;				}
S32 ScHY2_GetMax(void)						{	return lScHY2.max;				}
S32 ScHY2_GetMin(void)						{	return lScHY2.min;				}
U08 ScHY2_GetUpdnMod(void)					{	return lScHY2.updn_mod;			}
S32 ScHY2_GetUpdnDig(void)					{	return lScHY2.updn_dig;			}

// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScHY2_InitValu(void)
{
	lScHY2.stt = SCRN_S0_INTRO;
	lScHY2.fSb = _F_F;
	
	lScHY2.min = 0;
	lScHY2.max = 0;
	lScHY2.val = 0;

	lScHY2.updn_mod = SCRN_L2_UPDN_IDLE;
	lScHY2.updn_dig = 0;

}

void ScHY2_ProcValu(void)
{
#if 0
	switch(lScHY2.stt)
	{
		case SCRN_S0_INTRO:		ScHY2Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScHY2Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScHY2Stt_S2DttEv(evt, key);			break;
		default:				lScHY2.stt = SCRN_S0_INTRO; 		break;
	}
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

