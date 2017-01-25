// Copyright Werner Salomon 2002-2014
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Foo
{
    friend std::istream& operator>>( std::istream& in, Foo& foo );
private:
    int x_, y_;
    std::string desc_;
    double d_;
};

template< char C >
std::istream& Char( std::istream& in )
{
    char c;
    if( in >> c && c != C )
        in.setstate( std::ios_base::failbit );
    return in;
}
std::istream& operator>>( std::istream& in, Foo& foo )
{   // Format (Beispiel): "   23          ;         56           ;  Beschreibung  ;         0,0762"
    return getline( in >> foo.x_ >> Char<';'> >> foo.y_ >> Char<';'>, foo.desc_, ';' ) >> foo.d_;
}

int main()
{
    using namespace std;
    vector< Foo > foos;
    ifstream in("input.csv");
    if( !in.is_open() )
    {
        cerr << "Fehler beim Oeffnen" << endl;
        return -2;
    }
    in.imbue( locale("german") );   // -> ',' als Dezimaltrenner
    for( Foo foo; in >> foo; )
        foos.push_back( foo );
    if( in.eof() ) // EOF reached?
    {
        cout << "Ok " << foos.size() << " entries read" << endl;
    }
    return 0;
}
