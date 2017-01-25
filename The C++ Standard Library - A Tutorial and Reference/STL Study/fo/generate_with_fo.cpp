
#include <iostream>
#include <algorithm>
#include <list>

#include "../util/print.hpp"

class IntSequence {
private:
    int value_;
public:
    IntSequence(int v) : value_(v) {
    }
    
    int operator()(){
        return value_++;
    }
};

int main(int argc, char** argv) {
    
    std::list<int> simpleIntList;
    IntSequence aSequence(13);
    
    std::generate_n(
         std::back_inserter(simpleIntList),
         9,
         IntSequence(90)
    );
    PRINT_ELEMENTS(simpleIntList);

    //
    // replace elements, starting from the second up to 
    // the second last
    std::generate(
        ++simpleIntList.begin(),
        --simpleIntList.end(),
        IntSequence(33)
    );
    PRINT_ELEMENTS(simpleIntList);
    
    // the fo is passed in by-value, the sequence will still
    // start from the initial value
    std::generate_n(
            std::back_inserter(simpleIntList),
            3,
            aSequence
            );
    PRINT_ELEMENTS(simpleIntList);
    
    // once again, the fo is passed by-value,
    // the sequence generated will start again from
    // the initial value of the fo
    std::generate_n(
            std::back_inserter(simpleIntList),
            3,
            aSequence
    );
    PRINT_ELEMENTS(simpleIntList);
//    
    // fo passed in by-ref;
    // the sequence will start from initial value, however
    // since the current state of the fo is altered
    // in the existing instance, this will be maintained
    std::generate_n< std::back_insert_iterator<std::list<int> >, int, IntSequence&>(
                std::back_inserter(simpleIntList),
                3,
                aSequence
            );
    PRINT_ELEMENTS(simpleIntList);

    // fo passed in by-ref;
    // the sequence will continue from the state of the fo
    std::generate_n< std::back_insert_iterator<std::list<int> >, int, IntSequence&>(
                std::back_inserter(simpleIntList),
                3,
                aSequence
            );
    PRINT_ELEMENTS(simpleIntList);
    
    return 0;
    
}