#pragma once


// CDialogTab1 �Ի���

class CDialogTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab1)

public:
	CDialogTab1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogTab1();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
