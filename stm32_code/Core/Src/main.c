/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//Includes for OLED screen
#include "fonts.h"
#include "ssd1306.h"
#include <stdio.h>
#include <string.h>

// Includes for switchcase
#include "stm32f4xx_hal.h"

// Includes for ENCODER
#include <stdbool.h>
#include <stdint.h>

// PID
#include <math.h>

/*
// Includes for ML
#include <stdio.h>
#include "ai_datatypes_defines.h"
#include "ai_platform.h"
#include "cnnmodel.h"
#include "cnnmodel_data.h"
#include "stm32f4xx_hal_tim.h"
*/

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

// Enum to define gesture types
typedef enum {
    GESTURE_REST,
    GESTURE_THUMB_UP,
    GESTURE_FIST,
    GESTURE_POINTING,
    GESTURE_TRIPOD,
    GESTURE_PINCH
} Gesture_t;

//Function for main switch case
void ControlMotors(Gesture_t gesture);
Gesture_t getNextGesture(Gesture_t currentGesture);
Gesture_t readButtonAndDetermineGesture(void);

// Explicitly set to REST position at startup
Gesture_t lastGesture = GESTURE_REST; // Keep track of the last non-REST gesture
Gesture_t currentGesture = GESTURE_REST; // Current gesture state

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

// PID variables

	//PID M1
	volatile int lastA_M1 = 0;
	volatile int lastB_M1 = 0;
	volatile int32_t encoder_count_M1 = 0;
	volatile int32_t target_position_M1 = 0;
	float Kp_M1 = 1.0, Ki_M1 = 0.1, Kd_M1 = 0.01;
	float integral_M1 = 0, previous_error_M1 = 0;
	// END M1 variable
	char END_msg_M1[10];
	//PID M2
	volatile int lastA_M2 = 0;
	volatile int lastB_M2 = 0;
	volatile int32_t encoder_count_M2 = 0;
	volatile int32_t target_position_M2 = 0;
	float Kp_M2 = 1.0, Ki_M2 = 0.1, Kd_M2 = 0.01;
	float integral_M2 = 0, previous_error_M2 = 0;
	// END M2 variable
	char END_msg_M2[10];

	//PID M3
	volatile int lastA_M3 = 0;
	volatile int lastB_M3 = 0;
	volatile int32_t encoder_count_M3 = 0;
	volatile int32_t target_position_M3 = 0;
	float Kp_M3 = 1.0, Ki_M3 = 0.1, Kd_M3 = 0.01;
	float integral_M3 = 0, previous_error_M3 = 0;
	// END M3 variable
	char END_msg_M3[10];

	//PID M4
	volatile int lastA_M4 = 0;
	volatile int lastB_M4 = 0;
	volatile int32_t encoder_count_M4 = 0;
	volatile int32_t target_position_M4 = 0;
	float Kp_M4 = 1.0, Ki_M4 = 0.1, Kd_M4 = 0.01;
	float integral_M4 = 0, previous_error_M4 = 0;
	// END M4 variable
	char END_msg_M4[10];

	//PID M5
	volatile int lastA_M5 = 0;
	volatile int lastB_M5 = 0;
	volatile int32_t encoder_count_M5 = 0;
	volatile int32_t target_position_M5 = 0;
	float Kp_M5 = 1.0, Ki_M5 = 0.1, Kd_M5 = 0.01;
	float integral_M5 = 0, previous_error_M5 = 0;
	// END M2 variable
	char END_msg_M5[10];

	//PID M6
	volatile int lastA_M6 = 0;
	volatile int lastB_M6 = 0;
	volatile int32_t encoder_count_M6 = 0;
	volatile int32_t target_position_M6 = 0;
	float Kp_M6 = 1.0, Ki_M6 = 0.1, Kd_M6 = 0.01;
	float integral_M6 = 0, previous_error_M6 = 0;
	// END M6 variable
	char END_msg_M6[10];

// VBAT variables
	uint16_t V_BAT_raw;
	char V_BAT_msg[20];
	float V_in;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Forward declarations of the interrupt handlers
void HAL_GPIO_EXTI_Callback_M1(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback_M2(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback_M3(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback_M4(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback_M5(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback_M6(uint16_t GPIO_Pin);



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

	//CM1 variables test
	// Declarations
	uint32_t raw_CM1;
	float V_in_CM1;
	float current_A_CM1;
	float current_mA_CM1;
	char msg_CM1[30];
	char raw_msg_CM1[30];
	// Constants for CM1
	const float V_zero_CM1 = 1.607;  // Zero-current voltage in V (for ACS712)
	const float sensitivity_CM1 = 0.185;  // Sensitivity in V/A (for ACS712)


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_TIM14_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  /* USER CODE BEGIN 2 */

  // Start PWMs for all motors
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4); // Start PWM on PB1, PWM_M1
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // Start PWM on PC6, PWM_M2
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // Start PWM on PC7, PWM_M3
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); // Start PWM on PC8, PWM_M4
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // Start PWM on PA8, PWM_M5
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4); // Start PWM on PA11, PWM_M6

  // Start encoder interface
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_4);


  // OLED SCREEN
  SSD1306_Init();
  SSD1306_GotoXY (0,0);
  SSD1306_Puts ("Myoelectric", &Font_11x18, 1);
  SSD1306_GotoXY (0, 30);
  SSD1306_Puts ("Prosthesis", &Font_11x18, 1);
  SSD1306_UpdateScreen();
  HAL_Delay (1500);
  SSD1306_Clear();

  ControlMotors(currentGesture); // Ensure motors start in the REST position

   //ENCODER TEST Variables
   // Read initial states for encoders
   	   //Encoder for M1
   	   lastA_M1 = HAL_GPIO_ReadPin(GPIOA, M1_Encoder_A_Pin);
       lastB_M1 = HAL_GPIO_ReadPin(GPIOB, M1_Encoder_B_Pin);
       //Encoder for M2
       lastA_M2 = HAL_GPIO_ReadPin(GPIOA, M2_Encoder_A_Pin);
       lastB_M2 = HAL_GPIO_ReadPin(GPIOB, M2_Encoder_B_Pin);
   	   //Encoder for M3
   	   lastA_M3 = HAL_GPIO_ReadPin(GPIOA, M3_Encoder_A_Pin);
       lastB_M3 = HAL_GPIO_ReadPin(GPIOB, M3_Encoder_B_Pin);
   	   //Encoder for M4
   	   lastA_M4 = HAL_GPIO_ReadPin(GPIOA, M4_Encoder_A_Pin);
       lastB_M4 = HAL_GPIO_ReadPin(GPIOB, M4_Encoder_B_Pin);
   	   //Encoder for M5
   	   lastA_M5 = HAL_GPIO_ReadPin(GPIOA, M5_Encoder_A_Pin);
       lastB_M5 = HAL_GPIO_ReadPin(GPIOB, M5_Encoder_B_Pin);
   	   //Encoder for M6
   	   lastA_M6 = HAL_GPIO_ReadPin(GPIOA, M6_Encoder_A_Pin);
       lastB_M6 = HAL_GPIO_ReadPin(GPIOB, M6_Encoder_B_Pin);

//MotorPos variable
       int MotorPos = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

// Encoder value for display:
	//M1
	char buffer_PID_M1[10];
	snprintf(buffer_PID_M1, sizeof(buffer_PID_M1), "M1: %lu", encoder_count_M1);
	//M2
	char buffer_PID_M2[10];
	snprintf(buffer_PID_M2, sizeof(buffer_PID_M2), "M2: %lu", encoder_count_M2);
	//M3
	char buffer_PID_M3[10];
	snprintf(buffer_PID_M3, sizeof(buffer_PID_M3), "M3: %lu", encoder_count_M3);
	//M4
	char buffer_PID_M4[10];
	snprintf(buffer_PID_M4, sizeof(buffer_PID_M4), "M4: %lu", encoder_count_M4);
	//M5
	char buffer_PID_M5[10];
	snprintf(buffer_PID_M5, sizeof(buffer_PID_M5), "M5: %lu", encoder_count_M5);
	//M6
	char buffer_PID_M6[10];
	snprintf(buffer_PID_M6, sizeof(buffer_PID_M6), "M6: %lu", encoder_count_M6);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


//PRINT TO OLED
void PrintToScreen(void){
SSD1306_GotoXY(0, 0);
SSD1306_Puts(V_BAT_msg, &Font_11x18, 1);
SSD1306_GotoXY(0, 30);
//SSD1306_Puts(encoder_count_M1, &Font_11x18, 1); //buffer_PID_M1
SSD1306_UpdateScreen();
HAL_Delay(100);  // Consider reducing this delay or adjusting as needed for real-time control
SSD1306_Clear();
}


// Next gesture switch case
Gesture_t getNextGesture(Gesture_t currentGesture) {
    switch (currentGesture) {
        case GESTURE_REST:
            if (lastGesture == GESTURE_PINCH) { // Check what was the last non-REST gesture
                return GESTURE_THUMB_UP; // Start cycle anew after PINCH
            } else {
                // Determine the next gesture based on the last one
                switch (lastGesture) {
                    case GESTURE_THUMB_UP:
                        return GESTURE_FIST;
                    case GESTURE_FIST:
                        return GESTURE_POINTING;
                    case GESTURE_POINTING:
                        return GESTURE_TRIPOD;
                    case GESTURE_TRIPOD:
                        return GESTURE_PINCH;
                    default:
                        return GESTURE_THUMB_UP; // Default to start of sequence if unsure
                }
            }
        default:
            return GESTURE_REST; // Default to REST after any gesture
    }
}


Gesture_t readButtonAndDetermineGesture(void) {
    static uint32_t lastButtonPressTime = 0;
    if (HAL_GPIO_ReadPin(GPIOB, BTN_1_Pin) == GPIO_PIN_SET && HAL_GetTick() - lastButtonPressTime > 200) {
        lastButtonPressTime = HAL_GetTick();
        return getNextGesture(currentGesture); // Update the current gesture
    }
    return currentGesture; // Return the current gesture if no button press is detected
}



// Motor Control Function
void ControlMotors(Gesture_t gesture) {
    switch (gesture) {
        case GESTURE_REST:
            // Code to set motors to rest position
            SetMotorPosition(0, 0, 0); // Thumb motor, M1
            SetMotorPosition(1, 0, 0); // Ring finger motor, M2
            SetMotorPosition(2, 0, 0); // Middle finger motor, M3
            SetMotorPosition(3, 0, 0); // Index finger motor, M4
            SetMotorPosition(4, 0, 0); // Pinky, M5
            SetMotorPosition(5, 0, 0); // Thumb rotation, M6

            //DISPLAY
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Rest", &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            SSD1306_Clear();
            break;

        case GESTURE_THUMB_UP:
            // Code for Thumb Up gesture
            SetMotorPosition(0, 0, 0); // Thumb motor, M1
            SetMotorPosition(1, 1, 5000); // Ring finger motor, M2
            SetMotorPosition(2, 1, 5000); // Middle finger motor, M3
            SetMotorPosition(3, 1, 5000); // Index finger motor, M4
            SetMotorPosition(4, 1, 5000); // Pinky motor, M5
            SetMotorPosition(5, 0, 0); // Thumb rotation, M6

            //DISPLAY
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Thumb up", &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            SSD1306_Clear();
            break;

        case GESTURE_FIST:
            // Code for Fist gesture
            SetMotorPosition(0, 1, 5000); // Thumb motor, M1
            SetMotorPosition(1, 1, 5000); // Ring finger motor, M2
            SetMotorPosition(2, 1, 5000); // Middle finger motor, M3
            SetMotorPosition(3, 1, 5000); // Index finger motor, M4
            SetMotorPosition(4, 1, 5000); // Pinky motor, M5
            SetMotorPosition(5, 1, 5000); // Thumb rotation, M6

            //DISPLAY
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Fist", &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            SSD1306_Clear();
            break;

        case GESTURE_POINTING:
            // Code for Pointing gesture
            SetMotorPosition(0, 1, 5000); // Thumb motor, M1
            SetMotorPosition(1, 1, 5000); // Ring finger motor, M2
            SetMotorPosition(2, 1, 5000); // Middle finger motor, M3
            SetMotorPosition(3, 0, 0); // Index finger motor, M4
            SetMotorPosition(4, 1, 5000); // Pinky motor, M5
            SetMotorPosition(5, 1, 5000); // Thumb rotation, M6

            //DISPLAY
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Pointing", &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            SSD1306_Clear();
            break;

        case GESTURE_TRIPOD:
            // Code for Tripod gesture
            SetMotorPosition(0, 1, 2500); // Thumb motor, M1
            SetMotorPosition(1, 1, 5000); // Ring finger motor, M2
            SetMotorPosition(2, 1, 2500); // Middle finger motor, M3
            SetMotorPosition(3, 1, 2500); // Index finger motor, M4
            SetMotorPosition(4, 1, 5000); // Pinky motor, M5
            SetMotorPosition(5, 1, 2500); // Thumb rotation, M6

            //DISPLAY
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Tripod", &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            SSD1306_Clear();
            break;

        case GESTURE_PINCH:
            // Code for Pinch gesture
            SetMotorPosition(0, 1, 2500); // Thumb motor, M1
            SetMotorPosition(1, 1, 5000); // Ring finger motor, M2
            SetMotorPosition(2, 1, 5000); // Middle finger motor, M3
            SetMotorPosition(3, 1, 2500); // Index finger motor, M4
            SetMotorPosition(4, 1, 5000); // Pinky motor, M5
            SetMotorPosition(5, 1, 2500); // Thumb rotation, M6

            //DISPLAY
            SSD1306_GotoXY(0, 30);
            SSD1306_Puts("Pinch", &Font_11x18, 1);
            SSD1306_UpdateScreen();
            HAL_Delay(2000);
            SSD1306_Clear();
            break;
    }
}


Gesture_t readGesture(void)
{
    if (HAL_GPIO_ReadPin(GPIOB, BTN_1_Pin) == GPIO_PIN_SET) // Assuming active-high button
    {
        return GESTURE_THUMB_UP;
    }
    return GESTURE_REST; // No gesture detected
}


// MOTOR POSITION FUNCTION (Function to drive the motor to a given direction and position)

void SetMotorPosition(int motorID, int direction, int position) {
	  // Direction 1 is forward and 0 is backward
	      switch (motorID) {
	          case 0:  //THUMB MOTOR 1 = M1
	              if (direction == 1) {  // Forward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);   // MD3_AIN1(PB0) = High
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // MD3_AIN2(PB10) = Low
	              } else {  // Backward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); // MD3_AIN1(PB0) = Low
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);   // MD3_AIN2(PB10) = High
	              }
	            	  updatePID_M1(position);
	              }
	              break;

	          case 1:  // RING FINGER = M2
	              if (direction == 1) {  // Forward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);   // MD1_BIN1(PB3) = High
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET); // MD1_BIN2(PB4) = Low
	              } else {  // Backward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET); // MD1_BIN1(PB3) = Low
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);   // MD1_BIN2(PB4) = High
	              }
	              break;

	          case 2:  // MIDDLE FINGER = M3
	              if (direction == 1) {  // Forward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);   // MD2_AIN1(PB5) = High
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // MD2_AIN2(PB6) = Low
	              } else {  // Backward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // MD2_AIN1(PB5) = Low
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);   // MD2_AIN2(PB6) = High
	              }
	              break;

	          case 3:  // INDEX FINGER = M4
	              if (direction == 1) {  // Forward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);   // MD2_BIN1(PB7) = High
	                  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET); // MD2_BIN2(PC14) = Low
	              } else {  // Backward
	                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); // MD2_BIN1(PB7) = Low
	                  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);   // MD2_BIN2(PC14) = High
	              }
	              break;

	          case 4: //PINKY = M5
	              if (direction == 1) {  // Forward
	                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);   // MD1_AIN1(PA12) = High
	                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET); // MD1_AIN2(PA15) = Low
	              } else {  // Backward
	                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); // MD1_AIN1(PA12) = Low
	                  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);   // MD1_AIN2(PA15) = High
	              }
	              break;

	          case 5:  // THUMB rotation = M6
	              if (direction == 1) {  // Forward
	                  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);   // MD3_BIN1(PC11) = High
	                  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET); // MD3_BIN2(PC12) = Low
	              } else {  // Backward
	                  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET); // MD3_BIN1(PC11) = Low
	                  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);   // MD3_BIN2(PC12) = High
	              }
	              break;
	      }
}
//PID FUNCTIONS
	  // PID Function M1
	  void updatePID_M1(void)
	  {
	      float error_M1 = target_position_M1 - encoder_count_M1;
	      integral_M1 += error_M1 * 0.01;  // Assume update rate is 0.01 seconds for integral calculation
	      float derivative_M1 = (error_M1 - previous_error_M1) / 0.01;
	      float output_M1 = Kp_M1 * error_M1 + Ki_M1 * integral_M1 + Kd_M1 * derivative_M1;

	      previous_error_M1 = error_M1;

	      // Convert PID output to PWM duty cycle
	      if (output_M1 < 0) {
	          HAL_GPIO_WritePin(GPIOA, MD1_AIN1_Pin, GPIO_PIN_SET);
	          HAL_GPIO_WritePin(GPIOA, MD1_AIN2_Pin, GPIO_PIN_RESET);
	          output_M1 = -output_M1;
	      } else {
	          HAL_GPIO_WritePin(GPIOA, MD1_AIN1_Pin, GPIO_PIN_RESET);
	          HAL_GPIO_WritePin(GPIOA, MD1_AIN2_Pin, GPIO_PIN_SET);
	      }

	      output_M1 = fmin(output_M1, 1500); // Limit output to max PWM value
	      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 200);
	  }
	  // PID Function M2
	  void updatePID_M2(void)
	  {
	      float error_M2 = target_position_M2 - encoder_count_M2;
	      integral_M2 += error_M2 * 0.01;  // Assume update rate is 0.01 seconds for integral calculation
	      float derivative_M2 = (error_M2 - previous_error_M2) / 0.01;
	      float output_M2 = Kp_M2 * error_M2 + Ki_M2 * integral_M2 + Kd_M2 * derivative_M2;

	      previous_error_M2 = error_M2;

	      // Convert PID output to PWM duty cycle
	      if (output_M2 < 0) {
	          HAL_GPIO_WritePin(GPIOB, MD1_BIN1_Pin, GPIO_PIN_SET);
	          HAL_GPIO_WritePin(GPIOB, MD1_BIN2_Pin, GPIO_PIN_RESET);
	          output_M2 = -output_M2;
	      } else {
	          HAL_GPIO_WritePin(GPIOB, MD1_BIN1_Pin, GPIO_PIN_RESET);
	          HAL_GPIO_WritePin(GPIOB, MD1_BIN2_Pin, GPIO_PIN_SET);
	      }

	      output_M2 = fmin(output_M2, 1500); // Limit output to max PWM value
	      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, 200);
	  }
	  // PID Function M3
	  void updatePID_M3(void)
	  {
	      float error_M3 = target_position_M3 - encoder_count_M3;
	      integral_M3 += error_M3 * 0.01;  // Assume update rate is 0.01 seconds for integral calculation
	      float derivative_M3 = (error_M3 - previous_error_M3) / 0.01;
	      float output_M3 = Kp_M3 * error_M3 + Ki_M3 * integral_M3 + Kd_M3 * derivative_M3;

	      previous_error_M3 = error_M3;

	      // Convert PID output to PWM duty cycle
	      if (output_M3 < 0) {
	          HAL_GPIO_WritePin(GPIOB, MD2_AIN1_Pin, GPIO_PIN_SET);
	          HAL_GPIO_WritePin(GPIOB, MD2_AIN2_Pin, GPIO_PIN_RESET);
	          output_M3 = -output_M3;
	      } else {
	          HAL_GPIO_WritePin(GPIOB, MD2_AIN1_Pin, GPIO_PIN_RESET);
	          HAL_GPIO_WritePin(GPIOB, MD2_AIN2_Pin, GPIO_PIN_SET);
	      }

	      output_M3 = fmin(output_M3, 1500); // Limit output to max PWM value
	      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 200);
	  }
	  // PID Function M4
	  void updatePID_M4(void)
	  {
	      float error_M4 = target_position_M4 - encoder_count_M4;
	      integral_M4 += error_M4 * 0.01;  // Assume update rate is 0.01 seconds for integral calculation
	      float derivative_M4 = (error_M4 - previous_error_M4) / 0.01;
	      float output_M4 = Kp_M4 * error_M4 + Ki_M4 * integral_M4 + Kd_M4 * derivative_M4;

	      previous_error_M4 = error_M4;

	      // Convert PID output to PWM duty cycle
	      if (output_M4 < 0) {
	          HAL_GPIO_WritePin(GPIOB, MD2_BIN1_Pin, GPIO_PIN_SET);
	          HAL_GPIO_WritePin(GPIOC, MD2_BIN2_Pin, GPIO_PIN_RESET);
	          output_M4 = -output_M4;
	      } else {
	          HAL_GPIO_WritePin(GPIOB, MD2_BIN1_Pin, GPIO_PIN_RESET);
	          HAL_GPIO_WritePin(GPIOC, MD2_BIN2_Pin, GPIO_PIN_SET);
	      }

	      output_M4 = fmin(output_M4, 1500); // Limit output to max PWM value
	      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, 200);
	  }
	  // PID Function M5
	  void updatePID_M5(void)
	  {
	      float error_M5 = target_position_M5 - encoder_count_M5;
	      integral_M5 += error_M5 * 0.01;  // Assume update rate is 0.01 seconds for integral calculation
	      float derivative_M5 = (error_M5 - previous_error_M5) / 0.01;
	      float output_M5 = Kp_M5 * error_M5 + Ki_M5 * integral_M5 + Kd_M5 * derivative_M5;

	      previous_error_M5 = error_M5;

	      // Convert PID output to PWM duty cycle
	      if (output_M5 < 0) {
	          HAL_GPIO_WritePin(GPIOB, MD3_AIN1_Pin, GPIO_PIN_SET);
	          HAL_GPIO_WritePin(GPIOC, MD3_AIN2_Pin, GPIO_PIN_RESET);
	          output_M5 = -output_M5;
	      } else {
	          HAL_GPIO_WritePin(GPIOB, MD3_AIN1_Pin, GPIO_PIN_RESET);
	          HAL_GPIO_WritePin(GPIOC, MD3_AIN2_Pin, GPIO_PIN_SET);
	      }

	      output_M5 = fmin(output_M5, 1500); // Limit output to max PWM value
	      __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, 200);
	  }
	  // PID Function M6
	  void updatePID_M6(void)
	  {
	      float error_M6 = target_position_M6 - encoder_count_M6;
	      integral_M6 += error_M6 * 0.01;  // Assume update rate is 0.01 seconds for integral calculation
	      float derivative_M6 = (error_M6 - previous_error_M6) / 0.01;
	      float output_M6 = Kp_M6 * error_M6 + Ki_M6 * integral_M6 + Kd_M6 * derivative_M6;

	      previous_error_M6 = error_M6;

	      // Convert PID output to PWM duty cycle
	      if (output_M6 < 0) {
	          HAL_GPIO_WritePin(GPIOC, MD3_BIN1_Pin, GPIO_PIN_SET);
	          HAL_GPIO_WritePin(GPIOC, MD3_BIN2_Pin, GPIO_PIN_RESET);
	          output_M6 = -output_M6;
	      } else {
	          HAL_GPIO_WritePin(GPIOC, MD3_BIN1_Pin, GPIO_PIN_RESET);
	          HAL_GPIO_WritePin(GPIOC, MD3_BIN2_Pin, GPIO_PIN_SET);
	      }

	      output_M6 = fmin(output_M6, 1500); // Limit output to max PWM value
	      __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4, 200);
	  }

// ENCODER HANDLER

	  // Interrupt callback handler encoder M1
	  void HAL_GPIO_EXTI_Callback_M1(uint16_t GPIO_Pin) {
	      // Adjust the GPIO pins to the actual ones used for A and B
	      bool currentA_M1 = HAL_GPIO_ReadPin(GPIOA, M1_Encoder_A_Pin);
	      bool currentB_M1 = HAL_GPIO_ReadPin(GPIOB, M1_Encoder_B_Pin);

	      if (GPIO_Pin == M1_Encoder_A_Pin) {
	          if (currentA_M1 == currentB_M1) {
	          	encoder_count_M1++;
	          } else {
	          	encoder_count_M1--;
	          }
	          lastA_M1 = currentA_M1;
	      } else if (GPIO_Pin == M1_Encoder_B_Pin) {
	          if (currentA_M1 != currentB_M1) {
	          	encoder_count_M1++;
	          } else {
	          	encoder_count_M1--;
	          }
	          lastB_M1 = currentB_M1;
	      }
	  }
	  // Interrupt callback handler encoder M2
	  void HAL_GPIO_EXTI_Callback_M2(uint16_t GPIO_Pin) {
	      // Read the current state of A and B pins
	      bool currentA_M2 = HAL_GPIO_ReadPin(GPIOB, M2_Encoder_A_Pin);
	      bool currentB_M2 = HAL_GPIO_ReadPin(GPIOB, M2_Encoder_B_Pin);

	      // Check which pin triggered the interrupt
	      if (GPIO_Pin == M2_Encoder_A_Pin) {
	          // Determine direction by using the state of A and B
	          if (currentA_M2 != lastA_M2) { // Only act on changes
	              if (currentA_M2 == currentB_M2) {
	                  encoder_count_M2--;
	              } else {
	                  encoder_count_M2++;
	              }
	          }
	      } else if (GPIO_Pin == M2_Encoder_B_Pin) {
	          if (currentB_M2 != lastB_M2) { // Only act on changes
	              if (currentA_M2 != currentB_M2) {
	                  encoder_count_M2--;
	              } else {
	                  encoder_count_M2++;
	              }
	          }
	      }

	  // Interrupt callback handler encoder M3
		  	  void HAL_GPIO_EXTI_Callback_M3(uint16_t GPIO_Pin) {
		  	      // Adjust the GPIO pins to the actual ones used for A and B
		  	      bool currentA_M3 = HAL_GPIO_ReadPin(GPIOA, M3_Encoder_A_Pin);
		  	      bool currentB_M3 = HAL_GPIO_ReadPin(GPIOC, M3_Encoder_B_Pin);

		  	      if (GPIO_Pin == M3_Encoder_A_Pin) {
		  	          if (currentA_M3 == currentB_M3) {
		  	          	encoder_count_M3++;
		  	          } else {
		  	          	encoder_count_M3--;
		  	          }
		  	          lastA_M3 = currentA_M3;
		  	      } else if (GPIO_Pin == M3_Encoder_B_Pin) {
		  	          if (currentA_M3 != currentB_M3) {
		  	          	encoder_count_M3++;
		  	          } else {
		  	        	encoder_count_M3--;
		  	          }
		  	          lastB_M3 = currentB_M3;
		  	      }
		  	  }
			  // Interrupt callback handler encoder M4
			  	  void HAL_GPIO_EXTI_Callback_M4(uint16_t GPIO_Pin) {
			  	      // Adjust the GPIO pins to the actual ones used for A and B
			  	      bool currentA_M4 = HAL_GPIO_ReadPin(GPIOB, M4_Encoder_A_Pin);
			  	      bool currentB_M4 = HAL_GPIO_ReadPin(GPIOA, M4_Encoder_B_Pin);

			  	      if (GPIO_Pin == M4_Encoder_A_Pin) {
			  	          if (currentA_M4 == currentB_M4) {
			  	          	encoder_count_M4++;
			  	          } else {
			  	          	encoder_count_M4--;
			  	          }
			  	          lastA_M4 = currentA_M4;
			  	      } else if (GPIO_Pin == M4_Encoder_B_Pin) {
			  	          if (currentA_M4 != currentB_M4) {
			  	          	encoder_count_M4++;
			  	          } else {
			  	        	encoder_count_M4--;
			  	          }
			  	          lastB_M4 = currentB_M4;
			  	      }
			  	  }

					  // Interrupt callback handler encoder M6
					  	  void HAL_GPIO_EXTI_Callback_M6(uint16_t GPIO_Pin) {
					  	      // Adjust the GPIO pins to the actual ones used for A and B
					  	      bool currentA_M6 = HAL_GPIO_ReadPin(GPIOB, M6_Encoder_A_Pin);
					  	      bool currentB_M6 = HAL_GPIO_ReadPin(GPIOB, M6_Encoder_B_Pin);

					  	      if (GPIO_Pin == M6_Encoder_A_Pin) {
					  	          if (currentA_M6 == currentB_M6) {
					  	          	encoder_count_M6++;
					  	          } else {
					  	          	encoder_count_M6--;
					  	          }
					  	          lastA_M6 = currentA_M6;
					  	      } else if (GPIO_Pin == M6_Encoder_B_Pin) {
					  	          if (currentA_M6 != currentB_M6) {
					  	          	encoder_count_M6++;
					  	          } else {
					  	        	encoder_count_M6--;
					  	          }
					  	          lastB_M6 = currentB_M6;
					  	      }
					  	  }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */


void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
