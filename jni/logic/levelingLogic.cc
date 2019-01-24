#pragma once
#include "uart/ProtocolSender.h"


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
static void onUI_show() {//AA 55 05 03 FF 01 35 01 C7
	BYTE mode[] = { 0x03, 0xFF, 0x01, 0x35, 0x01};
	sendProtocol( mode , 5);
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

static bool onlevelingActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			break;
		default:
			break;
	}
	return false;
}
static bool onButtonClick_sys_back(ZKButton *pButton) {//AA 55 05 0E FF 01 3C 01 B5
	BYTE mode[] = { 0x0E, 0xFF, 0x01, 0x3C, 0x01};
	sendProtocol( mode , 5);
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return true;
}

static bool onButtonClick_zero(ZKButton *pButton) {//AA 55 05 0E FF 01 37 01 BA
    LOGD(" ButtonClick zero !!!\n");
	BYTE mode[] = { 0x0E, 0xFF, 0x01, 0x37, 0x01};
	sendProtocol( mode , 5);
    return false;
}

static bool onButtonClick_up5(ZKButton *pButton) {//AA 55 05 0E FF 01 38 01 B9
    //LOGD(" ButtonClick up5 !!!\n");
	BYTE mode[] = { 0x0E, 0xFF, 0x01, 0x38, 0x01};
	sendProtocol( mode , 5);
    return false;
}

static bool onButtonClick_save(ZKButton *pButton) {//AA 55 05 0E FF 01 39 01 B8
    //LOGD(" ButtonClick save !!!\n");
	BYTE mode[] = { 0x0E, 0xFF, 0x01, 0x39, 0x01};
	sendProtocol( mode , 5);
    return false;
}
static bool onButtonClick_down5(ZKButton *pButton) {//AA 55 05 0E FF 01 3A 01 B7
    //LOGD(" ButtonClick down5 !!!\n");
	BYTE mode[] = { 0x0E, 0xFF, 0x01, 0x3A, 0x01};
	sendProtocol( mode , 5);
    return false;
}
static bool onButtonClick_reset(ZKButton *pButton) {//AA 55 05 0E FF 01 3B 01 B6
    //LOGD(" ButtonClick reset !!!\n");
	BYTE mode[] = { 0x0E, 0xFF, 0x01, 0x3B, 0x01};
	sendProtocol( mode , 5);
    return false;
}

static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}



