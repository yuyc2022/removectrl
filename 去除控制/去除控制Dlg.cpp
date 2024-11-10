
// 去除控制Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "去除控制.h"
#include "去除控制Dlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <tlhelp32.h>
#include <cstring>
#include <locale.h>
#include <cstdio>
#include <atlbase.h>
#include <WinSock2.h>

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>

#include <stdio.h>
#include <io.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;


#define WM_SHOWTASK (WM_USER +1)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int killproceway=2;
HINSTANCE ntdlx;
HINSTANCE knelx;
int heihei=1;
char pro[10][5][20];
int propid[15][20];
int setdata[20];
int pron[10];
int n=0,jfn=0,jfnum=0,nage=0;
char xsjf[20][20];
CWnd* p;
HWND h;
HWND EditHwnd ;
HWND EditHwnd2;
char* jylj/*[100]*/;

#define ArraySize(ptr)    (sizeof(ptr) / sizeof(ptr[0]))

char adress[20];

/*
int GetNumVisibleLines(CRichEditCtrl* pCtrl)
{
	CRect rect;
	long nFirstChar, nLastChar;
	long nFirstLine, nLastLine;

	// Get client rect of rich edit control
	pCtrl->GetClientRect(rect);

	// Get character index close to upper left corner
	nFirstChar = pCtrl->CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	nLastChar = pCtrl->CharFromPos(CPoint(rect.right, rect.bottom));
	if (nLastChar < 0)
	{
		nLastChar = pCtrl->GetTextLength();
	}

	// Convert to lines
	nFirstLine = pCtrl->LineFromChar(nFirstChar);
	nLastLine  = pCtrl->LineFromChar(nLastChar);

	return (nLastLine - nFirstLine);
}
int AppendToLogAndScroll(const CString& csMsg, COLORREF color, int iFontSize)
{
	C去除控制Dlg lpp;

	long nVisible = 0;
	long nInsertionPoint = 0;
	CHARFORMAT cf;
	lpp.editor.GetSelectionCharFormat(cf);
	// Initialize character format structure
	cf.cbSize = sizeof(CHARFORMAT);
	static int iHeight = 100;
	cf.dwMask|=CFM_BOLD;
	cf.dwEffects |=CFE_BOLD;//设置粗体，取消用cf.dwEffects&=~CFE_BOLD;
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	cf.dwMask |= CFM_COLOR;
	cf.crTextColor = color;
	cf.dwMask|=CFM_SIZE;
	cf.yHeight = iHeight;//设置高度
	iHeight += 50;
	cf.dwMask |=CFM_FACE;
	_tcscpy(cf.szFaceName ,_T("微软雅黑"));//设置字体
	// Set insertion point to end of text
	nInsertionPoint = lpp.GetWindowTextLength();
	lpp.editor.SetSel(nInsertionPoint, -1);

	// Set the character format
	lpp.editor.SetSelectionCharFormat(cf);

	// Replace selection. Because we have nothing
	// selected, this will simply insert
	// the string at the current caret position.
	lpp.editor.ReplaceSel(csMsg);

	// Get number of currently visible lines or maximum number of visible lines
	// (We must call GetNumVisibleLines() before the first call to LineScroll()!)
	nVisible   = GetNumVisibleLines(&lpp.editor);

	// Now this is the fix of CRichEditCtrl's abnormal behaviour when used
	// in an application not based on dialogs. Checking the focus prevents
	// us from scrolling when the CRichEditCtrl does so automatically,
	// even though ES_AUTOxSCROLL style is NOT set.
	if (&lpp.editor != lpp.editor.GetFocus())
	{
		lpp.editor.LineScroll(INT_MAX);
		lpp.editor.LineScroll(1 - nVisible);
	}

	return 0;
}

*/


// C去除控制Dlg 消息处理程序



void writeday(char* dat)
{
	
	if(setdata[7]==0)return;
	FILE* fp = NULL; // 文件指针
	errno_t eResult;
	eResult = fopen_s(&fp,"ktr.txt","a+");
	if (eResult != 0)
		return;
	fputs("\n",fp);
	time_t t = time(0);
	char ch[64];
	strftime(ch, sizeof(ch), "%Y-%m-%d %H-%M-%S", localtime(&t));
	fputs(ch,fp);
	fputs(" ",fp);
	fputs(dat,fp);
	fclose(fp);
	return;
}
int udpsend(char *dat,int bagdx)
{
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
		{
			return -1;
		}

	if ( LOBYTE( wsaData.wVersion ) != 2 ||
	        HIBYTE( wsaData.wVersion ) != 2 )
		{
			WSACleanup( );
			return -1;
		}

	//创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == sockClient)
		//printf("socket() called failed! The error code is: %d\n", WSAGetLastError());
		return -1;


	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = inet_addr(adress);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(4705);

	//发送数据
	err = sendto(sockClient, dat, bagdx, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (SOCKET_ERROR == err)
		return -1;

//关闭套接字
	closesocket(sockClient);

	//终止套接字库的使用
	WSACleanup();

	return 0;
}
bool AdjustProcessPrivileges(HANDLE hProcess, LPCTSTR PrivilegeName)
{
	HANDLE hToken;
	bool bRet = false;
	TOKEN_PRIVILEGES tkp = { 0 };


	if (!OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			goto Exit;
		}
	LookupPrivilegeValue(NULL, PrivilegeName, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), (PTOKEN_PRIVILEGES)NULL, 0);
	bRet = true;
Exit:
	return bRet;
}


////////////////////////////////////内核//////////////////////////////////////////////////////////////////
int fpid(LPCSTR ProcessName)
{

	int i=0;
	i=0;
	PROCESSENTRY32 pe32;
	int wPid=0;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
		return false;
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while(bMore)
		{
			USES_CONVERSION;
			char* test1 = W2A(pe32.szExeFile);//转化成默认
			if(stricmp(ProcessName,test1) == 0)
				{
					wPid=pe32.th32ProcessID;
					return wPid;
				}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
	return 0;
}
typedef int (WINAPI *MYAPI1)(HANDLE,int);
typedef HANDLE (WINAPI *MYAPI2)(int,bool,int);
MYAPI1 MZwUnmapViewOfSection = NULL;
MYAPI2 Mopenprocess = NULL;
void skpx(ULONG PID)
{
	
	//C去除控制Dlg ll1;
	//ll1.textadd("进程ID获取成功");
	//if(heihei==0) return;
	writeday("skpx the bad process");
	killproceway=2;
	if(killproceway==1)
		{
			int i;
			ULONG base;
			HANDLE hProc=NULL;
			hProc=Mopenprocess(PROCESS_ALL_ACCESS,FALSE,PID);
			if(hProc!=NULL)
				for(i=0x1; i<=0x80; i++)
					{
						base=i*0x1000000;
						MZwUnmapViewOfSection(hProc,base);
					}
			CloseHandle(hProc);
		}
	if(killproceway==2)
		{
			HANDLE hThreadSnap = NULL;
			THREADENTRY32 te32;
			BOOL bThreadFind = FALSE;
			hThreadSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,NULL);
			if(hThreadSnap)
				{
					te32.dwSize = sizeof(THREADENTRY32);
					bThreadFind = Thread32First(hThreadSnap,&te32);
					while(bThreadFind)
						{
							if(te32.th32OwnerProcessID == PID)
								{
									HANDLE hThread = NULL;
									hThread = OpenThread(THREAD_ALL_ACCESS,FALSE,te32.th32ThreadID);
									if(hThread)
										{
											TerminateThread(hThread,0);
											CloseHandle(hThread);
										}
								}
							te32.dwSize = sizeof(THREADENTRY32);
							bThreadFind = Thread32Next(hThreadSnap,&te32);
						}
					CloseHandle(hThreadSnap);
				}

		}
	//ll1.textadd("结束进程完成");
}
BOOL FP(char *pProcess)
{
	//if(heihei==0) return false;
	//WCHAR* pProcess=0;

	int i=0;
	i=0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return false;
		}
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while(bMore)
		{
			USES_CONVERSION;
			char* test1 = W2A(pe32.szExeFile);//转化成默认
			if(stricmp(pProcess,test1) == 0)
				{

					return 1;
				}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}

	return 0;
}
BOOL FPfaster(int a,int b,char *pProcess)
{
	int i=0;
	i=0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
		return false;
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while(bMore)
		{
			USES_CONVERSION;
			char* test1 = W2A(pe32.szExeFile);//转化成默认
			if(stricmp(pProcess,test1) == 0)
				{
					propid[a][b]=pe32.th32ProcessID;
					return true;
				}
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
	propid[a][b]=0;
	return false;
}
PIMAGE_IMPORT_BY_NAME  pImportByName = NULL;
PIMAGE_THUNK_DATA    pOriginalThunk = NULL;
PIMAGE_THUNK_DATA    pFirstThunk = NULL;

//IAT HOOK的核心函数、
int IatHook(const char* DllName, const char* FunName,DWORD RealAddr);


//自己的OpenProcess函数、
HANDLE   WINAPI    MyOpenProcess    (DWORD dwDesiredAccess,  BOOL bInheritHandle,   DWORD dwProcessId);

DWORD MyOpenProcessAddr = (DWORD)MyOpenProcess;


typedef HANDLE (WINAPI * RealOpenProcess)(DWORD,BOOL,DWORD);

RealOpenProcess pRealOpenProcess = (RealOpenProcess)OpenProcess;

HANDLE WINAPI MyOpenProcess(DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwProcessId)
{
	if(fpid("去除控制.exe") == dwProcessId)  return 0;
	return ( pRealOpenProcess(dwDesiredAccess,bInheritHandle,dwProcessId) );
}

// ****************************************************** IAT  HOOK  函数的实现部分****************************************************/

int IatHook(const char* DllName, const char* FunName,DWORD RealAddr)

{

	/**************************   找相同的DLL   ****************************/
	HANDLE pBegin = GetModuleHandle(NULL);
	PBYTE  pBegin2 = (PBYTE)pBegin;
	PIMAGE_DOS_HEADER DOS = PIMAGE_DOS_HEADER(pBegin2);
	PIMAGE_NT_HEADERS NT = PIMAGE_NT_HEADERS(pBegin2+DOS->e_lfanew);
	PIMAGE_OPTIONAL_HEADER OPTION = &(NT->OptionalHeader);
	PIMAGE_IMPORT_DESCRIPTOR IMPORT = PIMAGE_IMPORT_DESCRIPTOR(OPTION->DataDirectory[1].VirtualAddress + pBegin2);

	while (IMPORT->Name)
		{
			char* OurDllName = (char*)(IMPORT->Name + pBegin2);
			if (0 == strcmpi(DllName , OurDllName))
				{
					break;
				}
			IMPORT++;
		}

	/*************************   找相同的API函数    ****************************/
	PIMAGE_IMPORT_BY_NAME  pImportByName = NULL;
	PIMAGE_THUNK_DATA   pOriginalThunk = NULL;
	PIMAGE_THUNK_DATA   pFirstThunk = NULL;
	pOriginalThunk = (PIMAGE_THUNK_DATA)(IMPORT->OriginalFirstThunk + pBegin2);
	pFirstThunk = (PIMAGE_THUNK_DATA)(IMPORT->FirstThunk + pBegin2);
	while (pOriginalThunk->u1.Function) //记住是Function
		{
			DWORD u1 = pOriginalThunk->u1.Ordinal;  //记住是Ordinal
			if ((u1 & IMAGE_ORDINAL_FLAG) != IMAGE_ORDINAL_FLAG) //说明MSB不是1  不是以序号导入
				{
					pImportByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pOriginalThunk->u1.AddressOfData + pBegin2);
					char* OurFunName = (char*)(pImportByName->Name); //下边的计算也可以
					//char* OurFunName2 = (char*)((DWORD)pOriginalThunk->u1.AddressOfData + pBegin2 + 2);
					if (0 == strcmpi(FunName,OurFunName))
						{
							//获取以pFirstThunk开始的内存的信息并将其保存到MEMORY_BASIC_INFORMATION结构中
							MEMORY_BASIC_INFORMATION   mbi_thunk;
							VirtualQuery (pFirstThunk, &mbi_thunk, sizeof(MEMORY_BASIC_INFORMATION));
							//VirtualProtect(mbi_thunk.BaseAddress,mbi_thunk.RegionSize, PAGE_READWRITE, &mbi_thunk.Protect);
							//修改以pFirstThunk开始的内存的的保护属性为PAGE_READWRITE并将原保护属性保存到&dwOLD中
							DWORD dwOLD;
							VirtualProtect(pFirstThunk,sizeof(DWORD),PAGE_READWRITE,&dwOLD);
							//更改真正OpenProcess的地址为自己写的MyOpenProcess函数的地址、、
							pFirstThunk->u1.Function = (DWORD)RealAddr;      //关键地方
							//恢复之前更改的内存的保护属性为人家自己的、、
							VirtualProtect(pFirstThunk,sizeof(DWORD),dwOLD,0);
							break;
						}
				}
			pOriginalThunk++;
			pFirstThunk++;
		}
	return 0;
}
int getFiles(string path,int gn)
{
	int num=0;
	intptr_t   hFile = 0;//文件句柄，过会儿用来查找
	struct _finddata_t fileinfo;//文件信息
	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
				{
					int lenm=strlen(fileinfo.name)-1;
					if(fileinfo.name[lenm]=='e'&&fileinfo.name[lenm-1]=='x'&&fileinfo.name[lenm-2]=='e')
						{
							num++;
							if(gn==2)
								cout<<fileinfo.name<<endl;
						}
				}
			while (_findnext(hFile, &fileinfo) == 0);   //能寻找到其他文件
			_findclose(hFile);  //结束查找，关闭句柄
		}
	return num;
}
int trucrc32=0;
bool xread()
{
	freopen("jfzs.dat","w",stdout);
	cout<<getFiles("c:/jfgl",0)<<endl;
	getFiles("c:/jfgl",2);
	fclose(stdout);

	freopen("ktr.dat","r",stdin);
	cin>>n;
	for(int i=1; i<=n; i++)
		{
			cin>>pron[i];
			for(int j=1; j<=pron[i]; j++)
				cin>>pro[i][j];
		}
	fclose(stdin);

	freopen("jfzs.dat","r",stdin);
	cin>>jfn;
	for(int i=1; i<=jfn; i++)
		cin>>xsjf[i];

	fclose(stdin);
	remove("jfzs.dat");
	return 0;
}
bool ope=0;


void check()
{
	for(int i=1; i<=jfn; i++)
		if(FPfaster(15,i,xsjf[i])==1)
			ope=1;
	nage=0;
	for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=pron[i]; j++)
				{
					if(FPfaster(i,j,pro[i][j])==1)
						{
							nage=i;
						}
				}

		}
	if(nage!=0) writeday("find dangerous process");
	if(nage==0) writeday("process safety");
	if(nage==0) SetWindowTextA(EditHwnd,"未运行");
	if(nage==1) SetWindowTextA(EditHwnd,"lanstar");
	if(nage==2)
		{
			SetWindowTextA(EditHwnd,"极域");
		}
	if(nage==3) SetWindowTextA(EditHwnd,"红蜘蛛");
	if(nage==4) SetWindowTextA(EditHwnd,"传奇");
	if(nage==5) SetWindowTextA(EditHwnd,"海创");
	if(nage>0) SetWindowTextA(EditHwnd2,"控制中");
	else SetWindowTextA(EditHwnd2,"未控制");

}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
	public:
		CAboutDlg();

// 对话框数据
		enum { IDD = IDD_ABOUTBOX };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
	protected:
		DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnQueryEndSession();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_QUERYENDSESSION()
END_MESSAGE_MAP()


// C去除控制Dlg 对话框




C去除控制Dlg::C去除控制Dlg(CWnd* pParent /*=NULL*/)
	:CDialogEx(C去除控制Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C去除控制Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, jiaoshi);
//	DDX_Control(pDX, IDC_RICHEDIT21, editor);
}

BEGIN_MESSAGE_MAP(C去除控制Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_BN_CLICKED(IDC_BUTTON3, &C去除控制Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &C去除控制Dlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON4, &C去除控制Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &C去除控制Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON11, &C去除控制Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &C去除控制Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON8, &C去除控制Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C去除控制Dlg::OnBnClickedButton9)

	ON_BN_CLICKED(IDC_BUTTON1, &C去除控制Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON10, &C去除控制Dlg::OnBnClickedButton10)

//	ON_EN_CHANGE(IDC_EDIT7, &C去除控制Dlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON15, &C去除控制Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &C去除控制Dlg::OnBnClickedButton16)
	
	ON_BN_CLICKED(IDC_BUTTON21, &C去除控制Dlg::OnBnClickedButton21)
	ON_WM_HOTKEY()
//	ON_EN_CHANGE(IDC_RICHEDIT21, &C去除控制Dlg::OnEnChangeRichedit21)
	ON_BN_CLICKED(IDC_ONEKILL, &C去除控制Dlg::OnBnClickedOnekill)
//	ON_WM_QUERYENDSESSION()
ON_BN_CLICKED(IDC_TOOL, &C去除控制Dlg::OnBnClickedTool)
END_MESSAGE_MAP()

void fuck()//杀掉
{
	if(nage!=0)
		for(int i=1; i<=pron[nage]; i++)
			skpx(propid[nage][i]);
	if(ope==1)
		for(int i=1; i<=jfn; i++)
			{
				if(propid[15][i]!=0)
					skpx(propid[15][i]);
				ope=0;
			}
}
void TopWindow(HWND &hWnd)
{
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
POINT logol;
char *randstr(const int len)
{
	char str[10];
	srand(time(NULL));
	int i;
	for (i = 0; i < len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[++i] = '\0';
	return str;
}
DWORD WINAPI keepcheck(LPVOID p)
{
	for(int i=1;; i++)
		{
			if(setdata[5]==1)
				TopWindow(h);
			check();
			if(i%2==0&&setdata[2]==1)
				{
					GetCursorPos(&logol);
					if(logol.x==0&&logol.y==0) fuck();
					SetWindowTextA(h,randstr(8));
				}
			Sleep(1800);
			//writeday("check all the process");
		}
	return 0;

}
#include "SUPPORT.h"
void donate()
{
	__asm 
	{
		_emit 0xEB
			_emit 0x10
			_emit 0x56
			_emit 0x4D
			_emit 0x50
			_emit 0x72
			_emit 0x6F
			_emit 0x74
			_emit 0x65
			_emit 0x63
			_emit 0x74
			_emit 0x20
			_emit 0x62
			_emit 0x65
			_emit 0x67
			_emit 0x69
			_emit 0x6E
			_emit 0x00
	}
	
	SUPPORT temp1;
	temp1.DoModal();
	__asm
	{
		_emit 0xEB
			_emit 0x0E
			_emit 0x56
			_emit 0x4D
			_emit 0x50
			_emit 0x72
			_emit 0x6F
			_emit 0x74
			_emit 0x65
			_emit 0x63
			_emit 0x74
			_emit 0x20
			_emit 0x65
			_emit 0x6E
			_emit 0x64
			_emit 0x00
	}
}
DWORD WINAPI nets(LPVOID p)
{
	Sleep(3000);
	donate();
	Sleep(15*60*1000);
	donate();
	return 0;
}
void setp()
{

	p = AfxGetMainWnd();
	h = p->m_hWnd;
	EditHwnd =  GetDlgItem(h,IDC_EDIT1);
	EditHwnd2 = GetDlgItem(h,IDC_EDIT2);
	HWND asas = GetDlgItem(h,IDC_EDIT6);
	SetWindowTextA(asas,"192.168.1.1");
	SetWindowTextA(GetDlgItem(h,IDC_EDIT8),"ping www.baidu.com");

}

void CheckProcess()
{
	if(setdata[13]!=5) return ;


	char szFileFullPath[MAX_PATH],szProcessName[MAX_PATH];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH);//获取文件路径
	int length=::strlen(szFileFullPath);
	for (int i=length-1; i>=0; i--) //从路径后面开始找\，即倒着找右斜杠
		{
			if (szFileFullPath[i]=='\\')//找到第一个\，就可以马上获取进程名称了
				{
					i++;
					for (int j=0; i<=length; j++) //结束符\0不能少,即i=length
						{
							szProcessName[j]=szFileFullPath[i++];
						}
					break;
				}
		}
	char newfilename[20];
	strcpy(newfilename,randstr(8));
	strcat(newfilename,".exe");
	//MessageBoxA(0,0,newfilename,MB_OK);
	bool doc=0;
	CopyFileA(szProcessName,newfilename,doc);
	FILE* fp = NULL; // 文件指针
	errno_t eResult;
	eResult = fopen_s(&fp,newfilename,"a+");
	fputs("\n",fp);
	time_t t = time(0);
	char ch[64];
	strftime(ch, sizeof(ch), "%Y-%m-%d %H-%M-%S", localtime(&t));
	fputs(ch,fp);
	fputs(" ",fp);
	fputs(randstr(18),fp);
	fclose(fp);
	return;
}
/////////////////////////////////////////功能区///////////////////////////////////////////////////////////////
bool havedll,gf=0;
#include <WinInet.h>
#include "textl.h"
BOOL C去除控制Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
		{
			BOOL bNameValid;
			CString strAboutMenu;
			bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
			ASSERT(bNameValid);
			if (!strAboutMenu.IsEmpty())
				{
					pSysMenu->AppendMenu(MF_SEPARATOR);
					pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
				}
		}

	HKEY hKEY;
	if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\System", 0, KEY_SET_VALUE, &hKEY))
	{
		RegDeleteValue(hKEY, L"DisableCMD");
	}
	RegCloseKey(hKEY);

	textl llp1;
	llp1.DoModal();
	RegisterHotKey(this->GetSafeHwnd(), 1001, MOD_ALT, 'K');
	RegisterHotKey(this->GetSafeHwnd(), 1002, MOD_ALT, 'k');
	RegisterHotKey(this->GetSafeHwnd(), 1003, MOD_ALT, 'h');
	RegisterHotKey(this->GetSafeHwnd(), 1004, MOD_ALT, 'H');
	AdjustProcessPrivileges(GetCurrentProcess(), SE_DEBUG_NAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	//USES_CONVERSION;
	//editor.SetBackgroundColor(FALSE,0);//设置背景为黑色
	//AppendToLogAndScroll(L"Made By Xupei 2020",RGB(0,255,0),20);
	
	//C去除控制Dlg::textadd("官网removectrl.mysxl.cn");
	int result=0;
	HINSTANCE hInst = LoadLibrary(L"xplu.DLL");
	HINSTANCE ntdlx = LoadLibrary(L"C://windows//system32//ntdll.DLL");
	HINSTANCE knelx = LoadLibrary(L"C://windows//system32//kernel32.dll");

	MZwUnmapViewOfSection=(MYAPI1)GetProcAddress(ntdlx,"ZwUnmapViewOfSection");
	Mopenprocess=(MYAPI2)GetProcAddress(knelx,"OpenProcess");

	if(hInst)
		{
			havedll=1;
			typedef int (WINAPI *MYFUNC)(int);
			MYFUNC fun = NULL;
			fun=(MYFUNC)GetProcAddress(hInst,"inito");
			if(fun) result=fun(6);
			//FreeLibrary(hInst);
		}

	xread();
	//C去除控制Dlg::textadd("配置文件读取成功");
	/*
	init_crc32_tab();
	unsigned int crcvalue;
	calc_img_crc(L"去除控制.exe", &crcvalue);
	if(crcvalue!=trucrc32||IsDebuggerPresent())
		heihei=0;
	*/
	setdata[1]=1;
	setdata[2]=1;
	setdata[5]=1;
	setdata[4]=1;
	setp();

	SetWindowTextA(h,randstr(8));
	HANDLE a = CreateThread(NULL,0,keepcheck,NULL,0,NULL);
	CreateThread(NULL,0,nets,NULL,0,NULL);
	if(havedll==1)
		{
			if(result==20040312) gf=1;
			else gf=0;
			if(gf==0) MessageBoxA(h,"加载第三方动态运行库","注意",MB_OK);
			if(setdata[4]==0&&gf==0)
				{
					hInst=NULL;
					havedll=0;
				}
		}
	if(hInst)
		{
			writeday("run the plu func began");
			typedef int (WINAPI *MYFUNC)(int);
			MYFUNC fun = NULL;
			fun=(MYFUNC)GetProcAddress(hInst,"began");
			if(fun) result=fun(nage);
			FreeLibrary(hInst);
		}

	IatHook("Kernel32.dll","OpenProcess",MyOpenProcessAddr);
	writeday("init successful");


	if(ope==1&&setdata[6]==1)
		for(int i=1; i<=jfn; i++)
			{
				if(propid[15][i]!=0)
					skpx(propid[15][i]);
				ope=0;
			}

	// TODO: 在此添加额外的初始化代码
	//	C去除控制Dlg::textadd("初始化完成");
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void C去除控制Dlg::ToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	USES_CONVERSION;
	wcscpy(nid.szTip,A2W("去除控制")); //信息提示条
	Shell_NotifyIcon(NIM_ADD,&nid); //在托盘区添加图标
	ShowWindow(SW_HIDE); //隐藏主窗口
}
void C去除控制Dlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy(nid.szTip,L"去除控制"); //信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_DELETE,&nid); //在托盘区删除图标
}
LRESULT C去除控制Dlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam!=IDR_MAINFRAME)
		return 1;
	switch(lParam)
		{
			case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
			{
				LPPOINT lpoint=new tagPOINT;
				::GetCursorPos(lpoint);//得到鼠标位置
				CMenu menu;
				menu.CreatePopupMenu();//声明一个弹出式菜单
				//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口将程序结束。
				menu.AppendMenu(MF_STRING,WM_DESTROY,L"关闭"); //确定弹出式菜单的位置
				menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); //资源回收
				HMENU hmenu=menu.Detach();
				menu.DestroyMenu();
				delete lpoint;
			}
			break;
			case WM_LBUTTONDBLCLK://双击左键的处理
			{
				this->ShowWindow(SW_SHOW);//显示主窗口
				DeleteTray();
			}
			break;
			default:
				break;
		}
	return 0;
}
void C去除控制Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
			CAboutDlg dlgAbout;
			dlgAbout.DoModal();
		}
	else if(nID==SC_MINIMIZE)
		{
			ToTray();
		}
	else if(nID==SC_CLOSE)
		{
					CheckProcess();
					writeday("service stop");
					UnregisterHotKey(this->GetSafeHwnd(), 1001);
					UnregisterHotKey(this->GetSafeHwnd(), 1002);
					UnregisterHotKey(this->GetSafeHwnd(), 1003);
					UnregisterHotKey(this->GetSafeHwnd(), 1004);
					CDialogEx::OnSysCommand(nID, lParam);
		}
	else
		{
			UnregisterHotKey(this->GetSafeHwnd(), 1001);
			UnregisterHotKey(this->GetSafeHwnd(), 1002);
			UnregisterHotKey(this->GetSafeHwnd(), 1003);
			UnregisterHotKey(this->GetSafeHwnd(), 1004);
			CDialogEx::OnSysCommand(nID, lParam);
		}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C去除控制Dlg::OnPaint()
{
	if (IsIconic())
		{
			CPaintDC dc(this); // 用于绘制的设备上下文

			SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
			// 使图标在工作区矩形中居中
			int cxIcon = GetSystemMetrics(SM_CXICON);
			int cyIcon = GetSystemMetrics(SM_CYICON);
			CRect rect;
			GetClientRect(&rect);
			int x = (rect.Width() - cxIcon + 1) / 2;
			int y = (rect.Height() - cyIcon + 1) / 2;

			// 绘制图标
			dc.DrawIcon(x, y, m_hIcon);
		}
	else
		{
			CDialogEx::OnPaint();
		}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C去除控制Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C去除控制Dlg::OnBnClickedButton3()//杀掉
{
	int result=0;
	if(nage==0)
		{
			MessageBoxA(h,"被控端不在运行哦，不用杀掉","去除控制",MB_OK);
			writeday("kill no success");
			return;
		}

	if(havedll==1)
		{

			HINSTANCE hInst = LoadLibrary(L"xplu.DLL");
			if(hInst)
				{
					writeday("run the plu func skill");
					typedef int (WINAPI *MYFUNC)(int);
					MYFUNC fun = NULL;
					fun=(MYFUNC)GetProcAddress(hInst,"skill");
					if(fun) result=fun(nage);
					FreeLibrary(hInst);
				}
		}
	if(result==21||havedll==0)
		{
			for(int i=1; i<=pron[nage]; i++)
				if(propid[nage][i]!=0)
					skpx(propid[nage][i]);
		}
	writeday("kill  successful");
	// TODO: 在此添加控件通知处理程序代码
}


void C去除控制Dlg::OnBnClickedButton2()//恢复
{
	FILE *yeres=fopen("start.lnk","r");
	fclose(stdin);
	if(yeres!=NULL)
		WinExec("cmd /c start.lnk",SW_HIDE);
	else
		MessageBoxA(h,"无法执行，请将电子教室快捷方式命名为start.lnk放置于根目录下","提醒",MB_OK);
		
	// TODO: 在此添加控件通知处理程序代码
}
int suc=3,h_star0=0;

char op[100];
void C去除控制Dlg::OnBnClickedButton7()
{
	//USES_CONVERSION;
	GetDlgItemTextA(h,IDC_EDIT4,op,80);
	if(strlen(op)==0)
		{
			MessageBoxA(h,"你还没有输入命令呢","提醒",MB_OK);
			return;
		}
	int p=MessageBoxA(h,op,"确认执行?",MB_OKCANCEL);
	if(p==1)
		system(op);
	// TODO: 在此添加控件通知处理程序代码
}


void C去除控制Dlg::OnBnClickedButton11()
{
	USES_CONVERSION;
	//ShellExecute(NULL, L"open",L"explorer.exe", L"removectrl.sxl.cn", NULL, SW_SHOW);
	ShellExecute(NULL, L"open",L"explorer.exe",L"https://removectrl.gitee.io/home/", NULL, SW_SHOW);
	// TODO: 在此添加控件通知处理程序代码
}

#include "SET.h"
void C去除控制Dlg::OnBnClickedButton12()
{


	//ShowWindow(IDD_DIALOG1);
	MessageBoxA(h,"如果你是技术人员，欢迎加入我们。\n群号：828869154 或直接搜  去除控制开发群 ","去除控制",MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}


void C去除控制Dlg::OnBnClickedButton8()
{
	if(ope==1)
		for(int i=1; i<=jfn; i++)
			{

				if(propid[15][i]!=0)
					skpx(propid[15][i]);

				ope=0;
			}
	else MessageBoxA(h,"然鹅机房助手并不在运行","去除控制",MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}


void C去除控制Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if(ope==1) skpx(fpid(xsjf[1]));
	else MessageBoxA(h,"然鹅机房助手并不在运行","去除控制",MB_OK);
	ope=0;
}



void C去除控制Dlg::OnBnClickedButton1()
{
	ShellExecute(NULL, L"open",L"explorer.exe",L"https://blog.csdn.net/qq_37485351/article/details/99538316", NULL, SW_SHOW);
	// TODO: 在此添加控件通知处理程序代码
}


void C去除控制Dlg::OnBnClickedButton10()
{
	GetDlgItemTextA(h,IDC_EDIT6,adress,20);
	MessageBoxA(h,adress,"确定？",MB_OKCANCEL);
}

int randnum(int fm,int lm)
{
	srand(int(time(0)));
	return (rand() % (lm-fm+1))+ fm;
}



void C去除控制Dlg::OnBnClickedButton15()
{
	SET dlg;
	dlg.DoModal();
	
	// TODO: 在此添加控件通知处理程序代码
}
bool isshowing=1;
#include "netw.h"
void C去除控制Dlg::OnBnClickedButton16()
{
	netw dlg;
	dlg.DoModal();
	isshowing=0;
	ShowWindow(SW_SHOW);
	isshowing=1;
	// TODO: 在此添加控件通知处理程序代码
}





void C去除控制Dlg::OnBnClickedButton21()
{
	__asm 
	{
		_emit 0xEB
			_emit 0x10
			_emit 0x56
			_emit 0x4D
			_emit 0x50
			_emit 0x72
			_emit 0x6F
			_emit 0x74
			_emit 0x65
			_emit 0x63
			_emit 0x74
			_emit 0x20
			_emit 0x62
			_emit 0x65
			_emit 0x67
			_emit 0x69
			_emit 0x6E
			_emit 0x00
	}
	SUPPORT temp1;
	temp1.DoModal();
	__asm
	{
		_emit 0xEB
			_emit 0x0E
			_emit 0x56
			_emit 0x4D
			_emit 0x50
			_emit 0x72
			_emit 0x6F
			_emit 0x74
			_emit 0x65
			_emit 0x63
			_emit 0x74
			_emit 0x20
			_emit 0x65
			_emit 0x6E
			_emit 0x64
			_emit 0x00
	}
	// TODO: 在此添加控件通知处理程序代码
}

extern HWND kp;
void C去除控制Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
		if(nHotKeyId==1001||nHotKeyId==1002) 
		{
			if(nage==0)
			{
				MessageBoxA(h,"被控端不在运行哦，不用杀掉","去除控制",MB_OK);
				return;
			}
				for(int i=1; i<=pron[nage]; i++)
					if(propid[nage][i]!=0)
						skpx(propid[nage][i]);
		}
		if(nHotKeyId==1003||nHotKeyId==1004)
		{

			


			if(::IsWindowVisible(kp)==1)
			{
				::ShowWindow(kp,SW_HIDE);
				 ShowWindow(SW_HIDE); 
			}
			else if(::IsWindowVisible(kp)==0)
			{
				if( ::IsWindowVisible(h)==1)
				{
					ShowWindow(SW_HIDE);
				}
				else if(::IsWindowVisible(h)==0)
				{
					ShowWindow(SW_SHOW);
				}
				::ShowWindow(kp,SW_SHOW);
			}
		}

	
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void C去除控制Dlg::OnEnChangeRichedit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


DWORD WINAPI timetnt1(LPVOID p)
{
	h_star0=1;
	Sleep(60*1000);
	for(int i=1; i<=pron[nage]; i++)
		skpx(propid[nage][i]);
	h_star0=0;
	return 0;
}




void C去除控制Dlg::OnBnClickedOnekill()

{
	if(nage==0)
	{
		MessageBoxA(h,"被控端未运行","去除控制",MB_OK);
		return;
	}
	if(h_star0==1)
	{
		MessageBoxA(h,"正在计时","去除控制",MB_OK);
		return;
	}
	MessageBoxA(h,"计时开始","去除控制",MB_OK);

	HANDLE dd = ::CreateThread(NULL,0,timetnt1,NULL,0,NULL);

	// TODO: 在此添加控件通知处理程序代码
}




BOOL CAboutDlg::OnQueryEndSession()
{
	if (!CDialogEx::OnQueryEndSession())
		return FALSE;
	// TODO:  在此添加专用的查询结束会话代码
	WinExec("cmd /c shutdown -a",SW_HIDE);
	MessageBoxA(h,"关机键拦截成功","提醒",MB_OK);
	fuck();
	return FALSE;
}




#include "tools.h"
void C去除控制Dlg::OnBnClickedTool()
{
	tools lp1;
	lp1.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


LRESULT C去除控制Dlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_QUERYENDSESSION == message)
	{
		WinExec("cmd /c shutdown -a",SW_HIDE);
		MessageBoxA(h,"关机键拦截成功","提醒",MB_OK);
		fuck();
		return FALSE;  // 根据MSDN，WM_QUERYENDSESSION 返回FALSE则取消关机
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
