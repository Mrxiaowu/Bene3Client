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

	if(data.page != 2){
		LOGD("当前读取的串口信息中的PageID不为2");
		return;
	}

//	if (mProtocolData.pdata != data.pdata) {
//		mProtocolData.pdata = data.pdata;
//	}
//	if(mProtocolData.page != data.page){
//		mProtocolData.page = data.page;
//	}
//	if (mProtocolData.region != data.region) {
//		mProtocolData.region = data.region;
//	}
//	if(mProtocolData.type != data.type){
//		mProtocolData.type = data.type;
//	}
//	if(mProtocolData.buttonIndex != data.buttonIndex){
//		mProtocolData.buttonIndex = data.buttonIndex;
//	}
//	LOGD("%s data.pdata",mProtocolData.pdata);


	if(data.type == 16){
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
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
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

static bool onButtonClick_fileList1(ZKButton *pButton) {
	LOGD(" ??? %d", mfileList1Ptr->isSelected());
	mfileList1Ptr->setSelected(true);
	mfileList2Ptr->setSelected(false);
	mfileList3Ptr->setSelected(false);
	LOGD(" ??? %d", mfileList1Ptr->isSelected());
	LOGD(" ButtonClick fileList1 !!!\n");//02FF10010100ED 第一行
	BYTE mode[] = { 0x02, 0xFF, 0x10, 0x01, 0x01, 0x00};
	sendProtocol(mode , 6);
	return true;
}

static bool onButtonClick_fileList2(ZKButton *pButton) {
	mfileList1Ptr->setSelected(false);
	mfileList2Ptr->setSelected(true);
	mfileList3Ptr->setSelected(false);
    LOGD(" ButtonClick fileList2 !!!\n");//02FF10010101EC
	BYTE mode[] = { 0x02, 0xFF, 0x10, 0x01, 0x01, 0x01};
	sendProtocol(mode , 6);
	return true;
}

static bool onButtonClick_fileList3(ZKButton *pButton) {
	mfileList1Ptr->setSelected(false);
	mfileList2Ptr->setSelected(false);
	mfileList3Ptr->setSelected(true);
    LOGD(" ButtonClick fileList3 !!!\n");//02FF10010102EB
	BYTE mode[] = { 0x02, 0xFF, 0x10, 0x01, 0x01, 0x02};
	sendProtocol(mode , 6);
    return true;
}

static bool onButtonClick_pageUp(ZKButton *pButton) {
	sendSampleProtocol(0x02, 0xFF, 0x01, 0x08, 0x01);//上页 02FF010801F5
	return true;
}

static bool onButtonClick_pageDown(ZKButton *pButton) {
	sendSampleProtocol(0x02, 0xFF, 0x01, 0x09, 0x01);//下页 02FF010901F4
	return true;
}
static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}
