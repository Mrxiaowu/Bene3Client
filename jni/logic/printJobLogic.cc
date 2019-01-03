#pragma once
#include "uart/ProtocolSender.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION		// 导入头文件前，需定义该宏
#include "stb_image_write.h"


//打印任务
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static SProtocolData mProtocolData;
static void onUI_init(){
	LOGD("printjob onUI_init !!!\n"); //06FF011F01DA
	sendSampleProtocol(0x06, 0xFF, 0x01, 0x1F, 0x01);
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


static void onUI_hide() { //当界面隐藏时触发

}


static void onUI_quit() {//当界面完全退出时触发

}


static void onProtocolDataUpdate(const SProtocolData &data) { //串口数据回调接口

	if(mProtocolData.page != data.page){
		mProtocolData.page = data.page;
	}
	if(data.page != 9){
		LOGD("当前读取的串口信息中的PageID不为9");
		return;
	} else {
		LOGD("进入打印任务页面");
	}

	if (mProtocolData.imageData != data.imageData) {
		mProtocolData.imageData = data.imageData;
	}
	LOGD("实际数据: %x" , mProtocolData.imageData);

	if (mProtocolData.region != data.region) {
		mProtocolData.region = data.region;
	}
	if(mProtocolData.type != data.type){
		mProtocolData.type = data.type;
	}
	if (mProtocolData.label != data.label) {
		mProtocolData.label = data.label;
	}

	int dw = 200, dh = 200;
	int n = 3;	// rgb

	uint8_t *buffer = (uint8_t *) malloc(dw * dh * n); // 存储转化后的图像数据
	memset(buffer, 0xFF, dw * dh * n);	// 对数组清零

	for(int i =0;i < dh;i++){
		for(int w =0;w < dw;w++){
			if(i < dh/3){
				buffer[i*dw*3+w*3]=buffer[i*dw*3+w*3+1]=buffer[i*dw*3+w*3+2]= 0xFF;
			}else if(i < dh*2/3){
				buffer[i*dw*3+w*3]=buffer[i*dw*3+w*3+1]=buffer[i*dw*3+w*3+2]= 0x00;
			}else{
				buffer[i*dw*3+w*3]=buffer[i*dw*3+w*3+1]=buffer[i*dw*3+w*3+2]=0x00;
			}
		}
	}

	int ret = stbi_write_jpg("/mnt/extsd/3.jpg", dw, dh, n, buffer, 100);
	printf("ret %d\n", ret);

	LOGD("保存完毕");

	if(mProtocolData.region == 16 && mProtocolData.type == 10 && mProtocolData.label == 2){
		LOGD("这是在传输图片");
//		MySaveBmp("/mnt/extsd/2.bmp", rgbbuf, width, height);
	}
}


static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}


static bool onprintJobActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

//返回按钮
static bool onButtonClick_sys_back(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("mainActivity");
	LOGD(" ButtonClick sys_back !!!\n");
	return false;
}


static void onProgressChanged_Seekbar1(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged Seekbar1 %d !!!\n", progress);
}

static bool onButtonClick_cancell(ZKButton *pButton) {
    LOGD(" ButtonClick cancell !!!\n");//09FF012A01CC
    mcancellPtr->setBackgroundPic("/mnt/extsd/ui/bitmap.png");
	sendSampleProtocol(0x09, 0xFF, 0x01, 0x2A, 0x01);
    return false;
}

static bool onButtonClick_stop(ZKButton *pButton) {
    LOGD(" ButtonClick stop !!!\n");//09FF012C01CA
    mstopPtr->setBackgroundPic("/mnt/extsd/3.jpg");
    sendSampleProtocol(0x09, 0xFF, 0x01, 0x2C, 0x01);
    return false;
}
