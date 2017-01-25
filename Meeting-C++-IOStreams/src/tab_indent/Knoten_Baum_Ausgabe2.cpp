// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm> // std::transform
#include <iostream>
#include <iterator> // std::ostream_iterator
#include <memory> // std::autp_ptr
#include <cassert>
#include <vector>

namespace
{
    const int IO_TABINFO = std::ios_base::xalloc();
}

struct Prefix
{
    enum Direction { UpTree, DownTree };
    Prefix& operator+=( Direction dir )
    {
        m_prefix.push_back( dir );
        return *this;
    }
    Prefix& operator--()
    {
        assert( !m_prefix.empty() );
        m_prefix.pop_back();
        return *this;
    }
    template< typename E, typename Traits >
    friend std::basic_ostream< E, Traits >& operator<<( std::basic_ostream< E, Traits >& out, const Prefix& pfx )
    {
        if( !pfx.m_prefix.empty() )
        {
            std::transform( pfx.m_prefix.begin(), pfx.m_prefix.end()-1, pfx.m_prefix.begin()+1,
                std::ostream_iterator< const char*, E, Traits >( out ), &Prefix::make_token );
            out << " +- ";
        }
        return out;
    }
    static void destroy( std::ios_base::event ev, std::ios_base& io, int index )
    {
        if( ev == std::ios_base::erase_event )
        {
            assert( index == IO_TABINFO );
            delete static_cast< Prefix* >( io.pword( IO_TABINFO ) );
            io.pword( IO_TABINFO ) = 0;
        }
    }
private:
    static const char* make_token( Direction code, Direction next )
    {
        if( code != next ) return " |  ";
        return "    ";
    }
    std::vector< Direction > m_prefix;
};

Prefix& getTabPrefix( std::ios_base& io )
{
    void*& p = io.pword( IO_TABINFO );
    if( !p )
    {   
        p = new Prefix;
        io.register_callback( &Prefix::destroy, IO_TABINFO );
    }
    return *static_cast< Prefix* >( p );
}

struct Indent
{
    template< typename T >
    Indent( std::ios_base& io, T add )
        : m_io( io )
    {
        getTabPrefix( m_io ) += add;
    }
    ~Indent()
    {
        --getTabPrefix( m_io );
    }
private:
    std::ios_base& m_io;
    // -- uncopyable
    Indent( const Indent& );
    Indent& operator=( const Indent& );
};

template< typename E, typename Traits >
std::basic_ostream< E, Traits >& tab( std::basic_ostream< E, Traits >& out )
{
    return out << getTabPrefix( out );
}



//////////////////////////////////////////////////////////////////////////////////////////

class FiboTree
{
    struct Knoten
    {
        explicit Knoten( int id = 1, Knoten* links = 0, Knoten* rechts = 0 ) 
            : m_id( id )
            , m_links( links )
            , m_rechts( rechts )
        {}
        ~Knoten() { delete m_links; delete m_rechts; }

        static Knoten* make_fibo_tree( int tiefe )
        {
            assert( tiefe >= 0 );
            switch( tiefe )
            {
            case 0:
                return 0;
            case 1:
                return new Knoten( 1 );
            }
            //default: tiefe >= 2
            return new Knoten( tiefe, make_fibo_tree( tiefe-1 ), make_fibo_tree( tiefe-2 ) );
        }

        friend std::ostream& operator<<( std::ostream& out, const Knoten& kn )
        {
            Knoten::print_child( out, kn.m_rechts, Prefix::UpTree );
            out << tab << "Knoten(" << kn.m_id << ")" << std::endl;
            Knoten::print_child( out, kn.m_links, Prefix::DownTree );
            return out;
        }

    private:
        template< typename T >
        static void print_child( std::ostream& out, const Knoten* child, T add )
        {
            if( child )
            {
                Indent ind( out, add );
                out << *child;
            }
        }
        // -- members
        int m_id;
        Knoten* m_links;
        Knoten* m_rechts;

        // -- uncopyable
        Knoten( const Knoten& );
        Knoten& operator=( const Knoten& );
    };

public:
    explicit FiboTree( int tiefe ) : m_root( Knoten::make_fibo_tree( tiefe ) ) {}
    friend std::ostream& operator<<( std::ostream& out, FiboTree& ft )
    {
        if( ft.m_root.get() )
            return out << *ft.m_root;
        return out;
    }
private:
    std::auto_ptr< Knoten > m_root;
};


int main()
{
    using namespace std;
    FiboTree tree( 8 );
    cout << tree << endl;
    return 0;
}
