#pragma once


// 最小化 对话框

class 最小化 : public CDialog
{
	DECLARE_DYNAMIC(最小化)

public:
	最小化(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~最小化();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
