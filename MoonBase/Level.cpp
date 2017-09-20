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

EntList& Level::GetBullets()
{
	return _Bullets;
};

EntList& Level::GetEnemies()
{
	return _Enemies;
};

Goal* Level::GetGoal()
{
	return _Goal;
};
void Level::SetGoal(Goal* g)
{
	_Goal = g;
};