
#include <cstdio>
#include <iostream>
#include <boost/iostreams/filter/stdio.hpp>

using namespace boost::iostreams;

class shell_comments_stdio_filter : public stdio_filter {
public:
	explicit shell_comments_stdio_filter(char comment_char = '#') 
		: comment_char_(comment_char) {
	}

private:

	//
	// implementation of the virtual function do_filter():
	// the local variable skip keeps track of whether you are currently
	// processing a comment; the while loop reads a character from std::cin,
	// updates skip and writes c to std::cout unless skip is true.
	void do_filter() {
		bool skip = false;
		int c;
		while((c = std::cin.get()) != EOF) {
			skip = c == comment_char_ ?
				true:
				c == '\n' ? false : skip;
			if(!skip)
				std::cout.put(c);
		}
	}

	char comment_char_;
};

