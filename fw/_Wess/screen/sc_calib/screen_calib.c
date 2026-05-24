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
// bsp
#include "bsp_ram.h"
// app
#include "app_main.h"
#include "app_schd1sec.h"
// function
#include "input_main.h"
#include "input_key.h"
// menu
#include "menu_factory.h"
#include "menu_engineer.h"
// display
#include "disp_string.h"
#include "disp_button.h"
// disp - screen
#include "dp_screen_echo.h"
// screen
#include "screen_main.h"
#include "screen_clb0_func.h"
#include "screen_clb1_list.h"
#include "screen_clb2_value.h"
// self
#include "screen_calib.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ScCLB_LS lScClb;


U16 lMsr_aTvg[MnEGN_TVG_MAX][TVG_IDX_MAX] = {
	{	  1,   3,   6,  9,   12,  15,  17,  20,  23,  26,  29,  32,  35,  38,  41,  44,  47,  49,  52,  55,		// 20
		 58,  61,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 113,    	// 40
		116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 157} ,							// ADC_BUFF_MAX/20
	{	  1,   5,   7,   9,  12,  15,  17,  20,  23,  26,  29,  32,  35,  38,  41,  44,  47,  49,  52,  55,		// 20
		 58,  61,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 113,    	// 40
		116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 157} ,							// ADC_BUFF_MAX/20

	{	  1,  10,  12,  13,  15,  16,  17,  20,  23,  26,  29,  32,  35,  38,  41,  44,  47,  49,  52,  55,		// 20
		 58,  61,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 113,    	// 40
		116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 157} ,							// ADC_BUFF_MAX/20
	{	  1,  13,  15,  16,  17,  19,  20,  22,  23,  26,  29,  32,  35,  38,  41,  44,  47,  49,  52,  55,		// 20
		 58,  61,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 113,    	// 40
		116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 157} ,							// ADC_BUFF_MAX/20

	{	  1,  16,  17,  19,  20,  22,  23,  25,  26,  28,  29,  32,  35,  38,  41,  44,  47,  49,  52,  55,		// 20
		 58,  61,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 113,    	// 40
		116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 157} ,							// ADC_BUFF_MAX/20
	{	  1,  19,  20,  22,  23,  25,  26,  28,  29,  31,  32,  33,  35,  38,  41,  44,  47,  49,  52,  55,		// 20
		 58,  61,  64,  67,  70,  73,  76,  79,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 113,    	// 40
		116, 119, 122, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 157} ,							// ADC_BUFF_MAX/20

	{	  1,  9,   14,	17,  20,  22,  24,	25,  27,  28,  29,	30,  31,  32,  33,	34,  35,  36,  37,	37,
	 	 38,  38,  39,	40,  40,  40,  41,	41,  42,  42,  42,	43,  43,  43,  44,	44,  44,  45,  45,	45,
		 45,  46,  46,	46,  46,  47,  47,	47,  48,  48,  48,  48,  49,  49,  49} ,		
};

U16 lMsr_aTvg_custom_DEF[TVG_IDX_MAX] = 
	{	  1,  12,  19,	24,  27,  30,  33,	35,  37,  38,  40,	41,  43,  44,  45,	46,  47,  48,  49,	50,
	 	 50,  51,  52,	53,  53,  54,  55,	55,  56,  56,  57,	57,  58,  58,  59,	59,  60,  60,  60,	61,
		 61,  62,  62,	62,  63,  63,  64,	64,  64,  65,  65,  65,  66,  67,  68};


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Parameter
//------------------------------------------------------------------------------------------------------------------------------
// TVG
#if 0
U16  ScCLB_PrGet_Tvg_Custom(U08 ch, U08 x)					   {	return lScClb.mPr.aTvg_custom[ch][x];		}
void ScCLB_PrSet_Tvg_Custom(U08 ch, U08 x, U16 val)		  {			lScClb.mPr.aTvg_custom[ch][x] = val;		}
U08  ScCLB_PrGet_Tvg_x_axis(U08 ch)								{	return lScClb.mPr.aTvg_x_axis[ch];			}
#endif
// Fuction
S32 ScCLB_PrGet_Value(U08 iCh, U08 iFn)
{
#if 0
	U08 sel;
	
	switch(iFn)
	{	// Calibration #1
		case ScCLB_F00_FREQ:			return lScClb.mPr.FREQ[iCh];
		case ScCLB_F01_TX_WAV:			return lScClb.mPr.wave[iCh];
		case ScCLB_F02_RX_GAIN:			return lScClb.mPr.gain[iCh];
		case ScCLB_F03_RX_TRANS:		return lScClb.mPr.gain_trans[iCh];
		case ScCLB_F04_RX_AMP:			return lScClb.mPr.amp[iCh];
		case ScCLB_F05_TVG_fEN:			return lScClb.mPr.fTvg[iCh];
		case ScCLB_F06_TVG_CUSTOM:		
			switch(ScCB2_GetSelStep())
			{
				case SCRN_L2_SEL_STEP0:	
					return lScClb.mPr.aTvg_x_axis[iCh];
				case SCRN_L2_SEL_STEP1:
					sel = lScClb.mPr.aTvg_x_axis[iCh];
					return lScClb.mPr.aTvg_custom[iCh][sel];
				default:				break;
			}
			break;
		// Callibration #2
		// Not Define
		default:						break;
	}
#endif
	return MENU_VAL_INVALID;

}


void ScCLB_PrSet_Value(S32 val)
{
#if 0
	U08 iCh = ScECH_PrGet_Chnnl();
	U08 iFn = ScCB1_GetIdxFunc();
	U08 sel;

	switch(iFn)
	{	// Calibration #1
		case ScCLB_F00_FREQ:			lScClb.mPr.FREQ[iCh] = (U08)val;				break;
		case ScCLB_F01_TX_WAV:			lScClb.mPr.wave[iCh] = (U16)val;				break;
		case ScCLB_F02_RX_GAIN:			lScClb.mPr.gain[iCh] = (U16)val;				break;
		case ScCLB_F03_RX_TRANS:		lScClb.mPr.gain_trans[iCh] = (U16)val;			break;		
		case ScCLB_F04_RX_AMP:			lScClb.mPr.amp[iCh]  = (U08)val;				break;
		// Calibration#2
		case ScCLB_F05_TVG_fEN:			lScClb.mPr.fTvg[iCh] = (U08)val;				break;
		case ScCLB_F06_TVG_CUSTOM:		
			switch(ScCB2_GetSelStep())
			{
				case SCRN_L2_SEL_STEP0:	
					lScClb.mPr.aTvg_x_axis[iCh] = (U08)val;		
					break;
				case SCRN_L2_SEL_STEP1:
					sel = lScClb.mPr.aTvg_x_axis[iCh];
					lScClb.mPr.aTvg_custom[iCh][sel] = val;
					break;
				default:
					break;
			}
			break;
		default:						
			break;
	}

	switch(iFn)
	{	// Calibration #1
		case ScCLB_F00_FREQ:		MRM_WrByte(_mScCLB_FREQ0  +(iCh*1), lScClb.mPr.FREQ[iCh]);						break;
		case ScCLB_F01_TX_WAV:		MRM_WrWord(_mScCLB_TX_W0_L+(iCh*2), lScClb.mPr.wave[iCh]);						break;
		case ScCLB_F02_RX_GAIN:		MRM_WrWord(_mScCLB_RX_G0_L+(iCh*2), lScClb.mPr.gain[iCh]);						break;
		case ScCLB_F03_RX_TRANS:	MRM_WrWord(_mScCLB_RX_TRANS_G0_L+(iCh*2), lScClb.mPr.gain_trans[iCh]);			break;
		case ScCLB_F04_RX_AMP:		MRM_WrByte(_mScCLB_RX_AMP0+(iCh*1), lScClb.mPr.amp[iCh]);						break;
		case ScCLB_F05_TVG_fEN:		MRM_WrByte(_mScCLB_TVG_F0+(iCh*1), lScClb.mPr.fTvg[iCh]);						break;
		case ScCLB_F06_TVG_CUSTOM:	
			switch(ScCB2_GetSelStep())
			{
				case SCRN_L2_SEL_STEP1:		
					switch(iCh)
					{
						case ScCLB_CH_0:	
							MRM_WrByte(_mScCLB_TVG_CH0+lScClb.mPr.aTvg_x_axis[iCh], lScClb.mPr.aTvg_custom[iCh][sel]);				
							break;
						case ScCLB_CH_1:
							MRM_WrByte(_mScCLB_TVG_CH1+lScClb.mPr.aTvg_x_axis[iCh], lScClb.mPr.aTvg_custom[iCh][sel]);				
							break;							
						default:			break;
					}
					break;
				default:					break;
			}
			break;
		// Not Define
		default:					break;
	}
#endif
}

void ScCLB_PrRst_Factory(void)
{
#if 0
	U08 i;
#if 0
	U32 aTvg[ScCLB_CH_NUM] = {_mScCLB_TVG_C0P0_L, _mScCLB_TVG_C1P0_L};
#endif
	for(i=0; i<ScCLB_CH_NUM; i++)
	{	// Calibration #1
		MRM_WrByte(_mScCLB_FREQ0  +(i*1), ScCLB_FREQ_DEF);
		MRM_WrWord(_mScCLB_TX_W0_L+(i*2), ScCLB_TX_WAV_DEF);
		MRM_WrWord(_mScCLB_RX_G0_L+(i*2), ScCLB_RX_GAIN_DEF);
		MRM_WrWord(_mScCLB_RX_TRANS_G0_L+(i*2), ScCLB_RX_TRANS_DEF);
		MRM_WrByte(_mScCLB_RX_AMP0+(i*1), ScCLB_RX_AMP_DEF);
		MRM_WrByte(_mScCLB_TVG_F0 +(i*1), ScCLB_TVG_DEF);
		// TVG 
#if 0
		for(j=0; j<ScCLB_TVG_NUM; j++)
			MRM_WrWord(aTvg[i] + (j*2), ScCLB_RX_GAIN_DEF);
#endif
	}
	for(i=0; i<ScCLB_TVG_X_AXIS_MAX;	i++)
	{
		MRM_WrByte(_mScCLB_TVG_CH0+i, lMsr_aTvg_custom_DEF[i]);
		MRM_WrByte(_mScCLB_TVG_CH1+i, lMsr_aTvg_custom_DEF[i]);
	}
#endif
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 ScCLB_GetLayer(void)			{	return lScClb.lyr;					}
U08 ScCLB_GetCh(void)				{	return lScClb.mPr.ch;				}	
// Set
void ScCLB_SetLayer(U08 lyr)		{	lScClb.lyr = lyr;					}
void ScCLB_SetCh(U08 ch)			{	lScClb.mPr.ch = ch;					}	


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Basic
//------------------------------------------------------------------------------------------------------------------------------
void ScCLB_PrInitMain(void)
{
#if 0
	U08 i;

	// Read Parameters
	for(i=0; i<ScCLB_CH_NUM; i++)
	{
		lScClb.mPr.FREQ[i] = MRM_RdByte(_mScCLB_FREQ0	+ (i*1));
		lScClb.mPr.wave[i] = MRM_RdWord(_mScCLB_TX_W0_L + (i*2));
		lScClb.mPr.gain[i] = MRM_RdWord(_mScCLB_RX_G0_L + (i*2));
		lScClb.mPr.gain_trans[i] = MRM_RdWord(_mScCLB_RX_TRANS_G0_L + (i*2));
		lScClb.mPr.amp[i] = MRM_RdByte(_mScCLB_RX_AMP0 + (i*1));
		lScClb.mPr.fTvg[i] = MRM_RdByte(_mScCLB_TVG_F0	+ (i*1));
		lScClb.mPr.aTvg_x_axis[i] = ScCLB_TVG_X_AXIS_MIN;
#if 0
		for(j=0; j<ScCLB_TVG_NUM; j++)
			lScClb.mPr.aTvg[i][j] = MRM_RdWord(aTvg[i] + (j*2));
#endif
	}

	for(i=0; i<ScCLB_TVG_X_AXIS_MAX; i++)
	{
		lScClb.mPr.aTvg_custom[ScCLB_CH_0][i] = MRM_RdByte(_mScCLB_TVG_CH0+i);
		lScClb.mPr.aTvg_custom[ScCLB_CH_1][i] = MRM_RdByte(_mScCLB_TVG_CH1+i);
		if(lScClb.mPr.aTvg_custom[ScCLB_CH_0][i] < 2000)	lScClb.mPr.aTvg_custom[ScCLB_CH_0][i] = lMsr_aTvg_custom_DEF[i];
		if(lScClb.mPr.aTvg_custom[ScCLB_CH_1][i] < 2000)	lScClb.mPr.aTvg_custom[ScCLB_CH_1][i] = lMsr_aTvg_custom_DEF[i];
	}

	// Dual Sensor
	lScClb.mPr.ch = MRM_RdByte(_mScCLB_CHNNL);

	// Check Parameters
	for(i=0; i<ScCLB_CH_NUM; i++)
	{
		if(lScClb.mPr.FREQ[i] >= ScCLB_FREQ_NUM)			lScClb.mPr.FREQ[i] = ScCLB_FREQ_DEF;
		if(lScClb.mPr.wave[i] < ScCLB_TX_WAV_MIN)			lScClb.mPr.wave[i] = ScCLB_TX_WAV_DEF;
		if(lScClb.mPr.wave[i] > ScCLB_TX_WAV_MAX)			lScClb.mPr.wave[i] = ScCLB_TX_WAV_DEF;
		if(lScClb.mPr.gain[i] < ScCLB_RX_GAIN_MIN)			lScClb.mPr.gain[i] = ScCLB_RX_GAIN_DEF;
		if(lScClb.mPr.gain[i] > ScCLB_RX_GAIN_MAX)			lScClb.mPr.gain[i] = ScCLB_RX_GAIN_DEF;
		if(lScClb.mPr.gain_trans[i] < ScCLB_RX_TRANS_MIN)	lScClb.mPr.gain_trans[i] = ScCLB_RX_TRANS_DEF;
		if(lScClb.mPr.gain_trans[i] > ScCLB_RX_TRANS_MAX)	lScClb.mPr.gain_trans[i] = ScCLB_RX_TRANS_DEF;
		if(lScClb.mPr.amp[i] >= ScCLB_RX_AMP_NUM)			lScClb.mPr.amp[i] = ScCLB_RX_AMP_DEF;
		if(lScClb.mPr.fTvg[i] < ScCLB_TVG_MIN)				lScClb.mPr.fTvg[i] = ScCLB_TVG_DEF;
		if(lScClb.mPr.fTvg[i] > ScCLB_TVG_MAX)				lScClb.mPr.fTvg[i] = ScCLB_TVG_DEF;
	#if 0
		for(j=0; j<ScCLB_TVG_NUM; j++)
			if(lScClb.mPr.aTvg[i][j] > ScCLB_RX_GAIN_MAX)		lScClb.mPr.aTvg[i][j] = ScCLB_RX_GAIN_DEF;
	#endif
	}

	// Check Sensor Type
	if(MnFTR_PrGet_SsChn() == MnFTR_SS_SINGLE)
	{
		lScClb.mPr.ch = ScCLB_CH_0;
		MRM_WrByte(_mScCLB_CHNNL, lScClb.mPr.ch);
	}
#endif

}

void ScCLB_InitMain(void)
{
	//U32 aTvg[ScCLB_CH_NUM] = {_mScCLB_TVG_C0P0_L, _mScCLB_TVG_C1P0_L};

	// Layer
	lScClb.lyr = SCRN_L0_FUNC;

	// Layers Init
	ScCB0_InitFunc();
	ScCB1_InitList();
	ScCB2_InitValu();

	ScCLB_PrInitMain();
}

void ScCLB_ProcMain(void)
{
	switch(lScClb.lyr)
	{
		case SCRN_L0_FUNC:		ScCB0_ProcFunc();			break;
		case SCRN_L1_LIST:		ScCB1_ProcList();			break;
		case SCRN_L2_VALU:		ScCB2_ProcValu();			break;
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

