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
// screen
#include "screen_main.h"
// menu
#include "menu_factory.h"
// display
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_button.h"
// disp - screen
#include "screen_eco2_value.h"
#include "dp_screen_hybrid.h"
#include "dp_screen_echo.h"
#include "dp_screen_info.h"
// self
#include "dp_screen_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------


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
void DpSCR_InitMain(void)
{
	Dphyb_InitVari();
	DpECO_InitVari();
	DpINF_InitVari();
}

void DpSCR_LnHrBttn(void)
{
	DpFIG_DrwRect(15, 390+(2*0), 760, 2, _chyb_LN_H00, 0);
	DpFIG_DrwRect(15, 390+(2*1), 760, 2, _chyb_LN_H01, 0);
	DpFIG_DrwRect(15, 390+(2*2), 760, 2, _chyb_LN_H02, 0);
}

void DpSCR_UpdtBttn(U08 lyr)
{
	DpSCR_LnHrBttn();

	switch(lyr)
	{
		case SCRN_L0_FUNC:
			DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_IDLE, TEXT_LIST_MENU, 17);
			DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_LEFT);
			DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_RIGH);

			#if 0
			if(MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL)	DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, _sFUNC, 19);
			else										DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_DISA, "-",	  40);
			#else
			switch(SCRN_GetPage())
			{
				case SCRN_P0_FRONT:
				case SCRN_P1_HYBRID:
				case SCRN_P3_INFO:			
					//DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_DISA, "",40);
					break;
				default:										DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_FUNC, 19);			break;
			}
			break;
			#endif
		case SCRN_L1_LIST:
			#if 0
			#else
			switch(SCRN_GetPage())
			{
				case SCRN_P0_FRONT:
				case SCRN_P1_HYBRID:
				case SCRN_P2_ECHO:
				case SCRN_P4_TREND:			DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_UP__);
				case SCRN_P3_INFO:			DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_DOWN);						break;
				default:					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_UP__);
											DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_DOWN);						break;
			}
			#endif
			DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 23);
			DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_IDLE, TEXT_LIST_SET,  26);
			break;

		case SCRN_L2_VALU:
			switch(ScEC2_GetMode())
			{
				case SCRN_L2_UPDN_DIG:
					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_LEFT);
					DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_RIGH);
					DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 23);
					DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SAVE, 17);
					break;
				case SCRN_L2_UPDN_DIG_VALUE:
				case SCRN_L2_UPDN_IDLE:
					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
					DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);
					DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 23);
					DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SAVE, 17);
					break;
			}		
			break;

	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

