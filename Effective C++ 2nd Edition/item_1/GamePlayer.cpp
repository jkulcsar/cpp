#include "GamePlayer.hpp"

//const int GamePlayer::NUM_TURNS;	// mandatory definition
	

GamePlayer::GamePlayer(void)
{
}

GamePlayer::GamePlayer(const char* name) : _name(name)
{
}

const char* GamePlayer::getName() const {
	return _name;
}

GamePlayer::~GamePlayer(void)
{
}
