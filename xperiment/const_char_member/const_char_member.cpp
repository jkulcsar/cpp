#include <iostream>
#include <string>
#include <vector>

class A {
	int& my_int;
	const char* my_str;
	const std::string& message;

	int _initSize;
	std::vector<std::string>	_words;
	std::vector<std::string>*	_pWords;

	std::string _another_str;

public:
	A(int& i, const char* str, const std::string& msg) : my_int(i), my_str(str), message(msg), _initSize(50) {
		_words.resize(_initSize);
		_pWords = new std::vector<std::string>(_initSize);
		_another_str.clear();

		_another_str = msg;
	}
	void show() {
		using namespace std;
		std::cout << my_int << " " << my_str << " " << message << std::endl;
		std::cout << "size of _words: " << _words.size() << std::endl;
		std::cout << "size of _pWords: " << _pWords->size() << std::endl;
		std::cout << "_another_str: " << _another_str << std::endl;

	}
};

int main(int argc, char** argv) {
	int i = 10;
	const char* hello = "hello";
	const std::string greeting("hola");

	A a(i, hello, greeting);


	a.show();

	return 0;
}