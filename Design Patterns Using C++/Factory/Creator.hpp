
#include "Product.hpp"

//
// the following is implementation using templates


// declarations
class Creator {
public:
	virtual Product* CreateProduct() = 0;
};

template <typename TheProductType>
class StandardCreator : public Creator {
public:
	virtual Product* CreateProduct();
};

// definitions
template <typename TheProductType>
Product* StandardCreator<TheProductType>::CreateProduct() {
	return new TheProductType;
}


