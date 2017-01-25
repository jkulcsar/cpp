//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How - IO mit C++ 
//
// Datei:           showState.h
//
// Beschreibung: 
//  Ausgabe der Flags einer IOS-Klasse (ios_base<> oder davon
//  abgeleitet).
//
// Anwendung:
//      CMyStream strm;    // abgeleitet von ios_base
//      strm << ...;
//      cout << "Zustand von MyStream: " << showState( strm ) << endl;
//
//  oder:
//      cin >> obj;
//      cout << "Zustand von cin: " << showState( cin ) << endl;
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
#ifndef _SHOWSTATE_H_
#define _SHOWSTATE_H_

#include "manipBase.h"

template< typename IO >
struct showState_t : public manipBase< showState_t< IO > >
{
    showState_t( const IO& io )
        : m_ios( io )
    {}

    template< typename Ostream >
    void operator()( Ostream& out ) const
    {
        if( m_ios.good() )
            out << "good ";
        else
        {
            if( m_ios.eof() )
                out << "eof ";
            out << "fail ";
            if( m_ios.bad() )
                out << "bad ";
        }
    }

private:
    const IO& m_ios;
};


// -- Factory-Function zum Erzeugen der Struktur
template< typename IO > inline
showState_t< IO > showState( const IO& io )
{
    return showState_t< IO >( io );
}


#endif  // ifndef _SHOWSTATE_H_
