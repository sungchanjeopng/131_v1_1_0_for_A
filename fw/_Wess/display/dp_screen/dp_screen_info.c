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
#include "app_status.h"
// bsp
#include "bsp_adc.h"
// measure
#include "measure_calc.h"
// menu
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_system.h"
// screen
#include "screen_main.h"
#include "screen_echo.h"
#include "screen_info.h"
#include "screen_inf1_list.h"
#include "screen_inf2_value.h"
#include "screen_calib.h"
// display
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_popup.h"
#include "disp_button.h"
// disp - screen
#include "dp_screen_main.h"
#include "dp_screen_hybrid.h"
// self
#include "dp_screen_info.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpPRM_LS lDpInf;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Update
//------------------------------------------------------------------------------------------------------------------------------

void DpIfnLvl_StrChnl(void)
{
	I08 pSt0[128] = {0, };
	U16 site_name;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);

	U08 type = MnFTR_PrGet_SsChn();

	if(type == MnFTR_SS_SINGLE)	
		return;


	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(pSt0, _sCH_1);
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);	
			_SPRINTF(pSt0, _sCH_2); 
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_CH_1);
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	

		#if 0
			_SPRINTF(pSt0, "1");
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X0+70, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);
		#endif
			DpSTR_GuiList(TEXT_LIST_CH_2);
			DpFIG_DrwRect(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpFRT_LVL_CHNL_X1, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	

		#if 0
			_SPRINTF(pSt0, "2");
			DpSTR_GuiLeft(DpFRT_LVL_CHNL_X1+70, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);		
		#endif
			break;
	}


	//DpFIG_DrwRect(DpFRT_LVL_CHNL_X0, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	site_name = MnSYS_PrGet_site_name(APP_CH_1);	

	_SPRINTF(pSt0, "(%c%d%d)",site_name/100,(site_name%100)/10,(site_name%100)%10);
	
	DpFIG_DrwRect(DpFRT_LVL_CHNL_X0+90, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpFRT_LVL_CHNL_X0+90, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);

	site_name = MnSYS_PrGet_site_name(APP_CH_2);	
	
	_SPRINTF(pSt0, "(%c%d%d)",site_name/100,(site_name%100)/10,(site_name%100)%10);
	DpFIG_DrwRect(DpFRT_LVL_CHNL_X1+90, DpFRT_LVL_CHNL_Y0, DpFRT_LVL_CHNL_WD, DpFRT_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpFRT_LVL_CHNL_X1+90, DpFRT_LVL_CHNL_Y0, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, pSt0);	

}


void DpInfUdt_LstTitle(U08 iFn)
{
	U16 x0_tt = ScPRM_ST_X0_TTL;
	U16 x1_tt = ScPRM_ST_X1_TTL;		
	U16 y0 = ScINF_ST_Y0_TTL + (ScPRM_LIN_HT * iFn);		
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	U08 type = MnFTR_PrGet_SsChn();


	switch(lang)
	{
		case MnSYS_LANG_ENG:
			switch(iFn)
			{
				case ScINF_OPT_SINGLE_FREQ:
					_SPRINTF(lDpInf.pStr, _siNF_FREQ);
					break;			
				case ScINF_OPT_SINGLE_OFFSET:
					_SPRINTF(lDpInf.pStr, _siNF_Offset);
					break;	
				case ScINF_OPT_SINGLE_4_20mA:
					_SPRINTF(lDpInf.pStr, _sINF_4_20mA);
					break;	
				case ScINF_OPT_SINGLE_TVG:
					_SPRINTF(lDpInf.pStr, _sINF_TVG);
					break;				
				case ScINF_OPT_SINGLE_DAMP:
					_SPRINTF(lDpInf.pStr, _sINF_DAMP);
					break;				
			}
			
			switch(iFn)
			{
				case ScINF_OPT_SINGLE_FREQ: 	
				case ScINF_OPT_SINGLE_OFFSET:
				case ScINF_OPT_SINGLE_4_20mA:
				case ScINF_OPT_SINGLE_TVG:
				case ScINF_OPT_SINGLE_DAMP:
					DpSTR_GuiLeft(x0_tt, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE17HsB, lDpInf.pStr);
					if(type == MnFTR_SS_DUAL)	
						DpSTR_GuiLeft(x1_tt, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE17HsB, lDpInf.pStr);
					break;				
			}
			break;
		case MnSYS_LANG_KOR:
			switch(iFn)
			{
				case ScINF_OPT_SINGLE_FREQ:
					_SPRINTF(lDpInf.pStr, "(Hz)");
					DpSTR_GuiLeft(x0_tt+90, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
					if(type == MnFTR_SS_DUAL)	
						DpSTR_GuiLeft(x1_tt+90, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
					DpSTR_GuiList(TEXT_LIST_FREQ);
					break;			
				case ScINF_OPT_SINGLE_OFFSET:
					_SPRINTF(lDpInf.pStr, "(m)");
					DpSTR_GuiLeft(x0_tt+120, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
					if(type == MnFTR_SS_DUAL)	
						DpSTR_GuiLeft(x1_tt+120, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);					
					DpSTR_GuiList(TEXT_LIST_OFFSET);
					break;	
				case ScINF_OPT_SINGLE_4_20mA:
					_SPRINTF(lDpInf.pStr, _sINF_4_20mA);
					break;	
				case ScINF_OPT_SINGLE_TVG:
					_SPRINTF(lDpInf.pStr, _sINF_TVG);
					break;				
				case ScINF_OPT_SINGLE_DAMP:
					DpSTR_GuiList(TEXT_LIST_DAMPING);
					break;				
			}
			
			switch(iFn)
			{
				case ScINF_OPT_SINGLE_4_20mA:
				case ScINF_OPT_SINGLE_TVG:
					DpSTR_GuiLeft(x0_tt, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
					if(type == MnFTR_SS_DUAL)	
						DpSTR_GuiLeft(x1_tt, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
					break;
				case ScINF_OPT_SINGLE_FREQ: 	
				case ScINF_OPT_SINGLE_OFFSET:
				case ScINF_OPT_SINGLE_DAMP:
					DpSTR_GuiLeft_KOR(x0_tt, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
					if(type == MnFTR_SS_DUAL)	
						DpSTR_GuiLeft_KOR(x1_tt, y0, _cINF_ST_TITLE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
					break;				
			}
			break;
	}


}

void DpInfUdt_LstValue(U08 iFn)
{
	U16 x0[APP_CH_NUM], y0;
	U32 col = _cINF_ST_VALUE;
	U08 i;
	S32 val,val2;

	U08 type = MnFTR_PrGet_SsChn();


	
	if(iFn >= ScINF_OPT_SINGLE_FREQ)
	{
		x0[APP_CH_1] = ScPRM_ST_X0_VAL-30;
		x0[APP_CH_2] = ScPRM_ST_X1_VAL-30;
		y0 = ScINF_ST_Y0_TTL + (ScPRM_LIN_HT * iFn);
	}


	for(i=0; i<type+1; i++)
	{
		switch(iFn)
		{
			case ScINF_OPT_SINGLE_FREQ:
				switch(MnMSR_CalGet_Ch_Value(i, MnMS1_OPT_SINGLE_FREQ))	
				{
					case MnMS1_FREQ_130K:	_SPRINTF(lDpInf.pStr,": 130K");		break;
					case MnMS1_FREQ_160K:	_SPRINTF(lDpInf.pStr,": 160K");		break;
					case MnMS1_FREQ_270K:	_SPRINTF(lDpInf.pStr,": 270K");		break;
					case MnMS1_FREQ_380K:	_SPRINTF(lDpInf.pStr,": 380K");		break;
					default:
						break;
				}
				DpSTR_GuiLeft(x0[i], y0, col, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
				break;
			case ScINF_OPT_SINGLE_OFFSET:
				val = MnMSR_CalGet_Ch_Value(i, MnMS1_OPT_SINGLE_OFFSET);	
				if(val>=0)	_SPRINTF(lDpInf.pStr, ": %01d.%02d", (U16)(abs(val)/100), (U16)(abs(val)%100));
				else		_SPRINTF(lDpInf.pStr, ": -%01d.%02d", (U16)(abs(val)/100), (U16)(abs(val)%100));
				
				DpSTR_GuiLeft(x0[i], y0, col, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
				break;
			case ScINF_OPT_SINGLE_4_20mA:
				val = MnOUT_CurPrGet_CH_Value(i, MnOS0_OPT_SINGLE_SET_04mA);
				val2 = MnOUT_CurPrGet_CH_Value(i, MnOS0_OPT_SINGLE_SET_20mA);

				_SPRINTF(lDpInf.pStr, ": %2d.%02d / %2d.%02d", (U16)(val/100), (U16)(val%100) , (U16)(val2/100), (U16)(val2%100));
				DpSTR_GuiLeft(x0[i], y0, col, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
				break;	
			case ScINF_OPT_SINGLE_TVG:
				val = MnEGN_PrGet_CH_Item(i, MnEGN_OPT_SINGLE_TVG);
				_SPRINTF(lDpInf.pStr, ": %d", val);
				DpSTR_GuiLeft(x0[i], y0, col, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
				break;			
			case ScINF_OPT_SINGLE_DAMP:
				val = MnMSR_CalGet_Ch_Value(i, MnMS1_OPT_SINGLE_DAMPING);
				_SPRINTF(lDpInf.pStr, ": %d", val);
				DpSTR_GuiLeft(x0[i], y0, col, _cBGD_SCRN, _fE22HsB, lDpInf.pStr);
				break;				
		}
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Processor
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L2
//------------------------------------------------------------------------------------------------------------------------------
void DpIF2_ValUpdat(U08 fDp)
{
#if 0

	I08 sCtt[3][16] = {{0, }, };
	U16 y0[2] = {DpPOP_CT1_Y0, DpPOP_CT2_Y0};
	U08 iFn = ScIF1_GetIdxFunc();
	S32 val = ScIF2_GetValue();


	switch(iFn)
	{
		case ScINF_F01_TX_WAVE:
			switch(val)
			{
				case ScPRM_TX_CYC_SEC01:	_SPRINTF(lDpInf.pStr, "1  sec");				break;
				case ScPRM_TX_CYC_SEC02:	_SPRINTF(lDpInf.pStr, "2  sec");				break;
				case ScPRM_TX_CYC_SEC03:	_SPRINTF(lDpInf.pStr, "3  sec");				break;
				case ScPRM_TX_CYC_SEC05:	_SPRINTF(lDpInf.pStr, "5  sec");				break;
				case ScPRM_TX_CYC_SEC10:	_SPRINTF(lDpInf.pStr, "10  sec");				break;
				case ScPRM_TX_CYC_SEC30:	_SPRINTF(lDpInf.pStr, "30  sec");				break;
				case ScPRM_TX_CYC_SEC60:	_SPRINTF(lDpInf.pStr, "60  sec");				break;
				default:					_SPRINTF(lDpInf.pStr, "NG (%d)", (U16)val);		break;
			}
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[0], _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sCtt[0]);
			break;

		case ScINF_LST_NUM:
			_SPRINTF(sCtt[0], _sCh_1);
			_SPRINTF(sCtt[1], _sCh_2);
			break;
	}

	switch(iFn)
	{
		case ScINF_LST_NUM:
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[0],	 _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sCtt[0]);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[1],	 _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sCtt[1]);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[val], _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sCtt[val]);
			break;
	}
#endif
}

void DpIF2_ValIntro(void)
{
#if 0

	U08 iFn = ScIF1_GetIdxFunc();
	U08 iCh = ScINF_PrGet_Chnnl();
	
	// Pop-Up Window
	DpPOP_DrwIntro();

	// Button
	DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
	DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);


	// Title
	switch(iFn)
	{
		case ScINF_LST_NUM:			_SPRINTF(lDpInf.pStr, _sCHNNL);				break;
		default:					_SPRINTF(lDpInf.pStr, _sNG);				break;
	}
	DpPOP_UdtTitle(lDpInf.pStr);

	// Old Value
	switch(iFn)
	{
		case ScINF_F01_TX_WAVE:
			DpSTR_GuiLeft(DpPOP_UNT_X0, DpPOP_OLD_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, _sSec_);
			DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN,     _cPOP_BG_WND, _fE17HsB, _sMIN);
			DpSTR_GuiLeft(DpPOP_MAX_X0, DpPOP_MAX_Y0, _cPOP_ST_MAX,     _cPOP_BG_WND, _fE17HsB, _sMAX);
			DpPOP_UdtExpla(_sRpt_PrsKeep);
			break;

		case ScINF_LST_NUM:
			switch(iCh)
			{
				case ScINF_CH_0:			_SPRINTF(lDpInf.pStr, _sCh_1);				break;
				case ScINF_CH_1:			_SPRINTF(lDpInf.pStr, _sCh_2);				break;
				default:					_SPRINTF(lDpInf.pStr, "NG (%d)", iCh);		break;
			}
			DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_OLD_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, lDpInf.pStr);
			break;

		default:
			DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_OLD_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, _sNG);
			break;
	}
#endif
	DpIF2_ValUpdat(_F_T);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L1
//------------------------------------------------------------------------------------------------------------------------------
void DpIF1_LstUpdat(void)
{
	U16 aSl[DpSCR_SBX_aNUMB];
	U08 iFn = ScINF_OPT_NUM;

	if(MnFTR_PrGet_SsChn() != MnFTR_SS_DUAL)
		return;

	aSl[DpSCR_SBX_aX0] = lDpInf.sbx.aX0[iFn];
	aSl[DpSCR_SBX_aY0] = lDpInf.sbx.aY0[iFn];
	aSl[DpSCR_SBX_aWd] = lDpInf.sbx.aWd[iFn];
	aSl[DpSCR_SBX_aHt] = lDpInf.sbx.aHt[iFn];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();
}

void DpIF1_LstIntro(void)
{
	DpSCR_UpdtBttn(SCRN_L1_LIST);
	DpIF1_LstUpdat();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L0
//------------------------------------------------------------------------------------------------------------------------------
void DpIF0_FncStdBy(void)
{
	RTC_TM rtc = RTC_GetTime();

	_SPRINTF(lDpInf.pStr, "20%02d - %d - %d   %2d:%02d", rtc.year, rtc.month, rtc.day, rtc.hours, rtc.minutes);

	DpSTR_GuiLeft(ScPRM_ST_X0_TTL, 360, _cSD_ORANGE, _cBGD_SCRN, _fE17HsB, lDpInf.pStr);



#if 0
	if(iCh >= ScINF_CH_NUM)
	{
		_SPRINTF(lDpInf.pStr, _sNG);

		DpFIG_DrwRect(ScPRM_ST_X1_VAL, y04, 80, 30, _cINF_BOX_BG, DpFIG_FILL);
		DpSTR_GuiLeft(ScPRM_ST_X1_VAL, y04, _cECO_LVL_VALU, _cINF_BOX_BG, _fE22HsB, lDpInf.pStr);
		return;
	}
#endif
#if 0
	switch(ScHYB_PrGet_LvTyp())
	{
		case ScHYB_LVL_SLDG:	val = MsCAL_GetVl_RsltSldg(iCh,0);		break;
		case ScHYB_LVL_DIST:	val = MsCAL_GetVl_RsltDist(iCh,0);		break;
		default:				return;
	}
#endif

#if 0
	if(ScHYB_PrGet_Unit_() == ScHYB_UNIT_FEET)
		val = (U16)MsCAL_Meter2Feet(val);
		
	if(val >= 1000)		_SPRINTF(lDpInf.pStr, "%2d.%02d", val/100, val%100);
	else				_SPRINTF(lDpInf.pStr, "%1d.%02d", val/100, val%100);

	DpFIG_DrwRect(ScPRM_ST_X1_VAL, y04, 80, 30, _cINF_BOX_BG, DpFIG_FILL);
	DpSTR_GuiLeft(ScPRM_ST_X1_VAL, y04, _cECO_LVL_VALU, _cINF_BOX_BG, _fE22HsB, lDpInf.pStr);
#endif
}

void DpIF0_FncIntro(void)
{
	U08 i;
	// Title & Background
	DpTTB_UdtIntro(TEXT_LIST_PARAMETER_SCREEN, 280, _cTTB_ST_TITLE);
	DpFIG_DrwRect(0,  60, 799, 410, _cBGD_SCRN,   DpFIG_FILL);				  HAL_Delay(3);		// Clear
	// Center Vertical Line
	DpFIG_DrwLinV(405, 120, 240, _cSD_WHITE);


	DpIfnLvl_StrChnl();

	_SPRINTF(lDpInf.pStr, _APP_VERISON);

	DpSTR_GuiLeft(ScPRM_ST_X1_VAL+60, 360, _cSD_ORANGE, _cBGD_SCRN, _fE17HsB, lDpInf.pStr);

#if 0
	// Saperate Horizental Line
	for(i=0; i<5; i++)		DpFIG_DrwLinH(x0_t, ScPRM_LIN_Y0 + (ScPRM_LIN_HT * i), h_le, _cINF_LIN_H);
	for(i=0; i<5; i++)		DpFIG_DrwLinH(x1_t, ScPRM_LIN_Y0 + (ScPRM_LIN_HT * i), h_le, _cINF_LIN_H);
#endif
#if 0
	// FW Version
	DpSTR_GuiLeft(640, 335, _cSD_LIGHTGRAY, _cINF_BOX_BG, _fE17HsB, (I08*)_APP_VERISON);
#endif
	// Channel
#if 0
	if(MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL)
	{
		switch(ScINF_PrGet_Chnnl())
		{
			case ScHYB_CH_0:		_SPRINTF(lDpInf.pStr, _sCH_1);			break;
			case ScHYB_CH_1:		_SPRINTF(lDpInf.pStr, _sCH_2);			break;
			default:				_SPRINTF(lDpInf.pStr, _sNG);			break;
		}
		DpSTR_GuiLeft(ScPRM_ST_X1_TTL, y04t, _cINF_ST_TITLE, _cINF_BOX_BG, _fE17HsB, lDpInf.pStr);
	}
#endif
#if 0
	// Result - Title
	switch(ScHYB_PrGet_LvTyp())
	{
		case ScHYB_LVL_SLDG:		_SPRINTF(lDpInf.pStr, _sSludge);		break;
		case ScHYB_LVL_DIST:		_SPRINTF(lDpInf.pStr, _sDist);			break;
	}
	DpSTR_GuiLeft(ScPRM_ST_X1_TTL+70, y04t, _cECO_LVL_TITL, _cINF_BOX_BG, _fE17HsB, lDpInf.pStr);

	// Result - Unit
	switch(ScHYB_PrGet_Unit_())
	{
		case ScHYB_UNIT_METER:		_SPRINTF(lDpInf.pStr, "m");				break;
		case ScHYB_UNIT_FEET:		_SPRINTF(lDpInf.pStr, "ft");			break;
	}
	DpSTR_GuiLeft(ScPRM_ST_X1_UNT, y04t, _cECO_LVL_TITL, _cINF_BOX_BG, _fE17HsB, lDpInf.pStr);
#endif
	// Parameter List
	for(i=0; i<ScINF_OPT_SINGLE_NUM; i++)
	{
		DpInfUdt_LstTitle(i);
		DpInfUdt_LstValue(i);
	}

	// Button
	DpSCR_UpdtBttn(SCRN_L0_FUNC);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpINF_InitVari(void)
{
	U08 i;

	_MEMSET(lDpInf.pStr, 0, sizeof(lDpInf.pStr));
	_MEMSET(lDpInf.pStr2, 0, sizeof(lDpInf.pStr2));
	//-------------------------------------------------------------------------
	// Sel-Box Position (Single)
	//-------------------------------------------------------------------------
	for(i=0; i<ScINF_OPT_NUM; i++)
	{
		lDpInf.sbx.aX0[i] = DpPRM_SBX_L0_SB_X0;
		lDpInf.sbx.aY0[i] = DpPRM_SBX_L0_SB_Y0 + (ScPRM_LIN_HT * i);
		lDpInf.sbx.aWd[i] = DpPRM_SBX_Lx_SB_WD;
		lDpInf.sbx.aHt[i] = DpPRM_SBX_Lx_SB_HT;
	}

	//-------------------------------------------------------------------------
	// Sel-Box Position (Dual)
	//-------------------------------------------------------------------------
	lDpInf.sbx.aX0[ScINF_OPT_NUM] = DpPRM_SBX_L0_SB_X1;
	lDpInf.sbx.aY0[ScINF_OPT_NUM] = DpPRM_SBX_L0_SB_Y0 + (ScPRM_LIN_HT * 4);
	lDpInf.sbx.aWd[ScINF_OPT_NUM] = DpPRM_SBX_Lx_SB_WD-95;
	lDpInf.sbx.aHt[ScINF_OPT_NUM] = DpPRM_SBX_Lx_SB_HT;
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

