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
#include "app_sys.h"
// measure
#include "measure_calc.h"
#include "measure_temperature.h"
#include "measure_cal1_field0.h"
// display
#include "disp_main.h"
#include "disp_color.h"
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_titlebar.h"
#include "disp_button.h"
#include "disp_popup.h"
// menu
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_system.h"
#include "menu_engineer.h"
// screen
#include "screen_main.h"
#include "screen_hyb1_list.h"
#include "screen_hyb2_value.h"
// disp - screen
#include "dp_screen_main.h"
#include "dp_screen_front.h"
// self
#include "dp_screen_hybrid.h"
// function
#include "output_current.h"

#include "data_save.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
Dphyb_LS lDphyb;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Line
//------------------------------------------------------------------------------------------------------------------------------
void DphybLin_Hori0(void)
{
	#if 1
	DpFIG_DrwRect(15, 235+(2*0), 410, 2, _chyb_LN_H00, 0);
	DpFIG_DrwRect(15, 235+(2*1), 410, 2, _chyb_LN_H01, 0);
	DpFIG_DrwRect(15, 235+(2*2), 410, 2, _chyb_LN_H02, 0);
	#else
	DpFIG_DrwRect(15, 235+(2*0), 490, 2, _chyb_LN_H00, 0);
	DpFIG_DrwRect(15, 235+(2*1), 490, 2, _chyb_LN_H01, 0);
	DpFIG_DrwRect(15, 235+(2*2), 490, 2, _chyb_LN_H02, 0);
	#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Level
//------------------------------------------------------------------------------------------------------------------------------
void DphybLvl_FgrlIcon(void)
{
	DpFIG_DrwCirc(35, 108, 5,     _chyb_LVL_ICON, _F_T);
	DpFIG_DrwCirc(40, 88,  6,     _chyb_LVL_ICON, _F_T);
	DpFIG_DrwElli(55, 105, 10, 8, _chyb_LVL_ICON, _F_T);
}

void DphybText_StrValue(U08 type)
{
	I08 pSt0[32] = {0, };
	U08 i;
	U16 x0[APP_CH_NUM] = {Dphyb_LVL_VALU_X0,Dphyb_LVL_VALU_X1};
	U16 y0[MsCAL_THR_TYPE_NUM] = {Dphyb_LVL_VALU_Y0,Dphyb_LVL_VALU_Y1};
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);


	if(type == MnFTR_SS_DUAL)
	{
		for(i=0; i<APP_CH_NUM; i++)
		{
			switch(lang)
			{
				case MnSYS_LANG_ENG:
					_SPRINTF(pSt0, _sLight_level);	
					DpFIG_DrwRect(x0[i]-20, y0[0]-40, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft(x0[i]-20, y0[0]-40, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0);

					_SPRINTF(pSt0, _sHeavy_level);
				
					DpFIG_DrwRect(x0[i]-20, y0[1]-40, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft(x0[i]-20, y0[1]-40, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);			
					break;
				case MnSYS_LANG_KOR:
					DpSTR_GuiList(TEXT_LIST_LIGHT_LEVEL);
					DpFIG_DrwRect(x0[i]-20, y0[0]-40, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(x0[i]-20, y0[0]-40, _cLight_level, _cBGD_SCRN, _fE22HsBKOR,  gDpStr.Text_list);
					_SPRINTF(pSt0, "(m)");
					DpSTR_GuiLeft(x0[i]-20+145, y0[0]-40, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0);	

					DpSTR_GuiList(TEXT_LIST_HEAVY_LEVEL);
					DpFIG_DrwRect(x0[i]-20, y0[1]-40, 100, 30, _cBGD_SCRN, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(x0[i]-20, y0[1]-40, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR,  gDpStr.Text_list);	

					_SPRINTF(pSt0, "(m)");
					DpSTR_GuiLeft(x0[i]-20+145, y0[1]-40, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);	
					break;
				default:
					break;
			}
		}
	}
	else if (type == MnFTR_SS_SINGLE)
	{
		switch(lang)
		{
			case MnSYS_LANG_ENG:
				_SPRINTF(pSt0, _sLight_level);	
				DpFIG_DrwRect(x0[1]-70, y0[0]-100, 100, 30, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft(x0[1]-70, y0[0]-100, _cLight_level, _cBGD_SCRN, _fE22HsB, pSt0);
		
				_SPRINTF(pSt0, _sHeavy_level);
			
				DpFIG_DrwRect(x0[1]-70, y0[1]-60, 100, 30, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft(x0[1]-70, y0[1]-60, _cHeavy_level, _cBGD_SCRN, _fE22HsB, pSt0);			
				break;
			case MnSYS_LANG_KOR:
				DpSTR_GuiList(TEXT_LIST_LIGHT_LEVEL);
				DpFIG_DrwRect(x0[1]-70, y0[0]-100, 100, 30, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft_KOR(x0[1]-70, y0[0]-100, _cLight_level, _cBGD_SCRN, _fE22HsBKOR,  gDpStr.Text_list);
				_SPRINTF(pSt0, "(m)");
				DpSTR_GuiLeft(x0[1]-70+145, y0[0]-100, _cLight_level, _cBGD_SCRN, _fE22HsB, pSt0);	
		
				DpSTR_GuiList(TEXT_LIST_HEAVY_LEVEL);
				DpFIG_DrwRect(x0[1]-70, y0[1]-60, 100, 30, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft_KOR(x0[1]-70, y0[1]-60, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR,  gDpStr.Text_list);	
		
				_SPRINTF(pSt0, "(m)");
				DpSTR_GuiLeft(x0[1]-70+145, y0[1]-60, _cHeavy_level, _cBGD_SCRN, _fE22HsB, pSt0);	
				break;
			default:
				break;
		}

	}
}

void DphybLvl_StrValue(U08 type)
{
	U16 valu[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	I08 pSt0[32] = {0, };
	U08 i,j;
	U16 x0[APP_CH_NUM] = {Dphyb_LVL_VALU_X0,Dphyb_LVL_VALU_X1};
	U16 y0[MsCAL_THR_TYPE_NUM] = {Dphyb_LVL_VALU_Y0,Dphyb_LVL_VALU_Y1};
	U64 font[MsCAL_THR_TYPE_NUM] = {_cLight_level,_cHeavy_level};

	if(type == MnFTR_SS_DUAL)
	{
		for(i=0; i<APP_CH_NUM; i++)
		{
			for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
			{

				switch(MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_OPERATION))
				{		
					case MnMS0_OPERATION_DISTANCE:
						valu[i][j] = MsCAL_GetVl_RsltDist(i, j);
						break;
					case MnMS0_OPERATION_SLUDGE:
						valu[i][j] = MsCAL_GetVl_RsltSldg(i, j);
						break;
					default:	
						break;
				}

				if((MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON) && (MsCAL1_GetfDp_dtt(i)==TRUE))
				{
					valu[i][j] = MsCAL1_Getrst_Value_old(i, MsCAL_THR_HEAVY);
				}


				
				if(valu[i][j] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu[i][j]/100, valu[i][j]%100);
				else					_SPRINTF(pSt0, "%1d.%02d", valu[i][j]/100, valu[i][j]%100);

				DpFIG_DrwRect(x0[i], y0[j], 100, 50, _cBGD_SCRN, DpFIG_FILL);
				DpSTR_GuiLeft(x0[i], y0[j], font[j], _cBGD_SCRN, _fE35HsB, pSt0); 

			}
		}
	}
	else if (type == MnFTR_SS_SINGLE)
	{
		y0[0] -= 20;
		y0[1] += 20;
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			switch(MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_OPERATION))
			{
				case MnMS0_OPERATION_SLUDGE:	valu[APP_CH_1][j] = MsCAL_GetVl_RsltSldg(APP_CH_1, j);	break;
				case MnMS0_OPERATION_DISTANCE:	valu[APP_CH_1][j] = MsCAL_GetVl_RsltDist(APP_CH_1, j);	break;
				default:
					break;
			}
			
			if(valu[APP_CH_1][j] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu[APP_CH_1][j]/100, valu[APP_CH_1][j]%100);
			else							_SPRINTF(pSt0, "%1d.%02d", valu[APP_CH_1][j]/100, valu[APP_CH_1][j]%100);
		
			DpFIG_DrwRect(x0[1]-70, y0[j]-50, 200, 80, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(x0[1]-70, y0[j]-50, font[j], _cBGD_SCRN, _fE75HsB, pSt0); 
		
		}
	}

}

void DphybLvl_StrTitle(void)
{
#if 0
	I08 pSt0[16] = {0, };
	U16 x0 = Dphyb_LVL_TITL_X0;
	U16 y0 = Dphyb_LVL_TITL_Y0;
	U16 wd = Dphyb_LVL_TITL_WD;
	U16 ht = Dphyb_LVL_TITL_HT;

	if(ScHYB_PrGet_LvTyp() == ScHYB_LVL_SLDG)		_SPRINTF(pSt0, _sSludge);
	else											_SPRINTF(pSt0, _sDist);

	DpFIG_DrwRect(x0, y0, wd, ht, _cBGD_SCRN, DpFIG_FILL);		// Clear
	HAL_Delay(1);
	DpSTR_GuiLeft(x0, y0, _chyb_LVL_T_IDLE, _cBGD_SCRN, _fE35HsB, pSt0);
#endif
}

void DphybLvl_StrUnit(void)
{
#if 0
	I08 pSt0[16] = {0, };

	if(ScHYB_PrGet_Unit_() == ScHYB_UNIT_METER)		_SPRINTF(pSt0, "m");
	else											_SPRINTF(pSt0, "ft");
	DpFIG_DrwRect(Dphyb_LVL_UNIT_X0, Dphyb_LVL_UNIT_Y0, Dphyb_LVL_UNIT_WD, Dphyb_LVL_UNIT_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(Dphyb_LVL_UNIT_X0, Dphyb_LVL_UNIT_Y0, _chyb_LVL_T_IDLE, _cBGD_SCRN, _fE75HsB, pSt0);
#endif
}

void DphybLvl_StrChnl(void)
{
#if 0
	I08 pSt0[16] = {0, };

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE)
		return;

	switch(ScHYB_PrGet_Chnnl())
	{
		case ScHYB_CH_0:		_SPRINTF(pSt0, _sCH_1);		break;
		case ScHYB_CH_1:		_SPRINTF(pSt0, _sCH_2);		break;
	}

	DpFIG_DrwRect(Dphyb_LVL_CHNL_X0, Dphyb_LVL_CHNL_Y0, Dphyb_LVL_CHNL_WD, Dphyb_LVL_CHNL_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(Dphyb_LVL_CHNL_X0, Dphyb_LVL_CHNL_Y0, _chyb_LVL_VAL, _cBGD_SCRN, _fE22HsB, pSt0);
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Box
//------------------------------------------------------------------------------------------------------------------------------
void DphybBox_FgrIcon(void)
{
	U16 x0 = Dphyb_BX_LV_IC_X0;

	// Up
	DpFIG_DrwCirc(x0,   Dphyb_BX_LEVEL_Y0+12, 12, _chyb_BOX_ICN_BG, _F_T);
	DpFIG_DrwRect(x0-2, Dphyb_BX_LEVEL_Y0+5,  4,  14, _chyb_BOX_ICN_FG, DpFIG_FILL);
	DpFIG_DrwRect(x0-5, Dphyb_BX_LEVEL_Y0+4,  10, 2,  _chyb_BOX_ICN_FG, DpFIG_FILL);
	DpFIG_DrwRect(x0-5, Dphyb_BX_LEVEL_Y0+16, 10, 2,  _chyb_BOX_ICN_FG, DpFIG_FILL);
	// Dn
	DpFIG_DrwCirc(x0,   Dphyb_BX_CURRT_Y0+12, 12, _chyb_BOX_ICN_BG, _F_T);
	DpSTR_GuiLeft(x0-5, Dphyb_BX_CURRT_Y0+5, _chyb_BOX_ICN_FG, _chyb_BOX_ICN_BG, _fE12HsM, "A");
}

void DphybBox_StrTitle(void)
{
#if 0
	I08 pSt0[16] = {0, };
	I08 pSt1[16] = {0, };

	if(ScHYB_PrGet_LvTyp() == ScHYB_LVL_SLDG)		_SPRINTF(pSt0, _sDist);
	else											_SPRINTF(pSt0, _sSludge);
	_SPRINTF(pSt1, _sCurr);

	DpSTR_GuiLeft(Dphyb_BX_LV_TL_X0, Dphyb_BX_LEVEL_Y0, _chyb_BOX_ICN_FG, _cSD_BLACK, _fE17HsB, pSt0);
	DpSTR_GuiLeft(Dphyb_BX_CR_TL_X0, Dphyb_BX_CURRT_Y0, _chyb_BOX_ICN_FG, _cSD_BLACK, _fE17HsB, pSt1);
#endif
}

void DphybBox_StrL0Val(void)
{
#if 0
	U16 valu;
	I08 pSt0[32] = {0, };
	U08 iCh  = ScHYB_PrGet_Chnnl();
	U08 unit = ScHYB_PrGet_Unit_();

	switch(ScHYB_PrGet_LvTyp())
	{
		case ScHYB_LVL_SLDG:		valu = MsCAL_GetVl_RsltDist(iCh,0);		break;
		case ScHYB_LVL_DIST:		valu = MsCAL_GetVl_RsltSldg(iCh,0);		break;
		default:					return;
	}
	
	if(MnMSR_FieldAGet_Value(MnMS1_I00_FIELDA_RUN))
	{
		switch(ScHYB_PrGet_LvTyp())
		{
			case ScHYB_LVL_SLDG:		valu = _MAX(MsCAL_GetVl_RsltDist(ScHYB_CH_0,0),MsCAL_GetVl_RsltDist(ScHYB_CH_1,0));	break;
			case ScHYB_LVL_DIST:		valu = _MIN(MsCAL_GetVl_RsltSldg(ScHYB_CH_0,0),MsCAL_GetVl_RsltSldg(ScHYB_CH_1,0));	break;
			default:					return;
		}
	}

	if(valu == lDphyb.bx_lv)
		return;
	lDphyb.bx_lv = valu;
	
	if(unit == ScHYB_UNIT_FEET)
		valu = (U16)MsCAL_Meter2Feet(valu);
	
	if(valu >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu/100, valu%100);
	else				_SPRINTF(pSt0, "%1d.%02d", valu/100, valu%100);
	DpFIG_DrwRect(Dphyb_BX_LV_VL_X0, Dphyb_BX_LEVEL_Y0, 80, 35, _cSD_BLACK, 0); 		// Clear
	DpSTR_GuiLeft(Dphyb_BX_LV_VL_X0, Dphyb_BX_LEVEL_Y0, _chyb_BOX_STR, _cSD_BLACK, _fE17HsB, pSt0);
#endif
}

void DphybBox_StrL1Crr(void)
{
#if 0
	I08 pSt0[32] = {0, };
	U08 iCh = ScHYB_PrGet_Chnnl();
	U16 valu = OuCUR_GetOutp_Value(iCh);
	
	if(valu >= 1000)	_SPRINTF(pSt0, "%2d.%02d", valu/100, valu%100);
	else				_SPRINTF(pSt0, "%1d.%02d", valu/100, valu%100);

	DpFIG_DrwRect(Dphyb_BX_CR_VL_X0, Dphyb_BX_CURRT_Y0, 80, 35, _cSD_BLACK, 0); 		// Clear
	DpSTR_GuiLeft(Dphyb_BX_CR_VL_X0, Dphyb_BX_CURRT_Y0, _chyb_BOX_STR, _cSD_BLACK, _fE17HsB, pSt0);
#endif
}

void DphybBox_StrUnit(void)
{
#if 0
	U16 x0 = Dphyb_BX_LV_UN_X0;
	U08 unit = ScHYB_PrGet_Unit_();
	I08 *pUn = "m ";

	if(unit == lDphyb.unit)
		return;
	lDphyb.unit = unit;

	if(unit == ScHYB_UNIT_FEET)		pUn = "ft";
	else							pUn = "m ";

	DpFIG_DrwRect(x0, Dphyb_BX_LEVEL_Y0, 60, 			   35, 		   _cSD_BLACK, DpFIG_FILL);		// Clear
	DpSTR_GuiLeft(x0, Dphyb_BX_LEVEL_Y0, _chyb_BOX_ICN_FG, _cSD_BLACK, _fE17HsB,   pUn);

	pUn ="mA";
	DpFIG_DrwRect(x0, Dphyb_BX_CURRT_Y0, 60, 35, _cSD_BLACK, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(x0, Dphyb_BX_CURRT_Y0, _chyb_BOX_ICN_FG, _cSD_BLACK, _fE17HsB, pUn);
#endif
}

void DphybBox_StrTime(void)
{
#if 0
	I08 pSt0[32] = {0, };
	RTC_TM valu = RTC_GetTime();

	if(valu.minutes == lDphyb.time.minutes)
		return;
	lDphyb.time.minutes = valu.minutes;
	
	_SPRINTF(pSt0, "20%02d - %d - %d  %2d:%02d", valu.year, valu.month, valu.day, valu.hours, valu.minutes);
	DpFIG_DrwRect(Dphyb_BX_RTC_T_X0, Dphyb_BX_RTC_T_Y0, 250, 25, _cBGD_SCRN, 0);
	DpSTR_GuiLeft(Dphyb_BX_RTC_T_X0, Dphyb_BX_RTC_T_Y0, _chyb_TANK_VAL, _cBGD_SCRN, _fE17HsB, pSt0);
#endif
}

void DphybTnk_StrSsDep(void)
{
#if 0
	U16 val;
	I08 pSt0[16] = {0, };
	I08 pSt1[8]  = {0, };
	U08 unit = ScHYB_PrGet_Unit_();

	val = ScHYB_PrGet_Value(ScHYB_PrGet_Chnnl(), ScHYB_F02_S_DEP);

	if(unit == ScHYB_UNIT_FEET)
		val = (U16)MsCAL_Meter2Feet(val);

	if(val >= 1000)		_SPRINTF(pSt0, "%2d.%02d", val/100, val%100);
	else				_SPRINTF(pSt0, "%1d.%02d", val/100, val%100);

	if(unit == ScHYB_UNIT_METER)		_SPRINTF(pSt1, "m");
	else								_SPRINTF(pSt1, "ft");

	DpSTR_GuiLeft(Dphyb_S_DEP_VL_X0, Dphyb_S_DEP_VL_Y0, _cINF_ST_VALUE, _cBGD_SCRN, _fE17HsB, pSt0);
	DpSTR_GuiLeft(Dphyb_S_DEP_UN_X0, Dphyb_S_DEP_UN_Y0, _cSD_LIGHTGRAY, _cBGD_SCRN, _fE17HsB, pSt1);
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Tank
//------------------------------------------------------------------------------------------------------------------------------
void DphybTnk_Fgrinit_Dual(void)
{
	U16 x0b[APP_CH_NUM] = {Dphyb_TK_BDR_X0,Dphyb_TK_BDR_X1}; 
	U16 y0b = Dphyb_TK_BDR_Y0;
	U16 y1b, y2b;
	U16 wid = Dphyb_TK_BDR_WD;
	U16 hei = Dphyb_TK_BDR_HT;				// X Center
	U16 i,j;
	// Height
	U16 empty[APP_CH_NUM];
	U16 empty_y[APP_CH_NUM];
	I08 pSt0[16]  = {0, };
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);
	U16 site_name;

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



	DpFIG_DrwLinV(x0b[1]-65, y0b, hei, _cSD_WHITE);

	for(i=0; i<APP_CH_NUM; i++)
	{
		empty[i]   = MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_EMPTY);
		empty_y[i] = Dphyb_TK_BDR_HT;
	

		for(j=0; j<11; j++)
		{
			DpFIG_DrwLinH(x0b[i]-5, y0b+((Dphyb_TK_BDR_HT/10)*j), 5, _cSD_GRAY);
		}

		if(empty[i] >= 1000)	_SPRINTF(pSt0, "%2d.%02d", empty[i]/100, empty[i]%100);
		else					_SPRINTF(pSt0, "%1d.%02d", empty[i]/100, empty[i]%100);

	
		DpFIG_DrwRect(x0b[i]-50, y0b-5, 30, 25, _cBGD_SCRN, 0);
		DpSTR_GuiLeft(x0b[i]-50, y0b-5, _chyb_TANK_VAL, _cBGD_SCRN, _fE12HsM, pSt0); 

		_SPRINTF(pSt0, "%1d.%02d", (empty[i]/2)/100, (empty[i]/2)%100);
		
		DpFIG_DrwRect(x0b[i]-50, y0b+((Dphyb_TK_BDR_HT/10)*5)-7, 30, 25, _cBGD_SCRN, 0);
		DpSTR_GuiLeft(x0b[i]-50, y0b+((Dphyb_TK_BDR_HT/10)*5)-7, _chyb_TANK_VAL, _cBGD_SCRN, _fE12HsM, pSt0); 

		DpFIG_DrwRect(x0b[i]-50, y0b+Dphyb_TK_BDR_HT-8, 30, 25, _cBGD_SCRN, 0);
		DpSTR_GuiLeft(x0b[i]-50, y0b+Dphyb_TK_BDR_HT-8, _chyb_TANK_VAL, _cBGD_SCRN, _fE12HsM, "0.00"); 

		y1b = y0b;
		y2b = (empty_y[i]*8) / 100;
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_00_08, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*8) / 100);
		y2b = ((empty_y[i]*17) / 100) - ((empty_y[i]*8) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_08_17, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*17) / 100);
		y2b = ((empty_y[i]*26) / 100) - ((empty_y[i]*17) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_17_26, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*26) / 100);
		y2b = ((empty_y[i]*37) / 100) - ((empty_y[i]*26) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_26_37, DpFIG_FILL);
		
		
		y1b = y0b+ ((empty_y[i]*37) / 100);
		y2b = ((empty_y[i]*58) / 100) - ((empty_y[i]*37) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_37_58, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*58) / 100);
		y2b = ((empty_y[i]*65) / 100) - ((empty_y[i]*58) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_58_65, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*65) / 100);
		y2b = ((empty_y[i]*100) / 100) - ((empty_y[i]*65) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_65_100, DpFIG_FILL);
	}
}


void DphybTnk_Fgrinit_Single(void)
{
	U16 x0b = Dphyb_TK_BDR_X0+30;
	U16 y0b = Dphyb_TK_BDR_Y0;
	U16 y1b, y2b;
	U16 wid = Dphyb_TK_BDR_WD*3;
	U16 hei = Dphyb_TK_BDR_HT;				// X Center
	// Height
	U16 empty;
	U16 empty_y;
	I08 pSt0[16]  = {0, };
	U08 j;

	DpFIG_DrwLinV(500, y0b-40, hei+50, _cSD_WHITE);

	empty   = MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_EMPTY);
	empty_y = Dphyb_TK_BDR_HT;


	for(j=0; j<11; j++)
	{
		DpFIG_DrwLinH(x0b-5, y0b+((Dphyb_TK_BDR_HT/10)*j), 5, _cSD_GRAY);
	}

	if(empty >= 1000)		_SPRINTF(pSt0, "%2d.%02d", empty/100, empty%100);
	else					_SPRINTF(pSt0, "%1d.%02d", empty/100, empty%100);


	DpFIG_DrwRect(x0b-50, y0b-5, 30, 25, _cBGD_SCRN, 0);
	DpSTR_GuiLeft(x0b-50, y0b-5, _chyb_TANK_VAL, _cBGD_SCRN, _fE12HsM, pSt0); 

	_SPRINTF(pSt0, "%1d.%02d", (empty/2)/100, (empty/2)%100);
	
	DpFIG_DrwRect(x0b-50, y0b+((Dphyb_TK_BDR_HT/10)*5)-7, 30, 25, _cBGD_SCRN, 0);
	DpSTR_GuiLeft(x0b-50, y0b+((Dphyb_TK_BDR_HT/10)*5)-7, _chyb_TANK_VAL, _cBGD_SCRN, _fE12HsM, pSt0); 

	DpFIG_DrwRect(x0b-50, y0b+Dphyb_TK_BDR_HT-8, 30, 25, _cBGD_SCRN, 0);
	DpSTR_GuiLeft(x0b-50, y0b+Dphyb_TK_BDR_HT-8, _chyb_TANK_VAL, _cBGD_SCRN, _fE12HsM, "0.00"); 

	y1b = y0b;
	y2b = (empty_y*8) / 100;
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_00_08, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*8) / 100);
	y2b = ((empty_y*17) / 100) - ((empty_y*8) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_08_17, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*17) / 100);
	y2b = ((empty_y*26) / 100) - ((empty_y*17) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_17_26, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*26) / 100);
	y2b = ((empty_y*37) / 100) - ((empty_y*26) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_26_37, DpFIG_FILL);
	
	
	y1b = y0b+ ((empty_y*37) / 100);
	y2b = ((empty_y*58) / 100) - ((empty_y*37) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_37_58, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*58) / 100);
	y2b = ((empty_y*65) / 100) - ((empty_y*58) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_58_65, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*65) / 100);
	y2b = ((empty_y*100) / 100) - ((empty_y*65) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_65_100, DpFIG_FILL);


}

void DphybTnk_FgrSingle(void)
{
	U16 x0b = Dphyb_TK_BDR_X0+30; 
	U16 y0b = Dphyb_TK_BDR_Y0;
	U16 y1b, y2b;
	U16 wid = Dphyb_TK_BDR_WD*3;
	U16 hei = Dphyb_TK_BDR_HT;				// X Center
	U16 j;
	
	// Height
	U16 dist[MsCAL_THR_TYPE_NUM];
	U16 dist_y[MsCAL_THR_TYPE_NUM];
	U16 sludge_y[MsCAL_THR_TYPE_NUM];
	U16 sludge_range;
	U16 dead;
	U16 dead_y;	
	U16 empty;
	U16 empty_y;

	U32 font[MsCAL_THR_TYPE_NUM] = {_cLight_level,_cHeavy_level};
	

	empty   = MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_EMPTY);
	empty_y = Dphyb_TK_BDR_HT-2;
	
	y1b = y0b;
	y2b = (empty_y*8) / 100;
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_00_08, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*8) / 100);
	y2b = ((empty_y*17) / 100) - ((empty_y*8) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_08_17, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*17) / 100);
	y2b = ((empty_y*26) / 100) - ((empty_y*17) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_17_26, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*26) / 100);
	y2b = ((empty_y*37) / 100) - ((empty_y*26) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_26_37, DpFIG_FILL);
	
	
	y1b = y0b+ ((empty_y*37) / 100);
	y2b = ((empty_y*58) / 100) - ((empty_y*37) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_37_58, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*58) / 100);
	y2b = ((empty_y*65) / 100) - ((empty_y*58) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_58_65, DpFIG_FILL);
	
	y1b = y0b+ ((empty_y*65) / 100);
	y2b = ((empty_y*100) / 100) - ((empty_y*65) / 100);
	DpFIG_DrwRect(x0b, y1b, wid, y2b, _chyb_WAT_65_100, DpFIG_FILL);


	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		dist[j]     = MsCAL_GetVl_RsltDist(APP_CH_1,j);
		if(dist[j] > empty) 
			dist[j] = empty;
		
		dist_y[j]   = ((dist[j] * (Dphyb_TK_BDR_HT))/empty);
		sludge_y[j] = Dphyb_TK_BDR_HT - dist_y[j];
	}
	
	sludge_range = abs(sludge_y[MsCAL_THR_LIGHT] - sludge_y[MsCAL_THR_HEAVY]);
	// Top Water

	if(dist_y[MsCAL_THR_LIGHT] <= dist_y[MsCAL_THR_HEAVY])
	{		
		y1b = y0b + dist_y[MsCAL_THR_LIGHT];
		if(sludge_y[MsCAL_THR_LIGHT]>0)
			DpFIG_DrwRect(x0b, y1b, wid, sludge_y[MsCAL_THR_LIGHT], _chyb_SLG_BSS,  DpFIG_FILL);	
		if(sludge_range>0)
		{
			DpFIG_DrwRect(x0b, y1b, wid, sludge_range, _cSD_WHITE,  DpFIG_FILL);
			DpFIG_DrwRect(x0b, y1b, wid, sludge_range, _chyb_SLG_TRANS,  DpFIG_FILL);
		}
	
	}
	else
	{			
		y1b = y0b + dist_y[MsCAL_THR_HEAVY];
		if(sludge_y[MsCAL_THR_HEAVY]>0)
			DpFIG_DrwRect(x0b, y1b, wid, sludge_y[MsCAL_THR_HEAVY], _chyb_SLG_BSS,  DpFIG_FILL);	
		if(sludge_range>0)
			DpFIG_DrwRect(x0b, y1b, wid, sludge_range, _chyb_SLG_TRANS,  DpFIG_FILL);
	}

	DpFIG_DrwRect(x0b+wid+10, y0b, 33, hei+20, _cBGD_SCRN,	DpFIG_FILL);	

	if(abs(dist_y[MsCAL_THR_LIGHT]-dist_y[MsCAL_THR_HEAVY])<30)
	{	
		DpSTR_GuiLeft(x0b+wid+27, y0b+dist_y[MsCAL_THR_HEAVY]-5, font[MsCAL_THR_HEAVY], _cBGD_SCRN, _fE12HsM, "H"); 
		DpSTR_GuiLeft(x0b+wid+27, y0b+dist_y[MsCAL_THR_HEAVY]-5, font[MsCAL_THR_HEAVY], _cBGD_SCRN, _fE12HsM, "H");
		DpSTR_GuiLeft(x0b+wid+15, y0b+dist_y[MsCAL_THR_LIGHT]-5, font[MsCAL_THR_LIGHT], _cBGD_SCRN, _fE12HsM, "L");
	}
	else
	{	
		DpSTR_GuiLeft(x0b+wid+15, y0b+dist_y[MsCAL_THR_LIGHT]-5, font[MsCAL_THR_LIGHT], _cBGD_SCRN, _fE12HsM, "L"); 
		DpSTR_GuiLeft(x0b+wid+15, y0b+dist_y[MsCAL_THR_HEAVY]-5, font[MsCAL_THR_HEAVY], _cBGD_SCRN, _fE12HsM, "H");
	}

	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		DpFIG_DrwLinH(x0b, y0b+dist_y[j], wid, font[j]);

	dead    = MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_DEADZONE);
	dead_y  = ((dead*Dphyb_TK_BDR_HT)/empty);
	DpFIG_DrwLinH(x0b, y0b+dead_y, wid, _cSD_DARKBLUE);		
	
}




void DphybTnk_FgrDual(void)
{
	U16 x0b[APP_CH_NUM] = {Dphyb_TK_BDR_X0,Dphyb_TK_BDR_X1}; 
	U16 y0b = Dphyb_TK_BDR_Y0;
	U16 y1b, y2b;
	U16 wid = Dphyb_TK_BDR_WD;
	U16 hei = Dphyb_TK_BDR_HT;				// X Center
	U16 i,j;
	
	// Height
	U16 dist[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 dist_y[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 sludge_y[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 sludge_range[APP_CH_NUM];
	U16 dead[APP_CH_NUM];
	U16 dead_y[APP_CH_NUM];	
	U16 empty[APP_CH_NUM];
	U16 empty_y[APP_CH_NUM];

	U32 font[MsCAL_THR_TYPE_NUM] = {_cLight_level,_cHeavy_level};
	
	for(i=0; i<APP_CH_NUM; i++)
	{
		empty[i]   = MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_EMPTY);
		empty_y[i] = Dphyb_TK_BDR_HT-2;
		
		y1b = y0b;
		y2b = (empty_y[i]*8) / 100;
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_00_08, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*8) / 100);
		y2b = ((empty_y[i]*17) / 100) - ((empty_y[i]*8) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_08_17, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*17) / 100);
		y2b = ((empty_y[i]*26) / 100) - ((empty_y[i]*17) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_17_26, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*26) / 100);
		y2b = ((empty_y[i]*37) / 100) - ((empty_y[i]*26) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_26_37, DpFIG_FILL);
		
		
		y1b = y0b+ ((empty_y[i]*37) / 100);
		y2b = ((empty_y[i]*58) / 100) - ((empty_y[i]*37) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_37_58, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*58) / 100);
		y2b = ((empty_y[i]*65) / 100) - ((empty_y[i]*58) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_58_65, DpFIG_FILL);
		
		y1b = y0b+ ((empty_y[i]*65) / 100);
		y2b = ((empty_y[i]*100) / 100) - ((empty_y[i]*65) / 100);
		DpFIG_DrwRect(x0b[i], y1b, wid, y2b, _chyb_WAT_65_100, DpFIG_FILL);

	
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			dist[i][j]     = MsCAL_GetVl_RsltDist(i,j);
			if(dist[i][j] > empty[i]) 
				dist[i][j] = empty[i];

			dist_y[i][j]   = ((dist[i][j] * (Dphyb_TK_BDR_HT))/empty[i]);
			sludge_y[i][j] = Dphyb_TK_BDR_HT - dist_y[i][j];
		}
		sludge_range[i] = abs(sludge_y[i][MsCAL_THR_LIGHT] - sludge_y[i][MsCAL_THR_HEAVY]);
		// Top Water

		if(dist_y[i][MsCAL_THR_LIGHT] <= dist_y[i][MsCAL_THR_HEAVY])
		{		
			y1b = y0b + dist_y[i][MsCAL_THR_LIGHT];
			if(sludge_y[i][MsCAL_THR_LIGHT]>0)
				DpFIG_DrwRect(x0b[i], y1b, wid, sludge_y[i][MsCAL_THR_LIGHT], _chyb_SLG_BSS,  DpFIG_FILL);	
			if(sludge_range[i]>0)
			{
				DpFIG_DrwRect(x0b[i], y1b, wid, sludge_range[i], _cSD_WHITE,  DpFIG_FILL);
				DpFIG_DrwRect(x0b[i], y1b, wid, sludge_range[i], _chyb_SLG_TRANS,  DpFIG_FILL);
			}
		
		}
		else
		{			
			y1b = y0b + dist_y[i][MsCAL_THR_HEAVY];
			if(sludge_y[i][MsCAL_THR_HEAVY]>0)
				DpFIG_DrwRect(x0b[i], y1b, wid, sludge_y[i][MsCAL_THR_HEAVY], _chyb_SLG_BSS,  DpFIG_FILL);	
			if(sludge_range[i]>0)
				DpFIG_DrwRect(x0b[i], y1b, wid, sludge_range[i], _chyb_SLG_TRANS,  DpFIG_FILL);
		}

		DpFIG_DrwRect(x0b[i]+wid+10, y0b, 33, hei+20, _cBGD_SCRN,	DpFIG_FILL);	

		if(abs(dist_y[i][MsCAL_THR_LIGHT]-dist_y[i][MsCAL_THR_HEAVY])<30)
		{	
			DpSTR_GuiLeft(x0b[i]+wid+27, y0b+dist_y[i][MsCAL_THR_HEAVY]-5, font[MsCAL_THR_HEAVY], _cBGD_SCRN, _fE12HsM, "H"); 
			DpSTR_GuiLeft(x0b[i]+wid+27, y0b+dist_y[i][MsCAL_THR_HEAVY]-5, font[MsCAL_THR_HEAVY], _cBGD_SCRN, _fE12HsM, "H");
			DpSTR_GuiLeft(x0b[i]+wid+15, y0b+dist_y[i][MsCAL_THR_LIGHT]-5, font[MsCAL_THR_LIGHT], _cBGD_SCRN, _fE12HsM, "L");
		}
		else
		{	
			DpSTR_GuiLeft(x0b[i]+wid+15, y0b+dist_y[i][MsCAL_THR_LIGHT]-5, font[MsCAL_THR_LIGHT], _cBGD_SCRN, _fE12HsM, "L"); 
			DpSTR_GuiLeft(x0b[i]+wid+15, y0b+dist_y[i][MsCAL_THR_HEAVY]-5, font[MsCAL_THR_HEAVY], _cBGD_SCRN, _fE12HsM, "H");
		}

		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
			DpFIG_DrwLinH(x0b[i], y0b+dist_y[i][j], wid, font[j]);

		dead[i]    = MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_DEADZONE);
		dead_y[i]  = ((dead[i]*Dphyb_TK_BDR_HT)/empty[i]);
		DpFIG_DrwLinH(x0b[i], y0b+dead_y[i], wid, _cSD_DARKBLUE);		
	}
	
}


void DphybTnk_LstFieldAdir(void)
{
#if 0

#endif
}

void DphybTnk_StrFsLoc(void)
{
#if 0

#endif
}

void DphybTnk_StrFsDir(void)
{
#if 0
	I08 pSt0[32] = {0, };
	_SPRINTF(pSt0, "      ");
	DpFIG_DrwRect(Dphyb_FS_DIR_VL_X0-20, Dphyb_FS_DIR_VL_Y0, 70, 15, _cBGD_SCRN, DpFIG_FILL);
	switch(MsCAL1_Getrst_dir())
	{
		case CAL1_DIRE_NONE:		_SPRINTF(pSt0, "-");										break;
		case CAL1_DIRE_CH_1TO0:		_SPRINTF(pSt0, _sCh_1TO0);									break;
		case CAL1_DIRE_CH_0TO1: 	_SPRINTF(pSt0, _sCh_0TO1);									 break;
		default:																				break;
	}	
	DpSTR_GuiLeft(Dphyb_FS_DIR_VL_X0-25, Dphyb_FS_DIR_VL_Y0, _cINF_ST_VALUE, _cBGD_SCRN, _fE12HsM, pSt0);
#endif
}

void DphybTnk_StrFsVel(void)
{
#if 0
	I08 pSt0[8]  = {0, };
	U16 val = MsCAL1_Getrst_vel();	
	U16 x0b = Dphyb_FS_VEL_VL_X0-20;

	DpFIG_DrwRect(Dphyb_FS_VEL_VL_X0-20, Dphyb_FS_VEL_VL_Y0, 70, 15, _cBGD_SCRN, DpFIG_FILL);
	if(!MsCAL1_GetfDp_cyc())   	_SPRINTF(pSt0, " -");	
	else							
	{
		_SPRINTF(pSt0, "%2d.%02d", val/100, val%100); 
		x0b = Dphyb_FS_VEL_VL_X0-30;
	}

	DpSTR_GuiLeft(x0b, Dphyb_FS_VEL_VL_Y0, _cINF_ST_VALUE, _cBGD_SCRN, _fE12HsM, pSt0);
	_SPRINTF(pSt0, "m/min");
	DpSTR_GuiLeft(Dphyb_FS_VEL_VL_X0+20, Dphyb_FS_VEL_VL_Y0, _cINF_ST_VALUE, _cBGD_SCRN, _fE12HsM, pSt0);
#endif
}


void DphybTnk_StrDeadz(void)
{
#if 0
	U16 val;
	I08 pSt0[16] = {0, };
	I08 pSt1[8]  = {0, };
	U08 unit = ScHYB_PrGet_Unit_();

	val = (U16)ScHYB_PrGet_Value(ScHYB_PrGet_Chnnl(), ScHYB_F03_DEADZ);

	if(unit == ScHYB_UNIT_FEET)
		val = (U16)MsCAL_Meter2Feet(val);

	if(val >= 1000)		_SPRINTF(pSt0, "%2d.%02d", val/100, val%100);
	else				_SPRINTF(pSt0, "%1d.%02d", val/100, val%100);

	if(unit == ScHYB_UNIT_METER)		_SPRINTF(pSt1, "m");
	else								_SPRINTF(pSt1, "ft");

	DpSTR_GuiLeft(Dphyb_DEADZ_VL_X0, Dphyb_DEADZ_VL_Y0, _cINF_ST_VALUE, _cBGD_SCRN, _fE17HsB, pSt0);
	DpSTR_GuiLeft(Dphyb_DEADZ_UN_X0, Dphyb_DEADZ_UN_Y0, _cSD_LIGHTGRAY, _cBGD_SCRN, _fE17HsB, pSt1);
#endif
}



void DphybTnk_StrDepth(void)
{
#if 0
	U16 val;
	I08 pSt0[16] = {0, };
	I08 pSt1[8]  = {0, };
	U08 unit = ScHYB_PrGet_Unit_();

	val = (U16)ScHYB_PrGet_Value(ScHYB_PrGet_Chnnl(), ScHYB_F04_T_DEP);

	if(unit == ScHYB_UNIT_FEET)
		val = (U16)MsCAL_Meter2Feet(val);

	if(val >= 1000)		_SPRINTF(pSt0, "%2d.%02d", val/100, val%100);
	else				_SPRINTF(pSt0, "%1d.%02d", val/100, val%100);

	if(unit == ScHYB_UNIT_METER)		_SPRINTF(pSt1, "m");
	else								_SPRINTF(pSt1, "ft");

	DpSTR_GuiLeft(Dphyb_T_DEP_VL_X0, Dphyb_T_DEP_VL_Y0, _cINF_ST_VALUE, _cBGD_SCRN, _fE17HsB, pSt0);
	DpSTR_GuiLeft(Dphyb_T_DEP_UN_X0, Dphyb_T_DEP_UN_Y0, _cSD_LIGHTGRAY, _cBGD_SCRN, _fE17HsB, pSt1);
#endif
}

void DphybUdt_TankTprt(U08 type)
{
#if 1
	S16 val;
	I08 pSt0[16] = {0, };
	U16 x0[APP_CH_NUM] = {Dphyb_TPRT_VL_X0,Dphyb_TPRT_VL_X1};
	U08 i;

	if(type == MnFTR_SS_DUAL)
	{
		for(i=0; i<APP_CH_NUM; i++)
		{
			val = MsTPR_GetTprt(i);

			if(val>=0)
			{
				if(val >= 100)	_SPRINTF(pSt0, "%2d.%d'C", val/10, abs(val%10));
				else			_SPRINTF(pSt0, "%1d.%d'C", val/10, abs(val%10));		
			}
			else
			{
				if(abs(val) >= 100)	_SPRINTF(pSt0, "-%2d.%d'C", abs(val/10), abs(val%10));
				else				_SPRINTF(pSt0, "-%1d.%d'C", abs(val/10), abs(val%10));	
			}
			
			DpFIG_DrwRect(x0[i], Dphyb_TPRT_VL_Y0, 100, 18, _cBGD_SCRN, 0);		// Clear
			DpSTR_GuiLeft(x0[i], Dphyb_TPRT_VL_Y0, _cTprt, _cBGD_SCRN, _fE12HsM, pSt0);
			DpSTR_GuiLeft(x0[i], Dphyb_TPRT_VL_Y0, _cTprt, _cBGD_SCRN, _fE12HsM, pSt0);
		}
	}
	else if (type == MnFTR_SS_SINGLE)
	{
		val = MsTPR_GetTprt(APP_CH_1);
		
		if(val>=0)
		{
			if(val >= 100)	_SPRINTF(pSt0, "%2d.%d'C", val/10, abs(val%10));
			else			_SPRINTF(pSt0, "%1d.%d'C", val/10, abs(val%10));		
		}
		else
		{
			if(abs(val) >= 100) _SPRINTF(pSt0, "-%2d.%d'C", abs(val/10), abs(val%10));
			else				_SPRINTF(pSt0, "-%1d.%d'C", abs(val/10), abs(val%10));	
		}
		
		DpFIG_DrwRect(x0[APP_CH_1]+30, Dphyb_TPRT_VL_Y0, 100, 18, _cBGD_SCRN, 0); 	// Clear
		DpSTR_GuiLeft(x0[APP_CH_1]+30, Dphyb_TPRT_VL_Y0, _cTprt, _cBGD_SCRN, _fE12HsM, pSt0);
		DpSTR_GuiLeft(x0[APP_CH_1]+30, Dphyb_TPRT_VL_Y0, _cTprt, _cBGD_SCRN, _fE12HsM, pSt0);
	}
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-Up Window
//------------------------------------------------------------------------------------------------------------------------------
void DpHY2_ValUpdat(void)
{
#if 0
	S32 min, max;
	I08 sCtt[3][16] = {{0, }, };
	U16 y0[2] = {DpPOP_CT1_Y0, DpPOP_CT2_Y0};
	U32 cBg = _cPOP_BG_WND;
	U08 iFn = ScHY1_GetIdxFunc();
	S32 val = ScHY2_GetValue();
	U08 unit =ScHYB_PrGet_Unit_();
	S32 dig = ScHY2_GetUpdnDig();
	S32 updn_mod = ScHY2_GetUpdnMod();

	DpFIG_DrwRect(250, 175, 200, 45, _cPOP_BG_WND, 0); // Clear
	DpFIG_DrwRect(250, 235, 200, 45, _cPOP_BG_WND, 0); // Clear
	
	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		_SPRINTF(sCtt[0], _sSludge);	_SPRINTF(sCtt[1], _sDist);		break;
		case ScHYB_F01_UNIT_:		_SPRINTF(sCtt[0], _sMeter);		_SPRINTF(sCtt[1], _sFeet);		break;
		case ScHYB_F02_S_DEP:		min = ScHYB_SS_DEP_MIN;			max = ScHYB_SS_DEP_MAX;			break;
		case ScHYB_F03_DEADZ:		min = ScHYB_DEADZ_MIN;			max = ScHYB_DEADZ_MAX;			break;
		case ScHYB_F04_T_DEP:		min = ScHYB_TK_DEP_MIN;			max = ScHYB_TK_DEP_MAX;			break;
		case ScHYB_FNC_NUMB:		_SPRINTF(sCtt[0], _sCh_1);		_SPRINTF(sCtt[1], _sCh_2);		break;
	}
	if(unit == ScHYB_UNIT_FEET)
	{
		val = (U16)MsCAL_Meter2Feet(val);
		min = (U16)MsCAL_Meter2Feet(min);
		max = (U16)MsCAL_Meter2Feet(max);
	}

	switch(iFn)
	{
		case ScHYB_F00_LEVEL:
		case ScHYB_F01_UNIT_:
		case ScHYB_FNC_NUMB:
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[0],   _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sCtt[0]);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[1],   _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sCtt[1]);
			DpSTR_GuiLeft(DpPOP_CT1_X0, y0[val], _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, sCtt[val]);
			break;
		case ScHYB_F02_S_DEP:
			_SPRINTF(sCtt[0], "%d.%02d", (U16)val/100, (U16)val%100);
			_SPRINTF(sCtt[1], "%d.%02d", (U16)min/100, (U16)min%100);
			_SPRINTF(sCtt[2], "%d.%02d", (U16)max/100, (U16)max%100);
			DpSTR_GuiLeft(250, 175,   _cPOP_ST_VAL_SEL, cBg, _fE35HsB, sCtt[0]);
			DpSTR_GuiLeft(DpPOP_MIN_X0+67, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sCtt[1]);
			DpSTR_GuiLeft(DpPOP_MAX_X0+67, DpPOP_MAX_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sCtt[2]);			
			break;
		case ScHYB_F03_DEADZ:
			_SPRINTF(sCtt[0], "%01d.%02d", (U16)val/100, (U16)val%100);
			_SPRINTF(sCtt[1], "%d.%02d", (U16)min/100, (U16)min%100);
			_SPRINTF(sCtt[2], "%d.%02d", (U16)max/100, (U16)max%100);
			break;
		case ScHYB_F04_T_DEP:
			_SPRINTF(sCtt[0], "%02d.%02d", (U16)val/100, (U16)val%100);
			_SPRINTF(sCtt[1], "%d.%02d", (U16)min/100, (U16)min%100);
			_SPRINTF(sCtt[2], "%d.%02d", (U16)max/100, (U16)max%100);
			break;
	}

	switch(updn_mod)
	{
		case SCRN_L2_UPDN_IDLE: 		return;
		case SCRN_L2_UPDN_DIG:
		case SCRN_L2_UPDN_DIG_VALUE:    DpFIG_DrwRect(250, 175, 100, 38, _cPOP_BG_WND, 0);  DpSTR_GuiLeftCursor(250, 175, _cPOP_ST_VAL_SEL, _cMNU_SEL_SCT, cBg, (U08)log10(max)-dig, _fE35HsB, sCtt[0]); break;
		default:	break;
	}
	DpSTR_GuiLeft(DpPOP_MIN_X0+67, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sCtt[1]);
	DpSTR_GuiLeft(DpPOP_MAX_X0+67, DpPOP_MAX_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, sCtt[2]);

	if(ScHY2_GetUpdnMod() != SCRN_L2_UPDN_DIG_VALUE)
		return;

	switch(dig)
	{
		case 4:	
			_SPRINTF(sCtt[0], "%d", (val/10000)%10);	DpSTR_GuiLeft(250, 235, _cMNU_SEL_SCT, cBg, _fE35HsB, sCtt[0]);
			break;
		case 3:
			_SPRINTF(sCtt[0], "%d", (val/1000)%10); DpSTR_GuiLeft(250, 235, _cMNU_SEL_SCT, cBg, _fE35HsB, sCtt[0]);
			break;
		case 2:
			_SPRINTF(sCtt[0], "%d", (val/100)%10); DpSTR_GuiLeft(250, 235, _cMNU_SEL_SCT, cBg, _fE35HsB, sCtt[0]);
			break;
		case 1:
			_SPRINTF(sCtt[0], "%d", (val/10)%10); DpSTR_GuiLeft(250, 235, _cMNU_SEL_SCT, cBg, _fE35HsB, sCtt[0]);
			break;
		case 0:
			_SPRINTF(sCtt[0], "%d", val%10); DpSTR_GuiLeft(250, 235, _cMNU_SEL_SCT, cBg, _fE35HsB, sCtt[0]);
			break;
	}
#endif
}

void DpHY2_ValIntro(void)
{
#if 0
	U16 val;
	I08 sTit[16] = {0, };
	I08 sOld[16] = {0, };
	I08 sUnt[4]  = {0, };
	U08 iFn = ScHY1_GetIdxFunc();
	U08 unit =ScHYB_PrGet_Unit_();

	// Pop-Up Window
	DpPOP_DrwIntro();
	// Button
	DpBTN_UdtArrow(DpBTN_I1_PREV, DpBTN_PREV_DOWN);
	DpBTN_UdtArrow(DpBTN_I2_NEXT, DpBTN_NEXT_UP__);

	// Title
	switch(iFn)
	{
		case ScHYB_F00_LEVEL:		_SPRINTF(sTit, _sLEVEL);			break;
		case ScHYB_F01_UNIT_:		_SPRINTF(sTit, _sUNIT);				break;
		case ScHYB_F02_S_DEP:		_SPRINTF(sTit, _sSS_DEP);			break;
		case ScHYB_F03_DEADZ:		_SPRINTF(sTit, _sDEADZN);			break;
		case ScHYB_F04_T_DEP:		_SPRINTF(sTit, _sTK_DEP);			break;
		case ScHYB_FNC_NUMB:		_SPRINTF(sTit, _sCHNNL);			break;
		default:					_SPRINTF(sTit, _sNG);				break;
	}
	DpPOP_UdtTitle(sTit);

	// Contents
	switch(iFn)
	{
		case ScHYB_F02_S_DEP:		val = (U16)ScHYB_PrGet_Value(ScHYB_PrGet_Chnnl(), iFn);		break;
		case ScHYB_F03_DEADZ:		val = (U16)ScHYB_PrGet_Value(ScHYB_PrGet_Chnnl(), iFn);		break;
		case ScHYB_F04_T_DEP:		val = (U16)ScHYB_PrGet_Value(ScHYB_PrGet_Chnnl(), iFn);		break;

		case ScHYB_FNC_NUMB:
			switch(ScHYB_PrGet_Chnnl())
			{
				case ScHYB_CH_0:			_SPRINTF(sOld, _sCh_1);			break;
				case ScHYB_CH_1:			_SPRINTF(sOld, _sCh_2);			break;
				default:					_SPRINTF(sOld, _sNG);			break;
			}
			break;
	}

	if(unit == ScHYB_UNIT_FEET)
	{
		val = (U16)MsCAL_Meter2Feet(val);
	}

		
	// Old & Unit
	switch(iFn)
	{
		case ScHYB_F00_LEVEL:
			switch(ScHYB_PrGet_LvTyp())
			{
				case ScHYB_LVL_SLDG:		_SPRINTF(sOld, _sSludge);		break;
				case ScHYB_LVL_DIST:		_SPRINTF(sOld, _sDist);			break;
				default:					_SPRINTF(sOld, _sNG);			break;
			}
			DpPOP_UdtOldVl(sOld);
			break;
		case ScHYB_F01_UNIT_:
			switch(ScHYB_PrGet_Unit_())
			{
				case ScHYB_UNIT_METER:		_SPRINTF(sOld, _sMeter);		break;
				case ScHYB_UNIT_FEET:		_SPRINTF(sOld, _sFeet);			break;
				default:					_SPRINTF(sOld, _sNG);			break;
			}
			DpPOP_UdtOldVl(sOld);
			break;
		case ScHYB_F02_S_DEP:
		case ScHYB_F03_DEADZ:
		case ScHYB_F04_T_DEP:
			_SPRINTF(sOld, "%2d.%02d", (U16)(val/100), (U16)(val%100));
			DpPOP_UdtOldVl(sOld);
			switch(ScHYB_PrGet_Unit_())
			{
				case ScHYB_UNIT_METER:		_SPRINTF(sUnt, "m");			break;
				case ScHYB_UNIT_FEET:		_SPRINTF(sUnt, "ft");			break;
			}
			DpSTR_GuiLeft(DpPOP_UNT_X0, DpPOP_OLD_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sUnt);
			DpSTR_GuiLeft(DpPOP_UNT_X0, DpPOP_OLD_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, sUnt);
			
			DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN,  _cPOP_BG_WND, _fE17HsB, _sMIN);
			DpSTR_GuiLeft(DpPOP_MAX_X0, DpPOP_MAX_Y0, _cPOP_ST_MAX,  _cPOP_BG_WND, _fE17HsB, _sMAX);
			DpPOP_UdtExpla(_sRpt_PrsKeep);
			break;
	}
	// Value
	DpHY2_ValUpdat();
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L1
//------------------------------------------------------------------------------------------------------------------------------
void DpHY1_LstUpdat(void)
{
#if 0
	U08 i;
	U08 iFn = ScHY1_GetIdxFunc();
	U16 aSl[DpSCR_SBX_aNUMB];

	for(i=0; i<ScHYB_FNC_NUMB; i++)
		DpFIG_DrwRect(lDphyb.sbx.aX0[i], lDphyb.sbx.aY0[i], lDphyb.sbx.aWd[i], lDphyb.sbx.aHt[i], _cBGD_SCRN, 2);

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL)
	{
		i = ScHYB_FNC_NUMB;
		DpFIG_DrwRect(lDphyb.sbx.aX0[i], lDphyb.sbx.aY0[i], lDphyb.sbx.aWd[i], lDphyb.sbx.aHt[i], _cBGD_SCRN, 2);
	}
	
	aSl[DpSCR_SBX_aX0] = lDphyb.sbx.aX0[iFn];
	aSl[DpSCR_SBX_aY0] = lDphyb.sbx.aY0[iFn];
	aSl[DpSCR_SBX_aWd] = lDphyb.sbx.aWd[iFn];
	aSl[DpSCR_SBX_aHt] = lDphyb.sbx.aHt[iFn];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();
#endif
}

void DpHY1_LstIntro(void)
{
#if 0
	DpSCR_UpdtBttn(SCRN_L1_LIST);
	DpHY1_LstUpdat();
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L0
//------------------------------------------------------------------------------------------------------------------------------
void DpHY0_FncStdBy(void)
{
	U08 type = MnFTR_PrGet_SsChn();

#if 1
	DphybLvl_StrValue(type);

	//DphybBox_StrL0Val();
	//DphybBox_StrL1Crr();
	//DphybBox_StrTime();
#endif
	// Tank - Figure
	switch(MnFTR_PrGet_SsChn())
	{
		case MnFTR_SS_SINGLE:		DphybTnk_FgrSingle();	break;
		case MnFTR_SS_DUAL:			DphybTnk_FgrDual();		break;
		default:					DphybTnk_FgrDual();		break;
	}
	
	// Tank - Temperature
	DphybUdt_TankTprt(type);
}

void DpHY0_FncIntro(void)
{
	U08 type = MnFTR_PrGet_SsChn();
	
	#if 0
	U08 fFldA = MnMSR_FieldAGet_Value(MnMS1_I00_FIELDA_RUN); 
	#endif

	Dphyb_InitVari();
	// Title
	DpTTB_UdtIntro(TEXT_LIST_TANK_SCREEN, 70, _cTTB_ST_TITLE);

	// Draw Screen Clear (& Status Update Flag Enable)
	DISP_IntroScrn();

	//DpFIG_DrwRect(x0b-1, y0b-1, wid+2,	hei+2, _cSD_GRAY, DpFIG_TK_02);

	// Meter Line
	DphybText_StrValue(type);

	if(type == MnFTR_SS_DUAL)
	{
		DphybTnk_Fgrinit_Dual();
	}
	else if(type == MnFTR_SS_SINGLE)
	{
		DphybTnk_Fgrinit_Single();
	}	
	// Update Parameter
	DpSCR_UpdtBttn(SCRN_L0_FUNC);

	// Update Parameter
	DpHY0_FncStdBy();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void Dphyb_InitVari(void)
{
	lDphyb.level = 0xffff;
	lDphyb.bx_lv = 0xffff;
	lDphyb.curr = 0xffff;
	lDphyb.tprt = 0xffff;
	lDphyb.unit = 0xff;
	lDphyb.time.minutes = 0;
#if 0
	// Sel-Box Position (Single)
	lDphyb.sbx.aX0[ScHYB_F00_LEVEL] = Dphyb_LVL_TITL_X0 - 8;
	lDphyb.sbx.aY0[ScHYB_F00_LEVEL] = Dphyb_LVL_TITL_Y0 - 3;
	lDphyb.sbx.aWd[ScHYB_F00_LEVEL] = Dphyb_LVL_TITL_WD;
	lDphyb.sbx.aHt[ScHYB_F00_LEVEL] = Dphyb_LVL_TITL_HT;

	lDphyb.sbx.aX0[ScHYB_F01_UNIT_] = Dphyb_LVL_UNIT_X0 - 8;
	lDphyb.sbx.aY0[ScHYB_F01_UNIT_] = Dphyb_LVL_UNIT_Y0 - 3;
	lDphyb.sbx.aWd[ScHYB_F01_UNIT_] = Dphyb_LVL_UNIT_WD;
	lDphyb.sbx.aHt[ScHYB_F01_UNIT_] = Dphyb_LVL_UNIT_HT;

	lDphyb.sbx.aX0[ScHYB_F02_S_DEP] = Dphyb_S_DEP_TL_X0 - 8;
	lDphyb.sbx.aY0[ScHYB_F02_S_DEP] = Dphyb_S_DEP_TL_Y0 - 3;
	lDphyb.sbx.aWd[ScHYB_F02_S_DEP] = 105;
	lDphyb.sbx.aHt[ScHYB_F02_S_DEP] = 30;

	lDphyb.sbx.aX0[ScHYB_F03_DEADZ] = Dphyb_DEADZ_TL_X0 - 8;
	lDphyb.sbx.aY0[ScHYB_F03_DEADZ] = Dphyb_DEADZ_TL_Y0 - 3;
	lDphyb.sbx.aWd[ScHYB_F03_DEADZ] = 105;
	lDphyb.sbx.aHt[ScHYB_F03_DEADZ] = 30;

	lDphyb.sbx.aX0[ScHYB_F04_T_DEP] = Dphyb_T_DEP_TL_X0 - 8;
	lDphyb.sbx.aY0[ScHYB_F04_T_DEP] = Dphyb_T_DEP_TL_Y0 - 3;
	lDphyb.sbx.aWd[ScHYB_F04_T_DEP] = 105;
	lDphyb.sbx.aHt[ScHYB_F04_T_DEP] = 30;

	lDphyb.sbx.aX0[ScHYB_FNC_NUMB]  = Dphyb_LVL_CHNL_X0 - 8;
	lDphyb.sbx.aY0[ScHYB_FNC_NUMB]  = Dphyb_LVL_CHNL_Y0 - 3;
	lDphyb.sbx.aWd[ScHYB_FNC_NUMB]  = Dphyb_LVL_CHNL_WD;
	lDphyb.sbx.aHt[ScHYB_FNC_NUMB]  = Dphyb_LVL_CHNL_HT;
#endif
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

