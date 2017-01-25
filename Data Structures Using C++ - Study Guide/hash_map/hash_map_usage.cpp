
#include <hash_map>
#include <ostream>
#include <iostream>

//
// from Stroustrup book: map vs. hash_map
// (1) a map is always sorted and lookup is based on this since the data structure
// used by map is (a variation of) binary search tree
// (2) a hash_map relies on a hash_function which maps a value to an index in such a way
// that two distinct values rarely collide (having the same index);
// basically, a hash table is implemented by placing a value at it's index or 'nearby' if
// the slot at that index is taken; finding an element at it's index is fast while finding one
// at 'nearby' position is not slow
//
// FUNDAMENTAL difference between map and hash_map:
// map requires a '<' for it's elemnt type while hash_map requires a '==' and hash function
//

using namespace std;

typedef char* MyStr;

struct MyInt
{
	int i;
	friend ostream& operator<<(ostream& ii, MyInt& jj);
	MyInt(int j = 0) : i(j) {
	}
};

ostream& operator<<(ostream& o, MyInt& j)
{
	o << j.i;
	return o;
}

struct greater_str
{
	// operator() must be declared const !
	bool operator()(const MyStr& x, const MyStr& y) const
	{
		if(strcmp(x,y) < 0)
			return true;
		else
			return false;
	}
};

struct less_str
{
	// operator() must be declared const !
	bool operator()(const MyStr& x, const MyStr& y) const
	{
		if(strcmp(x,y) > 0)
			return true;
		else
			return false;
	}
};

int main(int argc, char** argv)
{
	using namespace stdext;

	typedef pair<MyStr, MyInt> Int_Pair;
	hash_map<MyStr, MyInt>::iterator hm1_Iter, hm3_Iter, hm4_Iter, hm5_Iter, hm6_Iter;
	hash_map<MyStr, MyInt, hash_compare<MyStr, greater_str> >::iterator hm2_Iter;

	// create an empty hash_map hm0 of key type integer
	hash_map<MyStr, MyInt> hm0;

	// create am empty hash_map hm1 with the key comparison function
	// defined by us: less_str, then insert 4 elements
	hash_map<MyStr, MyInt, hash_compare<MyStr, less_str> > hm1;

	hm1.insert(Int_Pair("one", 0));
	hm1.insert(Int_Pair("two", 10));
	hm1.insert(Int_Pair("three", 20));
    hm1.insert(Int_Pair("four", 30));
    hm1.insert(Int_Pair("five", 40));

	//
	// show hm1
	cout << "hm1 =";
    for (hm1_Iter = hm1.begin(); hm1_Iter != hm1.end(); hm1_Iter++)
        cout << " " << hm1_Iter -> first << " " << hm1_Iter -> second;
    cout << endl;


	// create an empty hash_map hm2 with the key comparison
    // function geater_str (defined by us), then insert 2 elements
    hash_map<MyStr, MyInt, hash_compare<MyStr, greater_str> > hm2;
    hm2.insert(Int_Pair("one", 10));
    hm2.insert(Int_Pair("two", 20));

	//
	// show hm2
    cout << "hm2 =";
    for (hm2_Iter = hm2.begin(); hm2_Iter != hm2.end(); hm2_Iter++)
        cout << " " << hm2_Iter -> second;
    cout << endl;


	// get the allocator used by a previous hash_map (here: hm1)
	hash_map<MyStr, MyInt>::allocator_type hm1_Alloc;
	hm1_Alloc = hm1.get_allocator();
	// now create a new hash_map, reusing the allocator we got previously
	hash_map<MyStr, MyInt, hash_compare<MyStr, less_str> > hm3(hash_compare<MyStr, less_str>(), hm1_Alloc);
	hm3.insert(Int_Pair("three", 30));

	//
	// show hm3
	cout << "hm3 =";
    for (hm3_Iter = hm3.begin(); hm3_Iter != hm3.end(); hm3_Iter++)
        cout << " " << hm3_Iter -> second;
    cout << endl;

	//
	// create a copy of hm1 into a new hash_map (here: hm4)
	// note that the template parameters are exactly the same
	hash_map<MyStr, MyInt, hash_compare<MyStr, less_str> > hm4(hm1);

	//
	// show hm4
	cout << "hm4 =";
    for (hm4_Iter = hm4.begin(); hm4_Iter != hm4.end(); hm4_Iter++)
        cout << " " << hm4_Iter -> second;
    cout << endl;

	//
	// create a hash_map hm5 by copying the range hm1[_First, _Last)
    hash_map<MyStr, MyInt>::const_iterator hm1_bcIter, hm1_ecIter;
    hm1_bcIter = hm1.begin();
    hm1_ecIter = hm1.begin();
    hm1_ecIter++;
    hm1_ecIter++;
    hash_map<MyStr, MyInt> hm5(hm1_bcIter, hm1_ecIter);
    
	//
	// show hm5
	cout << "hm5 =";
    for (hm5_Iter = hm5.begin(); hm5_Iter != hm5.end(); hm5_Iter++)
        cout << " " << hm5_Iter -> second;
    cout << endl;

	//
	// create a hash_map hm6 by copying the range hm4[_First, _Last)
    // and with the allocator of hash_map hm2
    hash_map<MyStr, MyInt>::allocator_type hm2_Alloc;
    hm2_Alloc = hm2.get_allocator();
    hash_map<MyStr, MyInt, hash_compare<MyStr, less_str> > 
		hm6(hm4.begin(), ++hm4.begin(), hash_compare<MyStr, less_str > (), hm2_Alloc);

	//
	// show hm6
    cout << "hm6 =";
    for (hm6_Iter = hm6.begin(); hm6_Iter != hm6.end(); hm6_Iter++)
        cout << " " << hm6_Iter -> second;
    cout << endl;

	return 0;
}
