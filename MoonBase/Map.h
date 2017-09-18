#ifndef MAP_H
#define MAP_H

#include "Framework\Data\Grid.h"
#include "SFML\Graphics.hpp"
#include "Framework\Data\Pair.h"
#include "Framework\Entities\Entity.h"

#define CellWidth 32
#define CellHeight 32
#define Gravity 50.f

class Map
{
public:

	Grid& GetTiles();

	int CalcCol(int worldx);
	int CalcRow(int worldy);

	bool ResolveTileCollision(Entity* ent, float dt);

private:

	Grid _Tiles;	//	For the time being, 1 = solid, 0 = not solid.
};

void DebugGenMap(Map* map, int width, int height);
void DebugDrawMap(Map* map, sf::RenderWindow* rw, sf::Color solid);

#endif