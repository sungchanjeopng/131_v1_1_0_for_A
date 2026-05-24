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
// display
#include "disp_color.h"
#include "disp_figure.h"
#include "disp_string.h"
#include "menu_system.h"
// self
#include "disp_popup.h"


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
//  Global APIs - Update
//------------------------------------------------------------------------------------------------------------------------------
void DpPOP_UdtTitle(I08* pStr)
{
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	U08 sec = MENU_GetSection();

	switch(sec)
	{
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
			lang = MnSYS_LANG_ENG;
			break;
	}

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			DpSTR_GuiLeft(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, pStr);
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, pStr);
			break;
	}

}

void DpPOP_UdtOldVl(I08* pStr)
{
	DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
	DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_OLD_Y0,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE22HsB, pStr);
}

void DpPOP_UdtExpla(I08* pStr)
{
	//DpSTR_GuiLeft(DpPOP_EXP_X0, DpPOP_EXP_Y0, _cPOP_ST_EXP, _cPOP_BG_WND, _fE17HsB, pStr);
}

void DpPOP_UdtRange(S32 min, S32 max)
{
	I08 sMin[8] = {0, };
	I08 sMax[8] = {0, };

	_SPRINTF(sMin, "%d", min);
	_SPRINTF(sMax, "%d", max);

	DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN, _cPOP_BG_WND, _fE17HsB, _sMIN);
	DpSTR_GuiLeft(DpPOP_MAX_X0, DpPOP_MAX_Y0, _cPOP_ST_MAX, _cPOP_BG_WND, _fE17HsB, _sMAX);

	DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sMin);
	DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MAX_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sMax);
}

void DpPOP_UdtRangeMin(I08* pStr)
{
	DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN, _cPOP_BG_WND, _fE17HsB, _sMIN);
	DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, pStr);
}

void DpPOP_UdtRangeMax(I08* pStr)
{
	DpSTR_GuiLeft(DpPOP_MAX_X0, DpPOP_MAX_Y0, _cPOP_ST_MAX, _cPOP_BG_WND, _fE17HsB, _sMAX);
	DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MAX_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, pStr);
}

void DpPOP_UdtValue(U08 ln, U08 fSel, I08* pStr)
{
	U32 col;
	U16 y0[2] = {DpPOP_CT1_Y0, DpPOP_CT2_Y0};
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	if(fSel)		col = _cPOP_ST_VAL_SEL;
	else			col = _cPOP_ST_VAL_IDL;

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpFIG_DrwRect(DpPOP_CT1_X0, y0[ln], 100, 30, _cPOP_BG_WND, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpPOP_CT1_X0, y0[ln], col,	 _cPOP_BG_WND, _fE22HsBKOR, pStr);
			break;
		case MnSYS_LANG_ENG:
			DpFIG_DrwRect(DpPOP_CT1_X0, y0[ln], 100, 30, _cPOP_BG_WND, DpFIG_FILL);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[ln], col,     _cPOP_BG_WND, _fE22HsB, pStr);
			break;
	}


}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpPOP_InitMain(void)
{

}

void DpPOP_DrwIntro(void)
{
	// Window
	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_BGD_Y0,     DpPOP_BGD_WD, 4,   _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_BGD_Y0+4,   DpPOP_BGD_WD, 250, _cPOP_BG_WND, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_BGD_Y0+254, DpPOP_BGD_WD, 4,   0xff1C1F24,   DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_BGD_Y0+258, DpPOP_BGD_WD, 4,   0xff1F2F1F,   DpFIG_FILL);
	// Line
	DpFIG_DrwRect(DpPOP_LN0_X0, DpPOP_LN0_Y0, DpPOP_LN0_WD, 2, _cPOP_BG_LN_0, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_LN1_X0, DpPOP_LN1_Y0, DpPOP_LN1_WD, 2, _cPOP_BG_LN_1, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_LN2_X0, DpPOP_LN2_Y0, DpPOP_LN1_WD, 2, _cPOP_BG_LN_1, DpFIG_FILL);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Data Download Progress Popup (BLE trend full download, CMD 0x07/0x17)
//------------------------------------------------------------------------------------------------------------------------------
#define DpPOP_DL_X0		(100)
#define DpPOP_DL_Y0		(140)
#define DpPOP_DL_WD		(600)
#define DpPOP_DL_HT		(220)
#define DpPOP_DL_PAD	(30)
#define DpPOP_DL_BAR_X	(DpPOP_DL_X0 + DpPOP_DL_PAD)
#define DpPOP_DL_BAR_Y	(DpPOP_DL_Y0 + 160)
#define DpPOP_DL_BAR_W	(DpPOP_DL_WD - (DpPOP_DL_PAD * 2))
#define DpPOP_DL_BAR_H	(22)

/* A 하드웨어용 stub — B의 ResetUiLayer는 cascade가 심해 no-op 처리 */
static void DpPOP_ResetUiLayer(void)	{ }

void DpPOP_DrwDLoadStart(void)
{
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0,   DpPOP_DL_WD, 4,              _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0+4, DpPOP_DL_WD, DpPOP_DL_HT-4,  _cPOP_BG_WND, DpFIG_FILL);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 30, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, (I08*)"Data Download");
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 75, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, (I08*)"Downloading...");
	DpFIG_DrwRect(DpPOP_DL_BAR_X, DpPOP_DL_BAR_Y, DpPOP_DL_BAR_W, DpPOP_DL_BAR_H, _cPOP_BG_LN_0, DpFIG_FILL);
	LCD_FlipFrame();
}

void DpPOP_DrwDLoadProgress(U16 done, U16 total)
{
	I08 sLeft[24]  = {0, };
	I08 sRight[12] = {0, };
	U16 pct;
	U16 fillW;

	if(total == 0) total = 1;
	pct = (U16)(((U32)done * 100) / total);
	if(pct > 100) pct = 100;
	fillW = (U16)(((U32)DpPOP_DL_BAR_W * pct) / 100);

	DpFIG_DrwRect(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 115, DpPOP_DL_WD - (DpPOP_DL_PAD * 2), 28, _cPOP_BG_WND, DpFIG_FILL);
	_SPRINTF(sLeft, "%u / %u", done, total);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 115, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sLeft);
	_SPRINTF(sRight, "%u%%", pct);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_WD - DpPOP_DL_PAD - 65, DpPOP_DL_Y0 + 115, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sRight);
	DpFIG_DrwRect(DpPOP_DL_BAR_X, DpPOP_DL_BAR_Y, DpPOP_DL_BAR_W, DpPOP_DL_BAR_H, _cPOP_BG_LN_0, DpFIG_FILL);
	if(fillW > 0)
		DpFIG_DrwRect(DpPOP_DL_BAR_X, DpPOP_DL_BAR_Y, fillW, DpPOP_DL_BAR_H, _cPOP_ST_MIN, DpFIG_FILL);
	LCD_FlipFrame();
}

void DpPOP_DrwDLoadEnd(void)
{
	DpPOP_ResetUiLayer();
	LCD_FlipFrame();
}

//------------------------------------------------------------------------------------------------------------------------------
//  OTA Firmware Update Popup (BLE OTA, CMD 0x50)
//------------------------------------------------------------------------------------------------------------------------------
#define DpPOP_OTA_STS_Y		(DpPOP_DL_Y0 + 115)
#define DpPOP_OTA_RX_Y		(DpPOP_DL_Y0 + 75)

static void OtaPOP_ClearLine(U16 y0, U16 h)
{
	DpFIG_DrwRect(DpPOP_DL_X0 + DpPOP_DL_PAD, y0, DpPOP_DL_WD - (DpPOP_DL_PAD * 2), h, _cPOP_BG_WND, DpFIG_FILL);
}

void DpPOP_DrwOtaStart(void)
{
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0,   DpPOP_DL_WD, 4,              _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0+4, DpPOP_DL_WD, DpPOP_DL_HT-4,  _cPOP_BG_WND, DpFIG_FILL);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 30, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, (I08*)"Firmware Update");
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_RX_Y,   _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, (I08*)"Receiving data...");
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_STS_Y,  _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE17HsB, (I08*)"0 bytes");
	DpFIG_DrwRect(DpPOP_DL_BAR_X, DpPOP_DL_BAR_Y, DpPOP_DL_BAR_W, DpPOP_DL_BAR_H, _cPOP_BG_LN_0, DpFIG_FILL);
	LCD_FlipFrame();
}

void DpPOP_DrwOtaProgress(U32 rxBytes, U32 totalBytes)
{
	I08 sBuf[48] = {0, };
	U16 pct = 0;
	U16 fillW = 0;

	if(totalBytes > 0)
	{
		U32 p = (rxBytes * 100u) / totalBytes;
		if(p > 100u) p = 100u;
		pct = (U16)p;
		fillW = (U16)(((U32)DpPOP_DL_BAR_W * pct) / 100u);
	}

	OtaPOP_ClearLine(DpPOP_OTA_STS_Y, 28);
	if(totalBytes > 0)
	{
		I08 sRight[12] = {0, };
		_SPRINTF(sBuf, "%lu / %lu B", (unsigned long)rxBytes, (unsigned long)totalBytes);
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_STS_Y, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sBuf);
		_SPRINTF(sRight, "%u%%", pct);
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_WD - DpPOP_DL_PAD - 65, DpPOP_OTA_STS_Y, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sRight);
	}
	else
	{
		_SPRINTF(sBuf, "%lu bytes received", (unsigned long)rxBytes);
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_STS_Y, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sBuf);
	}

	DpFIG_DrwRect(DpPOP_DL_BAR_X, DpPOP_DL_BAR_Y, DpPOP_DL_BAR_W, DpPOP_DL_BAR_H, _cPOP_BG_LN_0, DpFIG_FILL);
	if(fillW > 0)
		DpFIG_DrwRect(DpPOP_DL_BAR_X, DpPOP_DL_BAR_Y, fillW, DpPOP_DL_BAR_H, _cPOP_ST_MIN, DpFIG_FILL);
	LCD_FlipFrame();
}

void DpPOP_DrwOtaStatus(const I08 *msg)
{
	OtaPOP_ClearLine(DpPOP_OTA_RX_Y,  22);
	OtaPOP_ClearLine(DpPOP_OTA_STS_Y, 28);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_RX_Y,  _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, (I08*)"Processing...");
	if(msg != 0)
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_STS_Y, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, (I08*)msg);
	LCD_FlipFrame();
}

void DpPOP_DrwOtaResult(U16 result)
{
	I08 *line1;
	I08 *line2;

	switch(result)
	{
		case 0x0001:  line1 = (I08*)"Update complete.";       line2 = (I08*)"Rebooting...";       break;
		case 0x0002:  line1 = (I08*)"Update failed.";         line2 = (I08*)"Data too short";     break;
		case 0x0003:  line1 = (I08*)"Update failed.";         line2 = (I08*)"CRC mismatch";       break;
		case 0x0004:  line1 = (I08*)"Update failed.";         line2 = (I08*)"Flash erase error";  break;
		case 0x0005:  line1 = (I08*)"Update failed.";         line2 = (I08*)"Flash write error";  break;
		case 0x0006:  line1 = (I08*)"Update failed.";         line2 = (I08*)"Timeout";            break;
		default:      line1 = (I08*)"Update failed.";         line2 = (I08*)"Unknown error";      break;
	}

	OtaPOP_ClearLine(DpPOP_OTA_RX_Y,  22);
	OtaPOP_ClearLine(DpPOP_OTA_STS_Y, 28);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_RX_Y,  _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, line1);
	DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_OTA_STS_Y, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, line2);
	LCD_FlipFrame();
}

void DpPOP_DrwOtaEnd(void)
{
	DpPOP_ResetUiLayer();
	LCD_FlipFrame();
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

