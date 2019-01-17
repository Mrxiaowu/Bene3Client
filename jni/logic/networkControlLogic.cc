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
	if(data.page != 5 && data.page != 7){
		LOGD("当前读取的串口信息中的PageID不为6或者7");
		return;
	}

	if(data.region == 6){
		if(data.type == 4){
			if(data.label == 10){
				mcurrentWIFITextPtr->setText(data.pdata);
			}
		}
	} else if(data.region == 7){
		if(data.type == 4){
			if(data.label == 12){
				mstaticipTextPtr->setText(data.pdata);
			}else if (data.label == 14){
				mdynamicIPTextPtr->setText(data.pdata);
			}
		}
	}

	if(data.page == 7 && data.region == 0xFF && data.type == 0xFF && data.label == 0xFF){
		mnetworkWindowPtr->setVisible(true);
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
	LOGD(" ButtonClick sys_back !!!\n");
	EASYUICONTEXT->openActivity("mainActivity");
	return true;
}


static bool onButtonClick_sure(ZKButton *pButton) {//AA 55 05 05 FF 01 1C 01 DE
	LOGD(" 网络控制的保存 !!!\n");
	sendSampleProtocol(0x05, 0xFF, 0x01, 0x1C, 0x01);
    return true;
}


static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}

static bool onButtonClick_networkSetting(ZKButton *pButton) {
    //LOGD(" ButtonClick networkSetting !!!\n");
    return false;
}

//仿照这个格式，这里在app后台也要进行定义好
//AA 55 17 47 58 48 32 30 31 52 54 33 35 49 43 34 38 33 32 5F 31 2E 30 2E 31 31 3F
static void onEditTextChanged_passwordButton(const std::string &text) {
	LOGD(" 正在输入键盘值 %s 密码长度 %d", text.c_str(),strlen(text.c_str()));

	UINT passWordLength = strlen(text.c_str()) + 1;
	BYTE passwordData[passWordLength];

	passwordData[0] = 0x48; //增加自己定的协议值为48
	for (UINT i = 1; i <= (strlen(text.c_str())); i++) {
//		LOGD("text %x", text.c_str()[i-1]);
		passwordData[i] = text.c_str()[i-1];
	}

	for (UINT i = 0; i < passWordLength; i++) {
		LOGD("passwordData %x", passwordData[i]);//第一个应该为48
	}
	sendProtocol(passwordData , passWordLength);
}

static bool onButtonClick_pointButton(ZKButton *pButton) {
	LOGD(" onButtonClick_USB !!!\n"); //02FF010701F6
	BYTE mode[] = { 0x02, 0xFF, 0x01, 0x07, 0x01 };
	sendProtocol( mode , 5);
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
	mnetworkWindowPtr->setVisible(false);
	return false;
}


static bool onButtonClick_publicSure(ZKButton *pButton) {
    LOGD(" ButtonClick publicSure !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x26, 0x01 };
	sendProtocol( mode , 5);
	mnetworkWindowPtr->setVisible(false);
    return false;
}
