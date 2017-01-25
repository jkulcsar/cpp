//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           SharedListCtrl.h
//
// Beschreibung: 
//  Ein Objekt dieser Klasse ist ein Wrapper fuer ein MFC-CListCtrl-Objekt.
//  Die Klasse wird von CListCtrlSbAdap benutzt. Fuer diese Klasse
//  liefert sie folgende Funktionalitaeten:
//   -  Share-Moeglichkeit von einem CListCtrl durch mehrere
//      Objekte der Klasse CListCtrlSbAdap.
//   -  Initialisierung des CListCtrl's
//      Zwei Spalten mit Ueberschriften (s. CSharedListCtrl::InitListCtrl)
//   -  Methode 'InsertItem' fuegt ein Item bestehen aus
//      zwei Texten (Prefix 'pfx' und eigentlicher Text) und einer Icon-Nr 
//      am Ort des aktuelle Item 'm_curItem' ein. Dies
//      wird immer hochgezaehlt.
//   -  Die Schnittstelle zu CListCtrlSbAdap (dieses H-File) ist MFC-frei!
//
//  Die Schnittstelle zum Anwender besteht nur in der Implementierung
//  der Methode InitListCtrl, bzw. den dazugehoerigen Konstanten. Hier
//  koennnen individuelle Anpassungen vorgenommen werden.
//  (siehe SharedListCtrl.cpp)
//
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
#if !defined(AFX_SHAREDLISTCTRL_H__711E4E67_2035_11D5_9BE8_525400DFD69D__INCLUDED_)
#define AFX_SHAREDLISTCTRL_H__711E4E67_2035_11D5_9BE8_525400DFD69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CListCtrl;

class CSharedListCtrl  
{
public:
	explicit CSharedListCtrl( CListCtrl& listCtrl );
	virtual ~CSharedListCtrl();

	void InsertItem( const char *pfx, int icon, const char* txt );

private:
	void InitListCtrl();

    // -- Members
    CListCtrl&  m_dev;          // 
    int         m_curItem;      // Item-Zaehler
};

#endif // !defined(AFX_SHAREDLISTCTRL_H__711E4E67_2035_11D5_9BE8_525400DFD69D__INCLUDED_)
