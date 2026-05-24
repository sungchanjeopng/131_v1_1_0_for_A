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
#include "bsp_ram.h"

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
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_system.h"
#include "menu_data.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_echo.h"
#include "screen_calib.h"
#include "screen_clb1_list.h"
#include "screen_clb2_value.h"
// disp - screen
#include "dp_screen_main.h"
#include "dp_screen_echo.h"
// data
#include "data_save.h"
// self
#include "dp_screen_calib.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
DpCLB_LS lDpClb;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Graph
//------------------------------------------------------------------------------------------------------------------------------
void DpClbGrp_TtlAmp(void)
{
#if 0
	U16 y0 = DpCLB_GRP_Y0 + 3;
	U16 y1 = DpCLB_GRP_Y0 + (DpCLB_GRP_HT/2) - 10;
	U16 y2 = DpCLB_GRP_Y0 + (DpCLB_GRP_HT)   - 15;

	DpSTR_GuiLeft(DpCLB_GRP_X0-45, y0, _cCLB_STR_GAIN, _cBGD_SCRN, _fE12HsM, "2482");
	DpSTR_GuiLeft(DpCLB_GRP_X0-45, y1, _cCLB_STR_GAIN, _cBGD_SCRN, _fE12HsM, "1241");
	DpSTR_GuiLeft(DpCLB_GRP_X0-45, y2, _cCLB_STR_GAIN, _cBGD_SCRN, _fE12HsM, "   0");
#endif
}

void DpClbGrp_FgrSignal(U08 iCh, U16 x0, U08 range, U08 type)
{
#if 0
	F32 ht_v;
	U16 y0_v;
	U16 ln;
	U16 s_dt = (U16)ScHYB_PrGet_Value(iCh, ScHYB_F02_S_DEP);
	U16 d_zn = (U16)ScHYB_PrGet_Value(iCh, ScHYB_F03_DEADZ);
	U16 t_dt = (U16)ScHYB_PrGet_Value(iCh, ScHYB_F04_T_DEP);


	ln=(x0*(t_dt-s_dt))/(DpCLB_GRP_WD_CURSOR_10);

	switch(type)
	{
		case ScECO_SCREEN_AVG:	ht_v = MsCAL_GetVl_EchoBuff(iCh, ln*(range+1)) / 16;	break;
		case ScECO_SCREEN_REAL: ht_v = ADC_GetEchoVal(iCh, ln*(range+1)) / 16;			break;
		default:																		break;
	}

	y0_v = DpCLB_GRP_Y0 + (DpCLB_GRP_HT - ht_v);
	
	if	((ln < d_zn)  && (ln < (t_dt-s_dt)))					DpFIG_DrwLinV(x0+DpCLB_GRP_X0, y0_v, ht_v, _cECO_LN_V_DDZN);
#if 1
	else if	((ln > d_zn)  && (ln > (t_dt-s_dt)))				DpFIG_DrwLinV(x0+DpCLB_GRP_X0, y0_v, ht_v, _cSD_DARKGRAY);
#else
	else if	((ln > d_zn)  && (ln > t_dt))						DpFIG_DrwLinV(ln/2+DpECO_GRP_X0, y0_v, ht_v, _cSD_DARKGRAY);
#endif
	else														DpFIG_DrwLinV(x0+DpCLB_GRP_X0, y0_v, ht_v, _cECO_LN_V_SLDG);
#endif
}


void DpClbGrp_LineGain(void)
{
#if 0
	U32 x0  = DpCLB_GRP_X0 - 10;
	U16 y0;
	S32 val = ScCB2_GetValue();
	U08 iFn = ScCB1_GetIdxFunc();
	F32 gain=(F32)val/100;


	if(gain>DpCLB_GAIN_HIGH)	y0 = ((F32)(DpECO_GRP_HT/200.00)*gain)+(F32)(DpECO_GRP_HT/2.00);	
	else						y0 = (F32)(DpECO_GRP_HT/2.00)*gain;

	if(ScCLB_GetLayer() != SCRN_L2_VALU)
		return;

	if(iFn != ScCLB_F02_RX_GAIN)
		return;

	DpFIG_DrwTria(x0, DpCLB_GAIN_P01-y0, x0-7, DpCLB_GAIN_P01-y0-5, x0-7, DpCLB_GAIN_P01-y0+5, _cCLB_GAIN_LINE);
	DpFIG_DrwLinH(DpCLB_GRP_X0, DpCLB_GAIN_P01-y0+3, DpCLB_GRP_WD, _cCLB_GAIN_LINE);
#endif
}



void DpClbGrp_LineTvg(void)
{
#if 0
	U32 i;
	U32 x0[TVG_IDX_MAX];
	U16 y0[TVG_IDX_MAX];	
	U08 ich = ScECH_PrGet_Chnnl();
	U08 iFn = ScCB1_GetIdxFunc();
	S32 val = ScCB2_GetValue();
	S32 gain  = ScCLB_PrGet_Value(ich,ScCLB_F02_RX_GAIN);
	U08 fTVG  = ScCLB_PrGet_Value(ich,ScCLB_F05_TVG_fEN);
	S32 trans = ScCLB_PrGet_Value(ich,ScCLB_F03_RX_TRANS);
	U16 s_dt = (U16)ScHYB_PrGet_Value(ich, ScHYB_F02_S_DEP);
	U16 t_dt = (U16)ScHYB_PrGet_Value(ich, ScHYB_F04_T_DEP);
	U08 sel;
	S32 vca,volt;
	
#if 0
	if(ScCLB_GetLayer() != SCRN_L2_VALU)
		return;
#endif
	if(ScCLB_GetLayer() == SCRN_L2_VALU)
	{
		switch(iFn)
		{				
			case ScCLB_F02_RX_GAIN:	 	gain    = val;													break;
			case ScCLB_F05_TVG_fEN:	 	fTVG    = val;													break;
			case ScCLB_F03_RX_TRANS: 	trans   = val;													break;
			case ScCLB_F06_TVG_CUSTOM:	fTVG    = ScCLB_TVG_CUSTOM;	 sel = ScCLB_PrGet_Tvg_x_axis(ich);	break;
			default:																					return;
		}
	}
	else	return;


	
	for(i=0; i<TVG_IDX_MAX; i++)
	{			
		switch(fTVG)
		{
			case ScCLB_TVG_OFF:		vca = 40;								break;
			case ScCLB_TVG_CUSTOM:	
				vca = ScCLB_PrGet_Tvg_Custom(ich,i);						
				if((ScCLB_GetLayer() == SCRN_L2_VALU) && (iFn == ScCLB_F06_TVG_CUSTOM) && (ScCB2_GetSelStep() == SCRN_L2_SEL_STEP1))
				{
					if(i==sel)
						vca = val;
				}
				break;
			break;
			default:				vca  = lMsr_aTvg[fTVG-1][i];			break;
		}
		
		volt = (vca*gain)+trans;
		if(volt>DAC_CON_DIG_MAX)	volt = DAC_CON_DIG_MAX;
		if(volt<0)					volt = 0;
		y0[i] = DpCLB_GAIN_P01-(F32)(DpCLB_GAIN_HT/DAC_CON_DIG_MAX)*volt;
		x0[i] =  ((i*20*DpCLB_GRP_WD_CURSOR_10)/(t_dt-s_dt))+DpCLB_GRP_X0;
		if(x0[i]>(DpCLB_GRP_X0+DpCLB_GRP_WD))	return;
		DpFIG_DrwCirc(x0[i]+3, y0[i], 3, _cCLB_GAIN_CIRC, _F_T);
		
		if(i > 0)	DpFIG_DrwLine(x0[i-1], y0[i-1], x0[i], y0[i], _cCLB_GAIN_LINE);
	}
#endif
}

void DpClbGrp_DrawLive(void)
{
	DaSav_dumpSetinit();

	U08 ch = ScCLB_GetCh();
	U16 i;
	U16 val[2][MsCAL_THR_TYPE_NUM];
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 x0,x1;
	U16 y0[MsCAL_THR_TYPE_NUM],y1[MsCAL_THR_TYPE_NUM];
	S32 dump_addr = DaSav_GetDumpAddr();
	U32 save_size = DaSav_GetSaveSize();
	U32 save_cnt = DaSav_GetCnt();
	U32 dump_cnt = 0;
	U32 dump_size =0;
	U08 rd_buf[SAV_PKT_MAX] = {0, };
	U08 rd_fld_buf[SAV_PKT_FLD_MAX] = {0, };
	U16 time;
	DpFIG_DrwRect(DpCLB_GRP_X0-2, DpCLB_GRP_Y0-10, DpCLB_GRP_WD+2, DpCLB_GRP_HT+15, _cBGD_SCRN, DpFIG_FILL);

	
	lDpClb.min[MsCAL_THR_LIGHT] = 0xffff;
	lDpClb.min[MsCAL_THR_HEAVY] = 0xffff;

	lDpClb.max[MsCAL_THR_LIGHT] = 0;
	lDpClb.max[MsCAL_THR_HEAVY] = 0;

	for(i=0; i<6; i++)
	{		
		DpFIG_DrwLinH(DpCLB_GRP_X0, DpCLB_GRP_Y0+(45*i), DpCLB_GRP_WD, _cTrend_line);
	}
	// Graph - Amplitude Rate
	//DpClbGrp_TtlAmp();
	// Graph - Meter Sign


	switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
	{
		case MnDS0_DISPLAY_TERM_1:	time = 720;  break;
		case MnDS0_DISPLAY_TERM_2:	time = 1440; break;
	}

	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)
	{
		if(save_cnt>time)
		{
			dump_addr -= SAV_PKT_MAX*time;
			if(dump_addr<0)
				dump_addr += save_size;
		}

		for(dump_cnt=0; dump_cnt<time; dump_cnt++)
		{			
			if(dump_size >= save_size)
				break;
			if(dump_cnt >=save_cnt)
				break;
			
			if(dump_addr+SAV_PKT_MAX>save_size)
			{
				dump_addr = 0;
			}

			
			MRM_RdBulk(_mTrBOD_START+dump_addr, rd_buf, SAV_PKT_MAX);

			switch(ch)
			{
				case APP_CH_1:
					val[1][MsCAL_THR_LIGHT] = (rd_buf[SAV_PKT_VAL_CH1_LIGHT_H]<<8) + rd_buf[SAV_PKT_VAL_CH1_LIGHT_L];
					val[1][MsCAL_THR_HEAVY] = (rd_buf[SAV_PKT_VAL_CH1_HEAVY_H]<<8) + rd_buf[SAV_PKT_VAL_CH1_HEAVY_L];
					break;
				case APP_CH_2:
					val[1][MsCAL_THR_LIGHT] = (rd_buf[SAV_PKT_VAL_CH2_LIGHT_H]<<8) + rd_buf[SAV_PKT_VAL_CH2_LIGHT_L];
					val[1][MsCAL_THR_HEAVY] = (rd_buf[SAV_PKT_VAL_CH2_HEAVY_H]<<8) + rd_buf[SAV_PKT_VAL_CH2_HEAVY_L];				
					break;
				default:
					break;
			}

			x1 = DpCLB_GRP_X0 + DpCLB_GRP_WD - ((DpCLB_GRP_WD*(dump_cnt))/time); 

			y1[MsCAL_THR_LIGHT] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[1][MsCAL_THR_LIGHT])/empty);

			y1[MsCAL_THR_HEAVY] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[1][MsCAL_THR_HEAVY])/empty);		


			if(lDpClb.min[MsCAL_THR_LIGHT] > val[1][MsCAL_THR_LIGHT])
				lDpClb.min[MsCAL_THR_LIGHT]  = val[1][MsCAL_THR_LIGHT];

			if(lDpClb.min[MsCAL_THR_HEAVY] > val[1][MsCAL_THR_HEAVY])
				lDpClb.min[MsCAL_THR_HEAVY]  = val[1][MsCAL_THR_HEAVY];	

			if(lDpClb.max[MsCAL_THR_LIGHT] < val[1][MsCAL_THR_LIGHT])
				lDpClb.max[MsCAL_THR_LIGHT]  = val[1][MsCAL_THR_LIGHT];

			if(lDpClb.max[MsCAL_THR_HEAVY] < val[1][MsCAL_THR_HEAVY])
				lDpClb.max[MsCAL_THR_HEAVY]  = val[1][MsCAL_THR_HEAVY];			

			
			if(dump_cnt>0)
			{
				x0 = DpCLB_GRP_X0 + DpCLB_GRP_WD - ((DpCLB_GRP_WD*((dump_cnt-1)))/time); 

				
				y0[MsCAL_THR_LIGHT] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[0][MsCAL_THR_LIGHT])/empty);

				y0[MsCAL_THR_HEAVY] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[0][MsCAL_THR_HEAVY])/empty);

				if((x0<=(DpCLB_GRP_X0 + DpCLB_GRP_WD)) && (x0>=(DpCLB_GRP_X0)) && (x1<=(DpCLB_GRP_X0 + DpCLB_GRP_WD)) && (x1>=(DpCLB_GRP_X0)))
				{
					if((y0[MsCAL_THR_LIGHT]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y0[MsCAL_THR_LIGHT]>=DpCLB_GRP_Y0) &&
						(y1[MsCAL_THR_LIGHT]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y1[MsCAL_THR_LIGHT]>=DpCLB_GRP_Y0))
					{	
						DpFIG_DrwLine(x0,y0[MsCAL_THR_LIGHT],x1,y1[MsCAL_THR_LIGHT]-1,_cLight_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_LIGHT],x1,y1[MsCAL_THR_LIGHT],_cLight_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_LIGHT],x1,y1[MsCAL_THR_LIGHT]+1,_cLight_level);
					}
					if((y0[MsCAL_THR_HEAVY]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y0[MsCAL_THR_HEAVY]>=DpCLB_GRP_Y0) &&
						(y1[MsCAL_THR_HEAVY]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y1[MsCAL_THR_HEAVY]>=DpCLB_GRP_Y0))
					{		
						DpFIG_DrwLine(x0,y0[MsCAL_THR_HEAVY],x1,y1[MsCAL_THR_HEAVY]-1,_cHeavy_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_HEAVY],x1,y1[MsCAL_THR_HEAVY],_cHeavy_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_HEAVY],x1,y1[MsCAL_THR_HEAVY]+1,_cHeavy_level);
					}
				}
			}

			switch(ch)
			{
				case APP_CH_1:		
					val[0][MsCAL_THR_LIGHT] = (rd_buf[SAV_PKT_VAL_CH1_LIGHT_H]<<8) + rd_buf[SAV_PKT_VAL_CH1_LIGHT_L];
					val[0][MsCAL_THR_HEAVY] = (rd_buf[SAV_PKT_VAL_CH1_HEAVY_H]<<8) + rd_buf[SAV_PKT_VAL_CH1_HEAVY_L];
					break;
				case APP_CH_2:
					val[0][MsCAL_THR_LIGHT] = (rd_buf[SAV_PKT_VAL_CH2_LIGHT_H]<<8) + rd_buf[SAV_PKT_VAL_CH2_LIGHT_L];
					val[0][MsCAL_THR_HEAVY] = (rd_buf[SAV_PKT_VAL_CH2_HEAVY_H]<<8) + rd_buf[SAV_PKT_VAL_CH2_HEAVY_L];
					break;
				default:
					break;
			}

			dump_addr += SAV_PKT_MAX;
			dump_size += SAV_PKT_MAX;		
		}
	}
	else if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		if(save_cnt>time)
		{
			dump_addr -= SAV_PKT_FLD_MAX*time;
			if(dump_addr<0)
				dump_addr += save_size;
		}
		
		for(dump_cnt=0; dump_cnt<time; dump_cnt++)
		{			
			if(dump_size >= save_size)
				break;
			if(dump_cnt >=save_cnt)
				break;
			
			if(dump_addr+SAV_PKT_FLD_MAX>save_size)
			{
				dump_addr = 0;
			}
		
			
			MRM_RdBulk(_mTrBOD_START+dump_addr, rd_fld_buf, SAV_PKT_FLD_MAX);
		
			switch(ch)
			{
				case APP_CH_1:
					val[1][MsCAL_THR_LIGHT] = (rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_L];
					val[1][MsCAL_THR_HEAVY] = (rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_L];
					break;
				case APP_CH_2:
					val[1][MsCAL_THR_LIGHT] = (rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_L];
					val[1][MsCAL_THR_HEAVY] = (rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_L];				
					break;
				default:
					break;
			}
		
			x1 = DpCLB_GRP_X0 + DpCLB_GRP_WD - ((DpCLB_GRP_WD*(dump_cnt))/time); 
		
			y1[MsCAL_THR_LIGHT] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[1][MsCAL_THR_LIGHT])/empty);
		
			y1[MsCAL_THR_HEAVY] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[1][MsCAL_THR_HEAVY])/empty); 	
		
		
			if(lDpClb.min[MsCAL_THR_LIGHT] > val[1][MsCAL_THR_LIGHT])
				lDpClb.min[MsCAL_THR_LIGHT]  = val[1][MsCAL_THR_LIGHT];
		
			if(lDpClb.min[MsCAL_THR_HEAVY] > val[1][MsCAL_THR_HEAVY])
				lDpClb.min[MsCAL_THR_HEAVY]  = val[1][MsCAL_THR_HEAVY]; 
		
			if(lDpClb.max[MsCAL_THR_LIGHT] < val[1][MsCAL_THR_LIGHT])
				lDpClb.max[MsCAL_THR_LIGHT]  = val[1][MsCAL_THR_LIGHT];
		
			if(lDpClb.max[MsCAL_THR_HEAVY] < val[1][MsCAL_THR_HEAVY])
				lDpClb.max[MsCAL_THR_HEAVY]  = val[1][MsCAL_THR_HEAVY]; 		
		
			
			if(dump_cnt>0)
			{
				x0 = DpCLB_GRP_X0 + DpCLB_GRP_WD - ((DpCLB_GRP_WD*((dump_cnt-1)))/time); 
		
				
				y0[MsCAL_THR_LIGHT] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[0][MsCAL_THR_LIGHT])/empty);
		
				y0[MsCAL_THR_HEAVY] = DpCLB_GRP_Y0 + DpCLB_GRP_HT - ((DpCLB_GRP_HT*val[0][MsCAL_THR_HEAVY])/empty);
		
				if((x0<=(DpCLB_GRP_X0 + DpCLB_GRP_WD)) && (x0>=(DpCLB_GRP_X0)) && (x1<=(DpCLB_GRP_X0 + DpCLB_GRP_WD)) && (x1>=(DpCLB_GRP_X0)))
				{
					if((y0[MsCAL_THR_LIGHT]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y0[MsCAL_THR_LIGHT]>=DpCLB_GRP_Y0) &&
						(y1[MsCAL_THR_LIGHT]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y1[MsCAL_THR_LIGHT]>=DpCLB_GRP_Y0))
					{	
						DpFIG_DrwLine(x0,y0[MsCAL_THR_LIGHT],x1,y1[MsCAL_THR_LIGHT]-1,_cLight_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_LIGHT],x1,y1[MsCAL_THR_LIGHT],_cLight_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_LIGHT],x1,y1[MsCAL_THR_LIGHT]+1,_cLight_level);
					}
					if((y0[MsCAL_THR_HEAVY]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y0[MsCAL_THR_HEAVY]>=DpCLB_GRP_Y0) &&
						(y1[MsCAL_THR_HEAVY]<=(DpCLB_GRP_Y0 + DpCLB_GRP_HT)) && (y1[MsCAL_THR_HEAVY]>=DpCLB_GRP_Y0))
					{		
						DpFIG_DrwLine(x0,y0[MsCAL_THR_HEAVY],x1,y1[MsCAL_THR_HEAVY]-1,_cHeavy_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_HEAVY],x1,y1[MsCAL_THR_HEAVY],_cHeavy_level);
						DpFIG_DrwLine(x0,y0[MsCAL_THR_HEAVY],x1,y1[MsCAL_THR_HEAVY]+1,_cHeavy_level);
					}
				}
			}
		
			switch(ch)
			{
				case APP_CH_1:		
					val[0][MsCAL_THR_LIGHT] = (rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_L];
					val[0][MsCAL_THR_HEAVY] = (rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_L];
					break;
				case APP_CH_2:
					val[0][MsCAL_THR_LIGHT] = (rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_L];
					val[0][MsCAL_THR_HEAVY] = (rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_L];
					break;
				default:
					break;
			}
		
			dump_addr += SAV_PKT_FLD_MAX;
			dump_size += SAV_PKT_FLD_MAX;		
		}

	}
#if 0
	_SPRINTF(sDbg, "%d  %d %d %d", dump_addr,save_size,dump_size,save_cnt);
	DpFIG_DrwRect(150, 30, 400, 25, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(150, 30, _cECO_LVL_TITL, _cBGD_SCRN, _fE17HsB, sDbg);
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Level
//------------------------------------------------------------------------------------------------------------------------------
void DpClbLvl_StrIntro(void)
{
#if 0
	I08 *pStr = lDpClb.pStr[0];

	// Title
	switch(ScHYB_PrGet_LvTyp())
	{
		case ScHYB_LVL_SLDG:	_SPRINTF(pStr, _sSludge);	break;
		case ScHYB_LVL_DIST:	_SPRINTF(pStr, _sDist);		break;
	}
	DpSTR_GuiLeft(DpCLB_LVL_TITL_X0, DpCLB_LVL_TITL_Y0, _cCLB_LVL_TITL, _cBGD_SCRN, _fE22HsB, pStr);

	// Unit
	if(ScHYB_PrGet_Unit_() == ScHYB_UNIT_METER)		_SPRINTF(pStr, "m");
	else											_SPRINTF(pStr, "ft");
	DpSTR_GuiLeft(DpCLB_LVL_UNIT_X0, DpCLB_LVL_UNIT_Y0, _cCLB_LVL_TITL, _cBGD_SCRN, _fE35HsB, pStr);

	// Channel
	if(MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE)
		return;

	switch(ScECH_PrGet_Chnnl())
	{
		case APP_CH_1:		_SPRINTF(pStr, _sCH_1);		break;
		case APP_CH_2:		_SPRINTF(pStr, _sCH_2);		break;
	}

	DpFIG_DrwRect(DpCLB_LVL_CH_X0, DpCLB_LVL_CH_Y0, DpCLB_LVL_CH_WD, DpCLB_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpCLB_LVL_CH_X0, DpCLB_LVL_CH_Y0, _cCLB_LVL_VALU, _cBGD_SCRN, _fE17HsB, pStr);
#endif
}

void DpClbLvl_StrTitle(void)
{
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);
	I08 pSt0[64] = {0, };


	DpFIG_DrwLinH(DpECO_LVL_TITL_X0, DpCLB_LVL_TITL_Y0, DpECO_BOX_FG_WD, _cSD_WHITE);

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			_SPRINTF(lDpClb.pStr[0],_sLight_level);
			
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+15, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+15, _cLight_level, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);

			_SPRINTF(lDpClb.pStr[0],  _sHeavy_level);
			
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+15, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+15, _cECO_LVL_VALU, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);	

			_SPRINTF(lDpClb.pStr[0], _sMax);

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+50, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+50, _cLight_level, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);
			
			_SPRINTF(lDpClb.pStr[0], _sMin);

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+90, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+90, _cLight_level, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);

			_SPRINTF(lDpClb.pStr[0], _sMax);

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+50, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+50, _cHeavy_level, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);

			_SPRINTF(lDpClb.pStr[0], _sMin);

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+90, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+90, _cHeavy_level, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);			

			_SPRINTF(lDpClb.pStr[0], "Time");
			DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2), DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);

			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
			{
				case MnDS0_INTV_01S:
				case MnDS0_INTV_10S:
					_SPRINTF(lDpClb.pStr[0], "(min)");
					DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2)+100, DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
					break;
				case MnDS0_INTV_10M:
				case MnDS0_INTV_01M:
					_SPRINTF(lDpClb.pStr[0], "(hour)");
					DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2)+100, DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
					break;					
				case MnDS0_INTV_01H:
					_SPRINTF(lDpClb.pStr[0], "(day)");
					DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2)+100, DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
					break;
			}
			break;
		case MnSYS_LANG_KOR:
			DpSTR_GuiList(TEXT_LIST_LIGHT_LEVEL);
			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20+145, DpCLB_LVL_TITL_Y0+15, _cLight_level, _cBGD_SCRN, _fE17HsB, pSt0); 

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+15, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+15,_cLight_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);

			DpSTR_GuiList(TEXT_LIST_HEAVY_LEVEL);
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+15, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+15,  _cECO_LVL_VALU, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	

			_SPRINTF(pSt0, "(m)");
			DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20+145, DpCLB_LVL_TITL_Y1+15, _cECO_LVL_VALU, _cBGD_SCRN, _fE17HsB, pSt0); 

			DpSTR_GuiList(TEXT_LIST_MAX_VALUE);
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+50, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+50, _cLight_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);
			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+50, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+50, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);

			DpSTR_GuiList(TEXT_LIST_MIN_VALUE);		

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+90, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+90, _cLight_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);

			DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+90, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
			DpSTR_GuiLeft_KOR(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+90, _cHeavy_level, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	

			DpSTR_GuiList(TEXT_LIST_TIME);	
			DpSTR_GuiLeft_KOR(DpCLB_GRP_X0+(DpCLB_GRP_WD/2), DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsMKOR, gDpStr.Text_list);			
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
			{
				case MnDS0_INTV_01S:
					_SPRINTF(lDpClb.pStr[0], "(min)");
					DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2)+50, DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
					break;
				case MnDS0_INTV_10M:
				case MnDS0_INTV_10S:
				case MnDS0_INTV_01M:
					_SPRINTF(lDpClb.pStr[0], "(hour)");
					DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2)+50, DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
					break;					
				case MnDS0_INTV_01H:
					_SPRINTF(lDpClb.pStr[0], "(day)");
					DpSTR_GuiLeft(DpCLB_GRP_X0+(DpCLB_GRP_WD/2)+50, DpCLB_GRP_Y0 + DpCLB_GRP_HT +36, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
					break;
			}
			break;
	}
	
	

#if 0
	_SPRINTF(lDpClb.pStr[0], _sLight_level);

	DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+15, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y0+15, _cLight_level, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);

	_SPRINTF(lDpClb.pStr[0], _sHeavy_level);


	DpFIG_DrwLinH(DpECO_LVL_TITL_X0, DpCLB_LVL_TITL_Y1, DpECO_BOX_FG_WD, _cSD_WHITE);

	DpFIG_DrwRect(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+15, DpECO_LVL_CH_WD, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpECO_LVL_VALU_X0-20, DpCLB_LVL_TITL_Y1+15, _cECO_LVL_VALU, _cBGD_SCRN, _fE17HsB, lDpClb.pStr[0]);	
#endif
	
}


void DpClbLvl_StrChnnl(void)
{
	U08 lang = MnSYS_PrGetBase_Item(MnSYS_LANG_KOR);
	U16 val;
	U08 ch = ScCLB_GetCh();

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE)
		return;

	switch(ch)
	{
		case APP_CH_1:		_SPRINTF(lDpClb.pStr[0], _sCH_1);	DpSTR_GuiList(TEXT_LIST_CH_1);	break;
		case APP_CH_2:		_SPRINTF(lDpClb.pStr[0], _sCH_2);	DpSTR_GuiList(TEXT_LIST_CH_2);	break;
	}

	switch(lang)
	{
		case MnSYS_LANG_ENG:
			DpFIG_DrwRect(DpECO_LVL_TITL_X0+40, DpECO_GRP_Y0-35, DpECO_LVL_CH_WD+10, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL); // Clear
			DpSTR_GuiLeft(DpECO_LVL_TITL_X0+40, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, lDpClb.pStr[0]);
			break;
		case MnSYS_LANG_KOR:

			DpFIG_DrwRect(DpECO_LVL_TITL_X0+40,  DpECO_GRP_Y0-35, DpECO_LVL_CH_WD+10, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
			DpSTR_GuiLeft_KOR(DpECO_LVL_TITL_X0+40, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsBKOR, gDpStr.Text_list);	
			break;
	}	


	val = MnSYS_PrGet_site_name(ch);

	_SPRINTF(lDpClb.pStr[0], "(%c%d%d)",val/100,(val%100)/10,(val%100)%10);


	DpFIG_DrwRect(DpECO_LVL_TITL_X0+40+70+20, DpECO_GRP_Y0-35, DpECO_LVL_CH_WD+10, DpECO_LVL_CH_HT, _cBGD_SCRN, DpFIG_FILL);	// Clear
	DpSTR_GuiLeft(DpECO_LVL_TITL_X0+40+70+20, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsN, lDpClb.pStr[0]);

}

void DpClbLvl_StrValue(void)
{
	U16 valu_light_min,valu_light_max;
	U16 valu_heavy_min,valu_heavy_max;
	U16 cnt = DaSav_GetCnt();

	valu_light_min = lDpClb.min[MsCAL_THR_LIGHT];	
	valu_heavy_min = lDpClb.min[MsCAL_THR_HEAVY];
	valu_light_max = lDpClb.max[MsCAL_THR_LIGHT];	
	valu_heavy_max = lDpClb.max[MsCAL_THR_HEAVY];

#if 0
	if(ScHYB_PrGet_Unit_() == ScHYB_UNIT_FEET)
		valu = (U16)MsCAL_Meter2Feet(valu);
#endif

	if(cnt>0)
	{
		if(valu_light_max >= 1000)	_SPRINTF(lDpClb.pStr[0], "%2d.%02d", valu_light_max/100, valu_light_max%100);
		else						_SPRINTF(lDpClb.pStr[0], "%1d.%02d", valu_light_max/100, valu_light_max%100);

		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y0+50, DpECO_LVL_CH_WD+30, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y0+50, _cLight_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);

		if(valu_light_min >= 1000)	_SPRINTF(lDpClb.pStr[0], "%2d.%02d", valu_light_min/100, valu_light_min%100);
		else						_SPRINTF(lDpClb.pStr[0], "%1d.%02d", valu_light_min/100, valu_light_min%100);


		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y0+90, DpECO_LVL_CH_WD+30, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y0+90, _cLight_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);

		if(valu_heavy_max >= 1000)	_SPRINTF(lDpClb.pStr[0], "%2d.%02d", valu_heavy_max /100, valu_heavy_max %100);
		else						_SPRINTF(lDpClb.pStr[0], "%1d.%02d", valu_heavy_max /100, valu_heavy_max %100);


		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y1+50, DpECO_LVL_CH_WD+30, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y1+50, _cHeavy_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);

		if(valu_heavy_min >= 1000)	_SPRINTF(lDpClb.pStr[0], "%2d.%02d", valu_heavy_min /100, valu_heavy_min %100);
		else						_SPRINTF(lDpClb.pStr[0], "%1d.%02d", valu_heavy_min /100, valu_heavy_min %100);


		if(valu_light_min > 1000)	_SPRINTF(lDpClb.pStr[0],"-");
		if(valu_light_max > 1000)	_SPRINTF(lDpClb.pStr[0],"-");
		if(valu_heavy_min > 1000)	_SPRINTF(lDpClb.pStr[0],"-");
		if(valu_heavy_max > 1000)	_SPRINTF(lDpClb.pStr[0],"-");

		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y1+90, DpECO_LVL_CH_WD+30, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y1+90, _cHeavy_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);	
	}
	else
	{
		//_SPRINTF(lDpClb.pStr[0], "R : %d", cnt);
		//DpSTR_GuiLeft(DpECO_LVL_TITL_X0-100, DpECO_GRP_Y0-35, _cSD_WHITE, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);

		_SPRINTF(lDpClb.pStr[0], "-");
		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y0+50, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+100, DpCLB_LVL_TITL_Y0+50, _cLight_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);

		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y0+90, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+100, DpCLB_LVL_TITL_Y0+90, _cLight_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);
	
		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y1+50, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+100, DpCLB_LVL_TITL_Y1+50, _cHeavy_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]);

		DpFIG_DrwRect(DpECO_LVL_VALU_X0+70, DpCLB_LVL_TITL_Y1+90, DpECO_LVL_CH_WD, DpECO_LVL_VALU_HT, _cBGD_SCRN, DpFIG_FILL);
		DpSTR_GuiLeft(DpECO_LVL_VALU_X0+100, DpCLB_LVL_TITL_Y1+90, _cHeavy_level, _cBGD_SCRN, _fE22HsB, lDpClb.pStr[0]); 
	}
}



//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions - Parameter Box - List
//------------------------------------------------------------------------------------------------------------------------------
void DpClbVal_SetString(U08 iFn, S32 val)
{
#if 0
	switch(iFn)
	{	// TVG (OFF & ON)
		case ScCLB_F00_FREQ:
			switch(val)
			{
				case ScCLB_FREQ_130K:		_SPRINTF(lDpClb.pStr[0], "130K");		break;
				case ScCLB_FREQ_160K:		_SPRINTF(lDpClb.pStr[0], "160K");		break;
				case ScCLB_FREQ_270K:		_SPRINTF(lDpClb.pStr[0], "270K");		break;
				case ScCLB_FREQ_380K:		_SPRINTF(lDpClb.pStr[0], "380K");		break;
				default:					_SPRINTF(lDpClb.pStr[0], _sNG);			break;
			}
			break;
		case ScCLB_F01_TX_WAV:				_SPRINTF(lDpClb.pStr[0], "%d", val);	break;
		case ScCLB_F02_RX_GAIN:				_SPRINTF(lDpClb.pStr[0], "%d", val);	break;
		case ScCLB_F03_RX_TRANS:			_SPRINTF(lDpClb.pStr[0], "%d", val);	break;	
		case ScCLB_F04_RX_AMP:
			switch(val)
			{
				case ScCLB_RX_AMP_x47:		_SPRINTF(lDpClb.pStr[0], "x47");		break;
				case ScCLB_RX_AMP_x100:		_SPRINTF(lDpClb.pStr[0], "x100");		break;
				default:					_SPRINTF(lDpClb.pStr[0], _sNG); 		break;
			}
			break;
		case ScCLB_F05_TVG_fEN:
			if(val == ScCLB_TVG_MIN)		_SPRINTF(lDpClb.pStr[0], "OFF");
			else							_SPRINTF(lDpClb.pStr[0], "%d", val);
			break;
		case ScCLB_F06_TVG_CUSTOM:			
			switch(ScCB2_GetSelStep())
			{
				case SCRN_L2_SEL_STEP0:		_SPRINTF(lDpClb.pStr[0], "%d", val);
											break;
				case SCRN_L2_SEL_STEP1:		_SPRINTF(lDpClb.pStr[0], "%d", val);
											break;
				default:					break;
			}
			break;
			_SPRINTF(lDpClb.pStr[0], "%d", val);	break;
		// Dual Sensor
		case ScCLB_FNC_NUM:
			switch(val)
			{
				case ScCLB_CH_0:	_SPRINTF(lDpClb.pStr[0], _sCh_1);				break;
				case ScCLB_CH_1:	_SPRINTF(lDpClb.pStr[0], _sCh_2);				break;
			}
			break;
		// Not Define
		default:					_SPRINTF(lDpClb.pStr[0], "%s", _sTBD);			break;
	}
#endif
}

void DpClbBox_LstTitle(U08 iFn)
{
#if 0
	U08 page = DpCLB_PG_0;
	U16 y0c, y0s;
	U16 x0c = DpCLB_BOX_L0_SB_X0;
	U16 x0s = DpCLB_BOX_L0_TL_X0;
	U16 w_c = DpCLB_BOX_Lx_SB_WD;
	U16 h_c = DpCLB_BOX_Lx_SB_HT;

	switch(iFn)
	{	// TVG (OFF & ON)
		case ScCLB_F00_FREQ:		_SPRINTF(lDpClb.pStr[0], _sFREQ);			break;
		case ScCLB_F01_TX_WAV:		_SPRINTF(lDpClb.pStr[0], _sTxWave);			break;
		case ScCLB_F02_RX_GAIN:		_SPRINTF(lDpClb.pStr[0], _sRxGain);			break;
		case ScCLB_F03_RX_TRANS:	_SPRINTF(lDpClb.pStr[0], _sRxTrans);		break;
		case ScCLB_F04_RX_AMP:		_SPRINTF(lDpClb.pStr[0], _sRxAMP);			break;
		case ScCLB_F05_TVG_fEN:		_SPRINTF(lDpClb.pStr[0], _sTVG);			break;
		case ScCLB_F06_TVG_CUSTOM:	_SPRINTF(lDpClb.pStr[0], _sTVG_Custom);		break;
		// Not Define
		default:					_SPRINTF(lDpClb.pStr[0], _sNG);				break;
	}

	if		(iFn >= (ScCLB_FNC_PAGE*2))		page = DpCLB_PG_2;
	else if (iFn >= (ScCLB_FNC_PAGE*1))		page = DpCLB_PG_1;
	else									page = DpCLB_PG_0;

	y0c = DpCLB_BOX_L0_SB_Y0 + (30 * (iFn - (ScCLB_FNC_PAGE*page)));
	y0s = DpCLB_BOX_L0_TL_Y0 + (30 * (iFn - (ScCLB_FNC_PAGE*page)));

	DpFIG_DrwRect(x0c, y0c, w_c, h_c, _cSD_BLACK, 0);
	DpSTR_GuiLeft(x0s, y0s, _cSD_LIGHTGRAY, _cSD_BLACK, _fE17HsB, lDpClb.pStr[0]);
#endif
}

void DpClbBox_LstValue(U08 iFn, S32 val)
{
#if 0
	U08 page = DpCLB_PG_0;
	U16 y0c, y0s;
	U16 x0c = DpCLB_BOX_L0_VL_X0;
	U16 x0s = DpCLB_BOX_L0_VL_X0;
	U32 col = _cCLB_BOX_VALU;
	sFONT sFt = _fE17HsB;

	DpClbVal_SetString(iFn, val);

	switch(iFn)
	{	// TVG (OFF & ON)
		case ScCLB_F00_FREQ:
		case ScCLB_F01_TX_WAV:
		case ScCLB_F02_RX_GAIN:	
		case ScCLB_F03_RX_TRANS:	
		case ScCLB_F04_RX_AMP:
		case ScCLB_F05_TVG_fEN:		col = _cCLB_BOX_VALU;	sFt = _fE17HsB;		break;
		case ScCLB_F06_TVG_CUSTOM:	return;
		// Not Define
		default:					col = _cSD_DARKGRAY;	sFt = _fE12HsM;		break;
	}

	if		(iFn >= (ScCLB_FNC_PAGE*2))		page = DpCLB_PG_2;
	else if (iFn >= (ScCLB_FNC_PAGE*1))		page = DpCLB_PG_1;
	else									page = DpCLB_PG_0;

	y0c = DpCLB_BOX_L0_SB_Y0 + (30 * (iFn - (ScCLB_FNC_PAGE*page)));
	y0s = DpCLB_BOX_L0_TL_Y0 + (30 * (iFn - (ScCLB_FNC_PAGE*page)));

	DpFIG_DrwRect(x0c, y0c, 40, 20, _cSD_BLACK, DpFIG_FILL);
	DpSTR_GuiLeft(x0s-5, y0s, col, _cSD_BLACK, sFt, lDpClb.pStr[0]);
#endif
}

void DpClbBox_LstAll(void)
{
#if 0
	U08 i, page, nLt, nFn;
	U16 bar_x0 = DpCLB_BOX_PB_X0;
	U16 bar_wd = DpCLB_BOX_PB_WD;
	U16 bar_ht = DpCLB_BOX_PB_HT;
	S32 val[ScCLB_OPT_CH_SEL+1] = {0, };
	U16 bar_y0[DpCLB_PG_NUM] = {DpCLB_BOX_PB_Y0, DpCLB_BOX_PB_Y1, DpCLB_BOX_PB_Y2};

	// Get Parameter (Page #0)
#if 0
	for(i=0; i<ScCLB_FNC_NUM; i++)
		val[i] = ScCLB_PrGet_Value(iCh, i);
#endif
	nLt = ScCB1_GetIdxFunc();

	// Parameter Box - Background
	DpFIG_DrwRect(DpCLB_BOX_FG_X0, DpCLB_BOX_FG_Y0, DpCLB_BOX_FG_WD, DpCLB_BOX_FG_HT, _cSD_BLACK, DpFIG_FILL);

	if		(nLt >= (ScCLB_FNC_PAGE*2))		page = DpCLB_PG_2;
	else if (nLt >= (ScCLB_FNC_PAGE*1))		page = DpCLB_PG_1;
	else									page = DpCLB_PG_0;

	// Disp Box - Page Bar
	DpFIG_DrwRect(bar_x0, bar_y0[page], bar_wd, bar_ht, _cSD_DARKGRAY, DpFIG_FILL);

	// Disp Box - Title & Value
	switch(page)
	{
		case DpECO_PG_0:	nFn = ScCLB_FNC_PAGE;							break;
		case DpECO_PG_1:
		case DpECO_PG_2:	nFn = ScCLB_FNC_NUM-(ScCLB_FNC_PAGE*page);		break;
		default:			return;
	}

	for(i=0; i<nFn; i++)
	{
		DpClbBox_LstTitle(i+(ScCLB_FNC_PAGE*page));
		DpClbBox_LstValue(i+(ScCLB_FNC_PAGE*page), val[i+(ScCLB_FNC_PAGE*page)]);
	}
#endif
}

void DpClbL1l_SelBox(void)
{
	U08 i;
	U16 aSl[DpSCR_SBX_aNUMB];
#if 0
	U08 iFn = ScCB1_GetIdxFunc();

	for(i=0; i<ScCLB_FNC_PAGE; i++)
		DpFIG_DrwRect(lDpClb.sbx.aX0[i], lDpClb.sbx.aY0[i], lDpClb.sbx.aWd[i], lDpClb.sbx.aHt[i], _cSD_BLACK, 2);

	if(MnFTR_PrGet_SsChn() == MnFTR_SS_DUAL)
	{
		i = ScCLB_FNC_NUM;
		DpFIG_DrwRect(lDpClb.sbx.aX0[i], lDpClb.sbx.aY0[i], lDpClb.sbx.aWd[i], lDpClb.sbx.aHt[i], _cSD_BLACK, 2);
	}

	if(iFn >= ScCLB_FNC_PAGE)
		iFn -= ScCLB_FNC_PAGE;

	aSl[DpSCR_SBX_aX0] = lDpClb.sbx.aX0[iFn];
	aSl[DpSCR_SBX_aY0] = lDpClb.sbx.aY0[iFn];
	aSl[DpSCR_SBX_aWd] = lDpClb.sbx.aWd[iFn];
	aSl[DpSCR_SBX_aHt] = lDpClb.sbx.aHt[iFn];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();
#endif

    i =ScCLB_OPT_CH_SEL;
	DpFIG_DrwRect(lDpClb.sbx.aX0[i], lDpClb.sbx.aY0[i], lDpClb.sbx.aWd[i], lDpClb.sbx.aHt[i], _cSD_BLACK, 2);

	aSl[DpSCR_SBX_aX0] = lDpClb.sbx.aX0[ScCLB_OPT_CH_SEL];
	aSl[DpSCR_SBX_aY0] = lDpClb.sbx.aY0[ScCLB_OPT_CH_SEL];
	aSl[DpSCR_SBX_aWd] = lDpClb.sbx.aWd[ScCLB_OPT_CH_SEL];
	aSl[DpSCR_SBX_aHt] = lDpClb.sbx.aHt[ScCLB_OPT_CH_SEL];

	DpFIG_DrwRect(aSl[DpSCR_SBX_aX0], aSl[DpSCR_SBX_aY0], aSl[DpSCR_SBX_aWd], aSl[DpSCR_SBX_aHt], _cBTN_FG_SELE, 2);
	DpSCR_LnHrBttn();

}

void DpClbL2v_StrMinMax(U08 iFn)
{

}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L3 - Value
//------------------------------------------------------------------------------------------------------------------------------
void DpCB2_ValUpdat(U08 fClr)
{
#if 0
	U16 x0t = DpECO_BOX_L0_TL_X0 + 30;
	U16 y0t[2] = {DpECO_BOX_L0_TL_Y0+40, DpECO_BOX_L0_TL_Y0+80};
	U08 iFn = ScCB1_GetIdxFunc();
	S32 val = ScCB2_GetValue();
	U08 iCh = ScECH_PrGet_Chnnl();


	// Value
	DpClbVal_SetString(iFn, val);



	switch(iFn)
	{
		case ScCLB_F00_FREQ:
		case ScCLB_F01_TX_WAV:
		case ScCLB_F02_RX_GAIN:	
		case ScCLB_F03_RX_TRANS:
		case ScCLB_F04_RX_AMP:
		case ScCLB_F05_TVG_fEN:
			DpFIG_DrwRect(x0t-15, y0t[0]+55, 90, 30, _cPOP_BG_WND, DpFIG_FILL);
			DpSTR_GuiLeft(x0t-15, y0t[0]+55, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, lDpClb.pStr[0]);
			break;			
		case ScCLB_F06_TVG_CUSTOM:
			switch(ScCB2_GetSelStep())
			{
				case SCRN_L2_SEL_STEP0:		_SPRINTF(lDpClb.pStr[1], "%d", ScCLB_PrGet_Tvg_Custom(iCh,val));
											DpFIG_DrwRect(x0t-15, y0t[0]+55, 90, 30, _cPOP_BG_WND, DpFIG_FILL);
											DpSTR_GuiLeft(x0t-15, y0t[0]+55, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, lDpClb.pStr[0]);
											DpFIG_DrwRect(x0t+90, y0t[0], 60, 30, _cPOP_BG_WND, DpFIG_FILL);
											DpSTR_GuiLeft(x0t+90, y0t[0], _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE17HsB, lDpClb.pStr[0]);
											DpFIG_DrwRect(x0t+90, y0t[0]+25, 60, 30, _cPOP_BG_WND, DpFIG_FILL);
											DpSTR_GuiLeft(x0t+90, y0t[0]+25, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE17HsB, lDpClb.pStr[1]); 	
											break;
				case SCRN_L2_SEL_STEP1:		_SPRINTF(lDpClb.pStr[1], "%d", ScCLB_PrGet_Tvg_x_axis(iCh));				
											DpFIG_DrwRect(x0t-15, y0t[0]+55, 90, 30, _cPOP_BG_WND, DpFIG_FILL);
											DpSTR_GuiLeft(x0t-15, y0t[0]+55, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, lDpClb.pStr[0]);
											DpFIG_DrwRect(x0t+90, y0t[0], 60, 30, _cPOP_BG_WND, DpFIG_FILL);
											DpSTR_GuiLeft(x0t+90, y0t[0], _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE17HsB, lDpClb.pStr[1]);
											DpFIG_DrwRect(x0t+90, y0t[0]+25, 60, 30, _cPOP_BG_WND, DpFIG_FILL);
											DpSTR_GuiLeft(x0t+90, y0t[0]+25, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE17HsB, lDpClb.pStr[0]); 
											break;
				default:					break;
			}

			break;
		default:
			DpFIG_DrwRect(x0t, y0t[0]+55, 80, 30, _cPOP_BG_WND, DpFIG_FILL);
			DpSTR_GuiLeft(x0t, y0t[0]+55, _cPOP_ST_VAL_SEL, _cPOP_BG_WND, _fE22HsB, _sNG);
			break;
	}
#endif
}

void DpCB2_ValIntro(void)
{
#if 0
	U08 fClr = _F_T;
	U16 x0t = DpCLB_BOX_L0_TL_X0;
	U16 y0t = DpCLB_BOX_L0_TL_Y0;
	U32 cOld  = _cPOP_ST_OLD;
	U32 cIdle = _cPOP_ST_VAL_IDL;
	U32 cBkgd = _cPOP_BG_WND;
	U08 iCh = ScECH_PrGet_Chnnl();
	U08 iFn = ScCB1_GetIdxFunc();

	// Background
	DpFIG_DrwRect(DpECO_BOX_FG_X0, DpECO_BOX_FG_Y0, DpECO_BOX_FG_WD, DpECO_BOX_FG_HT, _cPOP_BG_WND, DpFIG_FILL);
	DpFIG_DrwRect(DpECO_BOX_FG_X0, DpECO_BOX_FG_Y0, DpECO_BOX_FG_WD, DpECO_BOX_FG_HT, _cPOP_BG_WND, DpFIG_FILL);

	// Title
	switch(iFn)
	{
		case ScCLB_F00_FREQ:		_SPRINTF(lDpClb.pStr[0], _sFREQ);							break;
		case ScCLB_F01_TX_WAV:		_SPRINTF(lDpClb.pStr[0], _sTX_WAV);							break;
		case ScCLB_F02_RX_GAIN:		_SPRINTF(lDpClb.pStr[0], _sRX_GAIN);						break;
		case ScCLB_F03_RX_TRANS:	_SPRINTF(lDpClb.pStr[0], _sRX_TRANS);						break;	
		case ScCLB_F04_RX_AMP:		_SPRINTF(lDpClb.pStr[0], _sRX_AMP);							break;
		case ScCLB_F05_TVG_fEN:		_SPRINTF(lDpClb.pStr[0], _sTVG);							break;	
		case ScCLB_F06_TVG_CUSTOM:	_SPRINTF(lDpClb.pStr[0], _sTVG_Custom);						break;	
		// Not Define
		default:					_SPRINTF(lDpClb.pStr[0], _sNG);								break;
	}
	DpSTR_GuiLeft(x0t, DpECO_BOX_L0_TL_Y0, _cSD_WHITE, _cPOP_BG_WND, _fE22HsB, lDpClb.pStr[0]);

	// MIN / MAX
	DpClbL2v_StrMinMax(iFn);
	
	// Anouncement
	switch(iFn)
	{
		case ScCLB_F00_FREQ:
		case ScCLB_F01_TX_WAV:	
		case ScCLB_F02_RX_GAIN:
		case ScCLB_F03_RX_TRANS:	
		case ScCLB_F04_RX_AMP:
		case ScCLB_F05_TVG_fEN:		
		case ScCLB_F06_TVG_CUSTOM:	DpSTR_GuiLeft(x0t-5,  y0t+130, cIdle, cBkgd, _fE12HsM, _sRpt_PrsKeep);		break;
		// Not Define
		default:		break;
	}

	// Old
	DpClbVal_SetString(iFn, ScCLB_PrGet_Value(iCh, iFn));
	DpSTR_GuiLeft(x0t+120, y0t+100, cOld, cBkgd, _fE17HsB, lDpClb.pStr[0]);
	// Display
	DpCB2_ValUpdat(fClr);
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L1 - List
//------------------------------------------------------------------------------------------------------------------------------
void DpCB1_LstUpdat(void)
{
	DpClbBox_LstAll();
	DpClbL1l_SelBox();
}

void DpCB1_LstIntro(void)
{
	// Clear Tracking Width
	//DpFIG_DrwRect(DpECO_GRP_X0, DpECO_GRP_Y0-15, DpECO_GRP_WD, 8, _cBGD_SCRN, DpFIG_FILL);

	DpCB1_LstUpdat();
	DpSCR_UpdtBttn(SCRN_L1_LIST);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - L0 - Function
//------------------------------------------------------------------------------------------------------------------------------
void DpCB0_FncStdBy(U08 range)
{
	U32 dat_intv;

	switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
	{
		case MnDS0_INTV_01S:	dat_intv = SAV_INTERVAL_01S;	break;
		case MnDS0_INTV_10S: 	dat_intv = SAV_INTERVAL_10S;	break;
		case MnDS0_INTV_01M: 	dat_intv = SAV_INTERVAL_01M;	break;
		case MnDS0_INTV_10M: 	dat_intv = SAV_INTERVAL_10M;	break;
		case MnDS0_INTV_01H: 	dat_intv = SAV_INTERVAL_01H;	break;
		default:												break;
	}

	if((gTmr.c.c01sec)>(dat_intv+1))
		lDpClb.flag = _F_T;

	if(lDpClb.flag == _F_T)
	{
		DpClbGrp_DrawLive();
		//DpClbLvl_StrValue();
		DpClbLvl_StrValue();
		lDpClb.flag = _F_F;
		gTmr.c.c01sec = 0;
	}




}

void DpCB0_FncIntro(void)
{	
	U08 i;
	U16 sn_x0 = DpCLB_GRP_X0;
	U16 sn_y0 = DpCLB_GRP_Y0 + DpCLB_GRP_HT + 6;
	U16 sn_xG = DpCLB_GRP_WD_CURSOR;
	U16 empty = MnMSR_BaseGet_Ch_Value(ScCLB_GetCh(), MnMS0_OPT_SINGLE_EMPTY);
	U16 val = MnMSR_BaseGet_Ch_Value(ScCLB_GetCh(), MnMS0_OPT_SINGLE_EMPTY);
	U16 time1,time2;

	U08 type = MnFTR_PrGet_SsChn();

	if(type == MnFTR_SS_SINGLE)	
		ScCLB_SetCh(APP_CH_1);


	DpCLB_InitVari();
	// Title
	DpTTB_UdtIntro(TEXT_LIST_DATA_TREND_SCREEN, 260, _cTTB_ST_CALIB);
	// Screen
	DISP_IntroScrn();
	
	DpClbLvl_StrChnnl();
	DpClbLvl_StrTitle();
	// Graph - Boundary
	//DpFIG_DrwRect(DpCLB_GRP_X0-4, DpCLB_GRP_Y0-4, DpCLB_GRP_WD+8, DpCLB_GRP_HT+8, _cCLB_GRP_BDR, 2);
	//DpFIG_DrwLinH(DpCLB_GRP_X0, DpCLB_GRP_Y0, DpCLB_GRP_WD, _cTrend_line);
	for(i=0; i<6; i++)
	{		
		if(val >= 1000) _SPRINTF(lDpClb.pStr[0], "%2d.%02d", val/100, val%100);
		else if(val>0)	_SPRINTF(lDpClb.pStr[0], "%1d.%02d", val/100, val%100);
		else			_SPRINTF(lDpClb.pStr[0], "		 0");
		DpFIG_DrwLinH(DpCLB_GRP_X0, DpCLB_GRP_Y0+(45*i), DpCLB_GRP_WD, _cTrend_line);
		DpSTR_GuiLeft(DpCLB_GRP_X0-45, DpCLB_GRP_Y0+(45*i)-8, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
		val -= empty/5;
	}

	_SPRINTF(lDpClb.pStr[0], "(m)");
	DpSTR_GuiLeft(DpCLB_GRP_X0-45, DpCLB_GRP_Y0-30, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);

	switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
	{
		case MnDS0_INTV_01S: 
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	time1 = 12;  break;
				case MnDS0_DISPLAY_TERM_2:	time1 = 24;	break;
			}
			break;
		case MnDS0_INTV_10S:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	time1 = 120;  break;
				case MnDS0_DISPLAY_TERM_2:	time1 = 240;  break;
			}
			break;					
		case MnDS0_INTV_01M:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	time1 = 12;  break;
				case MnDS0_DISPLAY_TERM_2:	time1 = 24;  break;
			}
			break;					
		case MnDS0_INTV_10M:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	time1 = 120;  break;
				case MnDS0_DISPLAY_TERM_2:	time1 = 240;  break;
			}
			break;					
		case MnDS0_INTV_01H:
			switch(MnDAT_SavPrGet_Value(MnDS0_OPT_DISPLAY_TERM))
			{
				case MnDS0_DISPLAY_TERM_1:	time1 = 30;  break;
				case MnDS0_DISPLAY_TERM_2:	time1 = 60;  break;
			}
			break;					
		default:										
			break;
	}

	time2 = time1;
	for(i=0; i<7; i++)
	{
		time2 =time1- ((time1*i)/6);
		DpFIG_DrwLinV(sn_x0+ (sn_xG*i), sn_y0-8, 6, _cECO_GRP_BDR);
		_SPRINTF(lDpClb.pStr[0], "-%d", time2);
		DpSTR_GuiLeft(sn_x0+ (sn_xG*i)-12, sn_y0+5, _cTrend_line, _cBGD_SCRN, _fE12HsM, lDpClb.pStr[0]);
	}
	


#if 0
	DpFIG_DrwRect(sn_x0,	 sn_y0+35,   40, 7, _cECO_GRP_BDR, DpFIG_FILL);
	DpFIG_DrwCirc(sn_x0,	 sn_y0+35+4, 3,	  _cECO_GRP_BDR, _F_T);
	DpFIG_DrwCirc(sn_x0, sn_y0+35+4, 3,	  _cECO_GRP_BDR, _F_T);
	DpFIG_DrwTria(sn_x0, sn_y0+35,	sn_x0+10, sn_y0+35,	 sn_x0+10, sn_y0+35-7,  _cECO_GRP_BDR);
	DpFIG_DrwTria(sn_x0, sn_y0+35+7, sn_x0+10, sn_y0+35+7, sn_x0+10, sn_y0+35+15, _cECO_GRP_BDR);

	DpFIG_DrwRect(sn_x0+ DpECO_GRP_WD-45,	 sn_y0+35,   40, 7, _cECO_GRP_BDR, DpFIG_FILL);
	DpFIG_DrwCirc(sn_x0+ DpECO_GRP_WD-45,	 sn_y0+35+4, 3,	  _cECO_GRP_BDR, _F_T);
	DpFIG_DrwCirc(sn_x0+ DpECO_GRP_WD-45+40, sn_y0+35+4, 3,	  _cECO_GRP_BDR, _F_T);
	DpFIG_DrwTria(sn_x0+ DpECO_GRP_WD-45+40, sn_y0+35,   sn_x0+ DpECO_GRP_WD-45+40-10, sn_y0+35,   sn_x0+ DpECO_GRP_WD-45+40-10, sn_y0+35-8,	 _cECO_GRP_BDR);
	DpFIG_DrwTria(sn_x0+ DpECO_GRP_WD-45+40, sn_y0+35+7, sn_x0+ DpECO_GRP_WD-45+40-10, sn_y0+35+7, sn_x0+ DpECO_GRP_WD-45+40-10, sn_y0+35+8+7, _cECO_GRP_BDR);
#endif

	DpCB0_FncStdBy(0);

	// Box & Level zone
	//DpClbBox_LstAll();
	//DpClbLvl_StrIntro();
	//DpClbGrp_DrawLive();

	// Button
	DpSCR_UpdtBttn(SCRN_L0_FUNC);
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set
void DpCLB_Set_Trend_flag(U08 flag)				{		lDpClb.flag =flag;		}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void DpCLB_InitVari(void)
{
	U16 sn_y0 = DpCLB_GRP_Y0 + DpCLB_GRP_HT + 6;

	_MEMSET(lDpClb.pStr[0], 0, sizeof(lDpClb.pStr[0]));
	_MEMSET(lDpClb.pStr[1], 0, sizeof(lDpClb.pStr[0]));

#if 0
	// Sel-Box Position
	for(i=0; i<ScCLB_FNC_NUM; i++)
	{
		if		(i >= (ScECO_FNC_PAGE*2))		lDpClb.sbx.aY0[i] = y0 + (ht * (i-(ScECO_FNC_PAGE*2)));
		else if	(i >=  ScECO_FNC_PAGE)			lDpClb.sbx.aY0[i] = y0 + (ht * (i-(ScECO_FNC_PAGE)  ));
		else									lDpClb.sbx.aY0[i] = y0 + (ht * (i));

		lDpClb.sbx.aX0[i] = DpECO_BOX_L0_SB_X0;
		lDpClb.sbx.aWd[i] = DpECO_BOX_Lx_SB_WD;
		lDpClb.sbx.aHt[i] = DpECO_BOX_Lx_SB_HT;
	}
#endif
	lDpClb.sbx.aX0[ScCLB_OPT_CH_SEL] = DpECO_LVL_TITL_X0+30 - 8;
	lDpClb.sbx.aY0[ScCLB_OPT_CH_SEL] = DpECO_GRP_Y0-35 - 3;
	lDpClb.sbx.aWd[ScCLB_OPT_CH_SEL] = DpECO_LVL_CH_WD+130;
	lDpClb.sbx.aHt[ScCLB_OPT_CH_SEL] = DpECO_LVL_CH_HT;

	lDpClb.sbx.aX0[ScCLB_OPT_TREND_LEFT] = DpCLB_GRP_X0-10;
	lDpClb.sbx.aY0[ScCLB_OPT_TREND_LEFT] = sn_y0+35-12;
	lDpClb.sbx.aWd[ScCLB_OPT_TREND_LEFT] = 60;
	lDpClb.sbx.aHt[ScCLB_OPT_TREND_LEFT] = 40;

	lDpClb.sbx.aX0[ScCLB_OPT_TREND_RIGHT] = DpCLB_GRP_X0+DpECO_GRP_WD-45+40-10;
	lDpClb.sbx.aY0[ScCLB_OPT_TREND_RIGHT] = sn_y0+35-12;
	lDpClb.sbx.aWd[ScCLB_OPT_TREND_RIGHT] = 60;
	lDpClb.sbx.aHt[ScCLB_OPT_TREND_RIGHT] = 40;


	lDpClb.flag = _F_T;

}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

