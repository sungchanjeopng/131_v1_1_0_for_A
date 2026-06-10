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
#include "app_sys.h"
// bsp
#include "bsp_gpio.h"
#include "bsp_demux.h"
// self
#include "output_relay.h"
// screen
#include "screen_hybrid.h"
// function
#include "measure_calc.h"
// menu
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_lyr3_value.h"

//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------
U08 gRly_state;
static U08 lRly_state[MnOUT_RLY_NUM];

static const U08 lOuRly_DmxOut[MnOUT_RLY_NUM] = {
	DMX_OUT_RELAY_1,
	DMX_OUT_RELAY_2,
	DMX_OUT_RELAY_3,
	DMX_OUT_RELAY_4,
};

//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
OuRLY_LS lOuRly;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
static void OuRLY_SetContactCh(U08 rly, U08 con)
{
	if(rly >= MnOUT_RLY_NUM)	return;

	switch(con)
	{
		case OuRLY_OPEN:		DMX_SetIo(lOuRly_DmxOut[rly], GIO_LV_HI);	break;
		case OuRLY_CLOSED:	DMX_SetIo(lOuRly_DmxOut[rly], GIO_LV_LO);	break;
		default:
			break;
	}
}

static U08 OuRLY_GetAssignValue(U08 assign, U16 *pVal)
{
	U08 ch;
	U08 thr;

	switch(assign)
	{
		case MnOS1_ASSIGN_CH1_HEAVY:	ch = APP_CH_1;	thr = MsCAL_THR_HEAVY;	break;
		case MnOS1_ASSIGN_CH1_LIGHT:	ch = APP_CH_1;	thr = MsCAL_THR_LIGHT;	break;
		case MnOS1_ASSIGN_CH2_HEAVY:	ch = APP_CH_2;	thr = MsCAL_THR_HEAVY;	break;
		case MnOS1_ASSIGN_CH2_LIGHT:	ch = APP_CH_2;	thr = MsCAL_THR_LIGHT;	break;
		default:					return FALSE;
	}

	switch(MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION))
	{
		case MnMS0_OPERATION_DISTANCE:	*pVal = MsCAL_GetVl_RsltDist(ch, thr);	break;
		case MnMS0_OPERATION_SLUDGE:	*pVal = MsCAL_GetVl_RsltSldg(ch, thr);	break;
		default:					return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 OuRLY_GetTestfEn(void)		{	return lOuRly.test_fEn;		}

// Set
void OuRLY_SetTestfEn(U08 sel)	{	lOuRly.test_fEn = sel;		}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void OuRLY_SetContact(U08 con)
{
	OuRLY_SetContactCh(MnOUT_RLY_0, con);
}

void OuRLY_InitMain(void)
{	
	U08 rly;

	gRly_state = OuRLY_CLOSED;
	lOuRly.test_fEn = FALSE;

	for(rly=0; rly<MnOUT_RLY_NUM; rly++)
	{
		lRly_state[rly] = OuRLY_CLOSED;
		OuRLY_SetContactCh(rly, OuRLY_CLOSED);
	}
}


void OuRLY_ProcMain(void)
{
	U16 valu;
	U08 rly;
	U08 assign;
	U16 rly_act;
	U16 rly_stop;

	for(rly=0; rly<MnOUT_RLY_NUM; rly++)
	{
		valu = 0;
		assign = (U08)MnOUT_RlyPrGet_Value(MnOS1_OPT_RLY_ASSIGN(rly));
		rly_act  = (U16)MnOUT_RlyPrGet_Value(MnOS1_OPT_RLY_ACT(rly));
		rly_stop = (U16)MnOUT_RlyPrGet_Value(MnOS1_OPT_RLY_STOP(rly));

		if(lOuRly.test_fEn)
		{
			valu = MnLY3_GetValue();
		}
		else if(OuRLY_GetAssignValue(assign, &valu) == FALSE)
		{
			OuRLY_SetContactCh(rly, lRly_state[rly]);
			continue;
		}
	
		if((rly == MnOUT_RLY_2) || (rly == MnOUT_RLY_3))
		{
			if		(valu <= rly_act)	lRly_state[rly] = OuRLY_OPEN;
			else if (valu >= rly_stop)	lRly_state[rly] = OuRLY_CLOSED;
		}
		else if(rly_act > rly_stop)
		{
			if		(valu >= rly_act)	lRly_state[rly] = OuRLY_OPEN;
			else if (valu <= rly_stop)	lRly_state[rly] = OuRLY_CLOSED;
		}
		else if(rly_act < rly_stop)
		{
			if		(valu <= rly_act)	lRly_state[rly] = OuRLY_CLOSED;
			else if (valu >= rly_stop)	lRly_state[rly] = OuRLY_OPEN;		
		}

		OuRLY_SetContactCh(rly, lRly_state[rly]);
	}

	gRly_state = lRly_state[MnOUT_RLY_0];
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

