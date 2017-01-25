
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main( int argc, char* argv[] )
{
	std::string inFileName;
	std::string outFileName;
	std::vector< std::string > v;

	//
	// read argument(s)
	if( argc <= 2 )
		std::cout << "Usage: string_files <in_filename> <out_filename>" << std::endl;
	else
	{
		inFileName = argv[1];
		outFileName = argv[2];
	}

	if( !inFileName.empty() && !outFileName.empty())
	{
		std::cout << inFileName << std::endl;
		std::cout << outFileName << std::endl;

		std::ifstream infile( inFileName.c_str() );
		std::ofstream outfile( outFileName.c_str() );
		std::string tempstr;

		// read from text file
		while ( infile >> tempstr )
			v.push_back( tempstr );

		if( !v.empty() )
		{
			//vector< string >::iterator pos;
			//for( pos = v.begin(); pos != v.end(); ++pos )
			//{
			//	std::string str(*pos);
			//	outfile << hex << str;
			//}
			//
			// print out the contents of the vector
			vector< string >::iterator pos;
			int ncount = 0;	// count individual bytes to be written
			int fcount = 0; // count files
			for( pos = v.begin(); pos != v.end(); ++pos )
			{
				std::string str(*pos);
				ncount += str.size();
				if( ncount <= 128 )
					outfile << str;
				else
				{
					// first, close the file 
					outfile.flush();
					outfile.close();
					fcount++;

					// open new file, re-use same handler
					std::ostringstream oss;
					oss << outFileName << fcount << ".txt";
					outfile.open( oss.str().c_str() );

					// now write the string that failed the test
					// init counter
					ncount = 0;

					ncount += str.size();
					outfile << str;
				}

			}
		}
	}

	return 0;
}