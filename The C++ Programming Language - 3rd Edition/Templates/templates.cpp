#include "String.hpp"
#include <complex>

using namespace std;

//
// Function template overloading
//
// One can declare several function templates with the same name
// and even declare a combination of function templates and ordinary
// functions with the same name.
// When an overloaded function is called, overload resolution is necessary
// to find the right function or function template to be invoked.
//
template<typename T> T my_sqrt(T);
template<class T> complex<T> my_sqrt(complex<T>);
double my_sqrt(double);

void f(complex<double> z) {
	my_sqrt(2);	// sqrt<int>(int);
	my_sqrt(2.0);	// sqrt(double);
	my_sqrt(z);	// sqrt<double>(complex<double>);
}


int main(int argc, char** argv) {
	String<char> s;

	return 0;
}