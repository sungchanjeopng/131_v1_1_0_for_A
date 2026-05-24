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
#include "app_main.h"
#include "app_status.h"
// menu
#include "menu_factory.h"
// display
#include "fonts.h"
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
// self
#include "disp_status.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpSTT_LS lDpScr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void SttUdt_Box(void)
{
#if 0
	if(!APP_GetFgRun())
		return;

	if(!ApSTT_GetFlg_Udt())
		return;
#endif
	DpFIG_DrwRect(DpSTT_BOX_X0_, DpSTT_BOX_Y0_, DpSTT_BOX_WID, DpSTT_BOX_HEI, _cSD_BLACK, DpFIG_TK_02);

	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:
			break;
		case MnFTR_SS_DUAL:
			DpFIG_DrwRect(DpSTT_BOX_X0_, DpSTT_BOX_Y0_, DpSTT_BOX_WID/2, DpSTT_BOX_HEI, _cSD_BLACK, DpFIG_TK_02);
			break;
	}
}

void SttUdt_Zone0(void)
{
	I08 sStt[8] = {0, };
	U08 stt_0 = ApSTT_GetStatus(ApSTT_CH_S0);
	U08 ch_md = MnFTR_PrGet_SsChn();

	if(!APP_GetFgRun())
		return;

	switch(ch_md)
	{
		case MnFTR_SS_SINGLE:
			switch(stt_0)
			{
				case ApSTT_MSR_IDLE:
				case ApSTT_MSR_WEAK:		_SPRINTF(sStt, "%s", "ST00");		break;
				case ApSTT_MSR_TRAC:		_SPRINTF(sStt, "%s", "ST01");		break;				
				case ApSTT_MSR_OK:			_SPRINTF(sStt, "%s", "ST02");		break;
				case ApSTT_MSR_STOP:		_SPRINTF(sStt, "%s", "ST03");		break;
				case ApSTT_MSR_NG:			_SPRINTF(sStt, "%s", "ER01");		break;
				case ApSTT_TPR_NG:			_SPRINTF(sStt, "%s", "ER02");		break;				
			}
			DpFIG_DrwRect(635, DpSTT_BOX_Y0_+15, 70, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(635, DpSTT_BOX_Y0_+15, _cSTT_ST_MAIN, _cBGD_SCRN, _fE22HsB, sStt);			
			break;
		case MnFTR_SS_DUAL:
			switch(stt_0)
			{
				case ApSTT_MSR_IDLE:
				case ApSTT_MSR_WEAK:		_SPRINTF(sStt, "%s", "ST00");		break;
				case ApSTT_MSR_TRAC:		_SPRINTF(sStt, "%s", "ST01");		break;				
				case ApSTT_MSR_OK:			_SPRINTF(sStt, "%s", "ST02");		break;
				case ApSTT_MSR_STOP:		_SPRINTF(sStt, "%s", "ST03");		break;
				case ApSTT_MSR_NG:			_SPRINTF(sStt, "%s", "ER01");		break;
				case ApSTT_TPR_NG:			_SPRINTF(sStt, "%s", "ER02");		break;						
			}
			DpFIG_DrwRect(DpSTT_BOX_X0_+20, DpSTT_BOX_Y0_+15, 70, 30, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpSTT_BOX_X0_+20, DpSTT_BOX_Y0_+15, _cSTT_ST_MAIN, _cBGD_SCRN, _fE22HsB, sStt);

			break;
		default:
			break;
	}


}

void SttUdt_Zone1(void)
{
	I08 sStt[8] = {0, };
	U08 stt_0 = ApSTT_GetStatus(ApSTT_CH_S0);
	U08 stt_1 = ApSTT_GetStatus(ApSTT_CH_S1);
	U08 ch_md = MnFTR_PrGet_SsChn();
	U16 x0 = 670;

	if(!APP_GetFgRun())
		return;

	switch(ch_md)
	{
		case MnFTR_SS_SINGLE:
			return;
		case MnFTR_SS_DUAL:
			switch(stt_1)
			{
				case ApSTT_MSR_IDLE:
				case ApSTT_MSR_WEAK:		_SPRINTF(sStt, "%s", "ST00");		break;
				case ApSTT_MSR_TRAC:		_SPRINTF(sStt, "%s", "ST01");		break;				
				case ApSTT_MSR_OK:			_SPRINTF(sStt, "%s", "ST02");		break;
				case ApSTT_MSR_STOP:		_SPRINTF(sStt, "%s", "ST03");		break;
				case ApSTT_MSR_NG:			_SPRINTF(sStt, "%s", "ER01");		break;
				case ApSTT_TPR_NG:			_SPRINTF(sStt, "%s", "ER02");		break;	
			}
			break;
		default:	
			break;
	}

	DpFIG_DrwRect(x0+10, DpSTT_BOX_Y0_+15, 70, 30, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(x0+10, DpSTT_BOX_Y0_+15, _cSTT_ST_SUB0, _cBGD_SCRN, _fE22HsB, sStt);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DpSTT_InitMain(void)
{
	lDpScr.stt0 = ApSTT_MSR_NG;
	lDpScr.stt1 = ApSTT_MSR_NG;
}

void DpSTT_ProcMain(void)
{
	SttUdt_Box();
	SttUdt_Zone0();
	SttUdt_Zone1();
	ApSTT_SetFlg_Udt(_F_F);
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

