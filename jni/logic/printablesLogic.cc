#pragma once
#include "uart/ProtocolSender.h"

//文件管理

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


static SProtocolData mProtocolData;
static void onUI_init(){
	mProtocolData = getProtocolData(); // 初始化串口数据的结构体。
	LOGD("printables onUI_init !!!\n"); //00FF010201FD
	sendSampleProtocol(0x00, 0xFF, 0x01, 0x02, 0x01);
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
static bool onprintablesActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

//返回按钮
static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}
static int getListItemCount_Listview1(const ZKListView *pListView) {
    //LOGD("getListItemCount_Listview1 !\n");
    return 3;
}

static void obtainListItemData_Listview1(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ Listview1  !!!\n");
}

static void onListItemClick_Listview1(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ Listview1  !!!\n");
}

static bool onButtonClick_print(ZKButton *pButton) {
	LOGD(" onButtonClick_print !!!\n");//02FF010601F7
	BYTE mode[] = { 0x02, 0xFF, 0x01, 0x06, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_USB(ZKButton *pButton) {
	LOGD(" onButtonClick_USB !!!\n"); //02FF010701F6
	BYTE mode[] = { 0x02, 0xFF, 0x01, 0x07, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_delete(ZKButton *pButton) {
	LOGD(" onButtonClick_delete !!!\n"); //02FF010501F8
	BYTE mode[] = { 0x02, 0xFF, 0x01, 0x05, 0x01 };
	sendProtocol( mode , 5);
	return true;
}
