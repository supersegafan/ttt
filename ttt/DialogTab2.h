#pragma once


// CDialogTab2 �Ի���

class CDialogTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTab2)

public:
	CDialogTab2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogTab2();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
