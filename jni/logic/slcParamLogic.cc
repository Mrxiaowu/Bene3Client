#pragma once
#include "uart/ProtocolSender.h"


//SLC参数设置

static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};


static void onUI_init(){
	LOGD("slcParam onUI_init !!!\n"); //00FF010301FC
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x14, 0x01);//03FF011401E8
}


static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}


static void onUI_show() {
	LOGD("slcParam onUI_show !!!\n"); //00FF010301FC
	sendSampleProtocol(0x03, 0xFF, 0x01, 0x14, 0x01);//03FF011401E8

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


static bool onslcParamActivityTouchEvent(const MotionEvent &ev) {

	return false;
}
static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return true;
}


static bool onButtonClick_line(ZKButton *pButton) {
    //LOGD(" ButtonClick line !!!\n");
    return false;
}

static bool onButtonClick_ExposureTimeButtonJia(ZKButton *pButton) {//AA 55 07 04 FF 0F 00 01 28 23 A2
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x28, 0x23 };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_ExposureTimeButtonJian(ZKButton *pButton) { //AA 55 07 04 FF 0F 00 01 58 1B 7A
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomLayersJian(ZKButton *pButton) {// AA 55 07 04 FF 0F 02 01 02 00 E9
	LOGD(" onButtonClick_BottomLayersJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x02, 0x01,0x02, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomLayersJia(ZKButton *pButton) {// AA 55 07 04 FF 0F 02 01 03 00 E8
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomTimeJian(ZKButton *pButton) { // AA 55 07 04 FF 0F 04 01 78 E6 8B
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomTimeJia(ZKButton *pButton) {// AA 55 07 04 FF 0F 04 01 60 EA 9F
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_LiftDistanceJian(ZKButton *pButton) { //AA 55 07 04 FF 0F 01 01 03 00 E9
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_LiftRateJian(ZKButton *pButton) { //AA 55 07 04 FF 0F 03 01 5A 00 90
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_save(ZKButton *pButton) { //AA 55 05 04 FF 01 15 01 E6
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}
static bool onButtonClick_LiftDistanceJia(ZKButton *pButton) { //AA 55 07 04 FF 0F 01 01 04 00 E8
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}
static bool onButtonClick_LiftRateJia(ZKButton *pButton) { //AA 55 07 04 FF 0F 03 01 64 00 86
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}
