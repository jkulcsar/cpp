// ListCtrlOutDoc.cpp : implementation of the CListCtrlOutDoc class
//
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "stdafx.h"
#include "ListCtrlOut.h"

#include "ListCtrlOutDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutDoc

IMPLEMENT_DYNCREATE(CListCtrlOutDoc, CDocument)

BEGIN_MESSAGE_MAP(CListCtrlOutDoc, CDocument)
	//{{AFX_MSG_MAP(CListCtrlOutDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutDoc construction/destruction

CListCtrlOutDoc::CListCtrlOutDoc()
{
	// TODO: add one-time construction code here

}

CListCtrlOutDoc::~CListCtrlOutDoc()
{
}

BOOL CListCtrlOutDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutDoc serialization

void CListCtrlOutDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutDoc diagnostics

#ifdef _DEBUG
void CListCtrlOutDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CListCtrlOutDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutDoc commands
