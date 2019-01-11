#pragma once
#include "../uart/ProtocolSender.h"

//机器控制

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

static SProtocolData mProtocolData;
static void onUI_init(){
	mProtocolData = getProtocolData(); // 初始化串口数据的结构体。
	LOGD("printsetting onUI_init !!!\n"); //00FF010301FC
	sendSampleProtocol(0x00, 0xFF, 0x01, 0x03, 0x01);
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

}

static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onprintSettingActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

static bool onButtonClick_up5(ZKButton *pButton) {
	LOGD(" onButtonClick_up5 !!!\n");//03FF010A01F2
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x0A, 0x01);
	return true;
}

static bool onButtonClick_up100(ZKButton *pButton) {
	LOGD(" onButtonClick_up100 !!!\n"); //03FF010B01F1
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x0B, 0x01);
	return true;
}

static bool onButtonClick_up1000(ZKButton *pButton) {
	LOGD(" onButtonClick_up1000 !!!\n"); //03FF010C01F0
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x0C, 0x01);
	return true;
}

static bool onButtonClick_up5000(ZKButton *pButton) {
	LOGD(" onButtonClick_up5000 !!!\n"); //03FF010D01EF
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x0D, 0x01);
	return true;
}

static bool onButtonClick_down5(ZKButton *pButton) {
	LOGD(" onButtonClick_down5 !!!\n"); //03FF010E01EE
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x0E, 0x01);
	return true;
}

static bool onButtonClick_down100(ZKButton *pButton) {
	LOGD(" onButtonClick_down100 !!!\n"); //03FF010F01ED
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x0F, 0x01);
	return true;
}

static bool onButtonClick_dwon1000(ZKButton *pButton) {
	LOGD(" onButtonClick_dwon1000 !!!\n"); //03FF011001EC
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x10, 0x01);
	return true;
}

static bool onButtonClick_down5000(ZKButton *pButton) {
	LOGD(" onButtonClick_down5000 !!!\n"); //03FF011101EB
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x11, 0x01);
	return true;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return true;
}
static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}

static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}
