// SET.cpp : 实现文件
//

#include "stdafx.h"
#include "去除控制.h"
#include "SET.h"
#include "afxdialogex.h"
extern int killproceway;
extern  int setdata[20];
// SET 对话框

IMPLEMENT_DYNAMIC(SET, CDialogEx)

SET::SET(CWnd* pParent /*=NULL*/)
	: CDialogEx(SET::IDD, pParent)
{

	
}

SET::~SET()
{
	
}

void SET::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SET, CDialogEx)

	ON_BN_CLICKED(IDC_RADIO2, &SET::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &SET::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_CHECK3, &SET::OnBnClickedCheck3)
	
	ON_BN_CLICKED(IDC_CHECK4, &SET::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &SET::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &SET::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &SET::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &SET::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &SET::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK1, &SET::OnBnClickedCheck1)
END_MESSAGE_MAP()


// SET 消息处理程序




void SET::OnBnClickedRadio2()
{
	killproceway=2;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedRadio1()
{
	killproceway=1;
	// TODO: 在此添加控件通知处理程序代码
}



void SET::OnBnClickedCheck3()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	if(state==1)
	 setdata[1]=1;
	else
	 setdata[1]=0;
	  
	// TODO: 在此添加控件通知处理程序代码
}



void SET::OnBnClickedCheck4()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck();
	if(state==1)
		setdata[2]=1;
	else
		setdata[2]=0;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedCheck5()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck();
	if(state==1)
		setdata[3]=1;
	else
		setdata[3]=0;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedCheck6()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck();
	if(state==1)
		setdata[4]=1;
	else
		setdata[4]=0;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedCheck7()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck();
	if(state==1)
		setdata[5]=1;
	else
		setdata[5]=0;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedCheck8()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK8))->GetCheck();
	if(state==1)
		setdata[6]=1;
	else
		setdata[6]=0;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedCheck9()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK9))->GetCheck();
	if(state==1)
		setdata[7]=1;
	else
		setdata[7]=0;
	// TODO: 在此添加控件通知处理程序代码
}


void SET::OnBnClickedCheck1()
{
	int state =((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	if(state==1)
		setdata[13]=5;
	else
		setdata[13]=0;
	// TODO: 在此添加控件通知处理程序代码
}


BOOL SET::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(setdata[1]==1) ((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(BST_CHECKED); 
	if(setdata[2]==1) ((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(BST_CHECKED); 
	if(setdata[3]==1) ((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(BST_CHECKED); 
	if(setdata[4]==1) ((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(BST_CHECKED); 
	if(setdata[5]==1) ((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(BST_CHECKED); 
	if(setdata[6]==1) ((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(BST_CHECKED); 
	if(setdata[7]==1) ((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(BST_CHECKED); 
	if(setdata[13]==5) ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
