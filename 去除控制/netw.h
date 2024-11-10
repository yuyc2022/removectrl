#pragma once


// netw 对话框

class netw : public CDialogEx
{
	DECLARE_DYNAMIC(netw)

public:
	netw(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~netw();

// 对话框数据
	enum { IDD = IDD_NETW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
};
