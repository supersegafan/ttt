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
	//����0 �ɹ�  ���� ʧ��
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
	//segafan201706������tcp��ʽ��RTSP
	BOOL Init(CString inifile, CString ip, BOOL bSave = TRUE, BOOL bTCP = TRUE);
	//segafan201608����VLC˫������
	//BOOL Init(CString inifile, CString ip, BOOL bSave = TRUE);
	//BOOL Init(CString inifile, CString ip);
	BOOL IsSaveAvi();
	CString GetSavePath();
	//segafan201608����VLC˫������
	CString GetIniFilePath();
	CString GetIP();
	//segafan201704������Ƶ��ͼ����
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
	//segafan201608����VLC˫������
	CString m_strIniFilePath;
	//segafan201706������tcp��ʽ��RTSP
	BOOL m_bTCP;
};
#endif
 