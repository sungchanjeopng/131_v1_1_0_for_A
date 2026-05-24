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
#include "dac.h"
// screen
#include "screen_main.h"
#include "screen_echo.h"
#include "screen_calib.h"
#include "screen_eco1_list.h"
#include "screen_eco2_value.h"
// measure
#include "measure_gain.h"
// Menu
#include "menu_measure.h"
#include "menu_test.h"
// self
#include "bsp_dac.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
U32 lDac_tvg_idx;
U16 Dac_tvg[TVG_IDX_MAX];
//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U32 DAC_GetTvgIdx(void)			{	 return lDac_tvg_idx;		}
U16 DAC_GetTvgValue(U08 i)	{	return Dac_tvg[i];				}
// Set
void DAC_SetTvgIdx(U32 val)		{	 lDac_tvg_idx = val;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DAC_InitVari(void)
{
	lDac_tvg_idx = 0;
}

void DAC_OutpVolt(U16 volt)
{
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, volt);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
}


void DAC_filedValue(U08 ch)
{
	U08 i;
	U08 fTVG = MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_TVG);
	U16 gain = 45;

	for(i=0; i<TVG_IDX_MAX;i++)
	{
#if 0
		if(fTVG == 0)	Dac_tvg[i]  = (29*gain);
		else			Dac_tvg[i]  = ((S32)lMsr_aTvg[fTVG-1][i]*gain);
		

		
		if(Dac_tvg[i]>DAC_CON_DIG_MAX)	Dac_tvg[i] = DAC_CON_DIG_MAX;
		if(Dac_tvg[i]<0)				Dac_tvg[i] = 0;

		//Dac_tvg[i] = Dac_tvg[i]*0.725;
#endif
		Dac_tvg[i] = 1350;
	}

}

void DAC_ProcValue(U08 ch)
{
	U08 fTVG	= MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_TVG);
	S32 gain	= MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ECHO_AMP);
	S32 trans	= MnTST_PrGet_CH_Value(ch, MnTST_OPT_SINGLE_ECHO_AMP_B);
	U08 i;

	if(ScECH_GetLayer() == SCRN_L2_VALU)
	{
		S32 val 	= ScEC2_GetValue();
		U08 iFn 	= ScEC1_GetIdxFunc();
	
		switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:
				switch(iFn)
				{
					case ScECO_REAL_ECHO_AMP:	gain = val; break;
					case ScECO_REAL_TVG:		fTVG = val;	break;
					default:	break;
				}
				break;
			case ScECO_TYPE_AVG:
				break;
			default:
				break;
		}
	}



	for(i=0; i<TVG_IDX_MAX;i++)
	{
		if(fTVG == 0)	Dac_tvg[i]  = (29*gain)+trans;
		else			Dac_tvg[i]  = ((S32)lMsr_aTvg[fTVG-1][i]*gain)+trans;
		
		
		if(Dac_tvg[i]>DAC_CON_DIG_MAX)	Dac_tvg[i] = DAC_CON_DIG_MAX;
		if(Dac_tvg[i]<0)				Dac_tvg[i] = 0;

		//Dac_tvg[i] = Dac_tvg[i]*0.725;

	}

}
void DAC_ProcTvg(U08 ch, U16 idx)		// TVG: Time Variable Gain
{	
#if 0

	U08 fTVG 	= MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_TVG);
	S32 gain	= MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ECHO_AMP);

	S32 vca,volt;

	

	if(ScECH_GetLayer() == SCRN_L2_VALU)
	{
		S32 trans	= 0; 
		S32 val 	= ScEC2_GetValue();
		U08 iFn 	= ScEC1_GetIdxFunc();
		S32 vca,volt;
	
		switch(ScECH_GetType())
		{
			case ScECO_TYPE_REAL:
				switch(iFn)
				{
					case ScECO_REAL_ECHO_AMP:	gain = val; break;
					default:	break;
				}
				break;
			case ScECO_TYPE_AVG:
				break;
			default:
				break;
		}
	}


	if(fTVG == ScCLB_TVG_OFF)	vca  = 20;
	else						vca  = (S32)lMsr_aTvg[fTVG-1][idx];
	volt = (vca * gain);
	
	if(volt>DAC_CON_DIG_MAX)	volt = DAC_CON_DIG_MAX;
	if(volt<0)					volt = 0;
#endif
	DAC_OutpVolt(Dac_tvg[idx]);


}


void DAC_ProcMain(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

