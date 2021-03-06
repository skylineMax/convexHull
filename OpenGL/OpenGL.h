
// OpenGL_VS_2017.h : main header file for the OpenGL_VS_2017 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "Resource.h"       // main symbols


// COpenGLVS2017App:
// See OpenGL_VS_2017.cpp for the implementation of this class
//

class COpenGLApp : public CWinAppEx
{
public:
	COpenGLApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLApp theApp;
