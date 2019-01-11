#pragma once
#include "uart/ProtocolSender.h"


//SLC参数设置

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


static void onUI_init(){
	LOGD("slcParam onUI_init !!!\n"); //00FF010301FC
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x14, 0x01);//03FF011401E8
}


static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}


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

/**
 * 定时器触发函数
 * 不建议在此函数中写耗时操作，否则将影响UI刷新
 * 参数： id
 *         当前所触发定时器的id，与注册时的id相同
 * 返回值: true
 *             继续运行当前定时器
 *         false
 *             停止运行当前定时器
 */
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
static bool onslcParamActivityTouchEvent(const MotionEvent &ev) {

	return false;
}
static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return true;
}
static bool onButtonClick_ADDBUTTONbutton2(ZKButton *pButton) {
    //LOGD(" ButtonClick ADDBUTTONbutton2 !!!\n");
    return false;
}

static bool onButtonClick_ADDBUTTONbutton1(ZKButton *pButton) {
    //LOGD(" ButtonClick ADDBUTTONbutton1 !!!\n");
    return false;
}

static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    //LOGD(" ButtonClick Button3 !!!\n");
    return false;
}

static bool onButtonClick_Button4(ZKButton *pButton) {
    //LOGD(" ButtonClick Button4 !!!\n");
    return false;
}

static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}

static bool onButtonClick_Button5(ZKButton *pButton) {
    //LOGD(" ButtonClick Button5 !!!\n");
    return false;
}

static bool onButtonClick_Button6(ZKButton *pButton) {
    //LOGD(" ButtonClick Button6 !!!\n");
    return false;
}

static bool onButtonClick_Button7(ZKButton *pButton) {
    //LOGD(" ButtonClick Button7 !!!\n");
    return false;
}

static bool onButtonClick_Button8(ZKButton *pButton) {
    //LOGD(" ButtonClick Button8 !!!\n");
    return false;
}

static bool onButtonClick_save(ZKButton *pButton) {
    //LOGD(" ButtonClick save !!!\n");
    return false;
}
