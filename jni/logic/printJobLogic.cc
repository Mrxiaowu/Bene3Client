#pragma once
#include "uart/ProtocolSender.h"

typedef struct                       /**** BMP file header structure ****/
{
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
} BITMAPFILEHEADER;

typedef struct                       /**** BMP file info structure ****/
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

void MySaveBmp(const char *filename,unsigned char *rgbbuf,int width,int height)
{
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    /* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
    unsigned short bfType=0x4d42;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfSize = 2+sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+width*height*3;
    bfh.bfOffBits = 0x36;

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 5000;
    bih.biYPelsPerMeter = 5000;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Could not write file\n");
        return;
    }

    /*Write headers*/
    fwrite(&bfType,sizeof(bfType),1,file);
    fwrite(&bfh,sizeof(bfh),1, file);
    fwrite(&bih,sizeof(bih),1, file);

    fwrite(rgbbuf,width*height*3,1,file);
    fclose(file);
}

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

	if(mProtocolData.region == 16 && mProtocolData.type == 10 && mProtocolData.label == 2){
		LOGD("这是在传输图片");
		MySaveBmp("/mnt/extsd/1.png", mProtocolData.imageData, 200, 112);
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
    sendSampleProtocol(0x09, 0xFF, 0x01, 0x2C, 0x01);
//    mstopPtr->setBackgroundPic("/mnt/extsd/ui/bitmap.png");
    mstopPtr->setBackgroundPic("/mnt/extsd/1.png");
    return false;
}
