
// ȥ������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Cȥ������Dlg �Ի���

class Cȥ������Dlg : public CDialogEx
{
// ����
public:
	Cȥ������Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	
	
// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
