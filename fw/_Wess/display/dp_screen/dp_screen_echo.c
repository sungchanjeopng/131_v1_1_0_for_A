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
// bsp
#include "bsp_adc.h"
// app
#include "app_status.h"
// measure
#include "measure_calc.h"
// display
#include "disp_main.h"
#include "disp_color.h"
#include "disp_figure.h"
#include "disp_string.h"
#include "disp_titlebar.h"
#include "disp_button.h"
#include "disp_popup.h"
// menu
#include "menu_measure.h"
#include "menu_factory.h"
#include "menu_system.h"
#include "menu_test.h"
#include "menu_engineer.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_echo.h"
#include "screen_eco1_list.h"
#include "screen_eco2_value.h"
// disp - screen
#include "dp_screen_main.h"
#include "dp_screen_calib.h"
// self
#include "dp_screen_echo.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpECO_LS lDpEco;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Graph
//------------------------------------------------------------------------------------------------------------------------------
void DpEchoPOP_UdtOldVl(I08* pStr)
{
	DpSTR_GuiLeft(DpECO_LVL_TITL_X0+140, DpECO_GRP_Y0+60, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
	DpSTR_GuiLeft(DpECO_LVL_TITL_X0+140, DpECO_GRP_Y0+80,   _cPOP_ST_OLD,     _cPOP_BG_WND, _fE17HsB, pStr);
}

void DpEchoPOP_UdtTitle(I08* pStr)
{
	U16 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+20, _cPOP_ST_TIT, _cPOP_BG_WND, _fE17HsB, pStr);
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+20, _cPOP_ST_TIT, _cPOP_BG_WND, _fE17HsBKOR, pStr);
			break;
	}

}

void DpEchoPOP_DrwIntro(void)
{
	DpFIG_DrwRect(DpECO_LVL_TITL_X0, DpECO_GRP_Y0, DpECO_BOX_FG_WD+4, DpECO_BOX_FG_HT, _cPOP_BG_WND, DpFIG_FILL);

	// Window
	DpFIG_DrwRect(DpECO_LVL_TITL_X0, DpECO_GRP_Y0,     DpECO_BOX_FG_WD, 4,   _cPOP_BG_UPP, DpFIG_FILL);
	DpFIG_DrwRect(DpECO_LVL_TITL_X0, DpECO_GRP_Y0+4,   DpECO_BOX_FG_WD, 175, _cPOP_BG_WND, DpFIG_FILL);
	DpFIG_DrwRect(DpECO_LVL_TITL_X0, DpECO_GRP_Y0+180, DpECO_BOX_FG_WD, 4,   0xff1C1F24,   DpFIG_FILL);
	DpFIG_DrwRect(DpECO_LVL_TITL_X0, DpECO_GRP_Y0+182, DpECO_BOX_FG_WD, 4,   0xff1F2F1F,   DpFIG_FILL);
	// Line
	DpFIG_DrwRect(DpECO_LVL_TITL_X0+2, DpECO_GRP_Y0+4, DpECO_BOX_FG_WD, 2, _cPOP_BG_LN_0, DpFIG_FILL);
	DpFIG_DrwRect(DpECO_LVL_TITL_X0+10, DpECO_GRP_Y0+50, DpECO_BOX_FG_WD-10, 2, _cPOP_BG_LN_1, DpFIG_FILL);
	DpFIG_DrwRect(DpECO_LVL_TITL_X0+10, DpECO_GRP_Y0+110, DpECO_BOX_FG_WD-10, 2, _cPOP_BG_LN_1, DpFIG_FILL);
	DpFIG_DrwRect(DpECO_LVL_TITL_X0+10, DpECO_GRP_Y0+170, DpECO_BOX_FG_WD-10, 2, _cPOP_BG_LN_1, DpFIG_FILL);
}



void DpEcoGrp_TtlAmp(void)
{
	U16 y1_val = (ADC_VAL_MAX*10)/33;
	U16 y2_val = (ADC_VAL_MAX*20)/33;
	U16 y3_val = (ADC_VAL_MAX*30)/33;
	U16 y1 =DpECO_GRP_Y0+(DpECO_GRP_HT-(y1_val/16));
	U16 y2 =DpECO_GRP_Y0+(DpECO_GRP_HT-(y2_val/16));
	U16 y3 =DpECO_GRP_Y0+(DpECO_GRP_HT-(y3_val/16));

	DpSTR_GuiLeft(DpECO_GRP_X0-39, y3-10, _cECO_AMP_STD, _cBGD_SCRN, _fE12HsM, "3.0");
	DpSTR_GuiLeft(DpECO_GRP_X0-39, y2-10, _cECO_AMP_STD, _cBGD_SCRN, _fE12HsM, "2.0");
	DpSTR_GuiLeft(DpECO_GRP_X0-39, y1-10, _cECO_AMP_STD, _cBGD_SCRN, _fE12HsM, "1.0");
}

void DpEcoGrp_LineTvg(void)
{
	U32 i;
	U32 x0[TVG_IDX_MAX];
	U16 y0[TVG_IDX_MAX];	
	U08 ich = ScECH_PrGet_Chnnl();
	U08 iFn = ScEC1_GetIdxFunc();
	S32 val = ScEC2_GetValue();
	S32 gain  = MnMSR_CalGet_Ch_Value(ich, MnMS1_OPT_SINGLE_ECHO_AMP);
	U08 fTVG  = MnEGN_PrGet_CH_Item(ich, MnEGN_OPT_SINGLE_TVG);
	S32 trans = MnTST_PrGet_CH_Value(ich, MnTST_OPT_SINGLE_ECHO_AMP_B);
	U16 empty = MnMSR_BaseGet_Ch_Value(ich, MnMS0_OPT_SINGLE_EMPTY);
	S32 vca,volt;

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			switch(iFn)
			{
				case ScECO_REAL_ECHO_AMP:	gain = val;	break;
				case ScECO_REAL_TVG:		fTVG = val;	break;
				default:	return;
			}
			break;
		case ScECO_TYPE_AVG:
		default:
			return;
		
	}

	

	if(ScECH_GetLayer() != SCRN_L2_VALU)
		return;

	for(i=0; i<=(empty/20); i++)
	{			
		switch(fTVG)
		{
			case ScCLB_TVG_OFF:		vca = 29;								break;
			default:				vca  = lMsr_aTvg[fTVG-1][i];			break;
		}
		
		volt = (vca*gain)+trans;
		if(volt>DAC_CON_DIG_MAX)	volt = DAC_CON_DIG_MAX;
		if(volt<0)					volt = 0;
		y0[i] = DpECO_TRHD_000-(((DpECO_GRP_HT-10)*volt)/DAC_CON_DIG_MAX);
		x0[i] =  ((i*20*DpECO_GRP_WD_CURSOR_10)/(empty))+DpECO_GRP_X0;
		if(x0[i]>(DpECO_GRP_X0+DpECO_GRP_WD))	return;
		if(x0[i]<0)	return;

		if(y0[i] < (DpECO_TRHD_000-(DpECO_GRP_HT-10)))	return;
		if(y0[i] > DpECO_TRHD_000)	return;
		DpFIG_DrwCirc(x0[i]+3, y0[i], 3, _cCLB_GAIN_CIRC, _F_T);
		
		if(i > 0)	DpFIG_DrwLine(x0[i-1], y0[i-1], x0[i], y0[i], _cCLB_GAIN_LINE);
	}
}

void DpEcoGrp_FgrAsfBar(U08 iCh, U16 x0, U16 thd)
{
#if 0
	U16 asf = ScEC2_GetValue();
	F32 y0;

	switch(MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_THR_HEAVY))
	{
		case MnMS0_IV0_AUTO:	
			y0 = DpECO_TRHD_100+(DpECO_GRP_HT-(DpECO_GRP_HT*(F32)((F32)thd/ADC_VAL_MAX)));
			break;
		case MnMS0_IV0_MANUAL:	
			y0 = DpECO_TRHD_100+(DpECO_GRP_HT-(DpECO_GRP_HT*(F32)((F32)thd/ADC_VAL_MAX)));
			break;
		default:				
			break;
	}

	if(ScECH_GetLayer() != SCRN_L2_VALU)
		return;

	if(ScEC1_GetIdxFunc() != ScECO_F01_ASF_VL)
		return;

	DpFIG_DrwRect(x0+DpECO_GRP_X0, y0-8, asf, 8, _cECO_LN_H_ASF_, DpFIG_FILL);
#endif
}

void DpEcoGrp_FgrTrWidBar(U08 iCh, U16 x0, U16 thd)
{
#if 0
	U16 wid = ScEC2_GetValue();
	F32 y0;

	switch(MnMSR_BaseGet_Ch_Value(iCh, MnMS1_I))



	if(ScECH_GetLayer() != SCRN_L2_VALU)
		return;

	if(ScEC1_GetIdxFunc() != ScECO_F02_TR_WID)
		return;

	//DpFIG_DrwRect(DpECO_GRP_X0, y0, DpECO_GRP_WD, 8, _cBGD_SCRN,      DpFIG_FILL);
	DpFIG_DrwRect(x0+DpECO_GRP_X0-wid,  y0-8, wid*2,        8, _cECO_LN_H_D_WD, DpFIG_FILL);
#endif
}

void DpEcoGrp_FgrTrhdTria(U08 iCh, U32 thd, U16 type)
{
	F32 thr_max = MsCAL_GetVl_Threshold_Max(iCh);
	F32 thr_min = MsCAL_GetVl_Threshold_Min(iCh);
	F32 thr_range =  thr_max-thr_min;
	S16 val = ScEC2_GetValue();
	U08 ifn = ScEC1_GetIdxFunc();
	U08 page = SCRN_GetPage();
	U16 x0;	
	U16 y0;
	F32 y0_t;
	U08 thr_mod;
	U16 i;
	
	switch(type)
	{
		case MsCAL_THR_LIGHT:	
			thr_mod =  MnMSR_CalGet_Ch_Value(iCh, MnMS1_OPT_SINGLE_THR_LIGHT);
			break;
		case MsCAL_THR_HEAVY:	
			thr_mod =  MnMSR_CalGet_Ch_Value(iCh, MnMS1_OPT_SINGLE_THR_HEAVY);				
			break;
		default:				
			break;
	}


	switch(thr_mod)
	{
		case MnMS1_THRESHOLD_AUTO:
			val = thr_min+((thr_range*val)/100);

			if(ScECH_GetSave()==ScECO_SAVE_ON)
			{
				val = MsCAL_FIELD_THR;
				thd = MsCAL_FIELD_THR;
			}
			if(val>4095)	val = 4095;
			if(val<0) val = 0;
			y0 = DpECO_GRP_Y0+(DpECO_GRP_HT-(val/16));
			y0_t = DpECO_GRP_Y0+(DpECO_GRP_HT-(thd/16));	
			break;
		case MnMS1_THRESHOLD_MANUAL:
			val = (ADC_VAL_MAX * val)/33;
			
			if(ScECH_GetSave()==ScECO_SAVE_ON)
			{
				val = MsCAL_FIELD_THR;
				thd = MsCAL_FIELD_THR;
			}

			if(val>4095)	val = 4095;
			if(val<0) val = 0;

			y0 = DpECO_GRP_Y0+(DpECO_GRP_HT-(val/16));
			y0_t = DpECO_GRP_Y0+(DpECO_GRP_HT-(thd/16));
			break;			
	}
	

	switch(page)
	{
		case SCRN_P2_ECHO:		x0 = DpECO_GRP_X0;	break;
		case SCRN_P4_TREND:		x0 = DpCLB_GRP_X0;	break;
		default:									return;
	}

	switch(ScECH_GetLayer())
	{
		case SCRN_L2_VALU:
			if(ScECH_GetType() == ScECO_TYPE_AVG)
			{		
				switch(ifn)
				{
					case ScECO_AVG_THR_LIGHT:	
						if(type !=MsCAL_THR_LIGHT)	break;
						
						for(i=x0; i<(x0+DpECO_GRP_WD-4); i+=4)
						{
							DpFIG_DrwLinH(i, y0, 2, _cSD_WHITE);
						}
						break;
					case ScECO_AVG_THR_HEAVY:
						if(type !=MsCAL_THR_HEAVY)	break;
						
						for(i=x0; i<(x0+DpECO_GRP_WD-4); i+=4)
						{
							DpFIG_DrwLinH(i, y0, 2, _cSD_ORANGE);
						}
						break;
					case ScECO_AVG_ASF_LIGHT:							
						if(type == MsCAL_THR_LIGHT)
						{
							for(i=x0; i<(x0+DpECO_GRP_WD-4); i+=4)
							{
								DpFIG_DrwLinH(i, (U16)y0_t, 2, _cSD_WHITE);
							}
						}
						break;
					case ScECO_AVG_ASF_HEAVY:							
						if(type == MsCAL_THR_HEAVY)
						{
							for(i=x0; i<(x0+DpECO_GRP_WD-4); i+=4)
							{
								DpFIG_DrwLinH(i, (U16)y0_t, 2, _cSD_ORANGE);
							}
						}
						break;							
					default:
						break;
				}
				break;
			}
			break;
		default:
			switch(type)
			{
				case MsCAL_THR_LIGHT:		
					for(i=x0; i<(x0+DpECO_GRP_WD-4); i+=4)
					{
						DpFIG_DrwLinH(i, y0_t, 2, _cSD_WHITE);
					}
					break;
				case MsCAL_THR_HEAVY:	
					for(i=x0; i<(x0+DpECO_GRP_WD-4); i+=4)
					{
						DpFIG_DrwLinH(i, y0_t, 2, _cSD_ORANGE);
					}
					break; 
				default:				
					break;
			}	
			break;
	}
}




void DpECO_ASFValue(void)
{
#if 1
	if(ScECH_GetLayer() != SCRN_L2_VALU)
		return;
	U08 screen_type = ScECH_GetType();
	U08 ch = ScECH_PrGet_Chnnl();
	U08 ifn = ScEC1_GetIdxFunc();
	U16 val;
	
	switch(screen_type)
	{
		case ScECO_TYPE_REAL:	return;
		case ScECO_TYPE_AVG:
			switch(ifn)
			{
				case ScECO_AVG_THR_LIGHT:	return;
				case ScECO_AVG_THR_HEAVY:	return;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:
					switch(ScEC2_GetMode())
					{
						case SCRN_L2_UPDN_DIG:			val = MsCAL_GetVl_ASF_R(ch);	break;
						case SCRN_L2_UPDN_DIG_VALUE:	val = ScEC2_GetValue();			break;
					}		
					break;					
				default:
					break;
			}
			break;			
		default:
			return;
	}	



	DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0-10, 180, 180, _cBGD_SCRN, DpFIG_FILL);	// Clean
	_SPRINTF(lDpEco.pStr[0], "P : ");
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0, _cSD_ORANGE, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);
	_SPRINTF(lDpEco.pStr[0], "R : ");
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0+60, _cSD_ORANGE, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);
	_SPRINTF(lDpEco.pStr[0], "H : ");
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0+120, _cSD_ORANGE, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);

	if(ifn == ScECO_AVG_ASF_LIGHT)
		_SPRINTF(lDpEco.pStr[0], "%d",MnMSR_CalGet_Ch_Value(ch,MnMS1_OPT_SINGLE_ASF_LIGHT));
	if(ifn == ScECO_AVG_ASF_HEAVY)
		_SPRINTF(lDpEco.pStr[0], "%d",MnMSR_CalGet_Ch_Value(ch,MnMS1_OPT_SINGLE_ASF_HEAVY));


	DpFIG_DrwRect(DpECO_LVL_VALU_X0+30, DpECO_LVL_VALU_Y0, DpECO_LVL_VALU_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0+30, DpECO_LVL_VALU_Y0, _cSD_ORANGE, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);	

	_SPRINTF(lDpEco.pStr[0], "%d",val);

	DpFIG_DrwRect(DpECO_LVL_VALU_X0+30, DpECO_LVL_VALU_Y0+60, DpECO_LVL_VALU_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0+30, DpECO_LVL_VALU_Y0+60, _cSD_ORANGE, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);	


	_SPRINTF(lDpEco.pStr[0], "%d",MsCAL_GetVl_ASF_H(ch));

	DpFIG_DrwRect(DpECO_LVL_VALU_X0+30, DpECO_LVL_VALU_Y0+120, DpECO_LVL_VALU_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0+30, DpECO_LVL_VALU_Y0+120, _cSD_ORANGE, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);	
#endif
}

void DpECO_ASFDraw(void)
{
#if 1
	if(ScECH_GetLayer() != SCRN_L2_VALU)
		return;
	U16 x0;

	U08 screen_type = ScECH_GetType();
	U08 ifn = ScEC1_GetIdxFunc();
	U16 val = ScEC2_GetValue();
	U08 ch = ScECH_PrGet_Chnnl();
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 dead = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);
	U16 ht_a = DpECO_GRP_HT;
	U16 y0_a = DpECO_GRP_Y0;

	switch(screen_type)
	{
		case ScECO_TYPE_REAL:	return;
		case ScECO_TYPE_AVG:
			switch(ifn)
			{
				case ScECO_AVG_THR_LIGHT:	return;
				case ScECO_AVG_THR_HEAVY:	return;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:
					switch(ScEC2_GetMode())
					{
						case SCRN_L2_UPDN_DIG:			lDpEco.asf_x[ch] = val;	break;
						case SCRN_L2_UPDN_DIG_VALUE:	break;
					}		
					break;
				default:
					break;
			}
			break;			
		default:
			return;
	}	

	if(lDpEco.asf_x[ch] > empty) lDpEco.asf_x[ch] = empty;
	if(lDpEco.asf_x[ch] < dead)	lDpEco.asf_x[ch] = dead;
	x0 = (lDpEco.asf_x[ch]*DpECO_GRP_WD_CURSOR_10)/(empty);
	
	DpFIG_DrwLinV(x0+DpECO_GRP_X0, y0_a, ht_a, _cSD_ORANGE);
	DpFIG_DrwLinV(x0+DpECO_GRP_X0+1, y0_a, ht_a, _cSD_ORANGE);
	DpFIG_DrwLinV(x0+DpECO_GRP_X0+2, y0_a, ht_a, _cSD_ORANGE);

	DpFIG_DrwRect(DpECO_GRP_X0, y0_a-40, DpECO_GRP_WD, 30, _cBGD_SCRN, 0);
	DpSTR_GuiLeft(x0+DpECO_GRP_X0-15, y0_a-25, _cSD_ORANGE, _cBGD_SCRN, _fE12HsM, "ASF");

	DpECO_ASFValue();
#endif
}

#if 1
void DpEcoGrp_FgrSignal(U08 iCh, U16 i,U16 empty,U16 d_zn,U16 range, U08 type)
{
	U16 ht_v0;
	U16 y0_v;
	U16 x0,x1;
	U16 x_range=1;
	U16 n;


	if(empty<=d_zn)	return;



	if(range>DpECO_GRP_WD)
	{
		x0 = (i*DpECO_GRP_WD_CURSOR_10)/(empty);
		if(i!=0) 	x1 = ((i-1)*DpECO_GRP_WD_CURSOR_10)/(empty);
		x_range = x0-x1;


		if(ScECH_GetSave()==ScECO_SAVE_OFF)
		{
			switch(type)
			{
				case ScECO_TYPE_AVG:	
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_EchoBuff(iCh, i) / 16;
					else 
						ht_v0 = 0;
					break;
				case ScECO_TYPE_REAL: 
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_EchoReal(iCh, i) / 16;
					else
						ht_v0 = 0;
					break;
				default:	
					break;
			}
		}
		else if (ScECH_GetSave()==ScECO_SAVE_ON)
		{
			switch(type)
			{
				case ScECO_TYPE_AVG:	
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_FieldBuff(iCh, i) / 16;
					else 
						ht_v0 = 0;
					break;
				case ScECO_TYPE_REAL: 
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_FieldReal(iCh, i) / 16;
					else
						ht_v0 = 0;
					break;
				default:	
					break;
			}
		}
		
		y0_v = DpECO_GRP_Y0 + (DpECO_GRP_HT - ht_v0);

		if(x_range!=0)
		{
			DpFIG_DrwLinV(DpECO_GRP_X0+x0, DpECO_GRP_Y0, DpECO_GRP_HT, _cTTB_BG_MID);
			if	((i < d_zn)  && (i < (empty)))						DpFIG_DrwLinV(x0+DpECO_GRP_X0, y0_v, ht_v0, _cECO_LN_V_DDZN);
			else if ((i > d_zn)  && (i > (empty)))					DpFIG_DrwLinV(x0+DpECO_GRP_X0, y0_v, ht_v0, _cSD_DARKGRAY);
			else													DpFIG_DrwLinV(x0+DpECO_GRP_X0, y0_v, ht_v0, _cECO_LN_V_SLDG);
		}
	}
	else
	{
		x0 = (i*DpECO_GRP_WD_CURSOR_10)/(empty);
		if(i!=range)	x1 = ((i+1)*DpECO_GRP_WD_CURSOR_10)/(empty);
		x_range = x1-x0;

		if(ScECH_GetSave()==ScECO_SAVE_OFF)
		{
			switch(type)
			{
				case ScECO_TYPE_AVG:	
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_EchoBuff(iCh, i) / 16;
					else 
						ht_v0 = 0;
					break;
				case ScECO_TYPE_REAL: 
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_EchoReal(iCh, i) / 16;
					else
						ht_v0 = 0;
					break;
				default:	
					break;
			}
		}
		else if (ScECH_GetSave()==ScECO_SAVE_ON)
		{
			switch(type)
			{
				case ScECO_TYPE_AVG:	
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_FieldBuff(iCh, i) / 16;
					else 
						ht_v0 = 0;
					break;
				case ScECO_TYPE_REAL: 
					if(i<=ADC_BUFF_MAX)
						ht_v0 = MsCAL_GetVl_FieldReal(iCh, i) / 16;
					else
						ht_v0 = 0;
					break;
				default:	
					break;
			}
		}

		y0_v = DpECO_GRP_Y0 + (DpECO_GRP_HT - ht_v0);

		for(n=0; n<x_range; n++)
		{
			DpFIG_DrwLinV(DpECO_GRP_X0+x0+n, DpECO_GRP_Y0, DpECO_GRP_HT, _cTTB_BG_MID);
			if	((i < d_zn)  && (i < (empty)))						DpFIG_DrwLinV(x0+DpECO_GRP_X0+n, y0_v, ht_v0, _cECO_LN_V_DDZN);
			else if ((i > d_zn)  && (i > (empty)))					DpFIG_DrwLinV(x0+DpECO_GRP_X0+n, y0_v, ht_v0, _cSD_DARKGRAY);
			else													DpFIG_DrwLinV(x0+DpECO_GRP_X0+n, y0_v, ht_v0, _cECO_LN_V_SLDG);
		}
	}	
}
#endif

void DpEcoGrp_DrawLive(U08 range)
{
	U16 i;
	U08 iCh = ScECH_PrGet_Chnnl();
	U16 c;
	U32 thd;
	U16 thd_asf = MsCAL_GetVl_Threshold(iCh, MsCAL_THR_LIGHT);
	U16 ht_a = DpECO_GRP_HT;
	U16 y0_a = DpECO_GRP_Y0;
	U16 x0[MsCAL_THR_TYPE_NUM];
	U16 x1;
	U16 dist[MsCAL_THR_TYPE_NUM];
	U16 empty = (U16)MnMSR_BaseGet_Ch_Value(iCh,MnMS0_OPT_SINGLE_EMPTY);
	U16 d_zn = (U16)MnMSR_BaseGet_Ch_Value(iCh,MnMS0_OPT_SINGLE_DEADZONE);
	U08 screen_type = ScECH_GetType();
	U16 msr_range = (empty*110)/100;
	U16 val;

	if(empty<=d_zn)	return;

	if(ScECH_GetLayer() == SCRN_L2_VALU)
	{
		if(screen_type==ScECO_TYPE_REAL)
		{
			if(ScEC1_GetIdxFunc()==ScECO_REAL_EMPTY)
			{
				empty = ScEC2_GetValue();	
				msr_range = (empty*110)/100;
				DpFIG_DrwRect(DpECO_GRP_X0-20, DpECO_GRP_Y0 + DpECO_GRP_HT + 4+10, DpECO_GRP_WD, 35, _cBGD_SCRN, 0);
				for(i=0; i<12; i++)
				{
					if(i<11)
					{
						val = empty-((empty*i)/10);
						if(val>=1000)	_SPRINTF(lDpEco.pStr[0], "%02d.%02d",val/100,val%100);
						else			_SPRINTF(lDpEco.pStr[0], "%01d.%02d",val/100,val%100);
						DpSTR_GuiLeft(DpECO_GRP_X0+ (DpECO_GRP_WD_CURSOR*i)-18, DpECO_GRP_Y0 + DpECO_GRP_HT + 4+10, _cECO_AMP_STD, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);
					}	
				}
			

			}
			if(ScEC1_GetIdxFunc()==ScECO_REAL_DEADZONE)
			{
				d_zn = ScEC2_GetValue();	
			}			
		}
	}


	for(i=0; i<=msr_range; i++)
	{
		DpEcoGrp_FgrSignal(iCh, i, empty,d_zn,msr_range,screen_type);
	}


	if((ScECH_GetLayer() == SCRN_L2_VALU) && (ScECH_GetType() == ScECO_TYPE_AVG) && (ScEC2_GetMode()==SCRN_L2_UPDN_DIG))
	{
		if(ScEC1_GetIdxFunc()==ScECO_AVG_ASF_LIGHT)	
		{
			thd_asf = MsCAL_GetVl_Threshold(iCh, MsCAL_THR_LIGHT);
			for(i=0; i<=msr_range; i++)
			{
				if(i>=d_zn)
				{
					c = CalPrc_GetAsfCnt(iCh, i, thd_asf);
					i+=c;
				}
			}

		}
		
		if(ScEC1_GetIdxFunc()==ScECO_AVG_ASF_HEAVY)
		{
			thd_asf = MsCAL_GetVl_Threshold(iCh, MsCAL_THR_HEAVY);
			for(i=0; i<=msr_range; i++)
			{
				if(i>=d_zn)
				{
					c = CalPrc_GetAsfCnt(iCh, i, thd_asf);
					i+=c;
				}
			}
		}
	}
	
	DpFIG_DrwRect(DpECO_GRP_X0, y0_a-40, DpECO_GRP_WD, 35, _cBGD_SCRN, 0);


	x1 = (d_zn*DpECO_GRP_WD_CURSOR_10)/(empty);
	if((x1<=DpECO_GRP_WD_CURSOR_10))
	{
		DpFIG_DrwLinV(x1+DpECO_GRP_X0, y0_a, ht_a, _cECO_LN_V_DZ_L);
		DpFIG_DrwLinV(x1+DpECO_GRP_X0, y0_a, ht_a, _cECO_LN_V_DZ_L);
	}
	
	x1 = DpECO_GRP_WD_CURSOR_10;
	if((x1<=DpECO_GRP_WD_CURSOR_10))
	{
		DpFIG_DrwLinV(x1+DpECO_GRP_X0, y0_a, ht_a, _cSD_LIGHTGRAY); 
	}	


	DpEcoGrp_LineTvg();
	DpECO_ASFDraw();

	for(i=0; i<MsCAL_THR_TYPE_NUM;	i++)
	{
		thd = MsCAL_GetVl_Threshold(iCh, i);

		// Threshold
		DpEcoGrp_FgrTrhdTria(iCh, thd,i);

		switch(screen_type)
		{
			case ScECO_TYPE_REAL:	break;
			case ScECO_TYPE_AVG:
			default:
				if(ScECH_GetLayer() == SCRN_L2_VALU)
				{
					if((ScEC1_GetIdxFunc()==ScECO_AVG_ASF_LIGHT) || (ScEC1_GetIdxFunc()==ScECO_AVG_ASF_HEAVY))
						break;
				}

				dist[i] = MsCAL_GetVl_TracDist(iCh, i);

				if(ScECH_GetSave()==ScECO_SAVE_ON)
					dist[i]  = MsCAL_GetVl_FieldDist(iCh);		
				
				if(dist[i] > empty)	dist[i] = empty;
				if(dist[i] < d_zn)	break;
				x0[i] = (dist[i]*DpECO_GRP_WD_CURSOR_10)/(empty);
				
				switch(i)
				{
					case MsCAL_THR_LIGHT:
						DpFIG_DrwLinV(x0[i]+DpECO_GRP_X0, y0_a, ht_a, _cSD_WHITE);
						DpFIG_DrwLinV(x0[i]+DpECO_GRP_X0+1, y0_a, ht_a, _cSD_WHITE);
						DpFIG_DrwLinV(x0[i]+DpECO_GRP_X0+2, y0_a, ht_a, _cSD_WHITE);
						break;
					case MsCAL_THR_HEAVY:
						DpFIG_DrwLinV(x0[i]+DpECO_GRP_X0, y0_a, ht_a, _cSD_ORANGE);
						DpFIG_DrwLinV(x0[i]+DpECO_GRP_X0+1, y0_a, ht_a, _cSD_ORANGE);
						DpFIG_DrwLinV(x0[i]+DpECO_GRP_X0+2, y0_a, ht_a, _cSD_ORANGE);
						break;				
					default:	
						break;
				}
				break;
		}
	}


	switch(screen_type)
	{
		case ScECO_TYPE_REAL:	break;
		case ScECO_TYPE_AVG:
			if(ScECH_GetLayer() == SCRN_L2_VALU)
			{
				if((ScEC1_GetIdxFunc()==ScECO_AVG_ASF_LIGHT) || (ScEC1_GetIdxFunc()==ScECO_AVG_ASF_HEAVY))
					break;
			}


			if((abs(x0[MsCAL_THR_LIGHT] - x0[MsCAL_THR_HEAVY]))<20)
			{
				if(dist[MsCAL_THR_LIGHT] < d_zn)	break;			
				if(dist[MsCAL_THR_HEAVY] < d_zn)	break;		
				DpSTR_GuiLeft(x0[MsCAL_THR_LIGHT]+DpECO_GRP_X0-5, y0_a-22, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, "L");
				DpSTR_GuiLeft(x0[MsCAL_THR_HEAVY]+DpECO_GRP_X0-5, y0_a-35, _cSD_ORANGE, _cBGD_SCRN, _fE12HsM, "H");
			}
			else
			{
				if(dist[MsCAL_THR_LIGHT] < d_zn)	break;			
				if(dist[MsCAL_THR_HEAVY] < d_zn)	break;				
				DpSTR_GuiLeft(x0[MsCAL_THR_LIGHT]+DpECO_GRP_X0-5, y0_a-22, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, "L");
				DpSTR_GuiLeft(x0[MsCAL_THR_HEAVY]+DpECO_GRP_X0-5, y0_a-22, _cSD_ORANGE, _cBGD_SCRN, _fE12HsM, "H");
			}	
			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Level
//------------------------------------------------------------------------------------------------------------------------------
void DpEcoLvl_StrTitle(void)
{
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);
	I08 pSt0[64] = {0, };

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpEco.pStr[0], _sLight_level);
			
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0, _cLight_level, _cBGD_SCRN, _fE17HsB, lDpEco.pStr[0]);
			_SPRINTF(lDpEco.pStr[0], _sHeavy_level);
			
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0+90, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0+90, _cHeavy_level, _cBGD_SCRN, _fE17HsB, lDpEco.pStr[0]);	
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_LIGHT_LEVEL);
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0, _cLight_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20+145, DpECO_LVL_VALU_Y0, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0); 

			DpSTR_GuiList(TEXT_LIST_HEAVY_LEVEL);
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0+90, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpECO_LVL_VALU_Y0+90, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	
			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20+145, DpECO_LVL_VALU_Y0+90, _cHeavy_level, _cBGD_SCRN, _fE17HsB, pSt0);				
			break;
	}


}

void DpEcoLvl_StrValue(void)
{
	U16 valu_light;
	U16 valu_heavy;
	U08 iCh = ScECH_PrGet_Chnnl();

	switch(MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_OPERATION))
	{
		case MnMS0_OPERATION_SLUDGE:	
			valu_light = MsCAL_GetVl_RsltSldg(iCh,MsCAL_THR_LIGHT);		
			valu_heavy = MsCAL_GetVl_RsltSldg(iCh,MsCAL_THR_HEAVY);
			break;
		case MnMS0_OPERATION_DISTANCE:	
			valu_light = MsCAL_GetVl_RsltDist(iCh,MsCAL_THR_LIGHT);	
			valu_heavy = MsCAL_GetVl_RsltDist(iCh,MsCAL_THR_HEAVY);	
			break;
		default:				
			break;
	}


	if(ScECH_GetSave()==ScECO_SAVE_ON)
	{
		valu_heavy = MsCAL_GetVl_FieldSldg(iCh);
		valu_light = MsCAL_GetVl_FieldSldg(iCh);
	}
#if 0
	if(ScHYB_PrGet_Unit_() == ScHYB_UNIT_FEET)
		valu = (U16)MsCAL_Meter2Feet(valu);
#endif

	if(valu_light >= 1000)	_SPRINTF(lDpEco.pStr[0], "%2d.%02d", valu_light/100, valu_light%100);
	else					_SPRINTF(lDpEco.pStr[0], "%1d.%02d", valu_light/100, valu_light%100);

	DpFIG_DrwRect(DpECO_LVL_VALU_X0+10, DpECO_LVL_VALU_Y0+30, DpECO_LVL_VALU_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0+10, DpECO_LVL_VALU_Y0+30, _cLight_level, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);	

	if(valu_heavy >= 1000)	_SPRINTF(lDpEco.pStr[0], "%2d.%02d", valu_heavy /100, valu_heavy %100);
	else					_SPRINTF(lDpEco.pStr[0], "%1d.%02d", valu_heavy /100, valu_heavy %100);


	DpFIG_DrwRect(DpECO_LVL_VALU_X0+10, DpECO_LVL_VALU_Y0+120, DpECO_LVL_VALU_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0+10, DpECO_LVL_VALU_Y0+120, _cHeavy_level, _cBGD_SCRN, _fE35HsB, lDpEco.pStr[0]);
}

void DpEcoLvl_StrUnit(void)
{
#if 0
	I08 sUni[8]  = {0, };
	U08 unit = ScHYB_PrGet_Unit_();

	if(unit == ScHYB_UNIT_METER)		_SPRINTF(sUni, "m");
	else								_SPRINTF(sUni, "ft");
	DpSTR_GuiLeft(DpECO_LVL_UNIT_X0, DpECO_LVL_UNIT_Y0, _cECO_LVL_TITL, _cBGD_SCRN, _fE35HsB, sUni);
#endif
}

void DpEcoLvl_StrChnnl(void)
{
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);
	U16 val;
	U08 ch = ScECH_PrGet_Chnnl();

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE)
		return;

	switch(ch)
	{
		case APP_CH_1:		_SPRINTF(lDpEco.pStr[0], _sCH_1);	DpSTR_GuiList(TEXT_LIST_CH_1);	break;
		case APP_CH_2:		_SPRINTF(lDpEco.pStr[0], _sCH_2);	DpSTR_GuiList(TEXT_LIST_CH_2);	break;
	}



	switch(lang)
	{
		case MnSYS_LANG_ENG:
			DpFIG_DrwRect(DpECO_LVL_TITL_X0+40, DpECO_GRP_Y0-35, DpECO_LVL_CH_WD+10, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL); // Clear
			DpSTR_GuiLeft(DpECO_LVL_TITL_X0+40, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, lDpEco.pStr[0]);
			break;
		case MnSYS_LANG_KOR:
			DpFIG_DrwRect(DpECO_LVL_TITL_X0+40,  DpECO_GRP_Y0-35, DpECO_LVL_CH_WD+10, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+40, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);						
			break;
	}	

	val = MnSYS_PrGet_site_name(ch);

	_SPRINTF(lDpEco.pStr[0], "(%c%d%d)",val/100,(val%100)/10,(val%100)%10);


	DpFIG_DrwRect(DpECO_LVL_TITL_X0+40+70+20, DpECO_GRP_Y0-35, DpECO_LVL_CH_WD+10, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpECO_LVL_TITL_X0+40+70+20, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, lDpEco.pStr[0]);

	DpFIG_DrwLinH(DpECO_LVL_TITL_X0, DpECO_GRP_Y0, DpECO_BOX_FG_WD, _cSD_WHITE);
}




//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Layer
//------------------------------------------------------------------------------------------------------------------------------
void DpEcoLyr_StrUpdat(void)
{
#if 0
	U08 val = ScECH_PrGet_Value(ScECH_PrGet_Chnnl(),ScECO_H00_SCREEN_TYPE);
	// Title
	DpSTR_GuiLeft(DpECO_LYR_TITL_X0, DpECO_LYR_TITL_Y0, _cECO_LVL_VALU, _cBGD_SCRN, _fE17HsB, _sReal_Avg);

	DpFIG_DrwRect(DpECO_LYR_VALU_X0, DpECO_LYR_VALU_Y0, DpECO_LVL_CH_WD+20, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear

	switch(val)
	{
		case ScECO_SCREEN_REAL:		DpSTR_GuiLeft(DpECO_LYR_VALU_X0, DpECO_LYR_VALU_Y0, _cECO_BOX_TITL, _cBGD_SCRN, _fE17HsB, _sReal);	break;
		case ScECO_SCREEN_AVG:		DpSTR_GuiLeft(DpECO_LYR_VALU_X0, DpECO_LYR_VALU_Y0, _cECO_BOX_TITL, _cBGD_SCRN, _fE17HsB, "Avg.");	break;
		default:					break;
	}
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Parameter Box - List
//------------------------------------------------------------------------------------------------------------------------------
void DpEcoBox_LstTitle(U08 iFn)
{
	U08 page;
	U16 x0s = DpECO_BOX_L0_TL_X0;
	U16 w_c = DpECO_BOX_Lx_SB_WD;
	U16 h_c = DpECO_BOX_Lx_SB_HT;
	U16 y0s;
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);

	if(ScEC1_GetIdxFunc()<ScECO_FNC_PAGE)
	{
		page =DpECO_PG_0;	
	}
	else if(ScEC1_GetIdxFunc()>=ScECO_FNC_PAGE)
	{
		page =DpECO_PG_1;
	}


	#if 0
	if		(iFn >= (ScECO_FNC_PAGE*2))		page = DpECO_PG_2;
	else if (iFn >= (ScECO_FNC_PAGE*1))		page = DpECO_PG_1;
	else									page = DpECO_PG_0;
	#endif
	
	y0s = 270 + (DpECO_BOX_Lx_SB_HT * (iFn - (4*page)));

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			switch(ScECH_GetType())
			{
				case ScECO_TYPE_REAL:
					switch(iFn)
					{	// Page #0
						case ScECO_REAL_ECHO_AMP:		_SPRINTF(lDpEco.pStr[0], _sEcho_Amp);		break;
						case ScECO_REAL_MEAS_RESET:		_SPRINTF(lDpEco.pStr[0], _sMeasure_reset);	break;
						case ScECO_REAL_FREQ:			_SPRINTF(lDpEco.pStr[0], _sFrequency);		break;
						case ScECO_REAL_EMPTY:			_SPRINTF(lDpEco.pStr[0], _sEmpty);			break;
						case ScECO_REAL_DEADZONE:		_SPRINTF(lDpEco.pStr[0], _sDeadzone);		break;
						case ScECO_REAL_TVG:			_SPRINTF(lDpEco.pStr[0], _sTVG);			break;
						default:						break;
					}
					break;
				case ScECO_TYPE_AVG:
					switch(iFn)
					{	// Page #0
						case ScECO_AVG_THR_LIGHT:		_SPRINTF(lDpEco.pStr[0], _sThr_light);	break;
						case ScECO_AVG_THR_HEAVY:		_SPRINTF(lDpEco.pStr[0], _sThr_heavy);	break;
						case ScECO_AVG_ASF_LIGHT:		_SPRINTF(lDpEco.pStr[0], _sASF_LIGHT);	break;
						case ScECO_AVG_ASF_HEAVY:		_SPRINTF(lDpEco.pStr[0], _sASF_HEAVY);	break;
						default:						break;
					}
					break;			
			}			
			DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);		
			break;
		case MnSYS_LANG_KOR:
			DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
			switch(ScECH_GetType())
			{
				case ScECO_TYPE_REAL:
					switch(iFn)
					{	// Page #0
						case ScECO_REAL_ECHO_AMP:		DpSTR_GuiList(TEXT_LIST_ECHO_AMP);	break;
						case ScECO_REAL_MEAS_RESET:		DpSTR_GuiList(TEXT_LIST_MSR_RST);	break;
						case ScECO_REAL_FREQ:			DpSTR_GuiList(TEXT_LIST_FREQ);	break;
						case ScECO_REAL_EMPTY:			DpSTR_GuiList(TEXT_LIST_EMPTY);	break;
						case ScECO_REAL_DEADZONE:		DpSTR_GuiList(TEXT_LIST_DEADZONE);	break;
						case ScECO_REAL_TVG:
							_SPRINTF(lDpEco.pStr[0], _sTVG);
							DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
							DpSTR_GuiLeft(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);		
							return;
						default:						break;
					}
					break;
				case ScECO_TYPE_AVG:
					switch(iFn)
					{	// Page #0
						case ScECO_AVG_THR_LIGHT:		DpSTR_GuiList(TEXT_LIST_THR_LIGHT);	break;
						case ScECO_AVG_THR_HEAVY:		DpSTR_GuiList(TEXT_LIST_THR_HEAVY);	break;
						case ScECO_AVG_ASF_LIGHT:	
							DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
							DpSTR_GuiList(TEXT_LIST_LIGHT);
							DpSTR_GuiLeft_KOR(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);
							_SPRINTF(lDpEco.pStr[0], _sASF);		
							DpSTR_GuiLeft(x0s+60, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);
							return;
						case ScECO_AVG_ASF_HEAVY:	
							DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
							DpSTR_GuiList(TEXT_LIST_HEAVY);
							DpSTR_GuiLeft_KOR(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);
							_SPRINTF(lDpEco.pStr[0], _sASF);		
							DpSTR_GuiLeft(x0s+60, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);
							return;							
						default:						break;
					}				
					break;			
			}		
			DpSTR_GuiLeft_KOR(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);
			break;
	}




}

void DpEcoBox_LstValue(U08 iFn, S32 val)
{
	U08 page;
	U16 y0c, y0s;
	U16 x0c = DpECO_BOX_L0_VL_X0;
	U16 x0s = DpECO_BOX_L0_VL_X0;
	U32 col = _cECO_BOX_VALU;
	sFONT sFt = _fE12HsM;
	U08 iCh = ScECH_PrGet_Chnnl();
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);


	if(ScEC1_GetIdxFunc()<ScECO_FNC_PAGE)
	{
		page =DpECO_PG_0;	
	}
	else if(ScEC1_GetIdxFunc()>=ScECO_FNC_PAGE)
	{
		page =DpECO_PG_1;
	}


	y0c = 270 + (DpECO_BOX_Lx_SB_HT * (iFn - (4*page)));
	y0s = 270 + (DpECO_BOX_Lx_SB_HT * (iFn - (4*page)));


	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			switch(iFn)
			{
				case ScECO_REAL_ECHO_AMP:	_SPRINTF(lDpEco.pStr[0], ": %d", val);		break;
				case ScECO_REAL_MEAS_RESET:	_SPRINTF(lDpEco.pStr[0], ": -");			break;
				case ScECO_REAL_FREQ:		
					switch(val)
					{
						case MnMS1_FREQ_130K:	_SPRINTF(lDpEco.pStr[0], ": 130");		break;
						case MnMS1_FREQ_160K:	_SPRINTF(lDpEco.pStr[0], ": 160");		break;
						case MnMS1_FREQ_270K:	_SPRINTF(lDpEco.pStr[0], ": 270");		break;
						case MnMS1_FREQ_380K:	_SPRINTF(lDpEco.pStr[0], ": 380");		break;
						default:				break;
					}
					break;
				case ScECO_REAL_EMPTY:		_SPRINTF(lDpEco.pStr[0], ": %d.%02d", (U16)(val/100), (U16)(val%100));	break;
				case ScECO_REAL_DEADZONE:	_SPRINTF(lDpEco.pStr[0], ": %d.%02d", (U16)(val/100), (U16)(val%100));	break;
				case ScECO_REAL_TVG:		
					if(val == MnEGN_TVG_MIN)
					{
						if(lang == MnSYS_LANG_ENG)
							_SPRINTF(lDpEco.pStr[0], "OFF");
						else
						{
							DpFIG_DrwRect(x0c, y0c, 60, 20, _cBGD_SCRN, DpFIG_FILL);
							_SPRINTF(lDpEco.pStr[0], ":");	
							DpSTR_GuiLeft(x0s, y0s, col, _cBGD_SCRN, sFt, lDpEco.pStr[0]);
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft_KOR(x0s+5, y0s, col, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);			
							return;
						}
					}
					else
						_SPRINTF(lDpEco.pStr[0], ": %d", val);
					break;
				default:					return;
			}
			break;
		case ScECO_TYPE_AVG:
			switch(iFn)
			{	// Page #0
				case ScECO_AVG_THR_LIGHT:		
					switch(MnMSR_CalGet_Ch_Value(iCh, MnMS1_OPT_SINGLE_THR_LIGHT))
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpEco.pStr[0], ": %d%c", val,37);		break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpEco.pStr[0], ": %01d.%1dv", (U16)(val/10), (U16)(val%10));		break;
					}
					break;
				case ScECO_AVG_THR_HEAVY:
					switch(MnMSR_CalGet_Ch_Value(iCh, MnMS1_OPT_SINGLE_THR_HEAVY))
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(lDpEco.pStr[0], ": %d%c", val,37);		break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(lDpEco.pStr[0], ": %01d.%1dv", (U16)(val/10), (U16)(val%10));		break;
					}
					break;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:				_SPRINTF(lDpEco.pStr[0], ": %d", val);		break;
				default:						break;
			}
			break;				
	}


	DpFIG_DrwRect(x0c, y0c, 60, 20, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(x0s, y0s, col, _cBGD_SCRN, sFt, lDpEco.pStr[0]);
}

void DpEcoBox_LstAll(void)
{
	U08 i, page, num,end;
	U08 iCh = ScECH_PrGet_Chnnl();
	S32 val[16] = {0, };

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			num = ScECO_REAL_NUM;
			val[ScECO_REAL_ECHO_AMP] = MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_ECHO_AMP);
			val[ScECO_REAL_MEAS_RESET] = 0;
			val[ScECO_REAL_FREQ] = MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_FREQ);
			val[ScECO_REAL_EMPTY] = MnMSR_BaseGet_Ch_Value(iCh,MnMS0_OPT_SINGLE_EMPTY);
			val[ScECO_REAL_DEADZONE] = MnMSR_BaseGet_Ch_Value(iCh,MnMS0_OPT_SINGLE_DEADZONE);
			val[ScECO_REAL_TVG] = MnEGN_PrGet_CH_Item(iCh,MnEGN_OPT_SINGLE_TVG);
			switch(ScECH_GetLayer())
			{
				case SCRN_L2_VALU:	
					val[ScEC1_GetIdxFunc()]   = ScEC2_GetValue();	
					break;
				default:			
					break;
			}
			break;
		case ScECO_TYPE_AVG:
			num = ScECO_AVG_NUM;
			val[ScECO_AVG_THR_HEAVY]   = MnMSR_Get_Threshold_Ch_Value(iCh,MnMS1_OPT_SINGLE_THR_HEAVY);	
			val[ScECO_AVG_THR_LIGHT]   = MnMSR_Get_Threshold_Ch_Value(iCh,MnMS1_OPT_SINGLE_THR_LIGHT);		
			val[ScECO_AVG_ASF_HEAVY]   = MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_ASF_HEAVY);			
			val[ScECO_AVG_ASF_LIGHT]   = MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_ASF_LIGHT);	

			if(ScECH_GetLayer() == SCRN_L2_VALU)
			{
				val[ScEC1_GetIdxFunc()]    = ScEC2_GetValue();
				
				if(ScEC1_GetIdxFunc() == ScECO_AVG_ASF_LIGHT)
				{
					if(ScEC2_GetMode() == SCRN_L2_UPDN_DIG)	
						val[ScECO_AVG_ASF_LIGHT]	= MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_ASF_LIGHT);								
					if(ScEC2_GetMode() == SCRN_L2_UPDN_DIG_VALUE)		
						val[ScECO_AVG_ASF_LIGHT]	= ScEC2_GetValue();	
				}
				
				if(ScEC1_GetIdxFunc() == ScECO_AVG_ASF_HEAVY)
				{
					if(ScEC2_GetMode() == SCRN_L2_UPDN_DIG)	
						val[ScECO_AVG_ASF_HEAVY]	= MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_ASF_HEAVY);								
					if(ScEC2_GetMode() == SCRN_L2_UPDN_DIG_VALUE)		
						val[ScECO_AVG_ASF_HEAVY]	= ScEC2_GetValue();	
				}			
			}
			break;
		default:
			break;
	}


	if(ScEC1_GetIdxFunc()<ScECO_FNC_PAGE)
	{
		page =DpECO_PG_0;	
		if(num>=ScECO_FNC_PAGE)
			end= ScECO_FNC_PAGE;
		else 
			end= num;

	}
	else if(ScEC1_GetIdxFunc()>=ScECO_FNC_PAGE)
	{
		page = DpECO_PG_1;
		if(num>=ScECO_FNC_PAGE+4)
			end= ScECO_FNC_PAGE+4;
		else 
			end= num-4;
	}

	DpFIG_DrwRect(DpECO_BOX_L0_TL_X0-10, 280, DpECO_BOX_Lx_SB_WD+60, 110, _cBGD_SCRN, DpFIG_FILL);

	for(i=1; i<end; i++)
	{
		DpEcoBox_LstTitle(i+(4*page));
		DpEcoBox_LstValue(i+(4*page), val[i+(4*page)]);
	}
}


void DpEcoVal_SetString(U08 iFn, S32 val)
{
#if 0
	switch(iFn)
	{
		// Page #0
		case ScECO_F00_THRSHD:
		case ScECO_F01_ASF_VL:
		case ScECO_F02_TR_WID:			_SPRINTF(lDpEco.pStr[0], "%d", val);		break;
		case ScECO_F03_PROF_N:			_SPRINTF(lDpEco.pStr[0], "%d", val);		break;
		case ScECO_F04_DAMP_N:
			switch(val)
			{
				case ScECO_DAMP_001:	_SPRINTF(lDpEco.pStr[0], "1");				break;
				case ScECO_DAMP_010:	_SPRINTF(lDpEco.pStr[0], "10"); 			break;
				case ScECO_DAMP_030:	_SPRINTF(lDpEco.pStr[0], "30"); 			break;
				case ScECO_DAMP_060:	_SPRINTF(lDpEco.pStr[0], "60"); 			break;
				default:				_SPRINTF(lDpEco.pStr[0], _sNG); 			break;
			}
			break;
		// Page #1
		case ScECO_F05_OFFSET:			_SPRINTF(lDpEco.pStr[0], "%d", val);		break;
		// Dual Sensor
		case ScECO_H00_SCREEN_TYPE:
			break;
			switch(val)
			{
				case ScECO_SCREEN_REAL:	_SPRINTF(lDpEco.pStr[0], _sReal);			break;
				case ScECO_SCREEN_AVG:	_SPRINTF(lDpEco.pStr[0], _sAvg);			break;
				default:				_SPRINTF(lDpEco.pStr[0], _sNG);				break;
			}
			break;
		case ScECO_FNC_NUM:
			switch(ScECH_PrGet_Chnnl())
			{
				case ScECO_CH_0:		_SPRINTF(lDpEco.pStr[0], _sCH_1);			break;
				case ScECO_CH_1:		_SPRINTF(lDpEco.pStr[0], _sCH_2);			break;
			}
			break;
		// Not Yet
		default:						_SPRINTF(lDpEco.pStr[0], _sNG);				break;
	}
#endif
}

void DpEcoL1l_SelBox(void)
{
	U08 i;
	U16 aSl[DpSCR_SBX_aNUMB];
	U08 iFn = ScEC1_GetIdxFunc();
	U08 num = 0;

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:	num = ScECO_REAL_NUM;	break;
		case ScECO_TYPE_AVG:	num = ScECO_AVG_NUM;	break;
		default:										break;
	}

	for(i=0; i<num; i++)
		DpFIG_DrwRect(lDpEco.sbx.aX0[i], lDpEco.sbx.aY0[i], lDpEco.sbx.aWd[i], lDpEco.sbx.aHt[i], _cBGD_SCRN, 2);

	
	aSl[DpSCR_SBX_aX0] = lDpEco.sbx.aX0[iFn];
	aSl[DpSCR_SBX_aY0] = lDpEco.sbx.aY0[iFn];
	aSl[DpSCR_SBX_aWd] = lDpEco.sbx.aWd[iFn];
	aSl[DpSCR_SBX_aHt] = lDpEco.sbx.aHt[iFn];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();
}

void DpEcoL2l_SelBox(void)
{
	U08 i;
	U16 aSl[DpSCR_SBX_aNUMB];
	U08 iFn = ScEC1_GetIdxFunc();
	U08 num = 0;
	if((ScECH_GetType()==ScECO_TYPE_AVG) && (ScEC2_GetMode()==SCRN_L2_UPDN_DIG))
	{
		if((iFn == ScECO_AVG_ASF_HEAVY) || (iFn == ScECO_AVG_ASF_LIGHT))
		{
			DpEcoL1l_SelBox();
			return;
		}
	}	


	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:	num = ScECO_REAL_NUM;	break;
		case ScECO_TYPE_AVG:	num = ScECO_AVG_NUM;	break;
		default:										break;
	}

	
	for(i=0; i<num; i++)
		DpFIG_DrwRect(lDpEco.sbx.aX0[i], lDpEco.sbx.aY0[i], lDpEco.sbx.aWd[i], lDpEco.sbx.aHt[i], _cBGD_SCRN, 2);


	for(i=0; i<num; i++)
		DpFIG_DrwRect(lDpEco.sbx.aX0[i], lDpEco.sbx.aY0[i], lDpEco.sbx.aWd[i], lDpEco.sbx.aHt[i], _cBGD_SCRN, 2);

	
	aSl[DpSCR_SBX_aX0] = lDpEco.sbx.aX0[iFn];
	aSl[DpSCR_SBX_aY0] = lDpEco.sbx.aY0[iFn];
	aSl[DpSCR_SBX_aWd] = lDpEco.sbx.aWd[iFn];
	aSl[DpSCR_SBX_aHt] = lDpEco.sbx.aHt[iFn];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();
}


void DpEcoL2l_SelPopUp(void)
{
	U08 i;
	U16 aSl[DpSCR_SBX_aNUMB];
	U08 iFn = ScEC1_GetIdxFunc();
	U16 val = ScEC2_GetValue();
	U08 ch = ScECH_PrGet_Chnnl();
	U08 type = ScECH_GetType();
	U16 old = ScECH_PrGet_Value(ch, iFn);
	U08 num = 0;
	I08 pSt0[32] = {0, };
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_OPT_LANG);
	U08 x0s = DpECO_LVL_TITL_X0+20;
	U08 y0s = DpECO_GRP_Y0+20;
	U08 w_c = DpECO_BOX_FG_WD-20; 
	U08 h_c = DpECO_BOX_FG_HT-20;
	U32 cBg = _cPOP_BG_WND;
	U08 updn_mod = ScEC2_GetMode();
	S32 dig = ScEC2_Getupdn_dig();
	U08 flang = TRUE;
	
	if(ScECH_GetType()==ScECO_TYPE_AVG)
	{
		switch(iFn)
		{
			case ScECO_AVG_ASF_LIGHT:
			case ScECO_AVG_ASF_HEAVY:
				return;
		}
	}
	
	DpEchoPOP_DrwIntro();


	switch(lang)
	{
		case MnSYS_LANG_ENG:
			switch(ScECH_GetType())
			{
				case ScECO_TYPE_REAL:
					switch(iFn)
					{	// Page #0
						case ScECO_REAL_ECHO_AMP:		_SPRINTF(lDpEco.pStr[0], _sEcho_Amp);		break;
						case ScECO_REAL_MEAS_RESET:		_SPRINTF(lDpEco.pStr[0], _sMeasure_reset);	break;
						case ScECO_REAL_FREQ:			_SPRINTF(lDpEco.pStr[0], _sFrequency);		break;
						case ScECO_REAL_EMPTY:			_SPRINTF(lDpEco.pStr[0], _sEmpty);			break;
						case ScECO_REAL_DEADZONE:		_SPRINTF(lDpEco.pStr[0], _sDeadzone);		break;
						case ScECO_REAL_TVG:			_SPRINTF(lDpEco.pStr[0], _sTVG);			break;
						default:						break;
					}
					break;
				case ScECO_TYPE_AVG:
					switch(iFn)
					{	// Page #0
						case ScECO_AVG_THR_LIGHT:		_SPRINTF(lDpEco.pStr[0], _sThr_light);	break;
						case ScECO_AVG_THR_HEAVY:		_SPRINTF(lDpEco.pStr[0], _sThr_heavy);	break;
						case ScECO_AVG_ASF_LIGHT:		_SPRINTF(lDpEco.pStr[0], _sASF_LIGHT);	break;
						case ScECO_AVG_ASF_HEAVY:		_SPRINTF(lDpEco.pStr[0], _sASF_HEAVY);	break;
						default:						break;
					}
					break;			
			}						
			break;
		case MnSYS_LANG_KOR:
			switch(ScECH_GetType())
			{
				case ScECO_TYPE_REAL:
					switch(iFn)
					{	// Page #0
						case ScECO_REAL_ECHO_AMP:		DpSTR_GuiList(TEXT_LIST_ECHO_AMP);	break;
						case ScECO_REAL_MEAS_RESET:		DpSTR_GuiList(TEXT_LIST_MSR_RST);	break;
						case ScECO_REAL_FREQ:			DpSTR_GuiList(TEXT_LIST_FREQ);	break;
						case ScECO_REAL_EMPTY:			DpSTR_GuiList(TEXT_LIST_EMPTY);	break;
						case ScECO_REAL_DEADZONE:		DpSTR_GuiList(TEXT_LIST_DEADZONE);	break;
						case ScECO_REAL_TVG:
							_SPRINTF(lDpEco.pStr[0], _sTVG);
							DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+20, _cPOP_ST_TIT, _cPOP_BG_WND, _fE17HsB, lDpEco.pStr[0]);
							flang = FALSE;
							break;
						default:						break;
					}
					break;
				case ScECO_TYPE_AVG:
					switch(iFn)
					{	// Page #0
						case ScECO_AVG_THR_LIGHT:		DpSTR_GuiList(TEXT_LIST_THR_LIGHT);	break;
						case ScECO_AVG_THR_HEAVY:		DpSTR_GuiList(TEXT_LIST_THR_HEAVY);	break;
						case ScECO_AVG_ASF_LIGHT:	
							DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
							DpSTR_GuiList(TEXT_LIST_LIGHT);
							DpSTR_GuiLeft_KOR(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);
							_SPRINTF(lDpEco.pStr[0], _sASF);		
							DpSTR_GuiLeft(x0s+60, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);
							return;
						case ScECO_AVG_ASF_HEAVY:	
							DpFIG_DrwRect(x0s, y0s, w_c, h_c, _cBGD_SCRN, DpFIG_FILL);
							DpSTR_GuiList(TEXT_LIST_HEAVY);
							DpSTR_GuiLeft_KOR(x0s, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);
							_SPRINTF(lDpEco.pStr[0], _sASF);		
							DpSTR_GuiLeft(x0s+60, y0s, _cSD_WHITE, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);
							return;							
						default:						break;
					}				
					break;			
			}		
			_SPRINTF(lDpEco.pStr[0], gDpStr.Text_list);
			break;
	}

	if(flang)
		DpEchoPOP_UdtTitle(lDpEco.pStr[0]);

	flang = TRUE;
	
	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			switch(iFn)
			{
				case ScECO_REAL_ECHO_AMP:	_SPRINTF(pSt0, "%d", old);		break;
				case ScECO_REAL_MEAS_RESET:	_SPRINTF(pSt0, "-");			break;
				case ScECO_REAL_FREQ:
					switch(old)
					{
						case MnMS1_FREQ_380K:	_SPRINTF(pSt0, "380");		break;
						case MnMS1_FREQ_270K:	_SPRINTF(pSt0, "270");		break;
						case MnMS1_FREQ_160K:	_SPRINTF(pSt0, "160");		break;
						case MnMS1_FREQ_130K:	_SPRINTF(pSt0, "130");		break;
					}
					break;
				case ScECO_REAL_EMPTY:		_SPRINTF(pSt0, "%d.%02d", (U16)(old/100), (U16)(old%100));	break;
				case ScECO_REAL_DEADZONE:	_SPRINTF(pSt0, "%d.%02d", (U16)(old/100), (U16)(old%100));	break;
				case ScECO_REAL_TVG:		
					if(old ==0)
					{
						if(lang==MnSYS_LANG_ENG)
							_SPRINTF(pSt0, "OFF");
						else
						{
							DpSTR_GuiList(TEXT_LIST_OFF);
							DpSTR_GuiLeft(DpECO_LVL_TITL_X0+140, DpECO_GRP_Y0+60, _cPOP_ST_VAL_IDL, _cPOP_BG_WND, _fE17HsB, _sNOW_);
							DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+140, DpECO_GRP_Y0+83,	_cPOP_ST_OLD,	  _cPOP_BG_WND, _fE17HsBKOR, gDpStr.Text_list);
							flang=FALSE;
						}
					}
					else
						_SPRINTF(pSt0, "%d", old);		
					break;
				default:					
					return;
			}
			break;
		case ScECO_TYPE_AVG:
			switch(iFn)
			{	// Page #0
				case ScECO_AVG_THR_LIGHT:		
					switch(MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT))
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(pSt0, "%d%c", old,37);		break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(pSt0, "%01d.%1dv", (U16)(old/10), (U16)(old%10));		break;
					}
					break;
				case ScECO_AVG_THR_HEAVY:
					switch(MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY))
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(pSt0, "%d%c", old,37);		break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(pSt0, "%01d.%1dv", (U16)(old/10), (U16)(old%10));		break;
					}
					break;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:				_SPRINTF(pSt0, "%d", old);		break;
				default:								break;
			}
			break;				
	}

	if(flang)
		DpEchoPOP_UdtOldVl(pSt0);

	flang = TRUE;
	
	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:
			switch(iFn)
			{
				case ScECO_REAL_ECHO_AMP:	_SPRINTF(pSt0, "%d", val);		break;
				case ScECO_REAL_MEAS_RESET:
					switch(val)
					{
						case MENU_CHK_NO:	
							if(lang==MnSYS_LANG_ENG)
								_SPRINTF(pSt0, "NO");		
							else if(lang==MnSYS_LANG_KOR)
							{
								DpSTR_GuiList(TEXT_LIST_NO);
								DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+70, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
								return;
							}	
							break;
						case MENU_CHK_YES:
							if(lang==MnSYS_LANG_ENG)
								_SPRINTF(pSt0, "YES");		
							else if(lang==MnSYS_LANG_KOR)
							{
								DpSTR_GuiList(TEXT_LIST_YES);
								DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+70, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsBKOR, gDpStr.Text_list);
								return;
							}	
							break;
					}		
					break;
				case ScECO_REAL_FREQ:
					switch(val)
					{
						case MnMS1_FREQ_380K:	_SPRINTF(pSt0, "380kHz");		break;
						case MnMS1_FREQ_270K:	_SPRINTF(pSt0, "270kHz");		break;
						case MnMS1_FREQ_160K:	_SPRINTF(pSt0, "160kHz");		break;
						case MnMS1_FREQ_130K:	_SPRINTF(pSt0, "130kHz");		break;
					}
					break;
				case ScECO_REAL_EMPTY:		_SPRINTF(pSt0, "%02d.%02d(m)", (U16)(val/100), (U16)(val%100));	break;
				case ScECO_REAL_DEADZONE:	_SPRINTF(pSt0, "%02d.%02d(m)", (U16)(val/100), (U16)(val%100));	break;
				case ScECO_REAL_TVG:
				if(val ==0)
				{
					if(lang==MnSYS_LANG_ENG)
						_SPRINTF(pSt0, "OFF");
					else
					{
						DpSTR_GuiList(TEXT_LIST_OFF);
						DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+70, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE17HsBKOR, gDpStr.Text_list);
						return;
					}
				}
				else
					_SPRINTF(pSt0, "%d", val);		
				break;
				default:					return;
			}
			break;
		case ScECO_TYPE_AVG:
			switch(iFn)
			{	// Page #0
				case ScECO_AVG_THR_LIGHT:		
					switch(MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT))
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(pSt0, "%d%c", val,37);		break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(pSt0, "%01d.%1dv", (U16)(val/10), (U16)(val%10));		break;
					}
					break;
				case ScECO_AVG_THR_HEAVY:
					switch(MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY))
					{
						case MnMS1_THRESHOLD_AUTO:		_SPRINTF(pSt0, "%d%c", val,37);		break;
						case MnMS1_THRESHOLD_MANUAL:	_SPRINTF(pSt0, "%01d.%1dv", (U16)(val/10), (U16)(val%10));		break;
					}
					break;
				case ScECO_AVG_ASF_LIGHT:
				case ScECO_AVG_ASF_HEAVY:				_SPRINTF(pSt0, "%d", val);		break;
				default:								break;
			}
			break;				
	}

 


	switch(updn_mod)
	{
		case SCRN_L2_UPDN_IDLE:			DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+70, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, pSt0);	break;
		case SCRN_L2_UPDN_DIG:
		case SCRN_L2_UPDN_DIG_VALUE:	DpSTR_GuiLeftCursor(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+70, _cPOP_ST_VAL_SEL, _cMNU_SEL_SCT, cBg, (U08)log10(1000)-dig, _fE22HsB, pSt0);	break;
		default:	break;
	}

	if(updn_mod != SCRN_L2_UPDN_DIG_VALUE)
		return;

	switch(dig)
	{
		case 4:	
			_SPRINTF(pSt0, "%d", (abs(val)/10000)%10);	DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+120, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 3:
			_SPRINTF(pSt0, "%d", (abs(val)/1000)%10); DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+120, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 2:
			_SPRINTF(pSt0, "%d", (abs(val)/100)%10); DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+120, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 1:
			_SPRINTF(pSt0, "%d", (abs(val)/10)%10); DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+120, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
		case 0:
			_SPRINTF(pSt0, "%d", abs(val)%10); DpSTR_GuiLeft(DpECO_LVL_TITL_X0+20, DpECO_GRP_Y0+120, _cMNU_SEL_SCT, cBg, _fE22HsB, pSt0);
			break;
	}	
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L3 - Value
//------------------------------------------------------------------------------------------------------------------------------

void DpEC2_ValUpdat(void)
{
	DpEcoGrp_DrawLive(0);
	DpEcoBox_LstAll();
	DpEcoL2l_SelBox();
	DpEcoL2l_SelPopUp();
}


void DpEC2_ValIntro(void)
{
	DpFIG_DrwRect(DpECO_GRP_X0, DpECO_GRP_Y0-15, DpECO_GRP_WD+8, 8, _cBGD_SCRN, DpFIG_FILL);

	DpEC2_ValUpdat();
	DpSCR_UpdtBttn(SCRN_L2_VALU);
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L1 - List
//------------------------------------------------------------------------------------------------------------------------------
void DpEC1_LstUpdat(void)
{
	DpEcoBox_LstAll();
	DpEcoL1l_SelBox();
}

void DpEC1_LstIntro(void)
{
	// String Channel
	//DpEcoLvl_StrChnnl();
	// Screen Type
	//DpEcoLyr_StrUpdat();
	// Clear Tracking Width
	//DpFIG_DrwRect(DpECO_GRP_X0, DpECO_GRP_Y0-15, DpECO_GRP_WD+8, 8, _cBGD_SCRN, DpFIG_FILL);

	DpEC1_LstUpdat();
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L0 - Function
//------------------------------------------------------------------------------------------------------------------------------
void DpEC0_FncStdBy(U08 range)
{
	DpEcoGrp_DrawLive(range);
	DpEcoLvl_StrValue();
}

void DpEC0_FncIntro(void)
{
	U08 i;
	U16 sn_x0 = DpECO_GRP_X0;
	U16 sn_y0 = DpECO_GRP_Y0 + DpECO_GRP_HT + 4;
	U16 sn_xG = DpECO_GRP_WD_CURSOR;
	U16 y1_val = (ADC_VAL_MAX*10)/33;
	U16 y2_val = (ADC_VAL_MAX*20)/33;
	U16 y3_val = (ADC_VAL_MAX*30)/33;
	U16 y1 =DpECO_GRP_Y0+(DpECO_GRP_HT-(y1_val/16));
	U16 y2 =DpECO_GRP_Y0+(DpECO_GRP_HT-(y2_val/16));
	U16 y3 =DpECO_GRP_Y0+(DpECO_GRP_HT-(y3_val/16));
	U08 type = MnFTR_PrGet_SsChn();
	U08 ch = ScECH_PrGet_Chnnl();
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 val;


	if(type == MnFTR_SS_SINGLE)
	{
		ScECH_PrSet_Chnnl(APP_CH_1);
		ch = APP_CH_1;
	}
	else if (type == MnFTR_SS_DUAL)
		ch = ScECH_PrGet_Chnnl();
	
	DpECO_InitVari();
	// Title
	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:	DpTTB_UdtIntro(TEXT_LIST_REAL_ECHO_SCREEN, 300, _cTTB_ST_TITLE);	break;
		case ScECO_TYPE_AVG:	DpTTB_UdtIntro(TEXT_LIST_AVG_ECHO_SCREEN, 300, _cTTB_ST_TITLE);		break;
	}

	// Screen
	DISP_IntroScrn();

	// Graph - Boundary
	DpFIG_DrwRect(DpECO_GRP_X0-4, DpECO_GRP_Y0-4, DpECO_GRP_WD+8, DpECO_GRP_HT+8, _cECO_GRP_BDR, 2);
	DpFIG_DrwLinH(DpECO_GRP_X0-10, DpECO_GRP_Y0-2, 6, _cECO_GRP_BDR);
	DpFIG_DrwLinH(DpECO_GRP_X0-10, DpECO_GRP_Y0+DpECO_GRP_HT+8-6, 6, _cECO_GRP_BDR);
	// Graph - Amplitude Rate
	DpEcoGrp_TtlAmp();
	


	// Graph - Meter Sign
	for(i=0; i<12; i++)
	{
		if(i<11)
		{
			val = empty-((empty*i)/10);
			if(val>=1000)	_SPRINTF(lDpEco.pStr[0], "%02d.%02d",val/100,val%100);
			else			_SPRINTF(lDpEco.pStr[0], "%01d.%02d",val/100,val%100);
		
			DpSTR_GuiLeft(sn_x0+ (sn_xG*i)-18, sn_y0+10, _cECO_AMP_STD, _cBGD_SCRN, _fE12HsM, lDpEco.pStr[0]);
		}
		DpFIG_DrwLinV(sn_x0+ (sn_xG*i), sn_y0, 6, _cECO_GRP_BDR);	
	}

	
	DpFIG_DrwLinH(sn_x0-10, y1, 6, _cECO_GRP_BDR);
	DpFIG_DrwLinH(sn_x0-10, y2, 6, _cECO_GRP_BDR);
	DpFIG_DrwLinH(sn_x0-10, y3, 6, _cECO_GRP_BDR);
	
	// Layer (Multi / Single)
	//DpEcoLyr_StrUpdat();
	// Parameter Box
	DpEcoBox_LstAll();

	// Level
	DpEcoLvl_StrTitle();
	DpEcoLvl_StrUnit();
	DpEcoLvl_StrChnnl();

	// Button

	// Update Parameter
	DpEC0_FncStdBy(0);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DpECO_InitVari(void)
{
	U08 i, num;

	_MEMSET(lDpEco.pStr[0], 0, sizeof(lDpEco.pStr[0]));
	_MEMSET(lDpEco.pStr[1], 0, sizeof(lDpEco.pStr[0]));

	switch(ScECH_GetType())
	{
		case ScECO_TYPE_REAL:	num = ScECO_REAL_NUM;	break;
		case ScECO_TYPE_AVG:	num = ScECO_AVG_NUM;	break;
		default:										break;
	}


	// Sel-Box Position
	for(i=1; i<num; i++)
	{
		if		(i >= (ScECO_FNC_PAGE*2))		lDpEco.sbx.aY0[i] = 270 + (DpECO_BOX_Lx_SB_HT * ((i+1)-(ScECO_FNC_PAGE*2)));
		else if	(i >=  ScECO_FNC_PAGE)			lDpEco.sbx.aY0[i] = 270 + (DpECO_BOX_Lx_SB_HT * ((i+1)- ScECO_FNC_PAGE   ));
		else									lDpEco.sbx.aY0[i] = 270 + (DpECO_BOX_Lx_SB_HT *  i);

		lDpEco.sbx.aX0[i] = DpECO_BOX_L0_SB_X0;
		lDpEco.sbx.aWd[i] = DpECO_BOX_Lx_SB_WD+65;
		lDpEco.sbx.aHt[i] = DpECO_BOX_Lx_SB_HT-5;
	}

	lDpEco.sbx.aX0[ScECO_REAL_CH_SEL] = DpECO_LVL_TITL_X0+30 - 8;
	lDpEco.sbx.aY0[ScECO_REAL_CH_SEL] = DpECO_GRP_Y0-35 - 3;
	lDpEco.sbx.aWd[ScECO_REAL_CH_SEL] = DpECO_LVL_CH_WD+130;
	lDpEco.sbx.aHt[ScECO_REAL_CH_SEL] = DpECO_LVL_CH_HT;

}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

