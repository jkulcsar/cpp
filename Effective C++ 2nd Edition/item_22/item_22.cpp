
//
// item 22: 
// prefer pass-by-reference to pass-by-value

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
public:
  Person()
  {
	  cout << "In Person() ctor... " << endl;
  }

  Person(string n, string a) : name(a), address(a)
  {
	  cout << "In Person() parameterized ctor... " << endl;
	  //this.name = name;
	  //this.address = address;
  }

  ~Person()
  {
	  cout << "In Person() dtor... " << endl;
  }
  
private:
  string name, address;
};

class Student: public Person {
public:
  Student()  {
	  	  cout << "In Student() ctor... " << endl;
  }
  Student(string sn, string sa) : schoolName(sn), schoolAddress(sa)  {
	  cout << "In Student() parameterized ctor... " << endl;
  }
  ~Student()  {
	  cout << "In Student() dtor... " << endl;
  }
 
private:
  string schoolName, schoolAddress;
};


Student returnStudentByVal(Student s) {
  return s;
}

const Student& returnStudentByRef(const Student& s) {
	return s;
}

//
// another advantage of pass-by-reference is to avoid the "slicing" problem

class Window {
public:
	Window(string n) : name(n) {
		cout << "In Window ctor..." << endl;
	}
	string getName() const {
	  // return name of window
		return name;
	}
	virtual void display() const {
		// draw window and contents
		cout << "Displaying Window..." << endl;
	}
private:
	string name;
};
class WindowWithScrollBars: public Window {
public:
	WindowWithScrollBars(string name) : Window(name) {
		cout << "In WindowWithScrollBars ctor..." << endl;
	}
	virtual void display() const {
		cout << "Displaying WindowWithScrollBars..." << endl;
	}
};

// a function that suffers from the slicing problem
//
// The parameter w will be constructed — it's passed by value, remember? — 
// as a Window object, and all the specialized information that 
// made wwsb act like a WindowWithScrollBars object will be sliced off. 
// Inside printNameAndDisplay, w will always act like an object of class 
// Window (because it is an object of class Window), regardless of the 
// type of object that is passed to the function. In particular, 
// the call to display inside printNameAndDisplay will always call 
// Window::display, never WindowWithScrollBars::display. 
//
void printNameAndDisplayByVal(Window w)
{
  cout << w.getName() << endl;
  w.display();
}

// a function that doesn't suffer from the slicing problem
void printNameAndDisplayByRef(const Window& w)
{
  cout << w.getName() << endl;
  w.display();
}

int main(int argc, char** argv[])
{
	Student plato("Plato", "Athens");

	cout << "By value: " << endl;
	returnStudentByVal(plato);

	cout << "By reference: " << endl;
	returnStudentByRef(plato);

	cout << "Slicing problem: " << endl;
	WindowWithScrollBars wwsb("My Window-With-Scrollbars");
	printNameAndDisplayByVal(wwsb);
	printNameAndDisplayByRef(wwsb);


	return 0;
}