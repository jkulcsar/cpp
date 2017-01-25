// ListCtrlOutDoc.h : interface of the CListCtrlOutDoc class
//
/////////////////////////////////////////////////////////////////////////////
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(AFX_LISTCTRLOUTDOC_H__CB878EBB_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
#define AFX_LISTCTRLOUTDOC_H__CB878EBB_1F91_11D5_9BE7_525400DFD69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CListCtrlOutDoc : public CDocument
{
protected: // create from serialization only
	CListCtrlOutDoc();
	DECLARE_DYNCREATE(CListCtrlOutDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlOutDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlOutDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlOutDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLOUTDOC_H__CB878EBB_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
