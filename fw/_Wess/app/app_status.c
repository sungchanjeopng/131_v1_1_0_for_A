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
// bsp
#include "bsp_led.h"
// measure
#include "measure_calc.h"
// display
#include "disp_status.h"
#include "disp_string.h"
#include "disp_color.h"
#include "disp_titlebar.h"
#include "disp_figure.h"
// menu
#include "menu_measure.h"
#include "menu_engineer.h"
#include "menu_factory.h"
// self
#include "app_status.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ApSTT_LS lApStt;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ApSTT_GetStatus(U08 ss)					{	return lApStt.aStt[ss];		}
U08 ApSTT_GetFlg_Udt(void)					{	return lApStt.fUdt;			}
// Set
void ApSTT_SetStatus(U08 ss, U08 stt)		{	lApStt.aStt[ss] = stt;		}
void ApSTT_SetFlg_Udt(U08 flg)				{	lApStt.fUdt = flg;			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ApSTT_InitMain(void)
{
	lApStt.fUdt = _F_F;
	lApStt.fNg.byte = _F_F;
	lApStt.aStt[ApSTT_CH_S0] = ApSTT_MSR_IDLE;
	lApStt.aStt[ApSTT_CH_S1] = ApSTT_MSR_IDLE;

	_MEMSET(lApStt.sDbg, 0, sizeof(lApStt.sDbg));

	DpTTB_SetIconTgl(DpTTB_I1_MSR, TRUE);
}

void ApSTT_ProcMain(void)
{
	U08 stt;
	
	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:	stt = ApSTT_GetStatus(ApSTT_CH_S0);									break;
		case MnFTR_SS_DUAL:
			switch(ApSTT_GetStatus(ApSTT_CH_S0))
			{
				case ApSTT_MSR_IDLE:
				case ApSTT_MSR_TRAC:
				case ApSTT_MSR_WEAK:
				case ApSTT_MSR_OK:	stt = ApSTT_MSR_OK;	break;
				case ApSTT_TPR_NG:
				case ApSTT_MSR_NG:	stt = ApSTT_MSR_NG;	break;
			}
			switch(ApSTT_GetStatus(ApSTT_CH_S1))
			{
				case ApSTT_MSR_IDLE:
				case ApSTT_MSR_TRAC:
				case ApSTT_MSR_WEAK:
				case ApSTT_MSR_OK:
					if(stt == ApSTT_MSR_NG)
						break;
					stt = ApSTT_MSR_OK;
					break;
				case ApSTT_TPR_NG:	
				case ApSTT_MSR_NG:	
					stt = ApSTT_MSR_NG;	
					break;
			}
			break;			
		default:				
			break;
	}

	switch(stt)
	{
		case ApSTT_MSR_OK:
			DpTTB_SetIconTgl(DpTTB_I0_ALM, _F_F);
			DpTTB_SetIconTgl(DpTTB_I1_MSR, _F_T);
			break;
		case ApSTT_MSR_STOP:
			lApStt.aStt[ApSTT_CH_S0] = ApSTT_MSR_OK;
			lApStt.aStt[ApSTT_CH_S1] = ApSTT_MSR_OK;
			break;
		case ApSTT_MSR_NG:
		default:
			DpTTB_SetIconTgl(DpTTB_I0_ALM, _F_T);
			DpTTB_SetIconTgl(DpTTB_I1_MSR, _F_F);
			break;
	}

#if 0
	switch(MnMSR_fEN_ON)
	{
		case MnMSR_fEN_ON:
			DpTTB_SetIconTgl(DpTTB_I3_LCK, _F_F);
			switch(stt)
			{
				case ApSTT_MSR_OK:
					DpTTB_SetIconTgl(DpTTB_I0_ALM, _F_F);
					DpTTB_SetIconTgl(DpTTB_I1_MSR, _F_T);
					break;
				case ApSTT_MSR_STOP:
					lApStt.aStt[ApSTT_CH_S0] = ApSTT_MSR_OK;
					lApStt.aStt[ApSTT_CH_S1] = ApSTT_MSR_OK;
					break;
				case ApSTT_MSR_NG:
				default:
					DpTTB_SetIconTgl(DpTTB_I1_MSR, _F_F);
					DpTTB_SetIconTgl(DpTTB_I0_ALM, _F_T);
					break;
			}
			break;
		case MnMSR_fEN_OFF:
		default:
			DpTTB_SetIconTgl(DpTTB_I0_ALM, _F_F);
			DpTTB_SetIconTgl(DpTTB_I1_MSR, _F_F);
			DpTTB_SetIconTgl(DpTTB_I3_LCK, _F_T);
			lApStt.aStt[ApSTT_CH_S0] = ApSTT_MSR_STOP;
			lApStt.aStt[ApSTT_CH_S1] = ApSTT_MSR_STOP;
			break;
	}
#endif
	// LED
	LED_ProcMain();
	// Title Bar - Icon
	DpTTB_RunIconTgl();
	// Status Zone
	DpSTT_ProcMain();
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

