
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <termio.h>
#include <sys/ioctl.h>
#include "os/UpgradeMonitor.h"

#include "uart/UartContext.h"
#include "utils/Log.h"

#include <iostream>
#include <fstream>
#include<sys/stat.h>
#include<sys/types.h>



#define UART_DATA_BUF_LEN			16384	// 16KB
#define max_buffer_size   1024   /*定义缓冲区最大宽度*/  //为什么这里设置成1024不行？？



class DownloadThread : public Thread {
protected:
    virtual bool threadLoop(){
        UpgradeMonitor::getInstance()->checkUpgradeFile("/mnt/extsd/temp");
        return false;
    };
};

DownloadThread downloadThread;


extern int parseProtocol(const BYTE *pData, UINT len);

UartContext::UartContext() :
	mIsOpen(false),
	mUartID(0),
	mDataBufPtr(NULL),
	mDataBufLen(0) ,
	upgradeSize(0)
{

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
	char *hd[max_buffer_size]; /*定义接收缓冲区*/
	int retv,ncount=0;
	FILE* fp;

	system("mkdir /mnt/extsd/temp");

	if((fp=fopen("/mnt/extsd/temp/update.img","wb"))==NULL){
		LOGD("can not open/create file serialdata.");
	}
	LOGD("ready for receiving data...\n");

	Thread::sleep(5000);//

	int i = 0;
	retv=read(mUartID,hd,max_buffer_size);   /*接收数据*/
	while(retv>0) {
	    LOGD("最开始的 receive data size=%d\n",retv);
	    ncount+=retv;
	    i++;

	    //缓冲区的操作
//	    if(retv>1 && hd[retv-1]!='\0'){
//			fwrite(hd,retv,1,fp);//write to the file serialdata
//	    }else if(retv>1 && hd[retv-1]=='\0'){
//	    	LOGD("中止1");
//		    fwrite(hd,retv-1,1,fp);//data end with stop sending signal
//			break;
//        }else if(retv==1 && hd[retv-1]=='\0'){//单独收到终止信号
//			LOGD("中止2");
//			break;
//		}

		fwrite(hd,retv,1,fp);
		Thread::sleep(50);
		retv=read(mUartID,hd,max_buffer_size);

		if(retv <= 0){
			LOGD("检测到串口读不到信息，再等一会儿");
			Thread::sleep(2000);
			retv=read(mUartID,hd,max_buffer_size);
		}
	}
	LOGD("The received data size is:%d  +  %d",ncount,i);

	if(upgradeSize == ncount){
		LOGD("发来的包的正常，升级并重启");
		system("touch /mnt/extsd/zkautoupgrade");
		downloadThread.run("download-update");
	} else {
		LOGD("发来的包的长度和预计的包长度不等  发过来的包信息%d 实际接受的包%d ",upgradeSize,ncount);
		system("reboot");
	}
}
