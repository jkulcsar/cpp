

template <typename X>
class Base {
public:
	int basefield;
	typedef int T;
};

class D1 : public Base<Base<void> > {	// not a template case really
public:
	void f() {
		// usual access to inherited member
		basefield = 3;
	}
};

template <typename T>
class D2 : public Base<double> {
public:
	void f() {
		basefield = 7;
	}

	// T is Base<double>::T , NOT the template parameter!
	T strange;	
};

// non-dependent base classes behave very much like base classes in ordinary,
// non-template classes but there is a slightly unfortunate surprise:
// when an unqualified name is looked up in the templated derivation,
// the non-dependent bases are considered before the list of template parameters;
//
// this is counter-intuitive!
//
// this means that in the previous example the member 'strange' of the class template
// D2 always has the type T corresponding to Base<double>::T (which is int);
// for example, the following function is not valid C++ :

//		void g( D2<int*> d2, int* p ) {
//			d2.strange = p;	// error, type mismatch
//		}

template <typename T>
class DD : public Base<T> {
public:
	void f() {
		basefield = 0;
	}
};

//template<>
//class Base<bool> {
//public:
//	enum { basefield = 42 };
//};

void gg(DD<bool>& d) {
	d.f();
}


int main(int argc, char** argv) {

	return 0;
}
