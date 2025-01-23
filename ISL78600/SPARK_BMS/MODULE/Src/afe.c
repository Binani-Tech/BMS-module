/*
 * @filename	afe.c
 * @author		SPARKBMS TEAM
 * @date		Apr 13, 2023
 * @ingroup		FOLDER NAME
 * @prefix		AFE
 *
 * @brief		Add the description
 */

/*-------------------------------------------Includes--------------------------------------------------*/

#include "afe.h"
#include "crc.h"
#include "mcu_cfg.h"
#include "uart.h"
#include "gpio.h"
#include "bq76pl455_cfg.h"

/*-------------------------------------------Macros----------------------------------------------------*/


/*-------------------------------------------Variables-------------------------------------------------*/


/*-------------------------------------------Function Prototypes---------------------------------------*/


/*-------------------------------------------Function Implementation-----------------------------------*/

/*
 * @brief
 * @arguments
 * @retvar
 */

void AFE_Wakeup(void)
{
	for(uint8_t i=0; i<5; i++)
	{
		GPIO_TogglePin(GPIO_PIN_BMS_WAKEUP_PIN);
		HAL_Delay(1);
	}

	for(uint8_t i=1; i<=NO_OF_DAISY_STACK; i++)
	{
		AFE_WriteReg(BQ_ADDR, 12, 20, 1, FRMWRT_ALL_NR); //12 - Device control register addr.
		HAL_Delay(1);                                    //20 - 0010 0000 - fith bit is STACK_WAKE
	}

	GPIO_WritePin(GPIO_PIN_BMS_WAKEUP_PIN, GPIO_PIN_SET);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

int  AFE_WriteReg(uint8_t bID, uint16_t wAddr, uint64_t dwData, uint8_t bLen, uint8_t bWriteType)
{
	int bRes = 0;
	uint8_t bBuf[4] = {0, 0, 0, 0};
	switch(bLen)
	{
	case 1:
		bBuf[0] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 1, bWriteType);
		break;
	case 2:
		bBuf[0] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[1] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 2, bWriteType);
		break;
	case 3:
		bBuf[0] = (dwData & 0x0000000000FF0000) >> 16;
		bBuf[1] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[2] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 3, bWriteType);
		break;
	case 4:
		bBuf[0] = (dwData & 0x00000000FF000000) >> 24;
		bBuf[1] = (dwData & 0x0000000000FF0000) >> 16;
		bBuf[2] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[3] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 4, bWriteType);
		break;
	case 5:
		bBuf[0] = (dwData & 0x000000FF00000000) >> 32;
		bBuf[1] = (dwData & 0x00000000FF000000) >> 24;
		bBuf[2] = (dwData & 0x0000000000FF0000) >> 16;
		bBuf[3] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[4] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 5, bWriteType);
		break;
	case 6:
		bBuf[0] = (dwData & 0x0000FF0000000000) >> 40;
		bBuf[1] = (dwData & 0x000000FF00000000) >> 32;
		bBuf[2] = (dwData & 0x00000000FF000000) >> 24;
		bBuf[3] = (dwData & 0x0000000000FF0000) >> 16;
		bBuf[4] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[5] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 6, bWriteType);
		break;
	case 7:
		bBuf[0] = (dwData & 0x00FF000000000000) >> 48;
		bBuf[1] = (dwData & 0x0000FF0000000000) >> 40;
		bBuf[2] = (dwData & 0x000000FF00000000) >> 32;
		bBuf[3] = (dwData & 0x00000000FF000000) >> 24;
		bBuf[4] = (dwData & 0x0000000000FF0000) >> 16;
		bBuf[5] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[6] =  dwData & 0x00000000000000FF;;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 7, bWriteType);
		break;
	case 8:
		bBuf[0] = (dwData & 0xFF00000000000000) >> 56;
		bBuf[1] = (dwData & 0x00FF000000000000) >> 48;
		bBuf[2] = (dwData & 0x0000FF0000000000) >> 40;
		bBuf[3] = (dwData & 0x000000FF00000000) >> 32;
		bBuf[4] = (dwData & 0x00000000FF000000) >> 24;
		bBuf[5] = (dwData & 0x0000000000FF0000) >> 16;
		bBuf[6] = (dwData & 0x000000000000FF00) >> 8;
		bBuf[7] =  dwData & 0x00000000000000FF;
		bRes = AFE_WriteFrame(bID, wAddr, bBuf, 8, bWriteType);
		break;
	default:
		break;
	}
	return bRes;
}

/*
 * @brief
 * @arguments
 * @retvar
 */

int  AFE_ReadReg(uint8_t bID, uint16_t wAddr, void * pData, uint8_t bLen, uint8_t dwTimeOut)
{
	int   bRes = 0;
	uint8_t  bRX[8];

	memset(bRX, 0, sizeof(bRX));
	switch(bLen)
	{
	case 1:
		bRes = AFE_ReadFrameReq(bID, wAddr, 1);
		bRes = AFE_WaitRespFrame(bRX, 4, dwTimeOut);
		if (bRes == 1)
			*((uint8_t*)pData) = bRX[1] & 0x00FF;
		else
			bRes = 0;
		break;
	case 2:
		bRes = AFE_ReadFrameReq(bID, wAddr, 2);
		bRes = AFE_WaitRespFrame(bRX, 5, dwTimeOut);
		if (bRes == 2)
			*((uint16_t *)pData) = ((uint16_t)bRX[1] << 8) | (bRX[2] & 0x00FF);
		else
			bRes = 0;
		break;
	case 3:
		bRes = AFE_ReadFrameReq(bID, wAddr, 3);
		bRes = AFE_WaitRespFrame(bRX, 6, dwTimeOut);
		if (bRes == 3)
			*((uint32_t *)pData) = ((uint32_t)bRX[1] << 16) | ((uint16_t)bRX[2] << 8) | (bRX[3] & 0x00FF);
		else
			bRes = 0;
		break;
	case 4:
		bRes = AFE_ReadFrameReq(bID, wAddr, 4);
		bRes = AFE_WaitRespFrame(bRX, 7, dwTimeOut);
		if (bRes == 4)
			*((uint32_t *)pData) = ((uint32_t)bRX[1] << 24) | ((uint32_t)bRX[2] << 16) | ((uint16_t)bRX[3] << 8) | (bRX[4] & 0x00FF);
		else
			bRes = 0;
		break;
	default:
		break;
	}
	return bRes;
}

/*
 * @brief
 * @arguments
 * @retvar
 */

int  AFE_WriteFrame(uint8_t bID, uint16_t wAddr, uint8_t * pData, uint8_t bLen, uint8_t bWriteType)
{
	int	   bPktLen = 0;
	uint8_t   pFrame[32];
	uint8_t * pBuf = pFrame;
	uint16_t   wCRC;

	if (bLen == 7 || bLen > 8)
		return 0;

	memset(pFrame, 0x7F, sizeof(pFrame));
	if (wAddr > 255)	{
		*pBuf++ = 0x88 | bWriteType | bLen;	// use 16-bit address
		if (bWriteType == FRMWRT_SGL_R || bWriteType == FRMWRT_SGL_NR || bWriteType == FRMWRT_GRP_R || bWriteType == FRMWRT_GRP_NR)//(bWriteType != FRMWRT_ALL_NR)// || (bWriteType != FRMWRT_ALL_R))
		{
			*pBuf++ = (bID & 0x00FF);
		}
		*pBuf++ = (wAddr & 0xFF00) >> 8;
		*pBuf++ =  wAddr & 0x00FF;
	}
	else {
		*pBuf++ = 0x80 | bWriteType | bLen;	// use 8-bit address
		if (bWriteType == FRMWRT_SGL_R || bWriteType == FRMWRT_SGL_NR || bWriteType == FRMWRT_GRP_R || bWriteType == FRMWRT_GRP_NR)
		{
			*pBuf++ = (bID & 0x00FF);
		}
		*pBuf++ = wAddr & 0x00FF;
	}

	while(bLen--)
		*pBuf++ = *pData++;

	bPktLen = pBuf - pFrame;

	wCRC = CRC16_Calc(pFrame, bPktLen);
	*pBuf++ = wCRC & 0x00FF;
	*pBuf++ = (wCRC & 0xFF00) >> 8;
	bPktLen += 2;

	UART_AFE_Write(pFrame, bPktLen, 100);

	return bPktLen;
}

/*
 * @brief
 * @arguments
 * @retvar
 */

int  AFE_ReadFrameReq(uint8_t bID, uint16_t wAddr, uint8_t bByteToReturn)
{
	uint8_t bReturn = bByteToReturn - 1;

	if (bReturn > 127)
		return 0;

	return AFE_WriteFrame(bID, wAddr, &bReturn, 1, FRMWRT_SGL_R);
}

/*
 * @brief
 * @arguments
 * @retvar
 */

int  AFE_WaitRespFrame(uint8_t *pFrame, uint8_t bLen, uint32_t dwTimeOut)
{
	uint16_t wCRC = 0, wCRC16;
	uint8_t bBuf[132];
	uint8_t bRxDataLen;

	memset(bBuf, 0, sizeof(bBuf));

	UART_AFE_Read(bBuf, bLen, 100);

	bRxDataLen = bBuf[0];

	HAL_Delay(dwTimeOut);

	wCRC = bBuf[bRxDataLen+2];
	wCRC |= ((uint16_t)bBuf[bRxDataLen+3] << 8);
	wCRC16 = CRC16_Calc(bBuf, bRxDataLen+2);
	if (wCRC != wCRC16)
		return -1;

	memcpy(pFrame, bBuf, bRxDataLen + 4);

	return bRxDataLen + 1;
}
