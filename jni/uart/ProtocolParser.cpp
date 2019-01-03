#include <vector>
#include <system/Mutex.h>
#include "CommDef.h"
#include "uart/ProtocolParser.h"
#include "utils/Log.h"
#include <cstddef>
#include <iostream>

static Mutex sLock;
BYTE *mRealData;         //除去AA55和校检码的中间的实际的数据
static std::vector<OnProtocolDataUpdateFun> sProtocolDataUpdateListenerList;

void registerProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		sProtocolDataUpdateListenerList.push_back(pListener);
	}
}

void unregisterProtocolDataUpdateListener(OnProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
	LOGD("unregisterProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		std::vector<OnProtocolDataUpdateFun>::iterator iter =
				sProtocolDataUpdateListenerList.begin();
		for (; iter != sProtocolDataUpdateListenerList.end(); iter++) {
			if ((*iter) == pListener) {
				sProtocolDataUpdateListenerList.erase(iter);
				return;
			}
		}
	}
}

static void notifyProtocolDataUpdate(const SProtocolData &data) {
	Mutex::Autolock _l(sLock);
	std::vector<OnProtocolDataUpdateFun>::const_iterator iter =
			sProtocolDataUpdateListenerList.begin();
	for (; iter != sProtocolDataUpdateListenerList.end(); iter++) {
		(*iter)(data);
	}
}

static SProtocolData sProtocolData = {"\0"};

SProtocolData& getProtocolData() {
	return sProtocolData;
}


//BYTE赋值给BYTE
void BYTEToString(const BYTE *pData, UINT len){
	LOGD("串口长度=%d",len);

	UINT pDataStart = 9; //一般是从第9个数据开始读取
	if(pData[6] == 16){
		pDataStart = 10;
	}
	UINT pDataStartIndex = pDataStart - 1;//从起始数据减1是下标值
	BYTE temp[len-pDataStartIndex-1]; //要拼接的数据是总长度减去前面的数值和校检码，即减8再减1

	for(UINT i = pDataStartIndex; i < len-1; i++)
	{
		temp[i-pDataStartIndex]= pData[i];
	}
	LOGD("(char*)temp)=%s",(char*)temp);

	for (UINT i = 0; i < (len-pDataStartIndex-1); ++i) { //发现数据和自己预期的不对时，首先将数据全部打印出来！！
		LOGD("temp1 DEBUG %x", temp[i]);
	}
	LOGD("\n");

	sProtocolData.pdata = (char*)temp;
//	sProtocolData.len = len-1;
//	sProtocolData.pdata[len-1] = '\0';

	sProtocolData.page = pData[4];
	sProtocolData.region = pData[5];
	sProtocolData.type = pData[6];
	sProtocolData.label = pData[7];
	sProtocolData.buttonIndex = pData[8];
}

//获取校验码
BYTE getCheckSum(const BYTE *pData, int len) {

//#ifdef DEBUG_PRO_DATA
//	for (int i = 0; i < len; ++i) {
//		LOGD("%x DEBUG", pData[i]); //修改格式，将输出的16进制字符串修改为大写的
//	}
//	LOGD("\n");
//#endif

	int sum = 0;
	for (int i = 0; i < len; ++i){
		sum += pData[i];
	}
	return (BYTE) (~sum + 1);
}

/**
 * 解析每一帧数据
 */
static void procParse(const BYTE *pData, UINT len) {//在这里pData是一帧的所有数据，len是一帧的总长度

	LOGD("%x 长度ID", pData[2]);// 长度
	LOGD("%x CMD_ID", pData[3]);//CMD_ID
	LOGD("%x PageID", pData[4]);//Page_ID
	LOGD("%x Region_ID", pData[5]);//Region ID
	LOGD("%x Type_ID", pData[6]);//Type ID
	LOGD("%x labelID", pData[7]);//Label ID

	if(pData[2] == 0){ //长度等于0时代表是传输的是图片
		LOGD("当前首先的长度为0，可能为传输图片专用");
		if(pData[5] == 10 && pData[6] == 9 && pData[7] == 16 && pData[8] == 10 && pData[9] == 2){
			LOGD("条件全部满足，是在传输图片");

			UINT pDataStart = 11; //图片是从第9个数据开始读取
			UINT pDataStartIndex = pDataStart - 1;//从起始数据减1是下标值
			BYTE temp[len-pDataStartIndex-1]; //要拼接的数据是总长度减去前面的数值和校检码，即减8再减1

			for(UINT i = pDataStartIndex; i < len-1; i++)
			{
				temp[i-pDataStartIndex] = pData[i];
//				LOGD("pData[i]: %x" , pData[i]); //日志太多，注释掉
			}
			sProtocolData.imageData = (unsigned char*)temp;

			LOGD("sProtocolData.imageData: %x" , temp);
			LOGD("sProtocolData.imageData: %x" , sProtocolData.imageData);

			sProtocolData.page = pData[6]; //9
			sProtocolData.region = pData[7];//16
			sProtocolData.type = pData[8];//10
			sProtocolData.label = pData[9];//2
			LOGD("page:%x region:%x type:%x label:%x",pData[6],pData[7],pData[8],pData[9]);
		}
	} else {
		switch(pData[3]){
			case SWITCH_PAGE:
				LOGD("当前命令为3，为切换页面命令SWITCH_PAGE");
				switch(pData[4]){
					case 0x0c:
						LOGD("开机LOGO，认证信息");
						EASYUICONTEXT->openActivity("logoActivity");
						BYTE mode[] = { 0x0C, 0xFF, 0x0D, 0xFF, 0x02 };
						sendProtocol(mode , 5);
						break;

	//				default:
	//					LOGD("跳转页面命令，不需要再跳转了");
	//					break;
				}
				break;

			case SET_LABEL_VALUE:
				LOGD("当前命令为8，给label赋值");

				LOGD("页面ID=%x",pData[4]);
				BYTEToString(pData,len);

				break;

			default :
				LOGD("未知的命令");
				break;
		}
	}
	notifyProtocolDataUpdate(sProtocolData); // 通知协议数据更新
}


int parseProtocol(const BYTE *pData, UINT len) {

	int lastLength = len; // 剩余数据长度
	int dataLen;	// 数据包长度
	int frameLen;	// 帧的总长度
	int realDataIndex; //实际数据的起始位置

	while (lastLength >= DATA_PACKAGE_MIN_LEN) {
		// 找到一帧数据的数据头并校检
		while ((lastLength >= 2) && ((pData[0] != CMD_HEAD1) || (pData[1] != CMD_HEAD2))) {
			pData++;
			lastLength--;
			continue;
		}

		if (lastLength < DATA_PACKAGE_MIN_LEN) { //但剩余数据的长度不能比最小的还小
			break;
		}
		dataLen = pData[2];  //一般来说长度在第三个字节

		if(dataLen == 0){
			dataLen = MAKEWORD(pData[4],pData[3]);//前面为地位，后面为高位
			realDataIndex = 5; //如果是图片数据，那就是从第5块数据开始算
			frameLen = dataLen + 6; //图片的话的总长度为实际数据加上 头数据 2  长度数据3  校检码 1 也就是加6
		} else {
			realDataIndex = 3; //如果是正常的数据，那就是从第三块数据开始算
			frameLen = dataLen + DATA_PACKAGE_MIN_LEN; //总长度为实际数据加上 头数据 2  长度数据 1  校检码 1 也就是加上这个宏 4
		}
		LOGD("dataLen %x", dataLen);
		mRealData = new BYTE[dataLen];  //除去AA55和校检码的中间的实际的数据

		if (lastLength < frameLen) { //比较长度，如果第一次进来的时候的剩余数据长度和总长度不一致，说明包内筒不全
			break;
		}

		for (int i = 0; i <= dataLen; i++) {
			mRealData[i] = pData[i + realDataIndex];
		}

		LOGD("%x CheckSum1", getCheckSum(mRealData, dataLen));//这里调用了两遍gerchecksum，所以日志中会出现两遍日志
		LOGD("%x 最后的校检码", pData[frameLen - 1]);

#ifdef PRO_SUPPORT_CHECK_SUM
		if (getCheckSum(mRealData, dataLen) == pData[frameLen - 1]) { // 检测校验码
			LOGE("CheckSum successe!!!!!!\n");
			procParse(pData, frameLen); // 解析一帧数据,在这里可以写业务逻辑
		} else {
			LOGE("CheckSum error!!!!!!\n");
		}
#else
		procParse(pData, frameLen);
#endif

		delete mRealData;

		pData += frameLen;
		lastLength -= frameLen;
	}
//	LOGE("解析函数完毕，返回");
	return len - lastLength;
}
