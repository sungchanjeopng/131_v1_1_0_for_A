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
// menu
#include "menu_main.h"
#include "menu_measure.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
// display
#include "disp_main.h"
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_popup.h"
// disp - screen
#include "dp_screen_main.h"
// disp - menu
#include "dp_menu_main.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
#include "menu_factory.h"
// self
#include "dp_menu_measure.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpMSR_LS lDpMsr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set)
I08* DpMSR_GetAddrSct(U08 idx)		{	return lDpMsr.sSct[idx];	}
I08* DpMSR_GetAddrIt0(U08 idx)		{	return lDpMsr.sIt0[idx];	}
I08* DpMSR_GetAddrVl0(U08 idx)		{	return lDpMsr.sVl0[idx];	}
I08* DpMSR_GetAddrIt1(U08 idx)		{	return lDpMsr.sIt1[idx];	}
I08* DpMSR_GetAddrVl1(U08 idx)		{	return lDpMsr.sVl1[idx];	}



//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Additional
//------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Pop-Up
//------------------------------------------------------------------------------------------------------------------------------
void DpMSRBase_DualPopIntro(void)
{
	U08 fDp = _F_T;
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnMSR_BaseGet_Value(iIt);
	S32 min = -1, max = -1;
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			switch(iIt)
			{	// Page #0
				case MnMS0_OPT_UNIT:				_SPRINTF(lDpMsr.pStr, _sUnit);					break;
				case MnMS0_OPT_CH1_OPERATION:		_SPRINTF(lDpMsr.pStr, _sCH1_OPER);				break;
				case MnMS0_OPT_CH1_EMPTY:			_SPRINTF(lDpMsr.pStr, _sCH1_EMPTY); 			break;
				case MnMS0_OPT_CH1_DEADZONE:		_SPRINTF(lDpMsr.pStr, _sCH1_DEADZONE);			break;
				case MnMS0_OPT_CH1_MEASURE_CYCLE:	_SPRINTF(lDpMsr.pStr, _sCH1_MEASURE_CYCLE); 	break;
				case MnMS0_OPT_CH1_MEASURE_RESET:	_SPRINTF(lDpMsr.pStr, _sCH1_MEASURE_RESET); 	break;
				case MnMS0_OPT_CH2_OPERATION:		_SPRINTF(lDpMsr.pStr, _sCH2_OPER);				break;
				case MnMS0_OPT_CH2_EMPTY:			_SPRINTF(lDpMsr.pStr, _sCH2_EMPTY); 			break;
				case MnMS0_OPT_CH2_DEADZONE:		_SPRINTF(lDpMsr.pStr, _sCH2_DEADZONE);			break;
				case MnMS0_OPT_CH2_MEASURE_CYCLE:	_SPRINTF(lDpMsr.pStr, _sCH2_MEASURE_CYCLE); 	break;
				case MnMS0_OPT_CH2_MEASURE_RESET:	_SPRINTF(lDpMsr.pStr, _sCH2_MEASURE_RESET); 	break;		
				default:							_SPRINTF(lDpMsr.pStr, _sNG);					break;
			}
			break;
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt0[iIt]);
			break;
	}

	// Title

	DpPOP_UdtTitle(lDpMsr.pStr);

	// Old Value
	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_UNIT:		
			switch(val)
			{
				case MnMS0_UNIT_METER:		_SPRINTF(lDpMsr.pStr, "Meter");				break;
				case MnMS0_UNIT_PERCENT:	_SPRINTF(lDpMsr.pStr, "Percent");		break;
				default:					_SPRINTF(lDpMsr.pStr, _sNG);				break;
			}
			break;
		case MnMS0_OPT_CH1_OPERATION:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	_SPRINTF(lDpMsr.pStr, "Sludge");			break;
						case MnMS0_OPERATION_DISTANCE:	_SPRINTF(lDpMsr.pStr, "Distance");			break;
						default:						_SPRINTF(lDpMsr.pStr, _sNG);				break;
					}
					break;
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
						case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
						default:						break;
					}				
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;	
					break;
			}
			break;
		case MnMS0_OPT_CH1_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH1_DEADZONE:			_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", val);			break;
		case MnMS0_OPT_CH1_MEASURE_RESET:		fDp = _F_F;									break;
		case MnMS0_OPT_CH2_OPERATION:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	_SPRINTF(lDpMsr.pStr, "Sludge");			break;
						case MnMS0_OPERATION_DISTANCE:	_SPRINTF(lDpMsr.pStr, "Distance");			break;
						default:						_SPRINTF(lDpMsr.pStr, _sNG);				break;
					}
					break;
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
						case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
						default:						break;
					}				
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;	
					break;
			}
			break;
		case MnMS0_OPT_CH2_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH2_DEADZONE:			_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", val);			break;
		case MnMS0_OPT_CH2_MEASURE_RESET:		fDp = _F_F;									break;
		default:																			break;
	}
	
	if(fDp)	DpPOP_UdtOldVl(lDpMsr.pStr);

	fDp = _F_T;
	
	// Range (Min. / Max.)

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_UNIT:					fDp = _F_F;					break;
		case MnMS0_OPT_CH1_OPERATION:		
		case MnMS0_OPT_CH2_OPERATION:			fDp = _F_F;					break;
		case MnMS0_OPT_CH1_EMPTY:				
		case MnMS0_OPT_CH2_EMPTY:				min = MnMS0_EMPTY_MIN;		max = MnMS0_EMPTY_MAX;		break;
		case MnMS0_OPT_CH1_DEADZONE:			
		case MnMS0_OPT_CH2_DEADZONE:			min = MnMS0_DEADZONE_MIN;	max = MnMS0_DEADZONE_MAX;	break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		min = MnMS0_MSR_CYC_MIN;	max = MnMS0_MSR_CYC_MAX;	break;
		case MnMS0_OPT_CH1_MEASURE_RESET:		
		case MnMS0_OPT_CH2_MEASURE_RESET:		fDp = _F_F;									break;
		default:																			break;
	}

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_UNIT:																break;
		case MnMS0_OPT_CH1_OPERATION:		
		case MnMS0_OPT_CH2_OPERATION:														break;
		case MnMS0_OPT_CH1_EMPTY:				
		case MnMS0_OPT_CH2_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;
		case MnMS0_OPT_CH1_DEADZONE:			
		case MnMS0_OPT_CH2_DEADZONE:			_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", min);			break;
		case MnMS0_OPT_CH1_MEASURE_RESET:		
		case MnMS0_OPT_CH2_MEASURE_RESET:													break;
		default:																			break;
	}


	if(fDp)	DpPOP_UdtRangeMin(lDpMsr.pStr);

	fDp = _F_T;

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_UNIT:					fDp = _F_F;					break;
		case MnMS0_OPT_CH1_OPERATION:		
		case MnMS0_OPT_CH2_OPERATION:			fDp = _F_F;					break;
		case MnMS0_OPT_CH1_EMPTY:				
		case MnMS0_OPT_CH2_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;
		case MnMS0_OPT_CH1_DEADZONE:			
		case MnMS0_OPT_CH2_DEADZONE:			_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", max);			break;
		case MnMS0_OPT_CH1_MEASURE_RESET:		
		case MnMS0_OPT_CH2_MEASURE_RESET:		fDp = _F_F;									break;
		default:																			break;
	}


	if(fDp)	DpPOP_UdtRangeMax(lDpMsr.pStr);

	_SPRINTF(lDpMsr.pStr, _sSel_PsSet);


	DpPOP_UdtExpla(lDpMsr.pStr);

}

void DpMSRBase_SinglePopIntro(void)
{
	U08 fDp = _F_T;
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnMSR_BaseGet_Value(iIt);
	S32 min = -1, max = -1;
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt0[iIt]);
			break;
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt0[iIt]);
			break;
	}

	// Title

	DpPOP_UdtTitle(lDpMsr.pStr);

	// Old Value
	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_SINGLE_UNIT:		
			switch(val)
			{
				case MnMS0_UNIT_METER:		_SPRINTF(lDpMsr.pStr, "Meter");				break;
				case MnMS0_UNIT_PERCENT:	_SPRINTF(lDpMsr.pStr, "Percent");		break;
				default:					_SPRINTF(lDpMsr.pStr, _sNG);				break;
			}
			break;
		case MnMS0_OPT_SINGLE_OPERATION:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	_SPRINTF(lDpMsr.pStr, "Sludge");			break;
						case MnMS0_OPERATION_DISTANCE:	_SPRINTF(lDpMsr.pStr, "Distance");			break;
						default:						_SPRINTF(lDpMsr.pStr, _sNG);				break;
					}
					break;
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
						case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
						default:						break;
					}				
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;	
					break;
			}
			break;
		case MnMS0_OPT_SINGLE_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_SINGLE_DEADZONE:			_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", val);			break;
		case MnMS0_OPT_SINGLE_MEASURE_RESET:		fDp = _F_F;										break;
		default:																					break;
	}
	
	if(fDp)	DpPOP_UdtOldVl(lDpMsr.pStr);

	fDp = _F_T;
	
	// Range (Min. / Max.)

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_SINGLE_UNIT:					fDp = _F_F;					break;
		case MnMS0_OPT_SINGLE_OPERATION:			fDp = _F_F;					break;			
		case MnMS0_OPT_SINGLE_EMPTY:				min = MnMS0_EMPTY_MIN;		max = MnMS0_EMPTY_MAX;		break;		
		case MnMS0_OPT_SINGLE_DEADZONE:				min = MnMS0_DEADZONE_MIN;	max = MnMS0_DEADZONE_MAX;		break;	
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		min = MnMS0_MSR_CYC_MIN;	max = MnMS0_MSR_CYC_MAX;	break;	
		case MnMS0_OPT_SINGLE_MEASURE_RESET:		fDp = _F_F;												break;
		default:																							break;
	}

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_SINGLE_UNIT:																break;
		case MnMS0_OPT_SINGLE_OPERATION:														break;	
		case MnMS0_OPT_SINGLE_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;	
		case MnMS0_OPT_SINGLE_DEADZONE:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", min);		break;	
		case MnMS0_OPT_SINGLE_MEASURE_RESET:													break;
		default:																				break;
	}


	if(fDp)	DpPOP_UdtRangeMin(lDpMsr.pStr);

	fDp = _F_T;

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_SINGLE_UNIT:					fDp = _F_F;					break;	
		case MnMS0_OPT_SINGLE_OPERATION:			fDp = _F_F;					break;		
		case MnMS0_OPT_SINGLE_EMPTY:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;		
		case MnMS0_OPT_SINGLE_DEADZONE:				_SPRINTF(lDpMsr.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;		
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		_SPRINTF(lDpMsr.pStr, "%d sec", max);			break;		
		case MnMS0_OPT_SINGLE_MEASURE_RESET:		fDp = _F_F;										break;
		default:																					break;
	}


	if(fDp)	DpPOP_UdtRangeMax(lDpMsr.pStr);

	_SPRINTF(lDpMsr.pStr, _sSel_PsSet);


	DpPOP_UdtExpla(lDpMsr.pStr);

}



void DpMSRBase_PopIntro(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSRBase_DualPopIntro();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSRBase_SinglePopIntro();

}

void DpMSRBase_DualPopUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y1 = DpPOP_CT2_Y0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_UNIT:		
			switch(val)
			{
				case MnMS0_UNIT_METER:		_SPRINTF(pSt0, "Meter");			break;
				case MnMS0_UNIT_PERCENT:	_SPRINTF(pSt0, "Percent");		break;
				default:					_SPRINTF(pSt0, _sNG);				break;
			}
			break;
		case MnMS0_OPT_CH1_OPERATION:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	_SPRINTF(pSt0, "Sludge");			break;
						case MnMS0_OPERATION_DISTANCE:	_SPRINTF(pSt0, "Distance");			break;
						default:						_SPRINTF(pSt0, _sNG);				break;
					}
					break;
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
						case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
						default:						break;
					}				
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
			}
			break;
		case MnMS0_OPT_CH1_EMPTY:				_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH1_DEADZONE:			_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH1_MEASURE_CYCLE:		_SPRINTF(pSt0, "%02d", val);				break;
		case MnMS0_OPT_CH1_MEASURE_RESET:
												DpSTR_InitMain();
												DpPOP_UdtValue(0,	_F_F, gDpStr.sYnN[0]);
												DpPOP_UdtValue(1,	_F_F, gDpStr.sYnN[1]);
												DpPOP_UdtValue(val, _F_T, gDpStr.sYnN[val]);	return;
		case MnMS0_OPT_CH2_OPERATION:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	_SPRINTF(pSt0, "Sludge");			break;
						case MnMS0_OPERATION_DISTANCE:	_SPRINTF(pSt0, "Distance");			break;
						default:						_SPRINTF(pSt0, _sNG);				break;
					}
					break;
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
						case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
						default:						break;
					}				
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
			}
			break;
		case MnMS0_OPT_CH2_EMPTY:				_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH2_DEADZONE:			_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_CH2_MEASURE_CYCLE:		_SPRINTF(pSt0, "%02d", val);				break;
		case MnMS0_OPT_CH2_MEASURE_RESET:		DpSTR_InitMain();
												DpPOP_UdtValue(0,	_F_F, gDpStr.sYnN[0]);
												DpPOP_UdtValue(1,	_F_F, gDpStr.sYnN[1]);
												DpPOP_UdtValue(val, _F_T, gDpStr.sYnN[val]);	return;
		default:																				break;
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
	DpFIG_DrwRect(x0, y1, 500, 30, cBg, DpFIG_FILL);	

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

void DpMSRBase_SinglePopUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y1 = DpPOP_CT2_Y0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{	// Page #0
		case MnMS0_OPT_SINGLE_UNIT:		
			switch(val)
			{
				case MnMS0_UNIT_METER:		_SPRINTF(pSt0, "Meter");			break;
				case MnMS0_UNIT_PERCENT:	_SPRINTF(pSt0, "Percent");		break;
				default:					_SPRINTF(pSt0, _sNG);				break;
			}
			break;
		case MnMS0_OPT_SINGLE_OPERATION:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	_SPRINTF(pSt0, "Sludge");			break;
						case MnMS0_OPERATION_DISTANCE:	_SPRINTF(pSt0, "Distance");			break;
						default:						_SPRINTF(pSt0, _sNG);				break;
					}
					break;
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
						case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
						default:						break;
					}				
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
			}
			break;
		case MnMS0_OPT_SINGLE_EMPTY:				_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_SINGLE_DEADZONE:			_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;
		case MnMS0_OPT_SINGLE_MEASURE_CYCLE:		_SPRINTF(pSt0, "%02d", val);				break;
		case MnMS0_OPT_SINGLE_MEASURE_RESET:
			DpSTR_InitMain();
			DpPOP_UdtValue(0,	_F_F, gDpStr.sYnN[0]);
			DpPOP_UdtValue(1,	_F_F, gDpStr.sYnN[1]);
			DpPOP_UdtValue(val, _F_T, gDpStr.sYnN[val]);
			return;
		default:		
			break;
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
	DpFIG_DrwRect(x0, y1, 500, 30, cBg, DpFIG_FILL);	

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

void DpMSRBase_PopUpdat(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSRBase_DualPopUpdat();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSRBase_SinglePopUpdat();

}

void DpMSR_Cal_DualPopAddintro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val3 = MnMSR_CalGet_Value(iIt);
	S32 val2 = MnMSR_Get_Threshold_Value(iIt);
	S32 val = MnLY3_GetValue();
	S32 min = -1, max = -1;
	U08 fDp = _F_T; 							
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			switch(iIt)
			{	// Page #0
				case MnMS1_OPT_CH1_THR_LIGHT:		_SPRINTF(lDpMsr.pStr, _sCH1_THR_LIGHT);		break;
				case MnMS1_OPT_CH1_THR_HEAVY:		_SPRINTF(lDpMsr.pStr, _sCH1_THR_HEAVY);		break;
				case MnMS1_OPT_CH2_THR_LIGHT:		_SPRINTF(lDpMsr.pStr, _sCH2_THR_LIGHT);		break;
				case MnMS1_OPT_CH2_THR_HEAVY:		_SPRINTF(lDpMsr.pStr, _sCH2_THR_HEAVY);		break;
				default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
			}			
			break;
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt1[iIt]);
			break;
	}

	if(fDp) DpPOP_UdtTitle(lDpMsr.pStr);

	// Old Value
	switch(iIt)
	{	// Page #0

		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(val3)
			{
				case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, "%1d.%01d v", (U16)(val2/10), (U16)(val2%10));			break;
				case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr," %d %c", val2,37);											break;
				default:						break;
			}
			break;
		default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}

	if(fDp)	DpPOP_UdtOldVl(lDpMsr.pStr);


	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_AUTO:		min = MnMS1_THR_VAL_AUTO_MIN;	max= MnMS1_THR_VAL_AUTO_MAX;	break;
				case MnMS1_THRESHOLD_MANUAL: 	min = MnMS1_THR_VAL_MANUAL_MIN;	max= MnMS1_THR_VAL_MANUAL_MAX;	break;
				default:						break;
			}
			break;
		default:							_SPRINTF(lDpMsr.pStr, _sNG);							break;
	}

	switch(iIt)
	{	// Page #0

		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_MANUAL:		_SPRINTF(lDpMsr.pStr, "%1d.%01d v", (U16)(min/10), (U16)(min%10));			break;
				case MnMS1_THRESHOLD_AUTO:			_SPRINTF(lDpMsr.pStr," %d %c", min,37);											break;
				default:						break;
			}
			break;
		default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}



	if(fDp)	DpPOP_UdtRangeMin(lDpMsr.pStr);

	fDp = _F_T;
	
	switch(iIt)
	{	// Page #0

		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, "%1d.%01d v", (U16)(max/10), (U16)(max%10));			break;
				case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr, " %d %c", max,37);										break;
				default:						break;
			}
			break;
		default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}


	if(fDp)	DpPOP_UdtRangeMax(lDpMsr.pStr);

	_SPRINTF(lDpMsr.pStr, _sSel_PsSet);

	DpPOP_UdtExpla(lDpMsr.pStr);


}


void DpMSR_Cal_SinglePopAddintro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val3 = MnMSR_CalGet_Value(iIt);
	S32 val2 = MnMSR_Get_Threshold_Value(iIt);
	S32 val = MnLY3_GetValue();
	S32 min = -1, max = -1;
	U08 fDp = _F_T; 							
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			switch(iIt)
			{	// Page #0
				case MnMS1_OPT_SINGLE_THR_LIGHT:		_SPRINTF(lDpMsr.pStr, _sThr_light);		break;
				case MnMS1_OPT_SINGLE_THR_HEAVY:		_SPRINTF(lDpMsr.pStr, _sThr_heavy);		break;
				default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
			}			
			break;
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt1[iIt]);
			break;
	}

	if(fDp) DpPOP_UdtTitle(lDpMsr.pStr);

	// Old Value
	switch(iIt)
	{	// Page #0		
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(val3)
			{
				case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, "%1d.%01d v", (U16)(val2/10), (U16)(val2%10));			break;
				case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr," %d %c", val2,37);										break;
				default:						break;
			}
			break;
		default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}

	if(fDp)	DpPOP_UdtOldVl(lDpMsr.pStr);


	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_SINGLE_THR_LIGHT:		
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_AUTO:		min = MnMS1_THR_VAL_AUTO_MIN;	max= MnMS1_THR_VAL_AUTO_MAX;	break;
				case MnMS1_THRESHOLD_MANUAL: 	min = MnMS1_THR_VAL_MANUAL_MIN;	max= MnMS1_THR_VAL_MANUAL_MAX;	break;
				default:						break;
			}
			break;
		default:							_SPRINTF(lDpMsr.pStr, _sNG);							break;
	}

	switch(iIt)
	{	// Page #0
	
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_MANUAL:		_SPRINTF(lDpMsr.pStr, "%1d.%01d v", (U16)(min/10), (U16)(min%10));			break;
				case MnMS1_THRESHOLD_AUTO:			_SPRINTF(lDpMsr.pStr," %d %c", min,37);											break;
				default:						break;
			}
			break;
		default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}



	if(fDp)	DpPOP_UdtRangeMin(lDpMsr.pStr);

	fDp = _F_T;
	
	switch(iIt)
	{	// Page #0

		case MnMS1_OPT_SINGLE_THR_LIGHT:		
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, "%1d.%01d v", (U16)(max/10), (U16)(max%10));			break;
				case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr, " %d %c", max,37);										break;
				default:						break;
			}
			break;
		default:								_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}


	if(fDp)	DpPOP_UdtRangeMax(lDpMsr.pStr);

	_SPRINTF(lDpMsr.pStr, _sSel_PsSet);

	DpPOP_UdtExpla(lDpMsr.pStr);

}





void DpMSR_Cal_PopAddintro(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSR_Cal_DualPopAddintro();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSR_Cal_SinglePopAddintro();	


}


void DpMSR_Cal_DualPopAddupdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	S32 val2 = MnLY4_GetValue();	
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	// Old Value
	switch(iIt)
	{	// Page #0

		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(pSt0, "%1d.%01d", (U16)(val2/10), (U16)(val2%10));			break;
				case MnMS1_THRESHOLD_AUTO:		_SPRINTF(pSt0, "%d", val2);											break;
				default:						break;
			}
			break;
		default:								_SPRINTF(pSt0, _sNG);				break;
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
			_SPRINTF(pSt0, "%d", (abs(val)/10000)%10);	DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 3:
			_SPRINTF(pSt0, "%d", (abs(val)/1000)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 2:
			_SPRINTF(pSt0, "%d", (abs(val)/100)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 1:
			_SPRINTF(pSt0, "%d", (abs(val)/10)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 0:
			_SPRINTF(pSt0, "%d", abs(val)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
	}

}

void DpMSR_Cal_SinglePopAddupdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnLY3_GetValue();
	S32 val2 = MnLY4_GetValue();	
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	// Old Value
	switch(iIt)
	{	// Page #
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(val)
			{
				case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(pSt0, "%1d.%01d", (U16)(val2/10), (U16)(val2%10));			break;
				case MnMS1_THRESHOLD_AUTO:		_SPRINTF(pSt0, "%d", val2);											break;
				default:						break;
			}
			break;
		default:								_SPRINTF(pSt0, _sNG);				break;
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
			_SPRINTF(pSt0, "%d", (abs(val)/10000)%10);	DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 3:
			_SPRINTF(pSt0, "%d", (abs(val)/1000)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 2:
			_SPRINTF(pSt0, "%d", (abs(val)/100)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 1:
			_SPRINTF(pSt0, "%d", (abs(val)/10)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 0:
			_SPRINTF(pSt0, "%d", abs(val)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
	}

}

void DpMSRCal_PopAddupdat(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSR_Cal_DualPopAddupdat();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSR_Cal_SinglePopAddupdat();	
}


void DpMSRCal_DualPopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnMSR_CalGet_Value(iIt);
	S32 min = -1, max = -1;
	U08 fDp = _F_T; 							
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt1[iIt]);
		#if 0
			switch(iIt)
			{	// Page #0
				case MnMS1_OPT_CH1_FREQ:			_SPRINTF(lDpMsr.pStr, _sCH1_FREQ);			break;
				case MnMS1_OPT_CH1_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, _sCH1_ECHO_AMP);		break;
				case MnMS1_OPT_CH1_THR_LIGHT:		_SPRINTF(lDpMsr.pStr, _sCH1_THR_LIGHT); 	break;
				case MnMS1_OPT_CH1_THR_HEAVY:		_SPRINTF(lDpMsr.pStr, _sCH1_THR_HEAVY); 	break;
				case MnMS1_OPT_CH1_ASF_LIGHT: 		_SPRINTF(lDpMsr.pStr, _sCH1_ASF_LIGHT);		break;
				case MnMS1_OPT_CH1_ASF_HEAVY: 		_SPRINTF(lDpMsr.pStr, _sCH1_ASF_HEAVY);		break;				
				case MnMS1_OPT_CH1_DAMPING: 		_SPRINTF(lDpMsr.pStr, _sCH1_DAMPING);		break;
				case MnMS1_OPT_CH1_OFFSET:			_SPRINTF(lDpMsr.pStr, _sCH1_OFFSET);		break;
				case MnMS1_OPT_CH2_FREQ:			_SPRINTF(lDpMsr.pStr, _sCH2_FREQ);			break;
				case MnMS1_OPT_CH2_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, _sCH2_ECHO_AMP);		break;
				case MnMS1_OPT_CH2_THR_LIGHT:		_SPRINTF(lDpMsr.pStr, _sCH2_THR_LIGHT); 	break;
				case MnMS1_OPT_CH2_THR_HEAVY:		_SPRINTF(lDpMsr.pStr, _sCH2_THR_HEAVY); 	break;
				case MnMS1_OPT_CH2_ASF_LIGHT: 		_SPRINTF(lDpMsr.pStr, _sCH2_ASF_LIGHT);		break;
				case MnMS1_OPT_CH2_ASF_HEAVY: 		_SPRINTF(lDpMsr.pStr, _sCH2_ASF_HEAVY);		break;	
				case MnMS1_OPT_CH2_DAMPING: 		_SPRINTF(lDpMsr.pStr, _sCH2_DAMPING);		break;
				case MnMS1_OPT_CH2_OFFSET:			_SPRINTF(lDpMsr.pStr, _sCH2_OFFSET);		break;
				default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
			}
		#endif
			break;
		case MnSYS_LANG_KOR:
			switch(iIt)
			{	// Page #0
				case MnMS1_OPT_CH1_ASF_LIGHT: 			
					DpSTR_GuiList(TEXT_LIST_CH1_LIGHT); 
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0,DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+190, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "ASF");
					DpSTR_GuiList(TEXT_LIST_SET);	
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+250, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;
					break;
				case MnMS1_OPT_CH1_ASF_HEAVY: 			
					DpSTR_GuiList(TEXT_LIST_CH1_HEAVY); 
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0,DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+190, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "ASF");
					DpSTR_GuiList(TEXT_LIST_SET);	
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+250, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;
					break;					
				case MnMS1_OPT_CH2_ASF_LIGHT: 			
					DpSTR_GuiList(TEXT_LIST_CH2_LIGHT); 
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0,DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+190, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "ASF");
					DpSTR_GuiList(TEXT_LIST_SET);	
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+250, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;
					break;
				case MnMS1_OPT_CH2_ASF_HEAVY: 			
					DpSTR_GuiList(TEXT_LIST_CH2_HEAVY); 
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0,DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+190, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "ASF");
					DpSTR_GuiList(TEXT_LIST_SET);	
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+250, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;
					break;		
				default:
					_SPRINTF(lDpMsr.pStr, lDpMsr.sIt1[iIt]);
					break;
			}
			break;

	}


	
	if(fDp)	 DpPOP_UdtTitle(lDpMsr.pStr);

	fDp = _F_T;

	// Old Value
	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_CH1_FREQ:
		case MnMS1_OPT_CH2_FREQ:
			switch(val)
			{
				case MnMS1_FREQ_380K:		_SPRINTF(lDpMsr.pStr, "380kHz");		break;
				case MnMS1_FREQ_270K:		_SPRINTF(lDpMsr.pStr, "270kHz");		break;
				case MnMS1_FREQ_160K:		_SPRINTF(lDpMsr.pStr, "160kHz");		break;
				case MnMS1_FREQ_130K:		_SPRINTF(lDpMsr.pStr, "130kHz");		break;
				default:					break;
			}
			break;
		case MnMS1_OPT_CH1_ECHO_AMP:		
		case MnMS1_OPT_CH2_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, "%d", val);			break;
		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr, _sAUTO);			break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, _sMANUAL);		break;
						default:						break;
					}
					break;	
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		DpSTR_GuiList(TEXT_LIST_AUTO);		break;
						case MnMS1_THRESHOLD_MANUAL:	DpSTR_GuiList(TEXT_LIST_MANUAL);		break;
						default:						break;
					}
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);					
					break;						
			}
			break;
		case MnMS1_OPT_CH1_ASF_LIGHT:	
		case MnMS1_OPT_CH1_ASF_HEAVY:		
		case MnMS1_OPT_CH2_ASF_LIGHT:	
		case MnMS1_OPT_CH2_ASF_HEAVY:		_SPRINTF(lDpMsr.pStr, "%d", val);			break;
		case MnMS1_OPT_CH1_DAMPING:			
		case MnMS1_OPT_CH2_DAMPING:			_SPRINTF(lDpMsr.pStr, "%d", val);			break;
		case MnMS1_OPT_CH1_OFFSET:			
		case MnMS1_OPT_CH2_OFFSET:			
			if(val>=0)	_SPRINTF(lDpMsr.pStr, "%01d.%02d m", val/100, val%100);
			else		_SPRINTF(lDpMsr.pStr, "-%01d.%02d m", (abs(val)/100), (abs(val)%100));
			break;			
		default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}

	if(fDp)	DpPOP_UdtOldVl(lDpMsr.pStr);

	fDp = _F_T;

	
	// Range (Min. / Max.)

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_CH1_FREQ:
		case MnMS1_OPT_CH2_FREQ:			break;
		case MnMS1_OPT_CH1_ECHO_AMP:		
		case MnMS1_OPT_CH2_ECHO_AMP:		min = MnMS1_ECHO_AMP_MIN;	max	 = MnMS1_ECHO_AMP_MAX;	break;
		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:		break;
		case MnMS1_OPT_CH1_ASF_LIGHT:	
		case MnMS1_OPT_CH1_ASF_HEAVY:		
		case MnMS1_OPT_CH2_ASF_LIGHT:	
		case MnMS1_OPT_CH2_ASF_HEAVY:		min = MnMS1_ASF_MIN;		max = MnMS1_ASF_MAX;		break;
		case MnMS1_OPT_CH1_DAMPING:			
		case MnMS1_OPT_CH2_DAMPING:			min = MnMS1_DAMPING_MIN;	max = MnMS1_DAMPING_MAX;	break;
		case MnMS1_OPT_CH1_OFFSET:			
		case MnMS1_OPT_CH2_OFFSET:			min = MnMS1_OFFSET_MIN;		max = MnMS1_OFFSET_MAX;		break;
		default:							_SPRINTF(lDpMsr.pStr, _sNG);							break;
	}

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_CH1_FREQ:
		case MnMS1_OPT_CH2_FREQ:			fDp = _F_F;									break;
		case MnMS1_OPT_CH1_ECHO_AMP:		
		case MnMS1_OPT_CH2_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, "%d", min);			break;
		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:		fDp = _F_F;									break;
		case MnMS1_OPT_CH1_ASF_LIGHT:	
		case MnMS1_OPT_CH1_ASF_HEAVY:		
		case MnMS1_OPT_CH2_ASF_LIGHT:	
		case MnMS1_OPT_CH2_ASF_HEAVY:		_SPRINTF(lDpMsr.pStr, "%d", min);			break;
		case MnMS1_OPT_CH1_DAMPING:			
		case MnMS1_OPT_CH2_DAMPING:			_SPRINTF(lDpMsr.pStr, "%d", min);			break;
		case MnMS1_OPT_CH1_OFFSET:
		case MnMS1_OPT_CH2_OFFSET:
			if(val>=0)	_SPRINTF(lDpMsr.pStr, "%01d.%02d m", min/100, min%100);
			else		_SPRINTF(lDpMsr.pStr, "-%01d.%02d m", (abs(min)/100), (abs(min)%100));
			break;

		default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}


	if(fDp)	DpPOP_UdtRangeMin(lDpMsr.pStr);

	fDp = _F_T;

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_CH1_FREQ:
		case MnMS1_OPT_CH2_FREQ:			fDp = _F_F;									break;
		case MnMS1_OPT_CH1_ECHO_AMP:		
		case MnMS1_OPT_CH2_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, "%d", max);			break;
		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:		fDp = _F_F;									break;
		case MnMS1_OPT_CH1_ASF_LIGHT:	
		case MnMS1_OPT_CH1_ASF_HEAVY:		
		case MnMS1_OPT_CH2_ASF_LIGHT:	
		case MnMS1_OPT_CH2_ASF_HEAVY:		_SPRINTF(lDpMsr.pStr, "%d", max);			break;
		case MnMS1_OPT_CH1_DAMPING:			
		case MnMS1_OPT_CH2_DAMPING:			_SPRINTF(lDpMsr.pStr, "%d", max);			break;
		case MnMS1_OPT_CH1_OFFSET:
		case MnMS1_OPT_CH2_OFFSET:
			if(val>=0)	_SPRINTF(lDpMsr.pStr, "%01d.%02d m", max/100, max%100);
			else		_SPRINTF(lDpMsr.pStr, "-%01d.%02d m", (abs(max)/100), (abs(max)%100));
			break;
		default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}


	if(fDp)	DpPOP_UdtRangeMax(lDpMsr.pStr);

	fDp = _F_T;
	
	_SPRINTF(lDpMsr.pStr, _sSel_PsSet);

	DpPOP_UdtExpla(lDpMsr.pStr);

}

void DpMSRCal_SinglePopintro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnMSR_CalGet_Value(iIt);
	S32 min = -1, max = -1;
	U08 fDp = _F_T; 							
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpMsr.pStr, lDpMsr.sIt1[iIt]);
			break;
		case MnSYS_LANG_KOR:
			switch(iIt)
			{	// Page #0
				case MnMS1_OPT_SINGLE_ASF_LIGHT: 			
					DpSTR_GuiList(TEXT_LIST_LIGHT); 
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0,DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "ASF");
					DpSTR_GuiList(TEXT_LIST_SET);	
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+170, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;
					break;
				case MnMS1_OPT_SINGLE_ASF_HEAVY: 			
					DpSTR_GuiList(TEXT_LIST_HEAVY); 
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0,DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "ASF");
					DpSTR_GuiList(TEXT_LIST_SET);	
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+170, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					fDp = _F_F;
					break;					
				default:
					_SPRINTF(lDpMsr.pStr, lDpMsr.sIt1[iIt]);
					break;
			}
			break;

	}


	
	if(fDp)	 DpPOP_UdtTitle(lDpMsr.pStr);

	fDp = _F_T;

	// Old Value
	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_SINGLE_FREQ:
			switch(val)
			{
				case MnMS1_FREQ_380K:		_SPRINTF(lDpMsr.pStr, "380kHz");		break;
				case MnMS1_FREQ_270K:		_SPRINTF(lDpMsr.pStr, "270kHz");		break;
				case MnMS1_FREQ_160K:		_SPRINTF(lDpMsr.pStr, "160kHz");		break;
				case MnMS1_FREQ_130K:		_SPRINTF(lDpMsr.pStr, "130kHz");		break;
				default:					break;
			}
			break;	
		case MnMS1_OPT_SINGLE_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, "%d", val);			break;
		case MnMS1_OPT_SINGLE_THR_LIGHT:		
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr, _sAUTO);			break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, _sMANUAL);		break;
						default:						break;
					}
					break;	
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		DpSTR_GuiList(TEXT_LIST_AUTO);		break;
						case MnMS1_THRESHOLD_MANUAL:	DpSTR_GuiList(TEXT_LIST_MANUAL);		break;
						default:						break;
					}
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);					
					break;						
			}
			break;
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	
		case MnMS1_OPT_SINGLE_ASF_HEAVY:	_SPRINTF(lDpMsr.pStr, "%d", val);			break;		
		case MnMS1_OPT_SINGLE_DAMPING:		_SPRINTF(lDpMsr.pStr, "%d", val);			break;
		case MnMS1_OPT_SINGLE_OFFSET:					
			if(val>=0)	_SPRINTF(lDpMsr.pStr, "%01d.%02d m", val/100, val%100);
			else		_SPRINTF(lDpMsr.pStr, "-%01d.%02d m", (abs(val)/100), (abs(val)%100));
			break;			
		default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}

	if(fDp)	DpPOP_UdtOldVl(lDpMsr.pStr);

	fDp = _F_T;

	
	// Range (Min. / Max.)

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_SINGLE_FREQ:			break;
		case MnMS1_OPT_SINGLE_ECHO_AMP:		min = MnMS1_ECHO_AMP_MIN;	max	 = MnMS1_ECHO_AMP_MAX;	break;		
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:	break;
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	
		case MnMS1_OPT_SINGLE_ASF_HEAVY:	min = MnMS1_ASF_MIN;		max = MnMS1_ASF_MAX;		break;		
		case MnMS1_OPT_SINGLE_DAMPING:		min = MnMS1_DAMPING_MIN;	max = MnMS1_DAMPING_MAX;	break;			
		case MnMS1_OPT_SINGLE_OFFSET:		min = MnMS1_OFFSET_MIN;		max = MnMS1_OFFSET_MAX;		break;
		default:							_SPRINTF(lDpMsr.pStr, _sNG);							break;
	}

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_SINGLE_FREQ:			fDp = _F_F;									break;
		case MnMS1_OPT_SINGLE_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, "%d", min);			break;
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:		fDp = _F_F;									break;	
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	
		case MnMS1_OPT_SINGLE_ASF_HEAVY:		_SPRINTF(lDpMsr.pStr, "%d", min);			break;	
		case MnMS1_OPT_SINGLE_DAMPING:			_SPRINTF(lDpMsr.pStr, "%d", min);			break;
		case MnMS1_OPT_SINGLE_OFFSET:
			if(val>=0)	_SPRINTF(lDpMsr.pStr, "%01d.%02d m", min/100, min%100);
			else		_SPRINTF(lDpMsr.pStr, "-%01d.%02d m", (abs(min)/100), (abs(min)%100));
			break;

		default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}


	if(fDp)	DpPOP_UdtRangeMin(lDpMsr.pStr);

	fDp = _F_T;

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_SINGLE_FREQ:			fDp = _F_F;									break;	
		case MnMS1_OPT_SINGLE_ECHO_AMP:		_SPRINTF(lDpMsr.pStr, "%d", max);			break;	
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:		fDp = _F_F;									break;	
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	
		case MnMS1_OPT_SINGLE_ASF_HEAVY:		_SPRINTF(lDpMsr.pStr, "%d", max);			break;		
		case MnMS1_OPT_SINGLE_DAMPING:			_SPRINTF(lDpMsr.pStr, "%d", max);			break;
		case MnMS1_OPT_SINGLE_OFFSET:
			if(val>=0)	_SPRINTF(lDpMsr.pStr, "%01d.%02d m", max/100, max%100);
			else		_SPRINTF(lDpMsr.pStr, "-%01d.%02d m", (abs(max)/100), (abs(max)%100));
			break;
		default:							_SPRINTF(lDpMsr.pStr, _sNG);				break;
	}


	if(fDp)	DpPOP_UdtRangeMax(lDpMsr.pStr);

	fDp = _F_T;
	
	_SPRINTF(lDpMsr.pStr, _sSel_PsSet);

	DpPOP_UdtExpla(lDpMsr.pStr);


}



void DpMSRCal_PopIntro(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSRCal_DualPopIntro();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSRCal_SinglePopintro();	
}


void DpMSRCal_DualPopUpdat(void)
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
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_CH1_FREQ:
		case MnMS1_OPT_CH2_FREQ:
			switch(val)
			{
				case MnMS1_FREQ_380K:		_SPRINTF(pSt0, "380kHz");		break;
				case MnMS1_FREQ_270K:		_SPRINTF(pSt0, "270kHz");		break;
				case MnMS1_FREQ_160K:		_SPRINTF(pSt0, "160kHz");		break;
				case MnMS1_FREQ_130K:		_SPRINTF(pSt0, "130kHz");		break;
				default:					break;
			}
			break;
		case MnMS1_OPT_CH1_ECHO_AMP:		
		case MnMS1_OPT_CH2_ECHO_AMP:		_SPRINTF(pSt0, "%02d", val);			break;
		case MnMS1_OPT_CH1_THR_LIGHT:		
		case MnMS1_OPT_CH2_THR_LIGHT:
		case MnMS1_OPT_CH1_THR_HEAVY:
		case MnMS1_OPT_CH2_THR_HEAVY:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr, _sAUTO);			break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, _sMANUAL);		break;
						default:						break;
					}
					DpSTR_GuiLeft(x0, y0,	_cPOP_ST_VAL_SEL,	  cBg, _fE22HsB, lDpMsr.pStr);	
					break;	
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		DpSTR_GuiList(TEXT_LIST_AUTO);		break;
						case MnMS1_THRESHOLD_MANUAL:	DpSTR_GuiList(TEXT_LIST_MANUAL);	break;
						default:						break;
					}
					DpSTR_GuiLeft_KOR(x0, y0,	_cPOP_ST_VAL_SEL,	  cBg, _fE22HsBKOR, gDpStr.Text_list);					
					break;						
			}
			break;
		case MnMS1_OPT_CH1_ASF_LIGHT:	
		case MnMS1_OPT_CH1_ASF_HEAVY:		
		case MnMS1_OPT_CH2_ASF_LIGHT:	
		case MnMS1_OPT_CH2_ASF_HEAVY:		_SPRINTF(pSt0, "%04d", val);			break;
		case MnMS1_OPT_CH1_DAMPING:			
		case MnMS1_OPT_CH2_DAMPING:			_SPRINTF(pSt0, "%03d", val);			break;
		case MnMS1_OPT_CH1_OFFSET:
		case MnMS1_OPT_CH2_OFFSET:
			if(val>=0)						_SPRINTF(pSt0, "%01d.%02d", (U16)(abs(val)/100), (U16)(abs(val)%100));
			else							_SPRINTF(pSt0, "-%01d.%02d", (U16)(abs(val)/100), (U16)(abs(val)%100));
			break;
		default:							_SPRINTF(pSt0, _sNG);				break;
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
			_SPRINTF(pSt0, "%d", (abs(val)/10000)%10);	DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 3:
			_SPRINTF(pSt0, "%d", (abs(val)/1000)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 2:
			_SPRINTF(pSt0, "%d", (abs(val)/100)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 1:
			_SPRINTF(pSt0, "%d", (abs(val)/10)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 0:
			_SPRINTF(pSt0, "%d", abs(val)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
	}


}

void DpMSRCal_SinglePopUpdat(void)
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
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{	// Page #0
		case MnMS1_OPT_SINGLE_FREQ:
			switch(val)
			{
				case MnMS1_FREQ_380K:		_SPRINTF(pSt0, "380kHz");		break;
				case MnMS1_FREQ_270K:		_SPRINTF(pSt0, "270kHz");		break;
				case MnMS1_FREQ_160K:		_SPRINTF(pSt0, "160kHz");		break;
				case MnMS1_FREQ_130K:		_SPRINTF(pSt0, "130kHz");		break;
				default:					break;
			}
			break;		
		case MnMS1_OPT_SINGLE_ECHO_AMP:		_SPRINTF(pSt0, "%02d", val);			break;	
		case MnMS1_OPT_SINGLE_THR_LIGHT:
		case MnMS1_OPT_SINGLE_THR_HEAVY:
			switch(lang)
			{
				case MnSYS_LANG_ENG:	
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.pStr, _sAUTO);			break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.pStr, _sMANUAL);		break;
						default:						break;
					}
					DpSTR_GuiLeft(x0, y0,	_cPOP_ST_VAL_SEL,	  cBg, _fE22HsB, lDpMsr.pStr);	
					break;	
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnMS1_THRESHOLD_AUTO:		DpSTR_GuiList(TEXT_LIST_AUTO);		break;
						case MnMS1_THRESHOLD_MANUAL:	DpSTR_GuiList(TEXT_LIST_MANUAL);	break;
						default:						break;
					}
					DpSTR_GuiLeft_KOR(x0, y0,	_cPOP_ST_VAL_SEL,	  cBg, _fE22HsBKOR, gDpStr.Text_list);					
					break;						
			}
			break;	
		case MnMS1_OPT_SINGLE_ASF_LIGHT:	
		case MnMS1_OPT_SINGLE_ASF_HEAVY:		_SPRINTF(pSt0, "%04d", val);			break;			
		case MnMS1_OPT_SINGLE_DAMPING:			_SPRINTF(pSt0, "%03d", val);			break;
		case MnMS1_OPT_SINGLE_OFFSET:
			if(val>=0)						_SPRINTF(pSt0, "%01d.%02d", (U16)(abs(val)/100), (U16)(abs(val)%100));
			else							_SPRINTF(pSt0, "-%01d.%02d", (U16)(abs(val)/100), (U16)(abs(val)%100));
			break;
		default:							_SPRINTF(pSt0, _sNG);				break;
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
			_SPRINTF(pSt0, "%d", (abs(val)/10000)%10);	DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 3:
			_SPRINTF(pSt0, "%d", (abs(val)/1000)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 2:
			_SPRINTF(pSt0, "%d", (abs(val)/100)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 1:
			_SPRINTF(pSt0, "%d", (abs(val)/10)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 0:
			_SPRINTF(pSt0, "%d", abs(val)%10); DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
	}


}


void DpMSRCal_PopUpdat(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSRCal_DualPopUpdat();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSRCal_SinglePopUpdat();	


}



void DpMSR_PopUpdat(void)
{
	U08 sub = MnLY1_GetSection();

	switch(sub)
	{
		case MnMSR_SUB_BASE:		DpMSRBase_PopUpdat();	break;
		case MnMSR_SUB_CAL:			DpMSRCal_PopUpdat();	break;
		default:
			break;
	}

}

void DpMSR_PopIntro(void)
{
	U08 sub = MnLY1_GetSection();

	switch(sub)
	{
		case MnMSR_SUB_BASE:		DpMSRBase_PopIntro();	break;
		case MnMSR_SUB_CAL:			DpMSRCal_PopIntro();	break;
		default:
			break;
	}
	
	// Update API
	DpMSR_PopUpdat();

}

void DpMSR_AddIntro(void)
{
	U08 sub = MnLY1_GetSection();
	
	switch(sub)
	{
		case MnMSR_SUB_BASE:
			DpFIG_DrwRect(DpPOP_CT1_X0-5, 	DpPOP_CT2_Y0, 200, 40, _cPOP_BG_WND, DpFIG_FILL); 		// Clear
			DpSTR_GuiLeft(DpPOP_CT1_X0,     DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, _sRst);
			DpSTR_GuiLeft(DpPOP_CT1_X0+100, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, _sDone);
			DpFIG_DrwRect(DpPOP_EXP_X0-5, 	DpPOP_EXP_Y0, 400, 20,_cPOP_BG_WND, DpFIG_FILL); 		// Clear
			DpPOP_UdtExpla(_sExit_Prskey);
			break;
		case MnMSR_SUB_CAL:
			DpPOP_DrwIntro();
			DpMSR_Cal_PopAddintro();
			DpMSRCal_PopAddupdat();
			break;
		default:	
			break;
	}

}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpMSR_InitDualVari(void)
{
	S32 val = 0;
	// Item - Base 
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_BASE);
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_BASE],    gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CALIBRATION);
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_CAL], 	gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_UNIT);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_UNIT], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_OPERATION);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_OPERATION], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_EMPTY);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_EMPTY],  gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_DEADZONE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_DEADZONE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_MSR_CYC);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_MEASURE_CYCLE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_MSR_RST);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_MEASURE_RESET],   gDpStr.Text_list);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_OPERATION], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_OPERATION);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_OPERATION], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_EMPTY);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_EMPTY],  gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_DEADZONE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_DEADZONE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_MSR_CYC);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_MEASURE_CYCLE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_MSR_RST);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_MEASURE_RESET],   gDpStr.Text_list);

				
			// Item - FieldA
			DpSTR_GuiList(TEXT_LIST_CH1_FREQ);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_FREQ],  	     gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_ECHO_AMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_ECHO_AMP],    gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_THR_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_THR_LIGHT],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_THR_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_THR_HEAVY],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_ASF_LIGHT],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_ASF_HEAVY],   gDpStr.Text_list);			
			DpSTR_GuiList(TEXT_LIST_CH1_DAMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_DAMPING],     gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_OFFSET);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_OFFSET], 	 gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_FREQ);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_FREQ],  	     gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_ECHO_AMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_ECHO_AMP],    gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_THR_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_THR_LIGHT],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_THR_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_THR_HEAVY],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_ASF_LIGHT],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_ASF_HEAVY],   gDpStr.Text_list);		
			DpSTR_GuiList(TEXT_LIST_CH2_DAMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_DAMPING],     gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_OFFSET);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_OFFSET], 	 gDpStr.Text_list);

			break;
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_BASE],    _sBase);
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_CAL], 	_sCalibration);

			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_UNIT], _sUnit);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_OPERATION], _sCH1_OPER);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_EMPTY],  _sCH1_EMPTY);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_DEADZONE], _sCH1_DEADZONE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_MEASURE_CYCLE], _sCH1_MEASURE_CYCLE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH1_MEASURE_RESET],   _sCH1_MEASURE_RESET);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_OPERATION], _sCH2_OPER);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_EMPTY],  _sCH2_EMPTY);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_DEADZONE], _sCH2_DEADZONE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_MEASURE_CYCLE], _sCH2_MEASURE_CYCLE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_CH2_MEASURE_RESET],   _sCH2_MEASURE_RESET);
				
			// Item - FieldA
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_FREQ],  	     _sCH1_FREQ);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_ECHO_AMP],    _sCH1_ECHO_AMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_THR_LIGHT],   _sCH1_THR_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_THR_HEAVY],   _sCH1_THR_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_ASF_LIGHT],   _sCH1_ASF_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_ASF_HEAVY],   _sCH1_ASF_HEAVY);			
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_DAMPING],     _sCH1_DAMPING);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH1_OFFSET], 	 _sCH1_OFFSET);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_FREQ],  	     _sCH2_FREQ);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_ECHO_AMP],    _sCH2_ECHO_AMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_THR_LIGHT],   _sCH2_THR_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_THR_HEAVY],   _sCH2_THR_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_ASF_LIGHT],   _sCH2_ASF_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_ASF_HEAVY],   _sCH2_ASF_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_DAMPING],     _sCH2_DAMPING);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_CH2_OFFSET], 	 _sCH2_OFFSET);
			break;
	}

	// Value - Base
	switch(MnMSR_BaseGet_Value(MnMS0_OPT_UNIT))
	{
		case MnMS0_UNIT_METER:		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_UNIT], "Meter"); 			break;	
		case MnMS0_UNIT_PERCENT:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_UNIT], "Percent");		break;
		default:					_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_UNIT], _sNG);				break;
	}

	switch(MnMSR_BaseGet_Value(MnMS0_OPT_CH1_OPERATION))
	{
		case MnMS0_OPERATION_SLUDGE:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_OPERATION], "Sludge"); 			break;	
		case MnMS0_OPERATION_DISTANCE:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_OPERATION], "Distance");			break;
		default:						_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_OPERATION], _sNG);				break;
	}
	
	val = MnMSR_BaseGet_Value(MnMS0_OPT_CH1_EMPTY);		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_EMPTY], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnMSR_BaseGet_Value(MnMS0_OPT_CH1_DEADZONE);	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_DEADZONE], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnMSR_BaseGet_Value(MnMS0_OPT_CH1_MEASURE_CYCLE);		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_MEASURE_CYCLE], " %d sec",val);

	switch(MnMSR_BaseGet_Value(MnMS0_OPT_CH2_OPERATION))
	{
		case MnMS0_OPERATION_SLUDGE:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_OPERATION], "Sludge"); 			break;	
		case MnMS0_OPERATION_DISTANCE:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_OPERATION], "Distance");			break;
		default:						_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_OPERATION], _sNG);				break;
	}
	
	val = MnMSR_BaseGet_Value(MnMS0_OPT_CH2_EMPTY);		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_EMPTY], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnMSR_BaseGet_Value(MnMS0_OPT_CH2_DEADZONE);	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_DEADZONE], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnMSR_BaseGet_Value(MnMS0_OPT_CH2_MEASURE_CYCLE);		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_MEASURE_CYCLE], " %d sec", val);


	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH1_MEASURE_RESET], "-");
	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_CH2_MEASURE_RESET], "-");

	switch(MnMSR_CalGet_Value(MnMS1_OPT_CH1_FREQ))
	{
		case MnMS1_FREQ_380K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_FREQ], " 380kHz");	break;
		case MnMS1_FREQ_270K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_FREQ], " 270kHz");	break;
		case MnMS1_FREQ_160K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_FREQ], " 160kHz");	break;
		case MnMS1_FREQ_130K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_FREQ], " 130kHz");	break;
		default:						break;
	}
	
	switch(MnMSR_CalGet_Value(MnMS1_OPT_CH2_FREQ))
	{
		case MnMS1_FREQ_380K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_FREQ], " 380kHz");	break;
		case MnMS1_FREQ_270K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_FREQ], " 270kHz");	break;
		case MnMS1_FREQ_160K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_FREQ], " 160kHz");	break;
		case MnMS1_FREQ_130K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_FREQ], " 130kHz");	break;
		default:						break;
	}

	val = MnMSR_CalGet_Value(MnMS1_OPT_CH1_ECHO_AMP);		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_ECHO_AMP], " %d", val);

	val = MnMSR_Get_Threshold_Value(MnMS1_OPT_CH1_THR_LIGHT);

	switch(MnMSR_CalGet_Value(MnMS1_OPT_CH1_THR_LIGHT))
	{
		case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_THR_LIGHT], " %d %c", val,37);	break;
		case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_THR_LIGHT], " %01d.%01d v", (U16)(val/10), (U16)(val%10)); 	break;
		default:
			break;
	}

	val = MnMSR_Get_Threshold_Value(MnMS1_OPT_CH1_THR_HEAVY);

	switch(MnMSR_CalGet_Value(MnMS1_OPT_CH1_THR_HEAVY))
	{
		case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_THR_HEAVY], " %d %c", val,37);	break;
		case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH1_THR_HEAVY], " %01d.%01d v", (U16)(val/10), (U16)(val%10)); 	break;
		default:
			break;
	}

	val = MnMSR_Get_Threshold_Value(MnMS1_OPT_CH2_THR_LIGHT);

	switch(MnMSR_CalGet_Value(MnMS1_OPT_CH2_THR_LIGHT))
	{
		case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_THR_LIGHT], " %d %c", val,37);	break;
		case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_THR_LIGHT], " %01d.%01d v", (U16)(val/10), (U16)(val%10)); 	break;
		default:
			break;
	}

	val = MnMSR_Get_Threshold_Value(MnMS1_OPT_CH2_THR_HEAVY);

	switch(MnMSR_CalGet_Value(MnMS1_OPT_CH2_THR_HEAVY))
	{
		case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_THR_HEAVY], " %d %c", val,37);	break;
		case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_THR_HEAVY], " %01d.%01d v", (U16)(val/10), (U16)(val%10)); 	break;
		default:
			break;
	}

	
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH1_ASF_LIGHT);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH1_ASF_LIGHT)], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH1_ASF_HEAVY);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH1_ASF_HEAVY)], " %d", val);	
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH1_DAMPING);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH1_DAMPING)], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH1_OFFSET);			

	if(val>=0)		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH1_OFFSET)], "%01d.%02d m", (val/100), (val%100));
	else			_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH1_OFFSET)], "-%01d.%02d m", (abs(val)/100), (abs(val)%100));

	val = MnMSR_CalGet_Value(MnMS1_OPT_CH2_ECHO_AMP);		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_CH2_ECHO_AMP], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH2_ASF_LIGHT);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH2_ASF_LIGHT)], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH2_ASF_HEAVY);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH2_ASF_HEAVY)], " %d", val);	
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH2_DAMPING);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH2_DAMPING)], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_CH2_OFFSET);

	if(val>=0)		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH2_OFFSET)], " %01d.%02d m", (val/100), (val%100));
	else			_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_CH2_OFFSET)], " -%01d.%02d m", (abs(val)/100), (abs(val)%100));

	_MEMSET(lDpMsr.pStr, 0, sizeof(lDpMsr.pStr));


}

void DpMSR_InitSingleVari(void)
{

	S32 val = 0;
	// Item - Base 
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_BASE);
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_BASE],    gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CALIBRATION);
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_CAL], 	gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_UNIT);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_UNIT], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_OPERATION);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_OPERATION], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_EMPTY);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_EMPTY],  gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_DEADZONE);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_DEADZONE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_MSR_CYC);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_MEASURE_CYCLE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_MSR_RST);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_MEASURE_RESET],   gDpStr.Text_list);

				
			// Item - FieldA
			DpSTR_GuiList(TEXT_LIST_FREQ);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_FREQ],  	     gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_ECHO_AMP);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_ECHO_AMP],    gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_THR_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_THR_LIGHT],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_THR_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_THR_HEAVY],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_ASF_LIGHT],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_HEAVY);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_ASF_HEAVY],   gDpStr.Text_list);			
			DpSTR_GuiList(TEXT_LIST_DAMPING);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_DAMPING],     gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_OFFSET);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_OFFSET], 	 gDpStr.Text_list);
			break;
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_BASE],    _sBase);
			_SPRINTF(lDpMsr.sSct[MnMSR_SUB_CAL], 	_sCalibration);

			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_UNIT], _sUnit);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_OPERATION], _sOperation);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_EMPTY],  _sEmpty);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_DEADZONE], _sDeadzone);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_MEASURE_CYCLE], _sMeasure_cycle);
			_SPRINTF(lDpMsr.sIt0[MnMS0_OPT_SINGLE_MEASURE_RESET],   _sMeasure_reset);

				
			// Item - FieldA
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_FREQ],  	     _sFrequency);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_ECHO_AMP],    _sEcho_Amp);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_THR_LIGHT],   _sThr_light);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_THR_HEAVY],   _sThr_heavy);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_ASF_LIGHT],   _sASF_LIGHT);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_ASF_HEAVY],   _sASF_HEAVY);			
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_DAMPING],     _sDamping);
			_SPRINTF(lDpMsr.sIt1[MnMS1_OPT_SINGLE_OFFSET], 	 	_sOffset);
			break;
	}


	// Value - Base
	switch(MnMSR_BaseGet_Value(MnMS0_OPT_SINGLE_UNIT))
	{
		case MnMS0_UNIT_METER:		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_UNIT], "Meter"); 			break;	
		case MnMS0_UNIT_PERCENT:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_UNIT], "Percent");		break;
		default:					_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_UNIT], _sNG);				break;
	}

	switch(MnMSR_BaseGet_Value(MnMS0_OPT_SINGLE_OPERATION))
	{
		case MnMS0_OPERATION_SLUDGE:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_OPERATION], "Sludge"); 			break;	
		case MnMS0_OPERATION_DISTANCE:	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_OPERATION], "Distance");			break;
		default:						_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_OPERATION], _sNG);				break;
	}
	
	val = MnMSR_BaseGet_Value(MnMS0_OPT_SINGLE_EMPTY);		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_EMPTY], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnMSR_BaseGet_Value(MnMS0_OPT_SINGLE_DEADZONE);	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_DEADZONE], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnMSR_BaseGet_Value(MnMS0_OPT_SINGLE_MEASURE_CYCLE);		_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_MEASURE_CYCLE], " %d sec",val);



	_SPRINTF(lDpMsr.sVl0[MnMS0_OPT_SINGLE_MEASURE_RESET], "-");

	switch(MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_FREQ))
	{
		case MnMS1_FREQ_380K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_FREQ], " 380kHz");	break;
		case MnMS1_FREQ_270K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_FREQ], " 270kHz");	break;
		case MnMS1_FREQ_160K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_FREQ], " 160kHz");	break;
		case MnMS1_FREQ_130K:			_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_FREQ], " 130kHz");	break;
		default:						break;
	}
	

	val = MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_ECHO_AMP);		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_ECHO_AMP], " %d", val);

	val = MnMSR_Get_Threshold_Value(MnMS1_OPT_SINGLE_THR_LIGHT);

	switch(MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_THR_LIGHT))
	{
		case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_THR_LIGHT], " %d %c", val,37);	break;
		case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_THR_LIGHT], " %01d.%01d v", (U16)(val/10), (U16)(val%10)); 	break;
		default:
			break;
	}

	val = MnMSR_Get_Threshold_Value(MnMS1_OPT_SINGLE_THR_HEAVY);

	switch(MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_THR_HEAVY))
	{
		case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_THR_HEAVY], " %d %c", val,37);	break;
		case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpMsr.sVl1[MnMS1_OPT_SINGLE_THR_HEAVY], " %01d.%01d v", (U16)(val/10), (U16)(val%10)); 	break;
		default:
			break;
	}



	val = MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_ASF_LIGHT);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_SINGLE_ASF_LIGHT)], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_ASF_HEAVY);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_SINGLE_ASF_HEAVY)], " %d", val);	
	val = MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_DAMPING);		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_SINGLE_DAMPING)], " %d", val);
	val = MnMSR_CalGet_Value(MnMS1_OPT_SINGLE_OFFSET);			

	if(val>=0)		_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_SINGLE_OFFSET)], "%01d.%02d m", (val/100), (val%100));
	else			_SPRINTF(lDpMsr.sVl1[(MnMS1_OPT_SINGLE_OFFSET)], "-%01d.%02d m", (abs(val)/100), (abs(val)%100));



	_MEMSET(lDpMsr.pStr, 0, sizeof(lDpMsr.pStr));

}

void DpMSR_InitVari(void)
{

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSR_InitDualVari();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSR_InitSingleVari();
	
}


void DpMS1_StrSbSct(void)
{
	U08 i=0;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:

			DpSTR_GuiList(TEXT_LIST_BASE);
			DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*MnMSR_SUB_BASE), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CALIBRATION);
			DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*MnMSR_SUB_CAL), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, gDpStr.Text_list);
			break;		
		case MnSYS_LANG_ENG:
			for(i=0; i<MnMSR_SUB_NUM; i++)
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, lDpMsr.sSct[i]);
			break;
		default:
			break;
	}

}



void DpMSR_StrDualCntts(U08 idx)
{
	U08 i, n, page, iN, id;
	I08 *pItm, *pVal;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iIt = MnLY2_GetIdxItem();
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U64 back_color = _cMNU_BOX_BG;
	U64 text_color = _cMNU_STR_IDLE;



	switch(idx)
	{
		case MnMSR_SUB_BASE:		n = MnMS0_OPT_NUM;			break;
		case MnMSR_SUB_CAL: 		n = MnMS1_OPT_NUM;			break;
		default:					return;
	}

	if		(iIt >= (DpMNU_ITM_PAGE*2)) 	page = DpMNU_PG_2;
	else if (iIt >= (DpMNU_ITM_PAGE*1)) 	page = DpMNU_PG_1;
	else									page = DpMNU_PG_0;

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
		default:			return;
	}

	sel = (iIt%DpMNU_ITM_PAGE);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			for(i=0; i<iN; i++)
			{
				id = i+(DpMNU_ITM_PAGE*page);
				switch(idx)
				{
					case MnMSR_SUB_BASE:	pItm = lDpMsr.sIt0[id]; 	pVal = lDpMsr.sVl0[id]; break;
					case MnMSR_SUB_CAL: 	pItm = lDpMsr.sIt1[id]; 	pVal = lDpMsr.sVl1[id]; break;
					default:				return;
				}

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

				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, pItm);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
			}			
			break;
		case MnSYS_LANG_KOR:
			for(i=0; i<iN; i++)
			{
				id = i+(DpMNU_ITM_PAGE*page);
				DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-30-60, 37, _cMNU_BOX_BG, DpFIG_FILL);
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
				switch(idx)
				{
					case MnMSR_SUB_BASE:	
						pItm = lDpMsr.sIt0[id]; 	pVal = lDpMsr.sVl0[id]; 
						switch(id)
						{
							case MnMS0_OPT_CH1_OPERATION: 
								switch(MnMSR_BaseGet_Value(MnMS0_OPT_CH1_OPERATION))
								{
									case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
									case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
									default:						break;
								}				
								DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiList(TEXT_LIST_CH1_OPERATION); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								break;
							case MnMS0_OPT_CH2_OPERATION:								
								switch(MnMSR_BaseGet_Value(MnMS0_OPT_CH2_OPERATION))
								{
									case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
									case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
									default:						break;
								}								
								DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiList(TEXT_LIST_CH2_OPERATION); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								break;	
							default:
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal); 							
								break;
						}
						break;
					case MnMSR_SUB_CAL: 	
						pItm = lDpMsr.sIt1[id]; 	pVal = lDpMsr.sVl1[id]; 
						switch(id)
						{
							case MnMS1_OPT_CH1_ASF_LIGHT:			
								DpSTR_GuiList(TEXT_LIST_CH1_LIGHT); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_itm_x0+150, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "ASF");
								DpSTR_GuiList(TEXT_LIST_SET);	
								DpSTR_GuiLeft_KOR(box_itm_x0+200, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
							case MnMS1_OPT_CH1_ASF_HEAVY:			
								DpSTR_GuiList(TEXT_LIST_CH1_HEAVY); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_itm_x0+150, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "ASF");
								DpSTR_GuiList(TEXT_LIST_SET);	
								DpSTR_GuiLeft_KOR(box_itm_x0+200, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;								
							case MnMS1_OPT_CH2_ASF_LIGHT:			
								DpSTR_GuiList(TEXT_LIST_CH2_LIGHT); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_itm_x0+150, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "ASF");
								DpSTR_GuiList(TEXT_LIST_SET);	
								DpSTR_GuiLeft_KOR(box_itm_x0+200, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
							case MnMS1_OPT_CH2_ASF_HEAVY:			
								DpSTR_GuiList(TEXT_LIST_CH2_HEAVY); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_itm_x0+150, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "ASF");
								DpSTR_GuiList(TEXT_LIST_SET);	
								DpSTR_GuiLeft_KOR(box_itm_x0+200, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
							default:
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
						}
						break;
					default:				return;
				}
			}
			break;			
	}

}


void DpMSR_StrSingleCntts(U08 idx)
{
	U08 i, n, page, iN, id;
	I08 *pItm, *pVal;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iIt = MnLY2_GetIdxItem();
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U64 back_color = _cMNU_BOX_BG;
	U64 text_color = _cMNU_STR_IDLE;


	switch(idx)
	{
		case MnMSR_SUB_BASE:		n = MnMS0_OPT_SINGLE_NUM;			break;
		case MnMSR_SUB_CAL: 		n = MnMS1_OPT_SINGLE_NUM;			break;
		default:					return;
	}

	if		(iIt >= (DpMNU_ITM_PAGE*2)) 	page = DpMNU_PG_2;
	else if (iIt >= (DpMNU_ITM_PAGE*1)) 	page = DpMNU_PG_1;
	else									page = DpMNU_PG_0;

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
		default:			return;
	}

	sel = (iIt%DpMNU_ITM_PAGE);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			for(i=0; i<iN; i++)
			{
				id = i+(DpMNU_ITM_PAGE*page);
				switch(idx)
				{
					case MnMSR_SUB_BASE:	pItm = lDpMsr.sIt0[id]; 	pVal = lDpMsr.sVl0[id]; break;
					case MnMSR_SUB_CAL: 	pItm = lDpMsr.sIt1[id]; 	pVal = lDpMsr.sVl1[id]; break;
					default:				return;
				}

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

				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, pItm);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
			}			
			break;
		case MnSYS_LANG_KOR:
			for(i=0; i<iN; i++)
			{
				id = i+(DpMNU_ITM_PAGE*page);
				DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-30-60, 37, _cMNU_BOX_BG, DpFIG_FILL);
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
				switch(idx)
				{
					case MnMSR_SUB_BASE:	
						pItm = lDpMsr.sIt0[id]; 	pVal = lDpMsr.sVl0[id]; 
						switch(id)
						{
							case MnMS0_OPT_SINGLE_OPERATION: 
								switch(MnMSR_BaseGet_Value(MnMS0_OPT_SINGLE_OPERATION))
								{
									case MnMS0_OPERATION_SLUDGE:	DpSTR_GuiList(TEXT_LIST_SLUDGE);				break;	
									case MnMS0_OPERATION_DISTANCE:	DpSTR_GuiList(TEXT_LIST_DISTANCE);				break;
									default:						break;
								}				
								DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiList(TEXT_LIST_OPERATION); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								break;	
							default:
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal); 							
								break;
						}
						break;
					case MnMSR_SUB_CAL: 	
						pItm = lDpMsr.sIt1[id]; 	pVal = lDpMsr.sVl1[id]; 
						switch(id)
						{
							case MnMS1_OPT_SINGLE_ASF_LIGHT:			
								DpSTR_GuiList(TEXT_LIST_LIGHT); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "ASF");
								DpSTR_GuiList(TEXT_LIST_SET);	
								DpSTR_GuiLeft_KOR(box_itm_x0+130, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
							case MnMS1_OPT_SINGLE_ASF_HEAVY:			
								DpSTR_GuiList(TEXT_LIST_HEAVY); 
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "ASF");
								DpSTR_GuiList(TEXT_LIST_SET);	
								DpSTR_GuiLeft_KOR(box_itm_x0+130, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;								
							default:
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
						}
						break;
					default:				return;
				}
			}
			break;			
	}

}

void DpMSR_StrCntts(U08 idx)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpMSR_StrDualCntts(idx);
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpMSR_StrSingleCntts(idx);
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

