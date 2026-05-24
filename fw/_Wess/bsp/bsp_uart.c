//--------------------------------------------------------------------------------------------------
//  Copyright (C) 2022, WESS-Global Inc., All Rights Reserved.
//
//  The information contained herein is confidential property of WESS-Global Inc. The use,
//  copying, transfer or disclosure of such information is prohibited except by express written
//  agreement with WESS-Global Co.,LTD
//
//  $Date: 2022-05-26 12:00:00 +0900 $
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
//  Includes
//--------------------------------------------------------------------------------------------------
// Standard
#include <string.h>
// Core
#include "usart.h"
// self
#include "bsp_uart.h"
#include "bsp_gpio.h"
#include "bsp_demux.h"
// menu
#include "menu_data.h"
// data
#include "data_commu.h"

#include "stm32f7xx_hal_uart.h"

#include "main.h"
//--------------------------------------------------------------------------------------------------
//  Global variables
//--------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------
//  Local variables
//--------------------------------------------------------------------------------------------------
URT_LS lUrt;

//--------------------------------------------------------------------------------------------------
//  Local Funtions
//--------------------------------------------------------------------------------------------------
void UrtPrc_Wr485(U08* args, U08 arg_size)
{   
  HAL_GPIO_WritePin(USART3_TX_EN_GPIO_Port, USART3_TX_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart3,(U08*) args, arg_size, 1000); 
	HAL_GPIO_WritePin(USART3_TX_EN_GPIO_Port, USART3_TX_EN_Pin, GPIO_PIN_RESET);
}

void UrtPrc_Wr232(U08* args, U08 arg_size)
{
  /* URT_IDX_1 → BLE BoT-nLE521 (USART2). 기존 huart1(RS232 디버그)은 더이상 사용 안 함 */
  HAL_UART_Transmit(&huart2, (U08*) args, arg_size, 1000);
}


void UrtPrc_WrRF(U08* args, U08 arg_size)
{
	//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart6,(U08*) args, arg_size, 1000); 
	//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
}

//--------------------------------------------------------------------------------------------------
//  Global APIs
//--------------------------------------------------------------------------------------------------
#if 0
U08 URT_GetBuf_cnt(URT_IDX idx)					{	return lUrt.rx_param[idx].buf_cnt; }
U08 URT_GetBuf(URT_IDX idx, U08 buf_idx)		{	return lUrt.rx_param[idx].buf[buf_idx]; }
U08* URT_GetAddr(URT_IDX idx)					{    return lUrt.rx_param[idx].buf;				}
#endif


void URT_InitMain(U08 idx, U32 br)
{
	UART_HandleTypeDef *huart;

	HAL_GPIO_WritePin(USART3_TX_EN_GPIO_Port, USART3_TX_EN_Pin, GPIO_PIN_RESET);

	switch(idx)
	{
		case URT_IDX_1:		huart = &huart2;	huart->Init.BaudRate = br;		break;  /* BLE BoT-nLE521: baudrate 가변 (9600/115200) */
		case URT_IDX_2:		huart = &huart3;	huart->Init.BaudRate = br;		break;
		case URT_IDX_RF:	huart = &huart6;	huart->Init.BaudRate = 9600;	DMX_SetIo(DMX_OUT_RF_RESETIN, GIO_LV_HI);	break;
		default:
			break;
	}

    if(HAL_UART_Init(huart) != HAL_OK)
        Error_Handler();

	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);  /* BLE BoT-nLE521 RX */
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
}

void URT_TxPkt(U08 idx, U08* args, U08 size)
{
	__HAL_UART_DISABLE_IT(&huart2, UART_IT_RXNE);
	__HAL_UART_DISABLE_IT(&huart3, UART_IT_RXNE);
	switch(idx)
	{
		case URT_IDX_1:		UrtPrc_Wr232(args, size);	break;
		case URT_IDX_2:		UrtPrc_Wr485(args, size);	break;
		case URT_IDX_RF:	UrtPrc_WrRF(args,size);		break;
		default:										break;

	}
	//HAL_Delay(5);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
}

#if 0
void UrtCfg_SetRxBuff(URT_IDX idx, U08 dr)
{
    if(lUrt.rx_param[idx].buf_cnt >= MDB_RX_BUF_SIZE)
        lUrt.rx_param[idx].buf_cnt = 0;
	
    lUrt.rx_param[idx].buf[lUrt.rx_param[idx].buf_cnt] = dr;
    lUrt.rx_param[idx].buf_cnt++;
}
#endif 

void _ISR_URT_Callback(URT_IDX idx, U08 rdr)
{
	/* URT_IDX_1 (huart2) = BLE BoT-nLE521 — 항상 BLE 파서로 라우팅 */
	if(idx == URT_IDX_1)
	{
		DaBT_SetRxBuff(idx, rdr);
		return;
	}

	/* URT_IDX_2 (huart3) = RS485 Modbus */
	if(MnDAT_ComPrGet_Value(MnDS1_OPT_TYPE)!=MnDS1_TYPE_MDB)		return;
	DaMdb_SetRxBuff(idx, rdr);
}







