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
// lib
#include "app_sys.h"
// self
#include "bsp_spi.h"


//------------------------------------------------------------------------------------------------------------------------------
//  Global variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local variables
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Local Funtions
//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Access Local Variables
//------------------------------------------------------------------------------------------------------------------------------
// Get
// Set


//------------------------------------------------------------------------------------------------------------------------------
//  Global APIs - Operation
//------------------------------------------------------------------------------------------------------------------------------
void SPI_SetMram(void) // max. SCLK : 40 MHz
{
	HAL_SPI_DeInit(&hspi5);

	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi5.Init.CRCPolynomial = 7;
	hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi5.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

	if(HAL_SPI_Init(&hspi5) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_SPI_ENABLE(&hspi5);
}

void SPI_SetCurrent(void) // max. SCLK : 30.3 MHz
{
	HAL_SPI_DeInit(&hspi5);
	
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	#if 1
	hspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
	#else
	hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;
	#endif
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi5.Init.CRCPolynomial = 7;
	hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi5.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

	if(HAL_SPI_Init(&hspi5) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_SPI_ENABLE(&hspi5);
}

void SPI_SetExtAdc(void) // max. SCLK : 66.6 MHz
{
	HAL_SPI_DeInit(&hspi5);
	
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_16BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi5.Init.CRCPolynomial = 7;
	hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi5.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

	if(HAL_SPI_Init(&hspi5) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_SPI_ENABLE(&hspi5);
}

void SPI_CfgMode(U08 mode)
{
	U08 cpol, cpha;
	
	switch(mode)
	{
		case SPI_MODE0_DEFAULT:		cpol = SPI_POLARITY_LOW;	cpha = SPI_PHASE_1EDGE;		break;
		case SPI_MODE1_FALLING2:	cpol = SPI_POLARITY_LOW;	cpha = SPI_PHASE_2EDGE;		break;
		case SPI_MODE2_FALLING1:	cpol = SPI_POLARITY_HIGH;	cpha = SPI_PHASE_1EDGE;		break;	
		case SPI_MODE3_RISING2:		cpol = SPI_POLARITY_HIGH;	cpha = SPI_PHASE_2EDGE;		break;
		default:					break;
	}

	hspi5.Init.CLKPolarity 	= (U32)cpol;
	hspi5.Init.CLKPhase 	= (U32)cpha;

	if (HAL_SPI_Init(&hspi5) != HAL_OK)
	{
		Error_Handler();
	}    
}

void SPI_WrSize(U08* data, U08 len)
{
    HAL_SPI_Transmit(&hspi5, data, len, 5000);
}

void SPI_WrCmd(U08 cmd)
{
	U08 wr_data[2];
	
	wr_data[0] = (U08) ((cmd >> 4) & 0xF);
	wr_data[1] = (U08) (cmd & 0xF);
	HAL_SPI_Transmit(&hspi5, (U08*) wr_data, 2, 5000);

	while (HAL_SPI_GetState(&hspi5) != HAL_SPI_STATE_READY);
}

void SPI_WrAddr(unsigned long addr)
{
	U08 wr_data[2];
	U08 addr_0_UC_L, addr_1_UC_L, addr_2_UC_L, addr_3_UC_L, addr_4_UC_L, addr_5_UC_L;

	addr_0_UC_L = (U08) ((addr >> 20) & 0xF);
	addr_1_UC_L = (U08) ((addr >> 16) & 0xF);
	addr_2_UC_L = (U08) ((addr >> 12) & 0xF);
	addr_3_UC_L = (U08) ((addr >> 8) & 0xF);
	addr_4_UC_L = (U08) ((addr >> 4) & 0xF);
	addr_5_UC_L = (U08) (addr & 0xF);

	// address
	wr_data[0] = addr_0_UC_L;
	wr_data[1] = addr_1_UC_L;
	HAL_SPI_Transmit(&hspi5, wr_data, 2, 5000);

	wr_data[0] = addr_2_UC_L;
	wr_data[1] = addr_3_UC_L;
	HAL_SPI_Transmit(&hspi5, wr_data, 2, 5000);

	wr_data[0] = addr_4_UC_L;
	wr_data[1] = addr_5_UC_L;
	HAL_SPI_Transmit(&hspi5, wr_data, 2, 5000);

	while (HAL_SPI_GetState(&hspi5) != HAL_SPI_STATE_READY);
}

U08 SPI_RdByte(void)
{
	U08 rtn_val;
	
	HAL_SPI_Receive(&hspi5, &rtn_val, 1, 100);
#if 0	
	while((SPI5->SR & SPI_FLAG_TXE) == 0);
	SPI5->DR = 0x00;
	
	while((SPI5->SR & SPI_FLAG_RXNE) == 0);
	rtn_val=SPI5->DR;
#endif
	return rtn_val;
}

void SPI_InitMain(void)
{
    //__HAL_SPI_ENABLE(&hspi5);
}


//------------------------------------------------------------------------------------------------------------------------------
//  EOF
//------------------------------------------------------------------------------------------------------------------------------

