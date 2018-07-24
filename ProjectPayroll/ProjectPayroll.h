
// ProjectPayroll.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"	
#include "ProjectPayroll.h" // main symbols


// CProjectPayrollApp:
// See ProjectPayroll.cpp for the implementation of this class
//

class CProjectPayrollApp : public CWinApp
{
public:
	CProjectPayrollApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CProjectPayrollApp theApp;
