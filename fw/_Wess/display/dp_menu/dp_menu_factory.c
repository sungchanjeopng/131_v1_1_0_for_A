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
#include "disp_main.h"
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_button.h"
#include "disp_popup.h"
// menu
#include "menu_main.h"
#include "menu_factory.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
#include "menu_output.h"
// disp - menu
#include "dp_menu_main.h"
#include "dp_menu_system.h"
// self
#include "dp_menu_factory.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpFTR_LS lDpFtr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set)
I08* DpFTR_GetAddrItm(U08 idx)		{	return lDpFtr.sItm[idx];			}
I08* DpFTR_GetAddrVal(U08 idx)		{	return lDpFtr.sVal[idx];			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Additional
//------------------------------------------------------------------------------------------------------------------------------
void DpFTR_AddUpdat(void)
{

}

void DpFTR_AddIntro(void)
{
	// Pop-up Window
	DpPOP_DrwIntro();

	// Title
	switch(MnLY2_GetIdxItem())
	{
		case MnFTR_I00_SS_CH:		_SPRINTF(lDpFtr.pStr, _sCHNNL);			break;
		case MnFTR_I01_CH0_04mA:	_SPRINTF(lDpFtr.pStr, _sCH0_4mA);		break;
		case MnFTR_I02_CH0_20mA:	_SPRINTF(lDpFtr.pStr, _sCH0_20mA);		break;
		case MnFTR_I03_CH1_04mA:	_SPRINTF(lDpFtr.pStr, _sCH1_4mA);		break;
		case MnFTR_I04_CH1_20mA:	_SPRINTF(lDpFtr.pStr, _sCH1_20mA);		break;
		default:					_SPRINTF(lDpFtr.pStr, _sNG);			break;
	}
	DpPOP_UdtTitle(lDpFtr.pStr);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-Up
//------------------------------------------------------------------------------------------------------------------------------
void DpFTR_PopUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();

	DpFIG_DrwRect(x0, y1, 500, 30, cBg, DpFIG_FILL);	


	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iIt)
		{
			case MnFTR_I00_SS_CH:	
				if(val == MnFTR_SS_DUAL)
					_SPRINTF(pSt0, "Dual");
				if(val == MnFTR_SS_SINGLE)
					 _SPRINTF(pSt0, "Single");
				break;
			case MnFTR_I01_CH0_04mA:
			case MnFTR_I02_CH0_20mA:
			case MnFTR_I03_CH1_04mA:
			case MnFTR_I04_CH1_20mA:		_SPRINTF(pSt0, "%05d", val);	break;
			case MnFTR_I05_CH1_TRIM_12MA:
			case MnFTR_I06_CH1_TRIM_20MA:
				if(val>=0)	_SPRINTF(pSt0, "%03d", val);
				else		_SPRINTF(pSt0, "-%03d", abs(val));
				break;
			case MnFTR_I07_CH1_OUTPUT_4MA:	return;
			case MnFTR_I08_CH2_TRIM_12MA:
			case MnFTR_I09_CH2_TRIM_20MA:
				if(val>=0)	_SPRINTF(pSt0, "%03d", val);
				else		_SPRINTF(pSt0, "-%03d", abs(val));
				break;
			case MnFTR_I10_CH2_OUTPUT_4MA:	return;
			case MnFTR_I11_RELAY_TEST:
				_SPRINTF(pSt0, "%02d.%02d", val/100, val%100);	
				break;
			case MnFTR_I12_LANG:
				switch(val)
				{
					case MnSYS_LANG_KOR:		_SPRINTF(pSt0, "Korean");		break;
					case MnSYS_LANG_ENG:		_SPRINTF(pSt0, "English");		break;
					default:					_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnFTR_I13_TIME:		DpSy2Val_TimeUpdat();		return;
			case MnFTR_I14_VERSION:
			case MnFTR_I15_CLEAN_TEST:	return;
			default:
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iIt)
		{
			case MnFTR_OPT_SINGLE_SS_CH:		
				if(val == MnFTR_SS_DUAL)
					_SPRINTF(pSt0, "Dual");
				if(val == MnFTR_SS_SINGLE)
					 _SPRINTF(pSt0, "Single");
				break;
			case MnFTR_OPT_SINGLE_04mA:
			case MnFTR_OPT_SINGLE_20mA:		_SPRINTF(pSt0, "%05d", val);	break;
			case MnFTR_OPT_SINGLE_TRIM_12MA:
			case MnFTR_OPT_SINGLE_TRIM_20MA:
				if(val>=0)	_SPRINTF(pSt0, "%03d", val);
				else		_SPRINTF(pSt0, "-%03d", abs(val));
				break;
			case MnFTR_OPT_SINGLE_OUTPUT_4MA:	return;
			case MnFTR_OPT_SINGLE_RELAY_TEST:
				_SPRINTF(pSt0, "%02d.%02d", val/100, val%100);	
				break;
			case MnFTR_OPT_SINGLE_LANG:
				switch(val)
				{
					case MnSYS_LANG_KOR:		_SPRINTF(pSt0, "Korean");		break;
					case MnSYS_LANG_ENG:		_SPRINTF(pSt0, "English");		break;
					default:					_SPRINTF(pSt0, _sNG);			break;
				}
				break;
			case MnFTR_OPT_SINGLE_TIME:		DpSy2Val_TimeUpdat();		return;
			case MnFTR_OPT_SINGLE_VERSION:
			case MnFTR_OPT_SINGLE_CLEAN_TEST:	return;
			default:
				break;
		}
	}

	
	switch(updn_mod)
	{
		case MENU_V3_UPDN_IDLE:			DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);	break;
		case MENU_V3_UPDN_DIG:
		case MENU_V3_UPDN_DIG_VALUE:	DpSTR_GuiLeftCursor(x0, y0, _cPOP_ST_VAL_SEL, _cMNU_SEL_SCT, cBg, (U08)log10(max)-dig, _fE22HsB, pSt0);	break;
		default:	break;
	}


	if(MnLY3_GetUpdnMod() != MENU_V3_UPDN_DIG_VALUE)
		return;
	
	switch(dig)
	{
		case 4:	
			_SPRINTF(pSt0, "%d", (val/10000)%10);	DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 3:
			_SPRINTF(pSt0, "%d", (val/1000)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 2:
			_SPRINTF(pSt0, "%d", (val/100)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 1:
			_SPRINTF(pSt0, "%d", (val/10)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 0:
			_SPRINTF(pSt0, "%d", val%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
	}
}


void DpFTR_PopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	U08 fDp = _F_T;
	I08 sAct[8] = {0, };
	I08 sStop[8] = {0, };
	U16 act = MnOUT_RlyPrGet_Value(MnOS1_OPT_ACT);
	U16 stop = MnOUT_RlyPrGet_Value(MnOS1_OPT_STOP);

	_SPRINTF(lDpFtr.pStr,lDpFtr.sItm[iIt]);
	#if 0
	// Title
	switch(iIt)
	{
		case MnFTR_I00_SS_CH:		_SPRINTF(lDpFtr.pStr, _sSS_TYPE);		break;
		case MnFTR_I01_CH0_04mA:	_SPRINTF(lDpFtr.pStr, _sCH0_4mA);		break;
		case MnFTR_I02_CH0_20mA:	_SPRINTF(lDpFtr.pStr, _sCH0_20mA);		break;
		case MnFTR_I03_CH1_04mA:	_SPRINTF(lDpFtr.pStr, _sCH1_4mA);		break;
		case MnFTR_I04_CH1_20mA:	_SPRINTF(lDpFtr.pStr, _sCH1_20mA);		break;
		default:					_SPRINTF(lDpFtr.pStr, _sNG);			break;
	}
	#endif
	DpPOP_UdtTitle(lDpFtr.pStr);

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{

	// Old
		switch(iIt)
		{
			case MnFTR_I00_SS_CH:
				switch(val)
				{
					case MnFTR_SS_SINGLE:		_SPRINTF(lDpFtr.pStr, _sSingle);		break;
					case MnFTR_SS_DUAL: 		_SPRINTF(lDpFtr.pStr, _sDual); 			break;
					default:					_SPRINTF(lDpFtr.pStr, _sNG);			break;
				}
				break;
			case MnFTR_I01_CH0_04mA:
			case MnFTR_I02_CH0_20mA:
			case MnFTR_I03_CH1_04mA:
			case MnFTR_I04_CH1_20mA:			
			case MnFTR_I05_CH1_TRIM_12MA:
			case MnFTR_I06_CH1_TRIM_20MA:
				if(val>=0)	_SPRINTF(lDpFtr.pStr, "%d", val);
				else		_SPRINTF(lDpFtr.pStr, "-%d", abs(val));
				break;
			case MnFTR_I07_CH1_OUTPUT_4MA:
				fDp = _F_F;
				break;
			case MnFTR_I08_CH2_TRIM_12MA:
			case MnFTR_I09_CH2_TRIM_20MA:
				if(val>=0)	_SPRINTF(lDpFtr.pStr, "%d", val);
				else		_SPRINTF(lDpFtr.pStr, "-%d", abs(val));
				break;
			case MnFTR_I10_CH2_OUTPUT_4MA:
				fDp = _F_F;
				break;
			case MnFTR_I11_RELAY_TEST:
				fDp = _F_F;
				break;
			case MnFTR_I12_LANG:
				switch(val)
				{
					case MnSYS_LANG_KOR:		_SPRINTF(lDpFtr.pStr, "Korean");		break;
					case MnSYS_LANG_ENG:		_SPRINTF(lDpFtr.pStr, "English");		break;
					default:					_SPRINTF(lDpFtr.pStr, _sNG);			break;
				}
				break;
			case MnFTR_I13_TIME:
				fDp = _F_F;
				DpSy2Val_TimeIntro();
				break;
			case MnFTR_I14_VERSION:
			case MnFTR_I15_CLEAN_TEST:
				fDp = _F_F;
				break;
			default:							_SPRINTF(lDpFtr.pStr, _sNG);			break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iIt)
		{
			case MnFTR_OPT_SINGLE_SS_CH:
				switch(val)
				{
					case MnFTR_SS_SINGLE:		_SPRINTF(lDpFtr.pStr, _sSingle);		break;
					case MnFTR_SS_DUAL: 		_SPRINTF(lDpFtr.pStr, _sDual); 			break;
					default:					_SPRINTF(lDpFtr.pStr, _sNG);			break;
				}
				break;
			case MnFTR_OPT_SINGLE_04mA:
			case MnFTR_OPT_SINGLE_20mA:		
			case MnFTR_OPT_SINGLE_TRIM_12MA:
			case MnFTR_OPT_SINGLE_TRIM_20MA:
				if(val>=0)	_SPRINTF(lDpFtr.pStr, "%d", val);
				else		_SPRINTF(lDpFtr.pStr, "-%d", abs(val));
				break;
			case MnFTR_OPT_SINGLE_OUTPUT_4MA:
				fDp = _F_F;
				break;
			case MnFTR_OPT_SINGLE_RELAY_TEST:
				fDp = _F_F;
				break;
			case MnFTR_OPT_SINGLE_LANG:
				switch(val)
				{
					case MnSYS_LANG_KOR:		_SPRINTF(lDpFtr.pStr, "Korean");		break;
					case MnSYS_LANG_ENG:		_SPRINTF(lDpFtr.pStr, "English");		break;
					default:					_SPRINTF(lDpFtr.pStr, _sNG);			break;
				}
				break;
			case MnFTR_OPT_SINGLE_TIME:
				fDp = _F_F;
				DpSy2Val_TimeIntro();
				break;
			case MnFTR_OPT_SINGLE_VERSION:
			case MnFTR_OPT_SINGLE_CLEAN_TEST:
				fDp = _F_F;
				break;
			default:							_SPRINTF(lDpFtr.pStr, _sNG);			break;
		}

	}
	if(fDp)
		DpPOP_UdtOldVl(lDpFtr.pStr);
	
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		if(iIt==MnFTR_I11_RELAY_TEST)
		{
			_SPRINTF(sAct, "%2d.%02d m", (U16)(act/100), (U16)(act%100));
			_SPRINTF(sStop, "%2d.%02d m", (U16)(stop/100), (U16)(stop%100));



			DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN, _cPOP_BG_WND, _fE17HsB, "ACT");
			DpSTR_GuiLeft(DpPOP_MAX_X0, DpPOP_MAX_Y0, _cPOP_ST_MAX, _cPOP_BG_WND, _fE17HsB, "STOP");

			DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sAct);
			DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MAX_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sStop);
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		if(iIt==MnFTR_OPT_SINGLE_RELAY_TEST)
		{
			_SPRINTF(sAct, "%2d.%02d m", (U16)(act/100), (U16)(act%100));
			_SPRINTF(sStop, "%2d.%02d m", (U16)(stop/100), (U16)(stop%100));
		
		
		
			DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN, _cPOP_BG_WND, _fE17HsB, "ACT");
			DpSTR_GuiLeft(DpPOP_MAX_X0, DpPOP_MAX_Y0, _cPOP_ST_MAX, _cPOP_BG_WND, _fE17HsB, "STOP");
		
			DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sAct);
			DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MAX_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sStop);
		}
	}
#if 0
	// Range (Min. / Max.)
	switch(iIt)
	{
		case MnFTR_I01_CH0_04mA:
		case MnFTR_I03_CH1_04mA:		min = MnFTR_CFG_04mA_MIN;	max = MnFTR_CFG_04mA_MAX;		break;
		case MnFTR_I02_CH0_20mA:
		case MnFTR_I04_CH1_20mA:		min = MnFTR_CFG_20mA_MIN;	max = MnFTR_CFG_20mA_MAX;		break;
		case MnFTR_I00_SS_CH:
		default:
			break;
	}

	if(min != MENU_VAL_INVALID && max != MENU_VAL_INVALID)
		DpPOP_UdtRange(min, max);

	// Explanation
	switch(iIt)
	{
		case MnFTR_I00_SS_CH:
		case MnFTR_I01_CH0_04mA:
		case MnFTR_I03_CH1_04mA:
		case MnFTR_I02_CH0_20mA:
		case MnFTR_I04_CH1_20mA:			_SPRINTF(lDpFtr.pStr, _sSel_PsSet);		break;
		default:							_SPRINTF(lDpFtr.pStr, _sNG);			break;
	}
	DpPOP_UdtExpla(lDpFtr.pStr);

	// Update API
	DpFTR_PopUpdat();
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpFTR_InitVari(void)
{
	S32 val = 0;
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		// Item
		_SPRINTF(lDpFtr.sItm[MnFTR_I00_SS_CH],    _sChnl);
		_SPRINTF(lDpFtr.sItm[MnFTR_I01_CH0_04mA], _sCH0_4mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I02_CH0_20mA], _sCH0_20mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I03_CH1_04mA], _sCH1_4mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I04_CH1_20mA], _sCH1_20mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I05_CH1_TRIM_12MA], _sCH1_Trm_12mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I06_CH1_TRIM_20MA], _sCH1_Trm_20mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I07_CH1_OUTPUT_4MA], _sCH1_OUT_04mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I08_CH2_TRIM_12MA], _sCH2_Trm_12mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I09_CH2_TRIM_20MA], _sCH2_Trm_20mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_I10_CH2_OUTPUT_4MA], _sCH2_OUT_04mA);	
		_SPRINTF(lDpFtr.sItm[MnFTR_I11_RELAY_TEST], "Relay Test");
		_SPRINTF(lDpFtr.sItm[MnFTR_I12_LANG], "Lang");
		_SPRINTF(lDpFtr.sItm[MnFTR_I13_TIME], "Time");	
		_SPRINTF(lDpFtr.sItm[MnFTR_I14_VERSION], "Version");	
		_SPRINTF(lDpFtr.sItm[MnFTR_I15_CLEAN_TEST], "Clean Test");
		
		// Value #0 (Channel)
		_SPRINTF(lDpFtr.sChn[MnFTR_SS_SINGLE], _sSingle);
		_SPRINTF(lDpFtr.sChn[MnFTR_SS_DUAL],   _sDual);
		switch(MnFTR_PrGet_Value(MnFTR_I00_SS_CH))
		{
			case MnFTR_SS_SINGLE:	 	_SPRINTF(lDpFtr.sVal[MnFTR_I00_SS_CH], _sSingle);		break;
			case MnFTR_SS_DUAL:			_SPRINTF(lDpFtr.sVal[MnFTR_I00_SS_CH], _sDual); 		break;
			default:					_SPRINTF(lDpFtr.sVal[MnFTR_I00_SS_CH], _sNG); 			break;
		}
		// Value #1 (Ch0 - Config. 4mA)
		val = MnFTR_PrGet_Value(MnFTR_I01_CH0_04mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I01_CH0_04mA], "%d", val);
		// Value #2 (Ch0 - Config. 20mA)
		val = MnFTR_PrGet_Value(MnFTR_I02_CH0_20mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I02_CH0_20mA], "%d", val);
		// Value #3 (Ch1 - Config. 4mA)
		val = MnFTR_PrGet_Value(MnFTR_I03_CH1_04mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I03_CH1_04mA], "%d", val);
		// Value #4 (Ch1 - Config. 20mA)
		val = MnFTR_PrGet_Value(MnFTR_I04_CH1_20mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I04_CH1_20mA], "%d", val);

		val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_TRM_12mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I05_CH1_TRIM_12MA], "%d", val);
		val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_TRM_20mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I06_CH1_TRIM_20MA], "%d", val);

		_SPRINTF(lDpFtr.sVal[MnFTR_I07_CH1_OUTPUT_4MA], "-");

		val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_TRM_12mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I08_CH2_TRIM_12MA], "%d", val);
		val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_TRM_20mA);	_SPRINTF(lDpFtr.sVal[MnFTR_I09_CH2_TRIM_20MA], "%d", val);

		_SPRINTF(lDpFtr.sVal[MnFTR_I10_CH2_OUTPUT_4MA], "-");

		_SPRINTF(lDpFtr.sVal[MnFTR_I11_RELAY_TEST], "-");

		val = MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_LANG);
		
		switch(val)
		{
			case MnSYS_LANG_ENG:	_SPRINTF(lDpFtr.sVal[MnFTR_I12_LANG],	 "English");	break;
			case MnSYS_LANG_KOR:	DpSTR_GuiList(TEXT_LIST_KOREAN); _SPRINTF(lDpFtr.sVal[MnFTR_I12_LANG],	  gDpStr.Text_list);		break;
			default:
				break;
		}

		_SPRINTF(lDpFtr.sVal[MnFTR_I13_TIME], "-");

		_SPRINTF(lDpFtr.sVal[MnFTR_I14_VERSION], _APP_VERISON);
		_SPRINTF(lDpFtr.sVal[MnFTR_I15_CLEAN_TEST], "-");
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		// Item
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_SS_CH],	  _sChnl);
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_04mA], _sCH0_4mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_20mA], _sCH0_20mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_TRIM_12MA], _sCH1_Trm_12mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_TRIM_20MA], _sCH1_Trm_20mA);
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_OUTPUT_4MA], _sCH1_OUT_04mA);	
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_RELAY_TEST], "Relay Test");
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_LANG], "Lang");
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_TIME], "Time");	
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_VERSION], "Version");	
		_SPRINTF(lDpFtr.sItm[MnFTR_OPT_SINGLE_CLEAN_TEST], "Clean Test");
		
		// Value #0 (Channel)
		_SPRINTF(lDpFtr.sChn[MnFTR_SS_SINGLE], _sSingle);
		_SPRINTF(lDpFtr.sChn[MnFTR_SS_DUAL],   _sDual);
		switch(MnFTR_PrGet_Value(MnFTR_OPT_SINGLE_SS_CH))
		{
			case MnFTR_SS_SINGLE:		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_SS_CH], _sSingle);		break;
			case MnFTR_SS_DUAL: 		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_SS_CH], _sDual); 		break;
			default:					_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_SS_CH], _sNG);			break;
		}
		// Value #1 (Ch0 - Config. 4mA)
		val = MnFTR_PrGet_Value(MnFTR_OPT_SINGLE_04mA);	_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_04mA], "%d", val);
		// Value #2 (Ch0 - Config. 20mA)
		val = MnFTR_PrGet_Value(MnFTR_OPT_SINGLE_20mA);	_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_20mA], "%d", val);
		
		val = MnOUT_CurPrGet_Value(MnOS0_OPT_SINGLE_TRM_12mA); _SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_TRIM_12MA], "%d", val);
		val = MnOUT_CurPrGet_Value(MnOS0_OPT_SINGLE_TRM_20mA); _SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_TRIM_20MA], "%d", val);
		
		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_OUTPUT_4MA], "-");
	
		
		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_RELAY_TEST], "-");
		
		val = MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_LANG);

		switch(val)
		{
			case MnSYS_LANG_ENG:	_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_LANG],	 "English");	break;
			case MnSYS_LANG_KOR:	_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_LANG],	 "Korean");	break;
			default:
				break;
		}
		
		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_TIME], "-");
		
		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_VERSION], _APP_VERISON);
		_SPRINTF(lDpFtr.sVal[MnFTR_OPT_SINGLE_CLEAN_TEST], "-");


	}
	_MEMSET(lDpFtr.pStr, 0, sizeof(lDpFtr.pStr));
}

void DpFT2_StrCntts(void)
{
	U08 i,n,page,idx,iN;

	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iIt = MnLY2_GetIdxItem();
	U08 sel;
	U32 back_color = _cMNU_BOX_BG;
	U32 text_color = _cMNU_STR_IDLE;

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		n = MnFTR_ITM_NUM;
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		n = MnFTR_OPT_SINGLE_NUM;
	
	if 	(iIt >= (DpMNU_ITM_PAGE*5)) 	page = DpMNU_PG_5;
	else if	(iIt >= (DpMNU_ITM_PAGE*4))		page = DpMNU_PG_4;
	else if (iIt >= (DpMNU_ITM_PAGE*3))		page = DpMNU_PG_3;
	else if	(iIt >= (DpMNU_ITM_PAGE*2))		page = DpMNU_PG_2;
	else if (iIt >= (DpMNU_ITM_PAGE*1))		page = DpMNU_PG_1;
	else									page = DpMNU_PG_0;

	sel = (iIt%DpMNU_ITM_PAGE);

	switch(page)
	{
		case DpMNU_PG_0:	
			if(n>DpMNU_ITM_PAGE)		iN=DpMNU_ITM_PAGE;
			else						iN=n;
			break;
		case DpMNU_PG_1:
			if(n>(DpMNU_ITM_PAGE*2))	iN=DpMNU_ITM_PAGE;
			else						iN=n-DpMNU_ITM_PAGE;
			break;			
		case DpMNU_PG_2:
			if(n>(DpMNU_ITM_PAGE*3))	iN=DpMNU_ITM_PAGE;
			else						iN=n-(DpMNU_ITM_PAGE*2);
			break;		
		case DpMNU_PG_3:
			if(n>(DpMNU_ITM_PAGE*4))	iN=DpMNU_ITM_PAGE;
			else						iN=n-(DpMNU_ITM_PAGE*3);
			break;			
		case DpMNU_PG_4:
			if(n>(DpMNU_ITM_PAGE*5))	iN=DpMNU_ITM_PAGE;
			else						iN=n-(DpMNU_ITM_PAGE*4);
			break;		
		case DpMNU_PG_5:
			if(n>(DpMNU_ITM_PAGE*6))	iN=DpMNU_ITM_PAGE;
			else						iN=n-(DpMNU_ITM_PAGE*5);
			break;					
		default:			return;
	}


	// String
	for(i=0; i<iN; i++)
	{

		DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-30-60, 40, _cMNU_BOX_BG, DpFIG_FILL);

		if(MENU_GetLayer()>=MENU_L2_ITEM)
		{
			if(i==sel)
			{
				back_color = _cMNU_SEL_ITM;
				text_color = _cSD_DARKGRAY;
			}
			else
			{
				back_color = _cMNU_BOX_BG;
				text_color = _cMNU_STR_IDLE;				
			}
		}

		idx = i+(DpMNU_ITM_PAGE*page);

		switch(i)
		{
			case MnFTR_I00_SS_CH:
				switch(MnFTR_PrGet_SsChn())
				{
					case MnFTR_SS_SINGLE:	 	_SPRINTF(lDpFtr.sVal[MnFTR_I00_SS_CH], _sSingle);		break;
					case MnFTR_SS_DUAL:			_SPRINTF(lDpFtr.sVal[MnFTR_I00_SS_CH], _sDual); 		break;
					default:					_SPRINTF(lDpFtr.sVal[MnFTR_I00_SS_CH], _sNG); 			break;
				}
				break;
			default:
				break;
		}
		DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, lDpFtr.sItm[idx]);
		DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cTTB_BG_MID, _fE17HsB, lDpFtr.sVal[idx]);
	}
}




//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

