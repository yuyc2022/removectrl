#pragma once


// ��С�� �Ի���

class ��С�� : public CDialog
{
	DECLARE_DYNAMIC(��С��)

public:
	��С��(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~��С��();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
