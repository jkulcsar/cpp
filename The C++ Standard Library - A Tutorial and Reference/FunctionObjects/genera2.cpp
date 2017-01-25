#include <iostream>
#include <list>
#include <algorithm>

#include "print.hpp"

using namespace std;

class IntSequence {
public:
	IntSequence(int v) : value_(v) {
	}

	// "function call"
	int operator() () {
		return value_++;
	}
private:
	int value_;
};

int main(int argc, char** argv) {
	list<int> coll;
	IntSequence seq(1);	// sequence of integers, starting with 1

	// insert values from 1 to 4
	// - must pass function object by reference
	// in order to keep it's state (will continue counting from 5);
	// for this, we must pass generate_n explicit template arguments
	// fully qualified:
	//
	generate_n<back_insert_iterator<list<int> >, int, IntSequence&> (
		back_inserter(coll),	// start
		4,						// number of elements
		seq);					// generate values
	print_collection(coll, "Initial sequence: ");

	//insert values from 42 to 45
    generate_n (back_inserter(coll),         //start
                   4,                        //number of elements
                  IntSequence (42))   ;      //generates values
    print_collection(coll, "More added (non-reference used): ");


	//continue with first sequence
    // - pass function object by value
    //so that it will continue with 5 again
	//but will not keep it's state because the algorithm 
	//uses a local copy
    generate_n (back_inserter(coll),      //start
                4,                        //number of elements
               seq) ;                     //generates values
	print_collection(coll, "Sequence continued: ");

    generate_n (back_inserter(coll),      //start
                4,                        //number of elements
               seq) ;                     //generates values
	print_collection(coll, "Sequencer re-used (does not maintain state): ");

    generate_n<back_insert_iterator<list<int> >, int, IntSequence&> (
		back_inserter(coll),      //start
        8,                        //number of elements
        seq) ;                    //generates values
	print_collection(coll, "Sequencer re-used by reference (8 more elements added: ");

}