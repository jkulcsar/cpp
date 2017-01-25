
#include <iostream>
#include <vector>
#include <algorithm>
#include "../util/print.hpp"

class MeanValue {
private:
    size_t num_; // number of elements
    long   sum_; // sum of all elements
public:
    MeanValue() : num_(0), sum_(0) {
    }
    
    void operator()(int elem) {
        num_++;
        sum_ += elem;
    }
    
    double value() {
        if(num_ != 0)
            return (double)sum_ / (double)num_;
        else
            return 0;
    }
    
    
};

int main(int argc, char** argv) {
    
    std::vector<int> collection;
    
    for( int i=0; i<20; ++i)
        collection.push_back(i);
    PRINT_ELEMENTS(collection);

    // std::for_each has the unique ability to return the function
    // object it uses (no other algorithm does this)
    // this is a copy of the internal fo
    
    MeanValue mv = std::for_each(
            collection.begin(),
            collection.end(),
            MeanValue()
          );
    std::cout << "mean value is: " << mv.value() << std::endl;
    
    return 0;
}