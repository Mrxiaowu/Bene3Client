#include "uart/ProtocolSender.h"
#include "uart/UartContext.h"
#include <stdio.h>

//Bene3

extern BYTE getCheckSum(const BYTE *pData, int len);

/**
 * 需要根据协议格式进行拼接，以下只是个模板
 */
//bool sendProtocol(const UINT16 cmdID, const BYTE *pData, BYTE len) {
//	BYTE dataBuf[256];
//
//	dataBuf[0] = CMD_HEAD1;
//	dataBuf[1] = CMD_HEAD2;			// 同步帧头
//
//	dataBuf[2] = HIBYTE(cmdID);
//	dataBuf[3] = LOBYTE(cmdID);		// 命令字节
//
//	dataBuf[4] = len;
//
//	UINT frameLen = 5;
//
//	// 数据
//	for (int i = 0; i < len; ++i) {
//		dataBuf[frameLen] = pData[i];
//		frameLen++;
//	}
//
//#ifdef PRO_SUPPORT_CHECK_SUM
//	// 校验码
//	dataBuf[frameLen] = getCheckSum(dataBuf, frameLen);
//	frameLen++;
//#endif
//
//	return UARTCONTEXT->send(dataBuf, frameLen);
//}


bool sendProtocol( const BYTE *pData, BYTE len) {
	BYTE dataBuf[256]; //TODO 字节长度有待商榷

	dataBuf[0] = CMD_HEAD1;
	dataBuf[1] = CMD_HEAD2;		// 同步帧头 两个字节
	dataBuf[2] = LOBYTE(len);  //长度

	UINT frameLen = 3;   //一帧的开始长度

	for (int i = 0; i < len; ++i) {
		dataBuf[frameLen++] = pData[i];
	}

#ifdef PRO_SUPPORT_CHECK_SUM
	dataBuf[frameLen++] = getCheckSum(pData, len);
#endif

	return UARTCONTEXT->send(dataBuf, frameLen);
}


