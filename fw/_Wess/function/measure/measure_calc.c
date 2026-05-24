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
// api
#include "measure_main.h"
// bsp
#include "bsp_adc.h"
#include "bsp_sdram.h"
// app
#include "app_status.h"
#include "app_schd1sec.h"
// display
#include "disp_string.h"
#include "disp_figure.h"
#include "disp_color.h"
// screen
#include "screen_main.h"
#include "screen_hybrid.h"
#include "screen_echo.h"
#include "screen_calib.h"
#include "screen_eco1_list.h"
#include "screen_eco2_value.h"
// measure
#include "measure_calc.h"
// menu
#include "menu_engineer.h"
#include "menu_factory.h"
#include "menu_measure.h"
#include "menu_output.h"
#include "menu_data.h"
#include "menu_test.h"
// self
#include "measure_calc.h"
// function
#include "output_current.h"
#include "output_pcd.h"
#include "data_commu.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------
U16 test_cnt = 0;


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MsCAL_LS lMsCal;

// SDRAM_Prof(0xD0400000~ 0xD0450000 /0xD0450000~ 0xD0500000 ) - / SDRAM_ADDR(0xD0400000~ 0xD0800000)
U16 *SDRAM_aEco_prof_S0 = (U16 *)SDRAM_PROFILE_S0_ADDR;
U16 *SDRAM_aEco_prof_S1 = (U16 *)SDRAM_PROFILE_S1_ADDR;
U16 *SDRAM_aEco_prof_S2 = (U16 *)0xD0500000;
U16 *SDRAM_aEco_prof_S3 = (U16 *)0xD0600000;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


void MsCAL_InitVari(void)
{
	U16 i, j;

	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lMsCal.stp3_dist[MsCAL_CH_S0][j] = MnMSR_BaseGet_Value(MnMS0_OPT_CH1_EMPTY);
		lMsCal.stp3_sldg[MsCAL_CH_S0][j] = 0;
		lMsCal.rslt_dist[MsCAL_CH_S0][j] = MnMSR_BaseGet_Value(MnMS0_OPT_CH1_EMPTY);
		lMsCal.rslt_sldg[MsCAL_CH_S0][j] = 0;
		lMsCal.stp3_dist[MsCAL_CH_S1][j] = MnMSR_BaseGet_Value(MnMS0_OPT_CH2_EMPTY);
		lMsCal.stp3_sldg[MsCAL_CH_S1][j] = 0;
		lMsCal.rslt_dist[MsCAL_CH_S1][j] = MnMSR_BaseGet_Value(MnMS0_OPT_CH2_EMPTY);
		lMsCal.rslt_sldg[MsCAL_CH_S1][j] = 0;		
	}
	

	for(i=0; i<MsCAL_PROF_MAX; i++)
	{
		for(j=0; j<ADC_BUFF_MAX; j++)
		{
			SDRAM_aEco_prof_S0[j+(i*ADC_BUFF_MAX)] = 0;
			SDRAM_aEco_prof_S1[j+(i*ADC_BUFF_MAX)] = 0;
			if(i<5)
			{
				lMsCal.aEco_filed_prof[MsCAL_CH_S0][i][j] = 0;
				lMsCal.aEco_filed_prof[MsCAL_CH_S1][i][j] = 0;
			}
		}
	}

	for(i=0; i<MsCAL_CH_NUM; i++)
	{	
		lMsCal.csave_avg[i] = 0;
		lMsCal.asf_r[i] = 0;
		_MEMSET(lMsCal.aEco_rslt[i], 0, sizeof(lMsCal.aEco_rslt[i]));
		_MEMSET(lMsCal.dist_cycl[i], 0, sizeof(lMsCal.dist_cycl[i]));
		_MEMSET(lMsCal.dist_prof[i], 0, sizeof(lMsCal.dist_prof[i]));
		_MEMSET(lMsCal.aEco_real[i], 0, sizeof(lMsCal.aEco_real[i]));
		_MEMSET(lMsCal.save_real[i], 0, sizeof(lMsCal.aEco_real[i]));
		_MEMSET(lMsCal.save_rslt[i], 0, sizeof(lMsCal.aEco_rslt[i]));	
		_MEMSET(lMsCal.aEco_filed_rlst[i], 0, sizeof(lMsCal.aEco_filed_rlst[i]));	
		_MEMSET(lMsCal.aEco_field_real[i], 0, sizeof(lMsCal.aEco_field_real[i]));	

		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{	
			_MEMSET(lMsCal.dist_damp[i][j], 0, sizeof(lMsCal.dist_damp[i][j]));
		}
	}

	lMsCal.diff_dist    = 0;
	lMsCal.diff_sldg    = 0;
	lMsCal.avrg_dist    = 0;
	lMsCal.avrg_sldg    = 0;
	for(i=0; i<MsCAL_CH_NUM; i++)
	{
		lMsCal.thr[i][MsCAL_THR_HEAVY] = ADC_VAL_MAX/2;
		lMsCal.thr[i][MsCAL_THR_LIGHT] = ADC_VAL_MAX/3;
		// Threshold
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{	
			lMsCal.Refilter_cnt[i][j]  = 0;
			lMsCal.Tracking_dist[i][j] = 0;
			lMsCal.fRefilter[i][j]     = Tracking_OFF;
			lMsCal.NOT_Tracking_dist[i][j] = 0;
			lMsCal.NOT_Tracking_dist[i][j] = 0;
		}
		lMsCal.thr_max[i] = 0;
		lMsCal.thr_min[i] = 0;
		// Tracking
		// Error
		lMsCal.f_run[i]		= ERROR_OFF;
		lMsCal.error_sec[i]		= 0;
		lMsCal.signal_ok_sec[i]	= 0;
		lMsCal.signal_ng_sec[i]	= 0;
		lMsCal.f_signal[i]		= SIGNAL_OK;	
		lMsCal.stt[i]		= ApSTT_MSR_IDLE;

		CalPrc_Threshold_Value(i);
		
		lMsCal.valu[i] = 0;

		lMsCal.field_sldg[i] = 0;
		lMsCal.field_dist[i] = 0; 
	}
	lMsCal.mini_sens = APP_CH_1;
	lMsCal.cProf = 0;

	lMsCal.cnt = 0;
	lMsCal.step = 0;


}


void CalPrc_SttCheck(U08 iCh)
{
	U16 stt = ApSTT_GetStatus(iCh);
	U16 err_delay =  MnOUT_ErrPrGet_Value(MnOS3_OPT_ERR_DELAY);

	switch(lMsCal.stt[iCh])
	{
		case ApSTT_MSR_WEAK:
			switch(stt)
			{
				case ApSTT_MSR_TRAC:
				case ApSTT_MSR_OK:
				case ApSTT_MSR_IDLE:
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				case ApSTT_MSR_NG:
				case ApSTT_TPR_NG:
					MsCAL1_InitVari();
					CalPrc_ResetFlag(iCh);
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				default:
					break;
			}
			break;
		case ApSTT_MSR_TRAC:
			switch(stt)
			{
				case ApSTT_MSR_OK:	
				case ApSTT_MSR_WEAK:
				case ApSTT_MSR_IDLE:
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				case ApSTT_MSR_NG:
				case ApSTT_TPR_NG:
					MsCAL1_InitVari();
					CalPrc_ResetFlag(iCh);
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				default:
					break;
			}
			break;			
		case ApSTT_MSR_OK:
			switch(stt)
			{
				case ApSTT_MSR_OK:
					if(ApSCD_GetVl_Prof_Full(iCh)==FALSE)	ApSTT_SetStatus(iCh, ApSTT_MSR_TRAC);
					break;
				case ApSTT_MSR_WEAK:
				case ApSTT_MSR_TRAC:
				case ApSTT_MSR_IDLE:	
					if(ApSCD_GetVl_Prof_Full(iCh)==FALSE)	
					{
						ApSTT_SetStatus(iCh, ApSTT_MSR_TRAC);
						break;
					}
					lMsCal.error_sec[iCh] = 0;
					ApSTT_SetStatus(iCh, ApSTT_MSR_OK);
					break;
				case ApSTT_MSR_NG:
				case ApSTT_TPR_NG:	
					MsCAL1_InitVari();
					CalPrc_ResetFlag(iCh);
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				default:
					break;
			}
			break;
		case ApSTT_MSR_NG:
			switch(stt)
			{
				case ApSTT_MSR_OK:				
				case ApSTT_MSR_WEAK:
				case ApSTT_MSR_TRAC:
					if(++lMsCal.error_sec[iCh]>err_delay)
					{	
						lMsCal.error_sec[iCh]=0;
						ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					}	
					break;						
				case ApSTT_TPR_NG:
				case ApSTT_MSR_IDLE:	
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				default:
					break;
			}
			break;			
		case ApSTT_TPR_NG:
			switch(stt)
			{
				case ApSTT_MSR_OK:				
				case ApSTT_MSR_WEAK:
				case ApSTT_MSR_TRAC:
					if(++lMsCal.error_sec[iCh]>err_delay)
					{	
						lMsCal.error_sec[iCh]=0;
						ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					}	
					break;						
				case ApSTT_MSR_NG:
				case ApSTT_MSR_IDLE:	
					ApSTT_SetStatus(iCh, lMsCal.stt[iCh]);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

}

void CalPrc_ResetFlag(U08 ch)
{
	U16 j,i;

	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lMsCal.Refilter_cnt[ch][j]	= 0;
		lMsCal.Tracking_dist[ch][j] = 0;
		lMsCal.fRefilter[ch][j]	= Tracking_OFF;
	}

	for(i=0; i<MsCAL_PROF_MAX; i++)
	{
		for(j=0; j<ADC_BUFF_MAX; j++)
		{
			if(ch ==APP_CH_1)
				SDRAM_aEco_prof_S0[j+(i*ADC_BUFF_MAX)] = 0;
			if(ch ==APP_CH_2)
				SDRAM_aEco_prof_S1[j+(i*ADC_BUFF_MAX)] = 0;
			if(i<5)
			{
				lMsCal.aEco_filed_prof[ch][i][j] = 0;

			}
		}
	}

	_MEMSET(lMsCal.aEco_rslt[ch], 0, sizeof(lMsCal.aEco_rslt[ch]));
	_MEMSET(lMsCal.dist_cycl[ch], 0, sizeof(lMsCal.dist_cycl[ch]));
	_MEMSET(lMsCal.dist_prof[ch], 0, sizeof(lMsCal.dist_prof[ch]));
	_MEMSET(lMsCal.aEco_real[ch], 0, sizeof(lMsCal.aEco_real[ch]));
	_MEMSET(lMsCal.save_real[ch], 0, sizeof(lMsCal.aEco_real[ch]));
	_MEMSET(lMsCal.save_rslt[ch], 0, sizeof(lMsCal.aEco_rslt[ch]));	
	_MEMSET(lMsCal.aEco_filed_rlst[ch], 0, sizeof(lMsCal.aEco_filed_rlst[ch]));	
	_MEMSET(lMsCal.aEco_field_real[ch], 0, sizeof(lMsCal.aEco_field_real[ch]));	
	
	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{	
		_MEMSET(lMsCal.dist_damp[ch][j], 0, sizeof(lMsCal.dist_damp[ch][j]));
	}


	// Threshold
	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{	
		lMsCal.Refilter_cnt[ch][j]  = 0;
		lMsCal.Tracking_dist[ch][j] = 0;
		lMsCal.fRefilter[ch][j]	   = Tracking_OFF;
		lMsCal.NOT_Tracking_dist[ch][j] = 0;
		lMsCal.NOT_Tracking_dist[ch][j] = 0;
	}
	lMsCal.thr_max[ch] = 0;
	lMsCal.thr_min[ch] = 0;
	// Tracking
	// Error
	lMsCal.f_run[ch] 	= ERROR_OFF;
	lMsCal.error_sec[ch] 	= 0;
	lMsCal.signal_ok_sec[ch] = 0;
	lMsCal.signal_ng_sec[ch] = 0;
	lMsCal.f_signal[ch]		= SIGNAL_OK;	
	lMsCal.stt[ch]		= ApSTT_MSR_IDLE;
	
	CalPrc_Threshold_Value(ch);
	
	lMsCal.valu[ch] = 0;
	
	lMsCal.field_sldg[ch] = 0;
	lMsCal.field_dist[ch] = 0; 

	lMsCal.stt[ch] =  ApSTT_MSR_IDLE;

	ApSCD_Init1Sec(ch);
}

U16 CalPrc_GetAsfCnt(U08 ch, U16 st, U16 thd)
{
	U16 i;
	U16 c = 0;
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 signal_end = empty*1.1;
	U16 asf;
	U08 screen_type = ScECH_GetType();
	U08 ifn = ScEC1_GetIdxFunc();
	U16 val = ScEC2_GetValue();


	if((ScECH_GetLayer() == SCRN_L2_VALU) && (SCRN_GetPage() == SCRN_P2_ECHO))
	{
		switch(screen_type)
		{
			case ScECO_TYPE_REAL:	break;
			case ScECO_TYPE_AVG:
				switch(ifn)
				{
					case ScECO_AVG_THR_LIGHT:	break;
					case ScECO_AVG_THR_HEAVY:	break;
					case ScECO_AVG_ASF_LIGHT:
					case ScECO_AVG_ASF_HEAVY:
						signal_end = val;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}	
	}

	if(st<signal_end)
	{
		for(i=st; i<signal_end; i++)
		{
			if(thd <= lMsCal.aEco_rslt[ch][i])		c++;
			else									break;
		}
		asf = c*13.5;

		if(lMsCal.asf_r[ch]<asf)
		{
			lMsCal.asf_r[ch] = asf;
			if(lMsCal.asf_h[ch]<asf)
				lMsCal.asf_h[ch] = asf;
		}	
		else
			lMsCal.asf_r[ch] = asf;
	}
	
	return c;
}


U16 TPRT_Calib(U08 ch, U16 index)
{
	F32 c_factor;
	U16 return_dist;
	F32 val = MsTPR_GetTprt(ch) * 0.1;

	c_factor = (1410 + (val * 4.6) - (val * val * 0.055) + (val * val * val * 0.00029)) * 0.5;

	return_dist = ((index * 13.5 * 0.000001) * c_factor) * 100;

	return return_dist;
}


void CalPrc_Tprt_Check(U08 ch)
{
	S16 tprt = MsTPR_GetTprt(ch);

	switch(lMsCal.stt[ch])
	{
		case ApSTT_TPR_NG:
			if((tprt < -200) || (tprt > 1000))
    		{
				lMsCal.stt[ch] = ApSTT_TPR_NG;
			}
			else
			{
				lMsCal.stt[ch] = ApSTT_MSR_IDLE;
			}
			break;
		case ApSTT_MSR_NG:		
		case ApSTT_MSR_WEAK:
		case ApSTT_MSR_TRAC:
		case ApSTT_MSR_IDLE:
		case ApSTT_MSR_OK:		
			if((tprt < -200) || (tprt > 1000))
			{
				lMsCal.stt[ch] = ApSTT_TPR_NG;
			}
			break;
		default:				break;
	}
}


void CalPrc_Threshold_Auto_Value(U16 thr_val, U08 type,U08 ch)
{
	U16 per_end;
	S16 range = 0;
	S16 thr;
	U16 i;
	U16 deadz = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 signal_range = empty*1.1;

	lMsCal.thr_min[ch] = MsCAL_THR_MAX;	
	lMsCal.thr_max[ch] = 0;


	switch(lMsCal.stt[ch])
	{
		case ApSTT_MSR_OK:
		case ApSTT_MSR_TRAC:
			if(lMsCal.Tracking_dist[ch][MsCAL_THR_HEAVY] >lMsCal.Tracking_dist[ch][MsCAL_THR_LIGHT])
				per_end = lMsCal.Tracking_dist[ch][MsCAL_THR_HEAVY] + MnTST_PrGet_CH_Value(ch, MnTST_OPT_SINGLE_THR_RANGE);
			else
				per_end = lMsCal.Tracking_dist[ch][type] + MnTST_PrGet_CH_Value(ch, MnTST_OPT_SINGLE_THR_RANGE);

			if(per_end>=signal_range)		per_end = signal_range;
			break;
		case ApSTT_MSR_WEAK:	
			per_end = empty*1.1;
			break;
		default:				
			return;
	}



	for(i=deadz; i<=signal_range; i++)
	{
		if(i<=per_end)
		{
			if(lMsCal.thr_min[ch]>lMsCal.aEco_rslt[ch][i])		lMsCal.thr_min[ch] = lMsCal.aEco_rslt[ch][i];
			if(lMsCal.thr_max[ch]<lMsCal.aEco_rslt[ch][i])		lMsCal.thr_max[ch] = lMsCal.aEco_rslt[ch][i];
		}
	}

	range = lMsCal.thr_max[ch]-lMsCal.thr_min[ch];
	if(range<=0)	range = 0;
	
	thr = (lMsCal.thr_min[ch]+(F32)((range*thr_val)/100));

	if(thr>lMsCal.thr_max[ch])	thr = lMsCal.thr_max[ch];
	if(thr<0)	thr=0;
	if(thr>4095)	thr=4095;

	lMsCal.thr[ch][type] = thr;


}
void CalPrc_Threshold_Value(U08 ch)
{
	U16 thr_light_val = MnMSR_Get_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT);
	U16 thr_heavy_val = MnMSR_Get_Threshold_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY);
	U16 thr_light_mod = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_LIGHT);
	U16 thr_heavy_mod = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_THR_HEAVY);

	

	switch(thr_light_mod)
	{
		case MnMS1_THRESHOLD_AUTO:		CalPrc_Threshold_Auto_Value(thr_light_val, MsCAL_THR_LIGHT,ch);							break;
		case MnMS1_THRESHOLD_MANUAL:	lMsCal.thr[ch][MsCAL_THR_LIGHT] = (thr_light_val*ADC_VAL_MAX)/MnMS1_THR_VAL_MANUAL_MAX;	break;
		default:						break;
	}


	switch(thr_heavy_mod)
	{
		case MnMS1_THRESHOLD_AUTO:		CalPrc_Threshold_Auto_Value(thr_heavy_val, MsCAL_THR_HEAVY,ch);							break;
		case MnMS1_THRESHOLD_MANUAL:	lMsCal.thr[ch][MsCAL_THR_HEAVY] = (thr_heavy_val*ADC_VAL_MAX)/MnMS1_THR_VAL_MANUAL_MAX;	break;
		default:						break;
	}



#if 0
	lMsCal.thr_min[ch] = MsCAL_THR_MAX;	
	lMsCal.thr_max[ch] = 0;

	switch(lMsCal.fRefilter[ch])
	{
		case Tracking_ON:	
			per_end = lMsCal.Tracking_dist[ch] + MsCAL_TRACK_RANGE;	
			if(per_end>=empty)		per_end = empty;
			break;
		case Tracking_OFF:	
			per_end = empty;						
			break;
		default:							
			break;
	}


	for(i=deadz; i<=empty; i++)
	{
		if(i<=per_end)
		{
			if(lMsCal.thr_min[ch]>lMsCal.aEco_rslt[ch][i])		lMsCal.thr_min[ch] = lMsCal.aEco_rslt[ch][i];
			if(lMsCal.thr_max[ch]<lMsCal.aEco_rslt[ch][i])		lMsCal.thr_max[ch] = lMsCal.aEco_rslt[ch][i];
		}
	}

	range = lMsCal.thr_max[ch]-lMsCal.thr_min[ch];
	if(range<=0)	range = 0;
	
	thr = (lMsCal.thr_min[ch]+(F32)((range*thr_sel)/100));

	if(thr>lMsCal.thr_max[ch])	thr = lMsCal.thr_max[ch];

	lMsCal.thr[ch] = thr;
#endif
}

U08 CalPrc_Flt3Stp(U08 ch,U08 type)
{
	U16 i;
	U16 asf_c = 0;
	U16 c=0;
	U16 asf_v;
	U16 deadz = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);
	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 signal_end = empty*1.1;
	U16 window_time = MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_WINDOW_RESET_TIME);
	U16 window_range =  MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_WINDOW_RANGE);
	U16 tracking_Hi;
	U16 tracking_Lo;
	U08 msr_chk;

	switch(type)
	{
		case MsCAL_THR_LIGHT:	asf_v = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ASF_LIGHT);	break;
		case MsCAL_THR_HEAVY:	asf_v = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_ASF_HEAVY);	break;
	}


	if(asf_v>0) asf_v+=5;

	tracking_Hi = lMsCal.Tracking_dist[ch][type]+window_range;
	tracking_Lo = lMsCal.Tracking_dist[ch][type]-window_range;		
	msr_chk = ApSTT_MSR_WEAK;

	if(ApSCD_GetVl_Prof_Full(ch)==FALSE)	window_time = 0;
	//if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)	window_time = 0;

	for(i=deadz; i<=signal_end; i++)
	{		
		if(lMsCal.thr[ch][type] <= lMsCal.aEco_rslt[ch][i])			//Threshold
		{
			c = CalPrc_GetAsfCnt(ch, i, lMsCal.thr[ch][type]);
			asf_c = (c*13.5);
			if(asf_c >= asf_v)									//ASF
			{
				msr_chk = ApSTT_MSR_TRAC;
				
				if(window_time>0)
				{
					switch(lMsCal.fRefilter[ch][type])				//Tracking
					{
						case Tracking_ON:
							if((i>=tracking_Lo) && (i<=tracking_Hi))
							{
								lMsCal.Refilter_cnt[ch][type]  = 0;
								lMsCal.Tracking_dist[ch][type] = i;
								lMsCal.stp3_dist[ch][type] = TPRT_Calib(ch, i);
								if(lMsCal.stp3_dist[ch][type]<=empty)
									lMsCal.stp3_sldg[ch][type] = empty - lMsCal.stp3_dist[ch][type];
								else
									lMsCal.stp3_sldg[ch][type] = 0;
								msr_chk = ApSTT_MSR_OK;
								return msr_chk;
							}
							break;
						case Tracking_OFF:
							if(i<=empty)	lMsCal.Tracking_dist[ch][type] = i;
							else			lMsCal.Tracking_dist[ch][type] = empty;
							lMsCal.stp3_dist[ch][type]     = TPRT_Calib(ch, i);
							if(lMsCal.stp3_dist[ch][type]<=empty)
								lMsCal.stp3_sldg[ch][type] = empty - lMsCal.stp3_dist[ch][type];
							else
								lMsCal.stp3_sldg[ch][type] = 0;

							lMsCal.fRefilter[ch][type]     	= Tracking_ON;
							msr_chk = ApSTT_MSR_OK;
							return msr_chk;
						default:		break;	
					}
				}
				else if(window_time ==0)
				{

					if(i<=empty)		lMsCal.Tracking_dist[ch][type] = i;
					else				lMsCal.Tracking_dist[ch][type] = empty;					
					lMsCal.stp3_dist[ch][type] = TPRT_Calib(ch, i);
					if(lMsCal.stp3_dist[ch][type]<=empty)
						lMsCal.stp3_sldg[ch][type] = empty - lMsCal.stp3_dist[ch][type];
					else
						lMsCal.stp3_sldg[ch][type] = 0;

					
					msr_chk = ApSTT_MSR_OK;	
					
					return msr_chk;
				}
			}
			i += c;
		}		
	}

	return msr_chk;
}


void CalPrc_3stp_dist(U08 ch)
{
	U16 window_time   = MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_WINDOW_RESET_TIME);
	U08 msr_chk[MsCAL_THR_TYPE_NUM];
	U08 i,j;
	
	CalPrc_Threshold_Value(ch);

	switch(lMsCal.stt[ch])
	{
		case ApSTT_MSR_OK:
		case ApSTT_MSR_WEAK:
		case ApSTT_MSR_TRAC:	break;
		default:				return;
	}


	for(j=0; j<2;	j++)
	{
		msr_chk[j] = CalPrc_Flt3Stp(ch,j);
		
		switch(msr_chk[j])
		{
			case ApSTT_MSR_OK: 		
				lMsCal.stt[ch] =  ApSTT_MSR_OK;
				break;;
			case ApSTT_MSR_WEAK:	
				lMsCal.stt[ch] =  ApSTT_MSR_WEAK;
				//CalPrc_ResetFlag(ch);
				break;
			case ApSTT_MSR_TRAC:
				switch(lMsCal.fRefilter[ch][j])
				{
					case Tracking_ON:	
						for(i=0; i<MsCAL_THR_TYPE_NUM; i++)
						{
							if(++lMsCal.Refilter_cnt[ch][j]>window_time)
							{
								lMsCal.fRefilter[ch][j] = Tracking_OFF;
								lMsCal.Refilter_cnt[ch][j]=0;
								lMsCal.stt[ch] =  ApSTT_MSR_WEAK;
								if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)
									MsCAL_SaveEcho(ch);
								CalPrc_ResetFlag(ch);
							}
							else	
								lMsCal.stt[ch] =  ApSTT_MSR_TRAC;
						}
						break;
					case Tracking_OFF:	
						lMsCal.Refilter_cnt[ch][j]=0;
						lMsCal.stt[ch] =  ApSTT_MSR_WEAK;
						break;
					default:	
						break;
				}
				break;
			default:			
				break;
		}

	}





}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get Result
U16 MsCAL_GetVl_TracDist(U08 iCh,U08 type)					{	return lMsCal.Tracking_dist[iCh][type];		}
U16 MsCAL_GetVl_RsltDist(U08 iCh,U08 type)					{	return lMsCal.rslt_dist[iCh][type];			}
U16 MsCAL_GetVl_RsltSldg(U08 iCh,U08 type)					{	return lMsCal.rslt_sldg[iCh][type];			}
U16 MsCAL_GetVl_Stp3Dist(U08 iCh,U08 type)					{	return lMsCal.stp3_dist[iCh][type];			}
U16 MsCAL_GetVl_Stp3Sldg(U08 iCh,U08 type)					{	return lMsCal.stp3_sldg[iCh][type];			}
U16 MsCAL_GetVl_EchoBuff(U08 iCh, U16 idx)					{	return lMsCal.aEco_rslt[iCh][idx];			}
U16 MsCAL_GetVl_EchoReal(U08 iCh, U16 idx)					{	return lMsCal.aEco_real[iCh][idx];			}
U16 MsCAL_GetVl_SaveBuff(U08 iCh, U16 idx)					{	return lMsCal.save_rslt[iCh][idx];			}
U16 MsCAL_GetVl_SaveReal(U08 iCh, U16 idx)					{	return lMsCal.save_real[iCh][idx];			}
U16 MsCAL_GetVl_FieldBuff(U08 iCh, U16 idx)					{	return lMsCal.aEco_filed_rlst[iCh][idx];	}
U16 MsCAL_GetVl_FieldReal(U08 iCh, U16 idx)					{	return lMsCal.aEco_field_real[iCh][idx];	}
U16 MsCAL_GetVl_DiffDist(void)								{	return lMsCal.diff_dist;				}
U16 MsCAL_GetVl_DiffSldg(void)								{	return lMsCal.diff_sldg;				}
U16 MsCAL_GetVl_AvrgDist(void)								{	return lMsCal.avrg_dist;				}
U16 MsCAL_GetVl_AvrgSldg(void)								{	return lMsCal.avrg_sldg;				}
U16 MsCAL_GetVl_MiniDist(void)								{ 	return lMsCal.mini_dist;				}
U16 MsCAL_GetVl_MiniSldg(void)								{ 	return lMsCal.mini_sldg;				}
U08 MsCAL_GetVl_MiniSens(void)								{	return lMsCal.mini_sens;				}
U32 MsCAL_GetVl_Threshold(U08 iCh,U08 type)					{	return lMsCal.thr[iCh][type];				}
U32 MsCAL_GetVl_Threshold_Max(U08 iCh)						{	return lMsCal.thr_max[iCh];				}
U32 MsCAL_GetVl_Threshold_Min(U08 iCh)						{	return lMsCal.thr_min[iCh];				}

U16 MsCAL_GetVl_ASF_R(U08 iCh)								{	return lMsCal.asf_r[iCh];				}
U16 MsCAL_GetVl_ASF_H(U08 iCh)								{	return lMsCal.asf_h[iCh];				}

U16 MsCAL_GetVl_FieldDist(U08 iCh)							{	return lMsCal.field_dist[iCh];			}
U16 MsCAL_GetVl_FieldSldg(U08 iCh)							{	return lMsCal.field_sldg[iCh];			}


U08 MsCAL_Get_Stt(U08 iCh)									{	return lMsCal.stt[iCh];					}
// Set
void MsCAL_SetVl_ASF_R(U08 iCh,U16 val)						{	lMsCal.asf_r[iCh] = val;				}
void MsCAL_SetVl_ASF_H(U08 iCh,U16 val)						{	lMsCal.asf_h[iCh] = val;				}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Converter Unit
//------------------------------------------------------------------------------------------------------------------------------
F32 MsCAL_Feet2Meter(U16 feet)		{		return (feet  * MsCAL_CNST_FT2MT) + 0.5;		}
F32 MsCAL_Meter2Feet(U16 meter)		{		return (meter * MsCAL_CNST_MT2FT) + 0.5;		}

void MsCAL_SetVl_RsltDist(U08 iCh,U08 type, U16 val)					{	lMsCal.rslt_dist[iCh][type] = val;			}
void MsCAL_SetVl_RsltSldg(U08 iCh,U08 type, U16 val)					{	lMsCal.rslt_sldg[iCh][type] = val;			}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------



void MsCAL_CheckWeak(U08 iCh)
{
	U32 i;
	S16 thr_max = 0;
	U16 thr_min = (MnTST_PrGet_CH_Value(iCh, MnTST_OPT_SINGLE_THR_MIN)*4096)/33;
	U16 deadz = MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_DEADZONE);
	U16 empty = MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_EMPTY);
	
	U16 msr_range= (empty)*1.1;

	if((ScECH_GetLayer() == SCRN_L2_VALU) || (ScCLB_GetLayer() == SCRN_L2_VALU) || (MENU_GetLayer() >= MENU_L3_VALUE)) 
		return;

	switch(OuCUR_GetPCD_fRun())
	{
		case PCD_OFF:	break;
		case PCD_ON:	
		case PCD_TEST:	return;
		default:
			return;	
	}


	for(i=deadz; i<ADC_BUFF_MAX; i++)
	{
		if(i<=msr_range)
		{	
			if(ADC_GetEchoVal(iCh, i)>thr_min)		thr_max = ADC_GetEchoVal(iCh, i);
			if(thr_max<=0)							thr_max = 0;
		}
	}

	
	if(thr_max<thr_min)
	{
		switch(lMsCal.stt[iCh])
		{
			case ApSTT_TPR_NG:		return;
			case ApSTT_MSR_NG:		
				if(++lMsCal.signal_ng_sec[iCh]>MsCAL_SIGNAL_NG_TIME)
				{
					lMsCal.f_signal[iCh] = SIGNAL_NG;	
					lMsCal.signal_ok_sec[iCh] = 0;
					lMsCal.signal_ng_sec[iCh] = 0;
				}
				return;
			case ApSTT_MSR_OK:
			case ApSTT_MSR_TRAC:
			case ApSTT_MSR_IDLE:
			case ApSTT_MSR_WEAK:	lMsCal.stt[iCh] =  ApSTT_MSR_NG;	return;
			default:				return;
		}
	}
	else if (thr_max>=thr_min)
	{
		switch(lMsCal.stt[iCh])
		{
			case ApSTT_MSR_IDLE:	lMsCal.stt[iCh] =  ApSTT_MSR_WEAK;	break;
			case ApSTT_MSR_NG:	
				lMsCal.error_sec[iCh]=0;
				switch(lMsCal.f_signal[iCh])
				{
					case SIGNAL_NG:
						if(++lMsCal.signal_ok_sec[iCh]>MsCAL_SIGNAL_OK_TIME)
						{	
							lMsCal.stt[iCh] =  ApSTT_MSR_WEAK;
							lMsCal.f_signal[i] = SIGNAL_OK;
							lMsCal.signal_ok_sec[iCh] = 0;
						}	
						return;
					case SIGNAL_OK:			
						lMsCal.stt[iCh] =  ApSTT_MSR_WEAK;
						break;
					default:			return;
				}
				break;
			case ApSTT_TPR_NG:		return;
			case ApSTT_MSR_OK:
			case ApSTT_MSR_TRAC:
			case ApSTT_MSR_WEAK:	break;			
			default:				return;
		}
	}

}


void MsCAL_SaveEcho(U08 ch)
{
	U16 i;

	for(i=0; i<ADC_BUFF_MAX; i++)
	{
		lMsCal.save_real[ch][i] = lMsCal.aEco_real[ch][i];
		lMsCal.save_rslt[ch][i] = lMsCal.aEco_rslt[ch][i];
	}
}


void MsCAL_FieldAProf(U08 iCh,U08 idx)
{
	U32 i;
	S32 j;
	U64 sum[ADC_BUFF_MAX] = {0, };
	U16 deadz = MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_DEADZONE);
	U16 empty = MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_EMPTY);

	U16 empty_range = empty*1.1;
	
	if(idx>=5)
		idx=5;

	// Buffer Shift Save
	for(j=idx-1; j>0; j--)
	{
		if(idx<=1)	break;
		for(i=0; i<ADC_BUFF_MAX; i++)
		{
			switch(iCh)
			{
				case MsCAL_CH_S0 : lMsCal.aEco_filed_prof[iCh][j][i] = lMsCal.aEco_filed_prof[iCh][j-1][i]; break;
				case MsCAL_CH_S1 : lMsCal.aEco_filed_prof[iCh][j][i] = lMsCal.aEco_filed_prof[iCh][j-1][i]; break;
			}
		}
		DaMdb_ProcMain();
	}

	DaMdb_ProcMain();

	// Add Data
	for(i=0; i<ADC_BUFF_MAX; i++)
	{
		switch(iCh)
			{
			case MsCAL_CH_S0 : lMsCal.aEco_filed_prof[iCh][0][i] = ADC_GetEchoVal(iCh, i); break;
			case MsCAL_CH_S1 : lMsCal.aEco_filed_prof[iCh][0][i] = ADC_GetEchoVal(iCh, i); break;
		}
	}

	DaMdb_ProcMain();

	// Moving Average
	for(i=0; i<ADC_BUFF_MAX; i++)
	{
		for(j=0; j<idx; j++)
		{
			switch(iCh)
			{
				case MsCAL_CH_S0 : sum[i] += lMsCal.aEco_filed_prof[iCh][j][i]; break;
				case MsCAL_CH_S1 : sum[i] += lMsCal.aEco_filed_prof[iCh][j][i]; break;
			}
		}

		switch(iCh)
		{
			case MsCAL_CH_S0:	lMsCal.aEco_filed_rlst[MsCAL_CH_S0][i] = sum[i]/idx;	break;
			case MsCAL_CH_S1:	lMsCal.aEco_filed_rlst[MsCAL_CH_S1][i] = sum[i]/idx;	break;
		}
	}

	DaMdb_ProcMain();

	if(ApSCD_GetVl_Prof_Full(iCh))
	{
		for(i=deadz+50; i<empty_range; i++)
		{
			if(lMsCal.aEco_filed_rlst[iCh][i]>MsCAL_FIELD_THR)
			{
				lMsCal.field_dist[iCh] = i;
				if(lMsCal.field_dist[iCh]>=empty)
					lMsCal.field_dist[iCh] = empty;
				lMsCal.field_sldg[iCh] = empty-lMsCal.field_dist[iCh];

#if 0
				if((lMsCal.field_sldg[iCh]+offs)<=0)
					lMsCal.field_sldg[iCh] = 0;
				else
					lMsCal.field_sldg[iCh] = lMsCal.field_sldg[iCh]+offs;
#endif

				if((lMsCal.field_sldg[iCh])>=empty)
					lMsCal.field_sldg[iCh] = empty;					
				i=empty;
				break;
			}	
			else
			{
				lMsCal.field_dist[iCh] = empty;
				lMsCal.field_sldg[iCh] = 0;
			}
		}
	}
}


void MsCal_fieldReal(U08 iCh)
{
	U32 i;

	for(i=0; i<ADC_BUFF_MAX; i++)
	{
		lMsCal.aEco_field_real[iCh][i] = ADC_GetEchoVal(iCh, i);
	}


}

void MsCAL_ProcReal(U08 iCh)
{
	U32 i;

	for(i=0; i<ADC_BUFF_MAX; i++)
	{
		lMsCal.aEco_real[iCh][i] = ADC_GetEchoVal(iCh, i);
	}

}


void MsCAL_ProcRealSave380(U32 idx)
{
	U32 i;
	U32 j;

	RTC_TM curr_tm = RTC_GetTime();

	for(j=idx-1; j>0; j--)
	{
		if(idx<=1)	break;
		for(i=0; i<500; i++)
		{
			SDRAM_aEco_prof_S2[((j)*500)+i] = SDRAM_aEco_prof_S2[((j-1)*500)+i];
		}
	}	

	// Add Data
	for(i=0; i<500; i++)
	{
		SDRAM_aEco_prof_S2[i] = ADC_GetEchoVal(APP_CH_1, i);
		SDRAM_aEco_prof_S2[0] = curr_tm.day;
		SDRAM_aEco_prof_S2[1] = curr_tm.hours;
		SDRAM_aEco_prof_S2[2] = curr_tm.minutes;
	}

}




void MsCAL_ProcRealSave160(U32 idx)
{
	U32 i;
	U32 j;

	RTC_TM curr_tm = RTC_GetTime();

	for(j=idx-1; j>0; j--)
	{
		if(idx<=1)	break;
		for(i=0; i<500; i++)
		{
			SDRAM_aEco_prof_S3[((j)*500)+i] = SDRAM_aEco_prof_S3[((j-1)*500)+i];
		}
	}	

	// Add Data
	for(i=0; i<500; i++)
	{
		SDRAM_aEco_prof_S3[i] = ADC_GetEchoVal(APP_CH_1, i);
		SDRAM_aEco_prof_S3[0] = curr_tm.day;
		SDRAM_aEco_prof_S3[1] = curr_tm.hours;
		SDRAM_aEco_prof_S3[2] = curr_tm.minutes;
	}

}





void MsCAL_ProcProf(U08 iCh,U32 idx)
{
	U32 i;
	S32 j;
	U64 sum[ADC_BUFF_MAX] = {0, };
	U16 empyt_range = MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_EMPTY)*1.1;



#if 0
	switch(OuCUR_GetPCD_fRun())
	{
		case PCD_OFF:	break;
		case PCD_ON:	return;
		default:
			return;	
	}
#endif

	

	// Buffer Shift Save
	for(j=idx-1; j>0; j--)
	{
		if(idx<=1)	break;
		for(i=0; i<empyt_range; i++)
		{
			switch(iCh)
			{
				case MsCAL_CH_S0 : SDRAM_aEco_prof_S0[((j)*ADC_BUFF_MAX)+i] = SDRAM_aEco_prof_S0[((j-1)*ADC_BUFF_MAX)+i]; break;
				case MsCAL_CH_S1 : SDRAM_aEco_prof_S1[((j)*ADC_BUFF_MAX)+i] = SDRAM_aEco_prof_S1[((j-1)*ADC_BUFF_MAX)+i]; break;
			}
		}

		DaMdb_ProcMain();
	}
	
	DaMdb_ProcMain();

	// Add Data
	for(i=0; i<empyt_range; i++)
	{
		switch(iCh)
		{
			case MsCAL_CH_S0 : SDRAM_aEco_prof_S0[i] = ADC_GetEchoVal(iCh, i); break;
			case MsCAL_CH_S1 : SDRAM_aEco_prof_S1[i] = ADC_GetEchoVal(iCh, i); break;
		}
	}

	// Moving Average
	for(i=0; i<empyt_range; i++)
	{
		for(j=0; j<idx; j++)
		{
			switch(iCh)
			{
				case MsCAL_CH_S0 : sum[i] += SDRAM_aEco_prof_S0[(j*ADC_BUFF_MAX)+i]; break;
				case MsCAL_CH_S1 : sum[i] += SDRAM_aEco_prof_S1[(j*ADC_BUFF_MAX)+i]; break;
			}
		}
		DaMdb_ProcMain();

		switch(iCh)
		{
			case MsCAL_CH_S0:	lMsCal.aEco_rslt[MsCAL_CH_S0][i] = sum[i]/idx;	break;
			case MsCAL_CH_S1:	lMsCal.aEco_rslt[MsCAL_CH_S1][i] = sum[i]/idx;	break;
		}
	}


	DaMdb_ProcMain();


#if 0
	I08 sDbg[32];
	U08 a;
	_SPRINTF(sDbg, "%d %d %d %d", ADC_GetEchoVal(MsCAL_CH_S0, 100),lMsCal.aEco_real[MsCAL_CH_S0][100],lMsCal.aEco_rslt[MsCAL_CH_S0][100],sum[100]);
	DpFIG_DrwRect(150, 30, 400, 25, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(150, 30, _cECO_LVL_TITL, _cBGD_SCRN, _fE17HsB, sDbg);

#endif
}



void MsCAL_ProcSmooth(U08 ch)
{
	U32 i,j,k;
	U16 num = MnTST_PrGet_CH_Value(ch,MnTST_OPT_SINGLE_SMOOTH_NO);
	U16 size = MnTST_PrGet_CH_Value(ch,MnTST_OPT_SINGLE_SMOOTH_RANGE);
	U64 sum = 0;
	U16 deadz = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_DEADZONE);
	U16 echo_smooth[MsCAL_CH_NUM][ADC_BUFF_MAX];
	U16 empyt_range = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY)*1.1;

	if((ScECH_GetLayer() == SCRN_L2_VALU) || (ScCLB_GetLayer() == SCRN_L2_VALU) || (MENU_GetLayer() >= MENU_L3_VALUE)) 
		return;

	switch(MsCAL_Get_Stt(ch))
	{
		case ApSTT_TPR_NG:	
		case ApSTT_MSR_NG:		return;
		case ApSTT_MSR_OK:
		case ApSTT_MSR_TRAC:
		case ApSTT_MSR_IDLE:
		case ApSTT_MSR_WEAK:	break;
		default:				return;
	}


	if((num==0) || (size ==0))
	{
		return;
	}

	for(k=0; k<num;	k++)
	{
		for(i=deadz; i<empyt_range; i++)
		{
			for(j=0; j<=size; j++)
			{
				if(j==0)
				{
					if(k==0)	echo_smooth[ch][i] = lMsCal.aEco_rslt[ch][i];
					sum = echo_smooth[ch][i]; 
				}
				else
				{
					if(i>=j)						sum+= lMsCal.aEco_rslt[ch][i-j];	
					if(i+j<empyt_range)				sum+= lMsCal.aEco_rslt[ch][i+j];		
				}
			}
			if(i<size)								echo_smooth[ch][i] = sum / (size+i+1);
			else if(i+size>=empyt_range)			echo_smooth[ch][i] = sum / (size+i+1);
			else echo_smooth[ch][i] = (sum / ((size*2)+1));
		}
		DaMdb_ProcMain();
		for(i=deadz; i<empyt_range; i++)
			lMsCal.aEco_rslt[ch][i] = echo_smooth[ch][i];
	}

#if 0
	I08 sDbg[32];
	U08 a;
	_SPRINTF(sDbg, "%d %d %d", lMsCal.dist_prof[MsCAL_CH_S0][150],lMsCal.aEco_rslt[MsCAL_CH_S0][150],val);
	DpFIG_DrwRect(150, 30, 400, 25, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(150, 30, _cECO_LVL_TITL, _cBGD_SCRN, _fE17HsB, sDbg);
#endif
}


void MsCAL_Proc3Stp(U08 iCh)
{
	if((ScECH_GetLayer() == SCRN_L2_VALU) || (ScCLB_GetLayer() == SCRN_L2_VALU) || (MENU_GetLayer() >= MENU_L3_VALUE)) 
		return;

	
	CalPrc_3stp_dist(iCh);

}

void MsCAL_ProcDamp(U08 iCh, U16 idx)
{
	//I08 sDbg[32];
	U16 i,j;
	U64 sum[MsCAL_THR_TYPE_NUM];
	S16 dist[MsCAL_THR_TYPE_NUM];
	U16 empty = MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_EMPTY);
	S16 offs = MnMSR_CalGet_Ch_Value(iCh,MnMS1_OPT_SINGLE_OFFSET);

	if((ScECH_GetLayer() == SCRN_L2_VALU) || (ScCLB_GetLayer() == SCRN_L2_VALU) || (MENU_GetLayer() >= MENU_L3_VALUE)) 
		return;

	// Buffer Shift Save
	for(i=idx-1; i>0; i--)
	{
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
			lMsCal.dist_damp[iCh][j][i] = lMsCal.dist_damp[iCh][j][i-1];
	}
	
	
	// Save Step3 Data
	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lMsCal.dist_damp[iCh][j][0] = lMsCal.stp3_dist[iCh][j];
		sum[j] = 0;
	}
	// Sum Data
	for(i=0; i<idx; i++)
	{
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
			sum[j] += lMsCal.dist_damp[iCh][j][i];
	}
	
	// Offset
	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		switch(MnMSR_BaseGet_Ch_Value(iCh, MnMS0_OPT_SINGLE_OPERATION))
		{
			case MnMS0_OPERATION_DISTANCE:	dist[j] = sum[j]/idx + offs;  	break;
			case MnMS0_OPERATION_SLUDGE:	dist[j] = sum[j]/idx - offs;	if(dist[j]<= 0) dist[j] =0;  break;
			default:						break;
		}
	}


	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lMsCal.rslt_dist[iCh][j] = dist[j];

		// Final Result
		if(lMsCal.rslt_dist[iCh][j] > empty)	
		{
			lMsCal.rslt_dist[iCh][j] = empty;
			lMsCal.rslt_sldg[iCh][j] = 0;
		}
		else								
		{
			lMsCal.rslt_sldg[iCh][j] = empty  - lMsCal.rslt_dist[iCh][j];
		}	

		if(lMsCal.rslt_sldg[iCh][j] > empty)	lMsCal.rslt_sldg[iCh][j] = empty;
	}


#if 0
	if(!MnEGN_PrGet_Item(MnEGN_I03_fDP_DBG))
		return;
#endif
#if 0
	_SPRINTF(sDbg, "%d   %d", lMsCal.rslt_dist[0][0], lMsCal.rslt_dist[0][1]);
	DpFIG_DrwRect(150, 30, 400, 25, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(150, 30, _cECO_LVL_TITL, _cBGD_SCRN, _fE17HsB, sDbg);	
#endif
}


void MsCalPrc_DualParam(void)
{
#if 0
	if(MnFTR_PrGet_SsChn() != MnFTR_SS_DUAL)
		return;

	for(i=0; i<ADC_CH_NUMB; i++)
	{
		if(lMsCal.stp3_dist[i] == MsCAL_NG_LEVEL)
		{
			lMsCal.diff_dist = lMsCal.diff_sldg = MsCAL_NG_LEVEL;
			lMsCal.avrg_dist = lMsCal.avrg_sldg = MsCAL_NG_LEVEL;
			return;
		}
	}

	lMsCal.diff_dist = abs(lMsCal.rslt_dist[ADC_CH_SS0] - lMsCal.rslt_dist[ADC_CH_SS1]);
	lMsCal.diff_sldg = abs(lMsCal.rslt_sldg[ADC_CH_SS0] - lMsCal.rslt_sldg[ADC_CH_SS1]);

	lMsCal.avrg_dist = (lMsCal.rslt_dist[ADC_CH_SS0] + lMsCal.rslt_dist[ADC_CH_SS1]) >> 1;
	lMsCal.avrg_sldg = (lMsCal.rslt_sldg[ADC_CH_SS0] + lMsCal.rslt_sldg[ADC_CH_SS1]) >> 1;

	lMsCal.mini_dist = _MIN(lMsCal.rslt_dist[ADC_CH_SS0], lMsCal.rslt_dist[ADC_CH_SS1]);
	lMsCal.mini_sldg = _MIN(lMsCal.rslt_sldg[ADC_CH_SS0], lMsCal.rslt_sldg[ADC_CH_SS1]);

	lMsCal.mini_sens = _MIN_IDX(lMsCal.rslt_sldg[ADC_CH_SS0], lMsCal.rslt_sldg[ADC_CH_SS1]);
#endif
	
}


#if 0
void MsCAL_ProcCycle(U08 iCh, U16 cnt)
{
	U16 t_dep   = ScHYB_PrGet_Value(iCh, ScHYB_F04_T_DEP);
	U16 s_dep   = ScHYB_PrGet_Value(iCh, ScHYB_F02_S_DEP);
	U16 cpt_cyc = MnMSR_BaseGet_Value(MnMS0_I00_CH0_THR_MOD);
	U08 cpt_typ = MnMSR_BaseGet_Value(MnMS0_I01_CH1_THR_MOD);
	

	lMsCal.dist_cycl[iCh][cnt] = lMsCal.stp3_dist[iCh];
	lMsCal.dist_cycl[iCh][0] +=lMsCal.dist_cycl[iCh][cnt];

	if(cnt==cpt_cyc)
	{	
		switch(cpt_typ)
		{
			case MnMS0_IV1_AVRG:
				// Sum Data
				lMsCal.stp3_dist[iCh] = lMsCal.dist_cycl[iCh][0]/cnt;
				if(lMsCal.stp3_dist[iCh]==t_dep)	lMsCal.stp3_sldg[iCh]=t_dep-lMsCal.stp3_dist[iCh];
				else 								lMsCal.stp3_sldg[iCh] = t_dep - s_dep - lMsCal.stp3_dist[iCh];
				break;
			case MnMS0_IV1_LAST:
				lMsCal.stp3_dist[iCh]=lMsCal.dist_cycl[iCh][cpt_cyc];
				if(lMsCal.stp3_dist[iCh]==t_dep)	lMsCal.stp3_sldg[iCh]=t_dep-lMsCal.stp3_dist[iCh];
				else 								lMsCal.stp3_sldg[iCh] = t_dep - s_dep - lMsCal.stp3_dist[iCh];
				break;
			default:		break;
		}
		_MEMSET(lMsCal.dist_cycl[iCh], 0, sizeof(lMsCal.dist_cycl[iCh]));
	}
}
#endif

void MsCAL_ProcAvgSave(U08 ch)
{
	U32 i;
	U32 j;
	U16 idx;
	U16 idx_max;
	RTC_TM curr_tm = RTC_GetTime();

	U16 empty = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_EMPTY);
	U16 range = empty*1.1;

	lMsCal.csave_avg[ch]++;

	if(range>600)
		idx_max = 1000000/(2*range);
	else 
		idx_max = 800;

	if(lMsCal.csave_avg[ch]>idx_max)
		lMsCal.csave_avg[ch] = idx_max;

	if(ch == APP_CH_1)
	{
		for(j=lMsCal.csave_avg[ch]-1; j>0; j--)
		{
			if(lMsCal.csave_avg[ch]<=1)	break;
			for(i=0; i<range; i++)
			{
				SDRAM_aEco_prof_S2[((j)*range)+i] = SDRAM_aEco_prof_S2[((j-1)*range)+i];
			}
		}	

		// Add Data
		for(i=0; i<range; i++)
		{
			SDRAM_aEco_prof_S2[i] = lMsCal.aEco_rslt[APP_CH_1][i];
		}
		SDRAM_aEco_prof_S2[0] = curr_tm.day;
		SDRAM_aEco_prof_S2[1] = curr_tm.hours;
		SDRAM_aEco_prof_S2[2] = curr_tm.minutes;
		SDRAM_aEco_prof_S2[3] = empty;
		SDRAM_aEco_prof_S2[4] = range;
		SDRAM_aEco_prof_S2[5] = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_LIGHT);
		SDRAM_aEco_prof_S2[6] = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_HEAVY);
		SDRAM_aEco_prof_S2[7] = lMsCal.Tracking_dist[ch][MsCAL_THR_LIGHT];
		SDRAM_aEco_prof_S2[8] = lMsCal.Tracking_dist[ch][MsCAL_THR_HEAVY];
		SDRAM_aEco_prof_S2[9] = lMsCal.rslt_sldg[ch][MsCAL_THR_LIGHT];
		SDRAM_aEco_prof_S2[10] = lMsCal.rslt_sldg[ch][MsCAL_THR_HEAVY];

	}
	else if(ch == APP_CH_2)
	{
		for(j=lMsCal.csave_avg[ch]-1; j>0; j--)
		{
			if(lMsCal.csave_avg[ch]<=1)	break;
			for(i=0; i<range; i++)
			{
				SDRAM_aEco_prof_S3[((j)*range)+i] = SDRAM_aEco_prof_S3[((j-1)*range)+i];
			}
		}	
		
		// Add Data
		for(i=0; i<range; i++)
		{
			SDRAM_aEco_prof_S3[i] = lMsCal.aEco_rslt[APP_CH_2][i];
		}
		SDRAM_aEco_prof_S3[0] = curr_tm.day;
		SDRAM_aEco_prof_S3[1] = curr_tm.hours;
		SDRAM_aEco_prof_S3[2] = curr_tm.minutes;
		SDRAM_aEco_prof_S3[3] = empty;
		SDRAM_aEco_prof_S3[4] = range;
		SDRAM_aEco_prof_S3[5] = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_LIGHT);
		SDRAM_aEco_prof_S3[6] = (U16)MsCAL_GetVl_Threshold(ch, MsCAL_THR_HEAVY);
		SDRAM_aEco_prof_S3[7] = lMsCal.Tracking_dist[ch][MsCAL_THR_LIGHT];
		SDRAM_aEco_prof_S3[8] = lMsCal.Tracking_dist[ch][MsCAL_THR_HEAVY];
		SDRAM_aEco_prof_S3[9] = lMsCal.rslt_sldg[ch][MsCAL_THR_LIGHT];
		SDRAM_aEco_prof_S3[10] = lMsCal.rslt_sldg[ch][MsCAL_THR_HEAVY];
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

