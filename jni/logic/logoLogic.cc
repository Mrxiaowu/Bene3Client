#pragma once
#include "uart/ProtocolSender.h"
#include "uart/ProtocolData.h"
#include "uart/ProtocolData.h"
#include "utils/BrightnessHelper.h"

//class JumpMainPage : public Thread {
//protected:
//    virtual bool threadLoop(){
//    	LOGD("开始等待30秒");
//    	Thread::sleep(30000);
//    	LOGD("等待结束，打开主页面");
//    	EASYUICONTEXT->openActivity("mainActivity");
//        return false;
//    };
//};
//JumpMainPage jumpMainPage;


static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */

static void onUI_init(){
//	jumpMainPage.run("jumpMainPage");
	LOGD("当前屏幕版本号 %d.%d.%d",VERSIONINFO1,VERSIONINFO2,VERSIONINFO3);
	BRIGHTNESSHELPER->setBrightness(50);
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

static bool onlogoActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

static bool onButtonClick_logo(ZKButton *pButton) {
    //LOGD(" ButtonClick logo !!!\n");
    return false;
}
