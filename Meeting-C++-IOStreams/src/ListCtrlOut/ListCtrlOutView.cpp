//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           ListCtrlOutView.cpp
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
#include "stdafx.h"
#include "ListCtrlOut.h"

#include "ListCtrlOutDoc.h"
#include "ListCtrlOutView.h"

#include "ListCtrlSbAdap.h"
#include "icons.h"              // User-Defined Icons (s.u.)

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutView

IMPLEMENT_DYNCREATE(CListCtrlOutView, CListView)

BEGIN_MESSAGE_MAP(CListCtrlOutView, CListView)
	//{{AFX_MSG_MAP(CListCtrlOutView)
	ON_COMMAND(ID_GO, OnStart)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_Check, OnCheck)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutView construction/destruction
CListCtrlOutView::CListCtrlOutView()
    : CListView()
    , m_Icons()
    , m_reportSb()
    , m_cerr( cerr ) 
    , m_cout( cout ) 
    , m_genRand( 6789 )     // egal ! Startwert des Zufalls-Generators
{
	// TODO: add construction code here
}

CListCtrlOutView::~CListCtrlOutView()
{
}


BOOL CListCtrlOutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutView drawing

void CListCtrlOutView::OnDraw(CDC* pDC)
{
	CListCtrlOutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}



//////////////////////////////////////////////////////////////////////
//  hier geschieht das Anlegen der ListCtrlSb-Adapter 
//  und deren Initialisierung und die Initialisierung des ListCtrls
//
void CListCtrlOutView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

    if( !m_reportSb.get() )             // sicherstellen, dass nur EIN init
    {
        InitListCtrl();                 // ListCtrl und IconNo's initialisieren

        CListCtrlSbAdap lca( GetListCtrl() );  // Prototyp

        // -- cerr auf weiteres List-Ctrl umleiten
        //      Default-Icon ist jetzt icon::err
        m_cerr.rdbuf( lca.clone( icon::err.No() ), switch_ios::is_owner );

        // -- cout umleiten - default: kein Icon
        m_cout.rdbuf( lca.clone() );

        // -- Streambuf für temporäres Report
        m_reportSb.reset( lca.clone( icon::guckMal.No() ) ); 
    }
}



/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutView printing

BOOL CListCtrlOutView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListCtrlOutView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CListCtrlOutView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutView diagnostics

#ifdef _DEBUG
void CListCtrlOutView::AssertValid() const
{
	CListView::AssertValid();
}

void CListCtrlOutView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CListCtrlOutDoc* CListCtrlOutView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListCtrlOutDoc)));
	return (CListCtrlOutDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CListCtrlOutView message handlers

void CListCtrlOutView::OnCheck() 
{
	// Testzwecke - Überlauf des Buffers forcieren
	ostream out( m_reportSb.get() );
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	copy( arr, arr + sizeof(arr)/sizeof(arr[0]), 
        ostream_iterator< int >( out << icon::guckMal, " -                                - \n" ) );
    out << endl;

    out << "das ist ein Text ohne Zeilen-Ende" << flush;
    out << "-\n!" << flush;

}



//////////////////////////////////////////////////////////////////////
//  
void CListCtrlOutView::OnStart() 
{
	// TODO: Add your command handler code here
	ostream report( m_reportSb.get() );

    boost::uniform_smallint< int > z( 1, 7 );
    const int r = z( m_genRand );
    switch( r )
    {
    case 1:
        report << icon::err << "[report] Baetsch ... FEHLER auf report " << endl;
        break;
    case 2:
        report << icon::info << "[report] Info: " << endl;
        break;
    case 3:
        cout << "[cout] LF im Text ->\n<< ?? " << endl;
        break;
    case 5:
        report << "[report] da freut sich der Anwender " << endl;
        break;
    default:
        cout << "[cout] Ausgabe - random=" << r << endl;
        break;
    }
}



//////////////////////////////////////////////////////////////////////
//
void CListCtrlOutView::OnStop() 
{
    cerr << "Das ist eine Ausgabe auf 'cerr' " << endl;	
}



//////////////////////////////////////////////////////////////////////
//  Initialisiert die Icons des eigenen List-Ctrls
//    - Icons (IDI_ERROR1, IDR_LISTCTTYPE, IDI_DRACHE) in 
//      die SMALL-Liste anhaengen.
//  
//  Die globalen IconNo-Objekte werden mit den Nummern initialisiert
//
void CListCtrlOutView::InitListCtrl()
{
    // -- Image-Liste erzeugen
    m_Icons.Create( 16, 16, TRUE, 2, 2 );       // 16x16 small Icons
    CWinApp* pApp = AfxGetApp();

    // -- Icons zur Imageliste hinzufügen und Nummern ablegen
    //    (siehe Datei "icons.h")
    icon::err    = m_Icons.Add( pApp->LoadIcon(IDI_ERROR1) );   // error-Icon
    icon::info   = m_Icons.Add( pApp->LoadIcon(IDI_INFO) );     // info.Icon
    icon::guckMal= m_Icons.Add( pApp->LoadIcon(IDI_DRACHE) );   // ;-)

    CListCtrl& listCtrl = GetListCtrl();
    listCtrl.SetImageList( &m_Icons, LVSIL_SMALL);
}



//////////////////////////////////////////////////////////////////////
//  globale Icon#-Variablen anlegen (s. Datei "icons.h")
//
namespace icon
{
    CIconNo err;
    CIconNo info;
    CIconNo guckMal;
}

