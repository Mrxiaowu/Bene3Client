#pragma once
#include "uart/ProtocolSender.h"

//文件管理

void initPrintableStatus(){
	mfileList1Ptr->setSelected(false);
	mfileList2Ptr->setSelected(false);
	mfileList3Ptr->setSelected(false);
}


void initPublicPageStatus() {
	mButton1Ptr->setSelected(false);
	mButton2Ptr->setSelected(false);
	mButton3Ptr->setSelected(false);
	mButton4Ptr->setSelected(false);
	mButton5Ptr->setSelected(false);
	mButton6Ptr->setSelected(false);
	mButton1Ptr->setText("");
	mButton2Ptr->setText("");
	mButton3Ptr->setText("");
	mButton4Ptr->setText("");
	mButton5Ptr->setText("");
	mButton6Ptr->setText("");

}

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


static SProtocolData mProtocolData;
static void onUI_init(){
	mProtocolData = getProtocolData(); // 初始化串口数据的结构体。
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
	LOGD("printables onUI_show !!!\n"); //00FF010201FD
	sendSampleProtocol(0x00, 0xFF, 0x01, 0x02, 0x01);
	initPrintableStatus();
	initPublicPageStatus();
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

	if(data.page != 2 && data.page != 7){
		LOGD("当前读取的串口信息中的PageID不为2也不为7");
		return;
	}

	//TODO 判断文件名的长度，如果长了就启动文字滚动
	//文件管理设置信息
	if(data.page == 2 && data.region == 2 && data.type == 16 && data.label == 1){
		LOGD("当前的buttonIndex=%d",data.buttonIndex);
		if(data.buttonIndex == 0){
			LOGD("mfileList1Ptr!!");
			mfileList1Ptr->setText(data.pdata);
		} else if(data.buttonIndex == 1){
			mfileList2Ptr->setText(data.pdata);
		} else if(data.buttonIndex == 2){
			mfileList3Ptr->setText(data.pdata);
		}
	} else if(data.type == 4){
		mpageNumberPtr->setText(data.pdata);
	}

	//USB页面设置信息
	if(data.page == 2 && data.region == 12 && data.type == 16 && data.label == 0){
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


static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onprintablesActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

//返回按钮
static bool onButtonClick_sys_back(ZKButton *pButton) {
	LOGD(" ButtonClick sys_back !!!\n");
	EASYUICONTEXT->openActivity("mainActivity");
	return true;
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
	musbWindowPtr->setVisible(true);
	return true;
}

static bool onButtonClick_delete(ZKButton *pButton) {
	LOGD(" onButtonClick_delete !!!\n"); //02FF010501F8
	BYTE mode[] = { 0x02, 0xFF, 0x01, 0x05, 0x01 };
	sendProtocol( mode , 5);
	return true;
}

static bool onButtonClick_fileList1(ZKButton *pButton) {
	LOGD(" ??? %d", mfileList1Ptr->isSelected());
	initPrintableStatus();
	mfileList1Ptr->setSelected(true);
	LOGD(" ButtonClick fileList1 !!!\n");//02 FF 10 01 01 00 ED 第一行
	BYTE mode[] = { 0x02, 0xFF, 0x10, 0x01, 0x01, 0x00};
	sendProtocol(mode , 6);
	return true;
}

static bool onButtonClick_fileList2(ZKButton *pButton) {
	initPrintableStatus();
	mfileList2Ptr->setSelected(true);
    LOGD(" ButtonClick fileList2 !!!\n");//02FF10010101EC
	BYTE mode[] = { 0x02, 0xFF, 0x10, 0x01, 0x01, 0x01};
	sendProtocol(mode , 6);
	return true;
}

static bool onButtonClick_fileList3(ZKButton *pButton) {
	initPrintableStatus();
	mfileList3Ptr->setSelected(true);
    LOGD(" ButtonClick fileList3 !!!\n");//AA 55 06 02 FF 10 01 01 02 EB
	BYTE mode[] = { 0x02, 0xFF, 0x10, 0x01, 0x01, 0x02};
	sendProtocol(mode , 6);
    return true;
}

static bool onButtonClick_pageUp(ZKButton *pButton) {//AA 55 05 02 FF 01 08 01 F5
	initPrintableStatus();
	sendSampleProtocol(0x02, 0xFF, 0x01, 0x08, 0x01);
	return true;
}

static bool onButtonClick_pageDown(ZKButton *pButton) {
	initPrintableStatus();
	sendSampleProtocol(0x02, 0xFF, 0x01, 0x09, 0x01);//下页 AA 55 05 02 FF 01 09 01 F4
	return true;
}
static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
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
	musbWindowPtr->setVisible(false);
	initPrintableStatus();
	initPublicPageStatus();
	return false;
}

static bool onButtonClick_pgup(ZKButton *pButton) {//AA 55 05 07 FF 01 31 01 C7
	LOGD(" onButtonClick_pgup !!!\n");
	initPublicPageStatus();
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x31, 0x01 };
	sendProtocol( mode , 5);
	return false;
}

static bool onButtonClick_pgdown(ZKButton *pButton) {//AA 55 05 07 FF 01 32 01 C6
	LOGD(" onButtonClick_pgup !!!\n");
	initPublicPageStatus();
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x32, 0x01 };
	sendProtocol( mode , 5);
	return false;
}

static bool onButtonClick_cancell(ZKButton *pButton) {//AA 55 05 07 FF 01 27 01 D1
	LOGD(" onButtonClick_cancell !!!\n");
	BYTE mode[] = { 0x07, 0xFF, 0x01, 0x27, 0x01 };
	sendProtocol( mode , 5);
	musbWindowPtr->setVisible(false);
	initPrintableStatus();
	initPublicPageStatus();
	return false;
}
