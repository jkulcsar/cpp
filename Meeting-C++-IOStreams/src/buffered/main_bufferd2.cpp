//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How - IO mit C++ 
//
// Datei:           main_bufferd1.cpp
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
#include "wech.h"               // mein "Device"
#include "showState.h"          // gibt den Status eines IOS aus

#include <iostream>
using namespace std;




//////////////////////////////////////////////////////////////////////
//  Beispiel für einen streambuf mit gepufferter Ausgabe
//  
class MeinSB : public std::streambuf
{
public:
	MeinSB()
    { 
        setp( m_buff, m_buff+8 ); // jetzt sitzen die Pointer
	}

    ~MeinSB()
    {
        sync();                 // .. empfehlenswert
    }

protected:
    // -- wird gerufen, falls Buffer voll
virtual int_type overflow( int_type c = traits_type::eof() )
{
    if( write_to_device() < 0 )     // nach device schreiben
        return( traits_type::eof() );       // Oops! - Fehler
    
    if( traits_type::eq_int_type( c, traits_type::eof()) )
        return( traits_type::not_eof( c ) );

    *pptr() = traits_type::to_char_type( c );
    pbump( 1 );                     // pptr += 1
    return( c );                    // Ok
}	
    
    // -- wird nach flush (z.B. in endl) gerufen
    virtual int sync()
    {
        return( write_to_device() );
    }

private:
    // --   private: Schreibt den buffer in das Device
    int write_to_device()
    {
        int anz = pptr() - pbase();     // Anzahl Zeichen im Buffer
        if( anz == 0 )
            return( 0 );                // nix zu tun

        if( HauWech( pbase(), anz ) < 0 )    // to device
            return( -1 );               // Fehler!, dann weitergeben
        setp( m_buff, m_buff+8 );       // reset buffer - oder pbump( -anz ); !
        return( 0 );                    // Ok
    }

    char m_buff[8];  // das ist mein Buffer
};



//////////////////////////////////////////////////////////////////////
//  Anwendung von 'MeinSB'
//
int main()
{
    cout << "Beispiel 'gepufferte Ausgabe'" << endl;

    MeinSB sb;
    ostream out( &sb );

    out << 4711 << endl;
    out << "Ok !?" << endl;
    if( out )
        cout << "Alles klar! " << endl;

    out << "dann kann gar nix mehr schiefgehen !" << endl;
    if( !out )  // .. oder liegt da noch ein Fehler vor?
        cerr << "Error ! - Zustand von 'out': " << showState( out ) << endl;
    else
        cout << "jetzt geht's " << endl;

    out << "Huhu!"; // << endl - vergessen

    cout << "*** Programm Ende ***" << endl;
    return( 0 );
}
