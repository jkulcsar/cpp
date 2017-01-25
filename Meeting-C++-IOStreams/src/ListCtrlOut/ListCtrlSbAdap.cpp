//////////////////////////////////////////////////////////////////////
//
// Projekt:         Know How / iostreams & Co
//
// Packet:          ListCtrl-Output
//
// Datei:           ListCtrlSbAdap.cpp
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
#include "ListCtrlSbAdap.h"     // mein Include
#include "IconNo.h"             // CIconNo

#include <ctime>                // s. Methode prefix::Init()
#include <sstream>              // stringstream in Prefix()
#include <iostream>             // wg. rdbuf() in 'ostream << CIconNo'
#include <iomanip>              // wg. setfill, setw, ..


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

using namespace std;



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CListCtrlSbAdap::CListCtrlSbAdap( CListCtrl& listCtrl, int defaultIconNo )
    : base_type()
    , m_buf( 80 )   // char-buffer - Achtung: muss (!) groesser 0 initialisiert werden!
    , m_spDev()
    , m_prefix()
    , m_icon( defaultIconNo )
{
    m_spDev = t_spDev( new CSharedListCtrl( listCtrl ) );
}



//////////////////////////////////////////////////////////////////////
// Copy-Konstruktor
// streambuf & buffer werden nicht kopiert
//
CListCtrlSbAdap::CListCtrlSbAdap( const CListCtrlSbAdap& lca2, int defaultIconNo )
    : base_type()               // streambuf neu anlegen !
    , m_buf( 80 )               // char-buffer - neu anlegen
    , m_spDev( lca2.m_spDev )
    , m_prefix( lca2.m_prefix )
    , m_icon( defaultIconNo )
{
}



//////////////////////////////////////////////////////////////////////
//  
CListCtrlSbAdap* CListCtrlSbAdap::clone( int defaultIconNo )
{
    CListCtrlSbAdap* dup = new CListCtrlSbAdap( *this );
    dup->m_icon = t_icon( defaultIconNo );
    return( dup );
}



//////////////////////////////////////////////////////////////////////
// Bem.: Der (leere!) Destruktor ist notwendig, um die explicite
//  Kenntnis von 'CSharedListCtrl' über 
//  boost::shared_ptr<CSharedListCtrl> im H-File zu verhindern.
//
CListCtrlSbAdap::~CListCtrlSbAdap()
{
}



//////////////////////////////////////////////////////////////////////
//  Wird gerufen, wenn entweder einen neue Zeile (seit 'sync')
//  begonen wurde (!pbase()) oder der Buffer nicht ausreicht
//  also vergroessert werden muss.
//
CListCtrlSbAdap::int_type CListCtrlSbAdap::overflow( int_type c )
{
    if( !pbase() )                              // Pointer noch alle 0
    {
        // erstes Schreiben nach 'm_buf' steht an
        m_prefix.Init();                        // 1. Prefix-String Init
        m_buf[0] = traits_type::to_char_type( c );
        setp( m_buf.begin(), m_buf.begin()+1, m_buf.end() );
    }
    else
    {
        if( write() )                   // versuche wegzuschreiben, was geht
        {
            // es ist alles weg
            setp( pbase(), epptr() );   // Buffer ist frei
        }
        else if( pptr() == epptr() )    // trotzdem kein Platz im Buffer
        {
            // 'm_buf' ist zu klein -> also vergroessern
            m_buf.resize( 2*m_buf.size() );         // Buffer vergroessern
            // Put-Pointer neu setzen, aktuelle Schreibposition bestimmen
            setp( m_buf.begin(), m_buf.begin() + (pptr()-pbase()), m_buf.end() );
        }
        // jetzt ist wieder Platz in 'm_buf', ueberzaehliges Zeichen schreiben
        *pptr() = traits_type::to_char_type( c );
        pbump( 1 );
    }

    return( traits_type::not_eof( c ) );
}




//////////////////////////////////////////////////////////////////////
//  Schreibt den Inhalt von 'm_buf' als Item in das ListCtrl-Device
//  auf das 'm_spDev' zeigt.
//
int CListCtrlSbAdap::sync()
{
    if( write() )               // alles geschrieben ?
    {
        // ---  Buffer entfernen
        //      Das Setzen von 'pbase' auf 0 forciert den Aufruf von 'overflow'
        //      beim ersten Schreibversuch. (siehe Methode overflow)
        //      Und damit die Initialisierung des Prefixes
        setp( 0, 0 );
    }
    return( 0 );
}



//////////////////////////////////////////////////////////////////////
//  saver setzt eine Variable auf einen neuen Wert 'newVal'
//  und stellt in seinem Destruktor den alten Wert wieder her.
//
namespace { // nur lokal gültig
    template< typename T >
    struct saver
    {
        explicit saver( T& val, const T& newVal )
            : m_old( val )
            , m_val( val = newVal )
        {}

        ~saver()
        {
            m_val = m_old;
        }

        const T m_old;
        T& m_val;
    };
}



//////////////////////////////////////////////////////////////////////
//  schreibt jede volle Zeile in das Device CListCtrl.
//  liefert 'true' falls alle Zeichen aus dem Buffer weggeschrieben 
//  wurde.
//  In diesem Fall - return == true - muss sich der Aufrufer um die
//  Pointer des strembufs kümmern.
//
bool CListCtrlSbAdap::write()
{
#ifdef _MSC_VER // is Winzigweich :-(
    const char_type LF = _USE( getloc(), ctype< char_type > ).widen('\n');
    const char_type NL = _USE( getloc(), ctype< char_type > ).widen('\0');

#else                           // das wäre Standard
    const char_type LF = use_facet< ctype< char_type > >( getloc() ).widen('\n');
    const char_type NL = use_facet< ctype< char_type > >( getloc() ).widen('\0');
#endif

    char_type* pBeg = pbase();
    for( char_type* pEnd
        ; (pEnd = find( pBeg, pptr(), LF )) != pptr(); pBeg = pEnd + 1 )
    {
        saver< char_type > svr( *pEnd, NL );   // temporäres C-string Text-Ende
        // -- Item an das List-Ctrl anhaengen
        m_spDev->InsertItem( m_prefix().c_str(), m_icon(), pBeg );
    }

    if( pBeg != pbase() )       // Ist jetzt vorne im Buffer Platz ?
    {
        // dann kopiere den Rest nach vorne
        copy( pBeg, pptr(), pbase() );
    }
    if( pBeg != pptr() )        // es steht noch was im Buffer
    {
        // dann setze auch die Pointer auf die neuen Werte
        setp( pbase(), pbase() + ( pptr() - pBeg ), epptr() );
        return( false );
    }
    return( true );
}



//////////////////////////////////////////////////////////////////////
//  Setzt die interne Variable 'm_icon'
//  Gleichzeitig wird das 'm_prefix' initialisiert. Diese Routine
//  wird von den Manipulatoren
//  aufgerufen. D.h. es beginnt eine Ausgabe; daher das Init()!
//
void CListCtrlSbAdap::Icon( int iconNo )
{
    m_prefix.Init();
    m_icon = iconNo;
}



//////////////////////////////////////////////////////////////////////
//  Manipulator CIconNo (bzw. CIconNo-Ausgabe)
//  die aktuelle Icon# wird gesetzt.
//
namespace icon
{
    std::ostream& operator<<( std::ostream& out, const CIconNo& iconNo )
    {
        CListCtrlSbAdap* pLcAdap = dynamic_cast<CListCtrlSbAdap*>( out.rdbuf() );
        if( pLcAdap )
            pLcAdap->Icon( iconNo.m_icon );
        return( out );
    }
}



//////////////////////////////////////////////////////////////////////
//  Initialisieren des 'prefix'-Objekts.
//  Status ist 'Un-Initialized'
//
CListCtrlSbAdap::prefix::prefix()
    : m_text()
    , m_initialized( false )
{
}



//////////////////////////////////////////////////////////////////////
//  Initialisiert das Prefix mit der aktuellen Uhrzeit
//
void CListCtrlSbAdap::prefix::Init()
{
    if( m_initialized ) return;         // schon passiert, dann fertig

    // --- eintragen des Zeit-Stempels
    time_t jetzt;
    time( &jetzt );                     // Datum/Uhrzeit 'jetzt' setzen
    struct tm& t = *localtime( &jetzt );

    stringstream strm;
    strm << setfill('0') << setw(2) << t.tm_min << ':' << setw(2) << t.tm_sec;
    m_text = strm.str();                // String uebernehmen
    m_initialized = true;               // Merken verhindert doppeltes Init
}



//////////////////////////////////////////////////////////////////////
//  liefert den Prefix-Text zurueck und geht nach 'un-Initialized'
//
string CListCtrlSbAdap::prefix::operator()()
{
    m_initialized = false;
    return( m_text );
}

