
#include "Creator.hpp"

//
// the client code only supplies the product class:
class MyProduct : public Product {
public:
	MyProduct() {}
	virtual ~MyProduct() {}
	void doSomethingSpecific() {}
	virtual void sellProduct() {}
};


int main(int argc, char** argv) {
	StandardCreator<MyProduct> creator;
	Product* p = creator.CreateProduct();
	p->sellProduct();

	return 0;
}
