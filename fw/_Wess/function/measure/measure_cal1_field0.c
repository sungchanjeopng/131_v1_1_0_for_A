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
// app
#include "app_sys.h"
#include "app_status.h"
#include "app_schd1sec.h"
// bsp
#include "bsp_timer.h"
// measurement
#include "measure_calc.h"
// display
#include "disp_string.h"
#include "dp_screen_hybrid.h"
// self
#include "measure_cal1_field0.h"
// menu
#include "menu_engineer.h"
#include "menu_measure.h"
#include "menu_test.h"

#include "data_save.h"
#include "data_commu.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
CAL1_LV lCal1;

//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void MsCAL1_InitVari(void)
{
	U08 i = 0;
	
	lCal1.rst.vel = 0;
	lCal1.rst.cyc = 0;
	lCal1.rst.dir = CAL1_DIRE_NONE;
	lCal1.rst.pos = CAL1_POS_CH_NONE;
	lCal1.rst.pos_old = CAL1_POS_CH_NONE;	
	lCal1.jdg.stt = CAL1_DTT_NONE;
	lCal1.jdg.next_w_cnt = 0;
	lCal1.fDp.dtt_cnt = 0;
	lCal1.fDp.cyc = FALSE;
	lCal1.fin_dir = CAL1_FIN_DIRE_NONE;
	lCal1.fin_pos = CAL1_FIN_POS_NONE;	
	for(i=0; i<CAL1_CH_NUM; i++)
	{
		lCal1.fDp.dtt[i] = FALSE;
		lCal1.evt[i] = CAL1_EVT_NONE;
			
		lCal1.tick_1sec[i]	 = 0; 
		lCal1.fDtt[i]		 = _F_F;

		lCal1.dtt_tim[i].start   = 0;
		lCal1.dtt_tim[i].stop    = 0;
		lCal1.dtt_tim[i].elapsed = 0;
		lCal1.dtt_tim[i].start_old = 0;	
		lCal1.dtt_tim[i].stop_old = 0;		
		lCal1.rlst_old[i][MsCAL_THR_HEAVY] = 0;
		lCal1.rlst_old[i][MsCAL_THR_LIGHT] = 0;
		lCal1.rst.detect[i] = CAL1_RST_DET_NONE;
		lCal1.dtt_tim[i].delay_time = 0;
		lCal1.stt[i] = CAL1_DETECT_IDLE;
	}

	lCal1.rst.tim[CAL1_TIME_1ST] = 0;
	lCal1.rst.tim[CAL1_TIME_2ND] = 0;



	for(i=0; i<APP_CH_NUM; i++)
	{
		lCal1.hunting.cnt[i]=0;
		for(U08 j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{	
			_MEMSET(lCal1.hunting.buff[i][j], 0, sizeof(lCal1.hunting.buff[i][j]));
			lCal1.hunting.value[i][j] = 0;
		}
	}

}


void MsCal1Chk_Detect(U08 ch)
{
	U08 i;
	U16 valu[MsCAL_THR_TYPE_NUM];
	U16 profile = MnEGN_PrGet_CH_Item(ch, MnEGN_OPT_SINGLE_PROFILE);
	U16 damp = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_DAMPING);
	U16 intv = MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_MEASURE_CYCLE);
	U32 cnt;

	if(profile>=10)
		cnt = (damp*intv) + (profile*intv);
	else
		cnt = (damp*intv);

	switch(lCal1.evt[ch])
	{
		case CAL1_EVT_NONE:
		case CAL1_EVT_EXIT:
			lCal1.dtt_tim[ch].delay_time = 0;

			if(MsCAL_GetVl_FieldSldg(ch)>=11)
			{
				lCal1.fDtt[ch] = _F_T;
			}
			else 
				lCal1.fDtt[ch] = _F_F;
			break;
		case CAL1_EVT_PASS:
			if(MsCAL_GetVl_FieldSldg(ch)>=11)
			{
				lCal1.fDtt[ch] = _F_T;
			}
			else 
				lCal1.fDtt[ch] = _F_F;


			if(lCal1.fDtt[ch]== _F_F)
				lCal1.dtt_tim[ch].delay_time++;
			else
				lCal1.dtt_tim[ch].delay_time = 0;

			if(lCal1.dtt_tim[ch].delay_time>=cnt)
			{
				lCal1.fDtt[ch] = _F_F;
			}
			else
				lCal1.fDtt[ch] = _F_T;
			break;
		default:
			break;
	}

#if 0
	if(lCal1.fDtt[ch] == _F_F)
		lCal1.rlst_old[ch][MsCAL_THR_HEAVY] = MsCAL_GetVl_RsltSldg(ch,MsCAL_THR_HEAVY);
#endif
}


void MsCal1_ProcDetect_Pass(U08 ch, U08 detect)
{	
	if(detect == _F_T)
	{
		if((lCal1.tick_1sec[ch]-lCal1.dtt_tim[ch].start)>=3)
		{
			//MsCAL_SaveEcho(ch);

			lCal1.rst.detect[ch] = TRUE;

			lCal1.dtt_tim[ch].stop = lCal1.tick_1sec[ch];
			lCal1.dtt_tim[ch].stop_old = lCal1.tick_1sec[ch];



			switch(ch)
			{
				case CAL1_CH_1: lCal1.rst.pos = CAL1_POS_CH_1;	lCal1.fin_pos = CAL1_FIN_POS_CH_1;	break;
				case CAL1_CH_2: lCal1.rst.pos = CAL1_POS_CH_2;	lCal1.fin_pos = CAL1_FIN_POS_CH_2;	break;
				default:										break;
			}

			if(lCal1.rst.pos_old == CAL1_POS_CH_NONE)
			{
				lCal1.rst.dir = CAL1_DIRE_NONE;
			}
			else if(lCal1.rst.pos == CAL1_POS_CH_1)
			{
				if(lCal1.rst.pos_old == CAL1_POS_CH_2)			
				{
					lCal1.rst.dir = CAL1_DIRE_CH_2TO1;
				}
				else if(lCal1.rst.pos_old == CAL1_POS_CH_1) 	
				{
					lCal1.rst.dir = CAL1_DIRE_CH_1TO2;
				}
				else
					lCal1.rst.dir = CAL1_DIRE_NONE;
			}
			else if(lCal1.rst.pos == CAL1_POS_CH_2)
			{
				if(lCal1.rst.pos_old == CAL1_POS_CH_2)			
				{
					lCal1.rst.dir = CAL1_DIRE_CH_2TO1;
				}
				else if(lCal1.rst.pos_old == CAL1_POS_CH_1) 	
				{
					lCal1.rst.dir = CAL1_DIRE_CH_1TO2;	
				}
				else
					lCal1.rst.dir = CAL1_DIRE_NONE;
			}
		}
	}	
	else
	{
		if(lCal1.rst.detect)
		{
			if((lCal1.tick_1sec[ch]-lCal1.dtt_tim[ch].stop)<3)
			{
				return;
			}
			else
			{
				lCal1.fDp.dtt[ch] = FALSE;
				lCal1.rst.detect[ch] = FALSE;
				lCal1.tick_1sec[ch] = 0;

				switch(lCal1.jdg.stt)
				{
					case CAL1_DTT_NONE: 		
						lCal1.jdg.stt = CAL1_DTT_1ST;	
						lCal1.rst.tim[CAL1_DTT_1ST] = lCal1.rst.cyc;
						break;
					case CAL1_DTT_1ST:			
						if((lCal1.rst.pos==CAL1_POS_CH_1) && (lCal1.rst.pos_old==CAL1_POS_CH_2))
							lCal1.jdg.stt = CAL1_DTT_2ND;
						else if((lCal1.rst.pos==CAL1_POS_CH_2) && (lCal1.rst.pos_old==CAL1_POS_CH_1))
							lCal1.jdg.stt = CAL1_DTT_2ND;		

						if(lCal1.jdg.stt==CAL1_DTT_1ST)
							lCal1.rst.tim[CAL1_DTT_1ST] = lCal1.rst.cyc;
						if(lCal1.jdg.stt==CAL1_DTT_2ND)
							lCal1.rst.tim[CAL1_DTT_2ND] = lCal1.rst.cyc;
						break;
					case CAL1_DTT_2ND:			break;
					default:					break;
				}


				if(lCal1.rst.pos == CAL1_POS_CH_1)
				{
					if(lCal1.rst.pos_old == CAL1_POS_CH_1)
						lCal1.rst.dir = CAL1_DIRE_CH_1TO2;
					else if(lCal1.rst.pos_old == CAL1_POS_CH_2)
						lCal1.rst.dir = CAL1_DIRE_NONE;
				}
				else if(lCal1.rst.pos == CAL1_POS_CH_2)
				{
					if(lCal1.rst.pos_old == CAL1_POS_CH_2)
						lCal1.rst.dir = CAL1_DIRE_CH_2TO1;
					else if(lCal1.rst.pos_old == CAL1_POS_CH_1)
						lCal1.rst.dir = CAL1_DIRE_NONE;
				}

				
				lCal1.rst.pos_old = lCal1.rst.pos;							
			}		
		}
		else
		{
			lCal1.dtt_tim[ch].start = lCal1.dtt_tim[ch].start_old;
		}

		lCal1.evt[ch] = CAL1_EVT_EXIT;
	}

}


void MsCAL1_Procvelocity(U64 tim)
{
	U16 dist       = MnTST_PrGet_Value(MnTST_OPT_SENSOR_DISTANCE);
	U08 vel_unit   = MnMS1_IV7_m_min; 
	U16 unit_tim;
	U16 unit_meter;
	
	switch(vel_unit)
	{
		case MnMS1_IV7_m_sec: 	unit_meter=1;	  	unit_tim = 1.00; 		break;
		case MnMS1_IV7_m_min: 	unit_meter=1;   	unit_tim = 60.00;		break;
		case MnMS1_IV7_m_hour:	unit_meter=1;   	unit_tim = 3600.00;		break;
		case MnMS1_IV7_km_hour:	unit_meter=1000;	unit_tim = 3600.00;		break;
		default:															break;
	}
	
	lCal1.rst.vel = (dist*unit_tim)/(tim*unit_meter);	
	if(lCal1.rst.vel>= 0xffff)	lCal1.rst.vel = 0xffff;
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MsCAL1_Getrst_pos(void)  	    { return lCal1.rst.pos; }
U08 MsCAL1_Getrst_dir(void)	        { return lCal1.rst.dir;	}
U16 MsCAL1_Getrst_vel(void)	        { return lCal1.rst.vel;	}
U08 MsCAL1_Getrst_evt(U08 ch) { return lCal1.evt[ch];	}
U08 MsCAL1_Getjdg_stt(void)	        { return lCal1.jdg.stt;	}
U08 MsCAL1_GetfDp_dtt(U08 ch)		{ return lCal1.fDp.dtt[ch]; }
U08 MsCAL1_Get_fdtt(U08 ch)			{ return lCal1.fDtt[ch]; }

U08 MsCal1_Getrst_dtt(U08 ch)		{return lCal1.rst.detect[ch];	}
U08 MsCAL1_GetfDp_cyc(void)    	    { return lCal1.fDp.cyc;	}
U16 MsCAL1_Getrst_Value_old(U08 ch, U08 type)	{ return lCal1.rlst_old[ch][type];	}
U64 MsCAL1_Getrst_cyc(void)	{return lCal1.rst.cyc;	}
U08 MsCAL1_Getfin_pos(void)  	    { return lCal1.fin_pos; }
U08 MsCAL1_Getfin_dir(void)	        { return lCal1.fin_dir;	}

U16 MsCAL1_Hunting_value(U08 ch,U08 type)		{ return lCal1.hunting.value[ch][type];	}

// set
void MsCAL1_Setrst_cyc(U64 cyc)			{lCal1.rst.cyc =cyc;	}
//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void MsCal1_ProcDetect(U08 ch)
{

	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)	return;

	switch(MsCAL_Get_Stt(ch))
	{
		case ApSTT_MSR_WEAK:
		case ApSTT_MSR_OK:
		case ApSTT_MSR_TRAC:
			break;
		case ApSTT_MSR_IDLE:
		case ApSTT_MSR_NG:
		case ApSTT_MSR_STOP:
			return;
		default:			
			return;
	}

	lCal1.tick_1sec[ch]++;

	if(lCal1.tick_1sec[ch] > 0xfffffff0)
		lCal1.tick_1sec[ch] = 0;

	MsCal1Chk_Detect(ch);

	switch(lCal1.evt[ch])
	{
		case CAL1_EVT_NONE:
			if(lCal1.fDtt[ch] == _F_T)
			{
				lCal1.evt [ch] = CAL1_EVT_PASS;	
				lCal1.dtt_tim[ch].start = lCal1.tick_1sec[ch];  //gTmr.c.c01sec;	
			}
			break;
		case CAL1_EVT_PASS:
			MsCal1_ProcDetect_Pass(ch,lCal1.fDtt[ch]);
			break;
		case CAL1_EVT_EXIT:
			lCal1.evt[ch] = CAL1_EVT_NONE;
			break;
	}
}

void MsCal1_ProcJudge(void)
{
	U64 time;

	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)	return;

	if(lCal1.rst.cyc>0xFFFFFFF0)
		lCal1.rst.cyc=0;

	switch(lCal1.jdg.stt)
	{
		case CAL1_DTT_NONE:
			break;
		case CAL1_DTT_1ST:			
			break;
		case CAL1_DTT_2ND:				
			time = _ABS(lCal1.rst.tim[CAL1_DTT_2ND] - lCal1.rst.tim[CAL1_DTT_1ST]);
			MsCAL1_Procvelocity(time);
			lCal1.rst.cyc = 0;
			lCal1.jdg.stt = CAL1_DTT_NONE;
			lCal1.fDp.cyc = TRUE;
			break;
		default:
			break;
	}
}


void MsCal1_CalcResult(void)
{

}


void MsCal1_Hunting_Value(U08 ch)
{
	U16 i,j;
	U16 max = 0;
	U16 min = 0xffff;
	U16 max2 = 0;
	U16 min2 = 0xffff;	
	U16 range = MnTST_PrGet_Value(MnTST_OPT_FILTER_RANGE);
	
	if(ApSCD_GetVl_Prof_Full(ch)==FALSE)
	{
		lCal1.hunting.value[ch][MsCAL_THR_LIGHT] = MsCAL_GetVl_RsltSldg(ch,MsCAL_THR_LIGHT);
		lCal1.hunting.value[ch][MsCAL_THR_HEAVY] = MsCAL_GetVl_RsltSldg(ch,MsCAL_THR_HEAVY);	
		return;
	}

	for(i=0; i<lCal1.hunting.cnt[ch]; i++)
	{
#if 0

		deviation[i] = abs(lSav.trend_buff[ch][MsCAL_THR_HEAVY][i] - lSav.trend_mean[ch][MsCAL_THR_HEAVY]);
		deviation_squre[i] = deviation[i]*deviation[i];

		deviation_squre_sum += deviation_squre[i];
		
		if(max<lSav.trend_buff[ch][MsCAL_THR_HEAVY][i])
			max = lSav.trend_buff[ch][MsCAL_THR_HEAVY][i];
		if(min>lSav.trend_buff[ch][MsCAL_THR_HEAVY][i])
			min = lSav.trend_buff[ch][MsCAL_THR_HEAVY][i];

#endif

		if(max<lCal1.hunting.buff[ch][MsCAL_THR_HEAVY][i])
			max = lCal1.hunting.buff[ch][MsCAL_THR_HEAVY][i];
		if(min>lCal1.hunting.buff[ch][MsCAL_THR_HEAVY][i])
			min = lCal1.hunting.buff[ch][MsCAL_THR_HEAVY][i];

		if(max2<lCal1.hunting.buff[ch][MsCAL_THR_LIGHT][i])
			max2 = lCal1.hunting.buff[ch][MsCAL_THR_LIGHT][i];
		if(min2>lCal1.hunting.buff[ch][MsCAL_THR_LIGHT][i])
			min2 = lCal1.hunting.buff[ch][MsCAL_THR_LIGHT][i];
		DaMdb_ProcMain();
	}	

	if(MsCAL1_Get_fdtt(ch) == _F_F)
	{
		if(max>=min)
		{
			if((abs(max-min))<range)
				lCal1.hunting.value[ch][MsCAL_THR_HEAVY] = MsCAL_GetVl_RsltSldg(ch,MsCAL_THR_HEAVY);			
		}

		if(max2>=min2)
		{
			if((abs(max2-min2))<range)
				lCal1.hunting.value[ch][MsCAL_THR_LIGHT] = MsCAL_GetVl_RsltSldg(ch,MsCAL_THR_LIGHT); 		
		}

	}

#if 0
	st = lSav.trend_deviat_value[ch];
	st2 = lSav.trend_st_deviation[ch];

	if(ch==APP_CH_1)
		k = 30;
	else 
		k  =60;
	

	I08 sDbg[32];
	_SPRINTF(sDbg, "%ld,%ld %d %d %d %d %d %ld", deviation_squre_sum,st,st2,lSav.trend_mean[ch][MsCAL_THR_HEAVY],MsCAL_GetVl_RsltSldg(ch,MsCAL_THR_HEAVY),lSav.trend_cnt[ch],deviation[lSav.trend_cnt[ch]-1],deviation_squre[lSav.trend_cnt[ch]-1]);
	DpFIG_DrwRect(150, k, 400, 25, _cBGD_SCRN, DpFIG_FILL);
	DpSTR_GuiLeft(150, k, _cECO_LVL_TITL, _cBGD_SCRN, _fE17HsB, sDbg);
#endif
}


void MsCal1_Hunting_Damping(U08 ch)
{
	U16 i,j;
	S16 val[MsCAL_THR_TYPE_NUM];
	U16 empty;
	U16 time = MnTST_PrGet_Value(MnTST_OPT_FILTER_TIME);
	
	if(ApSCD_GetVl_Prof_Full(ch)==FALSE)
		return;

	empty = MnMSR_BaseGet_Ch_Value(ch,MnMS0_OPT_SINGLE_EMPTY);

	if(MsCAL1_Get_fdtt(ch)==_F_T)
		lCal1.hunting.cnt[ch] = 0;

	lCal1.hunting.cnt[ch]++;

	if(lCal1.hunting.cnt[ch]>time)
		lCal1.hunting.cnt[ch]=time;


	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		if(MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_SLUDGE)
			val[j] = MsCAL_GetVl_Stp3Sldg(ch,j);
		else if (MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_DISTANCE)
			val[j] = MsCAL_GetVl_Stp3Dist(ch,j);
	}

	// Buffer Shift Save
	for(i=lCal1.hunting.cnt[ch]-1; i>0; i--)
	{
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			lCal1.hunting.buff[ch][j][i] = lCal1.hunting.buff[ch][j][i-1];
		}
		DaMdb_ProcMain();
	}
	



	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lCal1.hunting.buff[ch][j][0] = val[j];
	}

}


void MsCal1_Hunting_Proc(void)
{
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		MsCal1_Hunting_Damping(APP_CH_1);
		MsCal1_Hunting_Damping(APP_CH_2);

		MsCal1_Hunting_Value(APP_CH_1);
		MsCal1_Hunting_Value(APP_CH_2);
	}
}



//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

