
// tttDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ttt.h"
#include "tttDlg.h"
#include "afxdialogex.h"

#include "OdbcSql.h"

#include "BASE64_API.h"

#include <Dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")

#include <string>
#include <sstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_THREAD (WM_USER + 127)
#define MESSAGEUPDATESERVERTIP (11)
#define ShowServerMessage(handle, strmessage) ::PostMessage(handle, WM_THREAD, MESSAGEUPDATESERVERTIP, (LPARAM)strmessage)

#define MESSAGEUPDATETESTTIP (12)
#define ShowTestMessage(handle) ::PostMessage(handle, WM_THREAD, MESSAGEUPDATETESTTIP, (LPARAM)0)

#pragma pack (push)
#pragma pack (1)
typedef struct tagFee_Rate
{
	UL FeeStartTime;
	UL FeeEndTime;
	UL FeeClass1;
	UL FeeClass2;
	UL FeeClass3;
	UL FeeClass4;
	UL FeeClass5;
	UL FeeClass6;
	UL FeeClass7;
	UL FeeClass8;
	UL FeeClass9;
	UL FeeClass10;
	UL FeeClass11;
	C  Reserve[2];
public:
	static US GetLength(){return sizeof(tagFee_Rate);}
}Fee_Rate;

typedef struct tagFee_RateTlb // TranType = 0002H
{
	US RecCount;
	C StationNo[6];
	UL StartTime;
	UL CycleStartTime;
	UL CycleEndTime;
	UL FreeTime;
	Fee_Rate FeeRates[1];
public:
	static US GetTranType() {return 0X02;}
	UL GetLenth(){return RecCount * Fee_Rate::GetLength() + 10;}
	US GetMacTacPos(){return GetLenth();}
}Fee_RateTlb;

#pragma pack (pop)

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtttDlg �Ի���




CtttDlg::CtttDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtttDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CtttDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WATTSCTRL1, m_Watts);
	DDX_Control(pDX, IDC_TAB1, m_tab1);
}

BEGIN_MESSAGE_MAP(CtttDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtttDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CtttDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtttDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CtttDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CtttDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CtttDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CtttDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CtttDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CtttDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CtttDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CtttDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CtttDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CtttDlg::OnBnClickedButton12)
	ON_MESSAGE(WM_THREAD, OnThreadMessage)
	ON_BN_CLICKED(IDC_BUTTON13, &CtttDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CtttDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CtttDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CtttDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CtttDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CtttDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CtttDlg::OnBnClickedButton19)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CtttDlg::OnSelchangeTab1)
END_MESSAGE_MAP()


// CtttDlg ��Ϣ�������
HANDLE g_hMutex;
CWinThread *g_pThreadtest;
CWinThread *g_pThreadtest2;
CSocket sockListen;
CSocket sockUDP;

CString g_strTest;

UINT ThreadImageRecieve( LPVOID pParam )
{
	CString strErrorMsg;
	int nListenPort = 4680;
	int nSucceed;
	sockListen.Close();
	nSucceed = sockListen.Create(nListenPort);
	if (nSucceed == 0)
	{
		strErrorMsg = " ClientListenSock Create����!";// + GetSocketError(GetLastError());
		AfxMessageBox(strErrorMsg);
	}
	nSucceed = sockListen.Listen();
	if (nSucceed == 0)
	{
		strErrorMsg = " ClientListenSock Listen����!";// + GetSocketError(GetLastError());
		AfxMessageBox(strErrorMsg);
		return -1;
	}
	CSocket sockRecv;
	SOCKADDR_IN client;
	int iAddrSize = sizeof(client);
	strErrorMsg = " ��ʼAccept";
	nSucceed = sockListen.Accept(sockRecv, (SOCKADDR *)&client, &iAddrSize);	//�������Ӳ�ȡ�öԷ�IP
	if (nSucceed == 0)
	{
		strErrorMsg = " ClientListenSock Accept����!";// + GetSocketError(GetLastError());
		AfxMessageBox(strErrorMsg);
		return -1;
	}
	strErrorMsg = " Accept�ɹ���";
	//AfxMessageBox(strErrorMsg);
	sockListen.Close();
	BYTE bufrecv[1000];
	int nrecv = sockRecv.Receive(bufrecv, sizeof(MessageHead) + sizeof(IODeviceVarietyMsg) + sizeof(VideoSnapshot));
	if (nrecv < (sizeof(MessageHead) + sizeof(IODeviceVarietyMsg) + sizeof(VideoSnapshot)))
	{
		sockRecv.Close();
		return -1;
	}
	UL filelen;
	BYTE *filebuf = new BYTE[MAXIMAGEFILELENGTH];
	MessageHead mh;
	IODeviceVarietyMsg dvm;
	VideoSnapshot vss;
	memcpy(&dvm, bufrecv + sizeof(MessageHead), sizeof(IODeviceVarietyMsg));
	memcpy(&vss, bufrecv + sizeof(MessageHead) + sizeof(IODeviceVarietyMsg), sizeof(VideoSnapshot));
	filelen = dvm.DataLength - sizeof(VideoSnapshot);
	UL recvlen = 0;
	do 
	{
		nrecv = sockRecv.Receive(filebuf + recvlen, filelen - recvlen);
		if (nrecv <= 0)
		{
			break;
		}
		else
		{
			recvlen += nrecv;
		}
	} while (recvlen < filelen);
	if (recvlen < filelen)
	{
		sockRecv.Close();
		return -1;
	}
	CString filepath;
	static UL fileindex = 0;
	fileindex++;
	filepath.Format("t:\\2\\%05d.jpg", fileindex);
	TRY 
	{
		CFile f;
		if (f.Open(filepath, CFile::modeCreate | CFile::modeReadWrite))
		{
			f.Write(filebuf, filelen);
			f.Close();
		}
	}
	CATCH( CFileException, e )
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e->m_cause << "\n";
#endif
		return FALSE;
	}
	END_CATCH
	//sockRecv.Send("1234567890", 10);
	sockRecv.Close();
	delete []filebuf;
	return 0;
}

UINT Threadtest( LPVOID pParam )
{
	CString strErrorMsg;
	int nListenPort = 10000;
	nListenPort = 5182;
	int nSucceed;
	sockListen.Close();
	nSucceed = sockListen.Create(nListenPort);
	if (nSucceed == 0)
	{
		strErrorMsg = " ClientListenSock Create����!";// + GetSocketError(GetLastError());
		//ShowMessage(pDlg->m_hWnd, "LaneListenSock Create����!", FALSE);
		//WriteLog(strErrorMsg);
		AfxMessageBox(strErrorMsg);
	}
	nSucceed = sockListen.Listen();
	if (nSucceed == 0)
	{
		strErrorMsg = " ClientListenSock Listen����!";// + GetSocketError(GetLastError());
		//ShowMessage(pDlg->m_hWnd, "Listen����!", FALSE);
		//WriteLog(strErrorMsg);
		AfxMessageBox(strErrorMsg);
		return -1;
	}
	CSocket sockRecv;
	SOCKADDR_IN client;
	int iAddrSize = sizeof(client);
	strErrorMsg = " ��ʼAccept";
	//WriteLog(strErrorMsg);
	nSucceed = sockListen.Accept(sockRecv, (SOCKADDR *)&client, &iAddrSize);	//�������Ӳ�ȡ�öԷ�IP
	if (nSucceed == 0)
	{
		strErrorMsg = " ClientListenSock Accept����!";// + GetSocketError(GetLastError());
		//ShowMessage(pDlg->m_hWnd, "Accept����!", FALSE);
		//WriteLog(strErrorMsg);
		AfxMessageBox(strErrorMsg);
		return -1;
	}
	strErrorMsg = " Accept�ɹ���";
	//ShowMessage(pDlg->m_hWnd, "Accept�ɹ���", FALSE);
	//WriteLog(strErrorMsg);
	AfxMessageBox(strErrorMsg);
	sockListen.Close();
	BYTE bufrecv[1000];
	int nrecv = sockRecv.Receive(bufrecv, 1000);
	sockRecv.Send("1234567890", 10);
	sockRecv.Close();
	return 0;

	while (TRUE)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		Sleep(5000);
		ReleaseMutex(g_hMutex);
		Sleep(100);
	}
	return 0;
}
#define MAXCOMMUNICATIONBUFFERUDP (1000)
UINT Threadtest2( LPVOID pParam )
{
	//CSocket sockUDP;
	int nListenPort = 9000;
	CString strErrorMsg;
	do 
	{
		if (!sockUDP.Create(nListenPort, SOCK_DGRAM))
		{
			strErrorMsg.Format("UPD Socket Create Error"); // , DeviceName = %s, DeviceIndex = %d", di.Name, nDeviceIndex + 1);
			//WriteLog(strErrorMsg);
			AfxMessageBox(strErrorMsg);
			Sleep(10000);
			continue;
		}
		break;
	} while (TRUE);
	BYTE bufrec[MAXCOMMUNICATIONBUFFERUDP];
	int len;
	CString strIP;
	UINT nPort;
	len = sockUDP.ReceiveFrom(&bufrec, MAXCOMMUNICATIONBUFFERUDP, strIP, nPort);
	strErrorMsg.Format("ReceiveFrom�ɹ�, IP=%s, Port=%d, len=%d", strIP, nPort, len);
	//WriteLog(strErrorMsg);
	AfxMessageBox(strErrorMsg);
	if ((len > 0) && (len <= MAXCOMMUNICATIONBUFFERUDP))
	{
		CString tpstr;
		memcpy(tpstr.GetBuffer(len), bufrec, len);
		tpstr.ReleaseBuffer();
		strErrorMsg.Format("ThreadMeteo: ��ʼ����, str=%s", tpstr);
		//WriteLog(strErrorMsg);
	}
	sockUDP.Close();
	return 1;
}

UINT ThreadVD( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)(pParam);
	int index = pDlg->m_nIndex;
	while (1)
	{
		pDlg->vdtest(index);
		Sleep(10);
	}
}

UINT ThreadQueue( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)(pParam);
	HINSTANCE hDll;
	hDll = LoadLibrary("libQueue.dll");
	if (NULL==hDll)
	{
		AfxMessageBox("DLL����ʧ��");
		return -1;
	}

	typedef int (*lpFun1)(int);
	lpFun1 pQueueRecoInit = NULL;
	pQueueRecoInit = (lpFun1)GetProcAddress(hDll, "_Z13QueueRecoIniti");
	if (NULL == pQueueRecoInit)
	{
		AfxMessageBox("DLL��QueueRecoInit����Ѱ��ʧ��");
		//return;
	}
	typedef float (*lpFun2)(float*);
	lpFun2 pQueueGetResult = NULL;
	pQueueGetResult = (lpFun2)GetProcAddress(hDll, "_Z14QueueGetResultPf");
	if (NULL == pQueueGetResult)
	{
		AfxMessageBox("DLL��SendMsg����Ѱ��ʧ��");
		//return;
	}
	pQueueRecoInit(0);
	float result;
	float res[2000];
	int count = 0;
	CString tpstr;
	while (TRUE)
	{
		result = pQueueGetResult(NULL);
		tpstr.Format("���鳤��=%.2f��", result);
		pDlg->GetDlgItem(IDC_STATIC_QUEUE)->SetWindowText(tpstr);
		//res[count] = result;
		//count ++;
		//if (count >= 2000)
		//{
		//	break;
		//}
		Sleep(500);
	}
	return 0;
}

LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	HANDLE lhDumpFile = CreateFile(_T("DumpFile.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL ,NULL);

	MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;
	loExceptionInfo.ExceptionPointers = ExceptionInfo;
	loExceptionInfo.ThreadId = GetCurrentThreadId();
	loExceptionInfo.ClientPointers = TRUE;
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),lhDumpFile, MiniDumpWithFullMemory, &loExceptionInfo, NULL, NULL);//MiniDumpWithFullMemory\MiniDumpWithDataSegs\MiniDumpNormal
	CloseHandle(lhDumpFile);

	return EXCEPTION_EXECUTE_HANDLER;
}

BOOL CtttDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	g_hMutex = NULL;
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	if(!g_hMutex)
	{
		AfxMessageBox("Mutex����ʧ�ܣ�");
	}

	m_bTakingSnapshot = FALSE;

	unsigned short ustt;
	unsigned char uctt[2];
	ustt = 0x1234;
	//memcpy(&ustt, 0x12345, 2);
	memcpy(&uctt, &ustt, 2);
	unsigned char uctp;
	uctp = ustt & 0xff;
	uctp = ustt >> 8;

	CString strTemplate = "abc abc 123joipa jabcedf";
	int tpiii = strTemplate.Replace("abc", "cba");

	m_tab1.InsertItem(0, _T("ttab1"));         // �����һ����ǩ��Register��     
	m_tab1.InsertItem(1, _T("ab2"));  // ����ڶ�����ǩ��Graphic��     
	m_dlgTab1.Create(IDD_DIALOG_TAB1, &m_tab1);    // ������һ����ǩҳ     
	m_dlgTab2.Create(IDD_DIALOG_TAB2, &m_tab1); // �����ڶ�����ǩҳ  
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С     
	m_tab1.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect     
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ     
	tabRect.left += 1;                    
	tabRect.right -= 1;     
	tabRect.top += 25;     
	tabRect.bottom -= 1;     
	// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ��ʾ     
	m_dlgTab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);     
	// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����     
	m_dlgTab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);  

	//g_pThreadtest = AfxBeginThread(Threadtest, this);
	//Sleep(300);
	//g_pThreadtest2 = AfxBeginThread(Threadtest2, this);

	//AfxBeginThread(ThreadQueue, this);

	//GetDlgItem(IDC_STATIC_QUEUE)->SetWindowText("���ǿ��Խ�����ʻ\r\nע�ⰲȫ�ַֺϺ����վ���");

	//int F2F0XSCommandGenerate(UT* bufSend, UT stationnumber, UT commandparam)
	//{
		UT bufSend[100];
		int len;
		len = 0;
		if (bufSend == NULL)
			return 0;
		//֡ͷ
		bufSend[len++] = 0xF2;
		//վ��
		//bufSend[len++] = 3;//stationnumber;
		bufSend[len++] = 13;//stationnumber;
		//���ٰ�
		//bufSend[len++] = 0xF6;//���ٰ�
		bufSend[len++] = 0xF7;//fban
		//����
		//bufSend[len++] = 0x2F;//���ٰ�
		bufSend[len++] = 0x7F;//
		//����
		//bufSend[len++] = 8;//commandparam;
		bufSend[len++] = 0x0b;
		bufSend[len++] = 0x0b;
		bufSend[len++] = 0x0a;
		bufSend[len++] = 0x06;
		bufSend[len++] = 0x0c;
		bufSend[len++] = 0x09;
		bufSend[len++] = 0x0f;
		bufSend[len++] = 0x07;

		bufSend[len++] = 0x0b;
		bufSend[len++] = 0x0c;
		bufSend[len++] = 0x0d;
		bufSend[len++] = 0x0d;
		bufSend[len++] = 0x0c;
		bufSend[len++] = 0x0a;
		bufSend[len++] = 0x0b;
		bufSend[len++] = 0x0b;

		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;

		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;
		bufSend[len++] = 0x0;

		//У��
		UT check = 0;
		for (int i = 1; i < len ; i++)
		{
			check ^= bufSend[i];
		}
		bufSend[len++] = check & 0x7F;
		//֡β
		bufSend[len++] = 0xF0;
		//return len;
	//}

		CString strlog = "";
		BYTE tpbyte;
		for (int i = 0; i < len ; i++)
		{
			CString tpstr;
			tpbyte = *(bufSend + i);	
			tpstr.Format("%02X ", tpbyte);
			strlog += tpstr;
		}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtttDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtttDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtttDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtttDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CTime temptime(2001, 2, 29, 0, 0, 0);
	CTime nexttime = temptime;
	SYSTEMTIME st;
	CString strtime;
	for (int i = 0; i < 10000 ; i++)
	{
		GetLocalTime(&st);
		strtime.Format("%4d-%02d-%02d %02d:%02d:%02d.%03d\r\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds);
		CFile f;
		if (f.Open(".\\time.txt", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite))
		{
			f.SeekToEnd();
			f.Write(strtime, strtime.GetLength());
			f.Close();
		}
	}
	return;

	unsigned short ustt = 65534;
	ustt++;
	ustt++;
	ustt++;
	AfxMessageBox("111");
	WaitForSingleObject(g_hMutex, INFINITE);
	AfxMessageBox("222");
	ReleaseMutex(g_hMutex);
	return;

	CString tpstr;
	tpstr.Format("abc");
	int i = 1;
	switch (i)
	{
	case 1:
		int iii;
		iii = 1;
		break;
	}
	//CDialogEx::OnOK();
}


void CtttDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL b;
	//if (sockListen.m_hSocket)
	//{
	//	sockListen.Close();
	//}

	//b = TerminateThread(g_pThreadtest->m_hThread, 0);

	//if (sockListen)
	//{
	//	sockListen.Close();
	//}

	//b = TerminateThread(g_pThreadtest2->m_hThread, 0);
	//if (sockUDP.m_hSocket)
	//{
	//	sockUDP.Close();
	//}
	//ReleaseMutex(g_hMutex);

	g_pThreadtest = AfxBeginThread(Threadtest, this);
	Sleep(300);
	g_pThreadtest2 = AfxBeginThread(Threadtest2, this);
}


void CtttDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSocket s;
	int b;
	b = s.Create();
	CString ip;
	ip = "192.168.0.26";
	ip = "192.168.10.5";
	ip = "192.168.10.105";
	ip = "10.31.35.239";
	//b = s.Connect(ip, 5180);
	//b = s.Connect(ip, 5182);
	b = s.Connect("10.31.35.253", 4680);
	
	int ret = GetLastError();
	b = s.Send("11111", 5);
	s.Close();
}


void CtttDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSocket s;
	int b;
	CString ip;
	ip = "192.168.0.26";
	ip = "192.168.10.5";
	b = s.Create(0, SOCK_DGRAM);
	b = s.SendTo("11111", 5, 9000, ip);
	s.Close();
}

CString jiexidat(UT *filebuff, int buflen)
{
	MessageHead mh;
	IODeviceFixMsgHead iodf;
	IODeviceBaseMsg iodb;
	VehicleDetectorMsg vdm;
	if (buflen < (sizeof(mh) + sizeof(iodf) + sizeof(iodb)))
	{
		return "";
	}
	memcpy(&mh, filebuff, sizeof(mh));
	memcpy(&iodf, filebuff + sizeof(mh), sizeof(iodf));
	memcpy(&iodb, filebuff + sizeof(mh) + sizeof(iodf), sizeof(iodb));
	memcpy(&vdm, iodb.DeviceData, sizeof(vdm));
	CTime tim = vdm.Time;
	CString strtime = tim.Format("%Y.%m.%d %H:%M:%S");
	CString ret;
	ret.Format("%d	%d	%s	%d	%d	%d	%d	%d	%d	%d",
		vdm.VDDeviceID, vdm.LaneID, strtime, vdm.UnitTimeFlow, vdm.UnitTimeShortVehicleFlow, vdm.UnitTimeMiddleVehicleFlow, vdm.UnitTimeLongVehicleFlow, vdm.TotalFlow, vdm.TotalOccupancy, vdm.AverageSpeed);
	return ret;
}

void CtttDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CString strDataPath;
	strDataPath = "d:\\data\\*.*";
	CFileFind ff;
	BOOL bFind;
	CString strDataExtension = "dat";
	if (ff.FindFile(strDataPath))
	{
		do
		{
			bFind = ff.FindNextFile();
			if (ff.IsDots())
				continue;
			if (ff.IsDirectory())
			{
				continue;
			}
			CString filepath = ff.GetFilePath();
			if (strDataExtension.CompareNoCase(filepath.Right(3)) == 0)
			{
				CFile f;
				CString strdat;
				if (f.Open(filepath, CFile::modeRead))
				{
					int buflen = f.GetLength();
					if ((buflen > 0) && (buflen < 2000))
					{
						UT buf[2000];
						f.Read(buf, buflen);
						strdat = jiexidat(buf, buflen);
					}
					f.Close();
				}
				else
				{
					AfxMessageBox("open data file error!");
				}
				CString resultpath;
				resultpath = "d:\\result.txt";
				if (f.Open(resultpath, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
				{
					f.SeekToEnd();
					f.Write(strdat.GetBuffer(strdat.GetLength()), strdat.GetLength());
					strdat.ReleaseBuffer();
					f.Write("\r\n", 2);
					f.Close();
					//break;
				}
				else
				{
					AfxMessageBox("open result.txt error!");
				}
			}
		}while(bFind);
	}
}

//BOOL CtttDlg::DeviceDataToFile(US nDeviceIndex, void* pDeviceMsg, US nDeviceState)
//{
//	BOOL b = FALSE;
//	CString strDataFileHead;
//	switch (m_DeviceInfo[nDeviceIndex].Type)
//	{
//	case DEVICETYPE_LEDBOARDF:
//		strDataFileHead.Format("D%02d_%s_", nDeviceIndex + 1, DATAFILE_LEDBOARDF);
//		//strDataFileHead = DATAFILE_LEDBOARDXS;
//		break;
//	case DEVICETYPE_LEDBOARDXS:
//		strDataFileHead.Format("D%02d_%s_", nDeviceIndex + 1, DATAFILE_LEDBOARDXS);
//		//strDataFileHead = DATAFILE_LEDBOARDXS;
//		break;
//	case DEVICETYPE_VEHICLEDETECTOR:
//		strDataFileHead.Format("D%02d_%s_", nDeviceIndex + 1, DATAFILE_VEHICLEDETECTOR);
//		//strDataFileHead = DATAFILE_VEHICLEDETECTOR;
//		break;
//	case DEVICETYPE_METEO:
//		strDataFileHead.Format("D%02d_%s_", nDeviceIndex + 1, DATAFILE_METEO);
//		//strDataFileHead = DATAFILE_METEO;
//		break;
//	case DEVICETYPE_PM25:
//		strDataFileHead.Format("D%02d_%s_", nDeviceIndex + 1, DATAFILE_PM25);
//		//strDataFileHead = DATAFILE_PM25;
//		break;
//	default:
//		return FALSE;
//		break;
//	}
//	UT savebuf[2000];
//	int savelen;
//	savelen = DeviceDataSaveBuf(nDeviceIndex, savebuf, pDeviceMsg, nDeviceState);//�����ݴ���д�ļ���buf
//	if (savelen > 0)
//	{
//		//buf����ɹ�
//		for (int i = 0; i < 3 ; i++)
//		{
//			if (WriteDataFile(savebuf, savelen, WORKPATH + PATHDATA, strDataFileHead))//д��¼�ļ�
//			{
//				b = TRUE;
//				break;
//			}
//			Sleep(1000);
//		}
//		WriteDataFile(savebuf, savelen, WORKPATH + PATHDATABAK, strDataFileHead);//дbak�ļ�
//		//!!!WriteDataFile(savebuf, savelen, PATHDATABAK2, DATAFILE_METEO);//дbak2�ļ�
//	} 
//	else
//		return FALSE;//buf����ʧ��
//	return b;
//}

int GetRandom()
{
	return (rand() % 10 - 4);
}

BOOL CtttDlg::VDMsgGenerate(int nDeviceIndex, VehicleDetectorMsg* pVDMsg)
{
	CString strvalue;
	//int value;
	//US year, month, day, hour, minute, second;
	memset(pVDMsg, 0, sizeof(pVDMsg));

	pVDMsg->TotalFlow = 30 + GetRandom();
	pVDMsg->TotalOccupancy = 25 + GetRandom();
	pVDMsg->LongVehicleOccupancy = 5 + GetRandom();
	pVDMsg->MiddleVehicleOccupancy = 10 + GetRandom();
	pVDMsg->AverageSpeed = 65 + GetRandom();
	pVDMsg->UnitTimeFlow = 30 + GetRandom();
	pVDMsg->ShortVehicleOccupancy = 13 + GetRandom();
	pVDMsg->UnitTimeLongVehicleFlow = 5 + GetRandom();
	pVDMsg->UnitTimeShortVehicleFlow = 20 + GetRandom();
	pVDMsg->UnitTimeMiddleVehicleFlow = 5 + GetRandom();
	pVDMsg->HeadWay = 10 + GetRandom();
	pVDMsg->LongVehicleAverageSpeed = 41 + GetRandom();
	pVDMsg->MiddleVehicleAverageSpeed = 52 + GetRandom();
	pVDMsg->ShortVehicleAverageSpeed = 68 + GetRandom();
	pVDMsg->VDDeviceID = nDeviceIndex;
	pVDMsg->LaneID = 1;
	CTime now = CTime::GetCurrentTime();
	pVDMsg->Time = now.GetTime();

	return TRUE;
}

void CtttDlg::vdtest(int nDeviceIndex)
{
	CString tpstr;
	if (nDeviceIndex % 5 == 0)
		tpstr = "<0300210031FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210032FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003>";
	if (nDeviceIndex % 5 == 1)
		tpstr = "<0300210034FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210035FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210036FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003>";
	if (nDeviceIndex % 5 == 2)
		tpstr = "<0300210033FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210034FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003>";
	if (nDeviceIndex % 5 == 3)
		tpstr = "<0300210031FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210032FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210033FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003>";
	if (nDeviceIndex % 5 == 4)
		tpstr = "<0300210031FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210032FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210033FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210034FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210035FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003><0300210036FFFFFF003><6300000000000000003><6600000000000000003><6800000000000000003><0420130924220503003>";
	VehicleDetectorResponseProcess(tpstr);
	return;

	VehicleDetectorMsg vdmsg;
	if (VDMsgGenerate(nDeviceIndex, &vdmsg) > 0)//����Ϣ�ַ������ȡ����������
	{
		//�ɹ�����һ������������
		//��ʼ���������ļ�
		//if (DeviceDataToFile(nDeviceIndex, &vdmsg))
		//{
		//}
		//else
		//{
		//}
	}
}

#define AVC_MSGHEAD_SIZE	10	/* port + id + data1 + data2 */
#define AVC_MSGBUF_SIZE		512
#define AVC_MSG_LIMIT		(AVC_MSGHEAD_SIZE + AVC_MSGBUF_SIZE)
#define MSG_CTRL		5	/* host control */
#define CTL_DEQHEAD		3	/* deque one vehicle at head */

void AVCMsgSend( BYTE id, DWORD dwData1, DWORD dwData2, char *msgbuf, int size )
{
	char buf[AVC_MSG_LIMIT];

	//dwData1 = ntohl( dwData1 );
	//dwData2 = ntohl( dwData2 );
	buf[0] = 0;
	buf[1] = id;
	memcpy( buf+2, &dwData1, 4 );
	memcpy( buf+6, &dwData2, 4 );
	if ( size > 0 && buf != NULL )
		memcpy( buf+AVC_MSGHEAD_SIZE, msgbuf, size );
}

void CtttDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//int m_cmdRC = (0x40000000 & 0x80000000) != 0;
	//CString ttt = m_cmdRC ? "ʧ��" : "�ɹ�";
	//AVCMsgSend( MSG_CTRL, CTL_DEQHEAD, 0, NULL, 0 );
	//return;
	for (int i = 0; i < 100 ; i++)
	{
		m_nIndex = i;
		AfxBeginThread(ThreadVD, this);
		Sleep(100);
	}
}

void CtttDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	COdbcSql mySql;
	BOOL bret;
	int i;
	char strsql[5000];
	CTime ttime(2017, 4, 1, 0, 0, 0);
	CTime ttime1(2017, 4, 10, 0, 0, 0);
	CTimeSpan ttimespan(0, 0, 0, 5);
	while (ttime < ttime1)
	//while (i < 1)
	//for (int i = 20170100; i < 20170101 ; i++)
	{
		bret = mySql.Connect("1a", "", "");
		if (bret)
		{
			CString tpsql;
			//strcpy_s(strsql, "DELETE FROM ��1 where id = 1");
			//tpsql.Format("CREATE TABLE Device%d (DeviceTime date primary key, Lane int, Flow int, Speed int, TimeOccupancy int, HeadWay int)", i);
			//tpsql.Format("CREATE TABLE Device%d (DeviceDate date, DeviceTime time, Lane int, Flow int, Speed int, TimeOccupancy int, HeadWay int, primary key(DeviceDate, DeviceTime))", i);
			CString tptime = ttime.Format("%H:%M:%S");
			CString tpdate = ttime.Format("%Y-%m-%d");
			tpsql.Format("INSERT INTO Device5 VALUES ('%s', '%s', '1', '10', '20', '33', '5')", tpdate, tptime);
			CString tpts = ttime.Format("%Y-%m-%d %H:%M:%S");
			tpsql.Format("INSERT INTO Device6 VALUES ('%s', '1', '10', '20', '33', '5')", tpts);
			ttime += ttimespan;
			//tpsql.Format("SELECT * from Device1 where Flow = 10 order by DeviceDate,DeviceTime");
			//tpsql.Format("SELECT * from d1 where date1 > CDate('2017-4-19 0:0:0')");
			tpsql.Format("SELECT SUM(flow) as flowsum, SUM(TimeOccupancy) as timeocctotal from device6");
			
			//tpsql.Format("SELECT * INTO Device%d FROM Device1", i);//���Ʊ��ṹ������
			//insert into device5 select * from device3//���Ʊ�����
			//select * from Device1 union all select * from Device2//��ѯ2����ͬ�ı�
			//update device7 set devicedate=devicedate+1
			strcpy_s(strsql, tpsql);

			//update device5 set DeviceDate = DeviceDate+1


			bret = mySql.ExeSQLSearch(strsql);
			if (bret)
			{
				mySql.sr = SQLExecute ( mySql.m_hstmt );
				if ((mySql.sr == SQL_SUCCESS) || (mySql.sr == SQL_SUCCESS_WITH_INFO))
				{
					int tttt = 1;
					SDWORD cb;
					DATE_STRUCT zddate;
					TIME_STRUCT zdtime;
					TIMESTAMP_STRUCT zdts;
					int zd1, zd2, zd3, zd4, zd5;
					//mySql.sr = SQLBindCol(mySql.m_hstmt, 1, SQL_C_TYPE_DATE , &zddate, 6, &cb);
					//mySql.sr = SQLBindCol(mySql.m_hstmt, 1, SQL_C_TYPE_TIME , &zdtime, 6, &cb);SQLUINTEGER 
					//mySql.sr = SQLBindCol(mySql.m_hstmt, 1, SQL_C_TYPE_TIMESTAMP , &zdts, 20, &cb);
					SQLBindCol(mySql.m_hstmt, 1, SQL_C_SLONG, &zd1, 4, &cb);
					SQLBindCol(mySql.m_hstmt, 2, SQL_C_SLONG, &zd2, 4, &cb);
					//SQLBindCol(mySql.m_hstmt, 3, SQL_C_SLONG, &zd3, 4, &cb);
					//SQLBindCol(mySql.m_hstmt, 4, SQL_C_SLONG, &zd4, 4, &cb);
					//SQLBindCol(mySql.m_hstmt, 5, SQL_C_SLONG, &zd5, 4, &cb);
					mySql.sr = SQLFetch(mySql.m_hstmt);
					while ((mySql.sr == SQL_SUCCESS) || (mySql.sr == SQL_SUCCESS_WITH_INFO))
					{
						int i;
						mySql.sr = SQLFetch(mySql.m_hstmt);
					}
				}
				else
				{
					AfxMessageBox("sql execute error!");
				}
			}
			else
			{
				AfxMessageBox("sql search error!");
			}
			mySql.DisConnect();
		}
		//Sleep(10);
	}
	

	CSocket s;
	int b; 
	BYTE recvbuf[1000];
	CString ip;
	CString tpstr;
	tpstr.Format("123 55%%66");
	b = s.Send("111", 3);
	return;
	b = s.Create();
	ip = "192.168.10.5";
	ip = "192.168.0.26";
	ip = "139.224.25.27";
	//b = s.Connect(ip, 5180);
	b = s.Connect(ip, 10000);
	int ret1 = GetLastError();
	tpstr = "{\"code\":\"2\", \"token\":\"3510\"}";
	memcpy(recvbuf, tpstr.GetBuffer(tpstr.GetLength()), tpstr.GetLength());
	tpstr.ReleaseBuffer();
	b = s.Send(tpstr.GetBuffer(tpstr.GetLength()), tpstr.GetLength());
	tpstr.ReleaseBuffer();
	b = s.Receive(recvbuf, 1000);
	s.Close();
}

int CtttDlg::VehicleDetectorResponseProcess(CString strVDRaw)
{
	CString strvd;
	int nbegin = 0;
	do 
	{
		nbegin = GetValidString(strVDRaw, strvd, nbegin, 21, STRINGMODEVEHICLEDETECTOR);
	} while (nbegin >= 0);
	return 1;
}

int CtttDlg::GetValidString(CString strInput, CString& strOutput, int nSearchBeginNum, int nStringMinLen, int nStringMode)
{
	CString strbegin, strend;
	switch (nStringMode)
	{
	case STRINGMODEMETEO:
	default:
		strbegin = '[';
		strend = ']';
		break;
	case STRINGMODEVEHICLEDETECTOR:
		strbegin = '<';
		strend = '>';
		break;
	}
	int nhead = strInput.Find(strbegin, nSearchBeginNum);
	int nend = strInput.Find(strend, nSearchBeginNum);
	if ((nhead < 0) || (nend < 0))
	{
		strOutput = "";
		return -1;
	}
	if ((nend - nhead + 1) < nStringMinLen)
	{
		strOutput = "";
		return nend + 1;
	}
	strOutput = strInput.Mid(nhead, nend - nhead + 1);
	return nend + 1;
}

void CtttDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//C m_DeviceID[6];
	//m_DeviceID[0] = 0x12;
	//m_DeviceID[1] = 0x34;
	//m_DeviceID[2] = 0x56;
	//m_DeviceID[3] = 0x78;
	//m_DeviceID[4] = 0x9a;
	//m_DeviceID[5] = 0xbc;
	//CString strSnapshot;
	//strSnapshot.Format("snapshot_%x%x%x%x%x%x", (BYTE)m_DeviceID[0], (BYTE)m_DeviceID[1], (BYTE)m_DeviceID[2], (BYTE)m_DeviceID[3], (BYTE)m_DeviceID[4], (BYTE)m_DeviceID[5]);
	//return;
	int nstate = m_VLCPlayer[0].GetState();
	if ((m_VLCPlayer[0].GetState() >= 3) && (m_VLCPlayer[0].GetState() < 5))
	{
		m_VLCPlayer[0].CloseVideo();
	}
	else
	{
		m_VLCPlayer[0].Init("d:\\1.ini", "192.168.71.51", FALSE);

		m_VLCPlayer[0].CloseVideo();
		m_VLCPlayer[0].PlayVideo(GetDlgItem(IDC_STATIC_VIDEO)->m_hWnd);
	}
	//2
	nstate = m_VLCPlayer[1].GetState();
	if ((m_VLCPlayer[1].GetState() >= 3) && (m_VLCPlayer[1].GetState() < 5))
	{
		m_VLCPlayer[1].CloseVideo();
	}
	else
	{
		m_VLCPlayer[1].Init("d:\\1.ini", "192.168.71.52", FALSE, 1);

		m_VLCPlayer[1].CloseVideo();
		m_VLCPlayer[1].PlayVideo(GetDlgItem(IDC_STATIC_VIDEO2)->m_hWnd);
	}
}

UL GetMessageID()
{
	static UL msgid = 0;
	msgid++;
	if (msgid > 1000000000)
		msgid = 0;
	return msgid;
}

BOOL CtttDlg::TakeSnapshot()
{
	BOOL bret = TRUE;
	static int count = 0;
	for (int i = 0; i < 2 ; i++)
	{
		int nstate = m_VLCPlayer[i].GetState();
		if ((m_VLCPlayer[i].GetState() >= 3) && (m_VLCPlayer[i].GetState() < 5))
		{
			count++;
			CString strSnapshot;
			strSnapshot.Format("t:\\t\\snapshot%d_%03d.png", i + 1, count);
			BOOL b = m_VLCPlayer[i].TakeSnapshot(strSnapshot, 640);//!!ͼƬ��������`
			if (b)
			{
				CString stroption, strSnapshotConvert;
				stroption.Format("-resize 960 -quality 60%%");//���ָ߿�Ƚ�ͼ���ȵ�����960��jpgͼ���������ó�60%
				strSnapshotConvert.Format("t:\\t\\snapshotconvert%d_%03d.jpg", i+ 1, count);
				ProcessImage(strSnapshot, strSnapshotConvert, "jpg", stroption, FALSE);
				//for (int i = 10; i > 4; i--)
				//{
				//	int per = i * 10;
				//	CString stroption, strper, file;
				//	stroption.Format("-resize 50%% -quality %d%%", per);
				//	strper.Format("q%d", per);
				//	file= strSnapshot;
				//	file.Replace(".png", ".jpg");
				//	file.Insert(file.Find(".jpg"), strper);
				//	ProcessImage(strSnapshot, file, "jpg", stroption, FALSE);
				//}
				//��ȡ�ļ�
				CFile f;
				//BYTE filebuf[MAXIMAGEFILELENGTH];
				BYTE *filebuf = new BYTE[MAXIMAGEFILELENGTH];
				UL filelen = 0;
				TRY 
				{
					if (f.Open(strSnapshotConvert, CFile::modeRead))
					{
						filelen = f.GetLength();
						if (filelen > MAXIMAGEFILELENGTH)
						{
							f.Close();
							return FALSE;
						}
						f.Read(filebuf, filelen);
						f.Close();
					}
				}
				CATCH( CFileException, e )
				{
#ifdef _DEBUG
					afxDump << "File could not be opened " << e->m_cause << "\n";
#endif
					return FALSE;
				}
				END_CATCH

				//��ͷ
				m_MessageHead.SetStatus(STATUS_REQUEST);
				C m_SelfID[6];
				C m_ServerID[6];
				m_SelfID[0] = 0x1f;
				m_SelfID[1] = m_SelfID[2] = m_SelfID[3] = m_SelfID[4] = m_SelfID[5] = 1;
				m_ServerID[0] = 0x1f;
				m_ServerID[1] = m_ServerID[4] = m_ServerID[5] = 1;
				m_ServerID[2] = m_ServerID[3] = 0;
				memcpy(m_MessageHead.utSendID, m_SelfID, sizeof(m_SelfID));
				memcpy(m_MessageHead.utReceiveID, m_ServerID, sizeof(m_ServerID));
				m_MessageHead.SetMessageID(GetMessageID());
				m_MessageHead.SetTranType(TRANTYPE_IOTOSERVERVARIETY);
				//����
				IODeviceVarietyMsg iodevicevarietymsghd;
				iodevicevarietymsghd.RecordType = RECORDTYPE_DEVICE;
				//SetSendID(iodevicevarietymsghd.SendID);
				iodevicevarietymsghd.BaseMsg.DeviceState = DEVICESTATE_NORMAL;
				iodevicevarietymsghd.DataLength = sizeof(VideoSnapshot) + filelen;
				iodevicevarietymsghd.BaseMsg.DeviceID[0] = i + 1;
				VideoSnapshot videoss;
				UL datalen;
				videoss.ImageFileType = 2;
				datalen = sizeof(IODeviceVarietyMsg);
				datalen = sizeof(VideoSnapshot);
				datalen = sizeof(IODeviceVarietyMsg) + sizeof(VideoSnapshot) + filelen;
				m_MessageHead.SetDataLen(datalen);

				BYTE *pbufsend = new BYTE[MAXIMAGEFILELENGTH + 1024];
				memcpy(pbufsend, &m_MessageHead, sizeof(MessageHead));
				memcpy(pbufsend + sizeof(MessageHead), &iodevicevarietymsghd, sizeof(IODeviceVarietyMsg));
				memcpy(pbufsend + sizeof(MessageHead) + sizeof(IODeviceVarietyMsg), &videoss, sizeof(VideoSnapshot));
				memcpy(pbufsend + sizeof(MessageHead) + sizeof(IODeviceVarietyMsg) + sizeof(VideoSnapshot), filebuf, filelen);
				datalen += sizeof(MessageHead);

				//���ԣ�������bufд�ļ�
				//TRY 
				//{
				//	if (f.Open("t:\\1.dat", CFile::modeReadWrite|CFile::modeCreate))
				//	{
				//		f.Write(pbufsend, datalen);
				//		f.Close();
				//	}
				//}
				//CATCH( CFileException, e )
				//{
				//	return FALSE;
				//}
				//END_CATCH

				//�������߳�
				//AfxBeginThread(ThreadImageRecieve, this);
				//Sleep(100);

				//����
				CSocket s;
				BYTE bufrecv[500];
				int nrecv;
				MessageHead mh;
				ResponseMsg rm;
				b = s.Create();
				if (b)
				{
					b = s.Connect("192.168.10.11", 5180);//!!ip��port��������
					//b = s.Connect("192.168.0.26", 4680);//!!ip��port��������
					if (b)
					{
						nrecv = s.Send(pbufsend, datalen);
						nrecv = s.Receive(&bufrecv, 500);
						s.Close();
						if (nrecv >= (sizeof(MessageHead) + sizeof(ResponseMsg)))
						{
							memcpy(&mh, bufrecv, sizeof(MessageHead));
							memcpy(&rm, bufrecv + sizeof(MessageHead), sizeof(ResponseMsg));
						}
					}
				}
				delete []filebuf;
				delete []pbufsend;
			}
			else
				bret = FALSE;
		}
	}
	return bret;
}

void CtttDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSnapshot;
	//for (int i = 0; i < 10 ; i++)
	//{
	//	strSnapshot.Format("t:\\t\\snapshot%02d.png", i + 1);
	//	int ii;
	//	if (i == 0)
	//		ii = 640;
	//	else
	//		ii = 192 * (i + 1);
	//	BOOL b = m_VLCPlayer[1].TakeSnapshot(strSnapshot, ii);//!!ͼƬ��������
	//}
	//return;
	if (!m_bTakingSnapshot)
	{
		m_bTakingSnapshot = !m_bTakingSnapshot;
		SetTimer(5, 100, NULL);
	} 
	else
	{
		m_bTakingSnapshot = !m_bTakingSnapshot;
		KillTimer(5);
	}
}

BOOL CtttDlg::ProcessImage(CString imagesrc, CString imagedest, CString imagetype, CString imageoptions, BOOL bDebug)
{
	CString strcmd;
	HINSTANCE ret;
	if (imagetype == "")
		strcmd.Format("/C convert \"%s\" %s \"%s\" ", imagesrc, imageoptions, imagedest);
	else
		strcmd.Format("/C convert \"%s\" %s %s:\"%s\" ", imagesrc, imageoptions, imagetype, imagedest);
	if (bDebug)
		ret = ShellExecute(NULL, "open", "cmd", strcmd, "C:\\Program Files\\ImageMagick-7.0.5-Q8\\", SW_SHOW);
	else
		ret = ShellExecute(NULL, "open", "cmd", strcmd, "C:\\Program Files\\ImageMagick-7.0.5-Q8\\", SW_HIDE);
	DWORD dw = WaitForSingleObject(ret, INFINITE);//WAIT_OBJECT_0
	if ((int)ret > 32)
		return TRUE;
	else
		return FALSE;
}

void CtttDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ProcessImage("t:\\1.png", "t:\\b50.jpg", "jpg", " -quality 50%", FALSE);
	CString tps = " /C dir && pause && \"magick t:\\snapshot.bmp t:\\111.jpg\"  && pause";
	tps = " /C dir && pause";
	//tps = "dir && pause && \"cd C:\\Program Files\\ImageMagick-7.0.5-Q8\\ \" && pause && \"magick t:\\snapshot.bmp t:\\111.jpg\" && pause";
	//tps = "/K convert \"t:\\1.png\" jpg:t:\\111.jpg ";
	//tps = " /K dir";
	//system(tps);
	//return;
	HINSTANCE ret;
	for (int i = 0; i < 10 ; i++)
	{

		//ret = ShellExecute(NULL, "open", "cmd", tps, NULL, SW_SHOW);
	}
	int i;
	i = 1;
	i = 2;
	CString strSnapshot, stroption, strSnapshotConvert;
	stroption.Format("-resize 960 -quality 60%%");//���ָ߿�Ƚ�ͼ���ȵ�����960��jpgͼ���������ó�60%
	strSnapshot.Format("t:\\t\\IMG*.jpg");
	strSnapshotConvert.Format("t:\\t\\IMGCVT.jpg");
	tps.Format(" \"%s\" %s \"%s\" ", strSnapshot, stroption, strSnapshotConvert);
	//ret = ShellExecute(NULL, "open", "convert.exe", tps, "C:\\Program Files\\ImageMagick-7.0.5-Q8\\", SW_HIDE);
	//DWORD dw = WaitForSingleObject(ret, INFINITE);//WAIT_OBJECT_0

	//ret = ShellExecute(NULL, "open", "cmd", tps, "C:\\Program Files\\ImageMagick-7.0.5-Q8\\", SW_SHOW);
	//tps = "cmd.exe " + tps;
	//WinExec(tps, SW_SHOW);
	//ret = ShellExecute(NULL, "open", "C:\\Program Files\\ImageMagick-7.0.5-Q8\\convert.exe", "t:\\1.png -resize 50% BMP:t:\\222.jpg", NULL, SW_SHOW);
	//ret;//ERROR_FILE_NOT_FOUND 
	SHELLEXECUTEINFO ShExecInfo = {0};
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "convert.exe";
	ShExecInfo.lpParameters = tps;
	ShExecInfo.lpDirectory = "C:\\Program Files\\ImageMagick-7.0.5-Q8\\";
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
}

void testfunc(CString* strpar = NULL)
{
	if (strpar != NULL)
	{
		*strpar = "123";
	}
}

void CtttDlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSnapshot, stroption, strSnapshotConvert;
	stroption.Format("-resize 960 -quality 60%%");//���ָ߿�Ƚ�ͼ���ȵ�����960��jpgͼ���������ó�60%
	strSnapshot.Format("t:\\t\\IMG*.jpg");
	strSnapshotConvert.Format("t:\\t\\IMGCVT.jpg");
	ProcessImage(strSnapshot, strSnapshotConvert, "", stroption, TRUE);
	int i= 1;
	return;

	BYTE tttt[500*1024];
	memset(tttt, 0, sizeof(tttt));
	CString filebuf;
	CFile f;
	int filelen;
	TRY 
	{
		if (f.Open("t:\\11.jpg", CFile::modeReadWrite))
		{
			filelen = f.GetLength();
			f.Read(tttt, filelen);
			//filebuf.ReleaseBuffer();
			f.Close();
		}
		if (f.Open("t:\\11t.jpg", CFile::modeCreate | CFile::modeReadWrite))
		{
			f.Write(tttt, filelen);
			//filebuf.ReleaseBuffer();
			f.Close();
		}
	}
	CATCH( CFileException, e )
	{
		return;
	}
	END_CATCH
		CSocket s;
	if (s.Create())
	{
		if (s.Connect("192.168.0.26", 5180))
		{
			int nn;
			nn = s.Send(tttt, filelen);
			nn = s.Receive(tttt, 200);
			Sleep(1000);
		}
		s.Close();
	}

	double ddd1 , ddd2;
	ddd1 = 0.12345;
	ddd2 = 1234567890123.1234567890;
	CString tpstr;
	unsigned int uitta;
	uitta = 100-200;
	CString strCommand, strDeviceNum, strParam;
	CTime now;
	int nDeviceNum = 3;
	strDeviceNum.Format("%03d", nDeviceNum);
	now = CTime::GetCurrentTime();
	strParam = now.Format("%Y%m%d%H%M00");
	strCommand.Format("<95%s%s>", strParam, strDeviceNum);
	return;

	//tpstr = "abcdefg";
	//testfunc();
	//testfunc(&tpstr);
	//tpstr.ReleaseBuffer();

	//CSocket s;
	int ret;
	BYTE chtp[100];
	if (s.Create())
	{
		if (s.Connect("192.168.110.240", 1024))
		//if (s.Connect("192.168.0.26", 54517))
		{
			tpstr = "<shut,22>";
			tpstr = "<open,22,16,0,3840,0,5760,1080>";
			ret = s.Send(tpstr.GetBuffer(tpstr.GetLength()), tpstr.GetLength());
			tpstr.ReleaseBuffer();
			ret = s.Receive(chtp, sizeof(chtp));
		}
		s.Close();
	}
}


//void DisplayDZ()
//{
//	int    i,j,k;   
//	unsigned    char    incode[3]="��";    //    Ҫ�����ĺ���   
//	unsigned    char    qh,wh;   
//	unsigned    long    offset;   
//	//    ռ�����ֽ�,    ȡ����λ��   
//	qh    =    incode[0]    -    0xa0;//�������            
//		wh    =    incode[1]    -    0xa0;   //���λ��               
//		offset    =    (94*(qh-1)+(wh-1))*32;          /*�õ�ƫ��λ��*/   
//
//		FILE    *HZK;   
//	char    mat[32];   
//	if((HZK=fopen("hzk16",    "rb"))    ==    NULL)   
//	{   
//		printf("Can't    Open    hzk16\n");   
//		exit(0);   
//	}   
//	fseek(HZK,    offset,    SEEK_SET);   
//	fread(mat,    32,    1,    HZK);
//	//��ʾ
//	for(j=0;j<16;j++)
//		for(i=0;i<2;i++)
//			for(k=0;k<8;k++)
//				if(mat[j][i]&(0x80>>k))
//				{
//					printf("%s",'#');
//				}
//				else
//				{
//					printf("%s",'-');
//				}
//
//	fclose(HZK);
//	fclose(fp);
//}

//#define FONTSIZE1 16  
#define FONTSIZE1 24  

int Not_In_Lib(char buff[FONTSIZE1 * FONTSIZE1 / 8])  
{  
	for (int i = 0; i < FONTSIZE1 * FONTSIZE1 / 8; i++)  
	{  
		if (buff[i])   //�����һ����Ϊ0������buff�����Ѿ����޸Ĺ����ֿ���ڴ����˳��˺���  
			return 0;  
	}  
	return 1;  
}  

int Get_Asc_Code(unsigned char *Get_Input_Char, char buff[])  
{  
	unsigned long offset;  
	FILE *ASC;  
	/*���ֿ��ļ�asc16*/  
	CString filename;
	filename.Format("t:\\ASC%d", FONTSIZE1);
	if ((ASC = fopen(filename, "rb+")) == NULL)  
	{  
		printf("Can't open asc,Please add it?");    
		return 0;
	}  
	//offset = *(Get_Input_Char) * 16;         /*ͨ��ascii�����ƫ����*/  
	offset = *(Get_Input_Char) * FONTSIZE1 * (((FONTSIZE1 / 2) + 7) / 8);         /*ͨ��ascii�����ƫ����*/ 
	fseek(ASC, offset, SEEK_SET);                /*���ļ�ָ���ƶ���ƫ������λ��*/  
	//fread(buff, 16, 1, ASC);                     /*��ƫ������λ�ö�ȡ32���ֽ�*/  
	fread(buff, FONTSIZE1 * (((FONTSIZE1 / 2) + 7) / 8), 1, ASC);                     
	printf("ASCII:%d,offset:%d \n\r", *Get_Input_Char, offset);  
	fclose(ASC);  
	return 1;  
}  

CString Print_Asc_Char(char *mat, char *Out_Put_1, char *Out_Put_2)  
{  
	int i, j, k; 
	CString strout = ""; 
	for (i = 0; i < FONTSIZE1; i++)          /*FONTSIZE1�����֣�һ����FONTSIZE1��*/  
	{  
		//int tt = ((FONTSIZE1 / 2) + 7) / 8;
        int size = ((FONTSIZE1 / 2) + 7) / 8;     //һ�е��ֽ���
        for (j = 0; j < size; j++)       /*ÿ����N���ֽڣ�ѭ���ж�ÿ���ֽ�*/
		//for (j = 0; j < ((FONTSIZE1 / 2) + 7) / 8; j++)       /*ÿ����N���ֽڣ�ѭ���ж�ÿ���ֽ�*/  
		{
			for (k = 0; k < 8; k++)       /*ÿ���ֽ���8λ��ѭ���ж�ÿλ�Ƿ�Ϊ1*/  
			{
                int index = i * size + j;
				//int tt = i * (((FONTSIZE1 / 2) + 7) / 8) + j;
                if (mat[index] & (0x80 >> k)) /*���Ե�ǰλ�Ƿ�Ϊ1*/
				//if (mat[i * (((FONTSIZE1 / 2) + 7) / 8) + j] & (0x80 >> k)) /*���Ե�ǰλ�Ƿ�Ϊ1*/  
				{
					printf("%s", Out_Put_1);         /*Ϊ1����ʾΪ�ַ�c1*/  
					strout += Out_Put_1;
				}
				else
				{
					printf("%s", Out_Put_2);     /*Ϊ0����ʾΪ�ַ�c2*/  
					strout += Out_Put_2;
				}
			}
		}
		printf("\n");                   /*����һ���Ժ󣬽��л���*/  
		strout += "\r\n";
	}    

	//for (i = 0; i < 24; i++)          /* 8x16�ĵ���һ����16��*/  
	////for (i = 0; i < 16; i++)          /* 8x16�ĵ���һ����16��*/  
	//{
	//	for ()
	//	for (j = 0; j < 16; j++)         /*����һ���ֽ�8λ�������ж�ÿλ�Ƿ�Ϊ0*/  
	//	//for (j = 0; j < 8; j++)         /*����һ���ֽ�8λ�������ж�ÿλ�Ƿ�Ϊ0*/  
	//	{
	//		if (mat[i] & (0x80 >> j))   /*���Ե�ǰλ�Ƿ�Ϊ1*/  
	//		{
	//			printf("%s", Out_Put_1);      /*Ϊ1����ʾΪ�ַ�c1*/  
	//			strout += Out_Put_1;
	//		}
	//		else
	//		{
	//			printf("%s", Out_Put_2);      /*Ϊ0����ʾΪ�ַ�c2*/  
	//			strout += Out_Put_2;
	//		}
	//	}
	//	printf("\n");                   /*����һ���Ժ󣬽��л���*/  
	//	strout += "\r\n";
	//}  
	return strout;
}  

int Get_HzK_Code(unsigned char *Get_Input_Char, char buff[])  
{  
	int not_find = 0;  
	unsigned char qh, wh;  
	unsigned long offset;  
	FILE *HZK;  
	CString filename;
	filename.Format("t:\\HZK%d", FONTSIZE1); 
	if ((HZK = fopen(filename, "rb+")) == NULL) /*���ֿ��ļ�hzk16*/  
	{  
		printf("Can't open,Please add it?\n");  
		return 0;
	}  
	/*����=����(���ֽ�)-160  λ��=����(���ֽ�)-160*/  
	qh     = *(Get_Input_Char) - 0xa0;           /*10���Ƶ�160����16���Ƶ�A0*/  
	wh     = *(Get_Input_Char + 1) - 0xa0;       /*���������λ��*/  
	offset = (94 * (qh - 1) + (wh - 1)) * FONTSIZE1 * FONTSIZE1 / 8; /*����ú������ֿ���ƫ����*/  
	not_find = fseek(HZK, offset, SEEK_SET); /*���ļ�ָ���ƶ���ƫ������λ��*/  
	if (not_find)  
	{  
		printf("δ�鵽������error������\n");  
		fclose(HZK);  
		return 0;  
	}  
	fread(buff, FONTSIZE1 * FONTSIZE1 / 8, 1, HZK);    /*��ƫ������λ�ö�ȡ32���ֽ�*/  
	if (Not_In_Lib(buff))  
	{  
		fclose(HZK);  
		printf("��δʶ���ַ�!\n");  
		system("pause");  
		return 0;  
	}  
	printf("qh:%d,wh:%d,offset:%ld\n\r", qh, wh, offset);  
	fclose(HZK);  
	return 1;  
}  

CString Print_HzK_Char(char *mat, char *Out_Put_1, char *Out_Put_2)  
{  
	int i, j, k;  
	CString strout = "";
	for (i = 0; i < FONTSIZE1; i++)          /*16x16�����֣�һ����16��*/  
	{  
		for (j = 0; j < FONTSIZE1 / 8; j++)       /*������2���ֽڣ�ѭ���ж�ÿ���ֽڵ�*/  
		{
			for (k = 0; k < 8; k++)       /*ÿ���ֽ���8λ��ѭ���ж�ÿλ�Ƿ�Ϊ1*/  
			{
				if (mat[i * FONTSIZE1 / 8 + j] & (0x80 >> k)) /*���Ե�ǰλ�Ƿ�Ϊ1*/  
				{
					printf("%s", Out_Put_1);         /*Ϊ1����ʾΪ�ַ�c1*/  
					strout += Out_Put_1;
				}
				else
				{
					printf("%s", Out_Put_2);     /*Ϊ0����ʾΪ�ַ�c2*/  
					strout += Out_Put_2;
				}
			}
		}
		printf("\n");                   /*����һ���Ժ󣬽��л���*/  
		strout += "\r\n";
	}    
	for (j = 0; j < FONTSIZE1 / 8; j++)       /*������2���ֽڣ�ѭ���ж�ÿ���ֽڵ�*/  
	{
		for (k = 0; k < 8; k++)       /*ÿ���ֽ���8λ��ѭ���ж�ÿλ�Ƿ�Ϊ1*/  
		{  
			for (i = 0; i < FONTSIZE1; i++)          /*16x16�����֣�һ����16��*/  
			{  
				if (mat[i * FONTSIZE1 / 8 + j] & (0x80 >> k)) /*���Ե�ǰλ�Ƿ�Ϊ1*/  
				{
					printf("%s", Out_Put_1);         /*Ϊ1����ʾΪ�ַ�c1*/  
					strout += Out_Put_1;
				}
				else
				{
					printf("%s", Out_Put_2);     /*Ϊ0����ʾΪ�ַ�c2*/  
					strout += Out_Put_2;
				}
			}  
			printf("\n");                   /*����һ���Ժ󣬽��л���*/  
			strout += "\r\n";
		}
	}
	return strout;
}  

void CtttDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char Buffer_English[72], Buffer_Chinese[FONTSIZE1 * FONTSIZE1 / 8];  
	unsigned char word[3] = {0};  
	unsigned char num[3] = {0};  
	num[0] = '2';
	memset(Buffer_English, 0, sizeof(Buffer_English));  
	memset(Buffer_Chinese, 0, sizeof(Buffer_Chinese)); 
	word[0] = 0xbc;
	word[1] = 0xce; 
	memcpy(word, "��", 2);
	char *Output_String1 = (char *)"��", *Output_String2 = (char *)"��"; 

	if (Get_Asc_Code(num, Buffer_English))  
	{  
		CString tpstr;
		tpstr = Print_Asc_Char(Buffer_English, Output_String1, Output_String2);  
		AfxMessageBox(tpstr);
		CFile f;
		if (f.Open("t:\\outasc.txt", CFile::modeCreate|CFile::modeWrite))
		{
			f.Write(tpstr.GetBuffer(tpstr.GetLength()), tpstr.GetLength());
			tpstr.ReleaseBuffer();
			f.Close();
		}
		memset(Buffer_English, 0, sizeof(Buffer_English));  
	}  
	if (Get_HzK_Code(word, Buffer_Chinese))  
	{  
		CString tpstr;
		tpstr = Print_HzK_Char(Buffer_Chinese, Output_String1, Output_String2);  
		AfxMessageBox(tpstr);
		CFile f;
		if (f.Open("t:\\outhzk.txt", CFile::modeCreate|CFile::modeWrite))
		{
			f.Write(tpstr.GetBuffer(tpstr.GetLength()), tpstr.GetLength());
			tpstr.ReleaseBuffer();
			f.Close();
		}
		memset(Buffer_Chinese, 0, sizeof(Buffer_Chinese));  
	}  
}

void CtttDlg::OnBnClickedButton12()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strbuf, strout;
	CFile f;
	int filelen;
	TRY 
	{
		//if (f.Open("t:\\t1.txt", CFile::modeReadWrite))
		if (f.Open("t:\\2.jpg", CFile::modeReadWrite))
		{
			filelen = f.GetLength();
			f.Read(strbuf.GetBuffer(filelen), filelen);
			strbuf.ReleaseBuffer();
			f.Close();
		}
	}
	CATCH( CFileException, e )
	{
		return;
	}
	END_CATCH
	//filelen = BASE64_Decode(strbuf.GetBuffer(strbuf.GetLength()), strbuf.GetLength(), (BYTE *)strout.GetBuffer(100000));
	filelen = BASE64_Encode((BYTE *)strbuf.GetBuffer(filelen), filelen, strout.GetBuffer(100000));
	strbuf.ReleaseBuffer();
	strout.ReleaseBuffer();
	TRY 
	{
		//if (f.Open("t:\\t1.jpg", CFile::modeCreate | CFile::modeReadWrite)
		if (f.Open("t:\\base64.txt", CFile::modeCreate | CFile::modeReadWrite))
		{
			f.Write(strout.GetBuffer(filelen), filelen);
			strout.ReleaseBuffer();
			f.Close();
		}
	}
	CATCH( CFileException, e )
	{
		return;
	}
	END_CATCH
		;
	return;

	CString tpstr;
	int len;
	len = BASE64_Encode((BYTE *)strout.GetBuffer(filelen), filelen, tpstr.GetBuffer(100000));
	tpstr.ReleaseBuffer();
	TRY 
	{
		if (f.Open("t:\\t1base64.txt", CFile::modeCreate | CFile::modeReadWrite))
		{
			f.Write(tpstr.GetBuffer(len), len);
			tpstr.ReleaseBuffer();
			f.Close();
		}
	}
	CATCH( CFileException, e )
	{
		return;
	}
	END_CATCH
}

BOOL WriteLog(CString strtip)
{
	//д�ļ�
	CFile f;
	CString filename, path, strtime;
	CTime now = CTime::GetCurrentTime();
	path = ".\\log\\";
	strtime = now.Format("%Y%m%d");
	filename = strtime;
	filename += ".txt";
	strtime = now.Format("%Y.%m.%d %H:%M:%S:");
	//TRY 
	{
		MakeSureDirectoryPathExists(path);
		if (f.Open(path + filename, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
		{
			f.SeekToEnd();
			f.Write(strtime.GetBuffer(strtime.GetLength()), strtime.GetLength());
			strtime.ReleaseBuffer();
			f.Write(strtip.GetBuffer(strtip.GetLength()), strtip.GetLength());
			strtip.ReleaseBuffer();
			f.Write("\r\n", 2);
			f.Close();
		}
	}
//	CATCH( CFileException, e )
//	{
//#ifdef _DEBUG
//		afxDump << "File could not be opened " << e->m_cause << "\n";
//#endif
//		return FALSE;
//	}
//	END_CATCH
		return TRUE;
}

LRESULT CtttDlg::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	CString tpstr = "A";
	char *pstr;
	switch (wParam)
	{
	case MESSAGEUPDATESERVERTIP:
		pstr = (char *)lParam;
		tpstr = pstr;
		WriteLog(tpstr);
		delete[] pstr;
		break;
	case MESSAGEUPDATETESTTIP:
		//WriteLog(g_strTest);
		tpstr = g_strTest;
		WriteLog(tpstr);
	}
	return 0 ;
}

UINT TestMsgThread1( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)pParam;
	CString tpstr;
	static int count = 0;
	for (int count = 0; count < 1000 ; count++)
	{
		char *pMsg = new char[500];
		tpstr.Format("AAA֪ͨ��Ϣ��¼��־�ַ���a long string����@#������&*��������=%d", count);
		strcpy(pMsg, (LPCTSTR)tpstr);
		ShowServerMessage(pDlg->m_hWnd, pMsg);
		Sleep(1);
	}
	return 0;
}
UINT TestMsgThread2( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)pParam;
	CString tpstr;
	static int count = 0;
	for (int count = 0; count < 1000 ; count++)
	{
		char *pMsg = new char[500];
		tpstr.Format("BBB֪ͨ��Ϣ��¼��־�ַ���a long string����@#������&*��������=%d", count);
		strcpy(pMsg, (LPCTSTR)tpstr);
		ShowServerMessage(pDlg->m_hWnd, pMsg);
		Sleep(1);
	}
	return 0;
}
UINT TestMsgThread3( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)pParam;
	CString tpstr;
	static int count = 0;
	for (int count = 0; count < 1000 ; count++)
	{
		char *pMsg = new char[500];
		tpstr.Format("CCC֪ͨ��Ϣ��¼��־�ַ���a long string����@#������&*��������=%d", count);
		strcpy(pMsg, (LPCTSTR)tpstr);
		ShowServerMessage(pDlg->m_hWnd, pMsg);
		Sleep(1);
	}
	return 0;
}

void CtttDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxBeginThread(TestMsgThread1, this);
	AfxBeginThread(TestMsgThread2, this);
	AfxBeginThread(TestMsgThread3, this);
}

void Fun2()
{
	//char tpch[200];
	//memset(tpch, 0, 300);
	//tpch[-1] = 1;
	int *p = NULL;
	*p = 0;
}

void Fun()
{
	Fun2();
}

void CtttDlg::OnBnClickedButton14()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	Fun();
	//MyUnhandledExceptionFilter(GetExceptionInformation());
	//try
	__try
	{
		Fun();
	}
	//catch (MyUnhandledExceptionFilter())
	//{
	//}
	//catch (...)
	__except(MyUnhandledExceptionFilter(GetExceptionInformation()))
	{
		AfxMessageBox("error!");
	}
	AfxMessageBox("continue running");
}
//_set_invalid_parameter_handler(HandleInvalidParameter)


void CtttDlg::OnBnClickedButton15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	double tpdb;
	CString tpstr, key;
	tpdb = 1234567890123;
	1503885498812;
	tpstr.Format("%f", tpdb);
	key.Format("DataChangeTime");
	WritePrivateProfileString("YunPark", key, tpstr, ".\\1.ini");
	GetPrivateProfileString("YunPark", key, "", tpstr.GetBuffer(MAX_PATH), MAX_PATH, ".\\1.ini");
	tpstr.ReleaseBuffer();
	tpdb = atof(tpstr);
	tpdb = tpdb;
}

bool CalculateFee_Rate(unsigned long minutes, unsigned long &Fee)
{
	//���ʱ�
	unsigned long AllFee = 0;
	CString strTlb = ".\\FeeRate.tlb";
	CFile f;
	if (!f.Open(strTlb, CFile::modeRead))
		//QString strTlb = m_strTlbPath + TLB_FEERATE;
		//QFile f(strTlb);
		//if(!f.open(QIODevice::ReadOnly))
		return false;
	char * buf = new char[(UINT)f.GetLength()];
	ULONGLONG ret = f.Read(buf, (UINT)f.GetLength());
	if(f.GetLength() != ret)
		//char * buf = new char[f.size()];
		//int ret = f.read(buf, f.size());
		//if(f.size() != ret)
	{
		delete []buf;
		return false;
	}
	f.Close();
	//f.close();
	Fee_RateTlb * pTlb = reinterpret_cast<Fee_RateTlb *>(buf);
	if(pTlb->FreeTime >= minutes)
	{
		Fee = AllFee;
		delete []buf;
		return true;
	}
	unsigned long elseminutes  = minutes;
	if(pTlb->FeeRates[pTlb->RecCount-1].FeeEndTime < elseminutes)
	{
		elseminutes = elseminutes -  pTlb->FeeRates[pTlb->RecCount-1].FeeEndTime;
		AllFee = AllFee + pTlb->FeeRates[pTlb->RecCount-1].FeeClass1;
		while((pTlb->CycleEndTime - pTlb->CycleStartTime)< elseminutes)
		{
			elseminutes = elseminutes - (pTlb->CycleEndTime - pTlb->CycleStartTime);
			unsigned long CycleStartTimeFee = 0;
			unsigned long CycleEndTimeFee = 0;
			if(!CalculateFee_Rate(pTlb->CycleStartTime,CycleStartTimeFee))
			{
				delete []buf;
				return false;
			}
			if(!CalculateFee_Rate(pTlb->CycleEndTime,CycleEndTimeFee))
			{
				delete []buf;
				return false;
			}
			AllFee = AllFee + CycleEndTimeFee - CycleStartTimeFee;
		}
		unsigned long elseStartTimeFee = 0;
		unsigned long elseEndTimeFee = 0;
		if(!CalculateFee_Rate(pTlb->CycleStartTime,elseStartTimeFee))
		{
			delete []buf;
			return false;
		}
		if(!CalculateFee_Rate(pTlb->CycleStartTime+elseminutes,elseEndTimeFee))
		{
			delete []buf;
			return false;
		}
		AllFee = AllFee + elseEndTimeFee - elseStartTimeFee;
	}
	else
	{
		for(UL i = 0; i < pTlb->RecCount; i++)
		{
			if(elseminutes > pTlb->FeeRates[i].FeeEndTime )
				continue;
			else
			{
				AllFee = AllFee + pTlb->FeeRates[i].FeeClass1;
				break;
			}
		}
	}
	Fee = AllFee;
	delete []buf;
	return true;
}

#define TESTSTRING "1234567"
void CtttDlg::OnBnClickedButton16()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime now = CTime::GetCurrentTime();
	UL nTime = now.GetTime() - 1000;
	UL timespansec = (now.GetTime() > nTime) ? (now.GetTime() - nTime) : 0;
	CTimeSpan ts(-99);
	LONGLONG tt = ts.GetTotalMinutes();

	//UL nTime = 1503986400;
	UL *pFee;
	UL nFee;
	pFee = &nFee;
	int nsize;

	unsigned long nfee;
	nTime = (UL)ts.GetTotalMinutes();
	CalculateFee_Rate(nTime, nfee);

	nsize = sizeof(TESTSTRING);
	CString tpstr = TESTSTRING;
	tpstr += ".dat";
	BOOL bb = (tpstr.Left(sizeof(TESTSTRING) - 1) == TESTSTRING);
	//CTime now = CTime::GetCurrentTime();
	CTimeSpan timespan(7199);
	//CTimeSpan timespan(now.GetTime() - nTime);
	int minute = timespan.GetTotalMinutes();
	bool b = CalculateFee_Rate(timespan.GetTotalMinutes(), (unsigned long &)*pFee);

}

BYTE BlockColor[1024];
void ProcessBlock(CDC *pDC, int width, int height)
{
	static long bcolor[]={0,0xffff0000,0xff00ff00,0xffffff00};
	int BlockGradeStart = 1;
	int x, y, i;
	BYTE c;
	COLORREF bmpcolor;
	int bmpr, bmpg, bmpb;
	for (x = 0; x < width; x++ )
		for (y = 0; y < height; y++ )
		{
			bmpcolor = pDC->GetPixel(x, y);
			bmpcolor &= 0xffffff;

			if ((long)bmpcolor == 0)
				continue;
			bmpr = GetRValue(bmpcolor);
			bmpg = GetGValue(bmpcolor);
			bmpb = GetBValue(bmpcolor);
			if ((bmpb != 0x80) || (bmpr + bmpg * 0x100) < BlockGradeStart)
				continue;
			if ((bmpr + bmpg * 0x100 - BlockGradeStart) >= 1024)
				continue;
			c = BlockColor[(bmpr + bmpg * 0x100 - BlockGradeStart)];
			if (c <= 3)
			{
				pDC->SetPixel(x, y, bcolor[c]);
			}
		}
}


CSocket g_Socket;  
void VerifySock(CSocket* pSock = NULL)
{
	pSock->Close();
	Sleep(1000);
	if (pSock->Create())
	{
		Sleep(1000);
		pSock->Close();
	}
}
UINT ThreadTestSocket(LPVOID)  
{  
	//BOOL bb = g_Socket.Create();  
	//int i = 1;
	//Sleep(10000);
	CSocket s;
	do 
	{
		if (s.Create())
		{
			Sleep(100);
			VerifySock(&s);
		}
		Sleep(100);
	} while (1);
	return 0;  
} 

UINT ThreadTestSocket2(LPVOID)  
{  
	CSocket s;
	do 
	{
		if (s.Create())
		{
			Sleep(100);
			VerifySock(&s);
		}
		Sleep(100);
	} while (1);
	return 0;  
} 
UINT ThreadTestSocket3(LPVOID)  
{  
	CSocket s;
	do 
	{
		if (s.Create())
		{
			Sleep(100);
			VerifySock(&s);
		}
		Sleep(100);
	} while (1);
	return 0;  
} 
UINT ThreadTestSocket4(LPVOID)  
{  
	CSocket s;
	do 
	{
		if (s.Create())
		{
			Sleep(100);
			VerifySock(&s);
		}
		Sleep(100);
	} while (1);
	return 0;  
} 
UINT ThreadTestSocket5(LPVOID)  
{  
	CSocket s;
	do 
	{
		if (s.Create())
		{
			Sleep(100);
			VerifySock(&s);
		}
		Sleep(100);
	} while (1);
	return 0;  
} 

void CtttDlg::OnBnClickedButton17()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxBeginThread(ThreadTestSocket, NULL);
	Sleep(100);
	AfxBeginThread(ThreadTestSocket2, NULL);
	Sleep(100);
	AfxBeginThread(ThreadTestSocket3, NULL);
	Sleep(100);
	AfxBeginThread(ThreadTestSocket4, NULL);
	Sleep(100);
	AfxBeginThread(ThreadTestSocket5, NULL);
	Sleep(100);
	//Sleep(1000);
	//g_Socket.Close();
}

void CtttDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		int iii;
		iii = 1;
		break;
	case 5:
		KillTimer(5);
		TakeSnapshot();
		SetTimer(5, 700, NULL);
		break;
	case 11:
		AfxBeginThread(ThreadTestSocket, NULL);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

UINT TestCStringThread1( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)pParam;
	//CString tpstr;
	//int count = 0;
	for (int count = 0; count < 10000 ; count++)
	{
		//char *pMsg = new char[500];
		g_strTest.Format("111֪ͨ��Ϣ��¼��־�ַ���a long string����@#������&*��������=%d", count);
		//strcpy(pMsg, (LPCTSTR)tpstr);
		ShowTestMessage(pDlg->m_hWnd);
		Sleep(1);
	}
	AfxMessageBox("TestCStringThread1 end");
	return 0;
}
UINT TestCStringThread2( LPVOID pParam )
{
	CtttDlg *pDlg = (CtttDlg *)pParam;
	//CString tpstr;
	//int count = 0;
	for (int count = 0; count < 10000 ; count++)
	{
		//char *pMsg = new char[500];
		g_strTest.Format("222֪ͨ��Ϣ��¼��־�ַ���a long string����@#������&*��������=%d", count);
		//strcpy(pMsg, (LPCTSTR)tpstr);
		ShowTestMessage(pDlg->m_hWnd);
		Sleep(1);
	}
	AfxMessageBox("TestCStringThread2 end");
	return 0;
}

void CtttDlg::OnBnClickedButton18()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxBeginThread(TestCStringThread1, this);
	AfxBeginThread(TestCStringThread2, this);
}


void CtttDlg::OnBnClickedButton19()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime tptime(2017, 2, 31, 23, 60, 0);
	tptime = tptime;
	unsigned long tplong = (unsigned long)tptime.GetTime();
	AfxMessageBox("abc");
}


void CtttDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect     

	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ     
	m_tab1.GetClientRect(&tabRect);     
	tabRect.left += 1;     
	tabRect.right -= 1;     
	tabRect.top += 25;     
	tabRect.bottom -= 1;     

	switch (m_tab1.GetCurSel())     
	{     
		// �����ǩ�ؼ���ǰѡ���ǩΪ��register��������ʾm_regdlg�Ի�������m_gradlg�Ի���     
	case 0:     
		m_dlgTab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);     
		m_dlgTab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);     
		break;     
		// �����ǩ�ؼ���ǰѡ���ǩΪ��graphic����������m_regdlg�Ի�����ʾm_gradlg�Ի���     
	case 1:     
		m_dlgTab1.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);     
		m_dlgTab2.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);     
		break;     
	default:     
		break;     
	}     
}

void ReplaceTemplate(CString strTemplate)
{
	CString strLog;
	int nReplace;
	strTemplate = "abc abc 123joipa jabcedf";
	nReplace = strTemplate.Replace("abc", "cba");
	if (nReplace != 1)
	{
		//strLog.Format();
		//WriteLog():
	}
}

BOOL ExportToFile(CString strTemplateFile, CString strOutputFile)
{
	CFile f;
	CString strFileContent;
	TRY
	{
		if (f.Open(strTemplateFile, CFile::modeRead))
		{
			ULONGLONG nFileLen = f.GetLength();
			f.Read(strFileContent.GetBuffer(nFileLen), nFileLen);
			strFileContent.ReleaseBuffer();
			f.Close();
		}

	}
	CATCH( CFileException, e )
	{
		return FALSE;
	}
	END_CATCH

	TRY
	{
		if (f.Open(strOutputFile, CFile::modeCreate | CFile::modeReadWrite))
		{
			f.Write(strFileContent.GetBuffer(0), strFileContent.GetLength());
			strFileContent.ReleaseBuffer();
			f.Close();
		}

	}
	CATCH( CFileException, e )
	{
		return FALSE;
	}
	END_CATCH
	return TRUE;
}