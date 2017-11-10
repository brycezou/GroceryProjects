
// GetCharacterDlg.h : 头文件
//

#pragma once
#include "opencv2/opencv.hpp"

using namespace cv;

// CGetCharacterDlg 对话框
class CGetCharacterDlg : public CDialogEx
{
// 构造
public:
	CGetCharacterDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETCHARACTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
