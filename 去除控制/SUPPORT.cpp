// SUPPORT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ȥ������.h"
#include "SUPPORT.h"
#include "afxdialogex.h"


// SUPPORT �Ի���

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


// SUPPORT ��Ϣ�������


void SUPPORT::OnBnClickedButton1()
{
	ShellExecute(NULL, L"open",L"explorer.exe",L" https://www.2345.com/?kremovectrl"  ,NULL ,SW_HIDE);
	CDialog::EndDialog(0); 
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL SUPPORT::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,L"https://www.2345.com/?kremovectrl");
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
