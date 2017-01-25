//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How - IO mit C++ 
//
// Datei:           main_manip_param.cpp
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
#include "manipBase.h"

#include <iostream>
using namespace std;



//////////////////////////////////////////////////////////////////////
//  
struct bar : public manipBase< bar > 
{
    bar( int x ) : m_x( x ) {}

    void operator()( basic_ios< char >& strm ) const
    {
        // mache was mit m_x und strm - z.B.:
        ostreambuf_iterator<char> oItr( strm.rdbuf() );
        for( int n = m_x; n; --n, ++oItr )
            if( (*oItr = '=').failed() ) // Zeichen in Streambuf schreiben
            {
                strm.setstate( ios_base::badbit );
                break;
            }
    }

private:
    int m_x;
}; 



//////////////////////////////////////////////////////////////////////
//  
int main()
{
    cout << "Beispiel fuer Manipulatoren mit Parametern \n" << endl;
    cout << bar( 24 ) << " <- ein bar " << endl;
    return( 0 );
}
