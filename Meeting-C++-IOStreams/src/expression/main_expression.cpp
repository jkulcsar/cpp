// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <iostream>
 
// --   liest 'C'; sonst wird 'in' auf Fehler gesetzt
template< char C >
std::istream& Char( std::istream& in )
{
    char c;
    if( in >> c && c != C )
        in.setstate( std::ios_base::failbit );
    return in;
}
 
// --   liefert 'true' falls das Zeichen 'e' in 'in' folgt
template< typename E, typename Traits >
bool ctest( std::basic_istream< E, Traits >& in, E e )
{
    if( in.good() )
    {
        const std::ctype< E >& ctype_fac = std::use_facet< std::ctype< E > >( in.getloc() );
        for( Traits::int_type m = in.rdbuf()->sgetc(); ; m = in.rdbuf()->snextc() )
        {
            if( Traits::eq_int_type( m, Traits::eof() ) )
            {
                in.setstate( std::ios_base::eofbit );
                break;
            }
            const char c = Traits::to_char_type( m );
            if( c == e )
            {   // --   gesuchtes Zeichen folgt im Stream
                in.rdbuf()->sbumpc();       // Zeichen konsumieren -> ++Lesezeiger
                return true;                // ok; Zeichen war da
            }
            if( (in.flags() & std::ios_base::skipws) == 0 || !ctype_fac.is( std::ctype< E >::space, c ) )
                break;
        }
    }
    return false;
}
 
// --   Der Ausdruck-Parser
template< typename T >
struct Expression
{
    typedef T value_type;
    explicit Expression( T& value ) : m_value( value ) {}
    friend std::istream& operator>>( std::istream& in, const Expression& expr )
    {
        expr.parse( in );
        return in;
    }
private:
    void parse( std::istream& in ) const;
    T& m_value;
};
 
template< typename T >
Expression< T > expression( T& value ) { return Expression< T >( value ); }
 
// --   Der Factor-Parser
template< typename T >
struct Factor
{
    explicit Factor( T& value ) : m_value( value ) {}
    friend std::istream& operator>>( std::istream& in, const Factor& x )
    {   // factor = number | "(" expression ")" .
        if( ctest( in, '(' ) )
            return in >> expression( x.m_value ) >> Char<')'>;
        return in >> x.m_value;
    }
private:
    T& m_value;
};
 
// --   Der Term-Parser
template< typename T >
struct Term
{
    explicit Term( T& value ) : m_value( value ) {}
    friend std::istream& operator>>( std::istream& in, const Term& x )
    {   // term = factor {("*"|"/") factor} .
        in >> Factor< T >( x.m_value );
        for( T value2;; )
        {
            if( ctest( in, '*' ) )
            {
                if( in >> Factor< T >( value2 ) ) x.m_value *= value2;
            }
            else if( ctest( in, '/' ) )
            {
                if( in >> Factor< T >( value2 ) ) x.m_value /= value2;
            }
            else
                break;
        }
        return in;
    }
private:
    T& m_value;
};
 
template< typename T >
void Expression< T >::parse( std::istream& in ) const
{   // expression = ["+"|"-"] term {("+"|"-") term} .
    const bool minus = !ctest( in, '+' ) && ctest( in, '-' ); // @Edit: Multiplikation mit -1 durch operator-() ersetzt
    in >> Term< T >( m_value );
    if( minus ) m_value = -m_value;
    for( T value2;; )
    {
        if( ctest( in, '+' ) )
        {
            if( in >> Term< T >( value2 ) ) m_value += value2;
        }
        else if( ctest( in, '-' ) )
        {
            if( in >> Term< T >( value2 ) ) m_value -= value2;
        }
        else
            break;
    }
}
 
int main()
{
    using namespace std;
    cout << "Taschenrechner mit den 4 Grundrechenarten:" << endl;
    cin >> noskipws;
    for( double d; cout << "> ", cin >> ws >> expression( d ); )
        cout << " = " << d << endl;
    return 0;
}