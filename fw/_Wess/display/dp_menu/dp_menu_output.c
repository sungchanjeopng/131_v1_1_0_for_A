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
#include "menu_output.h"
#include "menu_factory.h"
#include "menu_lyr0_section.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
// disp - screen
#include "dp_screen_main.h"
// disp - menu
#include "dp_menu_main.h"
// self
#include "dp_menu_output.h"
// measure
#include "measure_calc.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpOUT_LS lDpOut;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
// Popup - Current
void DpOutCur_PoPDualIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnOUT_CurPrGet_Value(iIt);
	S32 min = -1, max = -1;
	U08 fDp = _F_T;
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			fDp = _F_F;
			switch(iIt)
			{
				case MnOS0_OPT_CH1_ASSIGN:
				case MnOS0_OPT_CH2_ASSIGN:			
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, lDpOut.sIt0[iIt]);
					break;
				case MnOS0_OPT_CH1_SET_04mA:
					DpSTR_GuiList(TEXT_LIST_CH_1);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 4 mA");
					DpSTR_GuiList(TEXT_LIST_SET);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;
				case MnOS0_OPT_CH1_SET_20mA:
					DpSTR_GuiList(TEXT_LIST_CH_1);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB,  "20 mA");
					DpSTR_GuiList(TEXT_LIST_SET);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					break;			
				case MnOS0_OPT_CH1_TRM_12mA:
					DpSTR_GuiList(TEXT_LIST_CH_1);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 12 mA");
					DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					break;
				case MnOS0_OPT_CH1_TRM_20mA:
					DpSTR_GuiList(TEXT_LIST_CH_1);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "20 mA");
					DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;			
				case MnOS0_OPT_CH1_OUT_04mA:
					DpSTR_GuiList(TEXT_LIST_CH_1);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 4 mA");
					DpSTR_GuiList(TEXT_LIST_CH1_OUTPUT);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;			
				case MnOS0_OPT_CH2_SET_04mA:
					DpSTR_GuiList(TEXT_LIST_CH_2);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 4 mA");
					DpSTR_GuiList(TEXT_LIST_SET);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;
				case MnOS0_OPT_CH2_SET_20mA:
					DpSTR_GuiList(TEXT_LIST_CH_2);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "20 mA");
					DpSTR_GuiList(TEXT_LIST_SET);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;			
				case MnOS0_OPT_CH2_TRM_12mA:
					DpSTR_GuiList(TEXT_LIST_CH_2);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 12 mA");
					DpSTR_GuiList(TEXT_LIST_CH2_TRIM);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;
				case MnOS0_OPT_CH2_TRM_20mA:
					DpSTR_GuiList(TEXT_LIST_CH_2);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "20 mA");
					DpSTR_GuiList(TEXT_LIST_CH2_TRIM);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;			
				case MnOS0_OPT_CH2_OUT_04mA:
					DpSTR_GuiList(TEXT_LIST_CH_2);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					DpSTR_GuiLeft(DpPOP_TIT_X0+100,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 4 mA");
					DpSTR_GuiList(TEXT_LIST_CH2_OUTPUT);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+200, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;									
			}
			break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				//page #1
				case MnOS0_OPT_CH1_ASSIGN:		_SPRINTF(lDpOut.pStr, _sCH1_ASSIGN);			break;
				case MnOS0_OPT_CH1_SET_04mA:	_SPRINTF(lDpOut.pStr, _sCH1_SET_04mA);			break;
				case MnOS0_OPT_CH1_SET_20mA:	_SPRINTF(lDpOut.pStr, _sCH1_SET_20mA);			break;
				case MnOS0_OPT_CH1_TRM_12mA:	_SPRINTF(lDpOut.pStr, _sCH1_TRM_12mA);			break;
				case MnOS0_OPT_CH1_TRM_20mA:	_SPRINTF(lDpOut.pStr, _sCH1_TRM_20mA);			break;
				case MnOS0_OPT_CH1_OUT_04mA:	_SPRINTF(lDpOut.pStr, _sCH1_OUT_04mA);			break;	
				//page #2
				case MnOS0_OPT_CH2_ASSIGN:		_SPRINTF(lDpOut.pStr, _sCH2_ASSIGN);			break;
				case MnOS0_OPT_CH2_SET_04mA:	_SPRINTF(lDpOut.pStr, _sCH2_SET_04mA);			break;
				case MnOS0_OPT_CH2_SET_20mA:	_SPRINTF(lDpOut.pStr, _sCH2_SET_20mA);			break;
				case MnOS0_OPT_CH2_TRM_12mA:	_SPRINTF(lDpOut.pStr, _sCH2_TRM_12mA);			break;
				case MnOS0_OPT_CH2_TRM_20mA:	_SPRINTF(lDpOut.pStr, _sCH2_TRM_20mA);			break;
				case MnOS0_OPT_CH2_OUT_04mA:	_SPRINTF(lDpOut.pStr, _sCH2_OUT_04mA);			break;	
				default:						_SPRINTF(lDpOut.pStr, _sNG);					break;
			}		
			break;
	}

	if(fDp)		DpPOP_UdtTitle(lDpOut.pStr);
	fDp = _F_T;




	// Old Value
	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:
		case MnOS0_OPT_CH2_ASSIGN:
			fDp = _F_F;
			switch(lang)
			{
				case MnSYS_LANG_KOR:		
					switch(val)
					{
						case MnOS0_ASSIGN_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
						case MnOS0_ASSIGN_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
						default:					break;
					}																			
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE17HsBKOR,  gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(lDpOut.pStr, _sLight);										break;
						case MnOS0_ASSIGN_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy);										break;
						default:					_SPRINTF(lDpOut.pStr, _sNG);										break;
					}			
					fDp = _F_T;
					break;					
			}
			break;
		case MnOS0_OPT_CH1_SET_04mA:
		case MnOS0_OPT_CH1_SET_20mA:		
		case MnOS0_OPT_CH2_SET_04mA:
		case MnOS0_OPT_CH2_SET_20mA:	_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnOS0_OPT_CH1_TRM_12mA:
		case MnOS0_OPT_CH1_TRM_20mA:
		case MnOS0_OPT_CH2_TRM_12mA:
		case MnOS0_OPT_CH2_TRM_20mA:	_SPRINTF(lDpOut.pStr, "%d", val);									break;
		case MnOS0_OPT_CH1_OUT_04mA:
		case MnOS0_OPT_CH2_OUT_04mA:	fDp = _F_F;															break;
		default:						_SPRINTF(lDpOut.pStr, _sNG);										break;
	}	
	if(fDp)		DpPOP_UdtOldVl(lDpOut.pStr);
	fDp = _F_T;


	// Range (Min. / Max.)
	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:		
		case MnOS0_OPT_CH2_ASSIGN:		min = MnOS0_ASSIGN_MIN;	max = MnOS0_ASSIGN_MAX;		break;
		case MnOS0_OPT_CH1_SET_04mA:	
		case MnOS0_OPT_CH2_SET_04mA:
		case MnOS0_OPT_CH1_SET_20mA:
		case MnOS0_OPT_CH2_SET_20mA:	min = MnOS0_SET_MA_MIN;	max = MnOS0_SET_MA_MAX;		break;
		case MnOS0_OPT_CH1_TRM_12mA:
		case MnOS0_OPT_CH1_TRM_20mA:
		case MnOS0_OPT_CH2_TRM_12mA:
		case MnOS0_OPT_CH2_TRM_20mA:	min = MnOS0_TRIM_MIN;	max = MnOS0_TRIM_MAX;		break;		
		default:																			break;
	}
	
	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:
		case MnOS0_OPT_CH2_ASSIGN:
			fDp = _F_F;
			switch(min)
			{
				case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(lDpOut.pStr, _sLight);										break;
				case MnOS0_ASSIGN_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy);										break;
				default:					_SPRINTF(lDpOut.pStr, _sNG);										break;
			}															
			break;
		case MnOS0_OPT_CH1_SET_04mA:	
		case MnOS0_OPT_CH2_SET_04mA:
		case MnOS0_OPT_CH1_SET_20mA:
		case MnOS0_OPT_CH2_SET_20mA:	_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;
		case MnOS0_OPT_CH1_TRM_12mA:
		case MnOS0_OPT_CH1_TRM_20mA:
		case MnOS0_OPT_CH2_TRM_12mA:
		case MnOS0_OPT_CH2_TRM_20mA:	_SPRINTF(lDpOut.pStr, "%d", min);	break;
		case MnOS0_OPT_CH1_OUT_04mA:
		case MnOS0_OPT_CH2_OUT_04mA:	fDp = _F_F;							break;
		default:															break;
	}
	
	if(fDp)		DpPOP_UdtRangeMin(lDpOut.pStr);
	fDp = _F_T;
	
	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:
		case MnOS0_OPT_CH2_ASSIGN:
			fDp = _F_F;
			switch(max)
			{
				case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(lDpOut.pStr, _sLight);										break;
				case MnOS0_ASSIGN_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy);										break;
				default:					_SPRINTF(lDpOut.pStr, _sNG);										break;
			}															
			break;
		case MnOS0_OPT_CH1_SET_04mA:	
		case MnOS0_OPT_CH2_SET_04mA:
		case MnOS0_OPT_CH1_SET_20mA:
		case MnOS0_OPT_CH2_SET_20mA:	_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;
		case MnOS0_OPT_CH1_TRM_12mA:
		case MnOS0_OPT_CH1_TRM_20mA:
		case MnOS0_OPT_CH2_TRM_12mA:
		case MnOS0_OPT_CH2_TRM_20mA:	_SPRINTF(lDpOut.pStr, "%d", max);	break;
		case MnOS0_OPT_CH1_OUT_04mA:
		case MnOS0_OPT_CH2_OUT_04mA:	fDp = _F_F;							break;
		default:															break;
	}



	if(fDp)		DpPOP_UdtRangeMax(lDpOut.pStr);
	fDp = _F_T;

	// Explanation
	switch(iIt)
	{
		case MnOS0_OPT_CH1_ASSIGN:		
		case MnOS0_OPT_CH2_ASSIGN:
		case MnOS0_OPT_CH1_SET_04mA:	
		case MnOS0_OPT_CH2_SET_04mA:
		case MnOS0_OPT_CH1_SET_20mA:
		case MnOS0_OPT_CH2_SET_20mA:
		case MnOS0_OPT_CH1_TRM_12mA:
		case MnOS0_OPT_CH1_TRM_20mA:
		case MnOS0_OPT_CH2_TRM_12mA:
		case MnOS0_OPT_CH2_TRM_20mA:	_SPRINTF(lDpOut.pStr, _sSel_PsSet);		break;
		case MnOS0_OPT_CH1_OUT_04mA:
		case MnOS0_OPT_CH2_OUT_04mA:	_SPRINTF(lDpOut.pStr, _sExit_Prskey);	break;
		default:						_SPRINTF(lDpOut.pStr, _sNG);			break;
	}
	DpPOP_UdtExpla(lDpOut.pStr);	

}

void DpOutCur_PoPSingleIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnOUT_CurPrGet_CH_Value(APP_CH_1,iIt);
	S32 min = -1, max = -1;
	U08 fDp = _F_T;
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			fDp = _F_F;
			switch(iIt)
			{
				case MnOS0_OPT_SINGLE_ASSIGN:		
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, lDpOut.sIt0[iIt]);
					break;
				case MnOS0_OPT_SINGLE_SET_04mA:
					DpSTR_GuiLeft(DpPOP_TIT_X0, DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 4 mA");
					DpSTR_GuiList(TEXT_LIST_SET);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+100, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;
				case MnOS0_OPT_SINGLE_SET_20mA:
					DpSTR_GuiLeft(DpPOP_TIT_X0,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB,  "20 mA");
					DpSTR_GuiList(TEXT_LIST_SET);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+100, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					break;			
				case MnOS0_OPT_SINGLE_TRM_12mA:
					DpSTR_GuiLeft(DpPOP_TIT_X0,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 12 mA");
					DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+100, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					break;
				case MnOS0_OPT_SINGLE_TRM_20mA:
					DpSTR_GuiLeft(DpPOP_TIT_X0,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, "20 mA");
					DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+100, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;			
				case MnOS0_OPT_SINGLE_OUT_04mA:
					DpSTR_GuiLeft(DpPOP_TIT_X0,  DpPOP_OLD_Y0-2, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsB, " 4 mA");
					DpSTR_GuiList(TEXT_LIST_CH1_OUTPUT);
					DpSTR_GuiLeft_KOR(DpPOP_TIT_X0+100, DpPOP_OLD_Y0, _cPOP_ST_TIT, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);	
					break;												
			}
			break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				//page #1
				case MnOS0_OPT_SINGLE_ASSIGN:		_SPRINTF(lDpOut.pStr, _sASSIGN);			break;
				case MnOS0_OPT_SINGLE_SET_04mA:	_SPRINTF(lDpOut.pStr, "Set	  4mA");			break;
				case MnOS0_OPT_SINGLE_SET_20mA:	_SPRINTF(lDpOut.pStr, "Set	  20mA");			break;
				case MnOS0_OPT_SINGLE_TRM_12mA:	_SPRINTF(lDpOut.pStr, "Trim	  12mA");			break;
				case MnOS0_OPT_SINGLE_TRM_20mA:	_SPRINTF(lDpOut.pStr, "Trim	  20mA");			break;
				case MnOS0_OPT_SINGLE_OUT_04mA:	_SPRINTF(lDpOut.pStr, "Output  4mA");			break;	
				default:						_SPRINTF(lDpOut.pStr, _sNG);					break;
			}		
			break;
	}

	if(fDp)		DpPOP_UdtTitle(lDpOut.pStr);
	fDp = _F_T;




	// Old Value
	switch(iIt)
	{
		case MnOS0_OPT_SINGLE_ASSIGN:
			fDp = _F_F;
			switch(lang)
			{
				case MnSYS_LANG_KOR:		
					switch(val)
					{
						case MnOS0_ASSIGN_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
						case MnOS0_ASSIGN_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
						default:					break;
					}																			
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE17HsBKOR,  gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(lDpOut.pStr, _sLight);										break;
						case MnOS0_ASSIGN_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy);										break;
						default:					_SPRINTF(lDpOut.pStr, _sNG);										break;
					}			
					fDp = _F_T;
					break;					
			}
			break;	
		case MnOS0_OPT_SINGLE_SET_04mA:
		case MnOS0_OPT_SINGLE_SET_20mA:	_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;
		case MnOS0_OPT_SINGLE_TRM_12mA:
		case MnOS0_OPT_SINGLE_TRM_20mA:	_SPRINTF(lDpOut.pStr, "%d", val);									break;
		case MnOS0_OPT_SINGLE_OUT_04mA:	fDp = _F_F;															break;
		default:						_SPRINTF(lDpOut.pStr, _sNG);										break;
	}	
	if(fDp)		DpPOP_UdtOldVl(lDpOut.pStr);
	fDp = _F_T;


	// Range (Min. / Max.)
	switch(iIt)
	{	
		case MnOS0_OPT_SINGLE_ASSIGN:	min = MnOS0_ASSIGN_MIN;	max = MnOS0_ASSIGN_MAX;		break;	
		case MnOS0_OPT_SINGLE_SET_04mA:
		case MnOS0_OPT_SINGLE_SET_20mA:	min = MnOS0_SET_MA_MIN;	max = MnOS0_SET_MA_MAX;		break;
		case MnOS0_OPT_SINGLE_TRM_12mA:
		case MnOS0_OPT_SINGLE_TRM_20mA:	min = MnOS0_TRIM_MIN;	max = MnOS0_TRIM_MAX;		break;		
		default:																			break;
	}
	
	switch(iIt)
	{
		case MnOS0_OPT_SINGLE_ASSIGN:
			fDp = _F_F;
			switch(min)
			{
				case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(lDpOut.pStr, _sLight);										break;
				case MnOS0_ASSIGN_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy);										break;
				default:					_SPRINTF(lDpOut.pStr, _sNG);										break;
			}															
			break;
		case MnOS0_OPT_SINGLE_SET_04mA:
		case MnOS0_OPT_SINGLE_SET_20mA:	_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;
		case MnOS0_OPT_SINGLE_TRM_12mA:
		case MnOS0_OPT_SINGLE_TRM_20mA:	_SPRINTF(lDpOut.pStr, "%d", min);	break;
		case MnOS0_OPT_SINGLE_OUT_04mA:	fDp = _F_F;							break;
		default:															break;
	}
	
	if(fDp)		DpPOP_UdtRangeMin(lDpOut.pStr);
	fDp = _F_T;
	
	switch(iIt)
	{
		case MnOS0_OPT_SINGLE_ASSIGN:
			fDp = _F_F;
			switch(max)
			{
				case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(lDpOut.pStr, _sLight);										break;
				case MnOS0_ASSIGN_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy);										break;
				default:					_SPRINTF(lDpOut.pStr, _sNG);										break;
			}															
			break;	
		case MnOS0_OPT_SINGLE_SET_04mA:
		case MnOS0_OPT_SINGLE_SET_20mA:	_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;
		case MnOS0_OPT_SINGLE_TRM_12mA:
		case MnOS0_OPT_SINGLE_TRM_20mA:	_SPRINTF(lDpOut.pStr, "%d", max);	break;
		case MnOS0_OPT_SINGLE_OUT_04mA:	fDp = _F_F;							break;
		default:															break;
	}



	if(fDp)		DpPOP_UdtRangeMax(lDpOut.pStr);
	fDp = _F_T;

	// Explanation
	switch(iIt)
	{
		case MnOS0_OPT_SINGLE_ASSIGN:
		case MnOS0_OPT_SINGLE_SET_04mA:
		case MnOS0_OPT_SINGLE_SET_20mA:
		case MnOS0_OPT_SINGLE_TRM_12mA:
		case MnOS0_OPT_SINGLE_TRM_20mA:	_SPRINTF(lDpOut.pStr, _sSel_PsSet);		break;
		case MnOS0_OPT_SINGLE_OUT_04mA:	_SPRINTF(lDpOut.pStr, _sExit_Prskey);	break;
		default:						_SPRINTF(lDpOut.pStr, _sNG);			break;
	}
	DpPOP_UdtExpla(lDpOut.pStr);	


}

void DpOutCur_PopIntro(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpOutCur_PoPDualIntro();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpOutCur_PoPSingleIntro();
}

void DpOutCur_PopUpdat(void)
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
	S32 max = MnLY3_GetMax();
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(iIt)
		{
			case MnOS0_OPT_CH1_ASSIGN:
			case MnOS0_OPT_CH2_ASSIGN:
				switch(lang)
				{
					case MnSYS_LANG_KOR:		
						switch(val)
						{
							case MnOS0_ASSIGN_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
							case MnOS0_ASSIGN_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
							default:					break;
						}																			
						DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
						return;
					case MnSYS_LANG_ENG:
						switch(val)
						{
							case MnOS0_ASSIGN_LIGHT: 	_SPRINTF(pSt0, _sLight);										break;
							case MnOS0_ASSIGN_HEAVY:	_SPRINTF(pSt0, _sHeavy);										break;
							default:					_SPRINTF(pSt0, _sNG);										break;
						}															
						break;					
				}
				break;
			case MnOS0_OPT_CH1_SET_04mA:	
			case MnOS0_OPT_CH2_SET_04mA:
			case MnOS0_OPT_CH1_SET_20mA:
			case MnOS0_OPT_CH2_SET_20mA:	_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;	
			case MnOS0_OPT_CH1_TRM_12mA:
			case MnOS0_OPT_CH1_TRM_20mA:
			case MnOS0_OPT_CH2_TRM_12mA:
			case MnOS0_OPT_CH2_TRM_20mA:	
				if(val>=0)	_SPRINTF(pSt0, "%03d", val);
				else		_SPRINTF(pSt0, "-%03d", abs(val));
				break;
			default:						return;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(iIt)
		{
			case MnOS0_OPT_SINGLE_ASSIGN:
				switch(lang)
				{
					case MnSYS_LANG_KOR:		
						switch(val)
						{
							case MnOS0_ASSIGN_LIGHT:	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
							case MnOS0_ASSIGN_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
							default:					break;
						}																			
						DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
						return;
					case MnSYS_LANG_ENG:
						switch(val)
						{
							case MnOS0_ASSIGN_LIGHT:	_SPRINTF(pSt0, _sLight);							break;
							case MnOS0_ASSIGN_HEAVY:	_SPRINTF(pSt0, _sHeavy);							break;
							default:					_SPRINTF(pSt0, _sNG);								break;
						}															
						break;					
				}
				break;	
			case MnOS0_OPT_SINGLE_SET_04mA:
			case MnOS0_OPT_SINGLE_SET_20mA:	_SPRINTF(pSt0, "%02d.%02d", (U16)(val/100), (U16)(val%100));	break;	
			case MnOS0_OPT_SINGLE_TRM_12mA:
			case MnOS0_OPT_SINGLE_TRM_20mA:	
				if(val>=0)	_SPRINTF(pSt0, "%03d", val);
				else		_SPRINTF(pSt0, "-%03d", abs(val));
				break;
			default:						return;
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

// Popup - Relay
void DpOutRly_PopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	U08 fDp = _F_T;
	S32 val = MnOUT_RlyPrGet_Value(iIt);
	S32 min= MENU_VAL_INVALID, max= MENU_VAL_INVALID;
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpOut.pStr, lDpOut.sIt1[iIt]);	
			break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				case MnOS1_OPT_ASSIGN:	_SPRINTF(lDpOut.pStr, _sASSIGN);	break;
				case MnOS1_OPT_ACT:		_SPRINTF(lDpOut.pStr, _sACT);		break;
				case MnOS1_OPT_STOP:	_SPRINTF(lDpOut.pStr, _sSTOP);		break;
				case MnOS1_OPT_TEST:	_SPRINTF(lDpOut.pStr, _sTEST);		break;
				default:				_SPRINTF(lDpOut.pStr, _sNG);		break;
			}
			break;
	}


	DpPOP_UdtTitle(lDpOut.pStr);

	//old Value	
	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:
			fDp = _F_F;
			switch(lang)
			{
				case MnSYS_LANG_KOR:		
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_CH1_LIGHT);		break;
							case MnOS1_ASSIGN_CH1_HEAVY:	 DpSTR_GuiList(TEXT_LIST_CH2_HEAVY);		break;
							case MnOS1_ASSIGN_CH2_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_CH1_LIGHT);		break;
							case MnOS1_ASSIGN_CH2_HEAVY:	 DpSTR_GuiList(TEXT_LIST_CH2_HEAVY);		break;
							default:						break;
						}				
					}
					else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT:	 DpSTR_GuiList(TEXT_LIST_LIGHT);		break;
							case MnOS1_ASSIGN_CH1_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);		break;
							default:						break;
						}	
					}
					DpSTR_GuiLeft(DpPOP_MIN_X0-40, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0-40, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR,  gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(lDpOut.pStr, _sCH1_Light); 		break;
							case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(lDpOut.pStr, _sCH1_Heavy); 		break;
							case MnOS1_ASSIGN_CH2_LIGHT:	_SPRINTF(lDpOut.pStr, _sCH2_Light); 		break;
							case MnOS1_ASSIGN_CH2_HEAVY:	_SPRINTF(lDpOut.pStr, _sCH2_Heavy);			break;
							default:						_SPRINTF(lDpOut.pStr, _sNG);				break;
						}		
					}
					else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(lDpOut.pStr, _sLight); 		break;
							case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(lDpOut.pStr, _sHeavy); 		break;
							default:						_SPRINTF(lDpOut.pStr, _sNG);				break;
						}		
					}
					break;
			}
			break;
		case MnOS1_OPT_ACT:	
		case MnOS1_OPT_STOP:			_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(val/100), (U16)(val%100));	break;	 
		case MnOS1_OPT_TEST:			fDp = _F_F;															break;	
		default:						_SPRINTF(lDpOut.pStr, _sNG);										break;
	}	

	if(fDp)		DpPOP_UdtOldVl(lDpOut.pStr);
	fDp = _F_T;

	// Range (Min. / Max.)
	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:		min = MnOS1_ASSIGN_MIN; max = MnOS1_ASSIGN_MAX;			break;
		case MnOS1_OPT_ACT:			min = MnOS1_ACT_MIN;	max = MnOS1_ACT_MAX;			break;
		case MnOS1_OPT_STOP:		min = MnOS1_STOP_MIN;	max = MnOS1_STOP_MAX;			break;
		case MnOS1_OPT_TEST:		min = MnOS1_TEST_MIN;	max = MnOS1_TEST_MAX;			break;
		default:																			break;
	}


	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:
			fDp = _F_F;
			switch(min)
			{
				case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(lDpOut.pStr, _sCH1_Light); 		break;
				case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(lDpOut.pStr, _sCH1_Heavy); 		break;
				case MnOS1_ASSIGN_CH2_LIGHT:	_SPRINTF(lDpOut.pStr, _sCH2_Light); 		break;
				case MnOS1_ASSIGN_CH2_HEAVY:	_SPRINTF(lDpOut.pStr, _sCH2_Heavy);			break;
				default:						_SPRINTF(lDpOut.pStr, _sNG);				break;
			}
			break;
		case MnOS1_OPT_ACT:			
		case MnOS1_OPT_STOP:			
		case MnOS1_OPT_TEST:			_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(min/100), (U16)(min%100));	break;
		default:																							break;
	}

	if(fDp)		DpPOP_UdtRangeMin(lDpOut.pStr);

	fDp = _F_T;

	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:
			fDp = _F_F;
			switch(max)
			{
				case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(lDpOut.pStr, _sCH1_Light); 		break;
				case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(lDpOut.pStr, _sCH1_Heavy); 		break;
				case MnOS1_ASSIGN_CH2_LIGHT:	_SPRINTF(lDpOut.pStr, _sCH2_Light); 		break;
				case MnOS1_ASSIGN_CH2_HEAVY:	_SPRINTF(lDpOut.pStr, _sCH2_Heavy);			break;
				default:						_SPRINTF(lDpOut.pStr, _sNG);				break;
			}
			break;
		case MnOS1_OPT_ACT:			
		case MnOS1_OPT_STOP:			
		case MnOS1_OPT_TEST:			_SPRINTF(lDpOut.pStr, "%2d.%02d m", (U16)(max/100), (U16)(max%100));	break;
		default:																							break;
	}


	if(fDp)		DpPOP_UdtRangeMax(lDpOut.pStr);

	fDp = _F_T;

	_SPRINTF(lDpOut.pStr, _sSel_PsSet);

	DpPOP_UdtExpla(lDpOut.pStr);
}

void DpOutRly_PopUpdat(void)
{
	U16 val=(U16)MnLY3_GetValue();
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };
	U08 iIt = MnLY2_GetIdxItem();
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{
		case MnOS1_OPT_ASSIGN:
			switch(lang)
			{
				case MnSYS_LANG_KOR:		
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_CH1_LIGHT);									break;
							case MnOS1_ASSIGN_CH1_HEAVY:	 DpSTR_GuiList(TEXT_LIST_CH1_HEAVY);									break;
							case MnOS1_ASSIGN_CH2_LIGHT: 	 DpSTR_GuiList(TEXT_LIST_CH2_LIGHT);									break;
							case MnOS1_ASSIGN_CH2_HEAVY:	 DpSTR_GuiList(TEXT_LIST_CH2_HEAVY);									break;
							default:						break;
						}	
					}
					else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT:	 DpSTR_GuiList(TEXT_LIST_LIGHT);									break;
							case MnOS1_ASSIGN_CH1_HEAVY:	 DpSTR_GuiList(TEXT_LIST_HEAVY);									break;
							default:						break;
						}	
					}
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
				case MnSYS_LANG_ENG:
					if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(pSt0, _sCH1_Light); 		break;
							case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(pSt0, _sCH1_Heavy); 		break;
							case MnOS1_ASSIGN_CH2_LIGHT:	_SPRINTF(pSt0, _sCH2_Light); 		break;
							case MnOS1_ASSIGN_CH2_HEAVY:	_SPRINTF(pSt0, _sCH2_Heavy);			break;
							default:						_SPRINTF(pSt0, _sNG);				break;
						}		
					}
					else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
					{
						switch(val)
						{
							case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(pSt0, _sLight); 		break;
							case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(pSt0, _sHeavy); 		break;
							default:						_SPRINTF(pSt0, _sNG);				break;
						}		
					}
					break;
			}
			break;
		case MnOS1_OPT_ACT:
		case MnOS1_OPT_STOP:
		case MnOS1_OPT_TEST:	_SPRINTF(pSt0, "%02d.%02d", val/100, val%100);	break;
		default:				_SPRINTF(pSt0, _sNG);							break;
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

// Popup - PCD
void DpOutPcd_PopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnOUT_PcdPrGet_Value(iIt);
	S32 min = -1, max = -1;
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	U08 fDp = _F_T;


	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpOut.pStr, lDpOut.sIt2[iIt]);	break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				case MnOS2_OPT_MODE:	_SPRINTF(lDpOut.pStr, _sMode);	break;
				case MnOS2_OPT_INTV:	_SPRINTF(lDpOut.pStr, _sIntv);	break;
				case MnOS2_OPT_TERM:	_SPRINTF(lDpOut.pStr, _sTerm);	break;
				default:				_SPRINTF(lDpOut.pStr, _sNG);	break;
			}			
			break;
	}



	DpPOP_UdtTitle(lDpOut.pStr);

	//old Value

	switch(iIt)
	{
		case MnOS2_OPT_MODE:	_SPRINTF(lDpOut.pStr, "%d", val);	break;
		case MnOS2_OPT_INTV:	_SPRINTF(lDpOut.pStr, "%d sec", val);	break;
		case MnOS2_OPT_TERM:	_SPRINTF(lDpOut.pStr, "%d sec", val);	break;
		default:				_SPRINTF(lDpOut.pStr, _sNG);		break;
	}

	DpPOP_UdtOldVl(lDpOut.pStr);

	// Range (Min. / Max.)

	switch(iIt)
	{
		case MnOS2_OPT_MODE:	fDp = _F_F;	break;
		case MnOS2_OPT_INTV:	min = MnOS2_INTV_MIN;	max = MnOS2_INTV_MAX;		break;
		case MnOS2_OPT_TERM:	min = MnOS2_TERM_MIN;	max = MnOS2_TERM_MAX;		break;
		default:																	break;
	}

	switch(iIt)
	{
		case MnOS2_OPT_MODE:	fDp = _F_F;	break;
		case MnOS2_OPT_INTV:	 		 
		case MnOS2_OPT_TERM:	_SPRINTF(lDpOut.pStr, "%d sec", min);	break;
		default:														break;
	}
	if(fDp) DpPOP_UdtRangeMin(lDpOut.pStr);
	fDp = _F_T;

	switch(iIt)
	{
		case MnOS2_OPT_MODE:	fDp = _F_F;	break;
		case MnOS2_OPT_INTV:	 		 
		case MnOS2_OPT_TERM:	_SPRINTF(lDpOut.pStr, "%d sec", max);	break;
		default:														break;
	}
	if(fDp) DpPOP_UdtRangeMax(lDpOut.pStr);
	fDp = _F_T;
	_SPRINTF(lDpOut.pStr, _sSel_PsSet);

	DpPOP_UdtExpla(lDpOut.pStr);


}

void DpOutPcd_PopUpdat(void)
{
	U16 val;
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };
	U08 iIt = MnLY2_GetIdxItem();
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();

	val = (U16)MnLY3_GetValue();

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{
		case MnOS2_OPT_MODE:	_SPRINTF(pSt0, "%d", val);		break;
		case MnOS2_OPT_INTV:	_SPRINTF(pSt0, "%04d", val);	break;
		case MnOS2_OPT_TERM:	_SPRINTF(pSt0, "%03d", val);	break;
		default:				_SPRINTF(pSt0, _sNG);			break;
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

// Popup - Error
void DpOutErr_PopIntro(void)
{
	U08 iIt = MnLY2_GetIdxItem();
	S32 val = MnOUT_ErrPrGet_Value(iIt);
	S32 min = -1, max = -1;
	U08 fDp = _F_T;

	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpOut.pStr, lDpOut.sIt3[iIt]);	break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				case MnOS3_OPT_ERR_DELAY:		_SPRINTF(lDpOut.pStr, _sErr_Delay);		break;
				case MnOS3_OPT_ERR_OUTP:		_SPRINTF(lDpOut.pStr, _sErr_Output);	break;
				default:						_SPRINTF(lDpOut.pStr, _sNG);			break;
			}		
			break;
	}

	DpPOP_UdtTitle(lDpOut.pStr);

	// Old Value
	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:		_SPRINTF(lDpOut.pStr, "%d sec", val);		break;
		case MnOS3_OPT_ERR_OUTP:	
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					if(val == MnOS3_ERR_OUTPUT_HOLD)
					{
						DpSTR_GuiList(TEXT_LIST_HOLD);	
						DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR,  gDpStr.Text_list);
						fDp = _F_F;
					}
					else
					{
						switch(val)
						{
							case MnOS3_ERR_OUTPUT_HOLD:	DpSTR_GuiList(TEXT_LIST_HOLD);			break;
							case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(lDpOut.pStr, _s3_8mA);			break;
							case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(lDpOut.pStr, _s21_0mA);		break;
							default:					_SPRINTF(lDpOut.pStr, _sNG);			break;
						}															
					}
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnOS3_ERR_OUTPUT_HOLD:	_SPRINTF(lDpOut.pStr, _sHold);			break;
						case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(lDpOut.pStr, _s3_8mA);			break;
						case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(lDpOut.pStr, _s21_0mA);		break;
						default:					_SPRINTF(lDpOut.pStr, _sNG);			break;
					}
					break;		
			}
			break;
		default:						_SPRINTF(lDpOut.pStr, _sNG);			break;
	}

	if(fDp)		DpPOP_UdtOldVl(lDpOut.pStr);
	fDp = _F_F;
	// Range (Min. / Max.)
	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:		min = MnOS3_ERR_DELAY_MIN;	max = MnOS3_ERR_DELAY_MAX;	break;
		case MnOS3_OPT_ERR_OUTP:		min = MnOS3_ERR_OUTPUT_MIN;	max = MnOS3_ERR_OUTPUT_MAX;	break;
		default:																				break;
	}

	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:		_SPRINTF(lDpOut.pStr, "%d sec", min);	fDp = _F_F;	break;
		case MnOS3_OPT_ERR_OUTP:
			fDp = _F_F;	break;
			switch(min)
			{
				case MnOS3_ERR_OUTPUT_HOLD:	_SPRINTF(lDpOut.pStr, _sHold);			break;
				case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(lDpOut.pStr, _s3_8mA);			break;
				case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(lDpOut.pStr, _s21_0mA);		break;
				default:					_SPRINTF(lDpOut.pStr, _sNG);			break;
			}
			break;
		default:																break;
	}	
	if(fDp) DpPOP_UdtRangeMin(lDpOut.pStr);

	fDp = _F_T;

	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:		_SPRINTF(lDpOut.pStr, "%d sec", max);	fDp = _F_F;	break;
		case MnOS3_OPT_ERR_OUTP:
			fDp = _F_F;	break;
			switch(max)
			{
				case MnOS3_ERR_OUTPUT_HOLD:	_SPRINTF(lDpOut.pStr, _sHold);			break;
				case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(lDpOut.pStr, _s3_8mA);			break;
				case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(lDpOut.pStr, _s21_0mA);		break;
				default:					_SPRINTF(lDpOut.pStr, _sNG);			break;
			}
			break;
		default:																	break;
	}	
	
	if(fDp)  DpPOP_UdtRangeMax(lDpOut.pStr);

	fDp = _F_T;

	_SPRINTF(lDpOut.pStr, _sSel_PsSet);

	//DpPOP_UdtExpla(lDpOut.pStr);

}

void DpOutErr_PopUpdat(void)
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
	U08 lang  = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(iIt)
	{
		case MnOS3_OPT_ERR_DELAY:		_SPRINTF(pSt0, "%03d", val);		break;
		case MnOS3_OPT_ERR_OUTP:
			switch(lang)
			{
				case MnSYS_LANG_KOR:
					DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
					if(val == MnOS3_ERR_OUTPUT_HOLD)
					{
						DpSTR_GuiList(TEXT_LIST_HOLD);	
						DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
						return;
					}
					else
					{
						switch(val)
						{
							case MnOS3_ERR_OUTPUT_HOLD:	DpSTR_GuiList(TEXT_LIST_HOLD);			break;
							case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(pSt0, _s3_8mA);			break;
							case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(pSt0, _s21_0mA);		break;
							default:					_SPRINTF(pSt0, _sNG);			break;
						}															
					}
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnOS3_ERR_OUTPUT_HOLD:	_SPRINTF(pSt0, _sHold);			break;
						case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(pSt0, _s3_8mA);			break;
						case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(pSt0, _s21_0mA);		break;
						default:					_SPRINTF(pSt0, _sNG);			break;
					}
					break;		
			}
			break;
		default:							_SPRINTF(pSt0, _sNG);			break;
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

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set)
I08* DpOUT_GetAddrSct(U08 idx)		{	return lDpOut.sSct[idx];	}
I08* DpOUT_GetAddrIt0(U08 idx)		{	return lDpOut.sIt0[idx];	}
I08* DpOUT_GetAddrVl0(U08 idx)		{	return lDpOut.sVl0[idx];	}
I08* DpOUT_GetAddrIt1(U08 idx)		{	return lDpOut.sIt1[idx];	}
I08* DpOUT_GetAddrVl1(U08 idx)		{	return lDpOut.sVl1[idx];	}
I08* DpOUT_GetAddrIt2(U08 idx)		{	return lDpOut.sIt2[idx];	}
I08* DpOUT_GetAddrVl2(U08 idx)		{	return lDpOut.sVl2[idx];	}
I08* DpOUT_GetAddrIt3(U08 idx)		{	return lDpOut.sIt3[idx];	}
I08* DpOUT_GetAddrVl3(U08 idx)		{	return lDpOut.sVl3[idx];	}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Additional
//------------------------------------------------------------------------------------------------------------------------------
void DpOUT_AddUpdat(void)
{

}

void DpOUT_AddIntro(void)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-Up
//------------------------------------------------------------------------------------------------------------------------------
void DpOUT_PopUpdat(void)
{
	U08 sub = MnLY1_GetSection();
	
	switch(sub)
	{
		case MnOUT_SUB_CURRENT:		DpOutCur_PopUpdat();	break;
		case MnOUT_SUB_RELAY:		DpOutRly_PopUpdat();	break;
		case MnOUT_SUB_CLEAN:			DpOutPcd_PopUpdat();break;
		case MnOUT_SUB_ERROR:		DpOutErr_PopUpdat();	break;
		default:
			break;		
	}
}

void DpOUT_PopIntro(void)
{
	U08 sub = MnLY1_GetSection();

	switch(sub)
	{
		case MnOUT_SUB_CURRENT:		DpOutCur_PopIntro();	break;
		case MnOUT_SUB_RELAY:		DpOutRly_PopIntro();	break;
		case MnOUT_SUB_CLEAN:		DpOutPcd_PopIntro();	break;
		case MnOUT_SUB_ERROR:		DpOutErr_PopIntro();	break;
		default:
			break;
	}
	
	// Update API
	DpOUT_PopUpdat();
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpOUT_InitVari(void)
{
	S32 val = 0;
	U08 lang =MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_CURRENT], _sCurr);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_RELAY],   _sRelay);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_CLEAN],     _sPCD);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_ERROR],   _sErr);

			// Item (S0 - Current)
			// Page #0 (CH0)
			if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
			{
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_ASSIGN],  _sCH1_Assign);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_SET_04mA], _sCH1_Set_04mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_SET_20mA], _sCH1_Set_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_TRM_12mA], _sCH1_Trm_12mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_TRM_20mA], _sCH1_Trm_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_OUT_04mA], _sCH1_Out_04mA);
				// Page #1 (CH1)
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_ASSIGN],   _sCH2_Assign);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_SET_04mA], _sCH2_Set_04mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_SET_20mA], _sCH2_Set_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_TRM_12mA], _sCH2_Trm_12mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_TRM_20mA], _sCH2_Trm_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_OUT_04mA], _sCH2_Out_04mA);
			}
			else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
			{
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_ASSIGN],  "Assign");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_SET_04mA], "Set     4mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_SET_20mA], "Set     20mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_TRM_12mA], "Trim    12mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_TRM_20mA], "Trim    20mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_OUT_04mA], "Output  4mA");
			}
			// Item (S1 - Relay)
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_ASSIGN], _sAssign);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_ACT],	_sAct);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_STOP],   _sStop);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_TEST],   _sTest);
			// Item (S2 - PCD)
			_SPRINTF(lDpOut.sIt2[MnOS2_OPT_MODE], _sMode);
			_SPRINTF(lDpOut.sIt2[MnOS2_OPT_INTV], _sIntv);
			_SPRINTF(lDpOut.sIt2[MnOS2_OPT_TERM], _sTerm);
			// Item (S3 - Error)
			_SPRINTF(lDpOut.sIt3[MnOS3_OPT_ERR_DELAY], _sErr_Delay);
			_SPRINTF(lDpOut.sIt3[MnOS3_OPT_ERR_OUTP], _sErr_Output);		
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_CURRENT_MENU);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_CURRENT],  gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_RELAY);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_RELAY],    gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_CLEAN);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_CLEAN],      gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_ERROR);
			_SPRINTF(lDpOut.sSct[MnOUT_SUB_ERROR],    gDpStr.Text_list);

			// Item (S0 - Current)
			// Page #0 (CH0)
			if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
			{
				DpSTR_GuiList(TEXT_LIST_CH1_ASSIGN);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_ASSIGN],  gDpStr.Text_list);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_SET_04mA], _sCH1_Set_04mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_SET_20mA], _sCH1_Set_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_TRM_12mA], _sCH1_Trm_12mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_TRM_20mA], _sCH1_Trm_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH1_OUT_04mA], _sCH1_Out_04mA);
				// Page #1 (CH1)
				DpSTR_GuiList(TEXT_LIST_CH2_ASSIGN);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_ASSIGN],   gDpStr.Text_list);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_SET_04mA], _sCH2_Set_04mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_SET_20mA], _sCH2_Set_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_TRM_12mA], _sCH2_Trm_12mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_TRM_20mA], _sCH2_Trm_20mA);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_CH2_OUT_04mA], _sCH2_Out_04mA);
			}
			else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
			{
				DpSTR_GuiList(TEXT_LIST_ASSIGN);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_ASSIGN],	gDpStr.Text_list);
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_SET_04mA], "Set		4mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_SET_20mA], "Set		20mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_TRM_12mA], "Trim		12mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_TRM_20mA], "Trim		20mA");
				_SPRINTF(lDpOut.sIt0[MnOS0_OPT_SINGLE_OUT_04mA], "Output	4mA");
			}
				// Item (S1 - Relay)
			DpSTR_GuiList(TEXT_LIST_ASSIGN);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_ACT);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_ACT],	gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_STOP);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_STOP],   gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_TEST_MENU);
			_SPRINTF(lDpOut.sIt1[MnOS1_OPT_TEST],   gDpStr.Text_list);
			// Item (S2 - PCD)
			DpSTR_GuiList(TEXT_LIST_MODE);
			_SPRINTF(lDpOut.sIt2[MnOS2_OPT_MODE], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_INTV);
			_SPRINTF(lDpOut.sIt2[MnOS2_OPT_INTV], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_TERM);
			_SPRINTF(lDpOut.sIt2[MnOS2_OPT_TERM], gDpStr.Text_list);
			// Item (S3 - Error)
			DpSTR_GuiList(TEXT_LIST_ERROR_DELAY);
			_SPRINTF(lDpOut.sIt3[MnOS3_OPT_ERR_DELAY], gDpStr.Text_list);
			DpSTR_GuiList(TEXT_LIST_ERROR_OUTPUT);
			_SPRINTF(lDpOut.sIt3[MnOS3_OPT_ERR_OUTP], gDpStr.Text_list);
			break;

	}

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:
				switch(MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_ASSIGN))
				{
					case MnOS0_ASSIGN_LIGHT:		DpSTR_GuiList(TEXT_LIST_LIGHT);	_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], gDpStr.Text_list);	break;
					case MnOS0_ASSIGN_HEAVY:		DpSTR_GuiList(TEXT_LIST_HEAVY);	_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], gDpStr.Text_list);	break;
					default:						_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], _sNG);		break;
				}

				switch(MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_ASSIGN))
				{
					case MnOS0_ASSIGN_LIGHT:		DpSTR_GuiList(TEXT_LIST_LIGHT);	_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_ASSIGN], gDpStr.Text_list);	break;
					case MnOS0_ASSIGN_HEAVY:		DpSTR_GuiList(TEXT_LIST_HEAVY);	_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_ASSIGN], gDpStr.Text_list);	break;
					default:						_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_ASSIGN], _sNG);		break;
				}			
				break;
			case MnSYS_LANG_ENG:
				switch(MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_ASSIGN))
				{
					case MnOS0_ASSIGN_LIGHT:		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], _sLight);	break;
					case MnOS0_ASSIGN_HEAVY:		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], _sHeavy);	break;
					default:						_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], _sNG);		break;
				}
				
				switch(MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_ASSIGN))
				{
					case MnOS0_ASSIGN_LIGHT:		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_ASSIGN], _sLight);	break;
					case MnOS0_ASSIGN_HEAVY:		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_ASSIGN], _sHeavy);	break;
					default:						_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_ASSIGN], _sNG);		break;
				}			
				break;

		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:
				switch(MnOUT_CurPrGet_Value(MnOS0_OPT_SINGLE_ASSIGN))
				{
					case MnOS0_ASSIGN_LIGHT:		DpSTR_GuiList(TEXT_LIST_LIGHT); _SPRINTF(lDpOut.sVl0[MnOS0_OPT_SINGLE_ASSIGN], gDpStr.Text_list);	break;
					case MnOS0_ASSIGN_HEAVY:		DpSTR_GuiList(TEXT_LIST_HEAVY); _SPRINTF(lDpOut.sVl0[MnOS0_OPT_SINGLE_ASSIGN], gDpStr.Text_list);	break;
					default:						_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_ASSIGN], _sNG);		break;
				}
		
				break;
			case MnSYS_LANG_ENG:
				switch(MnOUT_CurPrGet_Value(MnOS0_OPT_SINGLE_ASSIGN))
				{
					case MnOS0_ASSIGN_LIGHT:		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_SINGLE_ASSIGN], _sLight);	break;
					case MnOS0_ASSIGN_HEAVY:		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_SINGLE_ASSIGN], _sHeavy);	break;
					default:						_SPRINTF(lDpOut.sVl0[MnOS0_OPT_SINGLE_ASSIGN], _sNG);		break;
				}		
				break;
		
		}
	}

	// Value (S0 - Current)



	// PAGE #0 (CH0)
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_SET_04mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_SET_04mA], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_SET_20mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_SET_20mA], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_TRM_12mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_TRM_12mA], " %d", val);
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH1_TRM_20mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH1_TRM_20mA], " %d", val);
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_SET_04mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_SET_04mA], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_SET_20mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_SET_20mA], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_TRM_12mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_TRM_12mA], " %d", val);
	val = MnOUT_CurPrGet_Value(MnOS0_OPT_CH2_TRM_20mA);		_SPRINTF(lDpOut.sVl0[MnOS0_OPT_CH2_TRM_20mA], " %d", val);

	// Value (S1 - Relay)
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:	
				switch(MnOUT_RlyPrGet_Value(MnOS1_OPT_ASSIGN))
				{
					case MnOS1_ASSIGN_CH1_LIGHT:	DpSTR_GuiList(TEXT_LIST_CH1_LIGHT);	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);	break;
					case MnOS1_ASSIGN_CH1_HEAVY:	DpSTR_GuiList(TEXT_LIST_CH1_HEAVY);	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);	break;
					case MnOS1_ASSIGN_CH2_LIGHT:	DpSTR_GuiList(TEXT_LIST_CH2_LIGHT);	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);	break;
					case MnOS1_ASSIGN_CH2_HEAVY:	DpSTR_GuiList(TEXT_LIST_CH2_HEAVY);	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);	break;
					default:						_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sNG);			break;
				}
				break;
			case MnSYS_LANG_ENG:
				switch(MnOUT_RlyPrGet_Value(MnOS1_OPT_ASSIGN))
				{
					case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sCH1_Light);	break;
					case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sCH1_Heavy);	break;
					case MnOS1_ASSIGN_CH2_LIGHT:	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sCH2_Light);	break;
					case MnOS1_ASSIGN_CH2_HEAVY:	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sCH2_Heavy);	break;
					default:						_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sNG);			break;
				}			
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:	
				switch(MnOUT_RlyPrGet_Value(MnOS1_OPT_ASSIGN))
				{
					case MnOS1_ASSIGN_CH1_LIGHT:	DpSTR_GuiList(TEXT_LIST_LIGHT); _SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);	break;
					case MnOS1_ASSIGN_CH1_HEAVY:	DpSTR_GuiList(TEXT_LIST_HEAVY); _SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], gDpStr.Text_list);	break;
					default:						_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sNG);			break;
				}
				break;
			case MnSYS_LANG_ENG:
				switch(MnOUT_RlyPrGet_Value(MnOS1_OPT_ASSIGN))
				{
					case MnOS1_ASSIGN_CH1_LIGHT:	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sLight);	break;
					case MnOS1_ASSIGN_CH1_HEAVY:	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sHeavy);	break;
					default:						_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ASSIGN], _sNG);			break;
				}			
				break;
		}
	}
	
	val = MnOUT_RlyPrGet_Value(MnOS1_OPT_ACT);	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_ACT],  "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	val = MnOUT_RlyPrGet_Value(MnOS1_OPT_STOP);	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_STOP], "%2d.%02d m", (U16)(val/100), (U16)(val%100));
	_SPRINTF(lDpOut.sVl1[MnOS1_OPT_TEST], 	"-");
	
	// Value (S2 - PCD)
	val = MnOUT_PcdPrGet_Value(MnOS2_OPT_MODE);	_SPRINTF(lDpOut.sVl2[MnOS2_OPT_MODE], " %d", (U16)val);
	val = MnOUT_PcdPrGet_Value(MnOS2_OPT_INTV);	_SPRINTF(lDpOut.sVl2[MnOS2_OPT_INTV], " %d sec", (U16)val);
	val = MnOUT_PcdPrGet_Value(MnOS2_OPT_TERM);	_SPRINTF(lDpOut.sVl2[MnOS2_OPT_TERM], " %d sec", (U08)val);

	// Value (S3 - Error)
	val = MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_DELAY);	_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_DELAY], " %d sec", (U16)val);
	
	switch(MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_OUTP))
	{
		case MnOS3_ERR_OUTPUT_HOLD:	
			switch(lang)
			{
				case MnSYS_LANG_ENG:		
					_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_OUTP], _sHold);		
					break;
				case MnSYS_LANG_KOR:
					DpSTR_GuiList(TEXT_LIST_HOLD);	_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_OUTP], gDpStr.Text_list);		
					break;
			}
			break;
		case MnOS3_ERR_OUTPUT_38mA:	_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_OUTP], _s3_8mA);		break;
		case MnOS3_ERR_OUTPUT_21mA:	_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_OUTP], _s21_0mA);	break;
		default:					_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_OUTP], _sNG);		break;
	}

	_MEMSET(lDpOut.pStr, 0, sizeof(lDpOut.pStr));
}

void DpOT1_StrSbSct(void)
{
	U08 i=0;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 lang =MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	for(i=0; i<MnOUT_SUB_NUM; i++)
	{
		switch(lang)
		{
			case MnSYS_LANG_ENG:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, lDpOut.sSct[i]);
				break;
			case MnSYS_LANG_KOR:
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, lDpOut.sSct[i]);
				break;
		}
	}

}


void DpOUT_StrCntts_Current(U08 idx,U08 i, U32 text_color, U32 back_color)
{
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(idx)
		{
			case MnOS0_OPT_CH1_ASSIGN:
			case MnOS0_OPT_CH2_ASSIGN:			
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, lDpOut.sIt0[idx]);
				DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, lDpOut.sVl0[idx]);
				break;
			case MnOS0_OPT_CH1_SET_04mA:
				DpSTR_GuiList(TEXT_LIST_CH_1);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "4 mA");
				DpSTR_GuiList(TEXT_LIST_SET);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;
			case MnOS0_OPT_CH1_SET_20mA:
				DpSTR_GuiList(TEXT_LIST_CH_1);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "20 mA");
				DpSTR_GuiList(TEXT_LIST_SET);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_CH1_TRM_12mA:
				DpSTR_GuiList(TEXT_LIST_CH_1);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, "12 mA");
				DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;
			case MnOS0_OPT_CH1_TRM_20mA:
				DpSTR_GuiList(TEXT_LIST_CH_1);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "20 mA");
				DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_CH1_OUT_04mA:
				DpSTR_GuiList(TEXT_LIST_CH_1);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "4 mA");
				DpSTR_GuiList(TEXT_LIST_CH1_OUTPUT);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_CH2_SET_04mA:
				DpSTR_GuiList(TEXT_LIST_CH_2);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "4 mA");
				DpSTR_GuiList(TEXT_LIST_SET);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;
			case MnOS0_OPT_CH2_SET_20mA:
				DpSTR_GuiList(TEXT_LIST_CH_2);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "20 mA");
				DpSTR_GuiList(TEXT_LIST_SET);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_CH2_TRM_12mA:
				DpSTR_GuiList(TEXT_LIST_CH_2);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "12 mA");
				DpSTR_GuiList(TEXT_LIST_CH2_TRIM);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;
			case MnOS0_OPT_CH2_TRM_20mA:
				DpSTR_GuiList(TEXT_LIST_CH_2);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "20 mA");
				DpSTR_GuiList(TEXT_LIST_CH2_TRIM);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_CH2_OUT_04mA:
				DpSTR_GuiList(TEXT_LIST_CH_2);
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);
				DpSTR_GuiLeft(box_itm_x0+80, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "4 mA");
				DpSTR_GuiList(TEXT_LIST_CH2_OUTPUT);
				DpSTR_GuiLeft_KOR(box_itm_x0+150, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;									
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(idx)
		{
			case MnOS0_OPT_SINGLE_ASSIGN:		
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, lDpOut.sIt0[idx]);
				DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, lDpOut.sVl0[idx]);
				break;
			case MnOS0_OPT_SINGLE_SET_04mA:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "4 mA");
				DpSTR_GuiList(TEXT_LIST_SET);
				DpSTR_GuiLeft_KOR(box_itm_x0+70, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;
			case MnOS0_OPT_SINGLE_SET_20mA:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "20 mA");
				DpSTR_GuiList(TEXT_LIST_SET);
				DpSTR_GuiLeft_KOR(box_itm_x0+70, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_SINGLE_TRM_12mA:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, "12 mA");
				DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
				DpSTR_GuiLeft_KOR(box_itm_x0+70, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;
			case MnOS0_OPT_SINGLE_TRM_20mA:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "20 mA");
				DpSTR_GuiList(TEXT_LIST_CH1_TRIM);
				DpSTR_GuiLeft_KOR(box_itm_x0+70, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;			
			case MnOS0_OPT_SINGLE_OUT_04mA:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i)-2, text_color, back_color, _fE17HsB, "4 mA");
				DpSTR_GuiList(TEXT_LIST_CH1_OUTPUT);
				DpSTR_GuiLeft_KOR(box_itm_x0+70, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, gDpStr.Text_list);	
				break;												
		}
	}
}


void DpOUT_StrCntts(void)
{
	U08 i, n, page, iN, idx;
	I08 *pItm, *pVal;
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U32 back_color = _cMNU_BOX_BG;
	U32 text_color = _cMNU_STR_IDLE;

	switch(iSb)
	{
		case MnOUT_SUB_CURRENT:	
			if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
				n = MnOS0_OPT_NUM;			
			else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
				n = MnOS0_OPT_SINGLE_NUM;
			break;
		case MnOUT_SUB_RELAY:		n = MnOS1_OPT_NUM;			break;
		case MnOUT_SUB_CLEAN:		n = MnOS2_OPT_NUM;			break;
		case MnOUT_SUB_ERROR:		n = MnOS3_OPT_NUM;			break;
		default:					return;
	}

	// Calc. Page
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


	for(i=0; i<iN; i++)
	{
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
		DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-60-30, 37, _cMNU_BOX_BG, DpFIG_FILL);

		idx = i+(DpMNU_ITM_PAGE*page);

		switch(lang)
		{
			case MnSYS_LANG_ENG:
				switch(iSb)
				{
					case MnOUT_SUB_CURRENT: 	pItm = lDpOut.sIt0[idx];	pVal = lDpOut.sVl0[idx];	break;
					case MnOUT_SUB_RELAY:		pItm = lDpOut.sIt1[idx];	pVal = lDpOut.sVl1[idx];	break;
					case MnOUT_SUB_CLEAN:		pItm = lDpOut.sIt2[idx];	pVal = lDpOut.sVl2[idx];	break;
					case MnOUT_SUB_ERROR:		pItm = lDpOut.sIt3[idx];	pVal = lDpOut.sVl3[idx];	break;
					default:					return;
				}


				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, pItm);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);				
				break;
			case MnSYS_LANG_KOR:
				switch(iSb)
				{
					case MnOUT_SUB_CURRENT: 
						pVal = lDpOut.sVl0[idx];
						DpOUT_StrCntts_Current(idx,i, text_color, back_color);
						DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
						break;
					case MnOUT_SUB_RELAY:	
						pItm = lDpOut.sIt1[idx];	pVal = lDpOut.sVl1[idx];
						switch(idx)
						{
							case MnOS1_OPT_ASSIGN:
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, pVal);			
								break;
							default:
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
						}
						break;
					case MnOUT_SUB_CLEAN:		
						pItm = lDpOut.sIt2[idx];	pVal = lDpOut.sVl2[idx];	
						DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
						DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
						break;
					case MnOUT_SUB_ERROR:		
						switch(idx)
						{
							case MnOS3_OPT_ERR_OUTP:
								pItm = lDpOut.sIt3[idx];	pVal = lDpOut.sVl3[idx];
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								switch(MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_OUTP))
								{
									case MnOS3_ERR_OUTPUT_HOLD: DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, pVal); break;
									case MnOS3_ERR_OUTPUT_38mA: 
									case MnOS3_ERR_OUTPUT_21mA: DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal); 		break;
									default:					_SPRINTF(lDpOut.sVl3[MnOS3_OPT_ERR_OUTP], _sNG);		break;
								}
								break;
							case MnOS3_OPT_ERR_DELAY:
								pItm = lDpOut.sIt3[idx];	pVal = lDpOut.sVl3[idx];
								DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR, pItm);
								DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, pVal);
								break;
						}
						break;
					default:					
						return;
				}				
				break;
		}

	}

}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

