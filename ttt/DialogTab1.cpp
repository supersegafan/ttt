// DialogTab1.cpp : 实现文件
//

#include "stdafx.h"
#include "ttt.h"
#include "DialogTab1.h"
#include "afxdialogex.h"


// CDialogTab1 对话框

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


// CDialogTab1 消息处理程序


void CDialogTab1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
