#pragma once


// tools �Ի���

class tools : public CDialogEx
{
	DECLARE_DYNAMIC(tools)

public:
	tools(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~tools();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
};
