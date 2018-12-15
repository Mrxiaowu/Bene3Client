#pragma once
#include "uart/ProtocolSender.h"
#include "uart/ProtocolData.h"

//机器控制，机器信息

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

static SProtocolData mProtocolData;
static void onUI_init(){
	mProtocolData = getProtocolData(); // 初始化串口数据的结构体。
	LOGD("machineInfo onUI_init !!!\n"); //06FF011F01DA    05FF011901E1
	sendSampleProtocol(0x05, 0xFF, 0x01, 0x19, 0x01);
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    	LOGD("2!!!\n"); //进不了
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
