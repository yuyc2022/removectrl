
// 去除控制Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// C去除控制Dlg 对话框

class C去除控制Dlg : public CDialogEx
{
// 构造
public:
	C去除控制Dlg(CWnd* pParent = NULL);	// 标准构造函数
	
	
// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	CEdit jiaoshi;
	afx_msg void ToTray();
	afx_msg void DeleteTray();
	afx_msg void OnShowTask();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam) ;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnEnChangeRichedit21();
	afx_msg void OnBnClickedOnekill();
	
	
	
	afx_msg void OnBnClickedTool();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
