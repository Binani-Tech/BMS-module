/*
 * @filename	stm32l4xx_it.h
 * @author		SPARKBMS TEAM
 * @date		13-Apr-2023
 * @ingroup		FOLDER NAME
 * @prefix		stm32l4xx_it
 *
 * @brief		Add the description
 */
#ifndef INC_STM32L4XX_IT_H_
#define INC_STM32L4XX_IT_H_

/*---------------------------------------Includes------------------------------------------------------*/


/*---------------------------------------Macros--------------------------------------------------------*/


/*---------------------------------------Variables-----------------------------------------------------*/

extern uint8_t brk_Flag;
extern uint8_t rst_count;
extern uint8_t sd_rst;
extern uint8_t sd_flag;
extern uint8_t uart_rst;
extern uint8_t uart_flag;

/*---------------------------------------Function Prototypes-------------------------------------------*/

void SysTick_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void HardFault_Handler(void);
void WWDG_IRQHandler(void);

/*User Specific Error Handler*/

void Error_Handler(void);


#endif /* INC_STM32L4XX_IT_H_ */
