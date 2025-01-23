/*
 * @filename	afe.h
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		AFE
 *
 * @brief		Add the description
*/

#ifndef INC_AFE_H_
#define INC_AFE_H_

/*---------------------------------------Includes------------------------------------------------------*/

#include "mcu_cfg.h"

/*---------------------------------------Macros--------------------------------------------------------*/

#define FRMWRT_SGL_R	0x00 // single device write with response
#define FRMWRT_SGL_NR	0x10 // single device write without response
#define FRMWRT_GRP_R	0x20 // group broadcast with response
#define FRMWRT_GRP_NR	0x30 // group broadcast without response
#define FRMWRT_ALL_R	0x60 // general broadcast with response
#define FRMWRT_ALL_NR	0x70 // general broadcast without response

/*---------------------------------------Variables-----------------------------------------------------*/


/*---------------------------------------Function Prototypes-------------------------------------------*/

void AFE_Wakeup(void);

int  AFE_WriteReg(uint8_t bID, uint16_t wAddr, uint64_t dwData, uint8_t bLen, uint8_t bWriteType);
int  AFE_ReadReg(uint8_t bID, uint16_t wAddr, void * pData, uint8_t bLen, uint8_t dwTimeOut);

int  AFE_WriteFrame(uint8_t bID, uint16_t wAddr, uint8_t * pData, uint8_t bLen, uint8_t bWriteType);
int  AFE_ReadFrameReq(uint8_t bID, uint16_t wAddr, uint8_t bByteToReturn);
int  AFE_WaitRespFrame(uint8_t *pFrame, uint8_t bLen, uint32_t dwTimeOut);


#endif /* INC_AFE_H_ */
