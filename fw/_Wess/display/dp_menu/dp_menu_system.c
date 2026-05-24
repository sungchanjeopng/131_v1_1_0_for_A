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
#include "app_main.h"
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
#include "menu_system.h"
#include "menu_lyr1_sub_sct.h"
#include "menu_lyr2_item.h"
#include "menu_lyr3_value.h"
#include "menu_lyr4_addition.h"
#include "menu_factory.h"
// disp - menu
#include "dp_menu_main.h"
// self
#include "dp_menu_system.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpSYS_LS lDpSys;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - L2 - I2 (Factory Reset)
//------------------------------------------------------------------------------------------------------------------------------
void DpSy2Val_FtRsUpdat(void)
{
	U08 i;
	U16 aY0[MnSYS_FTR_RST_NUM] = {DpPOP_CT1_Y0, DpPOP_CT2_Y0};
	I08 sCt[MnSYS_FTR_RST_NUM][8] = {{0, }, };
	U16 x0 = DpPOP_CT1_X0;
	U32 cBg = _cPOP_BG_WND;
	U08 val = MnLY3_GetValue();
	U08 lang;
	
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		lang = MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(sCt[0], _sNo);
			_SPRINTF(sCt[1], _sYes);
			for(i=0; i<MnSYS_FTR_RST_NUM; i++)
				DpSTR_GuiLeft(x0, aY0[i], _cPOP_ST_VAL_IDL, cBg, _fE22HsB, sCt[i]);
			
			DpSTR_GuiLeft(x0, aY0[val], _cPOP_ST_VAL_SEL, cBg, _fE22HsB, sCt[val]);
			break;
		case MnSYS_LANG_KOR:
			_SPRINTF(sCt[0], gDpStr.sYnN[0]);
			_SPRINTF(sCt[1], gDpStr.sYnN[1]);
			for(i=0; i<MnSYS_FTR_RST_NUM; i++)
				DpSTR_GuiLeft_KOR(x0, aY0[i], _cPOP_ST_VAL_IDL, cBg, _fE22HsBKOR, sCt[i]);
			
			DpSTR_GuiLeft_KOR(x0, aY0[val], _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, sCt[val]);

			break;
	}

	

}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - L2 - I1 (Screen Return Time)
//------------------------------------------------------------------------------------------------------------------------------
void DpSy2Val_RtTmUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 sCt[16] = {0, };
	U08 val = MnLY3_GetValue();
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);

	switch(val)
	{
		case MnSYS_RTN_TIM_MIN_05:		_SPRINTF(sCt, "5  %s", _sMin_);		break;
		case MnSYS_RTN_TIM_MIN_10:		_SPRINTF(sCt, "10  %s", _sMin_);		break;
		case MnSYS_RTN_TIM_MIN_30:		_SPRINTF(sCt, "30  %s", _sMin_);		break;
		case MnSYS_RTN_TIM_DISABLE:
			switch(lang)
			{
				case MnSYS_LANG_KOR:	
					DpSTR_GuiList(TEXT_LIST_OFF);
					DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					return;
				case MnSYS_LANG_ENG:
					_SPRINTF(sCt, _sOFF);		
					break;
			}
			break;
		default:						_SPRINTF(sCt, _sNG);					break;
	}

	DpSTR_GuiLeft(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsB, sCt);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - L2 - I0 (Time)
//------------------------------------------------------------------------------------------------------------------------------
void DpSy2Val_TimeIntro(void)
{
	RTC_TM rtc = MnSYS_PrGet_Rtc();

	_SPRINTF(lDpSys.pStr,_sNOW_);
	DpSTR_GuiLeft(DpPOP_OLD_X0-170,  DpPOP_OLD_Y0+3, 	_cPOP_ST_VAL_IDL,  _cPOP_BG_WND, _fE17HsB, lDpSys.pStr);

	_SPRINTF(lDpSys.pStr, "20%02d - %d - %d   %2d:%02d", rtc.year, rtc.month, rtc.day, rtc.hours, rtc.minutes);
	_SPRINTF(lDpSys.sTim[MnSYS_T00_YY], "%02d", rtc.year);
	_SPRINTF(lDpSys.sTim[MnSYS_T01_MM], "%02d", rtc.month);
	_SPRINTF(lDpSys.sTim[MnSYS_T02_DD], "%02d", rtc.day);
	_SPRINTF(lDpSys.sTim[MnSYS_T03_HH], "%02d", rtc.hours);
	_SPRINTF(lDpSys.sTim[MnSYS_T04_MN], "%02d", rtc.minutes);

	
	DpSTR_GuiLeft(DpPOP_OLD_X0-110,  DpPOP_OLD_Y0, _cPOP_ST_OLD,  _cPOP_BG_WND, _fE22HsB, lDpSys.pStr);
	DpSTR_GuiLeft(DpPOP_TM_X0_YY-50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, "20");
	DpSTR_GuiLeft(DpPOP_TM_X0_YY+50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, "-");
	DpSTR_GuiLeft(DpPOP_TM_X0_MM+50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, "-");
	DpSTR_GuiLeft(DpPOP_TM_X0_HH+50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, ":");
	#if 0
	DpPOP_UdtExpla(_sRpt_PrsKeep);
	#endif
}


void DpSy2Val_TimeUpdat(void)
{
	U08 i;
	U16 aX0[MnSYS_TIM_NUM] = {DpPOP_TM_X0_YY, DpPOP_TM_X0_MM, DpPOP_TM_X0_DD, DpPOP_TM_X0_HH, DpPOP_TM_X0_MN};
	U08 val = MnLY3_GetUpdnDig();

	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_CT1_Y0-3, DpPOP_BGD_WD, 30, _cPOP_BG_WND, DpFIG_FILL);


	DpSy2Val_TimeIntro();

	for(i=0; i<MnSYS_TIM_NUM; i++)
	{
		_SPRINTF(lDpSys.sTim[i], "%02d", MnLY3_GetTime(i));
		DpSTR_GuiLeft(aX0[i], DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, lDpSys.sTim[i]);
	}
	DpSTR_GuiLeft(aX0[val], DpPOP_CT1_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE22HsB, lDpSys.sTim[val]);

	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_CT1_Y0+27, DpPOP_BGD_WD, 5, _cPOP_BG_WND, DpFIG_FILL);
	DpFIG_DrwLinH(aX0[val], DpPOP_CT1_Y0+30,    33, _cMNU_SEL_SCT);
	DpFIG_DrwLinH(aX0[val], DpPOP_CT1_Y0+30-1, 33, _cMNU_SEL_SCT);
	DpFIG_DrwLinH(aX0[val], DpPOP_CT1_Y0+30-2, 33, _cMNU_SEL_SCT);


	if(MnLY3_GetUpdnMod() == MENU_V3_UPDN_DIG_VALUE)
	{
		DpFIG_DrwRect(DpPOP_TM_VL_X0-5, DpPOP_TM_VL_Y0, 200, 50, _cPOP_BG_WND, DpFIG_FILL);
		DpSTR_GuiLeft(DpPOP_TM_VL_X0,	DpPOP_TM_VL_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE35HsB, lDpSys.sTim[val]);	
	}	
	
}




void DpSy2Val_SiteIntro(void)
{
	U08 ch;

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(MnLY2_GetIdxItem())
		{
			case MnSYS_OPT_CH1_SITE_NAME:	ch = APP_CH_1;	break;
			case MnSYS_OPT_CH2_SITE_NAME:	ch = APP_CH_2;	break;
			default:						break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		ch = APP_CH_1;


	U08 site_name_hi = MnSYS_PrGet_site_name(ch)/100;
	U08 site_name_lo_10 = ((MnSYS_PrGet_site_name(ch))%100)/10;
	U08 site_name_lo_1 = ((MnSYS_PrGet_site_name(ch))%100)%10;

	_SPRINTF(lDpSys.pStr, "%c%d%d", site_name_hi,site_name_lo_10,site_name_lo_1);

	DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
	DpSTR_GuiLeft(DpPOP_OLD_X0, DpPOP_OLD_Y0,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE22HsB, lDpSys.pStr);

#if 0
	DpSTR_GuiLeft(DpPOP_TM_X0_YY-50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, "20");
	DpSTR_GuiLeft(DpPOP_TM_X0_YY+50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, "-");
	DpSTR_GuiLeft(DpPOP_TM_X0_MM+50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, "-");
	DpSTR_GuiLeft(DpPOP_TM_X0_HH+50, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, ":");
#endif
	#if 0
	DpPOP_UdtExpla(_sRpt_PrsKeep);
	#endif
}

void DpSy2Val_SiteUpdat(void)
{
	U16 aX0[MnSYS_SITE_SEL_NUM] = {DpPOP_TM_X0_YY-50, DpPOP_TM_X0_YY-30,DpPOP_TM_X0_YY-15};
	U08 dig = MnLY3_GetUpdnDig();
	U16 val = MnLY3_GetValue();
	U08 site_name_hi = val/100;
	U08 site_name_lo_10 = (val%100)/10;
	U08 site_name_lo_1 = (val%100)%10;
	U08 wd;
	
	_SPRINTF(lDpSys.sSel_site[MnSYS_SITE_SEL_HI], "%c", site_name_hi);
	DpSTR_GuiLeft(aX0[MnSYS_SITE_SEL_HI], DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, lDpSys.sSel_site[MnSYS_SITE_SEL_HI]);

	_SPRINTF(lDpSys.sSel_site[MnSYS_SITE_SEL_LO_10], "%d", site_name_lo_10);
	DpSTR_GuiLeft(aX0[MnSYS_SITE_SEL_LO_10], DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, lDpSys.sSel_site[MnSYS_SITE_SEL_LO_10]);

	_SPRINTF(lDpSys.sSel_site[MnSYS_SITE_SEL_LO_1], "%d", site_name_lo_1);
	DpSTR_GuiLeft(aX0[MnSYS_SITE_SEL_LO_1], DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, lDpSys.sSel_site[MnSYS_SITE_SEL_LO_1]);

	DpSTR_GuiLeft(aX0[dig], DpPOP_CT1_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE22HsB, lDpSys.sSel_site[dig]);

	DpFIG_DrwRect(DpPOP_BGD_X0, DpPOP_CT1_Y0+28, DpPOP_BGD_WD, 5, _cPOP_BG_WND, DpFIG_FILL);
	switch(dig)
	{
		case MnSYS_SITE_SEL_HI:	wd = 18;
		default:	wd=13;
	}
	
	DpFIG_DrwLinH(aX0[dig], DpPOP_CT1_Y0+31,    wd, _cMNU_SEL_SCT);
	DpFIG_DrwLinH(aX0[dig], DpPOP_CT1_Y0+31-1, wd, _cMNU_SEL_SCT);
	DpFIG_DrwLinH(aX0[dig], DpPOP_CT1_Y0+31-2, wd, _cMNU_SEL_SCT);

	if(MnLY3_GetUpdnMod() == MENU_V3_UPDN_DIG_VALUE)
	{
		DpFIG_DrwRect(DpPOP_TM_VL_X0-5, DpPOP_TM_VL_Y0, 200, 50, _cPOP_BG_WND, DpFIG_FILL);
		DpSTR_GuiLeft(DpPOP_TM_VL_X0,	DpPOP_TM_VL_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE35HsB, lDpSys.sSel_site[dig]);	
	}	
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get (Set)
I08* DpSYS_GetAddrSct(U08 idx)		{	return lDpSys.sSct[idx];			}
I08* DpSYS_GetAddrIt0(U08 idx)		{	return lDpSys.sIt0[idx];			}
I08* DpSYS_GetAddrVa0(U08 idx)		{	return lDpSys.sVa0[idx];			}
I08* DpSYS_GetAddrIt1(U08 idx)		{	return lDpSys.sIt1[idx];			}
I08* DpSYS_GetAddrVa1(U08 idx)		{	return lDpSys.sVa1[idx];			}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Additional
//------------------------------------------------------------------------------------------------------------------------------
void DpSYS_AddUpdat(void)
{
#if 0
	S32 val2 = MnLY3_GetValue();
	S32 val3 = MnLY4_GetValue();

	switch(MnLY2_GetIdxItem())
	{
		case MnSYS_OPT_TIME:
			_SPRINTF(lDpSys.sTim[val2], "%02d", (U08)val3);
			DpFIG_DrwRect(DpPOP_TM_VL_X0-5, DpPOP_TM_VL_Y0, 200, 50, _cPOP_BG_WND, DpFIG_FILL);
			DpSTR_GuiLeft(DpPOP_TM_VL_X0,	DpPOP_TM_VL_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE35HsB, lDpSys.sTim[val2]);
			break;
		case MnSYS_OPT_CH1_SITE_NAME:
		case MnSYS_OPT_CH2_SITE_NAME:
			DpSy2Val_SiteUpdat();
			switch(val2)
			{
				case MnSYS_SITE_SEL_HI:
					_SPRINTF(lDpSys.sSel_site[val2], "%c", (U08)val3);
					DpFIG_DrwRect(DpPOP_TM_VL_X0-5, DpPOP_TM_VL_Y0, 200, 50, _cPOP_BG_WND, DpFIG_FILL);
					DpSTR_GuiLeft(DpPOP_TM_VL_X0,	DpPOP_TM_VL_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE35HsB, lDpSys.sSel_site[val2]);
					break;
				case MnSYS_SITE_SEL_LO:
					_SPRINTF(lDpSys.sSel_site[val2], "%02d", (U08)val3);
					DpFIG_DrwRect(DpPOP_TM_VL_X0-5, DpPOP_TM_VL_Y0, 200, 50, _cPOP_BG_WND, DpFIG_FILL);
					DpSTR_GuiLeft(DpPOP_TM_VL_X0,	DpPOP_TM_VL_Y0, _cMNU_SEL_SCT, _cPOP_BG_WND, _fE35HsB, lDpSys.sSel_site[val2]);
					break;					
				default:					break;
			}
			break;
		case MnSYS_OPT_FTR_RST:
			DpFIG_DrwRect(DpPOP_CT1_X0-5, 	DpPOP_CT2_Y0, 200, 40, _cPOP_BG_WND, DpFIG_FILL); 		// Clear
			DpSTR_GuiLeft(DpPOP_CT1_X0, 	DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, _sRst);
			DpSTR_GuiLeft(DpPOP_CT1_X0+100, DpPOP_CT1_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE22HsB, _sDone);
			DpFIG_DrwRect(DpPOP_EXP_X0-5, 	DpPOP_EXP_Y0, 400, 20,_cPOP_BG_WND, DpFIG_FILL); 		// Clear
			DpPOP_UdtExpla(_sExit_Prskey);
			break;
		case MnSYS_OPT_LANG:
			break;

		default:
			return;
	}
#endif
}

void DpSYS_AddIntro(void)
{
	DpSYS_BasePopIntro();
	DpSYS_AddUpdat();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Pop-up
//------------------------------------------------------------------------------------------------------------------------------
void DpSYS_DualBasePopUpdat(void)
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

	switch(MnLY2_GetIdxItem())
	{
		case MnSYS_OPT_PASSCODE:		break;
		case MnSYS_OPT_LANG:			break;
		case MnSYS_OPT_RTN_TIM:			DpSy2Val_RtTmUpdat();		return;
		case MnSYS_OPT_TIME:			DpSy2Val_TimeUpdat();		return;
		case MnSYS_OPT_FTR_RST:			DpSy2Val_FtRsUpdat();		return;
		case MnSYS_OPT_CH1_SITE_NAME:
		case MnSYS_OPT_CH2_SITE_NAME:	DpSy2Val_SiteUpdat();		return;
		default:						break;
	}



	switch(iIt)
	{	// Page #0
		case MnSYS_OPT_PASSCODE:			_SPRINTF(pSt0, "%04d", val);	break;
		case MnSYS_OPT_LANG:		
			switch(lang)
			{
				case MnSYS_LANG_KOR:	
					switch(val)
					{
						case MnSYS_LANG_KOR:		DpSTR_GuiList(TEXT_LIST_KOREAN);	break;
						case MnSYS_LANG_ENG:		DpSTR_GuiList(TEXT_LIST_ENGLISH);	break;
					}
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnSYS_LANG_KOR:		_SPRINTF(pSt0, "Korean");		break;
						case MnSYS_LANG_ENG:		_SPRINTF(pSt0, "English");		break;
						default:					_SPRINTF(pSt0, _sNG);			break;
					}
					break;
			}
			break;
		default:															break;
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

void DpSYS_SingleBasePopUpdat(void)
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

	switch(MnLY2_GetIdxItem())
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		break;
		case MnSYS_OPT_SINGLE_LANG:			break;
		case MnSYS_OPT_SINGLE_RTN_TIM:		DpSy2Val_RtTmUpdat();		return;
		case MnSYS_OPT_SINGLE_TIME:			DpSy2Val_TimeUpdat();		return;
		case MnSYS_OPT_SINGLE_FTR_RST:		DpSy2Val_FtRsUpdat();		return;
		case MnSYS_OPT_SINGLE_SITE_NAME:	DpSy2Val_SiteUpdat();		return;
		default:						break;
	}



	switch(iIt)
	{	// Page #0
		case MnSYS_OPT_SINGLE_PASSCODE:			_SPRINTF(pSt0, "%04d", val);	break;
		case MnSYS_OPT_SINGLE_LANG:		
			switch(lang)
			{
				case MnSYS_LANG_KOR:	
					switch(val)
					{
						case MnSYS_LANG_KOR:		DpSTR_GuiList(TEXT_LIST_KOREAN);	break;
						case MnSYS_LANG_ENG:		DpSTR_GuiList(TEXT_LIST_ENGLISH);	break;
					}
					DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					switch(val)
					{
						case MnSYS_LANG_KOR:		_SPRINTF(pSt0, "Korean");		break;
						case MnSYS_LANG_ENG:		_SPRINTF(pSt0, "English");		break;
						default:					_SPRINTF(pSt0, _sNG);			break;
					}
					break;
			}
			break;
		default:															break;
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


void DpSYS_BasePopUpdat(void)
{

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpSYS_DualBasePopUpdat();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpSYS_SingleBasePopUpdat();

}

void DpSYS_DualBasePopIntro(void)
{

	S32 min, max;
	U08 fDp = _F_F;
	U08 iIt = MnLY2_GetIdxItem();
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpSys.pStr, lDpSys.sIt0[iIt]);
			break;
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpSys.pStr, lDpSys.sIt0[iIt]);
			break;
	}

	// Title

	DpPOP_UdtTitle(lDpSys.pStr);

	// Old
	fDp = _F_F;
	switch(iIt)
	{
		case MnSYS_OPT_PASSCODE:		break;
		case MnSYS_OPT_TIME:			DpSy2Val_TimeIntro();		break;
		case MnSYS_OPT_CH1_SITE_NAME:
		case MnSYS_OPT_CH2_SITE_NAME:	DpSy2Val_SiteIntro();		break;
		case MnSYS_OPT_LANG:
			switch(lang)
			{
				case MnSYS_LANG_KOR:	
					switch(MnSYS_PrGetBase_Item(iIt))
					{
						case MnSYS_LANG_KOR:		DpSTR_GuiList(TEXT_LIST_KOREAN);	break;
						case MnSYS_LANG_ENG:		DpSTR_GuiList(TEXT_LIST_ENGLISH);	break;
					}
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					fDp = _F_T; 	
					switch(MnSYS_PrGetBase_Item(iIt))
					{
						case MnSYS_LANG_KOR:		_SPRINTF(lDpSys.pStr, "Korean");		break;
						case MnSYS_LANG_ENG:		_SPRINTF(lDpSys.pStr, "English");		break;
						default:					_SPRINTF(lDpSys.pStr, _sNG);			break;
					}
					break;
			}
			break;
		case MnSYS_OPT_RTN_TIM: 	
			fDp = _F_T; 
			switch(MnSYS_PrGetBase_Item(iIt))
			{
				case MnSYS_RTN_TIM_DISABLE: 
					switch(lang)
					{
						case MnSYS_LANG_KOR:	
							fDp = _F_F; 
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
							DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
							break;
						case MnSYS_LANG_ENG:
							_SPRINTF(lDpSys.pStr, _sDisable);		
							break;
					}
					break;
				case MnSYS_RTN_TIM_MIN_05:		_SPRINTF(lDpSys.pStr, "5  min");		break;
				case MnSYS_RTN_TIM_MIN_10:		_SPRINTF(lDpSys.pStr, "10 min");		break;
				case MnSYS_RTN_TIM_MIN_30:		_SPRINTF(lDpSys.pStr, "30 min");		break;
				default:						_SPRINTF(lDpSys.pStr, _sNG);			break;
			}	
			break;
		default:					fDp = _F_F; 	_SPRINTF(lDpSys.pStr, _sNG);		break;
	}
	if(fDp)
		DpPOP_UdtOldVl(lDpSys.pStr);

	// MIN / MAX
	fDp = _F_F;
	switch(iIt)
	{	// Page #0
		case MnSYS_OPT_PASSCODE:	min = 0; max=9999; fDp = _F_T;	break;
		case MnSYS_OPT_TIME:		break;
		case MnSYS_OPT_FTR_RST: 	break;
		// Not Yet
		case MnSYS_OPT_LANG:		break;
		default:					break;
	}
#if 1
	if(fDp)
		DpPOP_UdtRange(min, max);
#endif
	// Explanation
	fDp = _F_F;
	switch(iIt)
	{
		case MnSYS_OPT_TIME:
#if 0
		case MnSYS_I01_RTN_TIM: 	fDp = _F_T; 	_SPRINTF(lDpSys.pStr, _sSel_PsSet); 	break;
#endif
		case MnSYS_OPT_FTR_RST: 	fDp = _F_T; 	_SPRINTF(lDpSys.pStr, _sCaut_Reset);	break;
		// Not Yet
		case MnSYS_OPT_LANG:		break;
		default:					fDp = _F_T; 	_SPRINTF(lDpSys.pStr, _sNG);			break;
	}
	if(fDp)
		DpPOP_UdtExpla(lDpSys.pStr);

}

void DpSYS_SingleBasePopIntro(void)
{
	S32 min, max;
	U08 fDp = _F_F;
	U08 iIt = MnLY2_GetIdxItem();
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpSys.pStr, lDpSys.sIt0[iIt]);
			break;
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpSys.pStr, lDpSys.sIt0[iIt]);
			break;
	}

	// Title

	DpPOP_UdtTitle(lDpSys.pStr);

	// Old
	fDp = _F_F;
	switch(iIt)
	{
		case MnSYS_OPT_SINGLE_PASSCODE:		break;
		case MnSYS_OPT_SINGLE_TIME:			DpSy2Val_TimeIntro();		break;
		case MnSYS_OPT_SINGLE_SITE_NAME:	DpSy2Val_SiteIntro();		break;
		case MnSYS_OPT_SINGLE_LANG:
			switch(lang)
			{
				case MnSYS_LANG_KOR:	
					switch(MnSYS_PrGetBase_Ch_Item(iIt))
					{
						case MnSYS_LANG_KOR:		DpSTR_GuiList(TEXT_LIST_KOREAN);	break;
						case MnSYS_LANG_ENG:		DpSTR_GuiList(TEXT_LIST_ENGLISH);	break;
					}
					DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
					break;
				case MnSYS_LANG_ENG:
					fDp = _F_T; 	
					switch(MnSYS_PrGetBase_Ch_Item(iIt))
					{
						case MnSYS_LANG_KOR:		_SPRINTF(lDpSys.pStr, "Korean");		break;
						case MnSYS_LANG_ENG:		_SPRINTF(lDpSys.pStr, "English");		break;
						default:					_SPRINTF(lDpSys.pStr, _sNG);			break;
					}
					break;
			}
			break;
		case MnSYS_OPT_SINGLE_RTN_TIM: 	
			fDp = _F_T; 
			switch(MnSYS_PrGetBase_Ch_Item(iIt))
			{
				case MnSYS_RTN_TIM_DISABLE: 
					switch(lang)
					{
						case MnSYS_LANG_KOR:	
							fDp = _F_F; 
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
							DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
							break;
						case MnSYS_LANG_ENG:
							_SPRINTF(lDpSys.pStr, _sDisable);		
							break;
					}
					break;
				case MnSYS_RTN_TIM_MIN_05:		_SPRINTF(lDpSys.pStr, "5  min");		break;
				case MnSYS_RTN_TIM_MIN_10:		_SPRINTF(lDpSys.pStr, "10 min");		break;
				case MnSYS_RTN_TIM_MIN_30:		_SPRINTF(lDpSys.pStr, "30 min");		break;
				default:						_SPRINTF(lDpSys.pStr, _sNG);			break;
			}	
			break;
		default:					fDp = _F_F; 	_SPRINTF(lDpSys.pStr, _sNG);		break;
	}
	if(fDp)
		DpPOP_UdtOldVl(lDpSys.pStr);

	// MIN / MAX
	fDp = _F_F;
	switch(iIt)
	{	// Page #0
		case MnSYS_OPT_SINGLE_PASSCODE:	min = 0; max=9999; fDp = _F_T;	break;
		case MnSYS_OPT_SINGLE_TIME:		break;
		case MnSYS_OPT_SINGLE_FTR_RST: 	break;
		// Not Yet
		case MnSYS_OPT_SINGLE_LANG:		break;
		default:						break;
	}
#if 1
	if(fDp)
		DpPOP_UdtRange(min, max);
#endif
	// Explanation
	fDp = _F_F;
	switch(iIt)
	{
		case MnSYS_OPT_SINGLE_TIME:
#if 0
		case MnSYS_I01_RTN_TIM: 	fDp = _F_T; 	_SPRINTF(lDpSys.pStr, _sSel_PsSet); 	break;
#endif
		case MnSYS_OPT_SINGLE_FTR_RST: 	fDp = _F_T; 	_SPRINTF(lDpSys.pStr, _sCaut_Reset);	break;
		// Not Yet
		case MnSYS_OPT_SINGLE_LANG:		break;
		default:					fDp = _F_T; 	_SPRINTF(lDpSys.pStr, _sNG);			break;
	}
	if(fDp)
		DpPOP_UdtExpla(lDpSys.pStr);

}


void DpSYS_BasePopIntro(void)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpSYS_DualBasePopIntro();
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpSYS_SingleBasePopIntro();


}

void DpSYS_AlarmPopUpdat(void)
{
	U16 x0 = DpPOP_CT1_X0;
	U16 y1 = DpPOP_CT2_Y0;
	U16 y0 = DpPOP_CT1_Y0;
	U32 cBg = _cPOP_BG_WND;
	I08 pSt0[16] = {0, };

	S32 val = MnLY3_GetValue();
	S32 dig = MnLY3_GetUpdnDig();
	S32 updn_mod = MnLY3_GetUpdnMod();
	S32 max  = MnLY3_GetMax();
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(MnLY2_GetIdxItem())
	{
		case MnSYS_OPT_ALARM_TIMER:
			switch(val)
			{
				case MnSYS_ALARM_TIMER_OFF:
					switch(lang)
					{
						case MnSYS_LANG_KOR:	
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft_KOR(x0, y0, _cPOP_ST_VAL_SEL, cBg, _fE22HsBKOR, gDpStr.Text_list);
							return;
						case MnSYS_LANG_ENG:
							_SPRINTF(pSt0, _sOFF);		
							break;
					}
					break;
				case MnSYS_ALARM_TIMER_1M:		_SPRINTF(pSt0, "1 Month");		break;
				case MnSYS_ALARM_TIMER_3M:		_SPRINTF(pSt0, "3 Month");		break;
				case MnSYS_ALARM_TIMER_6M:		_SPRINTF(pSt0, "6 Month");		break;
				case MnSYS_ALARM_TIMER_12M: 	_SPRINTF(pSt0, "12 Month");		break;
				default:						_SPRINTF(pSt0, _sNG);			break;
			}
			break;	
		case MnSYS_OPT_ALARM_RESET:
			DpPOP_UdtValue(0,	_F_F, gDpStr.sYnN[0]);
			DpPOP_UdtValue(1,	_F_F, gDpStr.sYnN[1]);
			DpPOP_UdtValue(val, _F_T, gDpStr.sYnN[val]);
			return;
		default:							break;
	}

	DpFIG_DrwRect(x0, y0, 200, 30, cBg, DpFIG_FILL);
	DpFIG_DrwRect(x0, y1, 200, 30, cBg, DpFIG_FILL);
	
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

void DpSYS_AlarmPopIntro(void)
{
	U08 fDp = _F_F;
	U08 iIt = MnLY2_GetIdxItem();
	U08 val = MnSYS_PrGetAlarm_Item(iIt);
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_KOR:
			_SPRINTF(lDpSys.pStr, lDpSys.sIt1[iIt]);
			break;
		case MnSYS_LANG_ENG:
			switch(iIt)
			{
				case MnSYS_OPT_ALARM_TIMER:		_SPRINTF(lDpSys.pStr, _sAlarm_timer);			break;
				case MnSYS_OPT_ALARM_RESET:		_SPRINTF(lDpSys.pStr, _sAlarm_reset);				break;	
				default:						_SPRINTF(lDpSys.pStr, _sNG);				break;
			}		
			break;
	}

	// Title

	DpPOP_UdtTitle(lDpSys.pStr);

	// Old
	fDp = _F_F;
	switch(iIt)
	{
		case MnSYS_OPT_ALARM_TIMER:		
			fDp = _F_T;
			switch(val)
			{
				case MnSYS_ALARM_TIMER_OFF:
					switch(lang)
					{
						case MnSYS_LANG_KOR:	
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_OLD_Y0+3, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
							DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_OLD_Y0,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
							fDp = _F_F;
							break;
						case MnSYS_LANG_ENG:
							_SPRINTF(lDpSys.pStr, _sDisable);		
							break;
					}
					break;
				case MnSYS_ALARM_TIMER_1M:		_SPRINTF(lDpSys.pStr, "1 Month");		break;
				case MnSYS_ALARM_TIMER_3M:		_SPRINTF(lDpSys.pStr, "3 Month");		break;
				case MnSYS_ALARM_TIMER_6M:		_SPRINTF(lDpSys.pStr, "6 Month");		break;
				case MnSYS_ALARM_TIMER_12M:		_SPRINTF(lDpSys.pStr, "12 Month");		break;
				default:						_SPRINTF(lDpSys.pStr, _sNG);			break;
			}
			break;	
		default:				
			_SPRINTF(lDpSys.pStr, _sNG);	
			break;
	}
	
	if(fDp)
		DpPOP_UdtOldVl(lDpSys.pStr);

	// MIN / MAX
	fDp = _F_T;
	switch(iIt)
	{	// Page #0
		case MnSYS_OPT_ALARM_TIMER:								
			DpSTR_GuiList(TEXT_LIST_OFF);
			DpSTR_GuiLeft(DpPOP_MIN_X0, DpPOP_MIN_Y0, _cPOP_ST_MIN, _cPOP_BG_WND, _fE17HsB, _sMIN);
			DpSTR_GuiLeft_KOR(DpPOP_OLD_X0, DpPOP_MIN_Y0, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsBKOR, gDpStr.Text_list);
			fDp = _F_F; 
			break;
		default:				
			fDp = _F_F; 
			break;
	}

	if(fDp)
		DpPOP_UdtRangeMin(lDpSys.pStr);

	fDp = _F_T;
	switch(iIt)
	{	// Page #0
		case MnSYS_OPT_ALARM_TIMER:	_SPRINTF(lDpSys.pStr, "12 Month");	break;
		default:				
			fDp = _F_F; 
			break;

	}

	if(fDp)
		DpPOP_UdtRangeMax(lDpSys.pStr);


}

void DpSYS_PopUpdat(void)
{
	U08 iSb = MnLY1_GetSection();


	switch(iSb)
	{
		case MnSYS_SUB_BASE:	DpSYS_BasePopUpdat();	break;
		case MnSYS_SUB_ALARM:	DpSYS_AlarmPopUpdat();	break;
		// Not Yet
		default:
			break;		
	}
}

void DpSYS_PopIntro(void)
{
	U08 iSb = MnLY1_GetSection();

	switch(iSb)
	{
		case MnSYS_SUB_BASE:	DpSYS_BasePopIntro();	break;
		case MnSYS_SUB_ALARM:	DpSYS_AlarmPopIntro();	break;
		// Not Yet
		default:
			break;		
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void DpSYS_InitVari(void)
{
	U08 i;
	U16 val;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:
				DpSTR_GuiList(TEXT_LIST_BASE);
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_BASE],gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_ALARM);
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_ALARM],    gDpStr.Text_list);	
				DpSTR_GuiList(TEXT_LIST_PASSCODE);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_PASSCODE],gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_LANG);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_LANG],    gDpStr.Text_list);	
				DpSTR_GuiList(TEXT_LIST_TIME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_TIME],    gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_RETURN_MEAS);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_RTN_TIM], gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_CH1_SITE_NAME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_CH1_SITE_NAME],    gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_CH2_SITE_NAME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_CH2_SITE_NAME],    gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_FACTORY_RESET);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_FTR_RST], gDpStr.Text_list);		
				DpSTR_GuiList(TEXT_LIST_TIMER);
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_TIMER],    gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_RESET);
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_RESET], gDpStr.Text_list);
				break;
			case MnSYS_LANG_ENG:
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_BASE],    _sBase);
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_ALARM], 	_sAlarm);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_PASSCODE],_sPasscode);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_LANG],    _sLang);	
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_TIME],    _sTime);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_RTN_TIM], _sRtnTim);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_CH1_SITE_NAME],    _sCH1_SITE_NAME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_CH2_SITE_NAME],    _sCH2_SITE_NAME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_FTR_RST], _sFtrRst);			
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_TIMER],    _sAlarm_timer);
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_RESET], _sAlarm_reset);	
				break;
			default:
				break;
		}
	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:
				DpSTR_GuiList(TEXT_LIST_BASE);
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_BASE],gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_ALARM);
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_ALARM],	  gDpStr.Text_list);	
				DpSTR_GuiList(TEXT_LIST_PASSCODE);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_PASSCODE],gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_LANG);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_LANG],	 gDpStr.Text_list); 
				DpSTR_GuiList(TEXT_LIST_TIME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_TIME],	 gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_RETURN_MEAS);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_RTN_TIM], gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_SITE_NAME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_SITE_NAME],	  gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_FACTORY_RESET);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_FTR_RST], gDpStr.Text_list); 	
				DpSTR_GuiList(TEXT_LIST_TIMER);
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_TIMER],	gDpStr.Text_list);
				DpSTR_GuiList(TEXT_LIST_RESET);
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_RESET], gDpStr.Text_list);
				break;
			case MnSYS_LANG_ENG:
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_BASE],	 _sBase);
				_SPRINTF(lDpSys.sSct[MnSYS_SUB_ALARM],	_sAlarm);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_PASSCODE],_sPasscode);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_LANG],	 _sLang);	
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_TIME],	 _sTime);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_RTN_TIM], _sRtnTim);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_SITE_NAME],	  _sSITE_NAME);
				_SPRINTF(lDpSys.sIt0[MnSYS_OPT_SINGLE_FTR_RST], _sFtrRst); 		
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_TIMER],	_sAlarm_timer);
				_SPRINTF(lDpSys.sIt1[MnSYS_OPT_ALARM_RESET], _sAlarm_reset);	
				break;
			default:
				break;
		}
	}

	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
	{
		val = MnSYS_PrGetBase_Item(MnSYS_OPT_PASSCODE);	
		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_PASSCODE],  "-");

		val = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


		switch(val)
		{
			case MnSYS_LANG_ENG:	_SPRINTF(lDpSys.sVa0[MnSYS_OPT_LANG],    "English");	break;
			case MnSYS_LANG_KOR:	DpSTR_GuiList(TEXT_LIST_KOREAN); _SPRINTF(lDpSys.sVa0[MnSYS_OPT_LANG],    gDpStr.Text_list);		break;
			default:
				break;
		}

		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_TIME], "-");

		switch(MnSYS_PrGetBase_Item(MnSYS_OPT_RTN_TIM))
		{
			case MnSYS_RTN_TIM_DISABLE:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_RTN_TIM], _sOFF);			break;
			case MnSYS_RTN_TIM_MIN_05:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_RTN_TIM], "5  min");		break;
			case MnSYS_RTN_TIM_MIN_10:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_RTN_TIM], "10 min");		break;
			case MnSYS_RTN_TIM_MIN_30:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_RTN_TIM], "30 min");		break;
			default:						_SPRINTF(lDpSys.sVa0[MnSYS_OPT_RTN_TIM], _sNG);					break;
		}

		val  = MnSYS_PrGet_site_name(APP_CH_1);

		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_CH1_SITE_NAME], "%c%d%d", val/100,(val%100)/10, (val%100)%10);

		val  = MnSYS_PrGet_site_name(APP_CH_2);

		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_CH2_SITE_NAME], "%c%d%d", val/100,(val%100)/10, (val%100)%10);


		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_FTR_RST], "-");

	}
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
	{
		val = MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_PASSCODE); 
		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_PASSCODE],  "-");
		
		val = MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_LANG);
		
		
		switch(val)
		{
			case MnSYS_LANG_ENG:	_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_LANG],	 "English");	break;
			case MnSYS_LANG_KOR:	DpSTR_GuiList(TEXT_LIST_KOREAN); _SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_LANG],	  gDpStr.Text_list);		break;
			default:
				break;
		}
		
		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_TIME], "-");
		
		switch(MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_RTN_TIM))
		{
			case MnSYS_RTN_TIM_DISABLE: 	_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_RTN_TIM], _sOFF);			break;
			case MnSYS_RTN_TIM_MIN_05:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_RTN_TIM], "5  min"); 	break;
			case MnSYS_RTN_TIM_MIN_10:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_RTN_TIM], "10 min"); 	break;
			case MnSYS_RTN_TIM_MIN_30:		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_RTN_TIM], "30 min"); 	break;
			default:						_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_RTN_TIM], _sNG); 				break;
		}
		
		val  = MnSYS_PrGet_site_name(APP_CH_1);
		
		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_SITE_NAME], "%c%d%d", val/100,(val%100)/10, (val%100)%10);
		
		_SPRINTF(lDpSys.sVa0[MnSYS_OPT_SINGLE_FTR_RST], "-");
	}


	val = MnSYS_PrGetAlarm_Item(MnSYS_OPT_ALARM_TIMER);
	switch(val)
	{
		case MnSYS_ALARM_TIMER_OFF: 	_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_TIMER], _sOFF);			break;
		case MnSYS_ALARM_TIMER_1M:		_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_TIMER], "1 Month");		break;
		case MnSYS_ALARM_TIMER_3M:		_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_TIMER], "3 Month");		break;
		case MnSYS_ALARM_TIMER_6M:		_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_TIMER], "6 Month");		break;
		case MnSYS_ALARM_TIMER_12M: 	_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_TIMER], "12 Month");		break;
		default:						_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_TIMER], _sNG); 		break;
	}	
	_SPRINTF(lDpSys.sVa1[MnSYS_OPT_ALARM_RESET], "-");

	_MEMSET(lDpSys.pStr, 0, sizeof(lDpSys.pStr));

	for(i=0; i<MnSYS_TIM_NUM; i++)
		_MEMSET(lDpSys.sTim[i], 0, sizeof(lDpSys.sTim[i]));
}

void DpSY1_StrSbSct(void)
{
	U08 i=0;
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	for(i=0; i<MnSYS_SUB_NUM; i++)
	{
		switch(lang)
		{
			case MnSYS_LANG_KOR:
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsBKOR, lDpSys.sSct[i]);
				break;			
			case MnSYS_LANG_ENG:
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), _cMNU_STR_IDLE, _cMNU_BOX_BG, _fE17HsB, lDpSys.sSct[i]);
				break;

		}
	}
}

void DpSy2_DualStrCntts(U08 sub)
{
	U08 i,n,page,idx,iN;
	U32 cStr =_cMNU_STR_IDLE;
	I08 *pItm, *pVal;	
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iIt = MnLY2_GetIdxItem();
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U32 back_color = _cMNU_BOX_BG;
	U32 text_color = _cMNU_STR_IDLE;
	U32 back_value_color = _cMNU_BOX_BG;
	U32 text_value_color = _cMNU_STR_IDLE;


	switch(sub)
	{
		case MnSYS_SUB_BASE:		n = MnSY0_OPT_NUM;			break;
		case MnSYS_SUB_ALARM:		n = MnSY1_OPT_NUM;			break;
		default:					return;
	}


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
		idx = i+(DpMNU_ITM_PAGE*page);

		DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-30-60, 37, _cMNU_BOX_BG, DpFIG_FILL);

		if(MENU_GetLayer()>=MENU_L2_ITEM)
		{
			if(i==sel)
			{
				back_color = _cMNU_SEL_ITM;
				text_color = _cSD_DARKGRAY;
				back_value_color = _cMNU_BOX_BG;
				text_value_color = _cSD_WHITE;	
			}
			else
			{
				back_color = _cMNU_BOX_BG;
				text_color = _cMNU_STR_IDLE;
				back_value_color = _cTTB_BG_MID;
				text_value_color = cStr;				
			}
		}

		switch(sub)
		{
			case MnSYS_SUB_BASE:	pItm = lDpSys.sIt0[idx]; 	pVal = lDpSys.sVa0[idx]; break;
			case MnSYS_SUB_ALARM: 	pItm = lDpSys.sIt1[idx]; 	pVal = lDpSys.sVa1[idx]; break;
			default:				return;
		}

		switch(lang)
		{
			case MnSYS_LANG_ENG:		
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, pItm);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), text_value_color,back_value_color, _fE17HsB, pVal);	
				break;
			case MnSYS_LANG_KOR:
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR,  pItm);
				if((sub == MnSYS_SUB_BASE) && (idx == MnSYS_OPT_RTN_TIM))
				{
					if( MnSYS_PrGetBase_Item(MnSYS_OPT_RTN_TIM)==MnSYS_RTN_TIM_DISABLE)
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsBKOR, gDpStr.Text_list);
						break;
					}
				}

				if((sub == MnSYS_SUB_BASE) && (idx == MnSYS_OPT_LANG))
				{
					if( MnSYS_PrGetBase_Item(MnSYS_OPT_LANG)==MnSYS_LANG_KOR)
					{
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsBKOR, pVal);
						break;
					}
				}
				
				if((sub == MnSYS_SUB_ALARM) && (idx == MnSYS_OPT_ALARM_TIMER))
				{
					if( MnSYS_PrGetAlarm_Item(MnSYS_OPT_ALARM_TIMER)==MnSYS_ALARM_TIMER_OFF)
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsBKOR, gDpStr.Text_list);
						break;
					}
				}

				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsB, pVal);		
				break;
		}
	}

}


void DpSy2_SingleStrCntts(U08 sub)
{
	U08 i,n,page,idx,iN;
	U32 cStr =_cMNU_STR_IDLE;
	I08 *pItm, *pVal;	
	U16 box_itm_x0 = DpMNU_STR_X0_ITM;
	U16 box_val_x0 = DpMNU_STR_X0_VAL;
	U16 str_y0 = DpMNU_STR_Y0;
	U16 str_yg = DpMNU_STR_YG;
	U08 iIt = MnLY2_GetIdxItem();
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);	
	U08 sel;
	U32 back_color = _cMNU_BOX_BG;
	U32 text_color = _cMNU_STR_IDLE;
	U32 back_value_color = _cMNU_BOX_BG;
	U32 text_value_color = _cMNU_STR_IDLE;


	switch(sub)
	{
		case MnSYS_SUB_BASE:		n = MnSY0_OPT_SINGLE_NUM;	break;
		case MnSYS_SUB_ALARM:		n = MnSY1_OPT_NUM;			break;
		default:					return;
	}


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
		idx = i+(DpMNU_ITM_PAGE*page);

		DpFIG_DrwRect(DpMNU_BOX_X0_VAL+60, str_y0+(str_yg*i)+15, DpMNU_BOX_WID-30-60, 37, _cMNU_BOX_BG, DpFIG_FILL);

		if(MENU_GetLayer()>=MENU_L2_ITEM)
		{
			if(i==sel)
			{
				back_color = _cMNU_SEL_ITM;
				text_color = _cSD_DARKGRAY;
				back_value_color = _cMNU_BOX_BG;
				text_value_color = _cSD_WHITE;	
			}
			else
			{
				back_color = _cMNU_BOX_BG;
				text_color = _cMNU_STR_IDLE;
				back_value_color = _cTTB_BG_MID;
				text_value_color = cStr;				
			}
		}

		switch(sub)
		{
			case MnSYS_SUB_BASE:	pItm = lDpSys.sIt0[idx]; 	pVal = lDpSys.sVa0[idx]; break;
			case MnSYS_SUB_ALARM: 	pItm = lDpSys.sIt1[idx]; 	pVal = lDpSys.sVa1[idx]; break;
			default:				return;
		}

		switch(lang)
		{
			case MnSYS_LANG_ENG:		
				DpSTR_GuiLeft(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsB, pItm);
				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), text_value_color,back_value_color, _fE17HsB, pVal);	
				break;
			case MnSYS_LANG_KOR:
				DpSTR_GuiLeft_KOR(box_itm_x0, str_y0+(str_yg*i), text_color, back_color, _fE17HsBKOR,  pItm);
				if((sub == MnSYS_SUB_BASE) && (idx == MnSYS_OPT_SINGLE_RTN_TIM))
				{
					if( MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_RTN_TIM)==MnSYS_RTN_TIM_DISABLE)
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsBKOR, gDpStr.Text_list);
						break;
					}
				}

				if((sub == MnSYS_SUB_BASE) && (idx == MnSYS_OPT_SINGLE_LANG))
				{
					if( MnSYS_PrGetBase_Item(MnSYS_OPT_SINGLE_LANG)==MnSYS_LANG_KOR)
					{
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsBKOR, pVal);
						break;
					}
				}
				
				if((sub == MnSYS_SUB_ALARM) && (idx == MnSYS_OPT_ALARM_TIMER))
				{
					if( MnSYS_PrGetAlarm_Item(MnSYS_OPT_ALARM_TIMER)==MnSYS_ALARM_TIMER_OFF)
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsBKOR, gDpStr.Text_list);
						break;
					}
				}

				DpSTR_GuiLeft(box_val_x0, str_y0+(str_yg*i), text_value_color,  back_value_color, _fE17HsB, pVal);		
				break;
		}
	}

}


void DpSY2_StrCntts(U08 sub)
{
	if(MnFTR_PrGet_SsChn()==MnFTR_SS_DUAL)
		DpSy2_DualStrCntts(sub);
	else if(MnFTR_PrGet_SsChn()==MnFTR_SS_SINGLE)
		DpSy2_SingleStrCntts(sub);
	
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

