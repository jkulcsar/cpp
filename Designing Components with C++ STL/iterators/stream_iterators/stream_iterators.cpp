
#include<fstream>
#include<iostream>
#include<iterator>
#include<string>
#include "identifier.hpp"

using namespace std;



int main(int argc, char** argv)
{
	//
	// a simple demo first
	//ifstream source("stream_iterators.cpp");
	//istream_iterator<string> pos(source), end;

	//if( pos == end )
	//	cout << "File not found!" << std::endl;
	//else
	//	while( pos != end )
	//	{
	//		cout << *pos << endl;
	//		++pos;
	//	}

	//cout << endl << endl;

	std::ifstream identifiers_source("identifier.hpp");
	std::istream_iterator<Identifier> identif_InPos(identifiers_source), identif_InEnd;

	std::ofstream target("idlist");
	// setup the output iterator, targeting on the output file
	// and using a custom separator (here: newline)
	std::ostream_iterator<Identifier> identif_OutPos(target, "\n");

	if( identif_InPos == identif_InEnd )
		std::cout << "File not found!" << std::endl;
	else
		while( identif_InPos != identif_InEnd )
		{
			*identif_OutPos++ = *identif_InPos++;
			//// the line above is equivalent to:
			//Identifier temp = *identif_InPos;
			//++identif_InPos;
			//*identif_OutPos = temp;
			//++identif_OutPos;
		}
			

	return 0;
}
