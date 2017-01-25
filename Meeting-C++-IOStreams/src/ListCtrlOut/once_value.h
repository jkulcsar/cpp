//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           once_value.h
//
// Beschreibung: 
//  Template zum Erzeugen eines Wertes, der nach einmaligen Lesen
//  wieder auf einen Default-Wert 'springt'.
//
// Anwendung:
//  once_value< int > once( 5 );    // Default ist 5
//  once = 42;                      // temporärer Wert ist jetzt 42
//  cout << "Temporärer Wert ist " << once() << endl; // -> 42
//  ..
//  cout << "Default-Wert ist " << once() << endl; // -> 5
//
//
// Autor:           Werner Salomon
//                  
// Compiler:        Microsoft Visual C++ 6.x
//
//////////////////////////////////////////////////////////////////////
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////
#ifndef _ONCE_VALUE_H_
#define _ONCE_VALUE_H_

template< typename T >
struct once_value
{
    typedef T   value_type;

    // ---  Wert mit Defaulteintrag erzeugen
    explicit once_value( const T& default_ = T() )
        : m_x( default_ )
        , m_default( default_ )
    {}

    // ---  Temporären Wert setzen
    const once_value& operator=( const T& x )
    {
        m_x = x;
        return( *this );
    }

    // ---  Einmaliger (!) lesender Zugriff
    T operator()()              
    {
        T ret( m_x );
        m_x = m_default;    // Default-Wert wieder herstellen
        return( ret );
    }

private:
    T   m_x;
    T   m_default;
};


#endif  // ifndef _ONCE_VALUE_H_
