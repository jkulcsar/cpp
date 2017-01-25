#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

//
// The node class is used to represent both leaf
// and internal nodes. leaf nodes have 0s in the
// child pointers, and their value member corresponds
// to the character they encode.  internal nodes
// don't have anything meaningful in their value
// member, but their child pointers point to
// other nodes.
//
struct node {
	int weight;
	unsigned char value;
	const node *child0;
	const node *child1;
//
// Construct a new leaf node for character c
//
	node( unsigned char c = 0, int i = -1 ) {
		value = c;
		weight = i;
		child0 = 0;
		child1 = 0;
	}
//
// Construct a new internal node that has
// children c1 and c2.
//
	node( const node* c0, const node *c1 ) {
		value = 0;
		weight = c0->weight + c1->weight;
		child0 = c0;
		child1 = c1;
	}
//
// The comparison operator used to order the
// priority queue.
//
	bool operator<( const node &a ) const {
		return weight < a.weight;
	}

	bool operator>( const node &a ) const {
		return weight > a.weight;
	}

	void traverse( string code = "" )  const;
};

//
// The traverse member function is used to
// print out the code for a given node.  It
// is designed to print the entire tree if
// called for the root node.
//
void node::traverse( string code ) const
{
	if ( child0 ) {
		child0->traverse( code + '0' );
		child1->traverse( code + '1' );
	} else {
		cout <<" " <<value <<"	  ";
		cout <<setw( 2 ) <<weight;
		cout <<"	 " <<code <<endl;
	}
}


//
// This routine does a quick count of all the
// characters in the input file.  I skip the
// whitespace.
//
void count_chars( int *counts )
{
	for ( int i = 0 ; i <256 ; i++ )
		counts[ i ] = 0;
	ifstream file( "input.dat" );
	if ( !file ) {
		cerr <<"Couldn't open the input file!\n";
		throw "abort";
	}
	file.setf( ios::skipws );
	for ( ; ; ) {
		unsigned char c;
		file>> c;
		if ( file )
			counts[ c ]++;
		else
			break;
   }
}


int main(int argc, char** argv) {
	int counts[ 256 ];
	count_chars( counts );
	
	priority_queue< node, vector<node>, greater<node> > q;

//
// First I push all the leaf nodes into the queue
//
	for ( int i = 0 ; i <256 ; i++ )
		if ( counts[ i ] )
			q.push( node( i, counts[ i ] ) );

//
// This loop removes the two smallest nodes from the
// queue.  It creates a new internal node that has
// those two nodes as children. The new internal node
// is then inserted into the priority queue.  When there
// is only one node in the priority queue, the tree
// is complete.
//
	while ( q.size() <1 ) {
		node *child0 = new node( q.top() );
		q.pop();
		node *child1 = new node( q.top() );
		q.pop();
		q.push( node( child0, child1 ) );
	}
//
// Now I dump the results
//
	cout <<"Char  Symbol   Code" <<endl;
	q.top().traverse();

	return 1;
}
