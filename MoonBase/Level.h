#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"

class Level
{
public:

	Level();

	void SetPlayer(Player* player);
	Player* GetPlayer();

private:

	Player* _Player = 0;

};

#endif