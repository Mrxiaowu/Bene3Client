#pragma once
#include "uart/ProtocolSender.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

#define STB_IMAGE_WRITE_IMPLEMENTATION		// 要在导入头文件前，定义该宏
#include "activity/imageWrite.h"



static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static SProtocolData mProtocolData;
static void onUI_init(){
	LOGD("printjob onUI_init !!!\n"); //06FF011F01DA
	sendSampleProtocol(0x06, 0xFF, 0x01, 0x1F, 0x01);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {

}


static void onUI_hide() { //当界面隐藏时触发

}


static void onUI_quit() {//当界面完全退出时触发

}

static string convertHsxStringToNormal(string hexString){
    string Normalstr = "";
    int i;
    for(i=hexString.length() ;i >= 2;i=i-2){
        Normalstr.append(hexString.substr(i-2,2));
    }
    return  Normalstr;
}



//width 宽度 height 长度
static void MySaveJPG() {
//static void MySaveJPG(const char *filename,unsigned char *rgbbuf,int width,int height) {
	const int dw = 200, dh = 112;
	const int n = 3;	// rgb

	int totalsize = dw * dh;
	uint8_t *buffer = (uint8_t *) malloc(totalsize * n); // 存储转化后的图像数据
	memset(buffer, 0xFF, totalsize * n);	// 对数组清零


	//原始字符串
	string hexString = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000380004001FC00060000600000000000000000000000000000078000EE07FC001E0000F00000000000000000000000000000078000EF0FFC10170000F000000000000000000000000000000F8000E78C0830370800F000000000000000000000000000000F8010E1C80830330801D00000000000000000000000000000098010E1E00870338801900000000000000000000000000000098030E0E00070738C03900000000000000000000000000000018070E0E000E0718C03800000000000000000000000000000038070E07000E071CE030000000000000000000000000000000380E0E07000E0E1CE070000000000000000000000000000000381C0E07000E0E0E6070000000000000000000000000000000381C0E07000E0C0E70E000000000000000000000000000000038380E07000E1C0E70E000000000000000000000000000000038700E07000E1C07F0FF00000000000000000000000000000038700E07000E1807F8FF01000000000000000000000000000038E00E0E00073803F8FF01000000000000000000000000000038C00E0E0007B8031C8001000000000000000000000000000038C00F1C8003B0031C8003000000000000000000000000000038800F7CC003F0011C8003000000000000000000000000000038800FF8FF01F0010E0007000000000000000000000000000038000FE07F00E0010E00070000000000000000000000000000180006801F00C0000600060000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000FEFFF83FE01FFF7F0000000000000000000000000000000000FEFFF83FF81FFF7F0000000000000000000000000000000000FE7FF81F7C1CFF7F0000000000000000000000000000000000800338001C00C0010000000000000000000000000000000000800338000E00C0010000000000000000000000000000000000800338000E00C0010000000000000000000000000000000000800338000E00C0010000000000000000000000000000000000800338001C00C0010000000000000000000000000000000000800338003C00C00100000000000000000000000000000000008003F81FF800C00100000000000000000000000000000000008003F81FF003C00100000000000000000000000000000000008003F81FC00FC001000000000000000000000000000000000080033800001FC001000000000000000000000000000000000080033800001CC0010000000000000000000000000000000000800338000038C0010000000000000000000000000000000000800338000038C0010000000000000000000000000000000000800338000038C0010000000000000000000000000000000000800338000038C0010000000000000000000000000000000000800338000E1CC00100000000000000000000000000000000008003F83FFE1FC00100000000000000000000000000000000008003F83FFC07C001000000000000000000000000000000000000000000C00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	//转化后的字符串
	string convertHexString = convertHsxStringToNormal(hexString);


//	LOGD(" convertHexString , %d ", convertHexString.length());

	int strLength = hexString.length();
//	bool ok;
	int strArrayLength = strLength/2;//16进制字符串长度


	//现在就差这里了！！！
	std::vector<uint8_t> hexArray;
	for(int i = 0; i < strArrayLength; i++) {
		hexArray.push_back(strtol(convertHexString.substr(2*i,2).c_str(), NULL, 16));
	}


	int hexArrayLength = strArrayLength*8;//16进制整数长度
	std::vector<uint8_t> hexArray2;
	for(int i=0;i < strArrayLength; i++){
		for(int j=0; j < 8 ;j++){
			bool ret = (hexArray.at(i) >> (7-j)) & 0x01;
			if(ret)
				hexArray2.push_back(0xFF);
			 else
				hexArray2.push_back(0x00);
		}
	}

//	int index = 14264;//用字符个数-1
//	qDebug() << " ??? " << hexArray2;
//	qDebug() << " ??? " << hexArray2.at(index) << hexArray2.at(index+1) << hexArray2.at(index+2)
//			 << hexArray2.at(index+3) << hexArray2.at(index+4) << hexArray2.at(index+5)
//			 << hexArray2.at(index+6) << hexArray2.at(index+7);

//	qDebug() << " hexArray.size " << hexArray.size() << " hexArray2:" << hexArray2.size();
//    qDebug() << " 字符串长 " << strLength << " totalsize:" << totalsize
//             << " 16进制:" << strArrayLength;

	for(int i = 0; i < totalsize; i++) {
		buffer[i*3] = buffer[i*3+1] = buffer[i*3+2] = hexArray2[i];
	}

	int ret = stbi_write_jpg("/mnt/extsd/1.jpg", dw, dh, n, buffer, 100);
	LOGD("ret %d\n", ret);
	free(buffer);
}


static void onProtocolDataUpdate(const SProtocolData &data) { //串口数据回调接口

	if(mProtocolData.page != data.page){
		mProtocolData.page = data.page;
	}
	if(data.page != 9){
		LOGD("当前读取的串口信息中的PageID不为9");
		return;
	} else {
		LOGD("进入打印任务页面");
	}

	if (mProtocolData.imageData != data.imageData) {
		mProtocolData.imageData = data.imageData;
	}
	if (mProtocolData.region != data.region) {
		mProtocolData.region = data.region;
	}
	if(mProtocolData.type != data.type){
		mProtocolData.type = data.type;
	}
	if (mProtocolData.label != data.label) {
		mProtocolData.label = data.label;
	}
//	if (mProtocolData.pdata != data.pdata) {
//		mProtocolData.pdata = data.pdata;
//	}

	//直接用data的是可以的！！！！


	if(mProtocolData.region == 16){
		if(mProtocolData.type == 1){
			if(mProtocolData.label == 45){
				myzhouTextPtr->setText(data.pdata);
			} else if(mProtocolData.label == 46){
				mlayerTextPtr->setText(data.pdata);
			} else if(mProtocolData.label == 47){
				mlayerspeedTextPtr->setText(data.pdata);
			} else if(mProtocolData.label == 48){
				mprintstatusTextPtr->setText(data.pdata);
			}
		} else if(mProtocolData.type == 4 && mProtocolData.label == 22){
			mfilenameTextPtr->setText(data.pdata);
		}
	} else if(mProtocolData.region == 17){
		if(mProtocolData.type == 4 && mProtocolData.label == 23){
			mprinttimeTextPtr->setText(data.pdata);
		} else if(mProtocolData.type == 12 && data.label == 0){

			LOGD("打印进度 %d",mProtocolData.pdata);
			mCirclebar1Ptr->setProgress(16);
		}
	}

	if(mProtocolData.region == 16 && mProtocolData.type == 10 && mProtocolData.label == 2){
		LOGD("这是在传输图片");
		MySaveJPG();
	}
}


static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onprintJobActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

//返回按钮
static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}

//取消按钮
static bool onButtonClick_cancell(ZKButton *pButton) {
    LOGD(" ButtonClick cancell !!!\n");//09FF012A01CC
    mprintImagePtr->setBackgroundPic("/mnt/extsd/ui/480x272.jpg");
	sendSampleProtocol(0x09, 0xFF, 0x01, 0x2A, 0x01);
    return false;
}

//停止按钮
static bool onButtonClick_stop(ZKButton *pButton) {
    LOGD(" ButtonClick stop !!!\n");//09FF012C01CA
    mprintImagePtr->setBackgroundPic("/mnt/extsd/1.jpg");
    sendSampleProtocol(0x09, 0xFF, 0x01, 0x2C, 0x01);
    return false;
}
static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}
