/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "oled_lib_tbz.h"
#include "gfx_internal.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define OLED_RESET  (1<<2)
#define OLED_DC     (1<<3)
#define OLED_CS     (1<<4)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_ms(uint32_t period)
{
    HAL_Delay(period);
}

void pin_cs(uint8_t pinstate)
{
    HAL_GPIO_WritePin(GPIOA, OLED_CS, pinstate);
}

void pin_dc(uint8_t pinstate)
{
    HAL_GPIO_WritePin(GPIOA, OLED_DC, pinstate);
}

void pin_rs(uint8_t pinstate)
{
    HAL_GPIO_WritePin(GPIOA, OLED_RESET, pinstate);
}

void transmit_data(uint8_t *data, uint32_t len)
{
    HAL_SPI_Transmit(&hspi1, data, len, 1000);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

    s_ssd1351 function_pointers;

    function_pointers.pin_cs = pin_cs;
    function_pointers.pin_rs = pin_rs;
    function_pointers.pin_dc = pin_dc;
    function_pointers.transmit_data = transmit_data;
    function_pointers.delay = delay_ms;

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  oled_init(&function_pointers, DISPLAY_ORIENTATION_UP);

//  uint8_t direction = 0;
//
//  uint8_t ctr0 = 20;

  gfx_std_screen_clear(colors.red);

  gfx_std_draw_circle(0, 63, 10, colors.green, 1);

//  gfx_std_draw_circle_filled(63, 63, 10, colors.red, 1);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

//        if(direction)
//        {
//            if(ctr0 < 108)
//            {
//                gfx_std_draw_circle_filled(ctr0 + 1, 10, 10, colors.black, 0);
//                gfx_std_draw_circle_filled(ctr0 + 1, 35, 10, colors.black, 0);
//                gfx_std_draw_circle_filled(ctr0 + 1, 60, 10, colors.black, 0);
//                gfx_std_draw_circle_filled(ctr0 + 1, 85, 10, colors.black, 0);
//            }
//            ctr0 -= 5;
//            gfx_std_draw_circle_filled(ctr0, 10, 10, colors.red, 0);
//            gfx_std_draw_circle_filled(ctr0, 35, 10, colors.red, 0);
//            gfx_std_draw_circle_filled(ctr0, 60, 10, colors.red, 0);
//            gfx_std_draw_circle_filled(ctr0, 85, 10, colors.red, 1);
//
//
//            if(ctr0 <= 25) direction = 0;
//        }
//        else
//        {
//            if(ctr0 > 20)
//            {
//                gfx_std_draw_circle_filled(ctr0 - 1, 10, 10, colors.black, 0);
//                gfx_std_draw_circle_filled(ctr0 - 1, 35, 10, colors.black, 0);
//                gfx_std_draw_circle_filled(ctr0 - 1, 60, 10, colors.black, 0);
//                gfx_std_draw_circle_filled(ctr0 - 1, 85, 10, colors.black, 0);
//            }
//            ctr0 += 5;
//            gfx_std_draw_circle_filled(ctr0, 10, 10, colors.red, 0);
//            gfx_std_draw_circle_filled(ctr0, 35, 10, colors.red, 0);
//            gfx_std_draw_circle_filled(ctr0, 60, 10, colors.red, 0);
//            gfx_std_draw_circle_filled(ctr0, 85, 10, colors.red, 1);
//
//
//            if(ctr0 >= 103) direction = 1;
//        }

//        gfx_std_draw_circle_filled(63, 63, 60, colors.red, 1);
//
//        gfx_std_draw_circle_filled(63, 63, 60, colors.yellow, 1);
//
//        gfx_std_draw_circle_filled(63, 63, 60, colors.green, 1);
//
//        gfx_std_draw_circle_filled(63, 63, 60, colors.cyan, 1);
//
//        gfx_std_draw_circle_filled(63, 63, 60, colors.blue, 1);
//
//        gfx_std_draw_circle_filled(63, 63, 60, colors.magenta, 1);

//        for(ctr0 = 1; ctr0 < 60; ctr0++)
//        {
//            gfx_std_draw_circle_filled(63, 63, ctr0, colors.red, 1);
//        }
//        for(ctr0 = 1; ctr0 < 60; ctr0++)
//        {
//            gfx_std_draw_circle_filled(63, 63, ctr0, colors.yellow, 1);
//        }
//        for(ctr0 = 1; ctr0 < 60; ctr0++)
//        {
//            gfx_std_draw_circle_filled(63, 63, ctr0, colors.green, 1);
//        }
//        for(ctr0 = 1; ctr0 < 60; ctr0++)
//        {
//            gfx_std_draw_circle_filled(63, 63, ctr0, colors.cyan, 1);
//        }
//        for(ctr0 = 1; ctr0 < 60; ctr0++)
//        {
//            gfx_std_draw_circle_filled(63, 63, ctr0, colors.blue, 1);
//        }
//        for(ctr0 = 1; ctr0 < 60; ctr0++)
//        {
//            gfx_std_draw_circle_filled(63, 63, ctr0, colors.magenta, 1);
//        }
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the Systick interrupt time 
  */
  __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
