//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           SharedListCtrl.cpp
//
// Autor:           Werner Salomon
//                  Kratzer Automation AG
//
// Compiler:        Microsoft Visual C++ 6.x
//
//////////////////////////////////////////////////////////////////////
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////
#include "afxcmn.h"             // wg. CListCtrl (statt stdafx.h !)
#include "SharedListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
//  Konstanten fuer das List-Ctrl
static const int LEN_ITEM1 = 60;        // Breite der Spalte 1 in Pixel
static const char ITEM1[] = "SP1";      // Ueberschrift Spalte 1
static const char ITEM2[] = "- Text -"; // Ueberschrift Spalte 2


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSharedListCtrl::CSharedListCtrl( CListCtrl& listCtrl )
    : m_dev( listCtrl )
    , m_curItem( 0 )
{
    InitListCtrl();                     // List-Control init
}

CSharedListCtrl::~CSharedListCtrl()
{
}



//////////////////////////////////////////////////////////////////////
//  Fuegt an das List-Ctrl 'm_dev' ein weiteres Item an
//  'pfx' enthält den Text und 'icon' die Icon# fuer Spalte 1
//  'txt' zeigt auf den Text in Spalte 2
//
void CSharedListCtrl::InsertItem( const char *pfx, int icon, const char* txt )
{
    const int item = m_dev.InsertItem( m_curItem++, pfx, icon );
    m_dev.SetItemText( item, 1 , txt );
}



//////////////////////////////////////////////////////////////////////
//  Initialisiert das eigenen List-Ctrl
//    - zwei Spalten eröffnen. "ITEM1" (s. Konstanten) 'LEN_ITEM' breit
//      "ITEM2" so breit, wie der Rest des Fensters      
//    - Style 'LVS_REPORT' einschalten.
//
void CSharedListCtrl::InitListCtrl()
{
	// -- zwei Spalte erzeugen
    // Spalte 0 mit Ueberschrift "ITEM" erzeugen (Sub-Item-Idx 0)
	m_dev.InsertColumn(0, CString( ITEM1 ), LVCFMT_LEFT,
		LEN_ITEM1, 0);
    // Spalte 1 mit Ueberschrift "Msg-Text" erzeugen  (Sub-Item-Idx 1)
	CRect           rect;
	m_dev.GetWindowRect(&rect);              // aktuelle Fenster-Masse
	m_dev.InsertColumn(1, CString( ITEM2 ), LVCFMT_LEFT,
		rect.Width()-LEN_ITEM1, 1);

    // -- Style 'LVS_REPORT' setzen
    long style = GetWindowLong( m_dev.m_hWnd, GWL_STYLE );
	style &= ~(LVS_TYPEMASK);           // turn off all the style (view mode) bits
	style |= LVS_REPORT;                // Set the new style for the control
	SetWindowLong( m_dev.m_hWnd, GWL_STYLE, style );
}
