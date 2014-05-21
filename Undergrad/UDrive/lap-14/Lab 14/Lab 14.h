// Lab 14.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLab14App:
// See Lab 14.cpp for the implementation of this class
//

class CLab14App : public CWinApp
{
public:
	CLab14App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CLab14App theApp;