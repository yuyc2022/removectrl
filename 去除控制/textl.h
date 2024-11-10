#pragma once


// textl 对话框

class textl : public CDialogEx
{
	DECLARE_DYNAMIC(textl)

public:
	textl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~textl();

// 对话框数据
	enum { IDD = IDD_textl };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
