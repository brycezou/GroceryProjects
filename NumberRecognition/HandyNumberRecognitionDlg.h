
// HandyNumberRecognitionDlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#include "opencv2/opencv.hpp"

using namespace cv;

// CHandyNumberRecognitionDlg �Ի���
class CHandyNumberRecognitionDlg : public CDialogEx
{
// ����
public:
	CHandyNumberRecognitionDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CDC *pDC;

// �Ի�������
	enum { IDD = IDD_HANDYNUMBERRECOGNITION_DIALOG };

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void OnRefreshWindow(void);
	void OnShowImage(IplImage* img, UINT ID);
	afx_msg void OnBnClickedButtonRecognize();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
