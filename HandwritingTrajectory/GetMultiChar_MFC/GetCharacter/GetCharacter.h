
// GetCharacter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetCharacterApp:
// �йش����ʵ�֣������ GetCharacter.cpp
//

class CGetCharacterApp : public CWinApp
{
public:
	CGetCharacterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetCharacterApp theApp;