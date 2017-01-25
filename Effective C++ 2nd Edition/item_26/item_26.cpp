//
// Item 26: Guard against potential ambiguity
//

class B;                    // forward declaration for
                            // class B
class A {
public:
	A(const B&){}           // an A can be
                            // constructed from a B
};

class B {
public:
	// a B can be converted to an A
	operator A() const {
		return *(A*)(this);
	}
};

void f(const A& a)
{
}

int main(int argc, char** argv[])
{
	const B b;
	A a(b);


	f(a);

//	f(b); // error, ambiguos
	f( static_cast<A>(b) );

	f( b.operator A() );
	f( A(b) );
	f( (A) b );
	

	return 0;
}