#pragma once


// textl �Ի���

class textl : public CDialogEx
{
	DECLARE_DYNAMIC(textl)

public:
	textl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~textl();

// �Ի�������
	enum { IDD = IDD_textl };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
