
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
using namespace std;

int main(int argc, char** argv) {

	try {
		po::options_description desc("Allowed descriptions");
		desc.add_options()
			("help", "produce help message")
			("compression", po::value<int>(), "set compression level")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if(vm.count("help")) {
			cout << desc << endl;
		}
		else {
			if(vm.count("compression")) {
				cout << "compression level was set to " << vm["compression"].as<int>() << endl;
			}
			else {
				cout << "compression level was not set" << endl;
			}
		}
	}
	catch(exception& e) {
		cerr << "" << e.what() << endl;
		return 1;
	}
	catch(...) {
		cerr << "Exception of unknown type!" << endl;
	}


	return 0;
}
