//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           ListCtrlSbAdap.h
//
// Beschreibung: 
//  streambuf zum Schreiben in ein CListCtrl aus def MFC
//
//
// Autor:           Werner Salomon
//                  Kratzer Automation AG
//
// Compiler:        Microsoft Visual C++ 6.x
//
//////////////////////////////////////////////////////////////////////
// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_LISTCTRLSBADAP_H__CB878EC5_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
#define AFX_LISTCTRLSBADAP_H__CB878EC5_1F91_11D5_9BE7_525400DFD69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedListCtrl.h"     // Member 'm_spDev'
#include "once_value.h"         // Wert, der nach einmal Lesen wieder auf den Default zurückfällt
#include "buffer.h"             // Member 'm_buf'

#include <boost/shared_ptr.hpp> // shared_ptr
#include <streambuf>            // meine Basis Klasse
#include <string>               // wg. prefix

class CListCtrl;


class CListCtrlSbAdap  : public std::streambuf
{
public:
	explicit CListCtrlSbAdap( CListCtrl& listCtrl, int defaultIconNo = -1 );
    CListCtrlSbAdap* clone( int defaultIconNo = -1 );
	~CListCtrlSbAdap();

    void Icon( int iconNo );    // aktuelle Icon# setzen

protected:
    // die Klasse ist nicht direkt kopierbar (siehe clone)
	CListCtrlSbAdap( const CListCtrlSbAdap& listCtrl, int defaultIconNo = -1 );
    CListCtrlSbAdap& operator=( const CListCtrlSbAdap& );  // nicht implementiert

    typedef std::basic_streambuf< char_type, traits_type >  base_type;

	bool write();
    virtual int_type overflow( int_type c = traits_type::eof() );
	virtual int sync();

private:
    // --- Typedefs
    typedef boost::shared_ptr< CSharedListCtrl >    t_spDev;

    class prefix
    {
    public:
        prefix();
        void Init();
        std::string operator()();
    private:
        std::string     m_text;
        bool            m_initialized;
    };

    typedef once_value< int >   t_icon;

    // --- Members
    buffer< char_type > m_buf;          // Zwischenspeicher für eine Zeile
    t_spDev             m_spDev;        // das Device
    prefix              m_prefix;       // Das 'Prefix'-Objekt für den Vorspann-Text
	t_icon              m_icon;         // Aktuelles & Default-Icon#
};

#endif // !defined(AFX_LISTCTRLSBADAP_H__CB878EC5_1F91_11D5_9BE7_525400DFD69D__INCLUDED_)
