#pragma once
#include "uart/ProtocolSender.h"


//SLC参数设置

static int exposureTime = 8000;
static int bottomTime = 60000;
static int bottomLayers = 3;
static int listDistance = 4;
static int listRate = 100;
const static int maxExposureTime = 30000;//普通层最大30秒
const static int mixExposureTime = 0;
const static int maxBottomTime = 1500000;//底层最大150秒
const static int mixBottomTime = 0;
const static int maxBottomLayers = 30;//底层层数最大30层
const static int mixBottomLayers = 0;
const static int maxListDistance = 20;//电机上升距离最大20mm
const static int mixListDistance = 0;
const static int maxListRate = 500;//电机上升下降的速度最大500mm/min
const static int mixListRate = 0;


void reversestr(char*source,char target[],unsigned int length)
{
	unsigned int i;
	for(i=0;i<length;i++)
		target[i]=source[length-1-i];
	target[i]=0;
}
void tohex(unsigned long num,char*hexStr)
{
	unsigned long n=num;
	char hextable[]="0123456789ABCDEF";
	char temphex[16],hex[16];
	unsigned long int i=0;
	while(n)
	{
		temphex[i++]=hextable[n%16];
		n/=16;
	}
	temphex[i]=0;
	reversestr(temphex,hex,i);
	strcpy(hexStr,hex);
}


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

void CharToByte(char* chars, BYTE* bytes, unsigned int count){
    for(unsigned int i = 0; i < count; i++){
        bytes[i] = (BYTE)chars[i];
    }
}

static bool onButtonClick_ExposureTimeButtonJia(ZKButton *pButton) {//AA 55 07 04 FF 0F 00 01 28 23 A2
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((exposureTime + 500) < maxExposureTime){
		exposureTime += 500;
	}
	LOGD("??? %d ??? %x",exposureTime , exposureTime);

//	char hexStr[4];
//	tohex(exposureTime,hexStr);
//
//	int  num = 32424;
//	char hex[4];
//	sprintf(hex, "%x", num);
//	puts(hex);
//	LOGD(" ?? %s",hex);
//
//	BYTE *hexbyte = new BYTE[2];
//	unsigned int i = 1;
//	CharToByte(hex,hexbyte,i);
//	LOGD(" ??? %x %x",hexbyte[0],hexbyte[1]);


//	mADDBUTTONexposureValuePtr->setText(exposureTime);
//	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01, hexbyte[0]};
//	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_ExposureTimeButtonJian(ZKButton *pButton) { //AA 55 07 04 FF 0F 00 01 58 1B 7A
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((exposureTime - 500) > mixExposureTime){
		exposureTime -= 500;
	}
	mADDBUTTONexposureValuePtr->setText(exposureTime);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomLayersJian(ZKButton *pButton) {// AA 55 07 04 FF 0F 02 01 02 00 E9
	LOGD(" onButtonClick_BottomLayersJian !!!\n");
	if((bottomLayers - 1) > mixBottomLayers){
		bottomLayers -= 1;
	}
	mADDBUTTONbottomValuePtr->setText(bottomLayers);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x02, 0x01,0x02, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomLayersJia(ZKButton *pButton) {// AA 55 07 04 FF 0F 02 01 03 00 E8
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((bottomLayers + 1) < maxBottomLayers){
		bottomLayers += 1;
	}
	mADDBUTTONbottomValuePtr->setText(bottomLayers);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomTimeJian(ZKButton *pButton) { // AA 55 07 04 FF 0F 04 01 78 E6 8B
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((bottomTime - 1000) > mixBottomTime){
		bottomTime -= 1000;
	}
	mADDBUTTONBottomTimeValuePtr->setText(bottomTime);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_BottomTimeJia(ZKButton *pButton) {// AA 55 07 04 FF 0F 04 01 60 EA 9F
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((bottomTime + 1000) < maxBottomTime){
		bottomTime += 1000;
	}
	mADDBUTTONBottomTimeValuePtr->setText(bottomTime);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_LiftDistanceJian(ZKButton *pButton) { //AA 55 07 04 FF 0F 01 01 03 00 E9
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((listDistance - 1) > mixListDistance){
		listDistance -= 1;
	}
	mADDBUTTONLiftDistancePtr->setText(listDistance);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}
static bool onButtonClick_LiftDistanceJia(ZKButton *pButton) { //AA 55 07 04 FF 0F 01 01 04 00 E8
	LOGD(" onButtonClick_ExposureTimeButtonJian !!!\n");
	if((listDistance + 1) < maxListDistance){
		listDistance += 1;
	}
	mADDBUTTONLiftDistancePtr->setText(listDistance);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_LiftRateJia(ZKButton *pButton) { //AA 55 07 04 FF 0F 03 01 64 00 86
	LOGD(" onButtonClick_LiftRateJia !!!\n");
	if((listRate + 20) < maxListRate){
		listRate += 20;
	}
	mADDBUTTONlistRatePtr->setText(listRate);
	BYTE mode[] = { 0x04, 0xFF, 0x0F, 0x00, 0x01,0x58, 0x1B };
	sendProtocol( mode , 7);
    return false;
}

static bool onButtonClick_LiftRateJian(ZKButton *pButton) { //AA 55 07 04 FF 0F 03 01 5A 00 90
	LOGD(" onButtonClick_LiftRateJian !!!\n");
	if((listRate - 20) > mixListRate){
		listRate -= 20;
	}
	mADDBUTTONlistRatePtr->setText(listRate);
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
