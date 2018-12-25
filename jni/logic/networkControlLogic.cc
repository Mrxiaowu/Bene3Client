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

	if(mProtocolData.page != data.page){
		mProtocolData.page = data.page;
	}

	if (mProtocolData.pdata != data.pdata) {
		mProtocolData.pdata = data.pdata;
	}

	if(mProtocolData.type != data.type){
		mProtocolData.type = data.type;
	}

	if(mProtocolData.page != 5){
		LOGD("当前读取的串口信息中的PageID不为5");
		return;
	}

	LOGD("%s data.pdata",mProtocolData.pdata);

	if(mProtocolData.type == 4){
		LOGD("当前读取的网络管理页面的label=%d",mProtocolData.label);
		if(mProtocolData.label == 10){
			mWifiIPPtr->setText(mProtocolData.pdata);
		} else if(mProtocolData.label == 12){
			mstaticIPTextPtr->setText(mProtocolData.pdata);
		} else if(mProtocolData.label == 14){
			mdynamicIPTextPtr->setText(mProtocolData.pdata);
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

static void onEditTextChanged_accessPointText(const std::string &text) {
    LOGD(" 标准事 %s !!!\n", text.c_str());
}

static bool onButtonClick_sure(ZKButton *pButton) {
	sendSampleProtocol(0x05, 0xFF, 0x01, 0x1C, 0x01);
    return true;
}

static void onEditTextChanged_passwordText(const std::string &text) {
	LOGD(" 正在输入键盘值 %s !!!\n", text.c_str());
}
