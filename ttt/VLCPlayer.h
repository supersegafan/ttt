#ifndef VLCPLAYER
#pragma once
#define VLCPLAYER
#include <windows.h>
//#include "HvH264Receiver.h"
typedef  struct
{
void *mp;
void *inst;
}vlcplayer;

class CVLCPlayer
{
public:
	CVLCPlayer(void);
	~CVLCPlayer(void);
	//返回0 成功  其他 失败
	//segafan201603
	//int VLCRecordStart( vlcplayer *player, const char* psz_filename, const char* psz_filename1);
	int RecordStart(const char* psz_filename );
	int RecordStop();
	int PlayVideo(HWND wnd,char* file = "");
	void CloseVideo();
	bool IsPlaying();
	int GetState();
	void SetPlayWnd(HWND wnd);
	void TogglePause();
	//segafan201706增加以tcp方式打开RTSP
	BOOL Init(CString inifile, CString ip, BOOL bSave = TRUE, BOOL bTCP = TRUE);
	//segafan201608增加VLC双击大画面
	//BOOL Init(CString inifile, CString ip, BOOL bSave = TRUE);
	//BOOL Init(CString inifile, CString ip);
	BOOL IsSaveAvi();
	CString GetSavePath();
	//segafan201608增加VLC双击大画面
	CString GetIniFilePath();
	CString GetIP();
	//segafan201704增加视频截图功能
	BOOL TakeSnapshot(CString strPath, unsigned int nWidth = 0, unsigned int nHeight = 0);
private:
	vlcplayer m_vlcPtr;
protected:
	;
public:
	;
private:
	CString m_strIP;
	BOOL m_bSaveAvi;
	CString m_strSavePath;
	int m_nSaveAviLength;
	CString m_strRtsp;
	//segafan201608增加VLC双击大画面
	CString m_strIniFilePath;
	//segafan201706增加以tcp方式打开RTSP
	BOOL m_bTCP;
};
#endif
 