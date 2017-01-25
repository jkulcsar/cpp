
#include <iostream>
#include <string>

#include "item_1.hpp"
#include "GamePlayer.hpp"


//using namespace std;


int main( int argc , char** argv )
{
	int one = 1; 
	int two = 2;
	const std::string s1 = "babab";
	const std::string s2 = "deded";
	double d1 = 1.0;
	double d2 = 2.0;

	std::cout << non_std_max(one, two) << std::endl;
	
	// for std::string we don't have operator > defined, called in the template function
//	std::cout << non_std_max(d1, d2) << std::endl;
	
	GamePlayer* gp = new GamePlayer();
	GamePlayer* gp_author = new GamePlayer(authorName);
	std::cout << "Player name: " << gp_author->getName() << std::endl;

	if(gp)
		delete gp;

	if(gp_author)
		delete gp_author;

	return 0;
}