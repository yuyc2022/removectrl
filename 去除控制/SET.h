#pragma once


// SET �Ի���

class SET : public CDialogEx
{
	DECLARE_DYNAMIC(SET)

public:
	SET(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SET();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
};
