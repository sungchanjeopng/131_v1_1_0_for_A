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
#include "bsp_dac.h"
// self
#include "measure_main.h"
// measure
#include "measure_sensor.h"
// screen
#include "screen_main.h"
#include "screen_calib.h"
#include "screen_clb1_list.h"
#include "screen_clb2_value.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MsGAN_LS lMsGan;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void MsAutoGain_Proc(U08 ch)
{
	U16 i;
	U16 j=1;
	U16 max = 0;
	U16 min = 4096;
	U16 trac_dist = MsCAL_GetVl_TracDist(ch,MsCAL_THR_HEAVY);
	U16 val[100];
	F32 sum_x=0, sum_y=0, sum_xy=0, sum_x2 = 0,m=0,b=0;

	

	for(i=trac_dist-20; i<trac_dist+20; i++)
	{	
		if(max<ADC_GetEchoVal(ch, i))
			lMsGan.agc_max = ADC_GetEchoVal(ch, i);
		if(min>ADC_GetEchoVal(ch, i))
			lMsGan.agc_min = ADC_GetEchoVal(ch, i);
		
		val[j] = ADC_GetEchoVal(ch, i);

		sum_x+= j;
		sum_y+= val[j];
		sum_xy= j*val[j];
		sum_x2+=j*j;

		j++;		
	}

	lMsGan.agc_m = ((40*sum_xy)-(sum_x*sum_y)) / ((40*sum_x2)-(sum_x*sum_x));
	b = (sum_y - m*sum_x) / 40;

}



void MsGAN_InitVari(void)
{
	lMsGan.rx_amp = ScCLB_RX_AMP_x100;
}

void MsGAN_CfgRx(U08 amp, U08 ch)
{
#if 0
	S32 val = ScCB2_GetValue();
	U08 iFn = ScCB1_GetIdxFunc();

	if(ScECH_GetLayer() == SCRN_L2_VALU)
	{
		switch(ScECH_GetType())
		{
			switch ScECO_TYPE_REAL:
				switch(iFn)
				{
					case ScECO_REAL_ECHO_AMP:  	amp = val;		break;
					default:									break;
				}
				break;
			switch ScECO_TYPE_AVG:
				break;
		}
		break;
	}
#endif
	switch(amp)
	{
		case ScCLB_RX_AMP_x47: 	DMX_SetIo(DMX_OUT_RX_Con_0,  MsSEN_G0_047);		break;	// DMX_OUT_RX_Con_0 : DMX_OUT_SEL_G
		case ScCLB_RX_AMP_x100: DMX_SetIo(DMX_OUT_RX_Con_0,  MsSEN_G1_100);		break;
	}


}

void MsGAN_ProcMain(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

