#pragma once
#include "../uart/ProtocolSender.h"

//Bene3

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");

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
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x0A, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_up100(ZKButton *pButton) {
	LOGD(" onButtonClick_up100 !!!\n"); //03FF010B01F1
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x0B, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_up1000(ZKButton *pButton) {
	LOGD(" onButtonClick_up1000 !!!\n"); //03FF010C01F0
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x0C, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_up5000(ZKButton *pButton) {
	LOGD(" onButtonClick_up5000 !!!\n"); //03FF010D01EF
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x0D, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_down5(ZKButton *pButton) {
	LOGD(" onButtonClick_down5 !!!\n"); //03FF010E01EE
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x0E, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_down100(ZKButton *pButton) {
	LOGD(" onButtonClick_down100 !!!\n"); //03FF010F01ED
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x0F, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_dwon1000(ZKButton *pButton) {
	LOGD(" onButtonClick_dwon1000 !!!\n"); //03FF011001EC
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x10, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_down5000(ZKButton *pButton) {
	LOGD(" onButtonClick_down5000 !!!\n"); //03FF011101EB
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x11, 0x01 };
	sendProtocol( mode , 5);
	return true;
}
static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}
