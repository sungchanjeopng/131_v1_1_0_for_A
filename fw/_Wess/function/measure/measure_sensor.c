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
// screen
#include "screen_echo.h"
#include "screen_calib.h"
#include "screen_main.h"
#include "screen_eco1_list.h"
#include "screen_eco2_value.h"
// menu
#include "menu_measure.h"
#include "menu_engineer.h"
#include "menu_test.h"
// self
#include "measure_sensor.h"


#include "tim.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------
U08 cnt_TX_CLK;

//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------
MsSEN_LS lMsSen;


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
U08 MsSEN_PrGet_Sel_ch(void)	{	return	lMsSen.ch;	}
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void MsSEN_Cfg_FREQ(U08 val)
{
	#if 1
	U16 psc, per, pulse;

	switch(val)
	{
		case MnMS1_FREQ_130K:	psc = 1;	per = 1537/2;		pulse = 768/2;	break;
		case MnMS1_FREQ_160K:	psc = 1;	per = 1250/2;		pulse = 625/2;	break;
		case MnMS1_FREQ_270K:	psc = 1;	per = 740/2;		pulse = 370/2;	break;
		case MnMS1_FREQ_380K:	psc = 1;	per = 526/2;		pulse = 263/2; 	break;
		default:				psc = 1;	per = 526/2;		pulse = 263/2; 	break;
		// 130k : 0, 1537
		// 270k : 0, 740
	}
	/* USER CODE BEGIN TIM2_Init 0 */
	
	/* USER CODE END TIM2_Init 0 */
	
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	
	/* USER CODE BEGIN TIM2_Init 1 */
	
	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = psc-1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = per-1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
	  Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
	{
	  Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulse;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
	  Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */
	
	/* USER CODE END TIM2_Init 2 */
	HAL_TIM_MspPostInit(&htim2);
	#else
	U08 num;

	switch(val)
	{
		case ScCLB_FREQ_160K:		num = 17;		break;
		case ScCLB_FREQ_380K:		num = 7;		break;
		default:					num = 7;		break;
	}
	/* USER CODE BEGIN TIM1_Init 0 */
	
	/* USER CODE END TIM1_Init 0 */
	
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
	
	/* USER CODE BEGIN TIM1_Init 1 */
	
	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = num-1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 74-1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
	  Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
	  Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 37;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
	  Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.BreakFilter = 0;
	sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
	sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
	sBreakDeadTimeConfig.Break2Filter = 0;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */
	
	/* USER CODE END TIM1_Init 2 */
	HAL_TIM_MspPostInit(&htim1);	
#endif
}

void MsSEN_InitVari(void)
{
	lMsSen.freq = ScCLB_FREQ_380K;
	lMsSen.ch = APP_CH_1;
	lMsSen.amp = ScCLB_RX_AMP_x100;

	MsGAN_CfgRx(ScCLB_RX_AMP_x100, lMsSen.ch);
	
	MsSEN_Cfg_FREQ(lMsSen.freq);
	DMX_SetIo(DMX_OUT_SEL_CH, lMsSen.ch);
	DMX_SetIo(DMX_OUT_RX_Con_1, MsSEN_Filiter_380);	// DMX_OUT_RX_Con_1 : DMX_OUT_SEL_FREQ

}

void MsSEN_TxSona(U08 cnt, U08 ch)
{
	cnt_TX_CLK = 0;

	U64 val1;
	
	if(ch == MsSEN_C0_CH1)
	{
		val1 = 0x00000010;
		//val2 = 0x00100000;
	}
	else if (ch == MsSEN_C1_CH2)
	{
		val1 = 0x00000020;
		//val2 = 0x00200000;
	}


//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	
	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
	__HAL_TIM_DISABLE(&htim2);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	TIM2->EGR = TIM_EGR_UG; 							 
	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

 	GPIOC->BSRR = val1;
//	HAL_TIM_Base_Start_IT(&htim8);
	HAL_TIM_Base_Start_IT(&htim3);



	while(cnt_TX_CLK < cnt);
	//		set Low 	   /	 set High 
	// 0000 0000 0001 0000	0000 0000 0000 0000
	// PC4 Low

	//		set Low 	   /	 set High 
	// 0000 0000 0010 0000	0000 0000 0000 0000
	// PC5 Low

#if 0
	GPIOC->BSRR = val2;	
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
#endif
//	HAL_TIM_Base_Stop_IT(&htim8);
	HAL_TIM_Base_Stop_IT(&htim3);

	HAL_TIM_Base_Start_IT(&htim6);
}


void MsSEN_Sel_CH(U08 ch)
{
	if(lMsSen.ch == ch) return;

	DMX_SetIo(DMX_OUT_SEL_CH, ch);
	lMsSen.ch  = ch;
}

void MsSEN_FieldProcMain(U08 ch)
{
	U08 amp    = MnTST_PrGet_Value(MnTST_OPT_HW_RX_AMP);
	U08 FREQ   = MnMS1_FREQ_160K;

	//ADC_ProcTprt();

	DAC_filedValue(ch);

	ISR_SetIrqDa();

	TMR_HalEnable(_F_F, _F_F);

	if(lMsSen.freq!=FREQ)
	{
		MsSEN_Cfg_FREQ(FREQ);
		#if 0
		switch(FREQ)
		{
			case MnMS1_FREQ_380K:
			case MnMS1_FREQ_270K:
				DMX_SetIo(DMX_OUT_SEL_FREQ, MsSEN_Filiter_380);
				break;
			case MnMS1_FREQ_160K:
			case MnMS1_FREQ_130K:
				DMX_SetIo(DMX_OUT_SEL_FREQ, MsSEN_Filiter_160);
				break;
		}
		#endif
		lMsSen.freq=FREQ;
	}

	if(lMsSen.amp!=amp)
	{
		MsGAN_CfgRx(amp, ch);
		lMsSen.amp = amp;
	}


	MsSEN_Sel_CH(ch);

	
	ISR_SetIrqEn();

	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	ADC_ProcEcho_FieldA(ch);
	HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);

}



void MsSEN_FREQ(U08 ch)
{
	U08 FREQ   = MnMSR_CalGet_Ch_Value(ch, MnMS1_OPT_SINGLE_FREQ);

	if(ScECH_GetLayer() == SCRN_L2_VALU)
	{
		if(ScECH_GetType()==ScECO_TYPE_REAL)
		{
			if(ScEC1_GetIdxFunc()==ScECO_REAL_FREQ)
				FREQ = ScEC2_GetValue();
		}
	}


	if(lMsSen.freq!=FREQ)
	{
		MsSEN_Cfg_FREQ(FREQ);

		switch(FREQ)
		{
			case MnMS1_FREQ_380K:
			case MnMS1_FREQ_270K:
				DMX_SetIo(DMX_OUT_RX_Con_1, MsSEN_Filiter_380);	// DMX_OUT_RX_Con_1 : DMX_OUT_SEL_FREQ
				break;
			case MnMS1_FREQ_160K:
			case MnMS1_FREQ_130K:
				DMX_SetIo(DMX_OUT_RX_Con_1, MsSEN_Filiter_160);	// DMX_OUT_RX_Con_1 : DMX_OUT_SEL_FREQ
				break;
		}

		lMsSen.freq=FREQ;
	}



}

void MsSEN_ProcMain(U08 ch)
{
	U08 amp    = MnTST_PrGet_Value(MnTST_OPT_HW_RX_AMP);

	ADC_ProcTprt();

	DAC_ProcValue(ch);

	ISR_SetIrqDa();

	TMR_HalEnable(_F_F, _F_F);

	MsSEN_FREQ(ch);

	if(lMsSen.amp!=amp)
	{
		MsGAN_CfgRx(amp, ch);
		lMsSen.amp = amp;
	}


	MsSEN_Sel_CH(ch);

	
	ISR_SetIrqEn();

	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	ADC_ProcEcho(ch);
	HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);

}




//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

