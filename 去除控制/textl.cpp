// textl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ȥ������.h"
#include "textl.h"
#include "afxdialogex.h"


// textl �Ի���

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


// textl ��Ϣ�������


void textl::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void textl::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


BOOL textl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT1,L"���������ѧϰ����ΪĿ�ģ����������κηǷ���;.����������й��ܾ�ֻ�������ڿ��ø�������ֹ���ڸɻ���.������������ʹ�ñ������ɵ�һ�к���������޹أ���������������ɾ�������.�����������ѣ�֧�����߲���ζ��ӵ�и���Ȩ��\n2020 XUPEI	");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
