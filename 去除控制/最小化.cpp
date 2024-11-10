// 最小化.cpp : 实现文件
//

#include "stdafx.h"
#include "去除控制.h"
#include "最小化.h"
#include "afxdialogex.h"


// 最小化 对话框

IMPLEMENT_DYNAMIC(最小化, CDialog)

最小化::最小化(CWnd* pParent /*=NULL*/)
	: CDialog(最小化::IDD, pParent)
{

}

最小化::~最小化()
{
}

void 最小化::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(最小化, CDialog)
END_MESSAGE_MAP()


// 最小化 消息处理程序
