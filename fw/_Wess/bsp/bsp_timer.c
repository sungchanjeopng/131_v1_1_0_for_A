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
#include "bsp_timer.h"
#include "app_main.h"
#include "menu_test.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------
TMR_GS gTmr;


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------
void TmrInit_Vari(void)
{
	gTmr.f.b.f001ms = FALSE;
	gTmr.f.b.f010ms = FALSE;
	gTmr.f.b.f050ms = FALSE;
	gTmr.f.b.f100ms = FALSE;
	gTmr.f.b.f500ms = FALSE;
	gTmr.f.b.f01sec = FALSE;
	
	gTmr.c.c001ms = 0;
	gTmr.c.c010ms = 0;
	gTmr.c.c050ms = 0;
	gTmr.c.c100ms = 0;
	gTmr.c.c100ms_01sec = 0;
	gTmr.c.c500ms = 0;
	gTmr.c.c01sec = 0;

	gTmr.c.timer1[APP_CH_1] = 0;
	gTmr.c.timer1[APP_CH_2] = 0;
}


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void TMR_InitMain(void)
{
	TmrInit_Vari();

	// Interrupt Enable
#if 0
	__HAL_TIM_CLEAR_FLAG (&htim6, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim6, 0);
	HAL_TIM_Base_Start_IT(&htim6);
#endif
	HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
#if 0

	__HAL_TIM_CLEAR_FLAG (&htim2, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	HAL_TIM_Base_Start_IT(&htim2);
#endif
	__HAL_TIM_CLEAR_FLAG (&htim3, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	HAL_TIM_Base_Start_IT(&htim3);

	__HAL_TIM_CLEAR_FLAG (&htim4, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_Base_Start_IT(&htim4);
	
	__HAL_TIM_CLEAR_FLAG (&htim5, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim5, 0);
	HAL_TIM_Base_Start_IT(&htim5);
	
	__HAL_TIM_CLEAR_FLAG (&htim7, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim7, 0);
	HAL_TIM_Base_Start_IT(&htim7);
	
	__HAL_TIM_CLEAR_FLAG (&htim14, TIM_FLAG_UPDATE);
	__HAL_TIM_SET_COUNTER(&htim14, 0);
	HAL_TIM_Base_Start_IT(&htim14);
}

void TMR_HalEnable(U08 fEn, U08 fClr)
{
	if(fEn)
	{
		if(fClr)
			TmrInit_Vari();

		//HAL_NVIC_EnableIRQ(TIM2_IRQn);
		//HAL_NVIC_EnableIRQ(TIM3_IRQn);
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
		HAL_NVIC_EnableIRQ(TIM5_IRQn);
		HAL_NVIC_EnableIRQ(TIM7_IRQn);
		HAL_NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn);
	}
	else
	{
		//HAL_NVIC_DisableIRQ(TIM2_IRQn);
		//HAL_NVIC_DisableIRQ(TIM3_IRQn);
		HAL_NVIC_DisableIRQ(TIM4_IRQn);
		HAL_NVIC_DisableIRQ(TIM5_IRQn);
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
		HAL_NVIC_DisableIRQ(TIM8_TRG_COM_TIM14_IRQn);
	}
}

//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - HAL Driver
//------------------------------------------------------------------------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	U08 cnt;


//	if(htim->Instance == TIM2)		gTmr.f.b.f001ms = TRUE;
//	if(htim->Instance == TIM3)		gTmr.f.b.f010ms = TRUE;
	if(htim->Instance == TIM4)		gTmr.f.b.f050ms = TRUE;
	if(htim->Instance == TIM5)		
	{
		gTmr.f.b.f100ms = TRUE;
		if(++gTmr.c.c100ms_01sec>=10)
		{
			gTmr.f.b.f100ms_01sec = TRUE;
			gTmr.c.c100ms_01sec = 0;
		}
	}
	if(htim->Instance == TIM7)		gTmr.f.b.f500ms = TRUE;
	if(htim->Instance == TIM14)		gTmr.f.b.f01sec = TRUE;


	if(htim->Instance == TIM3)		
	{	
		cnt_TX_CLK += 2;
	
		if(ADC_Get_FieldSel())
			cnt = 20;
		else
			cnt = MnTST_PrGet_CH_Value(MsSEN_PrGet_Sel_ch(),MnTST_OPT_SINGLE_PULSE_NO);
		if(cnt_TX_CLK >=cnt)
		{
			GPIOC->BSRR = (MsSEN_PrGet_Sel_ch()+1)*(0x00100000);	
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
		}
	}

}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

