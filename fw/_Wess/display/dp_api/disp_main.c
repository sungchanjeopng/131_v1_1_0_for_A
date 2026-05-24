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
#include "bsp_lcd.h"
// app
#include "app_status.h"
// menu
#include "menu_main.h"
// display
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_button.h"
#include "disp_status.h"
#include "disp_popup.h"
// disp - screen
#include "dp_screen_main.h"
// disp - menu
#include "dp_menu_main.h"
// self
#include "disp_main.h"


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
void DISP_InitMain(void)
{
	DpSTT_InitMain();
	DpFIG_InitMain();
	DpBTN_InitVari();

	DpSCR_InitMain();
	DpMN_InitMain();
}

void DISP_IntroScrn(void)
{
	// Contents Screen Clear
	DpFIG_DrwRect(DISP_WND_X0, DISP_WND_Y0, DISP_WND_WD, DISP_WND_HT, _cBGD_SCRN, DpFIG_FILL);

	// Status Box Update
	ApSTT_SetFlg_Udt(_F_T);
}

void DISP_IntroMenu(void)
{
	// Contents Screen Clear
	DpFIG_DrwRect(DISP_WND_X0, DISP_WND_Y0, DISP_WND_WD, DISP_WND_HT, _cBGD_SCRN, DpFIG_FILL);
	// Button
	DpMN_UpdtBttn(MENU_L0_SECTION);
	// Status Box Update
	ApSTT_SetFlg_Udt(_F_T);
}

void DISP_ProcFlipFrm(void)
{
	LCD_FlipFrame();
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

