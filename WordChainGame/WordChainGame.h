
// WordChainGame.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CWordChainGameApp:
// �� Ŭ������ ������ ���ؼ��� WordChainGame.cpp�� �����Ͻʽÿ�.
//

class CWordChainGameApp : public CWinApp
{
public:
	CWordChainGameApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CWordChainGameApp theApp;