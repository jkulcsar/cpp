//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How - IO mit C++ 
//
// Datei:           wech.cpp
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
#include "wech.h"

#include <iostream>
#include <algorithm>            // copy
#include <iterator>             // ostream_iterator
using namespace std;

namespace { // nur lokal definiert
    struct readable     // gibt auch Steuerzeichen lesbar aus
    {
        readable( char c ) : m_c(c) {}
        char m_c;
    };

    ostream& operator<<( ostream& out, const readable& r )
    {
        switch( r.m_c )
        {
        case '\n': return( out << "\\n" );
        case '\t': return( out << "\\t" );
        case '\r': return( out << "\\r" );
        case '\0': return( out << "\\0" );
        default: return( out << r.m_c );
        }
    }
}


int HauWech( const char* pBase, unsigned anz )
{
    static int cnt = 0;
    clog << " .. HauWech(" << ++cnt << "): ";
    copy( pBase, pBase + anz, ostream_iterator< readable >( clog ) );
    clog << endl;
    return 0;    // kein Fehler
}
