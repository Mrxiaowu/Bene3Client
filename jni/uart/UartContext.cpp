//Bene3
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <termio.h>
#include <sys/ioctl.h>

#include "uart/UartContext.h"
#include "utils/Log.h"

#define UART_DATA_BUF_LEN			16384	// 16KB
#define max_buffer_size   100   /*定义缓冲区最大宽度*/



extern int parseProtocol(const BYTE *pData, UINT len);

UartContext::UartContext() :
	mIsOpen(false),
	mUartID(0),
	mDataBufPtr(NULL),
	mDataBufLen(0) {

}

UartContext::~UartContext() {
	delete[] mDataBufPtr;
	closeUart();
}

bool UartContext::openUart(const char *pFileName, UINT baudRate) {
	LOGD("openUart pFileName = %s, baudRate = %d\n", pFileName, baudRate);
	mUartID = open(pFileName, O_RDWR|O_NOCTTY);

	if (mUartID <= 0) {
		mIsOpen = false;
	} else {
		struct termios oldtio = { 0 };
		struct termios newtio = { 0 };
		tcgetattr(mUartID, &oldtio);

		newtio.c_cflag = baudRate|CS8|CLOCAL|CREAD;
		newtio.c_iflag = 0;	// IGNPAR | ICRNL
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;	// ICANON
		newtio.c_cc[VTIME] = 0; /* inter-character timer unused */
		newtio.c_cc[VMIN] = 1; /* blocking read until 1 character arrives */
		tcflush(mUartID, TCIOFLUSH);
		tcsetattr(mUartID, TCSANOW, &newtio);

		// 设置为非阻塞
		fcntl(mUartID, F_SETFL, O_NONBLOCK);

		mIsOpen = run("uart");
		if (!mIsOpen) {
			close(mUartID);
			mUartID = 0;
		}

		LOGD("openUart mIsOpen = %d\n", mIsOpen);
	}

	return mIsOpen;
}

void UartContext::closeUart() {
	LOGD("closeUart mIsOpen: %d...\n", mIsOpen);
	if (mIsOpen) {
		requestExit();

		close(mUartID);
		mUartID = 0;
		mIsOpen = false;
	}
}

bool UartContext::send(const BYTE *pData, UINT len) {
	if (!mIsOpen) {
		return false;
	}

	if (write(mUartID, pData, len) != (int) len) {	// fail
		LOGD("send Fail\n");
		return false;
	}

	// success
//	LOGD("send Success\n");

	return true;
}

UartContext* UartContext::getInstance() {
	static UartContext sUC;
	return &sUC;
}

bool UartContext::readyToRun() {
	if (mDataBufPtr == NULL) {
		mDataBufPtr = new BYTE[UART_DATA_BUF_LEN];
	}

	if (mDataBufPtr == NULL) {
		closeUart();
	}

	return (mDataBufPtr != NULL);
}

bool UartContext::threadLoop() {
	if (mIsOpen) {
		// 可能上一次解析后有残留数据，需要拼接起来
		int readNum = read(mUartID, mDataBufPtr + mDataBufLen, UART_DATA_BUF_LEN - mDataBufLen);

		if (readNum > 0) {
			mDataBufLen += readNum;

			// 解析协议
			int len = parseProtocol(mDataBufPtr, mDataBufLen);
			if ((len > 0) && (len < mDataBufLen)) {
				// 将未解析的数据移到头部
				memcpy(mDataBufPtr, mDataBufPtr + len, mDataBufLen - len);
			}

			mDataBufLen -= len;
		} else {
			Thread::sleep(50);
		}
		return true;
	}
	return false;
}

void UartContext::receiverFile(){
	int flag_close = 0;
	char  hd[max_buffer_size]; /*定义接收缓冲区*/
	int retv,ncount=0;
	FILE* fp;

	///mnt/extsd/screen.bin
	if((fp=fopen("/mnt/extsd/screen","wb"))==NULL){
		LOGD("can not open/create file serialdata.");
	}
	LOGD("ready for receiving data...\n");

	LOGD("1秒");
	Thread::sleep(5000);
	LOGD("5秒");

	retv=read(mUartID,hd,max_buffer_size);   /*接收数据*/
	LOGD("retv %d",retv);

	while(retv>0) {
	   printf("receive data size=%d\n",retv);
	   ncount+=retv;
	   if(retv>1 && hd[retv-1]!='\0'){
			fwrite(hd,retv,1,fp);//write to the file serialdata
	   }else if(retv>1 && hd[retv-1]=='\0'){
			fwrite(hd,retv-1,1,fp);//data end with stop sending signal
			break;
		}
		//单独收到终止信号
		else if(retv==1 && hd[retv-1]=='\0'){
			printf("中止");
			break;
		}
		retv=read(mUartID,hd,max_buffer_size);
	}


	LOGD("The received data size is:%d\n",ncount);  /*print data size*/
	LOGD("\n");
	flag_close =close(mUartID);
	if(flag_close== -1)   /*判断是否成功关闭文件*/
		LOGD("close the Device failur！\n");
	if(fclose(fp)<0)
		LOGD("closing file serialdata fail!");
}
