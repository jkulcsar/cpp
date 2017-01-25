//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How - IO mit C++ 
//
// Datei:           manipBase.h
//
// Beschreibung: 
//  Base-Class fuer Manipulatoren mit einer beliebigen Anzahl (>0)
//  von Parametern.
//  Vorteile:
//      Arbeitet mit beliebigen Ausgabe-Streams
//      Der Aufrufer muss keine Template-Parameter angeben.
//      Der Programmierer des Manipulators spart die Ausgabe-Funktion
//          seiner Klasse in den Stream.
//
//  Quelle:
//      Effective Standard C++ Library: Curiously Recurring Manipulators
//      Klaus Kreft und Angelika Langer
//      aus C/C++ User Journal; Expert Forum; Juni 2001
//      (nach einer Idee von 
//          Kevlin Henney, Curbralan Ltd., kevlin@curbralan.com, July 2000)
//
// Anwendung:
//      Es ist ein Funktor zu definieren, der von manipBase<>
//      abgeleitet ist und der eine Methode oder ein Methoden-Template
//      von operator() mit einem Stream als Template-Parameter hat.
//
//      class myManip : public manipBase< myManip >
//      {
//      public:
//          myManip( typ1 param1, .. )  // viele Parameter
//              : manipBase< myManip >()
//              , .. Parameter initialisieren
//          {}
//      
//          // ---- die eigentliche Funktion, die die Arbeit macht
//          template< typename ios_class >
//          void operator()( ios_class& os ) const
//          {
//              .. Manipulation durchfuehren
//          }
//      
//      private:
//         typ1 param1 ..usw;
//      };
//
//      // Aufruf
//      einStream << myManip( param1, .. ) << .. ;
//
//
// Autor:           Werner Salomon
//                  Oktober 2002
//
// Compiler:        Microsoft Visual C++ 6.x
//
//////////////////////////////////////////////////////////////////////
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////
#ifndef _MANIPBASE_H_
#define _MANIPBASE_H_

template< class Manip >
class manipBase
{
public:
    template< class Ostream > inline
    Ostream& manipulate_o( Ostream& str ) const
    {
        // call Manip::operator( ios )
        static_cast< const Manip& >(*this).operator()( str );
        return( str );
    }
    template< class Istream > inline
    Istream& manipulate_i( Istream& str )
    {
        // call Manip::operator( ios, int )
        static_cast< Manip& >(*this).operator()( str, int() );
        return( str );
    }
};

template< class Ostream, class Manip > inline
Ostream& operator<<( Ostream& os, const manipBase< Manip >& m )
{ 
    return( m.manipulate_o( os ) );
}

template< class Istream, class Manip > inline
Istream& operator>>( Istream& os, manipBase< Manip >& m )
{ 
    return( m.manipulate_i( os ) );
}


#endif  // ifndef _MANIPBASE_H_