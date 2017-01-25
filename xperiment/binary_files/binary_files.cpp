
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main( int argc, char* argv[] )
{
	std::string filename;
	std::vector< std::string > v;

	////
	//// read argument(s)
	//if( argc <= 1 )
	//	std::cout << "Usage: " << argv[0] << "  <filename>" << std::endl;
	//else
	//	filename = argv[1];

	//if( !filename.empty() )
	//{
	//	std::cout << filename << std::endl;

	//	std::ifstream infile;
	//	std::ostringstream ostr;
	//	try
	//	{
	//		infile.open( filename.c_str(), std::ios::in, std::ios::binary );

	//		// save formatting flags of the current output stream (here: stringstream)
	//		ios::fmtflags	oldFormatFlags = ostr.flags();

	//		// modify formatting flags for output string (here: stringstream)
	//		// do not show base (here:hex) and make uppercase
	//		ostr.setf(ios_base::uppercase);

	//		char c;
	//		while( infile >> c )
	//			ostr << hex << static_cast<int>(c);


	//		// restore formatting flags
	//		ostr.flags( oldFormatFlags );

	//		std::cout << ostr.str();

	//		vector< string >::iterator pos;
	//		int ncount = 0;	// count individual bytes to be written
	//		int fcount = 0; // count files
	//		for( pos = v.begin(); pos != v.end(); ++pos )
	//		{
	//			std::string str(*pos);
	//			ncount += str.size();
	//			if( ncount <= 128 )
	//				outfile << str;
	//			else
	//			{
	//				// first, close the file 
	//				outfile.flush();
	//				outfile.close();
	//				fcount++;

	//				// open new file, re-use same handler
	//				std::ostringstream oss;
	//				oss << outFileName << fcount << ".txt";
	//				outfile.open( oss.str().c_str() );

	//				// now write the string that failed the test
	//				// init counter
	//				ncount = 0;

	//				ncount += str.size();
	//				outfile << str;
	//			}

	//		}
	//	}
	//	catch( ios_base::failure ex )
	//	{
	//		std::cout << ex.what();
	//	}
	//	catch( std::runtime_error re )
	//	{
	//		std::cout << re.what();
	//	}
	//}

	return 0;
}
