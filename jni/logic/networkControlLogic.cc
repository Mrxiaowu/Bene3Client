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
	if (mProtocolData.pdata != data.pdata) {
		mProtocolData.pdata = data.pdata;
	}

	LOGD("%s data.pdata",mProtocolData.pdata);

	if (mProtocolData.region != data.region) {
		mProtocolData.region = data.region;

	}

	if(mProtocolData.region == 16){   //这里要用10进制数来运算？
		LOGD("region == 16");
		mmodeltextPtr->setText(mProtocolData.pdata);
	} else if (mProtocolData.region == 18){
		LOGD("region == 18");
		msnsidtextPtr->setText(mProtocolData.pdata);
	} else if(mProtocolData.region == 20){
		LOGD("region == 20");
		mversiontext1Ptr->setText(mProtocolData.pdata);
	} else if(mProtocolData.region == 32){
		LOGD("region == 32");
		mversiontext2Ptr->setText(mProtocolData.pdata);
	}

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
static bool onnetworkControlActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}

static void onEditTextChanged_Edittext1(const std::string &text) {
    //LOGD(" onEditTextChanged_ Edittext1 %s !!!\n", text.c_str());
}
