
#ifndef __PRINTABLESACTIVITY_H__
#define __PRINTABLESACTIVITY_H__


#include "app/Activity.h"
#include "entry/EasyUIContext.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"

#include "utils/Log.h"
#include "control/ZKDigitalClock.h"
#include "control/ZKButton.h"
#include "control/ZKCircleBar.h"
#include "control/ZKDiagram.h"
#include "control/ZKListView.h"
#include "control/ZKPointer.h"
#include "control/ZKQRCode.h"
#include "control/ZKTextView.h"
#include "control/ZKSeekBar.h"
#include "control/ZKEditText.h"
#include "control/ZKVideoView.h"
#include "window/ZKSlideWindow.h"

/*TAG:Macro宏ID*/
#define ID_PRINTABLES_usbWindow    110002
#define ID_PRINTABLES_cancell    20019
#define ID_PRINTABLES_pgdown    20018
#define ID_PRINTABLES_pgup    20017
#define ID_PRINTABLES_sure    20016
#define ID_PRINTABLES_Button6    20015
#define ID_PRINTABLES_Button5    20014
#define ID_PRINTABLES_Button4    20013
#define ID_PRINTABLES_Button3    20005
#define ID_PRINTABLES_Button2    20006
#define ID_PRINTABLES_Button1    20004
#define ID_PRINTABLES_fileList3    20012
#define ID_PRINTABLES_fileList2    20011
#define ID_PRINTABLES_fileList1    20010
#define ID_PRINTABLES_Window1    110001
#define ID_PRINTABLES_printablePage    50010
#define ID_PRINTABLES_line    20009
#define ID_PRINTABLES_pageNumber    50001
#define ID_PRINTABLES_pageDown    20008
#define ID_PRINTABLES_pageUp    20007
#define ID_PRINTABLES_delete    20003
#define ID_PRINTABLES_USB    20002
#define ID_PRINTABLES_print    20001
#define ID_PRINTABLES_sys_back   100
/*TAG:Macro宏ID END*/

class printablesActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    printablesActivity();
    virtual ~printablesActivity();

    /**
     * 注册定时器
     */
	void registerUserTimer(int id, int time);
	/**
	 * 取消定时器
	 */
	void unregisterUserTimer(int id);
	/**
	 * 重置定时器
	 */
	void resetUserTimer(int id, int time);

protected:
    /*TAG:PROTECTED_FUNCTION*/
    virtual const char* getAppName() const;
    virtual void onCreate();
    virtual void onClick(ZKBase *pBase);
    virtual void onResume();
    virtual void onPause();
    virtual void onIntent(const Intent *intentPtr);
    virtual bool onTimer(int id);

    virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress);

    virtual int getListItemCount(const ZKListView *pListView) const;
    virtual void obtainListItemData(ZKListView *pListView, ZKListView::ZKListItem *pListItem, int index);
    virtual void onItemClick(ZKListView *pListView, int index, int subItemIndex);

    virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index);

    virtual bool onTouchEvent(const MotionEvent &ev);

    virtual void onTextChanged(ZKTextView *pTextView, const string &text);

    void rigesterActivityTimer();

    virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg);
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex);
    void startVideoLoopPlayback();
    void stopVideoLoopPlayback();
    bool parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList);
    int removeCharFromString(string& nString, char c);


private:
    /*TAG:PRIVATE_VARIABLE*/
    int mVideoLoopIndex;
    int mVideoLoopErrorCount;

};

#endif