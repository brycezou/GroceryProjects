
// HandyNumberRecognition.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHandyNumberRecognitionApp:
// �йش����ʵ�֣������ HandyNumberRecognition.cpp
//

class CHandyNumberRecognitionApp : public CWinApp
{
public:
	CHandyNumberRecognitionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHandyNumberRecognitionApp theApp;