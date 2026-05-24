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
// app
#include "app_main.h"
// screen
#include "screen_front.h"
#include "screen_hybrid.h"
#include "screen_echo.h"
#include "screen_calib.h"
#include "screen_info.h"
// self
#include "screen_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
SCRN_LS lScr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 SCRN_GetPage(void)			{	return lScr.page;		}
// Set
void SCRN_SetPage(U08 page)		{	lScr.page = page;		}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void SCRN_PrInitMain(void)
{
	ScHYB_PrInitMain();
	ScCLB_PrInitMain();
	ScINF_PrInitMain();
}


void SCRN_InitMain(void)
{
	lScr.page = SCRN_P0_FRONT;

	ScFRT_InitMain();
	ScHYB_InitMain();
	ScECH_InitMain();
	ScCLB_InitMain();
	ScINF_InitMain();
}

void SCRN_FtrReset(void)
{
	ScHYB_PrRst_Factory();
	ScCLB_PrRst_Factory();
	ScINF_PrRst_Factory();

	SCRN_PrInitMain();
}

void SCRN_ProcMain(void)
{
	switch(lScr.page)
	{
		case SCRN_P0_FRONT:		ScFRT_ProcMain();		break;
		case SCRN_P1_HYBRID:	ScHYB_ProcMain();		break;
		case SCRN_P2_ECHO:		ScECH_ProcMain();		break;
		case SCRN_P3_INFO:		ScINF_ProcMain();		break;
		case SCRN_P4_TREND:		ScCLB_ProcMain();		break;
		default:				break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

