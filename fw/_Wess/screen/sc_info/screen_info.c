//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
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
#include "bsp_ram.h"
// app
#include "app_main.h"
// function
#include "input_main.h"
#include "input_key.h"
// menu
#include "menu_factory.h"
// display
#include "disp_string.h"
// disp - screen
#include "dp_screen_info.h"
// screen
#include "screen_main.h"
#include "screen_inf0_func.h"
#include "screen_inf1_list.h"
#include "screen_inf2_value.h"
// self
#include "screen_info.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScINF_LS lScInf;


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Get
//------------------------------------------------------------------------------------------------------------------------------
U08 ScINF_PrGet_Chnnl(void)			{	return lScInf.mPr.iCh;			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameters - Set
//------------------------------------------------------------------------------------------------------------------------------
S32 ScINF_PrGet_Value(U08 iIt)
{
#if 0
	S32 val = MENU_VAL_INVALID;

	switch(iIt)
	{
		case ScINF_OPT_CH1_FREQ:	lScInf.mPr.val	= MnMSR_CalGet_Value(MnMS1_OPT_CH1_FREQ);			break;
		case ScINF_OPT_CH1_OFFSET:	lScInf.mPr.val	= MnMSR_CalGet_Value(MnMS1_OPT_CH1_OFFSET);			break;
		case ScINF_OPT_CH1_4mA:		lScInf.mPr.val	= MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_SET_04mA);		break;
		case ScINF_OPT_CH1_20mA:	lScInf.mPr.val	= MnMSR_BaseGet_Value(MnOS0_OPT_CH1_SET_20mA);		break;	
		case ScINF_OPT_CH1_MSR_CYC:	lScInf.mPr.val	= MnMSR_BaseGet_Value(MnMS0_OPT_CH1_MEASURE_CYCLE);	break;
		case ScINF_OPT_CH1_DAMP:	lScInf.mPr.val	= MnMSR_CalGet_Value(MnMS1_OPT_CH1_DAMPING);		break;
		case ScINF_OPT_CH2_FREQ:	lScInf.mPr.val	= MnMSR_CalGet_Value(MnMS1_OPT_CH2_FREQ);			break;
		case ScINF_OPT_CH2_OFFSET:	lScInf.mPr.val	= MnMSR_CalGet_Value(MnMS1_OPT_CH2_OFFSET);			break;
		case ScINF_OPT_CH2_4mA:		lScInf.mPr.val	= MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_SET_04mA);		break;
		case ScINF_OPT_CH2_20mA:	lScInf.mPr.val	= MnMSR_BaseGet_Value(MnOS0_OPT_CH2_SET_20mA);		break;	
		case ScINF_OPT_CH2_MSR_CYC:	lScInf.mPr.val	= MnMSR_BaseGet_Value(MnMS0_OPT_CH2_MEASURE_CYCLE);	break;
		case ScINF_OPT_CH2_DAMP:	lScInf.mPr.val	= MnMSR_CalGet_Value(MnMS1_OPT_CH2_DAMPING);		break;		
		default:
			break;
	}

	return val;
#endif
}



void ScINF_PrSet_Value(S32 val)
{
#if 0
	U08 iFn = ScIF1_GetIdxFunc();

	switch(iFn)
	{
		case ScINF_OPT_CH1_FREQ:	MnMSR_CalSet_Value(MnMS1_OPT_CH1_FREQ,val);				break;
		case ScINF_OPT_CH1_OFFSET:	MnMSR_CalSet_Value(MnMS1_OPT_CH1_OFFSET,val);			break;
		case ScINF_OPT_CH1_4mA:		MnOUT_CurPrSet_Value(MnOS0_OPT_CH1_SET_04mA,val);		break;
		case ScINF_OPT_CH1_20mA:	MnMSR_BaseSet_Value(MnOS0_OPT_CH1_SET_20mA,val);		break;	
		case ScINF_OPT_CH1_MSR_CYC:	MnMSR_BaseSet_Value(MnMS0_OPT_CH1_MEASURE_CYCLE,val);	break;
		case ScINF_OPT_CH1_DAMP:	MnMSR_CalSet_Value(MnMS1_OPT_CH1_DAMPING,val);			break;
		case ScINF_OPT_CH2_FREQ:	MnMSR_CalSet_Value(MnMS1_OPT_CH2_FREQ,val);				break;
		case ScINF_OPT_CH2_OFFSET:	MnMSR_CalSet_Value(MnMS1_OPT_CH2_OFFSET,val);			break;
		case ScINF_OPT_CH2_4mA:		MnOUT_CurPrSet_Value(MnOS0_OPT_CH2_SET_04mA,val);		break;
		case ScINF_OPT_CH2_20mA:	MnMSR_BaseSet_Value(MnOS0_OPT_CH2_SET_20mA,val);		break;	
		case ScINF_OPT_CH2_MSR_CYC:	MnMSR_BaseSet_Value(MnMS0_OPT_CH2_MEASURE_CYCLE,val);	break;
		case ScINF_OPT_CH2_DAMP:	MnMSR_CalSet_Value(MnMS1_OPT_CH2_DAMPING,val);			break;		
		default:
			break;
	}
#endif
}

void ScINF_PrRst_Factory(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables - Basic
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScPRM_GetLayer(void)			{	return lScInf.lyr;					}
// Set
void ScINF_SetLayer(U08 lyr)		{	lScInf.lyr = lyr;					}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic Operation
//------------------------------------------------------------------------------------------------------------------------------
void ScINF_PrInitMain(void)
{

}

void ScINF_InitMain(void)
{
	lScInf.lyr = SCRN_L0_FUNC;

	ScIF0_InitFunc();
	ScIF1_InitList();
	ScIF2_InitValu();

	ScINF_PrInitMain();
}

void ScINF_ProcMain(void)
{
	switch(lScInf.lyr)
	{
		case SCRN_L0_FUNC:		ScIF0_ProcFunc();			break;
		case SCRN_L1_LIST:		ScIF1_ProcList();			break;
		case SCRN_L2_VALU:		ScIF2_ProcValu();			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

