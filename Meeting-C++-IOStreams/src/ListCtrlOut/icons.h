//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           icons.h
//
// Beschreibung: 
//  Die unten extern deklarierten Objekte lassen sich bei der Ausgabe
//  in einen ostream als Manipulatoren verwenden, die ein bestimmtes Icon
//  der ausgegebenen Zeile voranstellen.
//  Beispiel:
//    #include "iocons.h"
//    #include <iostream>
//    ...
//    cout << icon::err << "hier ist ein Fehler aufgetreten.. " << endl;
//
//  Erfolgt diese Ausgabe in ein ListCtrl, so wird am Anfang dieser
//  Zeile das Icon 'icon::err' dargestellt.
//
//  Ein Objekt der Klasse CIconNo stellt ein Icon in einem ListCtrl 
//  dar. Es enthält den Index aus einer Image-List (MFC: CImageList),
//  auf die wiederum ein List-Ctrl (MFC: CListCtrl) zugreift.
//
//  Der Anwender stellt globale Objekte im namespace 'icon' zur 
//  Verfügung (s.u.). Diese werden hier extern deklariert.
//  Die Definition der Objekte sollte in der gleichen cpp-Datei wie
//  ihre Initialisierung stehen. (View-class eines MFC-Projekts)
//
//  Das Initialisieren der IconNo-Objekte geschieht zweckmäßig beim
//  Füllen der ImageList für das ListCtrl.
//
//  // Code-Auschnitt - Initialisieren eines CListView-Objekts
//  // Methode CListView::OnInitialUpdate()
//
//      m_Icons.Create( 16, 16, TRUE, 2, 2 );       // 16x16 small Icons
//      CWinApp* pApp = AfxGetApp();
//      
//      // -- Icons zur Imageliste hinzufügen und Nummern ablegen.
//      //    IDI_ERROR1 und IDR_LISTCTTYPE sind Icons aus den 
//      //    Resourcen des MFC-Projekts und muessen zur Verfuegung
//      //    gestellt werden.
//      icon::err    = m_Icons.Add( pApp->LoadIcon(IDI_ERROR1) );       // error-Icon
//      icon::info   = m_Icons.Add( pApp->LoadIcon(IDR_LISTCTTYPE) );   // info.Icon
//      
//      CListCtrl& listCtrl = GetListCtrl();  // Methode von CListView
//      listCtrl.SetImageList( &m_Icons, LVSIL_SMALL);
//
//  Bem.: Die Implementierung der Klasse CIconNo benötigt den streambuf
//  'class CListCtrlSbAdap'. (siehe ListCtrlAdap.cpp)
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
#ifndef _ICONS_H_
#define _ICONS_H_

#include "IconNo.h"             // Klasse CIconNo

namespace icon
{
    // -- frei von Anwender zu definierende globale Icon-Variablen
    extern CIconNo err;
    extern CIconNo info;
    extern CIconNo guckMal;
}

#endif  // ifndef _ICONS_H_
