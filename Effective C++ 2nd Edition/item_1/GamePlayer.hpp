#ifndef __GAMEPLAYER_HPP
#define __GAMEPLAYER_HPP

class GamePlayer
{
private:
	
	const char* _name;
	///
	/// this is only a declaration for the NUM_TUNS constant
	/// it still needs to be defined in the implementation file
	static const int NUM_TURNS = 5; // declaration of constant
	int scores[NUM_TURNS]; // use of constant

public:
	GamePlayer(void);
	GamePlayer(const char*);
	~GamePlayer(void);

	const char* getName() const;
};

// NOTE:
// contrary to the note in the book, with recent C++ standards and compilers,
// this mandatory definition is not required anymore; is regarded by the
// compiler as re-definition
//
//const int GamePlayer::NUM_TURNS;	// mandatory definition

#endif