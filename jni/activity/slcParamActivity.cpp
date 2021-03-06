
#include "slcParamActivity.h"

/*TAG:GlobalVariable全局变量*/
static ZKTextView* mADDBUTTONlistRatePtr;
static ZKTextView* mADDBUTTONLiftDistancePtr;
static ZKTextView* mADDBUTTONBottomTimeValuePtr;
static ZKTextView* mADDBUTTONbottomValuePtr;
static ZKTextView* mADDBUTTONexposureValuePtr;
static ZKButton* mLiftRateJiaPtr;
static ZKButton* mLiftDistanceJiaPtr;
static ZKButton* mLiftRateJianPtr;
static ZKButton* mLiftDistanceJianPtr;
static ZKButton* mBottomTimeJiaPtr;
static ZKButton* mBottomTimeJianPtr;
static ZKButton* mBottomLayersJiaPtr;
static ZKButton* mBottomLayersJianPtr;
static ZKButton* mExposureTimeButtonJianPtr;
static ZKButton* mExposureTimeButtonJiaPtr;
static ZKTextView* mADDBUTTONtext4Ptr;
static ZKTextView* mADDBUTTONtext3Ptr;
static ZKButton* msavePtr;
static ZKTextView* mTextview7Ptr;
static ZKTextView* mADDBUTTONtext2Ptr;
static ZKTextView* mslcSettingPtr;
static ZKButton* mlinePtr;
static ZKTextView* mADDBUTTONtext1Ptr;
static ZKButton* msys_backPtr;
static slcParamActivity* mActivityPtr;

/*register activity*/
REGISTER_ACTIVITY(slcParamActivity);

typedef struct {
	int id; // 定时器ID ， 不能重复
	int time; // 定时器  时间间隔  单位 毫秒
}S_ACTIVITY_TIMEER;

#include "logic/slcParamLogic.cc"

/***********/
typedef struct {
    int id;
    const char *pApp;
} SAppInfo;

/**
 *点击跳转window
 */
static SAppInfo sAppInfoTab[] = {
//  { ID_MAIN_TEXT, "TextViewActivity" },
};

/***************/
typedef bool (*ButtonCallback)(ZKButton *pButton);
/**
 * button onclick表
 */
typedef struct {
    int id;
    ButtonCallback callback;
}S_ButtonCallback;

/*TAG:ButtonCallbackTab按键映射表*/
static S_ButtonCallback sButtonCallbackTab[] = {
    ID_SLCPARAM_LiftRateJia, onButtonClick_LiftRateJia,
    ID_SLCPARAM_LiftDistanceJia, onButtonClick_LiftDistanceJia,
    ID_SLCPARAM_LiftRateJian, onButtonClick_LiftRateJian,
    ID_SLCPARAM_LiftDistanceJian, onButtonClick_LiftDistanceJian,
    ID_SLCPARAM_BottomTimeJia, onButtonClick_BottomTimeJia,
    ID_SLCPARAM_BottomTimeJian, onButtonClick_BottomTimeJian,
    ID_SLCPARAM_BottomLayersJia, onButtonClick_BottomLayersJia,
    ID_SLCPARAM_BottomLayersJian, onButtonClick_BottomLayersJian,
    ID_SLCPARAM_ExposureTimeButtonJian, onButtonClick_ExposureTimeButtonJian,
    ID_SLCPARAM_ExposureTimeButtonJia, onButtonClick_ExposureTimeButtonJia,
    ID_SLCPARAM_save, onButtonClick_save,
    ID_SLCPARAM_line, onButtonClick_line,
    ID_SLCPARAM_sys_back, onButtonClick_sys_back,
};
/***************/


typedef void (*SeekBarCallback)(ZKSeekBar *pSeekBar, int progress);
typedef struct {
    int id;
    SeekBarCallback callback;
}S_ZKSeekBarCallback;
/*TAG:SeekBarCallbackTab*/
static S_ZKSeekBarCallback SZKSeekBarCallbackTab[] = {
};


typedef int (*ListViewGetItemCountCallback)(const ZKListView *pListView);
typedef void (*ListViewobtainListItemDataCallback)(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index);
typedef void (*ListViewonItemClickCallback)(ZKListView *pListView, int index, int id);
typedef struct {
    int id;
    ListViewGetItemCountCallback getListItemCountCallback;
    ListViewobtainListItemDataCallback obtainListItemDataCallback;
    ListViewonItemClickCallback onItemClickCallback;
}S_ListViewFunctionsCallback;
/*TAG:ListViewFunctionsCallback*/
static S_ListViewFunctionsCallback SListViewFunctionsCallbackTab[] = {
};


typedef void (*SlideWindowItemClickCallback)(ZKSlideWindow *pSlideWindow, int index);
typedef struct {
    int id;
    SlideWindowItemClickCallback onSlideItemClickCallback;
}S_SlideWindowItemClickCallback;
/*TAG:SlideWindowFunctionsCallbackTab*/
static S_SlideWindowItemClickCallback SSlideWindowItemClickCallbackTab[] = {
};


typedef void (*EditTextInputCallback)(const std::string &text);
typedef struct {
    int id;
    EditTextInputCallback onEditTextChangedCallback;
}S_EditTextInputCallback;
/*TAG:EditTextInputCallback*/
static S_EditTextInputCallback SEditTextInputCallbackTab[] = {
};

typedef void (*VideoViewCallback)(ZKVideoView *pVideoView, int msg);
typedef struct {
    int id; //VideoView ID
    bool loop; // 是否是轮播类型
    int defaultvolume;//轮播类型时,默认视频音量
    VideoViewCallback onVideoViewCallback;
}S_VideoViewCallback;
/*TAG:VideoViewCallback*/
static S_VideoViewCallback SVideoViewCallbackTab[] = {
};


slcParamActivity::slcParamActivity() {
	//todo add init code here
	mVideoLoopIndex = 0;
	mVideoLoopErrorCount = 0;
}

slcParamActivity::~slcParamActivity() {
	//todo add init file here
    // 退出应用时需要反注册
    EASYUICONTEXT->unregisterGlobalTouchListener(this);
    onUI_quit();
    unregisterProtocolDataUpdateListener(onProtocolDataUpdate);
}

const char* slcParamActivity::getAppName() const{
	return "slcParam.ftu";
}

//TAG:onCreate
void slcParamActivity::onCreate() {
	Activity::onCreate();
    mADDBUTTONlistRatePtr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONlistRate);
    mADDBUTTONLiftDistancePtr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONLiftDistance);
    mADDBUTTONBottomTimeValuePtr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONBottomTimeValue);
    mADDBUTTONbottomValuePtr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONbottomValue);
    mADDBUTTONexposureValuePtr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONexposureValue);
    mLiftRateJiaPtr = (ZKButton*)findControlByID(ID_SLCPARAM_LiftRateJia);
    mLiftDistanceJiaPtr = (ZKButton*)findControlByID(ID_SLCPARAM_LiftDistanceJia);
    mLiftRateJianPtr = (ZKButton*)findControlByID(ID_SLCPARAM_LiftRateJian);
    mLiftDistanceJianPtr = (ZKButton*)findControlByID(ID_SLCPARAM_LiftDistanceJian);
    mBottomTimeJiaPtr = (ZKButton*)findControlByID(ID_SLCPARAM_BottomTimeJia);
    mBottomTimeJianPtr = (ZKButton*)findControlByID(ID_SLCPARAM_BottomTimeJian);
    mBottomLayersJiaPtr = (ZKButton*)findControlByID(ID_SLCPARAM_BottomLayersJia);
    mBottomLayersJianPtr = (ZKButton*)findControlByID(ID_SLCPARAM_BottomLayersJian);
    mExposureTimeButtonJianPtr = (ZKButton*)findControlByID(ID_SLCPARAM_ExposureTimeButtonJian);
    mExposureTimeButtonJiaPtr = (ZKButton*)findControlByID(ID_SLCPARAM_ExposureTimeButtonJia);
    mADDBUTTONtext4Ptr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONtext4);
    mADDBUTTONtext3Ptr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONtext3);
    msavePtr = (ZKButton*)findControlByID(ID_SLCPARAM_save);
    mTextview7Ptr = (ZKTextView*)findControlByID(ID_SLCPARAM_Textview7);
    mADDBUTTONtext2Ptr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONtext2);
    mslcSettingPtr = (ZKTextView*)findControlByID(ID_SLCPARAM_slcSetting);
    mlinePtr = (ZKButton*)findControlByID(ID_SLCPARAM_line);
    mADDBUTTONtext1Ptr = (ZKTextView*)findControlByID(ID_SLCPARAM_ADDBUTTONtext1);
    msys_backPtr = (ZKButton*)findControlByID(ID_SLCPARAM_sys_back);
	mActivityPtr = this;
	onUI_init();
    registerProtocolDataUpdateListener(onProtocolDataUpdate); 
    rigesterActivityTimer();
}

void slcParamActivity::onClick(ZKBase *pBase) {
	//TODO: add widget onClik code 
    int buttonTablen = sizeof(sButtonCallbackTab) / sizeof(S_ButtonCallback);
    for (int i = 0; i < buttonTablen; ++i) {
        if (sButtonCallbackTab[i].id == pBase->getID()) {
            if (sButtonCallbackTab[i].callback((ZKButton*)pBase)) {
            	return;
            }
            break;
        }
    }


    int len = sizeof(sAppInfoTab) / sizeof(sAppInfoTab[0]);
    for (int i = 0; i < len; ++i) {
        if (sAppInfoTab[i].id == pBase->getID()) {
            EASYUICONTEXT->openActivity(sAppInfoTab[i].pApp);
            return;
        }
    }

	Activity::onClick(pBase);
}

void slcParamActivity::onResume() {
	Activity::onResume();
	EASYUICONTEXT->registerGlobalTouchListener(this);
	startVideoLoopPlayback();
	onUI_show();
}

void slcParamActivity::onPause() {
	Activity::onPause();
	EASYUICONTEXT->unregisterGlobalTouchListener(this);
	stopVideoLoopPlayback();
	onUI_hide();
}

void slcParamActivity::onIntent(const Intent *intentPtr) {
	Activity::onIntent(intentPtr);
	onUI_intent(intentPtr);
}

bool slcParamActivity::onTimer(int id) {
	return onUI_Timer(id);
}

void slcParamActivity::onProgressChanged(ZKSeekBar *pSeekBar, int progress){

    int seekBarTablen = sizeof(SZKSeekBarCallbackTab) / sizeof(S_ZKSeekBarCallback);
    for (int i = 0; i < seekBarTablen; ++i) {
        if (SZKSeekBarCallbackTab[i].id == pSeekBar->getID()) {
            SZKSeekBarCallbackTab[i].callback(pSeekBar, progress);
            break;
        }
    }
}

int slcParamActivity::getListItemCount(const ZKListView *pListView) const{
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            return SListViewFunctionsCallbackTab[i].getListItemCountCallback(pListView);
            break;
        }
    }
    return 0;
}

void slcParamActivity::obtainListItemData(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].obtainListItemDataCallback(pListView, pListItem, index);
            break;
        }
    }
}

void slcParamActivity::onItemClick(ZKListView *pListView, int index, int id){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].onItemClickCallback(pListView, index, id);
            break;
        }
    }
}

void slcParamActivity::onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) {
    int tablen = sizeof(SSlideWindowItemClickCallbackTab) / sizeof(S_SlideWindowItemClickCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SSlideWindowItemClickCallbackTab[i].id == pSlideWindow->getID()) {
            SSlideWindowItemClickCallbackTab[i].onSlideItemClickCallback(pSlideWindow, index);
            break;
        }
    }
}

bool slcParamActivity::onTouchEvent(const MotionEvent &ev) {
    return onslcParamActivityTouchEvent(ev);
}

void slcParamActivity::onTextChanged(ZKTextView *pTextView, const std::string &text) {
    int tablen = sizeof(SEditTextInputCallbackTab) / sizeof(S_EditTextInputCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SEditTextInputCallbackTab[i].id == pTextView->getID()) {
            SEditTextInputCallbackTab[i].onEditTextChangedCallback(text);
            break;
        }
    }
}

void slcParamActivity::rigesterActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        registerTimer(temp.id, temp.time);
    }
}


void slcParamActivity::onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SVideoViewCallbackTab[i].id == pVideoView->getID()) {
        	if (SVideoViewCallbackTab[i].loop) {
                //循环播放
        		videoLoopPlayback(pVideoView, msg, i);
        	} else if (SVideoViewCallbackTab[i].onVideoViewCallback != NULL){
        	    SVideoViewCallbackTab[i].onVideoViewCallback(pVideoView, msg);
        	}
            break;
        }
    }
}

void slcParamActivity::videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex) {

	switch (msg) {
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED\n");
		pVideoView->setVolume(SVideoViewCallbackTab[callbackTabIndex].defaultvolume / 10.0);
		mVideoLoopErrorCount = 0;
		break;
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
		/**错误处理 */
		++mVideoLoopErrorCount;
		if (mVideoLoopErrorCount > 100) {
			LOGD("video loop error counts > 100, quit loop playback !");
            break;
		} //不用break, 继续尝试播放下一个
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED\n");
        std::vector<std::string> videolist;
        std::string fileName(getAppName());
        if (fileName.size() < 4) {
             LOGD("getAppName size < 4, ignore!");
             break;
        }
        fileName = fileName.substr(0, fileName.length() - 4) + "_video_list.txt";
        fileName = "/mnt/extsd/" + fileName;
        if (!parseVideoFileList(fileName.c_str(), videolist)) {
            LOGD("parseVideoFileList failed !");
		    break;
        }
		if (pVideoView && !videolist.empty()) {
			mVideoLoopIndex = (mVideoLoopIndex + 1) % videolist.size();
			pVideoView->play(videolist[mVideoLoopIndex].c_str());
		}
		break;
	}
}

void slcParamActivity::startVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		//循环播放
    		videoLoopPlayback(videoView, ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED, i);
    		return;
    	}
    }
}

void slcParamActivity::stopVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		if (videoView->isPlaying()) {
    		    videoView->stop();
    		}
    		return;
    	}
    }
}

bool slcParamActivity::parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList) {
	mediaFileList.clear();
	if (NULL == pFileListPath || 0 == strlen(pFileListPath)) {
        LOGD("video file list is null!");
		return false;
	}

	ifstream is(pFileListPath, ios_base::in);
	if (!is.is_open()) {
		LOGD("cann't open file %s \n", pFileListPath);
		return false;
	}
	char tmp[1024] = {0};
	while (is.getline(tmp, sizeof(tmp))) {
		string str = tmp;
		removeCharFromString(str, '\"');
		removeCharFromString(str, '\r');
		removeCharFromString(str, '\n');
		if (str.size() > 1) {
     		mediaFileList.push_back(str.c_str());
		}
	}
	LOGD("(f:%s, l:%d) parse fileList[%s], get [%d]files\n", __FUNCTION__,
			__LINE__, pFileListPath, mediaFileList.size());
	for (size_t i = 0; i < mediaFileList.size(); i++) {
		LOGD("file[%d]:[%s]\n", i, mediaFileList[i].c_str());
	}
	is.close();

	return true;
}

int slcParamActivity::removeCharFromString(string& nString, char c) {
    string::size_type   pos;
    while(1) {
        pos = nString.find(c);
        if(pos != string::npos) {
            nString.erase(pos, 1);
        } else {
            break;
        }
    }
    return (int)nString.size();
}

void slcParamActivity::registerUserTimer(int id, int time) {
	registerTimer(id, time);
}

void slcParamActivity::unregisterUserTimer(int id) {
	unregisterTimer(id);
}

void slcParamActivity::resetUserTimer(int id, int time) {
	resetUserTimer(id, time);
}
