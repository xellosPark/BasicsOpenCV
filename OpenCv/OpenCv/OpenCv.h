
// OpenCv.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// COpenCvApp:
// �� Ŭ������ ������ ���ؼ��� OpenCv.cpp�� �����Ͻʽÿ�.
//

class COpenCvApp : public CWinApp
{
public:
	COpenCvApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern COpenCvApp theApp;