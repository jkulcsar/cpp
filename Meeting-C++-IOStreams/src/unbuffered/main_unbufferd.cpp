//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How - IO mit C++ 
//
// Datei:           main_unbufferd.cpp
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
#include "showState.h"

#include <iostream>
#include <streambuf>
using namespace std;

struct Kassel
{
    Kassel() : m_err( false ) {}
    void setError() { m_err = true; }

    int operator()( char c )
    {
        if( m_err ) return( -1 );
        cout << "Kassel> " << c << endl;
        return 0;
    }

    bool m_err;
};

Kassel abNachKassel;



//////////////////////////////////////////////////////////////////////
//  Beispiel für einen streambuf mit ungepufferter Ausgabe
//
class MeinSB : public std::streambuf
{
protected:
    virtual int_type overflow( int_type c = traits_type::eof() )
    {
        if( !traits_type::eq_int_type( c, traits_type::eof()) )
            if( abNachKassel( traits_type::to_char_type( c ) ) < 0)
                return( traits_type::eof() );  // Fehler
        return traits_type::not_eof( c );
    }		
};


//////////////////////////////////////////////////////////////////////
//  Anwendung von 'MeinSB'
//
int main()
{
    cout << " .. Beispiel 'ungepufferte Ausgabe' " << endl;

    MeinSB sb;
    ostream out( &sb );

    for( int i=1; i<=2; ++i )
    {
        int z = 9422;
        out << z/2;
        clog << " .. nach dem " << i << ". Schreiben von " << z/2 << endl;
        clog << " .. Status von 'out': " << showState( out ) << endl;

        abNachKassel.setError();        // Fehler simulieren
    }

    return 0;
}
