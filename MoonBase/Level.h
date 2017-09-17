#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Map.h"

class Level
{
public:

	Level();

	void SetPlayer(Player* player);
	Player* GetPlayer();

	Map& GetMap();

private:

	Player* _Player = 0;
	Map _Map;
};

#endif