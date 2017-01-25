
//
// Ilustrates using shared_ptr with a type that requires other cleanup than
// a simple delete; there is support for such cases in shared_ptr through
// what is called custom deleters
// Example: managing FILE*

#include "boost/shared_ptr.hpp"
#include <iostream>

class FileCloser {
public:
	void operator()(FILE* file) {
		std::cout << "The FileCloser has been called with a FILE*, "
			"which now wil be closed." << std::endl;
		if(file != 0)
			fclose(file);
	}
};

int main(int argc, char** argv) {
	std::cout << "shared_ptr example with a custom deallocator." << std::endl;
	{
		FILE* f = fopen("test.txt", "r");
		if(f == 0) {
			std::cout << "Unable to open file." << std::endl;
			throw "Unable to open file";
		}

		boost::shared_ptr<FILE> my_shared_file(f, FileCloser());

		// position the file pointer
		fseek(my_shared_file.get(), 42, SEEK_SET);
	}
	std::cout << "By now, the FILE has been closed!" << std::endl;

	return 0;
}