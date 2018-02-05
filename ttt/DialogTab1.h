#pragma once


// CDialogTab1 对话框

class CDialogTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab1)

public:
	CDialogTab1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogTab1();

// 对话框数据
	enum { IDD = IDD_DIALOG_TAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
