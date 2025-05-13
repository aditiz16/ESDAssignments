/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
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
#include "stdlib.h";
#include "stdio.h";

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
void lcd_enable(void) ;
void lcd_data(unsigned char);
void lcd_cmd(unsigned char);
void lcd_init(void);
void lcd_displayString(int, int, unsigned char*);
void lcd_clear(void);

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		ITM_SendChar(*ptr++);
	}
	return len;
}


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  unsigned char buf[16] ;
  uint16_t val = 0 ;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	  HAL_ADC_Start(&hadc1);
	  	  if(HAL_ADC_PollForConversion(&hadc1,10)==HAL_OK)
	  	  {
	  		  val=(int)HAL_ADC_GetValue(&hadc1);
	  		  sprintf(buf, "%d",val);


	  			lcd_clear();
	  			lcd_displayString(1,1,buf);
	  			printf("%d\n", val) ;
	  	  }
	  	  HAL_ADC_Stop(&hadc1);

	  		HAL_Delay(100);


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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */


void lcd_enable(void)
{
	GPIOH->BSRR = (1<<1) ;
	HAL_Delay(1);
	GPIOH->BSRR = (1<<1) << 16 ;
	HAL_Delay(1);
}


void lcd_data(unsigned char data)
{
	 //	 RS = 1 for LCD data
	 GPIOD->BSRR = (1<<10) ;

 	//D5 If data exists SET else RESET
	 GPIOE->BSRR = (data & 0x01) ? (1<<11) : ((uint32_t)(1<<11) << 16);
	 GPIOE->BSRR = (data & 0x02) ? (1<<12) : ((uint32_t)(1<<12) << 16);
	 GPIOE->BSRR = (data & 0x04) ? (1<<13) : ((uint32_t)(1<<13) << 16);
	 GPIOE->BSRR = (data & 0x08) ? (1<<14) : ((uint32_t)(1<<14) << 16);
	 GPIOE->BSRR = (data & 0x10) ? (1<<15) : ((uint32_t)(1<<15) << 16);
	 GPIOD->BSRR = (data & 0x20) ? (1<<7) : ((uint32_t)(1<<7) << 16);
	 GPIOD->BSRR = (data & 0x40) ? (1<<8) : ((uint32_t)(1<<8) << 16);
	 GPIOD->BSRR = (data & 0x80) ? (1<<9) : ((uint32_t)(1<<9) << 16);

	 lcd_enable();
}

void lcd_cmd(unsigned char cmd)
{
	 //RS=0 for LCD command
	 GPIOD->BSRR = (1<<10) << 16 ;

	 GPIOE->BSRR = (cmd & 0x01) ? (1<<11) : ((uint32_t)(1<<11) << 16);
	 GPIOE->BSRR = (cmd & 0x02) ? (1<<12) : ((uint32_t)(1<<12) << 16);
	 GPIOE->BSRR = (cmd & 0x04) ? (1<<13) : ((uint32_t)(1<<13) << 16);
	 GPIOE->BSRR = (cmd & 0x08) ? (1<<14) : ((uint32_t)(1<<14) << 16);
	 GPIOE->BSRR = (cmd & 0x10) ? (1<<15) : ((uint32_t)(1<<15) << 16);
	 GPIOD->BSRR = (cmd & 0x20) ? (1<<7) : ((uint32_t)(1<<7) << 16);
	 GPIOD->BSRR = (cmd & 0x40) ? (1<<8) : ((uint32_t)(1<<8) << 16);
	 GPIOD->BSRR = (cmd & 0x80) ? (1<<9) : ((uint32_t)(1<<9) << 16);

	 lcd_enable();
}



void lcd_init(void)
 {
   // reset GPIO PH1
   GPIOH->BSRR = (1<<1) << 16 ;
   // reset all the pins of port E in use
	GPIOE->BSRR = ((1<<11) | (1<<12) | (1<<13) | (1<<14) | (1<<15)) << 16 ;
	// reset all bits of port D in use
	GPIOD->BSRR = ((1<<7) | (1<<8) | (1<<9)) << 16 ;

	lcd_cmd(0x38);						 //8bit use both lines
	lcd_cmd(0x06);						 //Entry mode
	lcd_cmd(0x0C);						 //display ON cursor OFF
	lcd_cmd(0x01);						 //Clear display
	lcd_cmd(0x80);						 //cursor at 1st line 1st position
 }


void lcd_setcursor(unsigned char row,unsigned char pos)
{
	lcd_cmd(0x0E);

	if (row == 1)
		lcd_cmd((pos & 0x0F)|0x80);
	else if (row == 2)
		lcd_cmd((pos & 0x0F)|0xC0);
}



void lcd_clear(void)
{
	 HAL_Delay(1);
	 lcd_cmd(0x01);
	 HAL_Delay(1);
}

void lcd_displayString(int row, int pos, unsigned char* ch)
{
	 unsigned char temp;

	if(row==1)
	{
		temp = 0x80 | (pos);			 //set cursor at 1st line pos position
	}
	else if(row ==2)
	{
		temp = 0xC0 | (pos);			//set cursor at 2nd line pos position
	}

	lcd_cmd(temp);

	while(*ch)							//while data is valid, display the string
		lcd_data(*ch++);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
