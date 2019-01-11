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

	sProtocolData.page = pData[4];
	sProtocolData.region = pData[5];
	sProtocolData.type = pData[6];
	sProtocolData.label = pData[7];
	sProtocolData.buttonIndex = pData[8];

	if(pData[4] == 9 && pData[5] == 0x11 && pData[6] == 0x01){
		LOGD("确实是更换状态");
		sProtocolData.cancellParam = pData[11];
	}

	std::string tempStr;
	for(UINT i = pDataStartIndex; i < len-1; i++){
		tempStr.append(1, pData[i]);
	}
	sProtocolData.pdata = tempStr;


	LOGD("%x page", pData[4]);// 长度
	LOGD("%x region", pData[5]);//CMD_ID
	LOGD("%x type", pData[6]);//Page_ID
	LOGD("%x label", pData[7]);//Region ID
	LOGD("%x buttonIndex", pData[8]);//Type ID

	LOGD("信息为 %s", sProtocolData.pdata.c_str());
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
	if(pData[2] == 0){ //长度等于0时代表是传输的是图片
		LOGD("当前首先的长度为0，可能为传输图片专用");
		int pDataStart = 11; //图片是从第9个数据开始读取
		int pDataStartIndex = pDataStart - 1;//从起始数据减1是下标值
		int tempLength = len-pDataStartIndex-1;//要拼接的数据是总长度减去前面的数值和校检码，即减8再减1
		BYTE *temp; //
		temp = new BYTE[tempLength];
		LOGD("%x tempLength数据长度", tempLength);//长度应该是datalan的长度减5

		if(pData[5] == 10 && pData[6] == 9 && pData[7] == 16 && pData[8] == 10 && pData[9] == 2){
			LOGD("条件全部满足，是在传输图片");

			for(UINT i = pDataStartIndex; i < len-1; i++)
			{
				temp[tempLength-(i-pDataStartIndex)] = pData[i];
			}

			sProtocolData.imageData = temp;
			sProtocolData.imageLength = tempLength; //一般是AF5
			sProtocolData.page = pData[6]; //9
			sProtocolData.region = pData[7];//16
			sProtocolData.type = pData[8];//10
			sProtocolData.label = pData[9];//2
			LOGD("page:%x region:%x type:%x label:%x",pData[6],pData[7],pData[8],pData[9]);
		}
		notifyProtocolDataUpdate(sProtocolData); // 通知协议数据更新
		delete[] temp;
	} else {
		switch(pData[3]){
			case SWITCH_PAGE:
				LOGD("当前命令为3，为切换页面命令SWITCH_PAGE");
				if(pData[5] == 0xFF && pData[6] == 0xFF && pData[7] == 0xFF){
					switch(pData[4]){
						case Logo_PageID:
							LOGD("开机LOGO，认证信息");
							EASYUICONTEXT->openActivity("mainActivity");
							BYTE mode1[] = { 0x0C, 0xFF, 0x0D, 0xFF, 0x02 };
							sendProtocol(mode1 , 5);
							break;

						case Print_PageID:
							LOGD("跳转到打印页面");
							EASYUICONTEXT->openActivity("printJobActivity");
							break;

						case PublicFile_PageID:
							LOGD("跳转到公共页面");
							EASYUICONTEXT->openActivity("publicWindowActivity");
							break;
					}
					//切换页面时也要将数据赋值
					sProtocolData.page = pData[4];
					sProtocolData.region = pData[5];
					sProtocolData.type = pData[6];
					sProtocolData.label = pData[7];
				} else {
					LOGD("不是切换页面的命令，怎么费事？");
				}
				break;

			case SET_LABEL_VALUE:
				LOGD("页面ID=%x,长度:%d",pData[4],len);
				BYTEToString(pData,len);
				break;

			case SWITCH_REGION:
				LOGD("可能用来更换暂停和停止的状态 %x,%x,%x ",pData[4],pData[5],pData[6]);
				BYTEToString(pData,len);
				break;

			default :
				LOGD("未知的命令");
				break;
		}
		notifyProtocolDataUpdate(sProtocolData); // 通知协议数据更新
	}
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
		LOGD("dataLen %d", dataLen);
		mRealData = new BYTE[dataLen];  //除去AA55和校检码的中间的实际的数据

		if (lastLength < frameLen) { //比较长度，如果第一次进来的时候的剩余数据长度和总长度不一致，说明包内筒不全
			break;
		}


		for (int i = 0; i < dataLen; i++) {
			mRealData[i] = pData[i + realDataIndex];
			LOGD("%d 定位于 %d 此时的数值为 %x", i ,i + realDataIndex,pData[i + realDataIndex]);
		}

		LOGD("%x CheckSum1", getCheckSum(mRealData, dataLen));//这里调用了两遍gerchecksum，所以日志中会出现两遍日志
		LOGD("%x 最后的校检码", pData[frameLen - 1]);
		LOGD("%d 一帧的总长度 %d", frameLen,dataLen+3); //应该是dataLen 加上 4

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
