
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

const char *pToStrings[] = {"one", "two", "three"};

const std::string  	simpleArrayOfStrings[] =
{

	"aaaaa",
	"bbbbb"
};

const int simple_matrix[2][2] = {{0,1}, {2,3}};

class A
{
	int& my_int;
	const char* my_str;

public:
	void show()
	{
		cout << "my_int: " << my_int << " address: " << &my_int << endl;
		cout << "my_str: " << my_str << " address: " << &my_str << endl;
		cout << endl;
	}

	A(int& i, const char* str) : my_int(i)
	{
//		my_int = i;
		my_str = str;
	}

	void set_my_int(int& new_int)
	{
		my_int = new_int;
//		my_int(new_int);
	}

	void set_my_str( const char* new_str)
	{
		my_str = new_str;
	}
};

void doStuffOnValue( A a )
{
	cout << "Doing stuff on object passed by value, its a local copy! " << endl;
	int local_int = 3;
	const char* local_str("local_str_by_val");
	a.set_my_int(local_int);
	a.set_my_str(local_str);
	a.show();
}

void doStuffOnReference( A& a )
{
	cout << "Doing stuff on object passed by refernce, its NOT a local copy! " << endl;
	int local_int = 5;
	const char* local_str("local_str_by_ref");
	a.set_my_int(local_int);
	a.set_my_str(local_str);
	a.show();
}

int main( int argc , char** argv )
{
	int main_int = 1;
	const char* main_str("main_str");
	
	A myA(main_int, main_str);
	myA.show();

	doStuffOnValue(myA);
	doStuffOnReference(myA);

	myA.show();

	return 0;
}