#pragma once


// SUPPORT �Ի���

class SUPPORT : public CDialog
{
	DECLARE_DYNAMIC(SUPPORT)

public:
	SUPPORT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SUPPORT();

// �Ի�������
	enum { IDD = IDD_SUPPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
