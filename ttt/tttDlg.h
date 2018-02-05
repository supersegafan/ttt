
// tttDlg.h : 头文件
//
#include "messagedefine.h"

#include "VLCPlayer.h"
#include "wattsctrl1.h"

#include "DialogTab1.h"
#include "DialogTab2.h"

#define STRINGMODEMETEO (1)
#define STRINGMODEVEHICLEDETECTOR (2)

#define MAXIMAGEFILELENGTH (2*1024*1024)

#pragma once

// CtttDlg 对话框
class CtttDlg : public CDialogEx
{
// 构造
public:
	CVLCPlayer m_VLCPlayer[2];
	BOOL m_bTakingSnapshot;
	MessageHead m_MessageHead;
	BOOL TakeSnapshot();
	BOOL ProcessImage(CString imagesrc, CString imagedest, CString imagetype = "", CString imageoptions = "", BOOL bDebug = FALSE);
	int m_nTotalFlow;
	int m_nTotalFlow1;
	int m_nTotalFlow2;
	int m_nTotalFlow3;
	int m_nIndex;
	int VehicleDetectorResponseProcess(CString strVDRaw);
	int GetValidString(CString strInput, CString& strOutput, int nSearchBeginNum = 0, int nStringMinLen = 0, int nStringMode = STRINGMODEMETEO);
	CtttDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TTT_DIALOG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
		afx_msg LRESULT OnThreadMessage(WPARAM wParam, LPARAM lParam);


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	BOOL VDMsgGenerate(int nDeviceIndex, VehicleDetectorMsg* pVDMsg);
	void vdtest(int nDeviceIndex);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	CWattsctrl1 m_Watts;
	CTabCtrl m_tab1;
	CDialogTab1 m_dlgTab1;
	CDialogTab1 m_dlgTab2;
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
