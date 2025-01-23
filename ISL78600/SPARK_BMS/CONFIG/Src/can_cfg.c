/*
 * @filename	can_cfg.c
 * @author		SPARKBMS TEAM
 * @date		04-May-2023
 * @ingroup		FOLDER NAME
 * @prefix		can_cfg
 * 
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "can_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

CAN_HandleTypeDef	can_cfg = {
		.Instance = CAN1,
		.Init.Mode = CAN_MODE_NORMAL,
		.Init.Prescaler = 20,			    //40 for 250kbps	// 20 for 500kbps
		.Init.SyncJumpWidth = CAN_SJW_1TQ,
		.Init.TimeSeg1 = CAN_BS1_6TQ,
		.Init.TimeSeg2 = CAN_BS2_1TQ,
		.Init.AutoBusOff = DISABLE,
		.Init.AutoRetransmission = DISABLE,
		.Init.AutoWakeUp = DISABLE,
		.Init.ReceiveFifoLocked = DISABLE,
		.Init.TimeTriggeredMode = DISABLE,
		.Init.TransmitFifoPriority = DISABLE
};

CAN_FilterTypeDef	can_filter_cfg = {
		.FilterActivation = CAN_FILTER_ENABLE,
		.FilterBank = 0,
		.FilterFIFOAssignment = CAN_RX_FIFO0,
		.FilterMode = CAN_FILTERMODE_IDMASK,
		.FilterScale = CAN_FILTERSCALE_32BIT,
		.FilterMaskIdHigh = 0X0000,     //0XFFFF,
		.FilterIdLow = 0X0000,
		.FilterIdHigh = 0X0000,       // (0X19090000 >> 13) & 0XFFFF,
		.FilterMaskIdLow = 0X0000
};
