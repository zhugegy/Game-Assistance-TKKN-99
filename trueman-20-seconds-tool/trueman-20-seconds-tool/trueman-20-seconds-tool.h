
// trueman-20-seconds-tool.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Ctrueman20secondstoolApp:
// See trueman-20-seconds-tool.cpp for the implementation of this class
//

class Ctrueman20secondstoolApp : public CWinApp
{
public:
	Ctrueman20secondstoolApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Ctrueman20secondstoolApp theApp;