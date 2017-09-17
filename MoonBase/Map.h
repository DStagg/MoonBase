#ifndef MAP_H
#define MAP_H

#include "Framework\Data\Grid.h"
#include "SFML\Graphics.hpp"

#define CellWidth 32
#define CellHeight 32

class Map
{
public:

	Grid& GetTiles();


private:

	Grid _Tiles;	//	For the time being, 1 = solid, 0 = not solid.
};

void DebugGenMap(Map* map, int width, int height);
void DebugDrawMap(Map* map, sf::RenderWindow* rw, sf::Color solid);

#endif