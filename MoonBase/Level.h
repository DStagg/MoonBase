#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Map.h"
#include "Goal.h"
#include "Enemy.h"

class Level
{
public:

	Level();

	void SetPlayer(Player* player);
	Player* GetPlayer();
	Map& GetMap();
	EntList& GetBullets();
	EntList& GetEnemies();
	Goal* GetGoal();
	void SetGoal(Goal* goal);

private:

	Player* _Player = 0;
	Map _Map;
	EntList _Bullets;
	EntList _Enemies;
	Goal* _Goal = 0;
};

#endif