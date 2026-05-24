/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app_sys.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim14;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USART1_TX_EN_Pin GPIO_PIN_3
#define USART1_TX_EN_GPIO_Port GPIOE
#define LED_OPR2_Pin GPIO_PIN_8
#define LED_OPR2_GPIO_Port GPIOI
#define SPI5_SCK_Pin GPIO_PIN_7
#define SPI5_SCK_GPIO_Port GPIOF
#define SPI5_MISO_Pin GPIO_PIN_8
#define SPI5_MISO_GPIO_Port GPIOF
#define SPI5_MOSI_Pin GPIO_PIN_9
#define SPI5_MOSI_GPIO_Port GPIOF
#define BT_BTI_MO_Pin GPIO_PIN_1
#define BT_BTI_MO_GPIO_Port GPIOC
#define BT_BTO_MI_Pin GPIO_PIN_2
#define BT_BTO_MI_GPIO_Port GPIOC
#define CS_MRAM_Pin GPIO_PIN_3
#define CS_MRAM_GPIO_Port GPIOC
#define PA3_TM2_TX_CLK_Pin GPIO_PIN_3
#define PA3_TM2_TX_CLK_GPIO_Port GPIOA
#define TX_CLK_EN1_Pin GPIO_PIN_4
#define TX_CLK_EN1_GPIO_Port GPIOC
#define TX_CLK_EN2_Pin GPIO_PIN_5
#define TX_CLK_EN2_GPIO_Port GPIOC
#define USART3_TX_EN_Pin GPIO_PIN_12
#define USART3_TX_EN_GPIO_Port GPIOB
#define ADC_DIN_Pin GPIO_PIN_11
#define ADC_DIN_GPIO_Port GPIOC
#define ADC_CONVST_Pin GPIO_PIN_12
#define ADC_CONVST_GPIO_Port GPIOC
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB
#define LED_OPR1_Pin GPIO_PIN_7
#define LED_OPR1_GPIO_Port GPIOI
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
