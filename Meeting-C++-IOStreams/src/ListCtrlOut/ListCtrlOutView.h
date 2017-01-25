//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Beschreibung: 
//  Beispiel für eine CListView
//
//
// Autor:           Werner Salomon
//                  
//
// Compiler:        Microsoft Visual C++ 6.x
//
//////////////////////////////////////////////////////////////////////
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_LISTCTRLOUTVIEW_H__CB878EBD_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
#define AFX_LISTCTRLOUTVIEW_H__CB878EBD_1F91_11D5_9BE7_525400DFD69D__INCLUDED_

#include <boost/random.hpp>     // Member 'm_genRand'
#include <boost/scoped_ptr.hpp>

#include "switch_ios.h"         // Member 'm_cerr'

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListCtrlOutView : public CListView
{
protected: // create from serialization only
	CListCtrlOutView();
	DECLARE_DYNCREATE(CListCtrlOutView)

// Attributes
public:
	CListCtrlOutDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlOutView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlOutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlOutView)
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    typedef boost::minstd_rand t_zufallsGenerator;
	void InitListCtrl();

    // ---  private Members
    CImageList          m_Icons;

    boost::scoped_ptr< std::streambuf > m_reportSb; // Streambuf für Report    
    switch_ios          m_cerr;         // Streambuf-switcher für cerr
    switch_ios          m_cout;         // Streambuf-switcher für cout

    t_zufallsGenerator  m_genRand;
};

#ifndef _DEBUG  // debug version in ListCtrlOutView.cpp
inline CListCtrlOutDoc* CListCtrlOutView::GetDocument()
   { return (CListCtrlOutDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLOUTVIEW_H__CB878EBD_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
