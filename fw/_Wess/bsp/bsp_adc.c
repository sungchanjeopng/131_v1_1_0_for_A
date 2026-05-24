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
// self
#include "bsp_adc.h"
#include "screen_calib.h"
#include "menu_test.h"
#include "stm32f7xx_hal_dac.h"
#include "dac.h"
#include "menu_measure.h"
//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
ADC_LS lAdc;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void AdcEcho_SetStart(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	if(HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

void AdcTprt_SetStart(void)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = ENABLE;
	hadc1.Init.NbrOfDiscConversion = 1;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 2;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
	  Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = ADC_REGULAR_RANK_2;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U16 ADC_GetTprtVal(U08 ch)				{	return lAdc.tprt_aVl[ch];			}
U16 ADC_GetTprtVlt(U08 idx)				{	return lAdc.tprt_aVt[idx];			}
U16 ADC_GetEchoVal(U08 ch, U16 idx)		{	return lAdc.echo_aBf[ch][idx];		}
U16 ADC_GetEchoIdx(void)				{	return lAdc.echo_idx;				}
U16 ADC_GetEchoIdx_max(void)			{	return lAdc.echo_idx_max;				}
U08 ADC_GetChnlIdx(void)				{	return lAdc.chnl_idx;				}
U32* ADC_GetEchoAddr(U08 ch)			{	return (U32*)&lAdc.echo_aBf[ch];	}
U08 ADC_Get_FieldSel(void)				{	return lAdc.filed_sel;				}
// Set
void ADC_SetEchoVal(U08 ch, U16 idx, U16 val)	{	lAdc.echo_aBf[ch][idx] = val;		}
void ADC_SetEchoIdx(U16 val)					{	lAdc.echo_idx = val;				}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void ADC_InitVari(void)
{
	lAdc.chnl_idx = ADC_CH_SS0;
	lAdc.echo_idx = 0;
	lAdc.echo_idx_max = 0;

	lAdc.tprt_aVl[ADC_CH_SS0] = 0;
	lAdc.tprt_aVl[ADC_CH_SS1] = 0;
	lAdc.tprt_aVt[ADC_CH_SS0] = 0;
	lAdc.tprt_aVt[ADC_CH_SS1] = 0;
	lAdc.filed_sel = 0;
	memset(lAdc.echo_aBf[ADC_CH_SS0], 0, sizeof(lAdc.echo_aBf[ADC_CH_SS0]));
	memset(lAdc.echo_aBf[ADC_CH_SS1], 0, sizeof(lAdc.echo_aBf[ADC_CH_SS1]));
}

void ADC_ProcTprt(void)
{
	AdcTprt_SetStart();
	
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	lAdc.tprt_aVl[ADC_CH_SS0] = HAL_ADC_GetValue(&hadc1);
	lAdc.tprt_aVt[ADC_CH_SS0] = 3300 * lAdc.tprt_aVl[ADC_CH_SS0] / 4096;
	
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	lAdc.tprt_aVl[ADC_CH_SS1] = HAL_ADC_GetValue(&hadc1);
	lAdc.tprt_aVt[ADC_CH_SS1] = 3300 * lAdc.tprt_aVl[ADC_CH_SS1] / 4096;
}

void ADC_ProcEcho(U08 ch)
{

	U16 cWave  = MnTST_PrGet_CH_Value(MsSEN_PrGet_Sel_ch(),MnTST_OPT_SINGLE_PULSE_NO);
	U08 FREQ   = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_FREQ);


	lAdc.chnl_idx = ch;
	lAdc.filed_sel = 0;
	if(FREQ == MnMS1_FREQ_380K)
		lAdc.echo_idx = cWave/5;
	else if(FREQ == MnMS1_FREQ_270K)
		lAdc.echo_idx = cWave/3.5;	
	else if(FREQ == MnMS1_FREQ_160K)
		lAdc.echo_idx = cWave/2.1;
	else if(FREQ == MnMS1_FREQ_130K)
		lAdc.echo_idx = cWave/1.7;

	lAdc.echo_idx_max = lAdc.echo_idx;
	
	MsSEN_TxSona(cWave,ch);
	DAC_OutpVolt(0);


	while(lAdc.echo_idx < ADC_BUFF_MAX);
	HAL_TIM_Base_Stop_IT(&htim6);

	DAC_OutpVolt(0);
	HAL_DAC_Stop(&hdac,DAC_CHANNEL_1);


}

void ADC_ProcEcho_FieldA(U08 ch)
{

	U16 cWave  = 20;


	lAdc.chnl_idx =ch;
	lAdc.filed_sel = 1;

	lAdc.echo_idx = cWave/2.1;

	lAdc.echo_idx_max = lAdc.echo_idx+1;


	MsSEN_TxSona(cWave,ch);
	DAC_OutpVolt(0);


	while(lAdc.echo_idx < ADC_BUFF_MAX);
	HAL_TIM_Base_Stop_IT(&htim6);

	DAC_OutpVolt(0);
	HAL_DAC_Stop(&hdac,DAC_CHANNEL_1);


}

//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

