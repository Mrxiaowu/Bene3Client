#ifndef _UART_PROTOCOL_DATA_H_
#define _UART_PROTOCOL_DATA_H_

#include <string>
#include "CommDef.h"

/******************** CmdID ***********************/
#define CMDID_POWER							0x0

/***UART CMD*************/
#define SWITCH_PAGE      3
#define SWITCH_REGION    4
#define SET_LABEL_VALUE  8
#define SET_ICON_VALUE  0A
#define TurnOff_PageID 13

//AA 55 05 03 00 FF FF FF 00 主页面
//AA 55 05 03 02 FF FF FF FE 文件管理页面
//AA 55 05 03 03 FF FF FF FD 电机控制页面
//AA 55 05 03 04 FF FF FF FC SLC参数设置页面
//AA 55 05 03 05 FF FF FF FB 网络控制页面
//AA 55 05 03 06 FF FF FF FA 控制机器的页面
//AA 55 05 03 07 FF FF FF F9 公共页面
//AA 55 05 03 08 FF FF FF F8
//AA 55 05 03 09 FF FF FF F7
//AA 55 05 03 0A FF FF FF F6
//AA 55 05 03 0B FF FF FF F5
//AA 55 05 03 0C FF FF FF F4 //LOGO
//AA 55 05 03 0D FF FF FF F3 //关机中


/**************Set Page 01 region 09 LABLES 15 value************/
//AA 55  +长度+08+PageID+RegionID+ TypeID+         CtrlID+Value+            Check Summer
//AA 55     0C 08   01      09       04      0F 41 42 43 44 45 46 00         46

//设置ListBox控件值
/**************Set Page 02 region 02 LISTBOX 01 index 00 value************/
//AA 55  +长度+08+PageID+RegionID+TypeID+CtrlID+Index+Value+Check Summer
//AA 55    0D  08   02      02      10     01     00    41 42 43 44 45 46 00 4E

//LCD2MCU返回值
/*LCD2MCU主要是pageID加regionID值*/
//AA 55  +长度+PageID+FF+TypeID+ButtonID+EeventID+Check Summer

//键盘返回值
//AA 55  +长度+PageID+FF+TypeID+ButtonID+EeventID+KeyValue+Check Summer

/****Event ID****/
#define EVT_TOUCH 1
#define EVT_SWITCH_PAGE 2

/***Type ID******/
#define	GL_NONE 0
#define GL_BUTTON  1  //按钮
#define GL_ANIMATIONICON 2
#define GL_CHECKBOX  3 //选择框
#define GL_LABEL  4, //标签
#define GL_SCROLLLABEL  5
#define GL_ICON  6
#define GL_COMBOBOX  7
#define GL_SLIDEBAR  8
#define GL_HISTOGRAM  9
#define GL_GRAPH_CHART 10  //图形图表，如LISTBOX
#define GL_REGION 0x0B
#define GL_PROGRESSBAR   0x0C
#define GL_PAGE
#define GL_BMP
#define GL_ADDBUTTON
#define GL_LISTBOX
#define GL_KEYBOARD 11

/***Page ID******/
#define  Menu_PageID         0
#define ScreenSaver_PageID  1
#define FileManage_PageID  2
#define MachineControl_PageID  3
#define ParameterSet_PageID  4
#define NetworkControl_PageID  5
#define MachineInfo_PageID  6
#define UsbFile_PageID  7
#define Dialog_PageID  8
#define Print_PageID  9
#define Keyboard_PageID  10
#define PowerOff_PageID 11
#define Logo_PageID 12

/***Region ID******/
#define MenuPage_PrintRegionID       0
#define ScreenSaverPage_RegionID  1
#define FileManagePage_RegionID 2
#define MachineControlPage_RegionID 3
#define ParameterSetPage_RegionID 4

#define NetworkContolPage_RegionID 5
#define NetworkContolPage_NetworkRegionID 6
#define NetworkContolPage_WireLANRegionID 7

#define  MachineInfoPage_RegionID  8
#define  MachineInfoPage_HardwareRegionID  9
#define  MachineInfoPage_LanguageRegionID  10
#define  MachineInfoPage_VersionRegionID  11

#define  UsbFilePage_FileRegionID 12
#define  UsbFilePage_ButtonRegionID 13

#define  DialogPage_BackRegionID 14
#define  DialogPage_DialogInfoRegionID 15

#define PrintPage_UpRegionID 16
#define PrintPage_DownRegionID 17
#define  KeyboardPage_RegionID 18
#define PowerOff_RegionID 19
#define  Logo_RegionID 20

/***Label ID******/
#define ScreenSaver_LabelID   0
#define FileManage_PageNumberLabelID 1

#define ParameterSet_ExposureTimeLabelID 2
#define ParameterSet_LiftDistanceLabelID 3
#define ParameterSet_BottomLayersLabelID 4
#define ParameterSet_LiftRateLabelID 5
#define ParameterSet_BottomTimeLabelID 6

#define NetWorkControl_PasswordLabelID 7
#define NetWorkControl_AccessPointLabelID 8
#define NetWorkControl_CurrentWifiLabelID 9
#define NetWorkControl_CurrentWifiValueLabelID 10
#define NetWorkControl_StaticIPLabelID 11
#define NetWorkControl_StaticIPValueLabelID 12
#define NetWorkControl_DynamicIPLabelID 13
#define NetWorkControl_DynamicIPValueLabelID 14

#define MachineInfo_ModelLabelID   15
#define MachineInfo_ModelNameLabelID   16
#define MachineInfo_SnsidLabelID   17
#define MachineInfo_SnsidNameLabelID   18
#define MachineInfo_VerLabelID   19
#define MachineInfo_VerNameLabelID   20

#define Dialog_DialogInfoLabelID   21

#define Print_FilenameLabelID 22
#define Print_TimeLabelID 23
#define TurnOff_LabelID 24

/***PROGRESSBAR ID******/
#define Print_PrintFileProgressBarID  0

/***Button ID******/
#define MenuPage_PrintButtonID       0
#define MenuPage_SystemSetButtonID  1
#define MenuPage_FileManageButtonID  2
#define MenuPage_PrintSetButtonID   3

#define FileManage_HomeButtonID 4
#define FileManage_DeleteButtonID 5
#define FileManage_PrintButtonID 6
#define FileManage_UsbButtonID 7
#define FileManage_PgUpButtonID 8
#define  FileManage_PgDnButtonID 9

#define  MachineControl_HomeButtonID  FileManage_HomeButtonID
#define  MachineControl_Up0_05ButtonID 10
#define  MachineControl_Up1ButtonID 11
#define  MachineControl_Up10ButtonID 12
#define  MachineControl_Up50ButtonID 13

#define  MachineControl_Dn0_05ButtonID 14
#define  MachineControl_Dn1ButtonID 15
#define  MachineControl_Dn10ButtonID 16
#define  MachineControl_Dn50ButtonID 17
#define  MachineControl_HMButtonID 18
#define  MachineControl_MachineControlButtonID 19
#define  MachineControl_ParameterSetButtonID 20

#define  ParameterSet_HomeButtonID  FileManage_HomeButtonID
#define  ParameterSet_SaveButtonID	21
#define  ParameterSet_MachineControlButtonID 22
#define  ParameterSet_ParameterSetButtonID 23

#define NetWorkControl_HomeButtonID    FileManage_HomeButtonID
#define  NetWorkControl_NetWorkControlButtonID 24
#define  NetWorkControl_MachineInfoButtonID 25
#define  NetWorkControl_NetWorkButtonID 26
#define  NetWorkControl_WiredLANButtonID 27
#define  NetWorkControl_ResetButtonID 28
#define  NetWorkControl_PasswordButtonID 29
#define  NetWorkControl_AccessPointButtonID 30

#define  MachineInfo_HomeButtonID  FileManage_HomeButtonID
#define MachineInfo_NetWorkControlButtonID 31
#define MachineInfo_MachineInfoButtonID   32
#define MachineInfo_HardwareButtonID   33
#define MachineInfo_LanguageButtonID   34
#define MachineInfo_ChButtonID   35
#define MachineInfo_EnButtonID   36
#define MachineInfo_VersionButtonID   37
#define UsbFile_UploadButtonID   38
#define UsbFile_CancelButtonID   39

#define Dialog_ConfirmButtonID 40
#define Dialog_CancelButtonID 41

#define Print_HomeButtonID FileManage_HomeButtonID
#define Print_StartButtonID 42
#define Print_PauseButtonID 43
#define Print_StopButtonID 44
#define Print_ThicknessButtonID 45
#define Print_PrintLayerButtonID 46
#define Print_PrintVelocityButtonID 47
#define Print_PrintStateButtonID 48

#define Keyboard_HomeButtonID FileManage_HomeButtonID

#define UsbFile_PgUpButtonID   49
#define UsbFile_PgDnButtonID   50

#define PowerOff_ConfirmButtonID 51
#define PowerOff_ConcelButtonID 52

/***LISTBOX ID******/
#define UsbFilePage_FileListboxID       0
#define FileManagePage_FileListboxID 1

/***AddButton ID******/
#define ParameterSet_ExposureTimeAddButtonID       0
#define ParameterSet_LiftDistanceAddButtonID       1
#define ParameterSet_BottomLayerAddButtonID       2
#define ParameterSet_LiftRateAddButtonID       3
#define ParameterSet_BottomTimeAddButtonID       4
/**************************************************/


/******************** 错误码 ***********************/
#define ERROR_CODE_CMDID			1
/**************************************************/

typedef struct {
	std::string textStr;
	BYTE power;
} SProtocolData;

#endif /* _UART_PROTOCOL_DATA_H_ */
