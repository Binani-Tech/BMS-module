/*
 * @filename	stm32l4xx_it.c
 * @author		SPARKBMS TEAM
 * @date		May 24, 2023
 * @ingroup		FOLDER NAME
 * @prefix		stm32l4xx_it
 *
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "mcu_cfg.h"
#include "stm32l4xx_it.h"
#include "can_cfg.h"
#include "uart_cfg.h"
#include "dma_cfg.h"
#include "contactor.h"
#include "ble.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/

volatile uint8_t FatFsCnt = 0;
volatile uint16_t Timer1, Timer2;
uint8_t brk_Flag = 0;
uint8_t rst_count = 0;
uint8_t sd_rst = 0;
uint8_t sd_flag = 0;
uint8_t uart_rst = 0;
uint8_t uart_flag = 0;

/*-------------------------------------------Function Prototypes---------------------------------------*/

void SDTimer_Handler(void);

/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void SDTimer_Handler(void)
{
  if(Timer1 > 0)
    Timer1--;

  if(Timer2 > 0)
    Timer2--;
}

void SysTick_Handler(void)
{
	FatFsCnt++;
	if(FatFsCnt >= 10)
	{
		FatFsCnt = 0;
		SDTimer_Handler();
	}

	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void MemManage_Handler(void)
{
	while(1);
}

void BusFault_Handler(void)
{
	while(1);
}

void UsageFault_Handler(void)
{
	while(1);
}

void HardFault_Handler(void)
{
	while(1);
}

void Error_Handler(void)
{
	while(1);
}

void CAN1_RX0_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&can_cfg);
}

void CAN1_TX_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&can_cfg);
}

void USART1_IRQHandler(void)
{
	Uart_isr(&uart_cfg[0]);
}

void DMA1_Channel1_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&dma_cfg[0]);
}

void EXTI3_IRQHandler(void)
{
	CONT_StateRequest(CONT_NORMAL);
}

void TIM7_IRQHandler(void)
{
	brk_Flag = 1;
	if(sd_flag != 0)
	{
		sd_rst++;
	}
	if(uart_flag != 0)
	{
		uart_rst++;
	}
	if(rst_count > 2 || sd_rst > 4 || uart_rst > 5)
	{
		WWDG_Init();
	}

	HAL_TIM_IRQHandler(&timer7_cfg);
}

