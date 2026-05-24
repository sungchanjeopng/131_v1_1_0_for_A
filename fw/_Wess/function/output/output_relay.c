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

//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
OuRLY_LS lOuRly;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


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
	switch(con)
	{
		case OuRLY_OPEN:		DMX_SetIo(DMX_OUT_RELAY_1, GIO_LV_HI);	break;
		case OuRLY_CLOSED:		DMX_SetIo(DMX_OUT_RELAY_1, GIO_LV_LO);	break;
		default:
			break;
	}
}

void OuRLY_InitMain(void)
{	
	gRly_state = OuRLY_CLOSED;
	lOuRly.test_fEn = FALSE;
	//OuRLY_SetContact(OuRLY_OPEN);
	OuRLY_SetContact(OuRLY_CLOSED);
}


void OuRLY_ProcMain(void)
{
	U16 valu;
	U08 assign = MnOUT_RlyPrGet_Value(MnOS1_OPT_ASSIGN);

	U16 rly_act		= MnOUT_RlyPrGet_Value(MnOS1_OPT_ACT);
	U16 rly_stop 	= MnOUT_RlyPrGet_Value(MnOS1_OPT_STOP);
	//Not Yet


	switch(assign)
	{
		case MnOS1_ASSIGN_CH1_HEAVY:	
			switch(MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_OPERATION))
			{
				case MnMS0_OPERATION_DISTANCE:	valu = MsCAL_GetVl_RsltDist(APP_CH_1,MsCAL_THR_HEAVY);	break;
				case MnMS0_OPERATION_SLUDGE:	valu = MsCAL_GetVl_RsltSldg(APP_CH_1,MsCAL_THR_HEAVY);	break;
				default:
					break;
			}
			break;
		case MnOS1_ASSIGN_CH1_LIGHT:
			switch(MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_OPERATION))
			{
				case MnMS0_OPERATION_DISTANCE:	valu = MsCAL_GetVl_RsltDist(APP_CH_1,MsCAL_THR_LIGHT);	break;
				case MnMS0_OPERATION_SLUDGE:	valu = MsCAL_GetVl_RsltSldg(APP_CH_1,MsCAL_THR_LIGHT);	break;
				default:
					break;
			}
			break;
		case MnOS1_ASSIGN_CH2_HEAVY:
			switch(MnMSR_BaseGet_Ch_Value(APP_CH_2, MnMS0_OPT_SINGLE_OPERATION))
			{
				case MnMS0_OPERATION_DISTANCE:	valu = MsCAL_GetVl_RsltDist(APP_CH_2,MsCAL_THR_HEAVY);	break;
				case MnMS0_OPERATION_SLUDGE:	valu = MsCAL_GetVl_RsltSldg(APP_CH_2,MsCAL_THR_HEAVY);	break;
				default:
					break;
			}
			break;
		case MnOS1_ASSIGN_CH2_LIGHT:
			switch(MnMSR_BaseGet_Ch_Value(APP_CH_2, MnMS0_OPT_SINGLE_OPERATION))
			{
				case MnMS0_OPERATION_DISTANCE:	valu = MsCAL_GetVl_RsltDist(APP_CH_2,MsCAL_THR_LIGHT);	break;
				case MnMS0_OPERATION_SLUDGE:	valu = MsCAL_GetVl_RsltSldg(APP_CH_2,MsCAL_THR_LIGHT);	break;
				default:
					break;
			}
			break;
		default:
			break;
	}
#if 0
	switch(ScHYB_PrGet_LvTyp())
	{
		case 0:
			switch(rly_assign)
			{
				case MnOS1_IV0_CH_0:		valu = valu_sldg_CH_S0;									break;
				case MnOS1_IV0_CH_1:		valu = valu_sldg_CH_S1;									break;
				case MnOS1_IV0_DIFF:		valu = _ABS(valu_sldg_CH_S0-valu_sldg_CH_S1);			break;
				case MnOS1_IV0_AVRG:		valu = (valu_sldg_CH_S0+valu_sldg_CH_S1)/MsCAL_CH_NUM;	break;
				default:					return;
			}			
			break;
		case 1:
			switch(rly_assign)
			{
				case MnOS1_IV0_CH_0:		valu = valu_dist_CH_S0;									break;
				case MnOS1_IV0_CH_1:		valu = valu_dist_CH_S1;									break;
				case MnOS1_IV0_DIFF:		valu = _ABS(valu_dist_CH_S0-valu_dist_CH_S1);			break;
				case MnOS1_IV0_AVRG:		valu = (valu_dist_CH_S0+valu_dist_CH_S1)/MsCAL_CH_NUM;	break;
				default:					return;
			}
			break;
		default:							return;

	}
#endif

	if(lOuRly.test_fEn)		valu=MnLY3_GetValue();
	
	
	if(rly_act > rly_stop)
	{
		if		(valu >= rly_act)	gRly_state = OuRLY_OPEN;
		else if (valu <= rly_stop)	gRly_state = OuRLY_CLOSED;
	}
	else if(rly_act < rly_stop)
	{
		if		(valu <= rly_act)	gRly_state = OuRLY_CLOSED;
		else if (valu >= rly_stop)	gRly_state = OuRLY_OPEN;		
	}

	OuRLY_SetContact(gRly_state);

	
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

