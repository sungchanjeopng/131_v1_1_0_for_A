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
#include "screen_eco2_value.h"
// menu
#include "menu_measure.h"
#include "menu_factory.h"
#include "menu_engineer.h"
// screen
#include "screen_main.h"
#include "screen_echo.h"
#include "screen_eco1_list.h"
// self
#include "screen_eco2_value.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScL2V_LS lScEc2;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Action API
//------------------------------------------------------------------------------------------------------------------------------
void ScEc2Evt_KeyFunc(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC2] Goto L1");
	INPU_ClrKeyEvt(evt);

	switch(lScEc2.updn_mod)
	{
		case SCRN_L2_UPDN_IDLE:
			break;
		case SCRN_L2_UPDN_DIG_VALUE:
			if(ScECH_GetType()==ScECO_TYPE_AVG)
				break;

			lScEc2.stt = SCRN_S1_STDBY;
			lScEc2.updn_mod = SCRN_L2_UPDN_DIG;
			DpEC2_ValUpdat();
			DpSCR_UpdtBttn(SCRN_L2_VALU);			
			return;
		case SCRN_L2_UPDN_DIG:
			break;
	}
	
	lScEc2.stt = SCRN_S0_INTRO;
	DpEC0_FncIntro();
	ScECH_SetLayer(SCRN_L1_LIST);
}

void ScEc2Evt_KeyPrev(U08 evt)
{
	U08 iFn = ScEC1_GetIdxFunc();
	U08 ch = ScECH_PrGet_Chnnl();
	U16 dead = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);	

	DpSTR_DebugExp(1, 1, "[ScEC2] PREV (Value--)");
	INPU_ClrKeyEvt(evt);

	DpEC2_ValUpdat();

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			switch(iFn)
			{	// Page #1
				case ScECO_REAL_ECHO_AMP:	if(--lScEc2.val < MnMS1_ECHO_AMP_MIN)	lScEc2.val = MnMS1_ECHO_AMP_MAX;		break;
				case ScECO_REAL_MEAS_RESET:	lScEc2.val=!lScEc2.val;															break;
				case ScECO_REAL_FREQ:		if(--lScEc2.val < MnMS1_FREQ_MIN)		lScEc2.val = MnMS1_FREQ_MAX;			break;
				case ScECO_REAL_EMPTY:	
				case ScECO_REAL_DEADZONE:	
					if(lScEc2.updn_mod==SCRN_L2_UPDN_DIG)
					{
						if(++lScEc2.updn_dig>3) 
							lScEc2.updn_dig  = 0;
					}
					else if(lScEc2.updn_mod==SCRN_L2_UPDN_DIG_VALUE)
					{
						switch(lScEc2.updn_dig)
						{
							case 3: if((lScEc2.val<1000) && (lScEc2.val>0)) lScEc2.val*=-1; else lScEc2.val-=1000;	break;
							case 2: if((lScEc2.val<100) && (lScEc2.val>0)) lScEc2.val*=-1;	else lScEc2.val-=100;	break;
							case 1: if((lScEc2.val<10) && (lScEc2.val>0)) lScEc2.val*=-1;	else lScEc2.val-=10;		break;
							case 0: lScEc2.val-=1;		break;
							default:	break;				
						}
						if(lScEc2.val<1)	lScEc2.val= 1;
					}
					break;
				case ScECO_REAL_TVG:		if(--lScEc2.val < MnEGN_TVG_MIN)		lScEc2.val = MnEGN_TVG_MAX;				break;
				default:					lScEc2.val = 9999;						break;
			}
			break;
		case ScECO_TYPE_AVG:
			switch(iFn)
			{
				case ScECO_AVG_THR_LIGHT:
					switch(MnMSR_CalGet_Ch_Value(ScECH_PrGet_Chnnl(), MnMS1_OPT_CH1_THR_LIGHT))
					{
						case MnMS1_THRESHOLD_AUTO:		
							lScEc2.val-=5;
							if(lScEc2.val < MnMS1_THR_VAL_AUTO_MIN)	lScEc2.val = MnMS1_THR_VAL_AUTO_MAX;		
							break;
						case MnMS1_THRESHOLD_MANUAL:
							if(--lScEc2.val < MnMS1_THR_VAL_MANUAL_MIN)	lScEc2.val = MnMS1_THR_VAL_MANUAL_MAX;		
							break;
						default:
							break;
					}
					break;
				case ScECO_AVG_THR_HEAVY:
					switch(MnMSR_CalGet_Ch_Value(ScECH_PrGet_Chnnl(), MnMS1_OPT_CH1_THR_HEAVY))
					{
						case MnMS1_THRESHOLD_AUTO:		
							lScEc2.val-=5;
							if(lScEc2.val < MnMS1_THR_VAL_AUTO_MIN) lScEc2.val = MnMS1_THR_VAL_AUTO_MAX;		
							break;
						case MnMS1_THRESHOLD_MANUAL:
							if(--lScEc2.val < MnMS1_THR_VAL_MANUAL_MIN) lScEc2.val = MnMS1_THR_VAL_MANUAL_MAX;		
							break;
						default:
							break;
					}
					break;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:
					switch(lScEc2.updn_mod)
					{
						case SCRN_L2_UPDN_DIG_VALUE:
							lScEc2.val-=13.5;
							if(lScEc2.val < 0)	lScEc2.val = 0;
							MsCAL_SetVl_ASF_R(ch,lScEc2.val);
							break;
						case SCRN_L2_UPDN_DIG:
							//MsCAL_SetVl_ASF_R(ch,0);
							switch(evt)
							{
								case KEY_EVT_REPEAT:
								case KEY_EVT_LONG:		lScEc2.val-=10; break;
								default:				lScEc2.val-=1;	break;
							}
							if(lScEc2.val < dead)	
								lScEc2.val = dead;
							break;
					}
					break;
				default:					break;
			}
			break;
		default:
			break;
	}

	DpEC2_ValUpdat();
	lScEc2.stt = SCRN_S1_STDBY;
}

void ScEc2Evt_KeyNext(U08 evt)
{
	U08 iFn = ScEC1_GetIdxFunc();
	U08 ch = ScECH_PrGet_Chnnl();
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 dead = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);	
	
	DpSTR_DebugExp(1, 1, "[ScEC2] NEXT (Value++)");
	INPU_ClrKeyEvt(evt);

	DpEC2_ValUpdat();

	switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:
				switch(iFn)
				{	// Page #1
					case ScECO_REAL_ECHO_AMP:	if(++lScEc2.val > MnMS1_ECHO_AMP_MAX)	lScEc2.val = MnMS1_ECHO_AMP_MIN;		break;
					case ScECO_REAL_MEAS_RESET: lScEc2.val=!lScEc2.val; 														break;
					case ScECO_REAL_FREQ:		if(++lScEc2.val > MnMS1_FREQ_MAX)		lScEc2.val = MnMS1_FREQ_MIN;			break;
					case ScECO_REAL_EMPTY:	
					case ScECO_REAL_DEADZONE:	
						if(lScEc2.updn_mod==SCRN_L2_UPDN_DIG)
						{
							if(--lScEc2.updn_dig<0) 
								lScEc2.updn_dig  = 3;
						}
						else if(lScEc2.updn_mod==SCRN_L2_UPDN_DIG_VALUE)
						{
							switch(lScEc2.updn_dig)
							{
								case 3: if((lScEc2.val>-1000) && (lScEc2.val<0)) lScEc2.val*=-1;	else lScEc2.val+=1000;	break;
								case 2: if((lScEc2.val>-100) && (lScEc2.val<0)) lScEc2.val*=-1; 	else lScEc2.val+=100;	break;
								case 1: if((lScEc2.val>-10) && (lScEc2.val<0)) lScEc2.val*=-1;		else lScEc2.val+=10;	break;
								case 0: lScEc2.val+=1;		break;
								default:	break;				
							}
							if(lScEc2.val>1000)	lScEc2.val= 1000;
						}
						break;
					case ScECO_REAL_TVG:		if(++lScEc2.val > MnEGN_TVG_MAX)		lScEc2.val = MnEGN_TVG_MIN; 			break;
					default:					lScEc2.val = 9999;						break;
				}
				break;
			case ScECO_TYPE_AVG:
				switch(iFn)
				{
					case ScECO_AVG_THR_LIGHT:
						switch(MnMSR_CalGet_Ch_Value(ScECH_PrGet_Chnnl(), MnMS1_OPT_SINGLE_THR_LIGHT))
						{
							case MnMS1_THRESHOLD_AUTO:		
								lScEc2.val+=5;
								if(lScEc2.val > MnMS1_THR_VAL_AUTO_MAX) lScEc2.val = MnMS1_THR_VAL_AUTO_MIN;		
								break;
							case MnMS1_THRESHOLD_MANUAL:
								if(++lScEc2.val > MnMS1_THR_VAL_MANUAL_MAX) lScEc2.val = MnMS1_THR_VAL_MANUAL_MIN;		
								break;
							default:
								break;
						}
						break;
					case ScECO_AVG_THR_HEAVY:
						switch(MnMSR_CalGet_Ch_Value(ScECH_PrGet_Chnnl(), MnMS1_OPT_SINGLE_THR_HEAVY))
						{
							case MnMS1_THRESHOLD_AUTO:		
								lScEc2.val+=5;
								if(lScEc2.val > MnMS1_THR_VAL_AUTO_MAX) lScEc2.val = MnMS1_THR_VAL_AUTO_MIN;		
								break;
							case MnMS1_THRESHOLD_MANUAL:
								if(++lScEc2.val > empty) lScEc2.val = dead;		
								break;
							default:
								break;
						}
						break;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:	
						switch(lScEc2.updn_mod)
						{
							case SCRN_L2_UPDN_DIG_VALUE:
								lScEc2.val+=13.5;
								if(lScEc2.val > 9999) lScEc2.val = 9999;	
								MsCAL_SetVl_ASF_R(ch,lScEc2.val);
								break;
							case SCRN_L2_UPDN_DIG:
								switch(evt)
								{
									case KEY_EVT_REPEAT:
									case KEY_EVT_LONG:		lScEc2.val+=10;	break;
									default:				lScEc2.val+=1;	break;
								}
								if(lScEc2.val > empty)	
									lScEc2.val = empty;
								break;
						}
						break;
					default:					break;
				}
				break;
			default:
				break;
		}



	DpEC2_ValUpdat();
	lScEc2.stt = SCRN_S1_STDBY;
}

void ScEc2Evt_KeyEnter(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC2] ENTER (Save)");
	INPU_ClrKeyEvt(evt);
	U08 iCh = ScECH_PrGet_Chnnl();

	switch(lScEc2.updn_mod)
	{
		case SCRN_L2_UPDN_IDLE:
			ScECH_PrSet_Value(lScEc2.val);
			break;
		case SCRN_L2_UPDN_DIG_VALUE:
			ScECH_PrSet_Value(lScEc2.val);
			if(ScECH_GetType()==ScECO_TYPE_AVG)
				break;

			lScEc2.stt = SCRN_S1_STDBY;
			lScEc2.updn_mod = SCRN_L2_UPDN_DIG;
			DpEC2_ValUpdat();
			DpSCR_UpdtBttn(SCRN_L2_VALU);			
			return;
		case SCRN_L2_UPDN_DIG:
			if(ScECH_GetType()==ScECO_TYPE_AVG)
			{
				lScEc2.val = MsCAL_GetVl_ASF_R(iCh);
			}			
			lScEc2.stt = SCRN_S1_STDBY;
			lScEc2.updn_mod = SCRN_L2_UPDN_DIG_VALUE;
			DpEC2_ValUpdat();
			DpSCR_UpdtBttn(SCRN_L2_VALU);
			return; 
	}



	lScEc2.stt = SCRN_S0_INTRO;
	DpEC0_FncIntro();
	DpEC2_ValUpdat();
	ScECH_SetLayer(SCRN_L1_LIST);
}

void ScEc2Evt_KeyInvalid(U08 evt)
{
	DpSTR_DebugExp(1, 1, "[ScEC2] Key (Invalid)");
	INPU_ClrKeyEvt(evt);

	lScEc2.stt = SCRN_S1_STDBY;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Status Machine
//------------------------------------------------------------------------------------------------------------------------------
void ScEc2Stt_S0Intro(U08 evt)
{
	U08 iCh = ScECH_PrGet_Chnnl();
	U08 iFn = ScEC1_GetIdxFunc();

	INPU_ClrKeyEvt(evt);

	lScEc2.updn_mod = SCRN_L2_UPDN_IDLE;

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			switch(iFn)
			{	// Page #0
				case ScECO_REAL_EMPTY:
				case ScECO_REAL_DEADZONE:	
					lScEc2.updn_mod = SCRN_L2_UPDN_DIG;
					break;
				case ScECO_REAL_ECHO_AMP:		
				default:
					break;
			}
			break;
		case ScECO_TYPE_AVG:
			switch(iFn)
			{
				case ScECO_AVG_THR_LIGHT:
				case ScECO_AVG_THR_HEAVY:
					break;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:
					lScEc2.updn_mod = SCRN_L2_UPDN_DIG;
					MsCAL_SetVl_ASF_H(iCh,0);
					MsCAL_SetVl_ASF_R(iCh,0);		
					break;
				default:
					break;
			}
			break;
		default:				
			break;
	}

	DpSTR_DebugExp_2(1, "[ScEC2] Evt - NONE"); 

	lScEc2.val = ScECH_PrGet_Value(iCh,iFn);
	DpEC2_ValIntro();
	DpSCR_UpdtBttn(SCRN_L2_VALU);
	lScEc2.stt = SCRN_S1_STDBY;
}

void ScEc2Stt_S1StdBy(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 1, "[ScEC2] Key - PUSH");			break;
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 1, "[ScEC2] Key - DTT_L");		break;
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 1, "[ScEC2] Key - SHORT");		break;
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 1, "[ScEC2] Key - REPEAT");		break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 1, "[ScEC2] Key - LONG");			break;
		default:
			//DpEcoGrp_DrawLive(0);
			DpEC2_ValUpdat();
			if(lScEc2.fSb)
				return;
			lScEc2.fSb = _F_T;
			DpSTR_DebugExp(0, 1, "[ScEC2] STBY - Pending");
			return;
	}

	lScEc2.stt = SCRN_S2_DTT_E;
	lScEc2.fSb = _F_F;
}

void ScEc2Stt_S2DttEv(U08 evt, U08 key)
{
	switch(evt)
	{
		case KEY_EVT_LONG:
		case KEY_EVT_REPEAT:
		case KEY_EVT_SHORT:
			switch(key)
			{
				case KEY_IDX_MENU:			ScEc2Evt_KeyFunc(evt);					break;
				case KEY_IDX_PREV:			ScEc2Evt_KeyPrev(evt);					break;
				case KEY_IDX_NEXT:			ScEc2Evt_KeyNext(evt);					break;
				case KEY_IDX_ENTER:			ScEc2Evt_KeyEnter(evt);					break;
				default:					ScEc2Evt_KeyInvalid(evt);				break;
			}
			break;

		case KEY_EVT_NONE:		DpSTR_DebugExp(1, 1, "[ScEC2] Evt - NONE");			break;
		default:				DpSTR_DebugExp(1, 1, "[ScEC2] Evt - Default");		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
S32 ScEC2_GetValue(void)			{	return lScEc2.val;		}
U08 ScEC2_GetMode(void)				{	return lScEc2.updn_mod;	}
S32 ScEC2_Getupdn_dig(void)			{	return lScEc2.updn_dig;	}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScEC2_InitValu(void)
{
	lScEc2.stt = SCRN_S0_INTRO;
	lScEc2.fSb = _F_F;
	lScEc2.val = 0;
	lScEc2.updn_dig = 0;
}
void ScEC2_ProcValu(void)
{
	U08 evt = INPU_GetKeyEvt();
	U08 key = INPU_GetKeyIdx();

	switch(lScEc2.stt)
	{
		case SCRN_S0_INTRO:		ScEc2Stt_S0Intro(evt);				break;
		case SCRN_S1_STDBY:		ScEc2Stt_S1StdBy(evt);				break;
		case SCRN_S2_DTT_E:		ScEc2Stt_S2DttEv(evt, key);			break;
		default:				lScEc2.stt = SCRN_S0_INTRO; 		break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

