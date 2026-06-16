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
#include "disp_titlebar.h"
#include "menu_system.h"
#include "menu_main.h"
#include "dp_menu_main.h"
// self
#include "disp_popup.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
#define DpPOP_KOR_USB_U		(53)
#define DpPOP_KOR_USB_S		(51)
#define DpPOP_KOR_USB_B		(34)
#define DpPOP_KOR_F			(38)
#define DpPOP_KOR_W			(55)
#define DpPOP_KOR_PUM		(189)
#define DpPOP_KOR_WE		(114)
#define DpPOP_KOR_EO		(100)
#define DpPOP_KOR_UP		(190)
#define DpPOP_KOR_ASC_LP	(191)
#define DpPOP_KOR_ASC_RP	(192)
#define DpPOP_KOR_ASC_U	(193)
#define DpPOP_KOR_ASC_S	(194)
#define DpPOP_KOR_ASC_B	(195)
#define DpPOP_KOR_SPACE		(173)

static const I08 sPopKorUsbDownload[] = {35, 113, 52, 45, DpPOP_KOR_SPACE, DpPOP_KOR_ASC_LP, DpPOP_KOR_ASC_U, DpPOP_KOR_ASC_S, DpPOP_KOR_ASC_B, DpPOP_KOR_ASC_RP, 0};
static const I08 sPopKorDownload[] = {35, 113, 52, 45, 0};
static const I08 sPopKorFwUpdate[] = {DpPOP_KOR_PUM, DpPOP_KOR_WE, DpPOP_KOR_EO, DpPOP_KOR_SPACE, DpPOP_KOR_UP, 41, 120, 156, DpPOP_KOR_ASC_LP, DpPOP_KOR_ASC_U, DpPOP_KOR_ASC_S, DpPOP_KOR_ASC_B, DpPOP_KOR_ASC_RP, 0};

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
// Match the standard value popup footprint (DpPOP_DrwIntro: X100 Y100 W600 H~262)
// so the export / download progress popup looks the same size as the rest of the UI.
#define DpPOP_DL_X0		(100)
#define DpPOP_DL_Y0		(100)
#define DpPOP_DL_WD		(600)
#define DpPOP_DL_HT		(258)
#define DpPOP_DL_PAD	(30)
#define DpPOP_DL_BAR_X	(DpPOP_DL_X0 + DpPOP_DL_PAD)
#define DpPOP_DL_BAR_Y	(DpPOP_DL_Y0 + 160)
#define DpPOP_DL_BAR_W	(DpPOP_DL_WD - (DpPOP_DL_PAD * 2))
#define DpPOP_DL_BAR_H	(22)

/* A 하드웨어용 stub — B의 ResetUiLayer는 cascade가 심해 no-op 처리 */
static void DpPOP_ResetUiLayer(void)	{ }

void DpPOP_DrwDLoadStart(void)
{
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0,   DpPOP_DL_WD, 4,              _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0+4, DpPOP_DL_WD, DpPOP_DL_HT-4,  _cPOP_BG_WND, DpFIG_FILL);
	if(lang == MnSYS_LANG_KOR)
		DpSTR_GuiLeft_KOR(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 30, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, (I08*)sPopKorDownload);
	else
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

void DpPOP_DrwUsbExportMsg(const I08 *line1, const I08 *line2)
{
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0,   DpPOP_DL_WD, 4,              _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0+4, DpPOP_DL_WD, DpPOP_DL_HT-4,  _cPOP_BG_WND, DpFIG_FILL);
	if(lang == MnSYS_LANG_KOR)
		DpSTR_GuiLeft_KOR(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 30, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, (I08*)sPopKorUsbDownload);
	else
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 30, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, (I08*)"Export (USB)");
	if(line1 != 0)
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 82, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, (I08*)line1);
	if(line2 != 0)
		DpSTR_GuiLeft(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 122, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, (I08*)line2);
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
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0,   DpPOP_DL_WD, 4,              _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpPOP_DL_X0, DpPOP_DL_Y0+4, DpPOP_DL_WD, DpPOP_DL_HT-4,  _cPOP_BG_WND, DpFIG_FILL);
	if(lang == MnSYS_LANG_KOR)
		DpSTR_GuiLeft_KOR(DpPOP_DL_X0 + DpPOP_DL_PAD, DpPOP_DL_Y0 + 30, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, (I08*)sPopKorFwUpdate);
	else
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
		case 0x0007:  line1 = (I08*)"Update failed.";         line2 = (I08*)"USB file error";     break;
		case 0x0008:  line1 = (I08*)"Update failed.";         line2 = (I08*)"Invalid image";      break;
		case 0x0009:  line1 = (I08*)"Update failed.";         line2 = (I08*)"Verify error";       break;
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
//  USB firmware file browser — keeps the native top bar (DpTTB) and bottom button
//  bar (DpMN), draws the file list in the content window between them.
//  NOTE: LCD_FillRect computes (799 - x0 - wid) / (479 - y0 - hei) for the 180-deg
//  panel, so every fill must keep x0+wid <= 799 and y0+hei <= 479 (else U16 underflow
//  -> garbage address -> nothing painted). The whole frame is redrawn each call so
//  it stays correct across the page-flipped framebuffers.
//------------------------------------------------------------------------------------------------------------------------------
#define FB_TOPBAR_H		(64)							// native DpTTB top bar height
#define FB_CONT_Y		(FB_TOPBAR_H)					// content window top (64)
#define FB_CONT_H		(388 - FB_TOPBAR_H)				// content height (up to button-bar line @390)
// NOTE: _fE17HsB glyph CELL height is 27px (top-anchored, extends downward).
// Keep the path text fully clear of the separator below it: path bottom = 70+27 = 97,
// separator at 104 -> 7px gap (previously 74+27=101 vs sep@102 -> bottom clipped/touched).
#define FB_PATH_Y		(FB_TOPBAR_H + 6)				// 70  : current path (27px cell -> 70..97)
#define FB_SEP_Y		(FB_TOPBAR_H + 40)				// 104 : separator (clear of path text)
#define FB_ROW_Y0		(110)							// first list row top
#define FB_ROW_H		(40)							// list row pitch
#define FB_TXT_DY		(5)								// text top offset within a row (27px cell in 36px box)
#define FB_NAME_X		(32)							// name column / left margin
#define FB_SIZE_X		(548)							// size column
#define FB_DATE_X		(656)							// date column

void DpPOP_DrwFileList(const I08 *curDir, const OTA_USB_FILE *list, U08 count,
                       U08 cursor, U08 pageTop, U08 rowsPerPage)
{
	I08 sBuf[48] = {0, };
	U08 row;

	// native top status bar (gradient), title replaced by this screen's name
	DpTTB_UdtIntro(TEXT_LIST_MENU, 70, _cTTB_ST_TITLE);
	if(MnSYS_PrGetBase_Item(MnSYS_OPT_LANG) == MnSYS_LANG_KOR)
		DpSTR_TitleBar_KOR((I08*)sPopKorFwUpdate, 70, _cTTB_ST_TITLE);
	else
		DpSTR_TitleBar((I08*)"Firmware Update (USB)", 70, _cTTB_ST_TITLE);
	DpTTB_RunIconTgl();		// draw the top-right status icons (USB / BLE / alarm / measure)

	// content window background (between top bar and the button-bar line @ y390)
	DpFIG_DrwRect(0, FB_CONT_Y, 799, FB_CONT_H, _cBGD_SCRN, DpFIG_FILL);

	// current path + separator
	DpSTR_GuiLeft(FB_NAME_X, FB_PATH_Y, _cSD_LIGHTGRAY, _cBGD_SCRN, _fE17HsB, (I08*)curDir);
	DpFIG_DrwRect(FB_NAME_X, FB_SEP_Y, 736, 2, _cSD_DARKGRAY, DpFIG_FILL);

	if (count > rowsPerPage)
	{
		U08 curPg = (U08)(pageTop / rowsPerPage) + 1;
		U08 totPg = (U08)((count + rowsPerPage - 1) / rowsPerPage);
		_SPRINTF(sBuf, "%u / %u", curPg, totPg);
		DpSTR_GuiLeft(620, FB_PATH_Y, _cSD_LIGHTGRAY, _cBGD_SCRN, _fE17HsB, sBuf);
	}

	if (count == 0)
	{
		DpSTR_GuiLeft(FB_NAME_X, FB_ROW_Y0 + 40, _cSD_LIGHTGRAY, _cBGD_SCRN, _fE17HsB,
		              (I08*)"No c1d-330 .bin files or folders.");
	}
	else
	{
		for (row = 0; row < rowsPerPage && (U08)(pageTop + row) < count; row++)
		{
			U08 idx = (U08)(pageTop + row);
			U16 ry  = (U16)(FB_ROW_Y0 + (U16)row * FB_ROW_H);
			U16 ty  = (U16)(ry + FB_TXT_DY);
			U32 bg, nameCol, metaCol;

			if (idx == cursor)
			{
				DpFIG_DrwRect(16, ry, 768, FB_ROW_H - 4, _cBTN_BX_SELE, DpFIG_FILL);
				bg = _cBTN_BX_SELE; nameCol = _cSD_WHITE; metaCol = _cSD_WHITE;
			}
			else
			{
				bg      = _cBGD_SCRN;
				nameCol = list[idx].isDir ? _cTTB_FG_PRDT : _cTTB_ST_TITLE;
				metaCol = _cSD_GRAY;
			}

			DpSTR_GuiLeft(FB_NAME_X, ty, nameCol, bg, _fE17HsB, (I08*)list[idx].name);

			if (!list[idx].isDir)
			{
				U16 fd = list[idx].fdate;
				U08 yy = (U08)((((fd >> 9) & 0x7F) + 80) % 100);
				U08 mm = (U08)((fd >> 5) & 0x0F);
				U08 dd = (U08)(fd & 0x1F);

				_SPRINTF(sBuf, "%luKB", (unsigned long)(list[idx].size / 1024u));
				DpSTR_GuiLeft(FB_SIZE_X, ty, metaCol, bg, _fE17HsB, sBuf);

				_SPRINTF(sBuf, "%02u-%02u-%02u", yy, mm, dd);
				DpSTR_GuiLeft(FB_DATE_X, ty, metaCol, bg, _fE17HsB, sBuf);
			}
		}
	}

	// native bottom button bar (BACK / up / down / SET) — same as the menu item layer
	DpMN_UpdtBttn(MENU_L2_ITEM);

	LCD_FlipFrame();
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

