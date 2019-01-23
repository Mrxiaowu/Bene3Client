#pragma once
#include "uart/ProtocolSender.h"
#include "utils/BrightnessHelper.h"


/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	int brightness = BRIGHTNESSHELPER->getBrightness();

	LOGD("当前亮度值为 %d",brightness);
	// 设置亮度值  brightness: 0 ~ 100
	BRIGHTNESSHELPER->setBrightness(brightness);

	mSeekBar1Ptr->setProgress(brightness);
	mSeekBar1Ptr->getProgress();
	mTextValuePtr->setText(brightness);
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


static void onUI_hide() {

}


static void onUI_quit() {

}


static void onProtocolDataUpdate(const SProtocolData &data) {

}


static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onscreenActivityTouchEvent(const MotionEvent &ev) {
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
static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
    //LOGD(" ButtonClick sys_back !!!\n");
    return false;
}

static void onProgressChanged_SeekBar1(ZKSeekBar *pSeekBar, int progress) {
    LOGD(" ProgressChanged SeekBar1 %d !!!\n", progress);
    mSeekBar1Ptr->setProgress(progress);
    mSeekBar1Ptr->getProgress();
	mTextValuePtr->setText(progress);
	BRIGHTNESSHELPER->setBrightness(progress);
}
