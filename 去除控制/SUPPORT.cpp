// SUPPORT.cpp : 实现文件
//

#include "stdafx.h"
#include "去除控制.h"
#include "SUPPORT.h"
#include "afxdialogex.h"


// SUPPORT 对话框

IMPLEMENT_DYNAMIC(SUPPORT, CDialog)

SUPPORT::SUPPORT(CWnd* pParent /*=NULL*/)
	: CDialog(SUPPORT::IDD, pParent)
{

}

SUPPORT::~SUPPORT()
{
}

void SUPPORT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SUPPORT, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &SUPPORT::OnBnClickedButton1)
END_MESSAGE_MAP()


// SUPPORT 消息处理程序


void SUPPORT::OnBnClickedButton1()
{
	ShellExecute(NULL, L"open",L"explorer.exe",L" https://www.2345.com/?kremovectrl"  ,NULL ,SW_HIDE);
	CDialog::EndDialog(0); 
	// TODO: 在此添加控件通知处理程序代码
}


BOOL SUPPORT::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,L"https://www.2345.com/?kremovectrl");
	// TODO:  在此添加额外的初始化
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
