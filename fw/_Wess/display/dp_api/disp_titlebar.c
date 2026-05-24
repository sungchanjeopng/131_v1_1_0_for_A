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
#include "bsp_timer.h"
#include "menu_factory.h"
#include "dp_screen_front.h"
// self
#include "disp_titlebar.h"
#include "data_commu.h"		/* DaBT_GetConnected (BLE 연결 상태) */
#include "bsp_usb.h"			/* BspUsb_GetStatus (USB 연결 상태) */


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpTTB_LS lDpTtb;
U32	lDpTtb_aBgc[16] = {	_cTTB_BG_G00, _cTTB_BG_G01, _cTTB_BG_G02, _cTTB_BG_G03, _cTTB_BG_G04,
						_cTTB_BG_G05, _cTTB_BG_G06, _cTTB_BG_G07, _cTTB_BG_G08, _cTTB_BG_G09,
						_cTTB_BG_G10, _cTTB_BG_G11, _cTTB_BG_G12, _cTTB_BG_G13, _cTTB_BG_G14,	};


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
void DpTTB_InitMain(void)
{

	lDpTtb.bTg_alm = 0;
	lDpTtb.bTg_msr = 0;

}

void DpTTB_SetIconTgl(U08 idx, U08 fEn)
{
	switch(idx)
	{
		case DpTTB_I0_ALM: 		lDpTtb.bTg_alm = fEn;		break;
		case DpTTB_I1_MSR: 		lDpTtb.bTg_msr = fEn;		break;
		case DpTTB_I2_SAV: 		lDpTtb.bTg_sav = fEn;		break;
		case DpTTB_I3_LCK: 		lDpTtb.bTg_lck = fEn;		break;
	}

}

void DpTTB_DrwIcon(U08 idx, U32 col)
{
	U16 x0 = DpTTB_IC_X0 + (DpTTB_IC_xG * idx);
	U16 y0 = DpTTB_IC_Y0;
	U08 opt = DpFIG_FILL;

	switch(idx)
	{
		case DpTTB_IC_USB:
			/* USB icon: 채움 삼각형 없이 선 기반으로 표시(깨짐 방지) */
			DpFIG_DrwLine(x0,   y0-18, x0,   y0+15, col);       /* Center stem */
			DpFIG_DrwLine(x0+1, y0-18, x0+1, y0+15, col);       /* Thickness */
			DpFIG_DrwLine(x0,   y0-18, x0-6, y0-10, col);       /* Top arrow left */
			DpFIG_DrwLine(x0,   y0-18, x0+6, y0-10, col);       /* Top arrow right */
			DpFIG_DrwLine(x0-5, y0-10, x0+5, y0-10, col);       /* Top arrow base */
			DpFIG_DrwLine(x0,   y0-1,  x0-16, y0+8,  col);      /* Left branch */
			DpFIG_DrwLine(x0+1, y0-1,  x0-15, y0+8,  col);
			DpFIG_DrwLine(x0,   y0-1,  x0+16, y0+5,  col);      /* Right branch */
			DpFIG_DrwLine(x0+1, y0-1,  x0+17, y0+5,  col);
			DpFIG_DrwCirc(x0-17, y0+9,  3, col, _F_F);          /* Left node */
			DpFIG_DrwRect(x0+14, y0+2,  7, 7, col, DpFIG_TK_02);/* Right node */
			DpFIG_DrwCirc(x0,    y0+16, 4, col, _F_F);          /* Bottom node */
			break;

		case DpTTB_I0_ALM:
			DpFIG_DrwCirc(x0, y0, 24, col, _F_F);
			DpFIG_DrwCirc(x0, y0, 25, col, _F_F);
			DpFIG_DrwCirc(x0, y0, 26, col, _F_F);
			DpFIG_DrwRect(x0-4, y0-16, 8, 20, col, opt);
			DpFIG_DrwRect(x0-4, y0+10, 8, 8,  col, opt);
			break;

		case DpTTB_I1_MSR:
			DpFIG_DrwCirc(x0,   y0-10, 4, col, _F_T);
			DpFIG_DrwRect(x0-6, y0+1,  12, 4, col, opt);
			DpFIG_DrwRect(x0-9, y0+14, 18, 4, col, opt);
			break;

		case DpTTB_I2_SAV:
			DpFIG_DrwRect(x0-3,  y0-16, 6,  24, col, opt);
			DpFIG_DrwRect(x0-20, y0+16, 38, 4,  col, opt);
			DpFIG_DrwRect(x0-20, y0+9,  8,  10, col, opt);
			DpFIG_DrwRect(x0+12, y0+9,  8,  10, col, opt);
			DpFIG_DrwTria(x0-3,  y0+8, x0-3, y0, x0-10, y0, col);
			DpFIG_DrwTria(x0+3,  y0+8, x0+3, y0, x0+10, y0, col);
			break;

		case DpTTB_I3_LCK:
			DpFIG_DrwRect(x0-3, y0-16, 6, 24, col, opt);
			DpFIG_DrwRect(x0+3, y0-12, 6, 3,  col, opt);
			DpFIG_DrwRect(x0+3, y0-7,  4, 5,  col, opt);
			DpFIG_DrwCirc(x0, y0+10, 9, col, _F_F);
			DpFIG_DrwCirc(x0, y0+10, 8, col, _F_F);
			DpFIG_DrwCirc(x0, y0+10, 7, col, _F_F);
			DpFIG_DrwCirc(x0, y0+10, 6, col, _F_F);
			DpFIG_DrwCirc(x0, y0+10, 5, col, _F_F);
			DpFIG_DrwCirc(x0, y0+10, 4, col, _F_F);
			DpFIG_DrwCirc(x0, y0+10, 3, col, _F_F);
			break;

		case DpTTB_IC_BT:
			/* Bluetooth icon: ble0507/c1d-330 v1_1_0 레퍼런스와 동일한 선 기반 로고 */
			DpFIG_DrwLine(x0,   y0-18, x0,   y0+18, col);
			DpFIG_DrwLine(x0,   y0-18, x0+9, y0-9,  col);
			DpFIG_DrwLine(x0+9, y0-9,  x0,   y0,    col);
			DpFIG_DrwLine(x0,   y0,    x0+9, y0+9,  col);
			DpFIG_DrwLine(x0+9, y0+9,  x0,   y0+18, col);
			DpFIG_DrwLine(x0-9, y0-9,  x0,   y0,    col);
			DpFIG_DrwLine(x0-9, y0+9,  x0,   y0,    col);
			DpFIG_DrwLine(x0+1, y0-18, x0+1, y0+18, col);
			DpFIG_DrwLine(x0+1, y0-18, x0+10, y0-9, col);
			DpFIG_DrwLine(x0+10, y0-9, x0+1, y0,    col);
			DpFIG_DrwLine(x0+1, y0,    x0+10, y0+9, col);
			DpFIG_DrwLine(x0+10, y0+9, x0+1, y0+18, col);
			DpFIG_DrwLine(x0-8, y0-9,  x0+1, y0,    col);
			DpFIG_DrwLine(x0-8, y0+9,  x0+1, y0,    col);
			break;
	}
}

void DpTTB_RunIconTgl(void)
{
	U32 cSel;
	U08 i;

	for(i=0; i<15; i++)
		DpFIG_DrwRect(520, 4*i, 278, 4, lDpTtb_aBgc[i], DpFIG_FILL);

	/* USB 연결 아이콘: 연결 상태에 따라 색상 표시 */
	{
		U32 usbCol;
		switch(BspUsb_GetStatus())
		{
			case BspUsb_ST_MOUNTED:		usbCol = _cSD_GREEN;		break;  /* Mount 완료 */
			case BspUsb_ST_CONNECTED:	usbCol = _cSD_YELLOW;		break;  /* 연결/인식 중 */
			case BspUsb_ST_ERROR:		usbCol = _cSD_RED;			break;  /* Mount 오류 */
			case BspUsb_ST_DISCONNECTED:
			default:					usbCol = _cSD_LIGHTGRAY;	break;  /* 미연결 */
		}
		DpTTB_DrwIcon(DpTTB_IC_USB, usbCol);
	}

	/* BLE 연결 아이콘: 연결 시 초록, 미연결 시 회색 */
	{
		U32 bleCol = (DaBT_GetConnected() == 1) ? _cSD_GREEN : _cSD_LIGHTGRAY;
		DpTTB_DrwIcon(DpTTB_IC_BT, bleCol);
	}

#if 0
	if(!lDpTtb.fFn.b.tgl)
		return;
#endif
	if(lDpTtb.bTg_msr)
	{
		if(lDpTtb.fDp_msr)	lDpTtb.fDp_msr = _F_F;
		else					lDpTtb.fDp_msr = _F_T;

		if(lDpTtb.fDp_msr)	cSel = _cSD_WHITE;
		else					cSel = _cSD_LIGHTGRAY;

		DpTTB_DrwIcon(DpTTB_I1_MSR, cSel);
	}



#if 1
	if(lDpTtb.bTg_alm)
	{
		if(lDpTtb.fDp_alm)		lDpTtb.fDp_alm = _F_F;
		else					lDpTtb.fDp_alm = _F_T;

		if(lDpTtb.fDp_alm)	cSel = _cSD_RED;
		else				cSel = _cSD_LIGHTGRAY;

		DpTTB_DrwIcon(DpTTB_I0_ALM, cSel);
	}


#endif


#if 0
	if(lDpTtb.bTg.b.sav)
	{
		if(lDpTtb.fDp.b.sav)	lDpTtb.fDp.b.sav = _F_F;
		else					lDpTtb.fDp.b.sav = _F_T;

		if(lDpTtb.fDp.b.sav)	cSel = _cSD_WHITE;
		else					cSel = _cSD_LIGHTGRAY;

		DpTTB_DrwIcon(DpTTB_I2_SAV, cSel);
	}
	else
		DpTTB_DrwIcon(DpTTB_I2_SAV, _cTTB_FG_ICON);


	if(lDpTtb.bTg.b.lck)
	{
		if(lDpTtb.fDp.b.lck)	lDpTtb.fDp.b.lck = _F_F;
		else					lDpTtb.fDp.b.lck = _F_T;

		if(lDpTtb.fDp.b.lck)	cSel = _cSD_WHITE;
		else					cSel = _cSD_LIGHTGRAY;

		DpTTB_DrwIcon(DpTTB_I3_LCK, cSel);
	}
	else
		DpTTB_DrwIcon(DpTTB_I3_LCK, _cTTB_FG_ICON);
#endif
}

void DpTTB_UdtIntro(U08 list, U16 x0, U32 col)
{
	U08 i;
	U08 pi_x0 = 30;
	U08 pi_y0 = 30;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	I08 pSt0[16]  = {0, };
	U16 site_name;
	U08 type = MnFTR_PrGet_SsChn();

	// Title Bar & String
	HAL_Delay(1);

	for(i=0; i<16; i++)
		DpFIG_DrwRect(0, 4*i, 798, 4, lDpTtb_aBgc[i], DpFIG_FILL);


	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(list);	
			DpSTR_TitleBar_KOR(gDpStr.Text_list, x0, col);
			break;
		case MnSYS_LANG_ENG:
			switch(list)
			{
				case TEXT_LIST_SLUDGE_LEVEL_METER:	DpSTR_TitleBar("Sludge Level Meter", x0, col);	break;
				case TEXT_LIST_REAL_ECHO_SCREEN:	DpSTR_TitleBar(_sECHO_REAL, x0, col);			break;
				case TEXT_LIST_AVG_ECHO_SCREEN:		DpSTR_TitleBar(_sECHO_AVG, x0, col);			break;
				case TEXT_LIST_PARAMETER_SCREEN:	DpSTR_TitleBar("PARAMETER", x0, col);			break;
				case TEXT_LIST_TANK_SCREEN:			DpSTR_TitleBar("TANK", x0, col);				break;
				case TEXT_LIST_DATA_TREND_SCREEN:	DpSTR_TitleBar("DATA TREND", x0, col);			break;
				case TEXT_LIST_MENU:				DpSTR_TitleBar(_sM_E_N_U, x0, col);				break;
				default:
					break;
			}
			break;
		default:
			break;
	}


#if 0
	DpSTR_TitleBar(pStr, x0, col);
#endif
	// Product Icon - Background
	DpFIG_DrwRect(pi_x0-20, pi_y0-10, 40, 20, _cTTB_FG_PRDT, DpFIG_FILL);		// Rect. Center Hori.
	DpFIG_DrwRect(pi_x0-10, pi_y0-20, 20, 40, _cTTB_FG_PRDT, DpFIG_FILL);		// Rect. Center Vert.
	DpFIG_DrwCirc(pi_x0-10, pi_y0-10, 8, _cTTB_FG_PRDT, _F_T);					// Circ. Conner L&U
	DpFIG_DrwCirc(pi_x0+10, pi_y0-10, 8, _cTTB_FG_PRDT, _F_T);					// Circ. Conner R&U
	DpFIG_DrwCirc(pi_x0-10, pi_y0+10, 8, _cTTB_FG_PRDT, _F_T);					// Circ. Conner L&D
	DpFIG_DrwCirc(pi_x0+10, pi_y0+10, 8, _cTTB_FG_PRDT, _F_T);					// Circ. Conner L&D
	// Product Icon - Figure
	DpFIG_DrwRect(pi_x0-1,  pi_y0-20, 2,  10, _cSD_WHITE, DpFIG_FILL);			// Line. Center Vert.
	DpFIG_DrwRect(pi_x0-5,  pi_y0-12, 10, 8,  _cSD_WHITE, DpFIG_FILL);			// Rect. Body Up
	DpFIG_DrwRect(pi_x0-10, pi_y0-7,  20, 10, _cSD_WHITE, DpFIG_FILL);			// Rect. Body Down
	DpFIG_DrwRect(pi_x0-20, pi_y0-2,  8,  3,  _cSD_WHITE, DpFIG_FILL);			// Line. Water Left
	DpFIG_DrwRect(pi_x0+12, pi_y0-2,  8,  3,  _cSD_WHITE, DpFIG_FILL);			// Line. Water Right
	DpFIG_DrwRect(pi_x0-5,  pi_y0+7,  10, 2,  _cSD_WHITE, DpFIG_FILL);			// Line. Water Right
	DpFIG_DrwRect(pi_x0-9,  pi_y0+13, 18, 2,  _cSD_WHITE, DpFIG_FILL);			// Line. Water Right
	// Status Icon

	//DpTTB_DrwIcon(DpTTB_I0_ALM, _cTTB_FG_ICON);
	//DpTTB_DrwIcon(DpTTB_I1_MSR, _cTTB_FG_ICON);
	//DpTTB_DrwIcon(DpTTB_I2_SAV, _cTTB_FG_ICON);
	//DpTTB_DrwIcon(DpTTB_I3_LCK, _cTTB_FG_ICON);
	
	if(type == MnFTR_SS_SINGLE)
	{
		site_name = MnSYS_PrGet_site_name(APP_CH_1);	

		_SPRINTF(pSt0, "%c%d%d",site_name/100,(site_name%100)/10,(site_name%100)%10);

		DpSTR_GuiLeft(400, 0, _cSD_WHITE, _cTTB_BG_G07, _fE35HsB, pSt0);
	}
	
}

void DpTTB_ProcMain(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

