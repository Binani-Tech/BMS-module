/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart3;

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* USER CODE BEGIN PV */

uint8_t BMS_TX_BUFF[24][3] = {
		{0x25,0x80,0x00},	//0: Read User Register-1
		{0xA5,0xBA,0x5A},	//1: Write 0x3A5A in User Register-1
		{0xA5,0x80,0x00},	//2: Write 0x0000 in User Register-1
		{0x26,0xC0,0x00},	//3:
		{0x27,0x00,0x00},	//4:
		{0x31,0x40,0x00},	//5:
		{0x10,0x00,0x00},	//6:
		{0x00,0x00,0x00},	//7: Dummy Bytes to Read Data
		{0x03,0x24,0x04},	//8: Identify Master (Device-1)
		{0x03,0x24,0x20},	//9: Identify Slave (Device-2)
		{0x03,0x24,0x30},	//10: Identify Slave (Device-3)
		{0x03,0x24,0x40},	//11: Identify Slave (Device-4)
		{0x03,0x24,0x50},	//12: Identify Slave (Device-5)
		{0x03,0x24,0x60},	//13: Identify Slave (Device-6)
		{0x03,0x24,0x70},	//14: Identify Slave (Device-7)
		{0x03,0x24,0x80},	//15: Identify Slave (Device-8)
		{0x03,0x24,0x90},	//16: Identify Slave (Device-9)
		{0x03,0x24,0xA0},	//17: Identify Slave (Device-10)
		{0x03,0x24,0xB0},	//18: Identify Slave (Device-11)
		{0x03,0x24,0xC0},	//19: Identify Slave (Device-12)
		{0x03,0x24,0xD0},	//20: Identify Slave (Device-13)
		{0x03,0x24,0xE0},	//21: Identify Slave (Device-14)
		{0x03,0x27,0xFE},	//22: Identify Complete
		{0x13,0x48,0x0C}	//23: Reset BMS IC
};

typedef struct
{
	uint8_t no0 : 1;
	uint8_t no1 : 1;
	uint8_t no2 : 1;
	uint8_t no3 : 1;
	uint8_t no4 : 1;
	uint8_t no5 : 1;
	uint8_t no6 : 1;
	uint8_t no7 : 1;
}user_bit;

uint8_t stackChecked = 1;

uint8_t BMS_RX_Buff[4];
uint8_t USER_TX_Buff[8];
uint8_t crc;

float Voltages[13];
float Voltages2[13];
float AllVoltages[25];

float Temperatures[4];
float Temperatures2[4];
float AllTemperatures[8];

float ADCEXT_TEMP[16];

uint16_t rawData[12];

#define ADCEXP_ADDR1		0X17
#define ADCEXP_ADDR2		0X15

uint8_t Rx_Buff[16]= {0};

uint8_t count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_CAN1_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC1_Init(void);
static void MX_DMA_Init(void);
/* USER CODE BEGIN PFP */

void delay_us(uint32_t delay);
void BMS_SendData(uint8_t *BMS_TX_Buff, uint8_t *BMS_RX_Buff);
uint8_t CalculateCRC4(uint8_t *Array, uint8_t len);
uint8_t isDataReady(void);
void SPI_CS_Low(void);
void SPI_CS_High(void);
void AFE_ReadReg(uint8_t *RX_Buff, uint8_t size);
void isIdentified(void);

void ResetAFE(void);

void ScanVoltages(void);
void ScanTemperatures(void);
void CalculatePackVoltage(uint8_t *Rx_Buff, float *Voltage);
void CalculateCellVoltage(uint8_t*Rx_Buff, float *Voltage);
void CalculateTemperature(uint8_t*Rx_Buff, float *Temperature);
void ReadAllVoltages(uint8_t totalStack, float *Voltage);
void ReadVoltages(uint8_t stackNo, float *Voltage);
void ReadTotalPackVoltage(uint8_t totalStack, float *Voltage);
void ReadPackVoltage(uint8_t stackNo, float *Voltage);
void ReadAllTemperatures(uint8_t totalStack, float *Temperature);
void ReadTemperatures(uint8_t stackNo, float *Temperature);

void ReadADCEXP_Temperatures(float *Temperatures);

void CAN1_Tx(void);

void I2C_Read(void);
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
  MX_SPI2_Init();
  MX_TIM6_Init();
  MX_USART3_UART_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

	HAL_GPIO_WritePin(Boot_Pin_GPIO_Port, Boot_Pin_Pin, GPIO_PIN_RESET);
	HAL_TIM_Base_Start(&htim6);

	isIdentified();

//	if(HAL_CAN_Start(&hcan1) != HAL_OK)
//	{
//		Error_Handler();
//	}

//	HAL_GPIO_WritePin(Chg_Cont_GPIO_Port, Chg_Cont_Pin, 1);
//	HAL_GPIO_WritePin(Dchg_Cont_GPIO_Port, Dchg_Cont_Pin, 1);
//	HAL_GPIO_WritePin(Pchg_Cont_GPIO_Port, Pchg_Cont_Pin, 1);


//	I2C_Read();

//	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)rawData, 12);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		ScanVoltages();

//		ReadVoltages(1, Voltages);
//		ReadPackVoltage(1, &Voltages[12]);
//
//		ReadVoltages(2, Voltages2);
//		ReadPackVoltage(2, &Voltages2[12]);

		ReadAllVoltages(2, AllVoltages);
		ReadTotalPackVoltage(2, &AllVoltages[24]);

		ScanTemperatures();

//		ReadTemperatures(1, Temperatures);
//		ReadTemperatures(2, Temperatures2);

		ReadAllTemperatures(2, AllTemperatures);

//		CAN1_Tx();
//
//		ReadADCEXP_Temperatures(ADCEXT_TEMP);

		HAL_Delay(500);
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 8;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00300B29;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }

  /** I2C Fast mode Plus enable
  */
  HAL_I2CEx_EnableFastModePlus(I2C_FASTMODEPLUS_I2C1);
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 64-1;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000-1;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Chg_Cont_Pin|Pchg_Cont_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Dchg_Cont_GPIO_Port, Dchg_Cont_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Boot_Pin_GPIO_Port, Boot_Pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SPI2_CS_Pin */
  GPIO_InitStruct.Pin = SPI2_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SPI2_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Data_Ready_Pin Fault_Pin */
  GPIO_InitStruct.Pin = Data_Ready_Pin|Fault_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Chg_Cont_Pin Pchg_Cont_Pin */
  GPIO_InitStruct.Pin = Chg_Cont_Pin|Pchg_Cont_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Dchg_Cont_Pin */
  GPIO_InitStruct.Pin = Dchg_Cont_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Dchg_Cont_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Boot_Pin_Pin */
  GPIO_InitStruct.Pin = Boot_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Boot_Pin_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void delay_us(uint32_t delay)
{
	__HAL_TIM_SET_COUNTER(&htim6,0);
	while(__HAL_TIM_GET_COUNTER(&htim6) < (delay));
}

void BMS_SendData(uint8_t *BMS_TX_Buff, uint8_t *BMS_RX_Buff)
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	//	delay_us(10);
	HAL_SPI_TransmitReceive(&hspi2, BMS_TX_Buff, BMS_RX_Buff, 1,100);

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
}

uint8_t CalculateCRC4(uint8_t *Array, uint8_t len)
{
	uint8_t ii = 0;
	uint8_t j = 0;
	uint8_t k = 0;

	user_bit bit = {0};
	user_bit ff = {0};
	user_bit carry = {0};

	uint8_t tempByte = 0;
	uint8_t result = 0;

	// Initialize bits
	bit.no0 = 0;
	bit.no1 = 0;
	bit.no2 = 0;
	bit.no3 = 0;

	for(ii=0; ii<len; ii++)
	{
		tempByte = *Array++;
		if(ii == (len - 1))
		{
			k = 4;
		}
		else
		{
			k = 8;
		}

		for(j = 0; j < k; j++)
		{
			carry.no0 = (tempByte & 0X80) > 0;
			tempByte = (uint8_t)((tempByte & 0X7F) * 2);
			ff.no0 = carry.no0 ^ bit.no3;
			ff.no1 = bit.no0 ^ bit.no3;
			ff.no2 = bit.no1;
			ff.no3 = bit.no2;
			bit.no0 = ff.no0;
			bit.no1 = ff.no1;
			bit.no2 = ff.no2;
			bit.no3 = ff.no3;
		}
	}

	result = 0;
	if(bit.no0) { result = (uint8_t)(result + 1); }
	if(bit.no1) { result = (uint8_t)(result + 2); }
	if(bit.no2) { result = (uint8_t)(result + 4); }
	if(bit.no3) { result = (uint8_t)(result + 8); }

	return result;
}

uint8_t isDataReady(void)
{
	uint8_t pinState = 0;
	pinState = HAL_GPIO_ReadPin(Data_Ready_GPIO_Port, Data_Ready_Pin);
	if(pinState == GPIO_PIN_RESET)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void SPI_CS_Low(void)
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
}

void SPI_CS_High(void)
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);
}

void AFE_ReadReg(uint8_t *RX_Buff, uint8_t size)
{
	uint8_t delay = 0;
	if(size > 0)
	{
		for(uint8_t i=0; i<size; i++)
		{
			while(isDataReady() != 1){
				if(delay == 36)
				{
					delay = 0;
					break;
				}
				delay_us(1);
				delay++;
			}
			SPI_CS_Low();
			HAL_SPI_Receive(&hspi2, &RX_Buff[i], 1, HAL_MAX_DELAY);
			SPI_CS_High();
//			while(isDataReady() != 0);
		}
	}
}

void CalculatePackVoltage(uint8_t *Rx_Buff, float *Voltage)
{
	uint16_t DATA = 0;
	uint32_t data32 = 0;

	for(uint8_t i=0; i<4; i++)
	{
		data32 |= (Rx_Buff[i] << (3 - i)*8);
	}

	DATA = (uint16_t)(data32 >> 4 & 0X0003FFF);

	if(DATA < 8191)
	{
		*Voltage = ((float)DATA*15.9350784*2.5)/8192;
	}
}

void CalculateCellVoltage(uint8_t*Rx_Buff, float *Voltage)
{
	uint16_t DATA = 0;
	uint32_t data32 = 0;

	for(uint8_t i=0; i<4; i++)
	{
		data32 |= (Rx_Buff[i] << (3 - i)*8);
	}

	DATA = (uint16_t)(data32 >> 4 & 0X0003FFF);

	if(DATA < 8191)
	{
		*Voltage = ((float)DATA*2*2.5)/8192;
	}
}

void CalculateTemperature(uint8_t*Rx_Buff, float *Temperature)
{
	uint16_t DATA = 0;
	uint32_t data32 = 0;
	float Vout = 0;
	float R_NTC = 0;

	for(uint8_t i=0; i<4; i++)
	{
		data32 |= (Rx_Buff[i] << (3 - i)*8);
	}

	DATA = (uint16_t)(data32 >> 4 & 0X0003FFF);

	Vout = ((float)DATA*2.5*2)/16384;
	R_NTC = (Vout * 10000)/(2.5 - Vout);
	*Temperature = ((298*3700)/(298*log((float)R_NTC/10000)+3700)) - 273;
}

void ScanVoltages(void)
{
	uint8_t Tx_Buff[3] = {0};
	uint8_t crc = 0;

	Tx_Buff[0] = 0XF3;
	Tx_Buff[1] = 0X04;
	Tx_Buff[2] = 0X00;
	crc = CalculateCRC4(Tx_Buff, 3);
	Tx_Buff[2] = Tx_Buff[2] + crc;

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	delay_us(50);
}

void ScanTemperatures(void)
{
	uint8_t Tx_Buff[3] = {0};
	uint8_t crc = 0;

	Tx_Buff[0] = 0XF3;
	Tx_Buff[1] = 0X08;
	Tx_Buff[2] = 0X00;
	crc = CalculateCRC4(Tx_Buff, 3);
	Tx_Buff[2] = Tx_Buff[2] + crc;

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	delay_us(50);
}

void ReadPackVoltage(uint8_t stackNo, float *Voltage)
{
	uint8_t Rx_Buff[4] = {0};
	uint8_t Tx_Buff[3] = {0};
	uint8_t pageNo = 1;
	uint8_t crc = 0;

	Tx_Buff[0] = ((stackNo & 0X0F) << 4) | pageNo;
	Tx_Buff[1] = 0X00;
	Tx_Buff[2] = 0X00;
	crc = CalculateCRC4(Tx_Buff, 3);
	Tx_Buff[2] = Tx_Buff[2] + crc;

	SPI_CS_Low();
	HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
	SPI_CS_High();

	while(isDataReady() != 1);
	AFE_ReadReg(Rx_Buff, 4);
	CalculatePackVoltage(Rx_Buff, Voltage);
}

void ReadTotalPackVoltage(uint8_t totalStack, float *Voltage)
{
	uint8_t Rx_Buff[4] = {0};
	uint8_t Tx_Buff[3] = {0};
	uint8_t pageNo = 1;
	uint8_t crc = 0;
	float StackVoltage[16] = {0};
	float TotalVoltage = 0;

	for(uint8_t stack=1; stack<(totalStack+1); stack++)
	{
		Tx_Buff[0] = ((stack & 0X0F) << 4) | pageNo;
		Tx_Buff[1] = 0X00;
		Tx_Buff[2] = 0X00;
		crc = CalculateCRC4(Tx_Buff, 3);
		Tx_Buff[2] = Tx_Buff[2] + crc;

		SPI_CS_Low();
		HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
		SPI_CS_High();

		while(isDataReady() != 1);
		AFE_ReadReg(Rx_Buff, 4);
		CalculatePackVoltage(Rx_Buff, &StackVoltage[stack-1]);

		TotalVoltage += StackVoltage[stack-1];
	}

	*Voltage = TotalVoltage;
}

void ReadVoltages(uint8_t stackNo, float *Voltage)
{
	uint8_t Rx_Buff[4] = {0};
	uint8_t Tx_Buff[3] = {0};
	uint8_t pageNo = 1;
	uint8_t crc = 0;

	for(uint8_t i=1; i<13; i++)
	{
		Tx_Buff[0] = ((stackNo & 0X0F) << 4) | pageNo;
		Tx_Buff[1] = ((i & 0X3F) << 2);
		Tx_Buff[2] = 0X00;
		crc = CalculateCRC4(Tx_Buff, 3);
		Tx_Buff[2] = Tx_Buff[2] + crc;

		SPI_CS_Low();
		HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
		SPI_CS_High();

		while(isDataReady() != 1);
		AFE_ReadReg(Rx_Buff, 4);
		CalculateCellVoltage(Rx_Buff, &Voltage[i-1]);
	}
}

void ReadAllVoltages(uint8_t totalStack, float *Voltage)
{
	uint8_t Rx_Buff[4] = {0};
	uint8_t Tx_Buff[3] = {0};
	uint8_t pageNo = 1;
	uint8_t crc = 0;
	uint8_t cellIndex = 0;

	for(uint8_t stack=1; stack<(totalStack+1); stack++)
	{
		for(uint8_t cellNo=1; cellNo<13; cellNo++)
		{
			Tx_Buff[0] = ((stack & 0X0F) << 4) | pageNo;
			Tx_Buff[1] = ((cellNo & 0X3F) << 2);
			Tx_Buff[2] = 0X00;
			crc = CalculateCRC4(Tx_Buff, 3);
			Tx_Buff[2] = Tx_Buff[2] + crc;

			SPI_CS_Low();
			HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
			SPI_CS_High();

			while(isDataReady() != 1);
			AFE_ReadReg(Rx_Buff, 4);
			CalculateCellVoltage(Rx_Buff, &Voltage[cellIndex]);
			cellIndex++;
		}
	}
}

void ReadTemperatures(uint8_t stackNo, float *Temperature)
{
	uint8_t Rx_Buff[4] = {0};
	uint8_t Tx_Buff[3] = {0};
	uint8_t pageNo = 1;
	uint8_t crc = 0;

	for(uint8_t i=1; i<5; i++)
	{
		Tx_Buff[0] = ((stackNo & 0X0F) << 4) | pageNo;
		Tx_Buff[1] = (((0X10 | i ) & 0X3F) << 2);
		Tx_Buff[2] = 0X00;
		crc = CalculateCRC4(Tx_Buff, 3);
		Tx_Buff[2] = Tx_Buff[2] + crc;

		SPI_CS_Low();
		HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
		SPI_CS_High();

		while(isDataReady() != 1);
		AFE_ReadReg(Rx_Buff, 4);
		CalculateTemperature(Rx_Buff, &Temperature[i-1]);
	}
}

void ReadAllTemperatures(uint8_t totalStack, float *Temperature)
{
	uint8_t Rx_Buff[4] = {0};
	uint8_t Tx_Buff[3] = {0};
	uint8_t pageNo = 1;
	uint8_t crc = 0;
	uint8_t tempIndex = 0;

	for(uint8_t stack=1; stack<(totalStack+1); stack++)
	{
		for(uint8_t tempNo=1; tempNo<5; tempNo++)
		{
			Tx_Buff[0] = ((stack & 0X0F) << 4) | pageNo;
			Tx_Buff[1] = (((0X10 | tempNo ) & 0X3F) << 2);
			Tx_Buff[2] = 0X00;
			crc = CalculateCRC4(Tx_Buff, 3);
			Tx_Buff[2] = Tx_Buff[2] + crc;

			SPI_CS_Low();
			HAL_SPI_Transmit(&hspi2, Tx_Buff, 3,HAL_MAX_DELAY);
			SPI_CS_High();

			while(isDataReady() != 1);
			AFE_ReadReg(Rx_Buff, 4);
			CalculateTemperature(Rx_Buff, &Temperature[tempIndex]);
			tempIndex++;
		}
	}
}

void ResetAFE(void)
{
	uint8_t TX_Buff[3] = {0};
	TX_Buff[0] = 0X13;
	TX_Buff[1] = 0X48;
	TX_Buff[2] = 0X00;
	crc = CalculateCRC4(TX_Buff, 3);
	TX_Buff[2] = TX_Buff[2] + crc;

	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, TX_Buff, 3,HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

	delay_us(50);
}

void isIdentified(void)
{
	uint8_t TX_Buff[3] = {0};

	uint32_t data32 = 0;
//	uint8_t delay = 0;
	do{
		switch(stackChecked)
		{
		uint8_t RX_Buff[4];
		case 1:
			TX_Buff[0] = 0X03;
			TX_Buff[1] = 0X24;
			TX_Buff[2] = 0X00;
			crc = CalculateCRC4(TX_Buff, 3);
			TX_Buff[2] = TX_Buff[2] + crc;

			delay_us(1);

			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&hspi2, TX_Buff, 3,HAL_MAX_DELAY);
			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

			while(isDataReady() != 1)
			{
//				if(delay == 36)
//				{
//					break;
//				}
//				delay_us(1);
//				delay++;
			}
			AFE_ReadReg(RX_Buff, 4);

			for(uint8_t i=0; i<4; i++)
			{
				data32 |= (RX_Buff[i] << (3 - i)*8);
			}

			if(data32 == 0X330000C)
			{
				stackChecked++;
				data32 = 0;
			}
			else
			{
				ResetAFE();
				data32 = 0;
				HAL_Delay(500);
			}

			break;

		case 2:
			TX_Buff[0] = 0X03;
			TX_Buff[1] = 0X24;
			TX_Buff[2] = 0X20;
			crc = CalculateCRC4(TX_Buff, 3);
			TX_Buff[2] = TX_Buff[2] + crc;

			delay_us(1);

			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&hspi2, TX_Buff, 3,HAL_MAX_DELAY);
			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

			while(isDataReady() != 1)
			{
//				if(delay == 36)
//				{
//					break;
//				}
//				delay_us(1);
//				delay++;
			}
			AFE_ReadReg(RX_Buff, 4);

			for(uint8_t i=0; i<4; i++)
			{
				data32 |= (RX_Buff[i] << (3 - i)*8);
			}

			if(data32 == 0X3262000)
			{
				stackChecked++;
				data32 = 0;
			}
			else
			{
				ResetAFE();
				stackChecked = 1;
			}

			break;

		case 3:
			TX_Buff[0] = 0X03;
			TX_Buff[1] = 0X27;
			TX_Buff[2] = 0XF0;
			crc = CalculateCRC4(TX_Buff, 3);
			TX_Buff[2] = TX_Buff[2] + crc;

			delay_us(1);

			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET);
			HAL_SPI_Transmit(&hspi2, TX_Buff, 3,HAL_MAX_DELAY);
			HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET);

			while(isDataReady() != 1)
			{
//				if(delay == 36)
//				{
//					break;
//				}
//				delay_us(1);
//				delay++;
			}
			AFE_ReadReg(RX_Buff, 4);

			for(uint8_t i=0; i<4; i++)
			{
				data32 |= (RX_Buff[i] << (3 - i)*8);
			}

			if(data32 == 0X2330000B)
			{
				stackChecked++;
				data32 = 0;
			}
			else
			{
				ResetAFE();
				stackChecked = 1;
			}

			break;


		}


	}while(stackChecked < 4);
}

void CAN1_Tx(void)
{
	uint32_t TxMailBox;
	uint8_t data[8] = {1,2,3,4,5,6,7,8};
	CAN_TxHeaderTypeDef	can_tx;

	can_tx.DLC = 8;
	can_tx.IDE = CAN_ID_EXT;
	can_tx.ExtId = 0X19090301;
	can_tx.RTR = CAN_RTR_DATA;

	HAL_UART_Transmit(&huart3, data, 8, HAL_MAX_DELAY);

	HAL_CAN_AddTxMessage(&hcan1, &can_tx, data, &TxMailBox);
	while(HAL_CAN_IsTxMessagePending(&hcan1, TxMailBox));
}

void I2C_Read(void)
{
	/* Analog Input Config in PIN_CFG */
	uint8_t Tx_Buff[3] = {0};
	Tx_Buff[0] = 0X08;
	Tx_Buff[1] = 0X5;
	Tx_Buff[2] = 0X00;

	HAL_I2C_Master_Transmit(&hi2c1, 0X15 << 1 , Tx_Buff, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Analog Pin Selection for Sequencing in AUTO_SEQ_CHSEL */
	uint8_t Tx_Buff2[3] = {0};
	Tx_Buff2[0] = 0X08;
	Tx_Buff2[1] = 0X12;
	Tx_Buff2[2] = 0XFF;

	HAL_I2C_Master_Transmit(&hi2c1, 0X15 << 1, Tx_Buff2, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Audo Sequence Mode and Enable Channel Sequencing in SEQUENCE_CFG */
	uint8_t Tx_Buff3[3] = {0};
	Tx_Buff3[0] = 0X08;
	Tx_Buff3[1] = 0X10;
	Tx_Buff3[2] = 0X11;

	HAL_I2C_Master_Transmit(&hi2c1, 0X15 << 1, Tx_Buff3, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Analog Input Config in PIN_CFG */
	uint8_t Tx_Buff4[3] = {0};
	Tx_Buff4[0] = 0X08;
	Tx_Buff4[1] = 0X5;
	Tx_Buff4[2] = 0X00;

	HAL_I2C_Master_Transmit(&hi2c1, 0X17 << 1 , Tx_Buff4, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Analog Pin Selection for Sequencing in AUTO_SEQ_CHSEL */
	uint8_t Tx_Buff5[3] = {0};
	Tx_Buff5[0] = 0X08;
	Tx_Buff5[1] = 0X12;
	Tx_Buff5[2] = 0XFF;

	HAL_I2C_Master_Transmit(&hi2c1, 0X17 << 1, Tx_Buff5, 3, HAL_MAX_DELAY);

	HAL_Delay(1);

	/* Audo Sequence Mode and Enable Channel Sequencing in SEQUENCE_CFG */
	uint8_t Tx_Buff6[3] = {0};
	Tx_Buff6[0] = 0X08;
	Tx_Buff6[1] = 0X10;
	Tx_Buff6[2] = 0X11;

	HAL_I2C_Master_Transmit(&hi2c1, 0X17 << 1, Tx_Buff6, 3, HAL_MAX_DELAY);

	HAL_Delay(1);
}

void ReadADCEXP_Temperatures(float *Temperatures)
{
	uint8_t RX_Buff[32] = {0};
	uint16_t Temp_ADC = 0;
	float Vout = 0;
	float R_NTC = 0;

	uint8_t Count = 0;

	HAL_I2C_Master_Receive(&hi2c1, ADCEXP_ADDR1 << 1, RX_Buff, 16, HAL_MAX_DELAY);
	HAL_Delay(1);
	HAL_I2C_Master_Receive(&hi2c1, ADCEXP_ADDR2 << 1, &RX_Buff[16], 16, HAL_MAX_DELAY);

	for(uint8_t i=0; i<16; i++)
	{
		Temp_ADC = ((RX_Buff[Count] << 8) | (RX_Buff[Count + 1] & 0XF0)) >> 4;
		Vout = ((float)Temp_ADC*3.3)/4095;
		R_NTC = (Vout * 10000)/(3.3 - Vout);
		Temperatures[i] = ((298*3700)/(298*log((float)R_NTC/10000)+3700)) - 273;
		Count += 2;
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

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 12;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc1.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_10;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_11;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_12;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

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
