//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           switch_ios.h
//
// Beschreibung: 
//  Helper zum Umschalten des Streambufs global verfügbarer iostreams.
//  
// Anwendung:
//  Die Klasse, die den Streambuf stellt und verwaltet hat einen
//  Member switch_ios,
//      class MyClass
//      {
//          ..
//      private:
//          switch_ios  m_cout;  // Umschalten von cout
//
//  der wie folgt initialisiert wird:
//      MyClass::MyClass( ..
//          : ..
//          , m_cout( cout )
//
//  Das Umschalten erfolgt mit der Methode rdbuf
//  Entweder:
//      m_cout.rdbuf( &m_myStreambuf ); // mein Streambuf
//  oder:
//      m_cout.rdbuf( new CMyStreambuf, switch_out::is_owner );
//      // hier wird der Streambuf von 'switch_out' auch gelöscht
//
//  Das Zurückschalten des alten Streambuf und ggf. das Löschen des
//  gesetzten ( Parameter switch_out::is_owner) geschieht im
//  Destruktor.
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
#ifndef _SWITCH_IOS_H_
#define _SWITCH_IOS_H_

#include <streambuf>

template< typename charT, typename traits = std::char_traits< charT > >
struct switch_basic_ios
{
    typedef enum { is_owner, do_not_delete } t_isowner;

    explicit switch_basic_ios( std::basic_ios< charT, traits >& ios_ )
        : m_ios( ios_ )
        , m_pOldSb( 0 )
        , m_owner( false )
    {}

    ~switch_basic_ios()
    {
        reset( m_pOldSb );
    }

    // ---  neuen Streambuf setzen
    void rdbuf( std::basic_streambuf< charT, traits >* newSb, 
            t_isowner owner = do_not_delete )
    {
        reset( newSb );
        m_owner = ( owner == is_owner );
    }

private:
    // -- neuen Streambuf setzen, alten löschen, falls ich der Owner bin
    void reset( std::basic_streambuf< charT, traits >* newSb )
    {
        std::basic_streambuf< charT, traits >* oldSb = m_ios.rdbuf( newSb );
        if( m_owner )
            delete oldSb;
    }

    // --   Member
    std::basic_ios< charT, traits >&  m_ios;
    std::basic_streambuf< charT, traits >* m_pOldSb;
    bool    m_owner;

    // -- nicht kopierbar!
    switch_basic_ios( const switch_basic_ios& );
    switch_basic_ios& operator=( const switch_basic_ios& );
};


typedef switch_basic_ios< char >    switch_ios;
typedef switch_basic_ios< wchar_t > switch_wios;

#endif  // ifndef _SWITCH_IOS_H_
