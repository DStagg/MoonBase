#include "Level.h"

Level::Level()
{

};

void Level::SetPlayer(Player* p)
{
	_Player = p;
};

Player* Level::GetPlayer()
{
	return _Player;
};

Map& Level::GetMap()
{
	return _Map;
};