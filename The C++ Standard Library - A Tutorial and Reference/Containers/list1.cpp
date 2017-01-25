#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

template<typename T>
void printLists (const list<T>& l1, const list<T>& l2)
    {

        cout << "list1: ";
        copy (l1.begin(), l1.end(), ostream_iterator<T>(cout," "));
		cout << endl;
		cout << "list2: ";
        copy (l2.begin(), l2.end(), ostream_iterator<T>(cout," "));
        cout << endl << endl;
    }


int main(int argc, char** argv)
{
	//create two empty lists
    list<int> list1, list2;

    //fill both lists with elements
    for (int i=0; i<6; ++i) {
		list1.push_back(i);
		list2.push_front(i);
	}
	printLists(list1, list2);

	//insert all elements of list1 before the first element with value 3 of list2 
	//find() returns an iterator to the first element with value 3
	list2.splice(
		find(list2.begin(), list2.end(), 3), // calculate target position
		list1 // source list
		);
	printLists(list1, list2);

	// move first element to the end
	list2.splice(
		list2.end(),	// destination position
		list2,			// source list
		list2.begin()	// source position
		);
	printLists(list1, list2);

	// sort the second list, assign it to the first list and remove the duplicates
	list2.sort();
	list1 = list2;
	list2.unique();
	printLists(list1, list2);

	// merge both lists into the first list
	// assuming both lists are already sorted,
	// the result will still be sorted 
	list1.merge(list2);
	printLists(list1, list2);
	std::next_permutation

	return 0;
}