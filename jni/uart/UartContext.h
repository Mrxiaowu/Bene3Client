//Bene3

#ifndef _UART_UARTCONTEXT_H_
#define _UART_UARTCONTEXT_H_

#include <vector>
#include "system/Thread.h"
#include "CommDef.h"

class UartContext : public Thread {
public:
	virtual ~UartContext();

	bool openUart(const char *pFileName, UINT baudRate);
	void closeUart();

	bool isOpen() { return mIsOpen; }

	bool send(const BYTE *pData, UINT len);

	static UartContext* getInstance();

	void receiverFile();


protected:
	virtual bool readyToRun();
	virtual bool threadLoop();

private:
	UartContext();

private:
	bool mIsOpen;
	int mUartID;

	// 用于拼接缓存数据，可能存在上一包数据解析未完全，残留有数据
	BYTE *mDataBufPtr;
	int mDataBufLen;
};

#define UARTCONTEXT		UartContext::getInstance()

#endif /* _UART_UARTCONTEXT_H_ */
