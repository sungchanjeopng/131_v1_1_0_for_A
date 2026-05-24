//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2021, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2020-07-13 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// bsp
#include "bsp_gpio.h"
#include "bsp_demux.h"
// app
#include "app_main.h"
// display
#include "disp_main.h"
#include "disp_string.h"
#include "disp_button.h"
// self
#include "input_key.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
KEY_LV lKey;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
U08 KeyChk_DmxIo(void)
{
	U08 key = 0;

	if(DMX_GetIo(DMX_INP_MBR_ENTER))		_B_SET(key, KEY_BIT_ENTER)
	else									_B_CLR(key, KEY_BIT_ENTER)
	if(DMX_GetIo(DMX_INP_MBR_RIGHT))		_B_SET(key, KEY_BIT_RIGHT)
	else									_B_CLR(key, KEY_BIT_RIGHT)
	if(DMX_GetIo(DMX_INP_MBR_LEFT_))		_B_SET(key, KEY_BIT_LEFT)
	else									_B_CLR(key, KEY_BIT_LEFT)
	if(DMX_GetIo(DMX_INP_MBR_BACK_))		_B_SET(key, KEY_BIT_BACK)
	else									_B_CLR(key, KEY_BIT_BACK)

	key = _InKEY_RD_INP(key);

	if(lKey.act == KEY_ACT_HIGH)
		key = ~key;

	return key;
}

void KeyPrc_PushDtt(U08 key)
{
	lKey.cHld = 0;
	lKey.cRpt = 0;

	switch(lKey.evt)
	{
		case KEY_EVT_NONE:		lKey.evt = KEY_EVT_PUSH;	lKey.idx = key;		break;
	}

	switch(lKey.evt)
	{
		case KEY_EVT_PUSH:		DpSTR_DebugExp(0, 0, "[Key] Push Detect - PUSH");			break;
		default:				DpSTR_DebugExp(0, 0, "[Key] Push Detect - Default");		break;
	}
}

void KeyPrc_PushLng(void)
{
	if(lKey.evt == KEY_EVT_DTT_L)
		return;

	if(++lKey.cHld < KEY_CNT_CHK_LONG)
		return;
	lKey.cHld = 0;

	switch(lKey.evt)
	{
		case KEY_EVT_PUSH:		lKey.evt = KEY_EVT_DTT_L;		break;
	}

	switch(lKey.evt)
	{
		case KEY_EVT_DTT_L:		DpSTR_DebugExp(0, 0, "[Key] Push Long - LONG");				break;
		default:				DpSTR_DebugExp(0, 0, "[Key] Push Long - Default");			break;
	}
}

void KeyPrc_PushRpt(void)
{
	switch(lKey.evt)
	{
		case KEY_EVT_DTT_L:
		case KEY_EVT_REPEAT:
			if(++lKey.cRpt < KEY_CNT_CHK_RPT)
				break;
			lKey.cRpt = 0;

			lKey.evt = KEY_EVT_REPEAT;
			break;
	}

	switch(lKey.evt)
	{
		case KEY_EVT_REPEAT:	DpSTR_DebugExp(0, 0, "[Key] Push Repeat - REPEAT");			break;
		default:				DpSTR_DebugExp(0, 0, "[Key] Push Repeat - Default");		break;
	}
}

void KeyPrc_RelsDtt(void)
{
	switch(lKey.evt)
	{
		case KEY_EVT_PUSH:		lKey.evt = KEY_EVT_SHORT;		break;
		case KEY_EVT_DTT_L:
		case KEY_EVT_REPEAT:	lKey.evt = KEY_EVT_LONG;		break;
	}

	switch(lKey.evt)
	{
		case KEY_EVT_SHORT:		DpSTR_DebugExp(0, 0, "[Key] Released - SHORT");				break;
		case KEY_EVT_LONG:		DpSTR_DebugExp(0, 0, "[Key] Released - LONG");				break;
		default:
			if(!lKey.fDp.b.dft)
			{
				DpSTR_DebugExp(0, 0, "[Key] Released - Default");
				lKey.fDp.b.dft = TRUE;
			}
			break;
	}
}

void KeyPrc_DispPsh(void)
{
	if(!lKey.fDp.b.psh)
	{
		lKey.fDp.b.psh = TRUE;

		switch(lKey.idx)
		{
			case KEY_IDX_MENU:		DpBTN_UdtEvent(DpBTN_I0_MENU, TRUE); 		break;
			case KEY_IDX_PREV:		DpBTN_UdtEvent(DpBTN_I1_PREV, TRUE);		break;
			case KEY_IDX_NEXT:	 	DpBTN_UdtEvent(DpBTN_I2_NEXT, TRUE);		break;
			case KEY_IDX_ENTER: 	DpBTN_UdtEvent(DpBTN_I3_ENTR, TRUE); 		break;
		}
	}
	
	lKey.fDp.b.rls = FALSE;
}

void KeyPrc_DispRls(void)
{
	if(!lKey.fDp.b.rls)
	{
		DpBTN_UdtEvent(DpBTN_I0_BACK, FALSE);
		DpBTN_UdtEvent(DpBTN_I1_PREV, FALSE);
		DpBTN_UdtEvent(DpBTN_I2_NEXT, FALSE);
		DpBTN_UdtEvent(DpBTN_I3_ENTR, FALSE);
		lKey.fDp.b.rls = TRUE;
	}
	
	lKey.fDp.b.psh = FALSE;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 InKEY_GetIdx(void)			{	return lKey.idx;				}
U08 InKEY_GetEvt(void)			{	return lKey.evt;				}
U16 InKEY_GetCtRpt(void)		{	return lKey.rpt;				}
U08 InKEY_GetFgNone(void)		{	return (U08)lKey.fDp.b.none;	}
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void InKEY_InitMain(U08 act)
{
	lKey.act = act;

	lKey.idx = KEY_IDX_NONE;
	lKey.evt = KEY_EVT_NONE;

	lKey.cHld = 0;
	lKey.cRpt = 0;

	lKey.fDp.byte = _F_F;
}

void InKEY_ClrEvt(U08 evt)
{
	switch(evt)
	{
		case KEY_EVT_REPEAT:
			_B_CLR(lKey.evt, evt);
			break;

		case KEY_EVT_NONE:
		default:
			lKey.idx = KEY_IDX_NONE;
			lKey.evt = KEY_EVT_NONE;
			
			lKey.cHld = 0;
			break;
	}

	lKey.cRpt = 0;
	lKey.fDp.b.dft = _F_F;
	DpSTR_DebugExp(0, 0, "[Key] Clear Event");
}

void InKEY_ProcMain(void)
{
	U08 key = KeyChk_DmxIo();
	U08 old = lKey.idx;

	if(!APP_GetFgRun())
		return;

	if(key != KEY_IDX_NONE)
	{
		lKey.fDp.b.none = _F_F;

		if(key != old)
			KeyPrc_PushDtt(key);
		else
		{
			KeyPrc_PushLng();
			KeyPrc_PushRpt();
		}

		KeyPrc_DispPsh();
	}
	else
	{
		KeyPrc_RelsDtt();
		KeyPrc_DispRls();

		if(lKey.evt == KEY_EVT_NONE)		lKey.fDp.b.none = _F_T;
		else								lKey.fDp.b.none = _F_F;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

