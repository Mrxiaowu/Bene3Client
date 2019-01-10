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

	if(data.page != 7){
		LOGD("当前读取的串口信息中的PageID不为2");
		return;
	}

	if(data.region == 12){
		if(data.type == 16){
			if(data.type == 16){
				if(data.label == 0){
					if(data.buttonIndex == 0){
						LOGD("buttonIndex!!");
						mButton1Ptr->setText(data.pdata);
					} else if(data.buttonIndex == 1){
						mButton2Ptr->setText(data.pdata);
					} else if(data.buttonIndex == 2){
						mButton3Ptr->setText(data.pdata);
					} else if(data.buttonIndex == 3){
						mButton4Ptr->setText(data.pdata);
					} else if(data.buttonIndex == 4){
						mButton5Ptr->setText(data.pdata);
					} else if(data.buttonIndex == 5){
						mButton6Ptr->setText(data.pdata);
					}
				}
			}
		}
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
static bool onpublicWindowActivityTouchEvent(const MotionEvent &ev) {

	return false;
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button6(ZKButton *pButton) {
    //LOGD(" ButtonClick Button6 !!!\n");
    return false;
}

static bool onButtonClick_Button5(ZKButton *pButton) {
    //LOGD(" ButtonClick Button5 !!!\n");
    return false;
}

static bool onButtonClick_Button4(ZKButton *pButton) {
    //LOGD(" ButtonClick Button4 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}

static bool onButtonClick_sure(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" onButtonClick_sure !!!\n");
	return false;
}

static bool onButtonClick_pgup(ZKButton *pButton) {
    //LOGD(" ButtonClick pgup !!!\n");
    return false;
}

static bool onButtonClick_pgdown(ZKButton *pButton) {
    //LOGD(" ButtonClick pgdown !!!\n");
    return false;
}

static bool onButtonClick_cancell(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" onButtonClick_cancell !!!\n");
	return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    //LOGD(" ButtonClick Button3 !!!\n");
    return false;
}
