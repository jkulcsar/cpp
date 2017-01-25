//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           IconNo.h
//
// Beschreibung: 
//  Klasse zur Representation eines Icons in einem ListCtrl.
//  (Details siehe icons.h)
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
#if !defined(AFX_ICONNO_H__711E4E66_2035_11D5_9BE8_525400DFD69D__INCLUDED_)
#define AFX_ICONNO_H__711E4E66_2035_11D5_9BE8_525400DFD69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iosfwd>

namespace icon
{
    class CIconNo  
    {
    public:             // -- Public-Interface
        // ---  Generieren
	    explicit CIconNo( int iconNo = -1 )
            : m_icon( iconNo )
        {}

        // ---  Zuweisung
        const CIconNo& operator=( int iconNo )
        {
            m_icon = iconNo;
            return( *this );
        }

        // ---  Abfrage der Nr.
        int No() const
        {
            return( m_icon );
        }

        // ---  Manipulator
        friend std::ostream& operator<<( std::ostream& out, const CIconNo& iconNo );

    private:
        int         m_icon;
    };
}



#endif // !defined(AFX_ICONNO_H__711E4E66_2035_11D5_9BE8_525400DFD69D__INCLUDED_)
