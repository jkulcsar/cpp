// alg_next_perm.cpp
// compile with: /EHsc
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <ostream>

using namespace std;
class CInt;
ostream& operator<<( ostream& osIn, const CInt& rhs );

class CInt
{
public:
	CInt( int n = 0 ) : m_nVal( n ){}
	CInt( const CInt& rhs ) : m_nVal( rhs.m_nVal ){}
	CInt&   operator=( const CInt& rhs ) {m_nVal =
		rhs.m_nVal; return *this;}
	bool operator<( const CInt& rhs ) const
	{ return ( m_nVal < rhs.m_nVal );}
	friend   ostream& operator<<( ostream& osIn, const CInt& rhs );

private:
	int m_nVal;
};

inline ostream& operator<<( ostream& osIn, const CInt& rhs )
{
	osIn << "CInt( " << rhs.m_nVal << " )";
	return osIn;
}

// Return whether modulus of elem1 is less than modulus of elem2
bool mod_lesser ( int elem1, int elem2 )
{
	if ( elem1 < 0 )
		elem1 = - elem1;
	if ( elem2 < 0 )
		elem2 = - elem2;
	return elem1 < elem2;
};

int main( )
{
	// Reordering the elements of type CInt in a deque
	// using the prev_permutation algorithm
	CInt c1 = 5, c2 = 1, c3 = 10;
	bool deq1Result;
	deque<CInt> deq1, deq2, deq3;
	deque<CInt>::iterator d1_Iter;

	deq1.push_back ( c1 );
	deq1.push_back ( c2 );
	deq1.push_back ( c3 );

	cout << "The original deque of CInts is deq1 = (";
	for ( d1_Iter = deq1.begin( ); d1_Iter != --deq1.end( ); d1_Iter++ )
		cout << " " << *d1_Iter << ",";
	d1_Iter = --deq1.end( );
	cout << " " << *d1_Iter << " )." << endl;

	deq1Result = next_permutation ( deq1.begin ( ) , deq1.end ( ) );

	if ( deq1Result )
		cout << "The lexicographically next permutation "
		<< "exists and has\nreplaced the original "
		<< "ordering of the sequence in deq1." << endl;
	else
		cout << "The lexicographically next permutation doesn't "
		<< "exist\n and the lexicographically "
		<< "smallest permutation\n has replaced the "
		<< "original ordering of the sequence in deq1." << endl;

	cout << "After one application of next_permutation,\n deq1 = (";
	for ( d1_Iter = deq1.begin( ); d1_Iter != --deq1.end( ); d1_Iter++ )
		cout << " " << *d1_Iter << ",";
	d1_Iter = --deq1.end( );
	cout << " " << *d1_Iter << " )." << endl << endl;

	// Permuting vector elements with binary function mod_lesser
	vector <int> v1;
	vector <int>::iterator Iter1;

	int i;
	for ( i = -3 ; i <= 3 ; i++ )
	{
		v1.push_back( i );
	}

	cout << "Vector v1 is ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	next_permutation ( v1.begin ( ) , v1.end ( ) , mod_lesser );

	cout << "After the first next_permutation, vector v1 is:\n v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")." << endl;

	int iii = 1;
	while ( iii <= 5 ) {
		next_permutation ( v1.begin ( ) , v1.end ( ) , mod_lesser );
		cout << "After another next_permutation of vector v1,\n v1 =   ( " ;
		for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ;Iter1 ++ )
			cout << *Iter1  << " ";
		cout << ")." << endl;
		iii++;
	}

	vector<char> v2;
	vector<char>::iterator Iter2;
	v2.push_back('e');
	v2.push_back('g');
	v2.push_back('k');
	v2.push_back('m');
	v2.push_back('z');
	while(next_permutation(v2.begin(), v2.end())) {
		for(Iter2 = v2.begin(); Iter2 != v2.end(); Iter2++)
			cout << *Iter2 << " ";
		cout << endl;
	}
}