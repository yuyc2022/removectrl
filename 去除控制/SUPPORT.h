#pragma once


// SUPPORT 对话框

class SUPPORT : public CDialog
{
	DECLARE_DYNAMIC(SUPPORT)

public:
	SUPPORT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SUPPORT();

// 对话框数据
	enum { IDD = IDD_SUPPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
