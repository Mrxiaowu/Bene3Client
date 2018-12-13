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

static SProtocolData sProtocolData = {"", 0 };

SProtocolData& getProtocolData() {
	return sProtocolData;
}

//获取校验码
BYTE getCheckSum(const BYTE *pData, int len) {

#ifdef DEBUG_PRO_DATA
	for (int i = 0; i < len; ++i) {
		LOGD("%x DEBUG", pData[i]); //修改格式，将输出的16进制字符串修改为大写的
	}
	LOGD("\n");
#endif

	int sum = 0;
	for (int i = 0; i < len; ++i) {
		sum += pData[i];
	}

	return (BYTE) (~sum + 1);
}

/**
 * 解析每一帧数据
 */
static void procParse(const BYTE *pData, UINT len) {//在这里pData是一帧的所有数据，len是一帧的总长度

//	switch (MAKEWORD(pData[2], pData[3])) {
//		case CMDID_POWER:
//			sProtocolData.power = pData[5];
//			LOGD("power status:%d",sProtocolData.power);
//			break;
//		}

	LOGD("%x pData[2]", pData[2]);// 长度
	LOGD("%x pData[3]", pData[3]);//CMD_ID
	LOGD("%x pData[4]", pData[4]);//Page_ID
	LOGD("%x pData[5]", pData[5]);//Region ID
	LOGD("%x pData[6]", pData[6]);//Type ID
	LOGD("%x pData[7]", pData[7]);//Label ID

	switch(pData[3]){
		case SWITCH_PAGE:
			LOGD("当前命令为3，为切换页面命令SWITCH_PAGE");
			switch(pData[4]){
				case 0x05:
					LOGD("需要跳转到networkPage页面，但这个屏幕不需要跳转了");
					break;

				case 0x0c:
					LOGD("开机LOGO，认证信息");
					EASYUICONTEXT->openActivity("logoActivity");
					BYTE mode[] = { 0x0C, 0xFF, 0x0D, 0xFF, 0x02 };
					sendProtocol(mode , 5);
					break;
			}
			break;

		case SET_LABEL_VALUE:
			LOGD("当前命令为8，给label赋值");
			switch (pData[7]){
				case NetWorkControl_CurrentWifiValueLabelID:
					LOGD("%x pData[7]",pData[7]);

					std::string newString;
					for(UINT i = 8; i < len-1; i++)
					{
						std::string byte(1, pData[i]);
					    char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
					    newString.push_back(chr);
					}
					LOGD("%s newString", newString);




					BYTE temp = 0;
					for(UINT i = 8; i < len-1; i++)
					{
						temp = MAKEWORD(pData[i],pData[i+1]);
					}
					sProtocolData.textStr = newString;

					std::cout << "Value of str is : " << std::endl;

					break;
			}
//			switch (pData[4]){
//				case NetworkControl_PageID:
//					LOGD("进入网络信息页面");
//					break;
//
//				case MachineInfo_PageID:
//					LOGD("进入网络信息页面");
//					break;
//			}
			break;

		default :
			LOGD("未知的命令");
			break;
	}

	// 通知协议数据更新
	notifyProtocolDataUpdate(sProtocolData);
}

//  AA 55 +长度+CMD+PageID+FF FF FF +Check Sum`mer
int parseProtocol(const BYTE *pData, UINT len) {

	int remainLen = len;	// 剩余数据长度
	int dataLen;	// 数据包长度
	int frameLen;	// 帧长度

	while (remainLen >= DATA_PACKAGE_MIN_LEN) {
		// 找到一帧数据的数据头
		while ((remainLen >= 2) && ((pData[0] != CMD_HEAD1) || (pData[1] != CMD_HEAD2))) {
			pData++;
			remainLen--;
			continue;
		}

		if (remainLen < DATA_PACKAGE_MIN_LEN) {
			break;
		}

		dataLen = pData[2];  //长度在第三个字节
		frameLen = dataLen + DATA_PACKAGE_MIN_LEN; //总长度为实际数据加上 头数据 2  长度数据 1  校检码 1 也就是加4
		if (remainLen < frameLen) { //比较长度，如果第一次进来的时候的剩余数据长度和总长度不一致，说明包内筒不全
			break;
		}

//		// 打印一帧数据，需要时在CommDef.h文件中打开DEBUG_PRO_DATA宏,打开之后会有很多日志，可以先注释
//#ifdef DEBUG_PRO_DATA
//		for (int i = 0; i < frameLen; ++i) {
//			LOGD("%x ", pData[i]);
//		}
//		LOGD("\n");
//#endif

		mRealData = new BYTE[dataLen];  //除去AA55和校检码的中间的实际的数据

		for (int i = 0; i <= dataLen; i++) {
			mRealData[i] = pData[i + 3];
		}

////实际数据的打印日志
//#ifdef DEBUG_PRO_DATA
//		for (int i = 0; i < dataLen; ++i) {
//			LOGD("%x mRealData", mRealData[i]);
//		}
//		LOGD("\n");
//#endif

		LOGD("%x CheckSum1", getCheckSum(mRealData, dataLen));//这里调用了两遍gerchecksum，所以日志中会出现两遍日志
		LOGD("%x CheckSum2", pData[frameLen - 1]);

#ifdef PRO_SUPPORT_CHECK_SUM

		if (getCheckSum(mRealData, dataLen) == pData[frameLen - 1]) { // 检测校验码
			procParse(pData, frameLen); // 解析一帧数据,在这里可以写业务逻辑
			LOGE("CheckSum successe!!!!!!\n");
		} else {
			LOGE("CheckSum error!!!!!!\n");
		}
#else
		procParse(pData, frameLen);
#endif

		pData += frameLen;
		remainLen -= frameLen;
	}
	return len - remainLen;
}


void hex_to_str(char *ptr,unsigned char *buf,int len)
{
	for(int i = 0; i < len; i++)
	{
		sprintf(ptr, "%02x",buf[i]);
		ptr += 2;
	}
}


// 转化十六进制编码为字符串
//    public static String toStringText(String s) {
//        byte[] baKeyword = new byte[s.length() / 2];
//        for (int i = 0; i < baKeyword.length; i++) {
//            try {
//                baKeyword[i] = (byte) (0xff & Integer.parseInt(s.substring(
//                        i * 2, i * 2 + 2), 16));
//            } catch (Exception e) {
//                e.printStackTrace();
//            }
//        }
//        try {
//            s = new String(baKeyword, "GB2312");// UTF-16le:Not
//        } catch (Exception e1) {
//            e1.printStackTrace();
//        }
//        return s;
//    }

//int parseProtocol(const BYTE *pData, UINT len) {
//	UINT remainLen = len;	// 剩余数据长度
//	UINT dataLen;	// 数据包长度
//	UINT frameLen;	// 帧长度
//
//	/**
//	 * 以下部分需要根据协议格式进行相应的修改，解析出每一帧的数据
//	 */
//	while (remainLen >= DATA_PACKAGE_MIN_LEN) {
//		// 找到一帧数据的数据头
//		while ((remainLen >= 2) && ((pData[0] != CMD_HEAD1) || (pData[1] != CMD_HEAD2))) {
//			pData++;
//			remainLen--;
//			continue;
//		}
//
//		if (remainLen < DATA_PACKAGE_MIN_LEN) {
//			break;
//		}
//
//		dataLen = pData[4];
//		frameLen = dataLen + DATA_PACKAGE_MIN_LEN;
//		if (frameLen > remainLen) {
//			// 数据内容不全
//			break;
//		}
//
//		// 打印一帧数据，需要时在CommDef.h文件中打开DEBUG_PRO_DATA宏
//#ifdef DEBUG_PRO_DATA
//		for (int i = 0; i < frameLen; ++i) {
//			LOGD("%x ", pData[i]);
//		}
//		LOGD("\n");
//#endif
//
//		// 支持checksum校验，需要时在CommDef.h文件中打开PRO_SUPPORT_CHECK_SUM宏
//#ifdef PRO_SUPPORT_CHECK_SUM
//		// 检测校验码
//		if (getCheckSum(pData, frameLen - 1) == pData[frameLen - 1]) {
//			// 解析一帧数据
//			procParse(pData, frameLen);
//		} else {
//			LOGE("CheckSum error!!!!!!\n");
//		}
//#else
//		// 解析一帧数据
//		procParse(pData, frameLen);
//#endif
//
//		pData += frameLen;
//		remainLen -= frameLen;
//	}
//
//	return len - remainLen;
//}
