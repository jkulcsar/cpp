
//
// set_sort_crit.cpp

// an example of specifying and using the sorting criterion for a set at runtime

#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

#include "../util/print.hpp"

//

template< typename T>
class RuntimeCmp {
public:

    enum cmp_mode {
        normal,
        reverse
    };
private:
    cmp_mode mode_;

public:

    RuntimeCmp(cmp_mode mode = normal) : mode_(mode) {
    }

    // compare two elements

    bool operator()(const T& elem1, const T& elem2) {
        return mode_ == normal ? elem1 < elem2 : elem2 < elem1;
    }

    // comparison for sorting criteria

    bool operator==(const RuntimeCmp& rc) {
        return mode_ == rc.mode_;
    }
};

typedef std::set<int, RuntimeCmp<int> > IntSet;

void fill (IntSet& set)
   {
       //fill insert elements in random order
       set.insert(4);
       set.insert(7);
       set.insert(5);
       set.insert(1);
       set.insert(6);
       set.insert(2);
       set.insert(5);
   }

int main(int argc, char** argv) {
    
    IntSet s1;
    fill(s1);
    PRINT_ELEMENTS(s1, "first set is: ");
    
    RuntimeCmp<int> reverse_order_comparator(RuntimeCmp<int>::reverse);
    IntSet s2(reverse_order_comparator);
    fill(s2);
    PRINT_ELEMENTS(s2, "the 2nd set, with reverse order comparator: ");
    
    return 0;
}
