// ListCtrlOut.h : main header file for the LISTCTRLOUT application
//
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(AFX_LISTCTRLOUT_H__CB878EB5_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
#define AFX_LISTCTRLOUT_H__CB878EB5_1F91_11D5_9BE7_525400DFD69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutApp:
// See ListCtrlOut.cpp for the implementation of this class
//

class CListCtrlOutApp : public CWinApp
{
public:
	CListCtrlOutApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlOutApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CListCtrlOutApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLOUT_H__CB878EB5_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
