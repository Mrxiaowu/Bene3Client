#pragma once


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


static bool onmainActivityTouchEvent(const MotionEvent &ev) {

	return false;
}

const char* IconTab[]={
		"printablesActivity",
		"printJobActivity",
		"printSettingActivity",
		"systemSettingActivity",
		"networkControlActivity",
		"machineInfoActivity",
		"slcParamActivity"
};

static void onSlideItemClick_Slidewindow1(ZKSlideWindow *pSlideWindow, int index) {
	LOGD("正在滑动窗口");
	if(index <= sizeof(IconTab)/sizeof(char*)){ //这里在这老是提示警告。。。
		EASYUICONTEXT->openActivity(IconTab[index]);
	}
	LOGD(" onSlideItemClick_ Slidewindow1 %d !!!\n", index);
}

