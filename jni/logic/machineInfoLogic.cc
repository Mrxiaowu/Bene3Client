#pragma once
#include "uart/ProtocolSender.h"


static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

static SProtocolData mProtocolData;
static void onUI_init(){
	mProtocolData = getProtocolData(); // 初始化串口数据的结构体。
	// 开始初始化页面的UI显示

	LOGD("machineInfo onUI_init !!!\n"); //06FF011F01DA
	BYTE mode[] = { 0x06, 0xFF, 0x01, 0x1F, 0x01 };
	sendProtocol( mode , 5);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    	LOGD("2!!!\n"); //进不了
    }
//    msnsidtextPtr->setText("123");
}

/*
 * 当界面显示时触发
 */
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


static void onProtocolDataUpdate(const SProtocolData &data) {
	LOGD("%s data.pdata",mProtocolData.pdata);
	if (mProtocolData.pdata != data.pdata) {
		mProtocolData.pdata = data.pdata;
	}
	msnsidtextPtr->setText(mProtocolData.pdata);
	LOGD("%s data.pdata",mProtocolData.pdata);
}

static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onmachineInfoActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}
