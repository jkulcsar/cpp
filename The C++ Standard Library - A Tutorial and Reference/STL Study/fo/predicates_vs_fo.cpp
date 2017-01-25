
#include <iostream>
#include <list>
#include <algorithm>
#include "../util/print.hpp"

using namespace std;


class Nth {    //function object that returns true for the nth call
    private:
    int nth;          //call for which to return true
    int count;        //call counter
    public:
    Nth (int n) : nth (n), count (0) {
    }
    bool operator() (int)  {
        return ++count == nth;
    }
    
//    bool operator() (int) const {
//        return ++count == nth;
//    }
};


int main()
{
    list<int> coll;


    //insert elements from 1 to 9
    for (int i=1; i<=9; ++i) {
        coll.push_back(i);
    }
    PRINT_ELEMENTS(coll,"collection is: ");


    // remove third element, however
    // Two elements, namely the third and sixth elements are removed. 
    // This happens because the usual implementation of the algorithm copies 
    // the predicate internally during the algorithm; this is normal STL behavior;
   
    list<int>::iterator pos;
    pos = remove_if (coll.begin(),coll.end(),   //range
                    Nth(3)),                   //remove criterion
                    coll.erase (pos,coll.end()
            );
    PRINT_ELEMENTS (coll, "nth removed: ");
    
    //
    // using pass-by-ref does not help because
    // the internal find_if called by remove_if
    // refers back 
    Nth nth(2);
    pos = remove_if< list<int>::iterator, Nth& > (
            coll.begin(), coll.end(),
            nth),
            coll.erase( pos, coll.end() 
         );
    PRINT_ELEMENTS (coll, "nth removed: ");
    
//This behavior is not a bug. The standard does not specify how often a 
//predicate might be copied internally by an algorithm. Thus, to get the 
//guaranteed behavior of the C++ standard library you should not pass a 
//function object for which the behavior depends on how often it is copied or 
//called. 
//Thus, if you call a unary predicate for two arguments and both arguments 
//are equal, then the predicate should always yield the same result. 
//That is, a predicate should not change its state due to a call, and a copy of 
//a predicate should have the same state as the original. To ensure that you 
//can't change the state of a predicate due to a function call, you should 
//declare operator () as constant member function.    

}
   