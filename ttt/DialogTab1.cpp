// DialogTab1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ttt.h"
#include "DialogTab1.h"
#include "afxdialogex.h"


// CDialogTab1 �Ի���

IMPLEMENT_DYNAMIC(CDialogTab1, CDialogEx)

CDialogTab1::CDialogTab1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogTab1::IDD, pParent)
{

}

CDialogTab1::~CDialogTab1()
{
}

void CDialogTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab1, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDialogTab1::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CDialogTab1 ��Ϣ�������


void CDialogTab1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
