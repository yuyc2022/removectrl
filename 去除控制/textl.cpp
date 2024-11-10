// textl.cpp : 实现文件
//

#include "stdafx.h"
#include "去除控制.h"
#include "textl.h"
#include "afxdialogex.h"


// textl 对话框

IMPLEMENT_DYNAMIC(textl, CDialogEx)

textl::textl(CWnd* pParent /*=NULL*/)
	: CDialogEx(textl::IDD, pParent)
{

}

textl::~textl()
{
}

void textl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(textl, CDialogEx)
	ON_BN_CLICKED(IDOK, &textl::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &textl::OnBnClickedCancel)
END_MESSAGE_MAP()


// textl 消息处理程序


void textl::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void textl::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


BOOL textl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT1,L"本软件仅以学习交流为目的，请勿用于任何非法用途.本软件的所有功能均只可以用于课堂辅助，禁止用于干坏事.事先声明，因使用本软件造成的一切后果与作者无关，如做不到请自行删除本软件.本软件永久免费，支持作者不意味着拥有更多权力\n2020 XUPEI	");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
