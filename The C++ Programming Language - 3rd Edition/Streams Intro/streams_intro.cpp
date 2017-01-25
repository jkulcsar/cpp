
#include <iostream>

using namespace std;

//13.12.3 Input/Output Using Auxiliary Functions
//If the implementation of an I/O operator requires access to the private data 
//of an object, the standard operators should delegate the actual work to 
//auxiliary member functions. This technique also allows polymorphic read and 
//write functions. This might look as follows:

   class Fraction {
     int num;
	 int denom;
     public:
       virtual void printOn (std::ostream& strm) const; // output
       virtual void scanFrom (std::istream& strm);      // input
      // ...
   };

   std::ostream& operator << (std::ostream& strm, const Fraction& f)
   {
       f.printOn (strm);
       return strm;
   }

   std::istream& operator >> (std::istream& strm, Fraction& f)
   {
       f.scanFrom (strm);
       return strm;
   }
//A typical example is the direct access to the numerator and denominator 
//of a fraction during input:

   void Fraction::scanFrom (std::istream& strm)
   {
       //...
       // assign values directly to the components
	   int n, d;
	   strm >> n;
	   strm >> d;
       num = n;
       denom = d;
   }
//If a class is not intended to be used as a base class, the I/O operators 
//can be made friends of the class. However, note that this approach reduces 
//the possibilities significantly when inheritance is used. Friend functions 
//cannot be virtual; so as a result, the wrong function might be called. 
//For example, if a reference to a base class actually refers to an object 
//of a derived class and is used as an argument for the input operator, 
//the operator for the base class is called. To avoid this problem, 
//derived classes should not implement their own I/O operators. 
//Thus, the implementation sketched previously is more general than the 
//use of friend functions.
//It should be used as a standard approach, although most examples use 
//friend functions instead.




class MyBase {
public:
	// ... other public members here
	virtual ostream& put(ostream& s) const = 0; // write *this to s
};

ostream& operator << (ostream& s, const MyBase& mb ) {
	return mb.put(s);
}


class SomeType : public MyBase {
public:
	// ...
	ostream& put(ostream& s) const {	// the real output function, overrides MyBase::put()
		return s;
	}
};

void f( const MyBase& mb, SomeType& st) {
	cout << mb << st;
}

int main(int argc, char** argv) {
	MyBase* mb = new SomeType();
	SomeType st;

	// mb is actually pointing to a SomeType!
	f(*mb, st);

	return 0;
}