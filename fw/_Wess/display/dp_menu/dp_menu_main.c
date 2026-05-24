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
// menu
#include "menu_main.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
// display
#include "fonts.h"
#include "disp_main.h"
#include "disp_color.h"
#include "disp_figure.h"
#include "disp_string.h"
#include "disp_button.h"
#include "disp_titlebar.h"
#include "disp_popup.h"
// disp - menu
#include "dp_menu_measure.h"
#include "dp_menu_output.h"
#include "dp_menu_data.h"
#include "dp_menu_system.h"
#include "dp_menu_engineer.h"
#include "dp_menu_factory.h"
#include "dp_menu_test.h"
// disp - screen
#include "dp_screen_main.h"
// self
#include "dp_menu_main.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
I08 lMn_sSct[MENU_SCN_NUM][16];


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L3 (Additional)
//------------------------------------------------------------------------------------------------------------------------------
void DpM4_AddUpdat(void)
{

}

void DpM4_AddIntro(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;

	U32 cBg = _cPOP_BG_WND;

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:		DpMSR_AddIntro();		break;
		case MENU_SC1_OUTP:		DpOUT_PopIntro();		DpOUT_AddIntro();		break;
		case MENU_SC2_DATA:		DpDAT_PopIntro();		DpDAT_AddIntro();		break;
		case MENU_SC3_SYST:		DpSYS_PopIntro();		DpSYS_AddIntro();		break;
		case MENU_SC4_EGNR:		DpEGN_PopIntro();		DpEGN_AddIntro();		break;
		case MENU_SC5_FCTR:		DpFTR_PopIntro();		DpFTR_AddIntro();		break;
		case MENU_SC6_TEST:		break;
		default:				return;
	}

	// Button
	DpMN_UpdtBttn(MENU_L4_ADDITION);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L2 (Value)
//------------------------------------------------------------------------------------------------------------------------------
void DpM3_UpdatPop(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U16 y1 = DpPOP_CT2_Y0;

	U32 cBg = _cPOP_BG_WND;
	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

	switch(MENU_GetSection())
	{
		case MENU_SC0_MEAS:		DpMSR_PopUpdat();		break;
		case MENU_SC1_OUTP:		DpOUT_PopUpdat();		break;
		case MENU_SC2_DATA:		DpDAT_PopUpdat();		break;
		case MENU_SC3_SYST:		DpSYS_PopUpdat();		break;
		case MENU_SC4_EGNR:		DpEGN_PopUpdat();		break;
		case MENU_SC5_FCTR: 	DpFTR_PopUpdat();		break;
		case MENU_SC6_TEST:		DpTST_PopUpdat();		break;
		default:				return;
	}
}

void DpM3_IntroPop(void)
{
	U08 iSc = MENU_GetSection();

	// Pop-up Window
	DpPOP_DrwIntro();

	switch(iSc)
	{
		case MENU_SC0_MEAS:		DpMSR_PopIntro();		break;
		case MENU_SC1_OUTP:		DpOUT_PopIntro();		break;
		case MENU_SC2_DATA:		DpDAT_PopIntro();		break;
		case MENU_SC3_SYST:		DpSYS_PopIntro();		break;
		case MENU_SC4_EGNR:		DpEGN_PopIntro();		break;
		case MENU_SC5_FCTR:		DpFTR_PopIntro();		break;
		case MENU_SC6_TEST:		DpTST_PopIntro();		break;
		default:				return;
	}

	// Update
	DpM3_UpdatPop();
	// Button
	//DpPOP_DrwIntro();
	DpMN_UpdtBttn(MENU_L3_VALUE);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L2 (Item)
//------------------------------------------------------------------------------------------------------------------------------
void DpM2_UpdatItm(void)
{	
	U08 iN;
	//U08 iPg = DpMNU_ITM_PAGE;
	U16 box_x0 = DpMNU_BOX_X0_ITM;
	U16 box_x1 = DpMNU_BOX_X0_VAL;
	U16 box_y0 = DpMNU_BOX_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iSc = MENU_GetSection();
	U08 iSb = MnLY1_GetSection();
	U08 iIt = MnLY2_GetIdxItem();	


#if 0
	// Box - Backgroud (Item & Value)
	switch(iSc)
	{
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:		
		case MENU_SC3_SYST:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
			DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			DpFIG_DrwRect(DpMNU_BOX_X0_VAL, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			break;
		case MENU_SC0_MEAS:
		case MENU_SC4_EGNR:
			DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID+60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, DpMNU_BOX_Y0, DpMNU_BOX_WID-60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			break;			
		default:
			break;
	}
#else
	DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID+60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
	DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, DpMNU_BOX_Y0, DpMNU_BOX_WID-60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);


#endif
	switch(iSc)
	{
		case MENU_SC0_MEAS:		DpMSR_StrCntts(iSb);		break;
		case MENU_SC1_OUTP:		DpOUT_StrCntts();			break;
		case MENU_SC2_DATA:		DpDAT_StrCntts(iSb);		break;
		case MENU_SC3_SYST:		DpSY2_StrCntts(iSb);		break;
		case MENU_SC4_EGNR:		DpEG2_StrCntts();			break;
		case MENU_SC5_FCTR:		DpFT2_StrCntts();			break;
		case MENU_SC6_TEST:		DpTS2_StrCntts();			break;
		default:				return;
	}

#if 0
	switch(iSc)
	{
		case MENU_SC0_MEAS:		
			switch(iSb)
			{
				case MnMSR_SUB_BASE:		sItm = DpMSR_GetAddrIt0(iIt);		sVal = DpMSR_GetAddrVl0(iIt);		break;
				case MnMSR_SUB_CAL:			sItm = DpMSR_GetAddrIt1(iIt);		sVal = DpMSR_GetAddrVl1(iIt);		break;
			}
			break;
		case MENU_SC1_OUTP:
			switch(iSb)
			{
				case MnOUT_SUB_CURRENT:		sItm = DpOUT_GetAddrIt0(iIt);		sVal = DpOUT_GetAddrVl0(iIt);		break;
				case MnOUT_SUB_RELAY:		sItm = DpOUT_GetAddrIt1(iIt);		sVal = DpOUT_GetAddrVl1(iIt);		break;
				case MnOUT_SUB_CLEAN:		sItm = DpOUT_GetAddrIt2(iIt);		sVal = DpOUT_GetAddrVl2(iIt);		break;
				case MnOUT_SUB_ERROR:		sItm = DpOUT_GetAddrIt3(iIt);		sVal = DpOUT_GetAddrVl3(iIt);		break;
			}
			break;
		case MENU_SC2_DATA:
			switch(iSb)
			{
				case MnDAT_SUB_SAVE:		sItm = DpDAT_GetAddrIt0(iIt);		sVal = DpDAT_GetAddrVl0(iIt);		break;
				case MnDAT_SUB_COMM:		sItm = DpDAT_GetAddrIt1(iIt);		sVal = DpDAT_GetAddrVl1(iIt);		break;
			}
			break;
		case MENU_SC3_SYST:					sItm = DpSYS_GetAddrIt0(iIt);		sVal = DpSYS_GetAddrVa0(iIt);		break;
		case MENU_SC4_EGNR:					sItm = DpEGN_GetAddrItm(iIt);		sVal = DpEGN_GetAddrVal(iIt);		break;
		case MENU_SC5_FCTR:					sItm = DpFTR_GetAddrItm(iIt);		sVal = DpFTR_GetAddrVal(iIt);		break;
		case MENU_SC6_TEST:					sItm = DpTST_GetAddrItm(iIt);		sVal = DpTST_GetAddrVal(iIt);		break;
	}
#endif
	iN = (iIt%DpMNU_ITM_PAGE);
 	
	// Selection Box
#if 0
	DpFIG_DrwRect(box_x0, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-5, 40, _cMNU_SEL_ITM, DpFIG_FILL);
	DpFIG_DrwRect(box_x1, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-30, 40, _cMNU_BOX_BG,  DpFIG_FILL);
	DpSTR_GuiLeft(str_x0-8,    str_y0+(str_yg*iN), _cSD_DARKGRAY, _cMNU_SEL_ITM, _fE17HsB, sItm);
	DpSTR_GuiLeft(str_x1,    str_y0+(str_yg*iN), _cSD_WHITE,    _cMNU_BOX_BG,  _fE17HsB, sVal);	
#endif

#if 0
	switch(iSc)
	{
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:		
		case MENU_SC3_SYST:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
			DpFIG_DrwRect(box_x0, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-5, 40, _cMNU_SEL_ITM, DpFIG_FILL);
			DpFIG_DrwRect(box_x1, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-30, 40, _cMNU_BOX_BG,  DpFIG_FILL);	
			DpSTR_GuiLeft(str_x0-8,    str_y0+(str_yg*iN), _cSD_DARKGRAY, _cMNU_SEL_ITM, _fE17HsB, sItm);
			DpSTR_GuiLeft(str_x1,	 str_y0+(str_yg*iN), _cSD_WHITE,	_cMNU_BOX_BG,  _fE17HsB, sVal); 
			break;
		case MENU_SC0_MEAS:	
		case MENU_SC4_EGNR:
			DpFIG_DrwRect(box_x0, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-5+60, 40, _cMNU_SEL_ITM, DpFIG_FILL);
			DpFIG_DrwRect(box_x1+60, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-30-60, 40, _cMNU_BOX_BG,  DpFIG_FILL);				
			DpSTR_GuiLeft(str_x0-8,    str_y0+(str_yg*iN), _cSD_DARKGRAY, _cMNU_SEL_ITM, _fE17HsB, sItm);
			DpSTR_GuiLeft(str_x1+60,	 str_y0+(str_yg*iN), _cSD_WHITE,	_cMNU_BOX_BG,  _fE17HsB, sVal); 
			break;			
		default:
			break;
	}	
#else

	DpFIG_DrwRect(box_x0, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-5+60, 40, _cMNU_SEL_ITM, DpFIG_FILL);
	DpFIG_DrwRect(box_x1+60, box_y0+(str_yg*iN)+15, DpMNU_BOX_WID-30-60, 40, _cMNU_BOX_BG,	DpFIG_FILL);		

	switch(iSc)
	{
		case MENU_SC0_MEAS:		DpMSR_StrCntts(iSb);		break;
		case MENU_SC1_OUTP:		DpOUT_StrCntts();			break;
		case MENU_SC2_DATA:		DpDAT_StrCntts(iSb);		break;
		case MENU_SC3_SYST:		DpSY2_StrCntts(iSb);			break;
		case MENU_SC4_EGNR:		DpEG2_StrCntts();			break;
		case MENU_SC5_FCTR:		DpFT2_StrCntts();			break;
		case MENU_SC6_TEST:		DpTS2_StrCntts();			break;
		default:				return;
	}

#endif
	
}

void DpM2_IntroItm(void)
{
	// Update
	DpM2_UpdatItm();
	// Button
	DpMN_UpdtBttn(MENU_L2_ITEM);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L1 (Sub-Section)
//------------------------------------------------------------------------------------------------------------------------------
void DpM1_UpdatSub(void)
{
	U08 i, n;
	I08 *sSct;
	U16 box_x0 = DpMNU_BOX_X0_SCT;
	U16 box_y0 = DpMNU_BOX_Y0;
	U16 str_x0 = DpMNU_STR_X0_SCT;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U32 col_st = _cMNU_STR_IDLE;
	U08 sct = MENU_GetSection();
	U08 sub = MnLY1_GetSection();
	I08 pSt0[16] = {0, };
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	// Sub-section - Background
	DpFIG_DrwRect(DpMNU_BOX_X0_SCT, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cMNU_BOX_BG,  DpFIG_FILL);

	switch(sct)
	{
		case MENU_SC0_MEAS:     n = MnMSR_SUB_NUM;		_SPRINTF(pSt0, _sMeas);		DpSTR_GuiList(TEXT_LIST_MEASUREMENT);	break;
		case MENU_SC1_OUTP:		n = MnOUT_SUB_NUM;		_SPRINTF(pSt0, _sOutp);		DpSTR_GuiList(TEXT_LIST_OUTPUT);		break;
		case MENU_SC2_DATA:		n = MnDAT_SUB_NUM;		_SPRINTF(pSt0, _sData);		DpSTR_GuiList(TEXT_LIST_DATA);			break;
		// Not Use
		case MENU_SC3_SYST:		n = MnSYS_SUB_NUM;		_SPRINTF(pSt0, _sSyst);		DpSTR_GuiList(TEXT_LIST_SYSTEM);		break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:				return;
	}

	// Main-section
	switch(lang)
	{
		case MnSYS_LANG_KOR:
			DpFIG_DrwRect(box_x0+10, box_y0+(str_yg*0)+15, DpMNU_BOX_WID-30, 40, _cMNU_SEL_SCT, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(str_x0,	 str_y0+(str_yg*0),    _cSD_WHITE, _cMNU_SEL_SCT, _fE17HsBKOR, gDpStr.Text_list);
			break;			
		case MnSYS_LANG_ENG:
			DpFIG_DrwRect(box_x0+10, box_y0+(str_yg*0)+15, DpMNU_BOX_WID-30, 40, _cMNU_SEL_SCT, DpFIG_FILL);
			DpSTR_GuiLeft(str_x0,	 str_y0+(str_yg*0),    _cSD_WHITE, _cMNU_SEL_SCT, _fE17HsB, pSt0);
			break;
		default:
			break;
	}
	

	switch(lang)
	{
		case MnSYS_LANG_KOR:
		// Sub-section - String (All)
			for(i=0; i<n; i++)
			{
				switch(sct)
				{
					case MENU_SC0_MEAS:
						switch(i)
						{
							case MnMSR_SUB_BASE:	DpSTR_GuiList(TEXT_LIST_BASE);			break;
							case MnMSR_SUB_CAL:		DpSTR_GuiList(TEXT_LIST_CALIBRATION);	break;
						}
						break;
					case MENU_SC1_OUTP:
						switch(i)
						{
							case MnOUT_SUB_CLEAN:	DpSTR_GuiList(TEXT_LIST_CLEAN);			break;
							case MnOUT_SUB_CURRENT:	DpSTR_GuiList(TEXT_LIST_CURRENT_MENU);	break;
							case MnOUT_SUB_RELAY:	DpSTR_GuiList(TEXT_LIST_RELAY);			break;
							case MnOUT_SUB_ERROR:	DpSTR_GuiList(TEXT_LIST_ERROR);			break;							
						}
						break;						
					case MENU_SC2_DATA:
						switch(i)
						{
							case MnDAT_SUB_SAVE:	DpSTR_GuiList(TEXT_LIST_SAVE);			break;
							case MnDAT_SUB_COMM:	DpSTR_GuiList(TEXT_LIST_COMM);			break;
						}
						break;						
					// Not Use
					case MENU_SC3_SYST:
						switch(i)
						{
							case MnSYS_SUB_BASE:	DpSTR_GuiList(TEXT_LIST_BASE);			break;
							case MnSYS_SUB_ALARM:	DpSTR_GuiList(TEXT_LIST_ALARM);			break;
						}
						break;	
					case MENU_SC4_EGNR:
					case MENU_SC5_FCTR:
					case MENU_SC6_TEST:
					default:				return;
				}
			
				DpSTR_GuiLeft_KOR(str_x0+10, str_y0+(str_yg*(i+1)), col_st, _cTTB_BG_MID, _fE17HsBKOR, gDpStr.Text_list);
			}
			
			// Sub-section - String (Select)
			switch(sct)
			{
				case MENU_SC0_MEAS:
					switch(sub)
					{
						case MnMSR_SUB_BASE:	DpSTR_GuiList(TEXT_LIST_BASE);			break;
						case MnMSR_SUB_CAL: 	DpSTR_GuiList(TEXT_LIST_CALIBRATION);	break;
					}
					break;
				case MENU_SC1_OUTP:
					switch(sub)
					{
						case MnOUT_SUB_CLEAN:	DpSTR_GuiList(TEXT_LIST_CLEAN); 		break;
						case MnOUT_SUB_CURRENT: DpSTR_GuiList(TEXT_LIST_CURRENT_MENU);	break;
						case MnOUT_SUB_RELAY:	DpSTR_GuiList(TEXT_LIST_RELAY); 		break;
						case MnOUT_SUB_ERROR:	DpSTR_GuiList(TEXT_LIST_ERROR); 		break;							
					}
					break;						
				case MENU_SC2_DATA:
					switch(sub)
					{
						case MnDAT_SUB_SAVE:	DpSTR_GuiList(TEXT_LIST_SAVE);			break;
						case MnDAT_SUB_COMM:	DpSTR_GuiList(TEXT_LIST_COMM);			break;
					}
					break;						
				// Not Use
				case MENU_SC3_SYST:
					switch(sub)
					{
						case MnSYS_SUB_BASE:	DpSTR_GuiList(TEXT_LIST_BASE);			break;
						case MnSYS_SUB_ALARM:	DpSTR_GuiList(TEXT_LIST_ALARM);			break;
					}
					break;	
				case MENU_SC4_EGNR:
				case MENU_SC5_FCTR:
				case MENU_SC6_TEST:
				default:				return;
			}

			DpFIG_DrwRect(box_x0+20, box_y0+(str_yg*(sub+1))+15, DpMNU_BOX_WID-50, 40, _cMNU_SEL_SUB, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(str_x0+10, str_y0+(str_yg*(sub+1)),	 _cSD_DARKGRAY, _cMNU_SEL_SUB, _fE17HsBKOR, gDpStr.Text_list);
			break;
		case MnSYS_LANG_ENG:
			// Sub-section - String (All)
			for(i=0; i<n; i++)
			{
				switch(sct)
				{
					case MENU_SC0_MEAS:     sSct = DpMSR_GetAddrSct(i);		break;
					case MENU_SC1_OUTP: 	sSct = DpOUT_GetAddrSct(i);		break;
					case MENU_SC2_DATA: 	sSct = DpDAT_GetAddrSct(i);		break;
					// Not Use
					case MENU_SC3_SYST:		sSct = DpSYS_GetAddrSct(i);		break;
					case MENU_SC4_EGNR:
					case MENU_SC5_FCTR:
					case MENU_SC6_TEST:
					default:				return;
				}

				DpSTR_GuiLeft(str_x0+10, str_y0+(str_yg*(i+1)), col_st, _cTTB_BG_MID, _fE17HsB, sSct);
			}

			// Sub-section - String (Select)
			switch(sct)
			{
				case MENU_SC0_MEAS:		sSct = DpMSR_GetAddrSct(sub);		break;
				case MENU_SC1_OUTP:		sSct = DpOUT_GetAddrSct(sub);		break;
				case MENU_SC2_DATA:		sSct = DpDAT_GetAddrSct(sub);		break;
				// Not Use
				case MENU_SC3_SYST:		sSct = DpSYS_GetAddrSct(sub);		break;
				case MENU_SC4_EGNR:
				case MENU_SC5_FCTR:
				case MENU_SC6_TEST:
				default:				return;
			}
			DpFIG_DrwRect(box_x0+20, box_y0+(str_yg*(sub+1))+15, DpMNU_BOX_WID-50, 40, _cMNU_SEL_SUB, DpFIG_FILL);
			DpSTR_GuiLeft(str_x0+10, str_y0+(str_yg*(sub+1)),    _cSD_DARKGRAY, _cMNU_SEL_SUB, _fE17HsB, sSct);			
			break;
	}





	// Item & Value - Background

#if 0
	switch(sct)
	{
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:
		case MENU_SC3_SYST:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
			DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cMNU_BOX_BG, DpFIG_FILL);
			DpFIG_DrwRect(DpMNU_BOX_X0_VAL, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cMNU_BOX_BG, 	  DpFIG_FILL);
			break;
		case MENU_SC0_MEAS:
		case MENU_SC4_EGNR:
			DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID+60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, DpMNU_BOX_Y0, DpMNU_BOX_WID-60, DpMNU_BOX_HEI, _cTTB_BG_MID, 	  DpFIG_FILL);
			break;			
		default:
			break;
	}
#else
	DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID+60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
	DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, DpMNU_BOX_Y0, DpMNU_BOX_WID-60, DpMNU_BOX_HEI, _cTTB_BG_MID, 	  DpFIG_FILL);

#endif


	// Item & Value - String
	switch(sct)
	{
		case MENU_SC0_MEAS:		DpMSR_StrCntts(sub);				break;
		case MENU_SC1_OUTP:		DpOUT_StrCntts();					break;
		case MENU_SC2_DATA:		DpDAT_StrCntts(sub);				break;
		// Not Use
		case MENU_SC3_SYST:		DpSY2_StrCntts(sub);					break;
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:				return;
	}
}

void DpM1_IntroSub(void)
{
	DpM1_UpdatSub();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L0 (Section)
//------------------------------------------------------------------------------------------------------------------------------
void DpM0_StdBySct(void)
{

}

void DpM0_IntroSct(void)
{
	U08 i, n,idx;
	U16 box_x0 = DpMNU_BOX_X0_SCT;
	U16 box_y0 = DpMNU_BOX_Y0;
	U16 str_x0 = DpMNU_STR_X0_SCT;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U32 col_st = _cMNU_STR_IDLE;
	U32 col_vl = _cTTB_BG_MID;
	U08 iSc = MENU_GetSection();
	U08 page;
	U08 iN;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	// Window
	DISP_IntroMenu();
	// Background
	DpFIG_DrwRect(DpMNU_BOX_X0_SCT, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cMNU_BOX_BG,  DpFIG_FILL);
	DpFIG_DrwRect(DpMNU_BOX_X0_SCT, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cMNU_BOX_BG,  DpFIG_FILL);

	// Check Hidden

	switch(MENU_GetFgHiddn())
	{
		case MENU_HIDDEN_IDLE:	n = MENU_SC3_SYST+1;	break;
		case MENU_HIDDEN_ENGR:	n = MENU_SC4_EGNR+1;	break;
		case MENU_HIDDEN_FCTR:	n = MENU_SCN_NUM;		break;
	}

	if 	(iSc >= (DpMNU_ITM_PAGE*1))			page = DpMNU_PG_1;
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
		default:			return;
	}


	switch(lang)
	{
		case MnSYS_LANG_ENG:
			for(i=0; i<iN; i++)
			{
				idx = i+(DpMNU_ITM_PAGE*page);
				if(idx >= MENU_SC4_EGNR)
					col_st = _cSD_GRAY;
			
				DpSTR_GuiLeft(str_x0, str_y0+(str_yg*i), col_st, _cTTB_BG_MID, _fE17HsB, lMn_sSct[idx]);
			}
			break;
		case MnSYS_LANG_KOR:
			for(i=0; i<iN; i++)
			{
				idx = i+(DpMNU_ITM_PAGE*page);
				if(idx >= MENU_SC4_EGNR)
					col_st = _cSD_GRAY;	
				
				switch(idx)
				{
					case MENU_SC0_MEAS:	DpSTR_GuiList(TEXT_LIST_MEASUREMENT);	break;
					case MENU_SC1_OUTP:	DpSTR_GuiList(TEXT_LIST_OUTPUT);		break;
					case MENU_SC2_DATA:	DpSTR_GuiList(TEXT_LIST_DATA);			break;
					case MENU_SC3_SYST: DpSTR_GuiList(TEXT_LIST_SYSTEM);		break;
					case MENU_SC4_EGNR: DpSTR_GuiList(TEXT_LIST_ENGINEER);	break;
					case MENU_SC5_FCTR: DpSTR_GuiList(TEXT_LIST_FACTORY);		break;
					case MENU_SC6_TEST: DpSTR_GuiList(TEXT_LIST_TEST_MENU);		break;
				}
			
				DpSTR_GuiLeft_KOR(str_x0, str_y0+(str_yg*i), col_st, _cTTB_BG_MID, _fE17HsBKOR, gDpStr.Text_list);				
			}
			break;
	}


	switch(page)
	{
		case DpMNU_PG_0:	
			idx = iSc;
			break;
		case DpMNU_PG_1:
			idx = iSc;
			iSc = iSc- DpMNU_ITM_PAGE;
			break;					
		default:			return;
	}


	// Section - Selection Box
	switch(lang)
	{
		case MnSYS_LANG_KOR:
			switch(idx)
			{
				case MENU_SC0_MEAS:	DpSTR_GuiList(TEXT_LIST_MEASUREMENT);	break;
				case MENU_SC1_OUTP:	DpSTR_GuiList(TEXT_LIST_OUTPUT);		break;
				case MENU_SC2_DATA:	DpSTR_GuiList(TEXT_LIST_DATA);			break;
				case MENU_SC3_SYST: DpSTR_GuiList(TEXT_LIST_SYSTEM);		break;
				case MENU_SC4_EGNR: DpSTR_GuiList(TEXT_LIST_ENGINEER);	break;
				case MENU_SC5_FCTR: DpSTR_GuiList(TEXT_LIST_FACTORY);		break;
				case MENU_SC6_TEST: DpSTR_GuiList(TEXT_LIST_TEST_MENU);		break;
			}			
			DpFIG_DrwRect(box_x0+10, box_y0+(str_yg*iSc)+15, DpMNU_BOX_WID-30, 40, _cMNU_SEL_SCT, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(str_x0,    str_y0+(str_yg*iSc),    _cSD_WHITE, _cMNU_SEL_SCT, _fE17HsBKOR,  gDpStr.Text_list);
			break;
		case MnSYS_LANG_ENG:
			DpFIG_DrwRect(box_x0+10, box_y0+(str_yg*iSc)+15, DpMNU_BOX_WID-30, 40, _cMNU_SEL_SCT, DpFIG_FILL);
			DpSTR_GuiLeft(str_x0,    str_y0+(str_yg*iSc),    _cSD_WHITE, _cMNU_SEL_SCT, _fE17HsB, lMn_sSct[idx]);
			break;			
	}

	switch(iSc)
	{
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA:		col_vl = _cSD_LIGHTBLACK;		break;
		case MENU_SC0_MEAS:
		case MENU_SC3_SYST:
		case MENU_SC4_EGNR:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
		default:				col_vl = _cMNU_BOX_BG;			break;
	}

#if 0
	switch(iSc)
	{
		case MENU_SC1_OUTP:
		case MENU_SC2_DATA: 
		case MENU_SC3_SYST:
		case MENU_SC5_FCTR:
		case MENU_SC6_TEST:
			DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			DpFIG_DrwRect(DpMNU_BOX_X0_VAL, DpMNU_BOX_Y0, DpMNU_BOX_WID, DpMNU_BOX_HEI, col_vl, 	  DpFIG_FILL);
			break;
		case MENU_SC0_MEAS:
		case MENU_SC4_EGNR:
			DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID+60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
			DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, DpMNU_BOX_Y0, DpMNU_BOX_WID-60, DpMNU_BOX_HEI, col_vl, 	  DpFIG_FILL);
			break;			
		default:
			break;
	}
#else
	DpFIG_DrwRect(DpMNU_BOX_X0_ITM, DpMNU_BOX_Y0, DpMNU_BOX_WID+60, DpMNU_BOX_HEI, _cTTB_BG_MID, DpFIG_FILL);
	DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, DpMNU_BOX_Y0, DpMNU_BOX_WID-60, DpMNU_BOX_HEI, col_vl,	  DpFIG_FILL);


#endif
	switch(idx)
	{
		case MENU_SC0_MEAS:		DpMSR_InitVari();		DpMS1_StrSbSct();		break;
		case MENU_SC1_OUTP:		DpOUT_InitVari();		DpOT1_StrSbSct();		break;
		case MENU_SC2_DATA:		DpDAT_InitVari();		DpDT1_StrSbSct();		break;
		case MENU_SC3_SYST:		DpSYS_InitVari();		DpSY1_StrSbSct();		break;
		case MENU_SC4_EGNR:		DpEGN_InitVari();		DpEG2_StrCntts();		break;
		case MENU_SC5_FCTR:		DpFTR_InitVari();		DpFT2_StrCntts();		break;
		case MENU_SC6_TEST:		DpTST_InitVari();		DpTS2_StrCntts();		break;
		default:				break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpMN_InitMain(void)
{
	DpMSR_InitVari();
	DpOUT_InitVari();
	DpDAT_InitVari();
	DpSYS_InitVari();
	// Special Menu
	DpEGN_InitVari();
	DpFTR_InitVari();
	DpTST_InitVari();

	_SPRINTF(lMn_sSct[MENU_SC0_MEAS], _sMeas);
	_SPRINTF(lMn_sSct[MENU_SC1_OUTP], _sOutp);
	_SPRINTF(lMn_sSct[MENU_SC2_DATA], _sData);
	_SPRINTF(lMn_sSct[MENU_SC3_SYST], _sSyst);
	_SPRINTF(lMn_sSct[MENU_SC4_EGNR], _sEgnr);
	_SPRINTF(lMn_sSct[MENU_SC5_FCTR], _sFctr);
	_SPRINTF(lMn_sSct[MENU_SC6_TEST], _sTest);	
}

void DpMN_UpdtBttn(U08 lyr)
{
	DpSCR_LnHrBttn();

	switch(lyr)
	{
		case MENU_L0_SECTION:
			DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_UP__);
			DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_DOWN);
			DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
			DpBTN_UdtArrow(DpBTN_I3_ENTR, DpBTN_NEXT_RIGH);
			break;

		case MENU_L2_ITEM:
			DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_UP__);
			DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_DOWN);
			DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_BACK, 10);
			DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SET,  20);
			break;

		case MENU_L3_VALUE:
			switch(MnLY3_GetUpdnMod())
			{
				case MENU_V3_UPDN_IDLE:
					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
					DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);
					DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
					DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SAVE,  20);				
					break;							
				case MENU_V3_UPDN_DIG_VALUE:
					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
					DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);
					DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_BACK, 18);
					DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SAVE,  20);				
					break;		
				case MENU_V3_UPDN_DIG:		
					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_LEFT);
					DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_RIGH);
					DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
					DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SET,  20);				
					break;					
				default:
					break;
			}
			break;
		case MENU_L4_ADDITION:
			switch(MENU_GetSection())
			{
				case MENU_SC3_SYST:
					switch(MnLY2_GetIdxItem())
					{
						case MnSYS_OPT_TIME:
							DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
							DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);
							DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
							DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SAVE, 10);
							break;

						default:
							DpBTN_ClearBtn(DpBTN_I1_PREV);
							DpBTN_ClearBtn(DpBTN_I2_NEXT);
							DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
							//DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, _sOK,   25);
							break;
					}
					break;

				case MENU_SC0_MEAS:
				default:
					DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
					DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);
					DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
					DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SAVE,  20);				
					break;							
			}
			break;
	}
}


void DpMn_PopUpdat(void)
{
  U16 x0 = DpPOP_CT1_X0;
  U16 y0 = DpPOP_CT1_Y0;
  U16 y1 = DpPOP_CT2_Y0;
  U32 cBg = _cPOP_BG_WND;
  I08 pSt0[16] = {0, };

  U08 mode =MENU_GetPassMode();
  U16 val = MENU_GetPassVal();

  S32 dig = MENU_GetPassdig();
  S32 max  = 9999;

  DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
  DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);

  _SPRINTF(pSt0, "%04d",val);

  DpSTR_GuiLeftCursor(x0, y0, _cPOP_ST_VAL_SEL, _cMNU_SEL_SCT, cBg, (U08)log10(max)-dig, _fE22HsB, pSt0); 


  if(mode != PASS_UPDN_DIG_VALUE)
    return;
  DpFIG_DrwRect(x0, y1, 500, 30, cBg, DpFIG_FILL);  

  switch(dig)
  {
    case 4:  
      _SPRINTF(pSt0, "%d", (val/10000)%10);  DpSTR_GuiLeft(x0, y1, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
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

void DpMn_PopIntro(void)
{
	I08 pSt0[32] = {0, };
	U08 lang=  MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(DISP_WND_X0, DISP_WND_Y0, DISP_WND_WD, 3, _cBGD_SCRN, DpFIG_FILL);
	DpPOP_DrwIntro();

	switch(lang)
	{
		case MnSYS_LANG_KOR:	DpSTR_GuiList(TEXT_LIST_PASSCODE);	_SPRINTF(pSt0, gDpStr.Text_list);	break;	
		case MnSYS_LANG_ENG:	_SPRINTF(pSt0, _sPasscode);	break;
	}
	

	DpPOP_UdtTitle(pSt0);

	_SPRINTF(pSt0, "%d", 0);

	DpPOP_UdtRangeMin(pSt0);

	_SPRINTF(pSt0, "%d", 9999);

	DpPOP_UdtRangeMax(pSt0);
  


	switch(MENU_GetPassMode())
	{			
		case PASS_UPDN_DIG_VALUE:
			DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
			DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);
			DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_BACK, 18);
			DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SET,  20); 			
			break;		
		case PASS_UPDN_DIG:		
			DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_LEFT);
			DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_RIGH);
			DpBTN_UdtStrng(DpBTN_I0_MENU, DpBTN_STT_ACTV, TEXT_LIST_EXIT, 18);
			DpBTN_UdtStrng(DpBTN_I3_ENTR, DpBTN_STT_ACTV, TEXT_LIST_SET,  20);				
			break;					
		default:
			break;
	}


}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

