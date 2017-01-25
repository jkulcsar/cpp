
#include "double-link-list.hpp"

int main(int argc, char** argv) {

	dllist list1;
	list1.insert_end(1);
	list1.insert_end(2);
	list1.revert();

	return 0;
}