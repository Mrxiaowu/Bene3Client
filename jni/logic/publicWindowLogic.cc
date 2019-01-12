#pragma once
#include "uart/ProtocolSender.h"


static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发,一般只会初始化一次
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	LOGD("publicWindow onUI_init");

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
	//还是不能每次打印页面都这样
//	LOGD("publicWindow onUI_show");
//	BYTE mode[] = { 0x06, 0xFF, 0x01, 0x36, 0x01};
//	sendProtocol( mode , 5);
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


static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onpublicWindowActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

static void initPublicPageStatus() {
	mButton1Ptr->setSelected(false);
	mButton2Ptr->setSelected(false);
	mButton3Ptr->setSelected(false);
	mButton4Ptr->setSelected(false);
	mButton5Ptr->setSelected(false);
	mButton6Ptr->setSelected(false);
}

static bool onButtonClick_Button1(ZKButton *pButton) {//AA 55 06 07 FF 10 00 01 00 E9
	LOGD(" onButtonClick_Button1 !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x10, 0x00, 0x01 ,0x00 };
	sendProtocol( mode , 6);
	initPublicPageStatus();
	mButton1Ptr->setSelected(true);
	return false;
}

static bool onButtonClick_Button6(ZKButton *pButton) {//AA 55 06 07 FF 10 00 01 05 E4
	LOGD(" onButtonClick_Button6 !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x10, 0x00, 0x01 ,0x05 };
	sendProtocol( mode , 6);
	initPublicPageStatus();
	mButton6Ptr->setSelected(true);
	return false;
}

static bool onButtonClick_Button5(ZKButton *pButton) {//AA 55 06 07 FF 10 00 01 04 E5
	LOGD(" onButtonClick_Button5 !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x10, 0x00, 0x01 ,0x04 };
	sendProtocol( mode , 6);
	initPublicPageStatus();
	mButton5Ptr->setSelected(true);
	return false;
}

static bool onButtonClick_Button4(ZKButton *pButton) {//AA 55 06 07 FF 10 00 01 03 E6
	LOGD(" onButtonClick_Button4 !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x10, 0x00, 0x01 ,0x03 };
	sendProtocol( mode , 6);
	initPublicPageStatus();
	mButton4Ptr->setSelected(true);
	return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {//AA 55 06 07 FF 10 00 01 01 E8
	LOGD(" onButtonClick_Button2 !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x10, 0x00, 0x01 ,0x01 };
	sendProtocol( mode , 6);
	initPublicPageStatus();
	mButton2Ptr->setSelected(true);
	return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {//AA 55 06 07 FF 10 00 01 02 E7
	LOGD(" onButtonClick_Button3 !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x10, 0x00, 0x01 ,0x02 };
	sendProtocol( mode , 6);
	initPublicPageStatus();
	mButton3Ptr->setSelected(true);
	return false;
}

static bool onButtonClick_sure(ZKButton *pButton) {//AA 55 05 07 FF 01 26 01 D2
	LOGD(" onButtonClick_sure !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x26, 0x01 };
	sendProtocol( mode , 5);
	return false;
}

static bool onButtonClick_pgup(ZKButton *pButton) {//AA 55 05 07 FF 01 31 01 C7
	LOGD(" onButtonClick_pgup !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x31, 0x01 };
	sendProtocol( mode , 5);
	return false;
}

static bool onButtonClick_pgdown(ZKButton *pButton) {//AA 55 05 07 FF 01 32 01 C6
	LOGD(" onButtonClick_pgup !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x32, 0x01 };
	sendProtocol( mode , 5);
	return false;
}

static bool onButtonClick_cancell(ZKButton *pButton) {//AA 55 05 07 FF 01 27 01 D1
	LOGD(" onButtonClick_cancell !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x27, 0x01 };
	sendProtocol( mode , 5);
	return false;
}


