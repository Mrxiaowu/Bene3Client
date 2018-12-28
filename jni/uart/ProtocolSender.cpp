#include "uart/ProtocolSender.h"
#include "uart/UartContext.h"
#include <stdio.h>

//Bene3

extern BYTE getCheckSum(const BYTE *pData, int len);

bool sendSampleProtocol(BYTE data1,BYTE data2,BYTE data3,BYTE data4,BYTE data5){
	BYTE mode[] = { data1, data2, data3, data4, data5 };
	return sendProtocol(mode , 5);
}


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
