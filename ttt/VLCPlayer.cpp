#include "stdafx.h"
#include "VLCPlayer.h"
#include "vlc/vlc.h"
#include<Dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "libvlc.lib")
#pragma comment(lib, "libvlccore.lib")

#ifdef __cplusplus
# define VLC_EXTERN extern "C"
#else
# define VLC_EXTERN
#endif

#if defined (_WIN32) && defined (DLL_EXPORT)
# define VLC_EXPORT __declspec(dllexport)
#else
# define VLC_EXPORT
#endif

#define VLC_API VLC_EXTERN VLC_EXPORT
#define input_thread_t void
#define vlc_object_t void
#define VLC_VAR_VOID      0x0010
#define VLC_VAR_BOOL      0x0020
#define VLC_VAR_INTEGER   0x0030
#define VLC_VAR_HOTKEY    0x0031
#define VLC_VAR_STRING    0x0040
#define VLC_VAR_VARIABLE  0x0044
#define VLC_VAR_FLOAT     0x0050
#define VLC_VAR_TIME      0x0060
#define VLC_VAR_ADDRESS   0x0070
#define VLC_VAR_COORDS    0x00A0
typedef int64_t mtime_t;
typedef union
{
    int64_t         i_int;
    bool            b_bool;
    float           f_float;
    char *          psz_string;
    void *          p_address;
    vlc_object_t *  p_object;
    void *    p_list;
    mtime_t         i_time;
    struct { int32_t x; int32_t y; } coords;
} vlc_value_t;

CVLCPlayer::CVLCPlayer(void)
	: m_strIP(_T(""))
{
	m_vlcPtr.mp = NULL;
	m_vlcPtr.inst = NULL;
}


CVLCPlayer::~CVLCPlayer(void)
{
}


VLC_API input_thread_t *libvlc_get_input_thread( libvlc_media_player_t *p_mi );
VLC_API int var_SetChecked( vlc_object_t *, const char *, int, vlc_value_t );
VLC_API void vlc_object_release( vlc_object_t * );

static inline int var_SetString( vlc_object_t *p_obj, const char *psz_name, const char *psz_string )
{
    vlc_value_t val;
    val.psz_string = (char *)psz_string;
    return var_SetChecked( p_obj, psz_name, VLC_VAR_STRING, val );
}

static inline int var_SetBool( vlc_object_t *p_obj, const char *psz_name, bool b )
{
    vlc_value_t val;
    val.b_bool = b;
    return var_SetChecked( p_obj, psz_name, VLC_VAR_BOOL, val );
}


int CVLCPlayer::RecordStop()
{
	input_thread_t *p_input_thread;
	libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
	if(p_mi==NULL) return -2;
	p_input_thread = libvlc_get_input_thread( p_mi );
	if( !p_input_thread )
		return -1;

	var_SetBool( p_input_thread, "record", false );

	vlc_object_release( p_input_thread );
	return 0;
}

//segafan201603
//int VLCRecordStart( vlcplayer *player, const char* psz_filename, const char* psz_filename1)
int CVLCPlayer::RecordStart(const char* psz_filename )
{
    libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
    input_thread_t *p_input_thread;
    if(p_mi==NULL) return -2;
    p_input_thread = libvlc_get_input_thread( p_mi );
    if( !p_input_thread )
        return -1;

    var_SetBool( p_input_thread, "record", false );
    var_SetString( p_input_thread, "input-record-path", psz_filename );
	//segafan201603
	//var_SetString( p_input_thread, "sout-record-dst-prefix", psz_filename1 );

    var_SetBool( p_input_thread, "record", true );
    vlc_object_release( p_input_thread );
    return 0;
}

int CVLCPlayer::PlayVideo(HWND wnd, char* file)
{
    libvlc_media_player_t *mp ;
    libvlc_instance_t * inst;
    libvlc_media_t *m;
    inst = libvlc_new (0, NULL);
    if (inst == NULL)
		return -1;

	char* video = new char[255];
	memset(video, 0, 255);
	if (file == "")
	{
		strncpy(video, m_strRtsp, m_strRtsp.GetLength());
	}
	else
	{
		strncpy(video, file, sizeof(file));
	}
    if(strncmp(video,"rtsp:",5)==0||strncmp(video,"http:",5)==0||strncmp(video,"mms:",3)==0||strncmp(video,"ftp:",4)==0)
        m = libvlc_media_new_location(inst, video);
    else
        m = libvlc_media_new_path (inst, video);
    const char *options[] = {
         ":video-title-position=4",
         ":newwork-caching=500",
         ":sout=#duplicate{dst=display,dst=std{access=file,mux=ts,dst='d:\\1.avi'}}"
     };
	//segafan201603
	int t1, t2;
	t1 = sizeof(options);
	t2 = sizeof(options[0]);
	CString tpstr, savefilename;
	CTime now = CTime::GetCurrentTime();
	int noption;
	if (m_bSaveAvi)
	{
		MakeSureDirectoryPathExists(m_strSavePath + now.Format("%Y%m%d\\"));
		savefilename.Format("%s%s%s.avi", m_strSavePath, now.Format("%Y%m%d\\"), now.Format("%Y-%m-%d %H;%M;%S"));
		tpstr.Format(":sout=#duplicate{dst=display,dst=std{access=file,mux=ts,dst='%s'}}", savefilename);
		options[2] = tpstr;
		noption = 3;
	}
	else
		noption = 2;

	for (int i = 0; i < noption; i++)
	//for (int i = 0; i < sizeof(options) / sizeof(options[0]); i++)
         libvlc_media_add_option (m, options[i]);
	//segafan201706增加以tcp方式打开RTSP
	if (m_bTCP)
	{
		const char *option1[] = {":rtsp-tcp"};
		libvlc_media_add_option (m, option1[0]);
	}

    mp = libvlc_media_player_new_from_media (m);
    libvlc_media_parse(m);
    libvlc_time_t duration = libvlc_media_get_duration(m);
    libvlc_media_release (m);
    m_vlcPtr.mp=(void *)mp;
    m_vlcPtr.inst=(void *)inst;

    libvlc_media_player_set_hwnd (mp, (void *)wnd);
    int s = libvlc_media_player_play (mp);
    if(s == 0)
    {
    libvlc_video_set_mouse_input(mp,0);
    libvlc_video_set_key_input(mp,0);
	//以下两行解决 VLC第一次无法录制的BUG
	//RecordStart("temp");
    //VLCRecordStart((vlcplayer *)player, "d:\\1\\", "1.avi");
    //RecordStop();
    }
    else
       CloseVideo();
    return s;
}

void CVLCPlayer::CloseVideo()
{
	if(m_vlcPtr.mp)
	{
		libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
		libvlc_media_player_stop (p_mi);
		libvlc_media_player_release (p_mi);
	}
	if(m_vlcPtr.inst)
		libvlc_release((libvlc_instance_t *)m_vlcPtr.inst);
	m_vlcPtr.mp=NULL;
	m_vlcPtr.inst=NULL;
}

bool CVLCPlayer::IsPlaying()
{
	if(m_vlcPtr.mp)
	{
		libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
		return libvlc_media_player_is_playing(p_mi);
	}
	return false;
}

int CVLCPlayer::GetState()
{
	static libvlc_state_t m_state = libvlc_NothingSpecial;
	if(m_vlcPtr.mp)
	{
		libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
		libvlc_state_t state = libvlc_media_player_get_state(p_mi);
		if (m_state != state)
		{
			m_state = state;
		}
		return m_state;
	}
	return false;
}

void CVLCPlayer::SetPlayWnd(HWND wnd)
{
	int s;
	libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
	//void *pwnd = libvlc_media_player_get_hwnd(p_mi);

	//libvlc_media_player_stop (p_mi);
	//libvlc_media_player_set_pause(p_mi,1);  
	libvlc_media_player_pause(p_mi);
	libvlc_media_player_set_hwnd (p_mi, (void *)wnd);
	libvlc_media_player_pause(p_mi);

	s = libvlc_media_player_play (p_mi);
    //libvlc_media_player_set_pause(p_mi,0);
	//s = s;
}

void CVLCPlayer::TogglePause()
{
	libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
	libvlc_toggle_fullscreen(p_mi);
	//libvlc_media_player_pause(p_mi);
}

//segafan201704增加视频截图功能
BOOL CVLCPlayer::TakeSnapshot(CString strPath, unsigned int nWidth, unsigned int nHeight)
{
	libvlc_media_player_t *p_mi= (libvlc_media_player_t*) m_vlcPtr.mp;
	int ret = libvlc_video_take_snapshot(p_mi, 0, strPath, nWidth, nHeight);
	if (ret == 0)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}

//segafan201706增加以tcp方式打开RTSP
BOOL CVLCPlayer::Init(CString inifile, CString ip, BOOL bSave, BOOL bTCP)
//segafan201608增加VLC双击大画面
//BOOL CVLCPlayer::Init(CString inifile, CString ip, BOOL bSave)
//BOOL CVLCPlayer::Init(CString inifile, CString ip)
{
	m_strIP = ip;
	char path[MAX_PATH];
	//segafan201608增加VLC双击大画面
	m_strIniFilePath = inifile;
	if (bSave)
	{
		m_bSaveAvi = GetPrivateProfileInt(m_strIP, _T("EnableSaveH264"), 0, inifile);
	} 
	else
	{
		m_bSaveAvi = FALSE;
	}
	//m_bSaveAvi = GetPrivateProfileInt(m_strIP, _T("EnableSaveH264"), 0, inifile);

	//segafan201706增加以tcp方式打开RTSP
	m_bTCP = bTCP;

	GetPrivateProfileString(m_strIP, _T("SavePath"), "", path, MAX_PATH, inifile);
	m_nSaveAviLength = GetPrivateProfileInt(m_strIP, _T("AviTime"), 0, inifile);
	GetPrivateProfileString(m_strIP, _T("RTSP"), "", m_strRtsp.GetBuffer(MAX_PATH), MAX_PATH, inifile);
	m_strRtsp.ReleaseBuffer();
	if (m_strRtsp == "")
	{
		GetPrivateProfileString(m_strIP, _T("RSTP"), "", m_strRtsp.GetBuffer(MAX_PATH), MAX_PATH, inifile);
		m_strRtsp.ReleaseBuffer();
	}
	if (m_strRtsp == "")
	{
		return FALSE;
	}

	if (path != "")
	{
		m_strSavePath.Format("%s\\%s\\", path, m_strIP);
	}
	else
	{
		m_strSavePath.Empty();;
		m_bSaveAvi = FALSE;
	}
	return TRUE;
}

BOOL CVLCPlayer::IsSaveAvi()
{
	return m_bSaveAvi;
}

CString CVLCPlayer::GetSavePath()
{
	return m_strSavePath;
}

//segafan201608增加VLC双击大画面
CString CVLCPlayer::GetIniFilePath()
{
	return m_strIniFilePath;
}

//segafan201608增加VLC双击大画面
CString CVLCPlayer::GetIP()
{
	return m_strIP;
}