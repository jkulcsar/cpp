
#include <iostream>

class B1 {
private:
	int b1;
public:
	void mf1();
};

void B1::mf1() {
	std::cout << "b1=" << b1 << std::endl;
}

class B2 {
private:
	int b2;
public:
	void mf2();
};

void B2::mf2() {
	std::cout << "b2=" << b2 << std::endl;
}

class D : public B1, public B2 {
private:
	int d;
};


//void call_memfun(D obj, D::*pmf() ) {
//	obj.*pmf();
//}

int main(int argc, char** argv) {
	D obj;
	obj.mf1();
	obj.mf2();

	//call_memfun(obj, &D::mf1);
	//call_memfun(obj, &D::mf2);

	return 0;
}
