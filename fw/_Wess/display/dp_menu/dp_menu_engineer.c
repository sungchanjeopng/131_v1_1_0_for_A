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
#include "menu_engineer.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// disp - menu
#include "dp_menu_main.h"
// self
#include "dp_menu_engineer.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpEGN_LS lDpEgn;


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set)
I08* DpEGN_GetAddrItm(U08 idx)		{	return lDpEgn.sItm[idx];			}
I08* DpEGN_GetAddrVal(U08 idx)		{	return lDpEgn.sVal[idx];			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Additional
//------------------------------------------------------------------------------------------------------------------------------
void DpEGN_AddUpdat(void)
{

}

void DpEGN_AddIntro(void)
{
	DpEGN_PopIntro();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-Up
//------------------------------------------------------------------------------------------------------------------------------
void DpEGN_PopUpdat(void)
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
	{
		case MnEGN_OPT_THRESHOLD_SYNC:
			DpPOP_UdtValue(0,   _F_F, gDpStr.sOnF[0]);
			//DpPOP_UdtValue(1,   _F_F, gDpStr.sOnF[1]);
			//DpPOP_UdtValue(val, _F_T, gDpStr.sOnF[val]);
			return;
		case MnEGN_OPT_CH1_PROFILE:					
		case MnEGN_OPT_CH2_PROFILE:					_SPRINTF(pSt0, "%03d", val);	break;
		case MnEGN_OPT_CH1_TVG:
		case MnEGN_OPT_CH2_TVG:
			if(val == 0)		
			{
				if(lang == MnSYS_LANG_KOR)
				{
					DpSTR_GuiList(TEXT_LIST_OFF);
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
				}
				else if(lang == MnSYS_LANG_ENG)
				{
					_SPRINTF(pSt0, "OFF");
					DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, pSt0);
					
				}
				return;
			}
			else if (val>0)		_SPRINTF(pSt0, "%d", val);	
			break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:		_SPRINTF(pSt0, "%03d", val);	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:			_SPRINTF(pSt0, "%02d.%02d", val/100, val%100);	break;
		case MnEGN_OPT_MSR:
			DpPOP_UdtValue(0,   _F_F, gDpStr.sOnF[0]);
			DpPOP_UdtValue(1,   _F_F, gDpStr.sOnF[1]);
			DpPOP_UdtValue(val, _F_T, gDpStr.sOnF[val]);
			return;		
		default:						_SPRINTF(pSt0, _sNG);		break;
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



#if 0
	switch(MnLY2_GetIdxItem())
	{
		case MnEGN_I00_THRESHOLD_MIN:
		case MnEGN_I01_SMOOTH_NUM:
		case MnEGN_I02_SMOOTH_RANGE:	_SPRINTF(pSt0, "%d", val);		break;
		case MnEGN_I03_fDP_DBG:			
			DpPOP_UdtValue(0,   _F_F, gDpStr.sOnF[0]);
			DpPOP_UdtValue(1,   _F_F, gDpStr.sOnF[1]);
			DpPOP_UdtValue(val, _F_T, gDpStr.sOnF[val]);
			return;
		case MnEGN_I04_fDP_ECHO:
			DpPOP_UdtValue(0,   _F_F, gDpStr.sOnF[0]);
			DpPOP_UdtValue(1,   _F_F, gDpStr.sOnF[1]);
			DpPOP_UdtValue(val, _F_T, gDpStr.sOnF[val]);
			return;
		case MnEGN_I05_RX_BPF:			_SPRINTF(pSt0, "%d", val);		break;
		default:
			DpPOP_UdtValue(val, _F_F, _sNG);
			return;
	}
#endif
}

void DpEGN_PopIntro(void)
{
	U08 fDp = _F_T;
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnEGN_PrGet_Item(iIt);
	S32 min = -1, max = -1;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:		
			// Title
			switch(iIt)
			{
				case MnEGN_OPT_THRESHOLD_SYNC:				_SPRINTF(lDpEgn.pStr, _sThr_Sync);				break;
				case MnEGN_OPT_CH1_PROFILE: 				_SPRINTF(lDpEgn.pStr, _sCH1_Profile);			break;
				case MnEGN_OPT_CH1_TVG: 					_SPRINTF(lDpEgn.pStr, _sCH1_TVG);				break;
				case MnEGN_OPT_CH1_WINDOW_RESET_TIME:		_SPRINTF(lDpEgn.pStr, _sCH1_Window_Reset_Time); break;
				case MnEGN_OPT_CH1_WINDOW_RANGE:			_SPRINTF(lDpEgn.pStr, _sCH1_Window_Range);		break;
				case MnEGN_OPT_CH2_PROFILE: 				_SPRINTF(lDpEgn.pStr, _sCH2_Profile);			break;
				case MnEGN_OPT_CH2_TVG: 					_SPRINTF(lDpEgn.pStr, _sCH2_TVG);				break;
				case MnEGN_OPT_CH2_WINDOW_RESET_TIME:		_SPRINTF(lDpEgn.pStr, _sCH2_Window_Reset_Time); break;
				case MnEGN_OPT_CH2_WINDOW_RANGE:			_SPRINTF(lDpEgn.pStr, _sCH2_Window_Range);		break;
				case MnEGN_OPT_MSR: 						_SPRINTF(lDpEgn.pStr, _sStruct_MSR);			break;
				default:									_SPRINTF(lDpEgn.pStr, _sNG);					break;
			}
			break;
		case MnSYS_LANG_KOR:
			fDp = _F_F;
			switch(iIt)
			{
				case MnEGN_OPT_CH1_TVG:
					DpSTR_GuiList(TEXT_LIST_CH_1);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR,gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, lDpEgn.sItm[iIt]);
					break;
				case MnEGN_OPT_CH2_TVG:
					DpSTR_GuiList(TEXT_LIST_CH_2);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, lDpEgn.sItm[iIt]);
					break;				
				case MnEGN_OPT_MSR:
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR,lDpEgn.sItm[iIt]);			
					break;
				default:
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR,lDpEgn.sItm[iIt]);					
					break;
			}	
			break;
	}

	if(fDp) DpPOP_UdtTitle(lDpEgn.pStr);

	// Old
	fDp = _F_T;


	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnEGN_THRESHOLD_SYNC_OFF:		_SPRINTF(lDpEgn.pStr, gDpStr.sOnF[0]);		break;
						case MnEGN_THRESHOLD_SYNC_ON:		_SPRINTF(lDpEgn.pStr, gDpStr.sOnF[1]);		break;
						default:
							break;
					}
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE22HsBKOR, lDpEgn.pStr);
					fDp = _F_F;
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnEGN_THRESHOLD_SYNC_OFF:		_SPRINTF(lDpEgn.pStr, _sOFF);		break;
						case MnEGN_THRESHOLD_SYNC_ON:		_SPRINTF(lDpEgn.pStr, _sON);		break;
						default:
							break;
					}
					break;
			}
			break;
		case MnEGN_OPT_CH1_PROFILE:					
		case MnEGN_OPT_CH2_PROFILE:					_SPRINTF(lDpEgn.pStr, "%d", val);	break;
		case MnEGN_OPT_CH1_TVG:
		case MnEGN_OPT_CH2_TVG:
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					fDp = _F_F;
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					if(val ==0)
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					}
					else	
					{
						_SPRINTF(lDpEgn.pStr, "%d", val);
						DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_OLD_Y0,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE22HsB, lDpEgn.pStr);	
					}
					break;			
				case MnSYS_LANG_ENG:
					if(val == 0)		_SPRINTF(lDpEgn.pStr, _sOFF);
					else if (val>0)		_SPRINTF(lDpEgn.pStr, "%d", val);	
			}
			break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:		_SPRINTF(lDpEgn.pStr, "%d sec", val);	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:			_SPRINTF(lDpEgn.pStr,"%2d.%02d m", (U16)(val/100), (U16)(val%100));
		case MnEGN_OPT_MSR:
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					switch(val)
					{
						case MnEGN_MSR_OFF:		_SPRINTF(lDpEgn.pStr, gDpStr.sOnF[0]);		break;
						case MnEGN_MSR_ON:		_SPRINTF(lDpEgn.pStr, gDpStr.sOnF[1]);		break;
						default:
							break;
					}
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE22HsBKOR, lDpEgn.pStr);
					fDp = _F_F;
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnEGN_MSR_OFF:		_SPRINTF(lDpEgn.pStr, _sOFF);		break;
						case MnEGN_MSR_ON:		_SPRINTF(lDpEgn.pStr, _sON);		break;
						default:
							break;
					}
					break;
			}
			break;		
		default:						_SPRINTF(lDpEgn.pStr, _sNG);		break;
	}


	if(fDp)
		DpPOP_UdtOldVl(lDpEgn.pStr);


	fDp = _F_T;

	// Range (Min. / Max.)

	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:				fDp = _F_F;	break;
		case MnEGN_OPT_CH1_PROFILE:					
		case MnEGN_OPT_CH2_PROFILE:					min = MnEGN_PROFILE_MIN;	max = MnEGN_PROFILE_MAX;	break;
		case MnEGN_OPT_CH1_TVG:
		case MnEGN_OPT_CH2_TVG:						min = MnEGN_TVG_MIN;		max = MnEGN_TVG_MAX;		break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:		min = MnEGN_WINDOW_RESET_TIME_MIN;		max = MnEGN_WINDOW_RESET_TIME_MAX;		break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:			min = MnEGN_WINDOW_RANGE_MIN;		max = MnEGN_WINDOW_RANGE_MAX;		break;
		case MnEGN_OPT_MSR:							fDp = _F_F;	break;	
		default:									_SPRINTF(lDpEgn.pStr, _sNG);		break;
	}


	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:				fDp = _F_F;	break;
		case MnEGN_OPT_CH1_PROFILE:					
		case MnEGN_OPT_CH2_PROFILE:					_SPRINTF(lDpEgn.pStr, "%d", min);	break;
		case MnEGN_OPT_CH1_TVG:
		case MnEGN_OPT_CH2_TVG:			
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					fDp = _F_F;
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN, _cPOP_BG_WND, _fE17HsB, _sMIN);
					if(min ==0)
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsBKOR, gDpStr.Text_list);
					}
					else	
					{
						_SPRINTF(lDpEgn.pStr, "%d", min);
						DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, lDpEgn.pStr); 
					}
					break;			
				case MnSYS_LANG_ENG:
					_SPRINTF(lDpEgn.pStr, _sOFF);		
					break;
			}
			break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:		_SPRINTF(lDpEgn.pStr, "%d sec", min);	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:			_SPRINTF(lDpEgn.pStr,"%2d.%02d m", (U16)(min/100), (U16)(min%100));
		case MnEGN_OPT_MSR:							fDp = _F_F;	break;		
		default:									_SPRINTF(lDpEgn.pStr, _sNG);		break;
	}


	if(fDp)	DpPOP_UdtRangeMin(lDpEgn.pStr);

	fDp = _F_T;

	switch(iIt)
	{
		case MnEGN_OPT_THRESHOLD_SYNC:				fDp = _F_F;	break;
		case MnEGN_OPT_CH1_PROFILE:					
		case MnEGN_OPT_CH2_PROFILE:					_SPRINTF(lDpEgn.pStr, "%d", max);	break;
		case MnEGN_OPT_CH1_TVG:
		case MnEGN_OPT_CH2_TVG:						_SPRINTF(lDpEgn.pStr, "%d", max);	break;
		case MnEGN_OPT_CH1_WINDOW_RESET_TIME:
		case MnEGN_OPT_CH2_WINDOW_RESET_TIME:		_SPRINTF(lDpEgn.pStr, "%d sec", max);	break;
		case MnEGN_OPT_CH1_WINDOW_RANGE:
		case MnEGN_OPT_CH2_WINDOW_RANGE:			_SPRINTF(lDpEgn.pStr,"%2d.%02d m", (U16)(max/100), (U16)(max%100));
		case MnEGN_OPT_MSR:							fDp = _F_F;	break;		
		default:									_SPRINTF(lDpEgn.pStr, _sNG);		break;
	}



	if(fDp)	DpPOP_UdtRangeMax(lDpEgn.pStr);
	fDp = _F_T;

#if 0 
	// Value
	switch(MnLY2_GetIdxItem())
	{
		case MnEGN_I00_THRESHOLD_MIN:
		case MnEGN_I01_SMOOTH_NUM:
		case MnEGN_I02_SMOOTH_RANGE:	break;
		case MnEGN_I03_fDP_DBG:			DpPOP_UdtValue(0, _F_F, gDpStr.sOnF[0]);
										DpPOP_UdtValue(1, _F_F, gDpStr.sOnF[1]);		break;
		case MnEGN_I04_fDP_ECHO:		DpPOP_UdtValue(0, _F_F, gDpStr.sOnF[0]);
										DpPOP_UdtValue(1, _F_F, gDpStr.sOnF[1]);		break;
		case MnEGN_I05_RX_BPF:			break;
		default:						DpPOP_UdtValue(0, _F_F, _sNG);					return;
	}
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpEGN_InitVari(void)
{
	S32 val = 0;

	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_THR_SYNC);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_THRESHOLD_SYNC], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_PROFILE_NO);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_PROFILE], gDpStr.Text_list);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_TVG], "TVG");
			DpSTR_GuiList(TEXT_LIST_CH1_WINDOW_RESET_TIME);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_WINDOW_RESET_TIME], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH1_WINDOW_RANGE);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_WINDOW_RANGE],gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_PROFILE_NO);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_PROFILE], gDpStr.Text_list);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_TVG], _sCH2_TVG);
			DpSTR_GuiList(TEXT_LIST_CH2_WINDOW_RESET_TIME);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_WINDOW_RESET_TIME], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CH2_WINDOW_RANGE);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_WINDOW_RANGE],gDpStr.Text_list);	
			DpSTR_GuiList(TEXT_LIST_SLUDGE_COLLECTOR_DETECT);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_MSR],gDpStr.Text_list);		
			break;
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_THRESHOLD_SYNC], _sThr_Sync);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_PROFILE], _sCH1_Profile);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_TVG], _sCH1_TVG);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_WINDOW_RESET_TIME], _sCH1_Window_Reset_Time);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH1_WINDOW_RANGE],_sCH1_Window_Range);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_PROFILE], _sCH2_Profile);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_TVG], "CH2 TVG");
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_WINDOW_RESET_TIME], _sCH2_Window_Reset_Time);
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_CH2_WINDOW_RANGE],_sCH2_Window_Range);	
			_SPRINTF(lDpEgn.sItm[MnEGN_OPT_MSR], _sStruct_MSR);
			break;
	}



	val = MnEGN_PrGet_Item(MnEGN_OPT_THRESHOLD_SYNC);
	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpEgn.sVal[MnEGN_OPT_THRESHOLD_SYNC], gDpStr.sOnF[0]);
			break;
			#if 0
			switch(val)
			{
				case MnEGN_THRESHOLD_SYNC_OFF:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_THRESHOLD_SYNC], gDpStr.sOnF[0]); 	break;
				case MnEGN_THRESHOLD_SYNC_ON:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_THRESHOLD_SYNC], gDpStr.sOnF[1]);		break;
				default:
					break;
			}
			break;
			#endif
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpEgn.sVal[MnEGN_OPT_THRESHOLD_SYNC], _sOFF);	
			break;
			#if 0
			switch(val)
			{
				case MnEGN_THRESHOLD_SYNC_OFF:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_THRESHOLD_SYNC], _sOFF);		break;
				case MnEGN_THRESHOLD_SYNC_ON:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_THRESHOLD_SYNC], _sON);		break;
				default:
					break;
			}
			break;
			#endif
	}
	val = MnEGN_PrGet_Item(MnEGN_OPT_CH1_PROFILE);
	_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH1_PROFILE], " %d", val);

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH1_TVG);
	if(val == 0)_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH1_TVG], " OFF");	
	else		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH1_TVG], " %d", val);	

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH1_WINDOW_RESET_TIME);
	_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH1_WINDOW_RESET_TIME], " %d sec", val);

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH1_WINDOW_RANGE);	
	_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH1_WINDOW_RANGE], "%2d.%02d m", (U16)(val/100), (U16)(val%100));

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH2_PROFILE);
	_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH2_PROFILE], " %d", val);

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH2_TVG);
	if(val == 0)_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH2_TVG], " OFF");	
	else		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH2_TVG], " %d", val);		

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH2_WINDOW_RESET_TIME);
	_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH2_WINDOW_RESET_TIME], " %d sec", val);

	val = MnEGN_PrGet_Item(MnEGN_OPT_CH2_WINDOW_RANGE);	
	_SPRINTF(lDpEgn.sVal[MnEGN_OPT_CH2_WINDOW_RANGE], "%2d.%02d m", (U16)(val/100), (U16)(val%100));	


	val = MnEGN_PrGet_Item(MnEGN_OPT_MSR);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			switch(val)
			{
				case MnEGN_MSR_OFF:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_MSR], gDpStr.sOnF[0]); 	break;
				case MnEGN_MSR_ON:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_MSR], gDpStr.sOnF[1]);		break;
				default:
					break;
			}
			break;
		case MnSYS_LANG_ENG:
			switch(val)
			{
				case MnEGN_MSR_OFF:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_MSR], _sOFF);	break;
				case MnEGN_MSR_ON:		_SPRINTF(lDpEgn.sVal[MnEGN_OPT_MSR], _sON);		break;
				default:
					break;
			}
			break;
	}
	
	_MEMSET(lDpEgn.pStr, 0, sizeof(lDpEgn.pStr));
}

void DpEG2_StrCntts(void)
{
	U08 i,n,page,idx,iN;
	U32 cStr =_cMNU_STR_IDLE;
	U08 iIt = MnLY2_GetIdxItem();	
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U32 back_color = _cMNU_BOX_BG;
	U32 text_color = _cMNU_STR_IDLE;

	n = MnEGN_OPT_NUM;

	if (iIt >= (DpMNU_ITM_PAGE*1))		page = DpMNU_PG_1;
	else								page = DpMNU_PG_0;

	switch(page)
	{
		case DpMNU_PG_0:	
			if(n>DpMNU_ITM_PAGE)		iN=DpMNU_ITM_PAGE;
			else						iN=n;
			break;
		case DpMNU_PG_1:	iN = n-(DpMNU_ITM_PAGE*page);		break;
		default:			return;
	}

	sel = (iIt%DpMNU_ITM_PAGE);

	// String
	for(i=0; i<iN; i++)
	{
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


		idx = i+(DpMNU_ITM_PAGE*page);

		switch(lang)
		{
			case MnSYS_LANG_ENG:		
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, lDpEgn.sItm[idx]);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), cStr,			 _cTTB_BG_MID, _fE17HsB, lDpEgn.sVal[idx]);
				break;
			case MnSYS_LANG_KOR:
				switch(idx)
				{
					case MnEGN_OPT_CH1_TVG:
						DpSTR_GuiList(TEXT_LIST_CH_1);
						DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR,  gDpStr.Text_list);
						DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, lDpEgn.sItm[idx]);
						if(MnEGN_PrGet_Item(MnEGN_OPT_CH1_TVG) ==0)
						{
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), cStr,_cTTB_BG_MID, _fE17HsBKOR,gDpStr.Text_list);
						}
						else	
							DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), cStr,_cTTB_BG_MID, _fE17HsB, lDpEgn.sVal[idx]);		
						break;
					case MnEGN_OPT_CH2_TVG:
						DpSTR_GuiList(TEXT_LIST_CH_2);
						DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR,  gDpStr.Text_list);
						DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, lDpEgn.sItm[idx]);
						if(MnEGN_PrGet_Item(MnEGN_OPT_CH2_TVG) ==0)
						{
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), cStr,_cTTB_BG_MID, _fE17HsBKOR, gDpStr.Text_list);
						}
						else	
							DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), cStr,_cTTB_BG_MID, _fE17HsB, lDpEgn.sVal[idx]);		
						break;			
					case MnEGN_OPT_THRESHOLD_SYNC:
					case MnEGN_OPT_MSR:
						DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR,  lDpEgn.sItm[idx]);
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), cStr,			 _cTTB_BG_MID, _fE17HsBKOR, lDpEgn.sVal[idx]);					
						break;
					default:
						DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR,  lDpEgn.sItm[idx]);
						DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), cStr,			 _cTTB_BG_MID, _fE17HsB, lDpEgn.sVal[idx]);							
						break;
				}	
				break;
		}

	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

