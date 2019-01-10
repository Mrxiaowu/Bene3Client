#pragma once
#include "uart/ProtocolSender.h"

//网络控制

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


 //当界面构造时触发
static SProtocolData mProtocolData;
static void onUI_init(){
	mProtocolData = getProtocolData(); // 初始化串口数据的结构体。
	LOGD("machineInfo onUI_init !!!\n"); //00FF010101FE
	sendSampleProtocol(0x00, 0xFF, 0x01, 0x01, 0x01);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}


//当界面显示时触发

static void onUI_show() {

}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {
	if(data.page != 5){
		LOGD("当前读取的串口信息中的PageID不为6");
		return;
	}

//	if(mProtocolData.page != data.page){
//		mProtocolData.page = data.page;
//	}
//	if (mProtocolData.pdata != data.pdata) {
//		mProtocolData.pdata = data.pdata;
//	}
//	if (mProtocolData.region != data.region) {
//		mProtocolData.region = data.region;
//	}
//	if(mProtocolData.type != data.type){
//		mProtocolData.type = data.type;
//	}
//	LOGD("%s data.pdata",mProtocolData.pdata);

	LOGD("data.pdata %x", data.pdata);
	if(data.region == 6){
		if(data.type == 4){
			if(data.label == 10){
				mcurrentWIFITextPtr->setText(data.pdata);
			}
		}
	} else if(data.region == 7){
		if(data.type == 4){
			if(data.label == 12){
				mstaticipTextPtr->setText(data.pdata);
			}else if (data.label == 14){
				mdynamicIPTextPtr->setText(data.pdata);
			}
		}
	}
}


static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}

/**
 * 有新的触摸事件时触发
 * 参数：ev
 *         新的触摸事件
 * 返回值：true
 *            表示该触摸事件在此被拦截，系统不再将此触摸事件传递到控件上
 *         false
 *            触摸事件将继续传递到控件上
 */
static bool onnetworkControlActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}


static bool onButtonClick_sure(ZKButton *pButton) {
	LOGD(" 网络控制的保存 !!!\n");
	sendSampleProtocol(0x05, 0xFF, 0x01, 0x1C, 0x01);
    return true;
}

//仿照这个格式，这里在app后台也要进行定义好
//AA 55 17 47 58 48 32 30 31 52 54 33 35 49 43 34 38 33 32 5F 31 2E 30 2E 31 31 3F
static void onEditTextChanged_passwordText(const std::string &text) {
	LOGD(" 正在输入键盘值 %s 密码长度 %d", text.c_str(),strlen(text.c_str()));

	UINT passWordLength = strlen(text.c_str()) + 1;
	BYTE passwordData[passWordLength];

	passwordData[0] = 0x48; //增加自己定的协议值为48
	for (UINT i = 1; i <= (strlen(text.c_str())); i++) {
//		LOGD("text %x", text.c_str()[i-1]);
		passwordData[i] = text.c_str()[i-1];
	}

	for (UINT i = 0; i < passWordLength; i++) {
		LOGD("passwordData %x", passwordData[i]);//第一个应该为48
	}
	sendProtocol(passwordData , passWordLength);
}

static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}

static bool onButtonClick_networkSetting(ZKButton *pButton) {
    //LOGD(" ButtonClick networkSetting !!!\n");
    return false;
}
