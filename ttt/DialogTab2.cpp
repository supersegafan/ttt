// DialogTab2.cpp : 实现文件
//

#include "stdafx.h"
#include "ttt.h"
#include "DialogTab2.h"
#include "afxdialogex.h"


// CDialogTab2 对话框

IMPLEMENT_DYNAMIC(CDialogTab2, CDialogEx)

CDialogTab2::CDialogTab2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogTab2::IDD, pParent)
{

}

CDialogTab2::~CDialogTab2()
{
}

void CDialogTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTab2, CDialogEx)
END_MESSAGE_MAP()


// CDialogTab2 消息处理程序
