
// GetCharacterDlg.h : ͷ�ļ�
//

#pragma once
#include "opencv2/opencv.hpp"

using namespace cv;

// CGetCharacterDlg �Ի���
class CGetCharacterDlg : public CDialogEx
{
// ����
public:
	CGetCharacterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETCHARACTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IplImage *dstImage;
	bool OnOpenRecvSocket(int recvport);
	CString m_strImageName;
	CString m_strTxtFileName;
	afx_msg void OnBnClickedButtonSave();
	void OnShowImage(IplImage* img, UINT ID);
};
