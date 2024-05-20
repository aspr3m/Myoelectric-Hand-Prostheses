/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MD2_BIN2_Pin GPIO_PIN_14
#define MD2_BIN2_GPIO_Port GPIOC
#define MYO_1_Pin GPIO_PIN_0
#define MYO_1_GPIO_Port GPIOC
#define V_BAT_ADC_Pin GPIO_PIN_1
#define V_BAT_ADC_GPIO_Port GPIOC
#define CM1_Pin GPIO_PIN_2
#define CM1_GPIO_Port GPIOC
#define CM2_Pin GPIO_PIN_3
#define CM2_GPIO_Port GPIOC
#define M4_Encoder_B_Pin GPIO_PIN_0
#define M4_Encoder_B_GPIO_Port GPIOA
#define M4_Encoder_B_EXTI_IRQn EXTI0_IRQn
#define M1_Encoder_A_Pin GPIO_PIN_1
#define M1_Encoder_A_GPIO_Port GPIOA
#define M1_Encoder_A_EXTI_IRQn EXTI1_IRQn
#define MYO_3_Pin GPIO_PIN_2
#define MYO_3_GPIO_Port GPIOA
#define M2_Encoder_A_Pin GPIO_PIN_3
#define M2_Encoder_A_GPIO_Port GPIOA
#define M2_Encoder_A_EXTI_IRQn EXTI3_IRQn
#define M2_Encoder_B_Pin GPIO_PIN_4
#define M2_Encoder_B_GPIO_Port GPIOA
#define M2_Encoder_B_EXTI_IRQn EXTI4_IRQn
#define M3_Encoder_A_Pin GPIO_PIN_5
#define M3_Encoder_A_GPIO_Port GPIOA
#define M3_Encoder_A_EXTI_IRQn EXTI9_5_IRQn
#define CM5_Pin GPIO_PIN_6
#define CM5_GPIO_Port GPIOA
#define MYO_2_Pin GPIO_PIN_7
#define MYO_2_GPIO_Port GPIOA
#define CM3_Pin GPIO_PIN_4
#define CM3_GPIO_Port GPIOC
#define CM4_Pin GPIO_PIN_5
#define CM4_GPIO_Port GPIOC
#define MD3_AIN1_Pin GPIO_PIN_0
#define MD3_AIN1_GPIO_Port GPIOB
#define M1_Encoder_B_Pin GPIO_PIN_2
#define M1_Encoder_B_GPIO_Port GPIOB
#define M1_Encoder_B_EXTI_IRQn EXTI2_IRQn
#define M4_Encoder_A_Pin GPIO_PIN_10
#define M4_Encoder_A_GPIO_Port GPIOB
#define M4_Encoder_A_EXTI_IRQn EXTI15_10_IRQn
#define M5_Encoder_A_Pin GPIO_PIN_11
#define M5_Encoder_A_GPIO_Port GPIOB
#define M5_Encoder_A_EXTI_IRQn EXTI15_10_IRQn
#define M5_Encoder_B_Pin GPIO_PIN_12
#define M5_Encoder_B_GPIO_Port GPIOB
#define M5_Encoder_B_EXTI_IRQn EXTI15_10_IRQn
#define M6_Encoder_A_Pin GPIO_PIN_13
#define M6_Encoder_A_GPIO_Port GPIOB
#define M6_Encoder_A_EXTI_IRQn EXTI15_10_IRQn
#define M6_Encoder_B_Pin GPIO_PIN_14
#define M6_Encoder_B_GPIO_Port GPIOB
#define M6_Encoder_B_EXTI_IRQn EXTI15_10_IRQn
#define BTN_1_Pin GPIO_PIN_15
#define BTN_1_GPIO_Port GPIOB
#define BTN_1_EXTI_IRQn EXTI15_10_IRQn
#define M3_Encoder_B_Pin GPIO_PIN_9
#define M3_Encoder_B_GPIO_Port GPIOC
#define M3_Encoder_B_EXTI_IRQn EXTI9_5_IRQn
#define MD1_AIN1_Pin GPIO_PIN_12
#define MD1_AIN1_GPIO_Port GPIOA
#define MD1_AIN2_Pin GPIO_PIN_15
#define MD1_AIN2_GPIO_Port GPIOA
#define MD3_AIN2_Pin GPIO_PIN_10
#define MD3_AIN2_GPIO_Port GPIOC
#define MD3_BIN1_Pin GPIO_PIN_11
#define MD3_BIN1_GPIO_Port GPIOC
#define MD3_BIN2_Pin GPIO_PIN_12
#define MD3_BIN2_GPIO_Port GPIOC
#define RGBIC_Pin GPIO_PIN_2
#define RGBIC_GPIO_Port GPIOD
#define MD1_BIN1_Pin GPIO_PIN_3
#define MD1_BIN1_GPIO_Port GPIOB
#define MD1_BIN2_Pin GPIO_PIN_4
#define MD1_BIN2_GPIO_Port GPIOB
#define MD2_AIN1_Pin GPIO_PIN_5
#define MD2_AIN1_GPIO_Port GPIOB
#define MD2_AIN2_Pin GPIO_PIN_6
#define MD2_AIN2_GPIO_Port GPIOB
#define MD2_BIN1_Pin GPIO_PIN_7
#define MD2_BIN1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
