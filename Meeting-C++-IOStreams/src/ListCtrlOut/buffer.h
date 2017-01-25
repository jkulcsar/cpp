//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           buffer.h
//
// Beschreibung: 
//  Einfache buffer-Klasse, die ein Array dynamisch anlegen und
//  vergrößern kann.
//  Das Interface ist einem std::<container> nachempfunden.
//
//  Es ist garantiert, das
//      - sich die Elemente in einem fortlaufenden Speicherbereich
//        befinden.
//      - die Iterator-Methoden stehts Werte vom Typ T* liefern.
//
//  Der Buffer ist dafür konzipiert 'von außen' auf die einzelnen
//  Elemente zugreifen zu können.
//
// Anwendung:
//  buffer< char > buf(200);    // char-Buffer 200
//  fill( buf.begin(), buf.end(), 'x' ); // ales mit 'x' füllen
//  char* p = buf.begin() + 12;
//  *p = '-';                   // zulässig !
//  buf.resize( 300 );          // Buffer vergrößern, 
//                              //  alter Inhalt wird kopiert.
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
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <algorithm>        // copy

template< typename T >
class buffer
{
public:
    typedef T               value_type;
    typedef value_type*     iterator;

    explicit buffer( unsigned sz )
        : m_base( new T[sz] )
        , m_end( m_base + sz )
    {}

    ~buffer()
    {
        delete[] m_base;
    }

    
    void resize( unsigned newSz )
    {
        T* base = new T[newSz];
        if( size() < newSz )    // alter Inhalt passt nicht - newSz ist kleiner!
            m_end = m_base + newSz;
        std::copy( m_base,  m_end, base );
        delete[] m_base;
        m_base = base;
        m_end = m_base + newSz;
    }

    iterator begin() { return( m_base ); }
    iterator end() { return( m_end ); }

    T& operator[]( unsigned i )
    {
        return( *(m_base + i) );
    }

    unsigned size() const
    {
        return( m_end - m_base );
    }

private:
    T*  m_base;
    T*  m_end;

    // ---  nicht kopierbar
    buffer( const buffer& );
    buffer& operator=( const buffer& );
};

#endif  // ifndef _BUFFER_H_
