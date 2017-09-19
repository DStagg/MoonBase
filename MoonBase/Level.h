#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Map.h"
#include "Goal.h"

class Level
{
public:

	Level();

	void SetPlayer(Player* player);
	Player* GetPlayer();
	Map& GetMap();
	EntList& GetBullets();
	Goal* GetGoal();
	void SetGoal(Goal* goal);

private:

	Player* _Player = 0;
	Map _Map;
	EntList _Bullets;
	Goal* _Goal = 0;
};

#endif