
//
// list_splicing.cpp
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

template< typename T >
void show_list(const std::list<T>& l) {
    std::copy(l.begin(), l.end(), std::ostream_iterator<T>(std::cout, "\t|"));
    std::cout << std::endl << std::endl;
}

int  main(int argc, char** argv) {

    typedef std::list<int> IntList;
    
    IntList il1;
    IntList il2;
    
    for(size_t index = 0; index < 10; ++index) {
        il1.push_back(index);
        il2.push_back(index * 3);
    }
    
    show_list(il1);
    show_list(il2);
    
    // insert all elements of the second list into the first list, 
    // before the element with value 3
    il1.splice( 
        std::find(il1.begin(), il1.end(), 3),
        il2);
    
    show_list(il1);
    return 0;
}
