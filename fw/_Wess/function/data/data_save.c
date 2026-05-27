//------------------------------------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use, copying, transfer or disclosure of
//  such information is prohibited except by express written agreement with WESS-Global Co.,LTD
//
//  $ Date: 2022-05-26 12:00:00 +0900 $
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------------------------------------------------------------
// std
#include <stdio.h>
#include <string.h>
#include <math.h>

// bsp
#include "bsp_ram.h"
#include "bsp_uart.h"
#include "bsp_timer.h"
#include "bsp_usb.h"
// app
#include "app_main.h"
#include "app_status.h"
#include "app_schd1sec.h"
// self
#include "data_save.h"
// menu
#include "menu_measure.h"
#include "menu_system.h"
#include "menu_data.h"
#include "menu_factory.h"
#include "menu_lyr4_addition.h"
#include "menu_engineer.h"
#include "dp_menu_data.h"
// screen
#include "screen_hybrid.h"
// display
#include "disp_titlebar.h"
#include "disp_main.h"
#include "disp_color.h"
#include "disp_figure.h"
// input
#include "input_main.h"
#include "input_key.h"
// measure
#include "measure_cal1_field0.h"
#include "measure_temperature.h"
#include "measure_calc.h"

#include "disp_string.h"
#include "fonts.h"
#include "menu_lyr3_value.h"
#include "data_commu.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
SAV_LS lSav;




//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U32 DaSav_GetCnt(void)		{	return lSav.save_cnt;		}
U08 DaSav_GetDumfEn(void)		{	return lSav.dump_f_en;		}
U32 DaSav_GetDumpAddr(void)	{	return lSav.dump_addr;			}
U32 DaSav_GetSaveSize(void)	{	return lSav.save_size;			}


// Set
void DaSav_SetDumfEn(U08 fen)		{	lSav.dump_f_en = fen;		}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------


void DaSAV_FtrReset(void)
{
	lSav.save_f_ov = FALSE;
	
	MRM_WrByte(_mTrHDR_SAV_OVF, FALSE);
	MRM_WrLong(_mTrHDR_SAV_ADDR3, lSav.save_addr);
}

void DaSav_dumpSetinit(void)
{
	if(lSav.save_f_ov)
	{
		if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)
			lSav.save_size = lSav.save_cnt*SAV_PKT_MAX;
		else if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
			lSav.save_size = lSav.save_cnt*SAV_PKT_FLD_MAX;
		
		if(lSav.save_addr>=lSav.save_size)	lSav.dump_addr = 0; 
		else	lSav.dump_addr = lSav.save_addr;	
	}
	else	
	{
		lSav.save_size = lSav.save_addr;
		lSav.dump_addr = 0;
	}
	lSav.dump_cnt = 0;
}

void DaSAV_DumpInit(void)
{
	lSav.dump_f_en = TRUE;
	lSav.save_loading = FALSE;

	DaSav_dumpSetinit();
#if 0
	if(lSav.save_f_ov)
	{
		switch(MnMSR_FieldAGet_Value(MnMS1_I00_FIELDA_RUN))
		{	
			case MnMS1_IV0_OFF:	
				lSav.save_size = lSav.save_cnt*SAV_PKT_MAX;
				if(lSav.save_addr>=lSav.save_size)	lSav.dump_addr = 0;	
				else	lSav.dump_addr = lSav.save_addr;			
				break;
			case MnMS1_IV0_ON:	
				lSav.save_size = lSav.save_cnt*SAV_PKT_FLD_MAX;
				if(lSav.save_addr>=lSav.save_size)	lSav.dump_addr = 0;	
				else	lSav.dump_addr = lSav.save_addr;			
				break;				
			default:																	
				break;
		}
	}
	else	lSav.dump_addr = 0;
#endif
}

U08 DaSAV_DumpProgress_Save_380(U08 *rtn_pct)
{
	U08 key = INPU_GetKeyIdx(); 
	U08 buff[10000] = {0, };
	U64 buff_cnt = 0;
	U16 i;
	U08 rtn = RTN_BUSY;
	U16 i_max;
	U16 empty = MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_EMPTY);
	U16 range = empty*1.1;


	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
		i_max = 500;
	else
		i_max = range;

	URT_InitMain(URT_IDX_1,115200);

	if(key == KEY_IDX_MENU)
	{
		lSav.dump_size = 0;
		lSav.dump_f_en = FALSE;
		DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_F);
		lSav.save_loading = FALSE;	
		MnLY4_GotoLyr2();
		return SAV_DOWN_OK;		
	}
	else
		INPU_ClrKeyEvt(KEY_EVT_NONE);


	buff[buff_cnt++] = 0x0D;	// CR
	buff[buff_cnt++] = 0x0A;	// LF

	

	buff[buff_cnt++] = (lSav.dump_cnt / 1000) % 10 + '0';
	buff[buff_cnt++] = (lSav.dump_cnt/  100) % 10 + '0';
	buff[buff_cnt++] = (lSav.dump_cnt /   10) % 10 + '0';
	buff[buff_cnt++] =	lSav.dump_cnt		   % 10 + '0';

	buff[buff_cnt++] = 0x0D;	// CR
	buff[buff_cnt++] = 0x0A;	// LF

	for(i=0; i<i_max; i++)
	{	
#if 0
		if(i%38==0)
		{
			buff[buff_cnt++] = 0x0D;	// CR
			buff[buff_cnt++] = 0x0A;	// LF	
		}
#endif
		buff[buff_cnt++] = (SDRAM_aEco_prof_S2[((lSav.dump_cnt)*i_max)+i]/ 1000) % 10 + '0';
		buff[buff_cnt++] = (SDRAM_aEco_prof_S2[((lSav.dump_cnt)*i_max)+i]/ 100) % 10 + '0';
		buff[buff_cnt++] = (SDRAM_aEco_prof_S2[((lSav.dump_cnt)*i_max)+i]/ 10) % 10 + '0';
		buff[buff_cnt++] = SDRAM_aEco_prof_S2[((lSav.dump_cnt)*i_max)+i] % 10 + '0';
		buff[buff_cnt++] = 0x2f;	// CR

		if(i%20==0)
		{
			URT_TxPkt(URT_IDX_1, buff, buff_cnt);
			buff_cnt = 0;
		}
	}

	lSav.dump_cnt++;


	if(lSav.dump_cnt == 799)
	{
		lSav.dump_size = 0;
		lSav.dump_f_en = FALSE;
		DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_F);
		lSav.save_loading = FALSE;	
		MnLY4_GotoLyr2();
		return SAV_DOWN_OK; 	
	}

	*rtn_pct = (lSav.dump_cnt/799)*100;

	return rtn;
}


U08 DaSAV_DumpProgress_Save_160(U08 *rtn_pct)
{
	U08 key = INPU_GetKeyIdx(); 
	U08 buff[10000] = {0, };
	U64 buff_cnt = 0;
	U16 i;
	U08 rtn = RTN_BUSY;
	U16 empty = MnMSR_BaseGet_Ch_Value(APP_CH_2, MnMS0_OPT_SINGLE_EMPTY);
	U16 range = empty*1.1;
	U16 i_max;


	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
		i_max = 500;
	else
		i_max = range;

	URT_InitMain(URT_IDX_1,115200);

	if(key == KEY_IDX_MENU)
	{
		lSav.dump_size = 0;
		lSav.dump_f_en = FALSE;
		DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_F);
		lSav.save_loading = FALSE;	
		MnLY4_GotoLyr2();
		return SAV_DOWN_OK;		
	}
	else
		INPU_ClrKeyEvt(KEY_EVT_NONE);


	buff[buff_cnt++] = 0x0D;	// CR
	buff[buff_cnt++] = 0x0A;	// LF

	

	buff[buff_cnt++] = (lSav.dump_cnt / 1000) % 10 + '0';
	buff[buff_cnt++] = (lSav.dump_cnt/  100) % 10 + '0';
	buff[buff_cnt++] = (lSav.dump_cnt /   10) % 10 + '0';
	buff[buff_cnt++] =	lSav.dump_cnt		   % 10 + '0';

	buff[buff_cnt++] = 0x0D;	// CR
	buff[buff_cnt++] = 0x0A;	// LF

	for(i=0; i<i_max; i++)
	{	
#if 0
		if(i%38==0)
		{
			buff[buff_cnt++] = 0x0D;	// CR
			buff[buff_cnt++] = 0x0A;	// LF	
		}
#endif
		buff[buff_cnt++] = (SDRAM_aEco_prof_S3[((lSav.dump_cnt)*i_max)+i]/ 1000) % 10 + '0';
		buff[buff_cnt++] = (SDRAM_aEco_prof_S3[((lSav.dump_cnt)*i_max)+i]/ 100) % 10 + '0';
		buff[buff_cnt++] = (SDRAM_aEco_prof_S3[((lSav.dump_cnt)*i_max)+i]/ 10) % 10 + '0';
		buff[buff_cnt++] = SDRAM_aEco_prof_S3[((lSav.dump_cnt)*i_max)+i] % 10 + '0';
		buff[buff_cnt++] = 0x2f;	// CR

		if(i%20==0)
		{
			URT_TxPkt(URT_IDX_1, buff, buff_cnt);
			buff_cnt = 0;
		}
	}

	lSav.dump_cnt++;


	if(lSav.dump_cnt == 799)
	{
		lSav.dump_size = 0;
		lSav.dump_f_en = FALSE;
		DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_F);
		lSav.save_loading = FALSE;	
		MnLY4_GotoLyr2();
		return SAV_DOWN_OK; 	
	}

	*rtn_pct = (lSav.dump_cnt/799)*100;

	return rtn;
}



U08 DaSAV_DumpProgress(U08 *rtn_pct)
{
	#if 0
	U08 stt_msr = 0xFF;
	U08 stt_err = 0xFF;
	U16 stt_flg = 0xFFFF;
	U32 stt_int = 0xFFFFFFFF;
	#endif
	U08 rtn = RTN_BUSY;

	U08 rd_fld_buf[SAV_PKT_FLD_MAX] = {0, };
	U08 rd_buf[SAV_PKT_MAX] = {0, };
	U16 sav_val[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 sav_field_raw[APP_CH_NUM];
	S16 sav_tpr[APP_CH_NUM];
	U08 buff[64] = {0, };
	U16 buff_cnt = 0;
	U16 field_vel;
	U64 save_cnt;
	S32 assign = MnLY3_GetValue();
	U08 unit;
	
	switch(assign)
	{
		case MnDS0_DOWN_CH1_HEAVY:
		case MnDS0_DOWN_CH1_LIGHT:	
			unit= MnMSR_BaseGet_Ch_Value(APP_CH_1, MnMS0_OPT_SINGLE_UNIT);
			break;
		case MnDS0_DOWN_CH2_HEAVY:
		case MnDS0_DOWN_CH2_LIGHT:	
			unit = MnMSR_BaseGet_Ch_Value(APP_CH_2, MnMS0_OPT_SINGLE_UNIT);
			break;
		default:	
			break;
	}


	U08 key = INPU_GetKeyIdx(); 


	if(lSav.dump_size >= lSav.save_size)
	{
		lSav.dump_size = 0;
		lSav.dump_f_en = FALSE;
		DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_F);
		lSav.save_loading = FALSE;
		buff[0]=0x5d;
		URT_TxPkt(URT_IDX_1, buff, 1);
		MnLY4_GotoLyr2();
		return SAV_DOWN_OK;
	}

	if(key == KEY_IDX_MENU)
	{
		lSav.dump_size = 0;
		lSav.dump_f_en = FALSE;
		DpTTB_SetIconTgl(DpTTB_I2_SAV,_F_F);
		lSav.save_loading = FALSE;	
		MnLY4_GotoLyr2();
		return SAV_DOWN_OK;		
	}
	else
		INPU_ClrKeyEvt(KEY_EVT_NONE);

	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)
	{
		if(lSav.dump_addr+SAV_PKT_MAX>lSav.save_size)
		{
			lSav.dump_addr = 0;
		}
		
		MRM_RdBulk(_mTrBOD_START+lSav.dump_addr, rd_buf, SAV_PKT_MAX);
		if(!lSav.save_loading)
		{
			buff[buff_cnt++] = 0x5b; // '['
			buff[buff_cnt++] = 0x44; // 'D'
			
			save_cnt = lSav.save_cnt*18;
			
			buff[buff_cnt++] =	(save_cnt		& 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >>  4) & 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >>  8) & 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >> 12) & 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >> 16) & 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >> 20) & 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >> 24) & 0x0f)+ 0x30;
			buff[buff_cnt++] = ((save_cnt >> 28) & 0x0f)+ 0x30;
			
			buff[buff_cnt++] = (unit		   & 0x0f )+ 0x30;
			buff[buff_cnt++] = ((unit >>  4) & 0x0f )+ 0x30;
		}
		lSav.save_loading = TRUE;
		
		buff[buff_cnt++] = (rd_buf[SAV_PKT_TM_YEAR] 			& 0x0f)+ 0x30;
		buff[buff_cnt++] = ((rd_buf[SAV_PKT_TM_YEAR]	>>	4)	& 0x0f)+ 0x30;
		buff[buff_cnt++] = (rd_buf[SAV_PKT_TM_MONTH]				& 0x0f)+ 0x30;
		buff[buff_cnt++] = ((rd_buf[SAV_PKT_TM_MONTH]	>>	4)	& 0x0f)+ 0x30;
		buff[buff_cnt++] = (rd_buf[SAV_PKT_TM_DAY]				& 0x0f)+ 0x30;
		buff[buff_cnt++] = ((rd_buf[SAV_PKT_TM_DAY] 		>>	4)	& 0x0f)+ 0x30;
		buff[buff_cnt++] = (rd_buf[SAV_PKT_TM_HOUR] 			& 0x0f)+ 0x30;
		buff[buff_cnt++] = ((rd_buf[SAV_PKT_TM_HOUR]		>>	4)	& 0x0f)+ 0x30;
		buff[buff_cnt++] = (rd_buf[SAV_PKT_TM_MIN]				& 0x0f)+ 0x30;
		buff[buff_cnt++] = ((rd_buf[SAV_PKT_TM_MIN] 		>>	4)	& 0x0f)+ 0x30;
		
		switch(assign)
		{
			case MnDS0_DOWN_CH1_LIGHT:
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH1_LIGHT_L]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH1_LIGHT_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH1_LIGHT_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH1_LIGHT_H]	>>	4)	& 0x0f)+ 0x30;	
				
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH1_L]	& 0x0f )+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH1_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH1_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH1_H]	>>	4)	& 0x0f)+ 0x30;					
				break;
			case MnDS0_DOWN_CH1_HEAVY:
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH1_HEAVY_L]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH1_HEAVY_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH1_HEAVY_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH1_HEAVY_H]	>>	4)	& 0x0f)+ 0x30;	
				
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH1_L]	& 0x0f )+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH1_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH1_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH1_H]	>>	4)	& 0x0f)+ 0x30;					
				break;					
			case MnDS0_DOWN_CH2_LIGHT:
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH2_LIGHT_L]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH2_LIGHT_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH2_LIGHT_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH2_LIGHT_H]	>>	4)	& 0x0f)+ 0x30;	
				
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH2_L]	& 0x0f )+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH2_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH2_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH2_H]	>>	4)	& 0x0f)+ 0x30;					
				break;

			case MnDS0_DOWN_CH2_HEAVY:
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH2_HEAVY_L]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH2_HEAVY_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_VAL_CH2_HEAVY_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_VAL_CH2_HEAVY_H]	>>	4)	& 0x0f)+ 0x30;	
				
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH2_L]	& 0x0f )+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH2_L]	>>	4)	& 0x0f)+ 0x30;
				buff[buff_cnt++] = (rd_buf[SAV_PKT_TPR_CH2_H]	& 0x0f)+ 0x30;
				buff[buff_cnt++] = ((rd_buf[SAV_PKT_TPR_CH2_H]	>>	4)	& 0x0f)+ 0x30;					
				break;				
			default:
				break;
		}


		URT_InitMain(URT_IDX_1,115200);

		URT_TxPkt(URT_IDX_1, buff, buff_cnt);
		
		lSav.dump_addr += SAV_PKT_MAX;
		lSav.dump_size += SAV_PKT_MAX;
	}
	else if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		lSav.dump_cnt++;
		
		if(lSav.dump_addr+SAV_PKT_FLD_MAX>lSav.save_size)
		{
			lSav.dump_addr = 0;
		}
		
		MRM_RdBulk(_mTrBOD_START+lSav.dump_addr, rd_fld_buf, SAV_PKT_FLD_MAX);
		
		buff[buff_cnt++] = 0x0D;	// CR
		buff[buff_cnt++] = 0x0A;	// LF
		
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_TM_YEAR] / 10) % 10 + '0';
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_TM_YEAR]		  % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_TM_MONTH] / 10) % 10 + '0';
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_TM_MONTH] 	   % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_TM_DAY] / 10) % 10 + '0';
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_TM_DAY]		 % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_TM_HOUR] / 10) % 10 + '0';
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_TM_HOUR]		  % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_TM_MIN] / 10) % 10 + '0';
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_TM_MIN]		 % 10 + '0';
		
		buff[buff_cnt++] = 0x2C;   // ,

		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_CH1_EVT] /  100) % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_CH1_EVT] /   10) % 10 + '0';
		buff[buff_cnt++] =	rd_fld_buf[SAV_PKT_FLD_CH1_EVT]		   % 10 + '0';


		buff[buff_cnt++] = 0x2C;   // ,
		
		sav_val[APP_CH_1][MsCAL_THR_LIGHT] = (rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_LIGHT_L];
		
		buff[buff_cnt++] = (sav_val[APP_CH_1][MsCAL_THR_LIGHT] / 1000) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_1][MsCAL_THR_LIGHT] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_1][MsCAL_THR_LIGHT] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_val[APP_CH_1][MsCAL_THR_LIGHT]		   % 10 + '0';
		
		buff[buff_cnt++] = 0x2C;   // ,
		
		sav_val[APP_CH_1][MsCAL_THR_HEAVY] = (rd_fld_buf[SAV_PKT_FLD_CH1_HEAVY_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_HEAVY_L];
		
		buff[buff_cnt++] = (sav_val[APP_CH_1][MsCAL_THR_HEAVY] / 1000) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_1][MsCAL_THR_HEAVY] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_1][MsCAL_THR_HEAVY] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_val[APP_CH_1][MsCAL_THR_HEAVY]		   % 10 + '0';
		
		buff[buff_cnt++] = 0x2C;   //
		
		sav_field_raw[APP_CH_1] = (rd_fld_buf[SAV_PKT_FLD_CH1_RAW_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH1_RAW_L];

		buff[buff_cnt++] = (sav_field_raw[APP_CH_1] / 1000) % 10 + '0';
		buff[buff_cnt++] = (sav_field_raw[APP_CH_1] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_field_raw[APP_CH_1] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_field_raw[APP_CH_1]		   % 10 + '0';
		
		buff[buff_cnt++] = 0x2C;   // ,		
		sav_tpr[APP_CH_1] = (rd_fld_buf[SAV_PKT_FLD_TPR_CH1_H]<<8) + rd_fld_buf[SAV_PKT_FLD_TPR_CH1_L];
		
		if(sav_tpr[APP_CH_1]>=0)
			buff[buff_cnt++] = 0x2B;   // ,
		else
			buff[buff_cnt++] = 0x2D;   // ,
			
		sav_tpr[APP_CH_1]=abs(sav_tpr[APP_CH_1]);
		
		buff[buff_cnt++] = (sav_tpr[APP_CH_1] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_tpr[APP_CH_1] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_tpr[APP_CH_1]		  % 10 + '0';

		buff[buff_cnt++] = 0x2C;   // ,

		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_CH2_EVT] /  100) % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_CH2_EVT] /   10) % 10 + '0';
		buff[buff_cnt++] =	rd_fld_buf[SAV_PKT_FLD_CH2_EVT]		   % 10 + '0';


		buff[buff_cnt++] = 0x2C;   // ,
		
		sav_val[APP_CH_2][MsCAL_THR_LIGHT] = (rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_LIGHT_L];
		
		buff[buff_cnt++] = (sav_val[APP_CH_2][MsCAL_THR_LIGHT] / 1000) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_2][MsCAL_THR_LIGHT] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_2][MsCAL_THR_LIGHT] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_val[APP_CH_2][MsCAL_THR_LIGHT]		   % 10 + '0';
		
		sav_val[APP_CH_2][MsCAL_THR_HEAVY] = (rd_fld_buf[SAV_PKT_FLD_CH2_HEAVY_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_HEAVY_L];
		
		buff[buff_cnt++] = 0x2C;   // ,
		
		buff[buff_cnt++] = (sav_val[APP_CH_2][MsCAL_THR_HEAVY] / 1000) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_2][MsCAL_THR_HEAVY] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_val[APP_CH_2][MsCAL_THR_HEAVY] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_val[APP_CH_2][MsCAL_THR_HEAVY]		   % 10 + '0';
		
		buff[buff_cnt++] = 0x2C;   //
		
		sav_field_raw[APP_CH_2] = (rd_fld_buf[SAV_PKT_FLD_CH2_RAW_H]<<8) + rd_fld_buf[SAV_PKT_FLD_CH2_RAW_L];

		buff[buff_cnt++] = (sav_field_raw[APP_CH_2] / 1000) % 10 + '0';
		buff[buff_cnt++] = (sav_field_raw[APP_CH_2] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_field_raw[APP_CH_2] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_field_raw[APP_CH_2]		   % 10 + '0';		
		buff[buff_cnt++] = 0x2C;   // ,
		
		sav_tpr[APP_CH_2] = (rd_fld_buf[SAV_PKT_FLD_TPR_CH2_H]<<8) + rd_fld_buf[SAV_PKT_FLD_TPR_CH2_L];
		
		if(sav_tpr[APP_CH_2]>=0)
			buff[buff_cnt++] = 0x2B;   // ,
		else
			buff[buff_cnt++] = 0x2D;   // ,
			
		sav_tpr[APP_CH_2]=abs(sav_tpr[APP_CH_2]);
		
		buff[buff_cnt++] = (sav_tpr[APP_CH_2] /  100) % 10 + '0';
		buff[buff_cnt++] = (sav_tpr[APP_CH_2] /   10) % 10 + '0';
		buff[buff_cnt++] =	sav_tpr[APP_CH_2]		  % 10 + '0';
		
	
		buff[buff_cnt++] = 0x2C;   // ,
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_STT] / 100) % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_STT] / 10) % 10 + '0';
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_STT]		  % 10 + '0';	

		buff[buff_cnt++] = 0x2C;   // ,
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_POS] + '0';
		
		buff[buff_cnt++] = 0x2C;   // ,
		buff[buff_cnt++] = rd_fld_buf[SAV_PKT_FLD_DIR]+ '0';

		buff[buff_cnt++] = 0x2C;   // ,

		//field_vel = (rd_buf[SAV_PKT_FLD_VEL_H]<<8) + rd_fld_buf[SAV_PKT_FLD_VEL_L];

		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_VEL_H]/  100) % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_VEL_H] /   10) % 10 + '0';
		buff[buff_cnt++] =	rd_fld_buf[SAV_PKT_FLD_VEL_H]		   % 10 + '0';				

		buff[buff_cnt++] = 0x2C;   // ,


		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_VEL_L]/  100) % 10 + '0';
		buff[buff_cnt++] = (rd_fld_buf[SAV_PKT_FLD_VEL_L] /   10) % 10 + '0';
		buff[buff_cnt++] =	rd_fld_buf[SAV_PKT_FLD_VEL_L]		   % 10 + '0';


		buff[buff_cnt++] = 0x00; // NULL
		
		URT_InitMain(URT_IDX_1,115200);
		
		URT_TxPkt(URT_IDX_1, buff, buff_cnt);
		
		lSav.dump_addr += SAV_PKT_FLD_MAX;
		lSav.dump_size += SAV_PKT_FLD_MAX;

	}	

	#if 1
	*rtn_pct = ((F32)lSav.dump_size/(F32)lSav.save_size)*100;

	return rtn;
	#endif
}

static U16 DaSAV_MakeU16(const U08 *buf, U08 hi, U08 lo)
{
	return (U16)(((U16)buf[hi] << 8) | (U16)buf[lo]);
}

static S16 DaSAV_MakeS16(const U08 *buf, U08 hi, U08 lo)
{
	return (S16)DaSAV_MakeU16(buf, hi, lo);
}

static void DaSAV_UsbCopyName(I08 *dst, U16 dstSize, const I08 *src)
{
	if((dst == (void *)0) || (dstSize == 0U) || (src == (void *)0))
		return;

	strncpy(dst, src, dstSize - 1U);
	dst[dstSize - 1U] = 0;
}

static void DaSAV_UsbWriteStdRec(BSP_USB_FILE *pFile, const U08 *r)
{
	U16 ch1Light = DaSAV_MakeU16(r, SAV_PKT_VAL_CH1_LIGHT_H, SAV_PKT_VAL_CH1_LIGHT_L);
	U16 ch1Heavy = DaSAV_MakeU16(r, SAV_PKT_VAL_CH1_HEAVY_H, SAV_PKT_VAL_CH1_HEAVY_L);
	S16 ch1Tpr   = DaSAV_MakeS16(r, SAV_PKT_TPR_CH1_H,       SAV_PKT_TPR_CH1_L);
	U16 ch2Light = DaSAV_MakeU16(r, SAV_PKT_VAL_CH2_LIGHT_H, SAV_PKT_VAL_CH2_LIGHT_L);
	U16 ch2Heavy = DaSAV_MakeU16(r, SAV_PKT_VAL_CH2_HEAVY_H, SAV_PKT_VAL_CH2_HEAVY_L);
	S16 ch2Tpr   = DaSAV_MakeS16(r, SAV_PKT_TPR_CH2_H,       SAV_PKT_TPR_CH2_L);

	BspUsb_FilePrintf(pFile,
		"20%02u-%02u-%02u %02u:%02u,%u,%u,%d,%u,%u,%d\r\n",
		(unsigned int)r[SAV_PKT_TM_YEAR],
		(unsigned int)r[SAV_PKT_TM_MONTH],
		(unsigned int)r[SAV_PKT_TM_DAY],
		(unsigned int)r[SAV_PKT_TM_HOUR],
		(unsigned int)r[SAV_PKT_TM_MIN],
		(unsigned int)ch1Light,
		(unsigned int)ch1Heavy,
		(int)ch1Tpr,
		(unsigned int)ch2Light,
		(unsigned int)ch2Heavy,
		(int)ch2Tpr);
}

static void DaSAV_UsbWriteFieldRec(BSP_USB_FILE *pFile, const U08 *r)
{
	BspUsb_FilePrintf(pFile,
		"20%02u-%02u-%02u %02u:%02u,%u,%u,%u,%u,%d,%u,%u,%u,%u,%d,%u,%u,%u,%u,%u\r\n",
		(unsigned int)r[SAV_PKT_FLD_TM_YEAR],
		(unsigned int)r[SAV_PKT_FLD_TM_MONTH],
		(unsigned int)r[SAV_PKT_FLD_TM_DAY],
		(unsigned int)r[SAV_PKT_FLD_TM_HOUR],
		(unsigned int)r[SAV_PKT_FLD_TM_MIN],
		(unsigned int)r[SAV_PKT_FLD_CH1_EVT],
		(unsigned int)DaSAV_MakeU16(r, SAV_PKT_FLD_CH1_LIGHT_H, SAV_PKT_FLD_CH1_LIGHT_L),
		(unsigned int)DaSAV_MakeU16(r, SAV_PKT_FLD_CH1_HEAVY_H, SAV_PKT_FLD_CH1_HEAVY_L),
		(unsigned int)DaSAV_MakeU16(r, SAV_PKT_FLD_CH1_RAW_H,   SAV_PKT_FLD_CH1_RAW_L),
		(int)DaSAV_MakeS16(r, SAV_PKT_FLD_TPR_CH1_H, SAV_PKT_FLD_TPR_CH1_L),
		(unsigned int)r[SAV_PKT_FLD_CH2_EVT],
		(unsigned int)DaSAV_MakeU16(r, SAV_PKT_FLD_CH2_LIGHT_H, SAV_PKT_FLD_CH2_LIGHT_L),
		(unsigned int)DaSAV_MakeU16(r, SAV_PKT_FLD_CH2_HEAVY_H, SAV_PKT_FLD_CH2_HEAVY_L),
		(unsigned int)DaSAV_MakeU16(r, SAV_PKT_FLD_CH2_RAW_H,   SAV_PKT_FLD_CH2_RAW_L),
		(int)DaSAV_MakeS16(r, SAV_PKT_FLD_TPR_CH2_H, SAV_PKT_FLD_TPR_CH2_L),
		(unsigned int)r[SAV_PKT_FLD_STT],
		(unsigned int)r[SAV_PKT_FLD_POS],
		(unsigned int)r[SAV_PKT_FLD_DIR],
		(unsigned int)r[SAV_PKT_FLD_VEL_H],
		(unsigned int)r[SAV_PKT_FLD_VEL_L]);
}

U08 DaSAV_UsbExportCsv(I08 *filenameBuf, U16 filenameBufSize)
{
	BSP_USB_FILE file;
	I08 fname[BspUsb_FILENAME_MAX];
	U08 rec[SAV_PKT_FLD_MAX];
	U08 fieldMode;
	U08 ret;
	U32 recSize;
	U32 maxCnt;
	U32 count;
	U32 activeSize;
	U32 startAddr;
	U32 ofs;
	U32 i;

	// Snapshot ring-buffer pointers first; do not reuse the legacy UART dump state.
	fieldMode = (MnEGN_PrGet_Item(MnEGN_OPT_MSR) == MnEGN_MSR_ON) ? TRUE : FALSE;
	recSize   = (fieldMode == TRUE) ? SAV_PKT_FLD_MAX : SAV_PKT_MAX;
	maxCnt    = MRM_SIZE_TRD_DAT / recSize;
	count     = lSav.save_cnt;
	if(count > maxCnt)
		count = maxCnt;

	if(lSav.save_f_ov == FALSE)
	{
		activeSize = lSav.save_addr;
		count = activeSize / recSize;
		startAddr = 0;
	}
	else
	{
		activeSize = count * recSize;
		startAddr = lSav.save_addr;
		if((activeSize == 0U) || (startAddr >= activeSize))
			startAddr = 0;
	}

	BspUsb_MakeFilename(fname, sizeof(fname), "ENV130", ".csv");
	ret = BspUsb_FileOpenUnique(&file, fname);
	if(ret != BspUsb_FILE_OK)
		return ret;

	DaSAV_UsbCopyName(filenameBuf, filenameBufSize, file.name);

	if(fieldMode == TRUE)
		BspUsb_FilePrintf(&file, "Date,Ch1Event,CH1-Light Level,CH1-Heavy Level,Ch1Raw,CH1-Temp,Ch2Event,CH2-Light Level,CH2-Heavy Level,Ch2Raw,CH2-Temp,Status,Position,Direction,VelH,VelL\r\n");
	else
		BspUsb_FilePrintf(&file, "Date,CH1-Light Level,CH1-Heavy Level,CH1-Temp,CH2-Light Level,CH2-Heavy Level,CH2-Temp\r\n");

	for(i = 0; (i < count) && (file.error == BspUsb_FILE_OK); i++)
	{
		ofs = startAddr + (i * recSize);
		if((activeSize != 0U) && (ofs >= activeSize))
			ofs %= activeSize;

		MRM_RdBulk(_mTrBOD_START + ofs, rec, (U08)recSize);
		if(fieldMode == TRUE)
			DaSAV_UsbWriteFieldRec(&file, rec);
		else
			DaSAV_UsbWriteStdRec(&file, rec);

		if((i & 0x3FU) == 0U)
			DaMdb_ProcMain();
	}

	ret = BspUsb_FileClose(&file);
	DaSAV_UsbCopyName(filenameBuf, filenameBufSize, file.name);
	return ret;
}

void DaSAV_DeleteData(void)
{
	memset(&lSav.prv_tim, 0, sizeof(RTC_TM));
	
	lSav.t_1s_cnt = 0;
	
	lSav.save_f_ov  = FALSE;
	lSav.save_addr = 0;
	lSav.save_cnt = 0;
	lSav.save_size = 0;	
	
	MRM_WrByte(_mTrHDR_SAV_OVF,   lSav.save_f_ov);
	MRM_WrLong(_mTrHDR_SAV_ADDR3, lSav.save_addr);
	MRM_WrLong(_mTrHDR_SAV_CNT3,  lSav.save_cnt);

	DaSAV_InitVari();
}


U08* DaSAV_GetPkt(U32 idx)
{
	U32 diff = 0;
	U32 addr_now = _mTrBOD_START + lSav.save_addr;
	U32 addr_cal = addr_now - (idx*SAV_PKT_MAX);

	if(addr_cal < _mTrBOD_START)
	{
		diff     = _mTrBOD_START - addr_cal;
		addr_cal = _mTrBOD_START + MRM_SIZE_TRD_DAT - diff;
	}

	MRM_RdBulk(addr_cal, lSav.pkt, SAV_PKT_MAX);

	return lSav.pkt;
}
#if 0
void DaTrend_Proc(U08 ch)
{
	U16 i,j;
	S16 val[MsCAL_THR_TYPE_NUM];
	S64 sum[MsCAL_THR_TYPE_NUM];
	U16 empty;

	if(ApSCD_GetVl_Prof_Full(ch)==FALSE)
		return;

	empty = MnMSR_BaseGet_Ch_Value(ch,MnMS0_OPT_SINGLE_EMPTY);

	if(MsCAL1_Get_fdtt(ch)==_F_T)
		lSav.trend_cnt[ch] = 0;

	lSav.trend_cnt[ch]++;

	if(lSav.trend_cnt[ch]>300)
		lSav.trend_cnt[ch]=300;


	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		if(MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_SLUDGE)
			val[j] = MsCAL_GetVl_RsltSldg(ch,j);
		else if (MnMSR_BaseGet_Ch_Value(ch, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_DISTANCE)
			val[j] = MsCAL_GetVl_RsltDist(ch,j);
	}

	// Buffer Shift Save
	for(i=lSav.trend_cnt[ch]-1; i>0; i--)
	{
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			lSav.trend_buff[ch][j][i] = lSav.trend_buff[ch][j][i-1];
		}
		DaMdb_ProcMain();
	}
	


	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lSav.trend_buff[ch][j][0] = val[j];
		sum[j] = 0;
	}
	
	// Sum Data
	for(i=0; i<lSav.trend_cnt[ch]; i++)
	{
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			sum[j] += lSav.trend_buff[ch][j][i];
		}
		DaMdb_ProcMain();
	}

	for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
	{
		lSav.trend_mean[ch][j] = sum[j]/lSav.trend_cnt[ch];

	
		if(lSav.trend_mean[ch][j]>=empty)
			lSav.trend_mean[ch][j] = empty;

		if(lSav.trend_mean[ch][j]<0)
			lSav.trend_mean[ch][j] = 0;
	}
}
#endif

void DaSAV_ProcSave(void)
{	
	U16 val[APP_CH_NUM][MsCAL_THR_TYPE_NUM];
	U16 field_raw_val[APP_CH_NUM];
	S16 tpr[APP_CH_NUM];
	U16 dat_intv = 0;
	U08 buff_dat[SAV_PKT_MAX] = {0, };
	U08 buff_field_dat[SAV_PKT_FLD_MAX] = {0, };
	RTC_TM curr_tm = RTC_GetTime();
	U16 i,j;
	U08 stt = (ApSTT_GetStatus(ApSTT_CH_S0)*10)+ApSTT_GetStatus(ApSTT_CH_S1);
	
	for(i=0; i<APP_CH_NUM; i++)
	{
		for(j=0; j<MsCAL_THR_TYPE_NUM; j++)
		{
			if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)
			{
				if(MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_SLUDGE)
					val[i][j] = MsCAL_GetVl_RsltSldg(i,j);
				else if (MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_DISTANCE)
					val[i][j] = MsCAL_GetVl_RsltDist(i,j);
			}
			else if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
			{				
				if(MnMSR_BaseGet_Ch_Value(i, MnMS0_OPT_SINGLE_OPERATION) == MnMS0_OPERATION_SLUDGE)
					field_raw_val[i] = MsCAL_GetVl_RsltSldg(i,MsCAL_THR_HEAVY);
				else
					field_raw_val[i] = MsCAL_GetVl_RsltDist(i,MsCAL_THR_HEAVY);
				
			}
		}
		tpr[i] = MsTPR_GetTprt(i);
	}



	
	switch(MnDAT_SavPrGet_Value(MnDS0_OPT_INTERVAL))
	{
		case MnDS0_INTV_01S:	dat_intv = SAV_INTERVAL_01S;	break;
		case MnDS0_INTV_10S: 	dat_intv = SAV_INTERVAL_10S;	break;
		case MnDS0_INTV_01M: 	dat_intv = SAV_INTERVAL_01M;	break;
		case MnDS0_INTV_10M: 	dat_intv = SAV_INTERVAL_10M;	break;
		case MnDS0_INTV_01H: 	dat_intv = SAV_INTERVAL_01H;	break;
		default:												break;
	}


#if 0
	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{
		DaTrend_Proc(APP_CH_1);
		DaTrend_Proc(APP_CH_2);

		DaSav_St_deviation(APP_CH_1);
		DaSav_St_deviation(APP_CH_2);
	}
#endif

	if(lSav.dump_f_en == TRUE)
		return;

	if(++lSav.t_1s_cnt < dat_intv)
		return;

	lSav.t_1s_cnt = 0;

	memcpy(&lSav.prv_tim, &curr_tm, sizeof(RTC_TM)); 

	if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_OFF)
	{

		if((lSav.save_addr+SAV_PKT_MAX) > MRM_SIZE_TRD_DAT)
		{
			lSav.save_addr = 0;
			lSav.save_f_ov = TRUE;
		}

		buff_dat[SAV_PKT_TM_YEAR]	= curr_tm.year;
		buff_dat[SAV_PKT_TM_MONTH]	= curr_tm.month;
		buff_dat[SAV_PKT_TM_DAY]	= curr_tm.day;
		buff_dat[SAV_PKT_TM_HOUR]	= curr_tm.hours;
		buff_dat[SAV_PKT_TM_MIN]	= curr_tm.minutes;
		buff_dat[SAV_PKT_VAL_CH1_LIGHT_H] = (U08)((val[APP_CH_1][MsCAL_THR_LIGHT] & 0xff00) >> 8);
		buff_dat[SAV_PKT_VAL_CH1_LIGHT_L] = (U08)((val[APP_CH_1][MsCAL_THR_LIGHT] & 0x00ff) >> 0);
		buff_dat[SAV_PKT_VAL_CH1_HEAVY_H] = (U08)((val[APP_CH_1][MsCAL_THR_HEAVY] & 0xff00) >> 8);
		buff_dat[SAV_PKT_VAL_CH1_HEAVY_L] = (U08)((val[APP_CH_1][MsCAL_THR_HEAVY] & 0x00ff) >> 0);	
		buff_dat[SAV_PKT_TPR_CH1_H] = (U08)((tpr[APP_CH_1] & 0xff00) >> 8);
		buff_dat[SAV_PKT_TPR_CH1_L] = (U08)((tpr[APP_CH_1] & 0x00ff) >> 0);
		buff_dat[SAV_PKT_VAL_CH2_LIGHT_H] = (U08)((val[APP_CH_2][MsCAL_THR_LIGHT] & 0xff00) >> 8);
		buff_dat[SAV_PKT_VAL_CH2_LIGHT_L] = (U08)((val[APP_CH_2][MsCAL_THR_LIGHT] & 0x00ff) >> 0);
		buff_dat[SAV_PKT_VAL_CH2_HEAVY_H] = (U08)((val[APP_CH_2][MsCAL_THR_HEAVY] & 0xff00) >> 8);
		buff_dat[SAV_PKT_VAL_CH2_HEAVY_L] = (U08)((val[APP_CH_2][MsCAL_THR_HEAVY] & 0x00ff) >> 0);	
		buff_dat[SAV_PKT_TPR_CH2_H] = (U08)((tpr[APP_CH_2] & 0xff00) >> 8);
		buff_dat[SAV_PKT_TPR_CH2_L] = (U08)((tpr[APP_CH_2] & 0x00ff) >> 0);	
		buff_dat[SAV_PKT_STT] = stt;
		
		MRM_WrBulk(_mTrBOD_START+lSav.save_addr, buff_dat, SAV_PKT_MAX);
		lSav.save_addr +=SAV_PKT_MAX;
		
		if(!lSav.save_f_ov) lSav.save_size = lSav.save_addr;
		
	}
	else if(MnEGN_PrGet_Item(MnEGN_OPT_MSR)==MnEGN_MSR_ON)
	{

		if((lSav.save_addr+SAV_PKT_FLD_MAX) > MRM_SIZE_TRD_DAT)
		{
			lSav.save_addr = 0;
			lSav.save_f_ov = TRUE;
		}
#if 0
		buff_field_dat[SAV_PKT_FLD_TM_YEAR]	= curr_tm.year;
		buff_field_dat[SAV_PKT_FLD_TM_MONTH]	= curr_tm.month;
		buff_field_dat[SAV_PKT_FLD_TM_DAY]	= curr_tm.day;
		buff_field_dat[SAV_PKT_FLD_TM_HOUR]	= curr_tm.hours;
		buff_field_dat[SAV_PKT_FLD_TM_MIN]	= curr_tm.minutes;
		buff_field_dat[SAV_PKT_FLD_CH1_EVT]   = (U08)((lSav.trend_deviat_value[APP_CH_1] & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH1_LIGHT_H] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_1, MsCAL_THR_HEAVY) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH1_LIGHT_L] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_1, MsCAL_THR_HEAVY) & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH1_HEAVY_H] = ((MsCAL_GetVl_FieldSldg(APP_CH_1) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH1_HEAVY_L] = ((MsCAL_GetVl_FieldSldg(APP_CH_1) & 0x00ff) >> 0);	
		buff_field_dat[SAV_PKT_FLD_CH1_RAW_H] = (U08)((field_raw_val[APP_CH_1] & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH1_RAW_L] = (U08)((field_raw_val[APP_CH_1] & 0x00ff) >> 0);			
		buff_field_dat[SAV_PKT_FLD_TPR_CH1_H] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_1, MsCAL_THR_LIGHT) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_TPR_CH1_L] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_1, MsCAL_THR_LIGHT) & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH2_EVT]   = (U08)((lSav.trend_deviat_value[APP_CH_2] & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH2_LIGHT_H] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_2, MsCAL_THR_HEAVY) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH2_LIGHT_L] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_2, MsCAL_THR_HEAVY) & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH2_HEAVY_H] = (U08)((MsCAL_GetVl_FieldSldg(APP_CH_2) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH2_HEAVY_L] = (U08)((MsCAL_GetVl_FieldSldg(APP_CH_2)  & 0x00ff) >> 0);	
		buff_field_dat[SAV_PKT_FLD_CH2_RAW_H] = (U08)((field_raw_val[APP_CH_2] & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH2_RAW_L] = (U08)((field_raw_val[APP_CH_2] & 0x00ff) >> 0);			
		buff_field_dat[SAV_PKT_FLD_TPR_CH2_H] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_2, MsCAL_THR_LIGHT) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_TPR_CH2_L] = (U08)((MsCAL1_Getrst_Value_old(APP_CH_2, MsCAL_THR_LIGHT) & 0x00ff) >> 0); 
		buff_field_dat[SAV_PKT_FLD_STT] = ((U08)MsCal1_Getrst_dtt(APP_CH_1) || (U08)MsCal1_Getrst_dtt(APP_CH_2));
		buff_field_dat[SAV_PKT_FLD_POS] = (U08)MsCAL1_Getfin_pos();
		buff_field_dat[SAV_PKT_FLD_DIR] = (U08)MsCAL1_Getfin_dir();
		buff_field_dat[SAV_PKT_FLD_VEL_H] = (U08)((lSav.trend_deviat_value2[APP_CH_1] & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_VEL_L] = (U08)((lSav.trend_deviat_value2[APP_CH_2] & 0x00ff) >> 0);
#else
		buff_field_dat[SAV_PKT_FLD_TM_YEAR]	= curr_tm.year;
		buff_field_dat[SAV_PKT_FLD_TM_MONTH]	= curr_tm.month;
		buff_field_dat[SAV_PKT_FLD_TM_DAY]	= curr_tm.day;
		buff_field_dat[SAV_PKT_FLD_TM_HOUR]	= curr_tm.hours;
		buff_field_dat[SAV_PKT_FLD_TM_MIN]	= curr_tm.minutes;
		buff_field_dat[SAV_PKT_FLD_CH1_EVT]   = MsCal1_Getrst_dtt(APP_CH_1);
		buff_field_dat[SAV_PKT_FLD_CH1_LIGHT_H] = (U08)((MsCAL_GetVl_FieldSldg(APP_CH_1) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH1_LIGHT_L] = (U08)((MsCAL_GetVl_FieldSldg(APP_CH_1) & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH1_HEAVY_H] = (U08)((MsCAL1_Hunting_value(APP_CH_1, MsCAL_THR_HEAVY) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH1_HEAVY_L] = (U08)((MsCAL1_Hunting_value(APP_CH_1, MsCAL_THR_HEAVY) & 0x00ff) >> 0);	
		buff_field_dat[SAV_PKT_FLD_CH1_RAW_H] = (U08)((field_raw_val[APP_CH_1] & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH1_RAW_L] = (U08)((field_raw_val[APP_CH_1] & 0x00ff) >> 0);			
		buff_field_dat[SAV_PKT_FLD_TPR_CH1_H] = (U08)((tpr[APP_CH_1] & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_TPR_CH1_L] = (U08)((tpr[APP_CH_1] & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH2_EVT]   = MsCal1_Getrst_dtt(APP_CH_2);
		buff_field_dat[SAV_PKT_FLD_CH2_LIGHT_H] = (U08)((MsCAL_GetVl_FieldSldg(APP_CH_2) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH2_LIGHT_L] = (U08)((MsCAL_GetVl_FieldSldg(APP_CH_2) & 0x00ff) >> 0);
		buff_field_dat[SAV_PKT_FLD_CH2_HEAVY_H] = (U08)((MsCAL1_Hunting_value(APP_CH_2, MsCAL_THR_HEAVY) & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH2_HEAVY_L] = (U08)((MsCAL1_Hunting_value(APP_CH_2, MsCAL_THR_HEAVY) & 0x00ff) >> 0);	
		buff_field_dat[SAV_PKT_FLD_CH2_RAW_H] = (U08)((field_raw_val[APP_CH_2] & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_CH2_RAW_L] = (U08)((field_raw_val[APP_CH_2] & 0x00ff) >> 0);			
		buff_field_dat[SAV_PKT_FLD_TPR_CH2_H] = (U08)((tpr[APP_CH_2] & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_TPR_CH2_L] = (U08)((tpr[APP_CH_2] & 0x00ff) >> 0); 
		buff_field_dat[SAV_PKT_FLD_STT] = stt;
		buff_field_dat[SAV_PKT_FLD_POS] = (U08)MsCAL1_Getrst_pos();
		buff_field_dat[SAV_PKT_FLD_DIR] = (U08)MsCAL1_Getrst_dir();
		buff_field_dat[SAV_PKT_FLD_VEL_H] = (U08)((MsCAL1_Getrst_dir() & 0xff00) >> 8);
		buff_field_dat[SAV_PKT_FLD_VEL_L] = (U08)((MsCAL1_Getrst_dir() & 0x00ff) >> 0);





#endif
		
		MRM_WrBulk(_mTrBOD_START+lSav.save_addr, buff_field_dat, SAV_PKT_FLD_MAX);
		lSav.save_addr +=SAV_PKT_FLD_MAX;
		
		if(!lSav.save_f_ov) lSav.save_size = lSav.save_addr;


	}

	if(!lSav.save_f_ov)	lSav.save_cnt++;	

	// Header
	MRM_WrByte(_mTrHDR_SAV_OVF, lSav.save_f_ov);
	MRM_WrLong(_mTrHDR_SAV_ADDR3, lSav.save_addr);
	MRM_WrLong(_mTrHDR_SAV_CNT3, lSav.save_cnt);
}

void DaSAV_InitVari(void)
{
	U08 i,j;
	#if 1
	memset(&lSav.prv_tim, 0, sizeof(RTC_TM));
	#endif
	lSav.t_1s_cnt = 0xffff;

	lSav.save_f_ov = MRM_RdByte(_mTrHDR_SAV_OVF);
	lSav.save_addr = MRM_RdLong(_mTrHDR_SAV_ADDR3);
	lSav.save_cnt  = MRM_RdLong(_mTrHDR_SAV_CNT3);

	lSav.dump_addr = 0;
	lSav.dump_size = 0;
	lSav.dump_f_en = FALSE;

	lSav.save_loading = FALSE;

	for(i=0; i<SAV_PKT_MAX; i++)
		lSav.pkt[i] = 0;

}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

