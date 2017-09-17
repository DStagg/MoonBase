#include "Map.h"

Grid& Map::GetTiles()
{
	return _Tiles;
};

void DebugGenMap(Map* map, int width, int height)
{
	if (width < 3) width = 3;
	if (height < 3) height = 3;

	map->GetTiles().Resize(width, height);

	for (int x = 0; x < map->GetTiles().GetWidth(); x++)
		for (int y = 0; y < map->GetTiles().GetHeight(); y++)
		{
			if ((x == 0) || (y == 0) || (x == map->GetTiles().GetWidth() - 1) || (y == map->GetTiles().GetHeight() - 1))
				map->GetTiles().SetCell(x, y, 1);
			else
				map->GetTiles().SetCell(x, y, 0);
		}

};

int Map::CalcCol(int worldx)
{
	return (worldx - (worldx % CellWidth)) / CellWidth;
};

int Map::CalcRow(int worldy)
{
	return (worldy - (worldy % CellHeight)) / CellHeight;
};

void DebugDrawMap(Map* map, sf::RenderWindow*rw, sf::Color solid)
{
	for (int x = 0; x < map->GetTiles().GetWidth(); x++)
		for (int y = 0; y < map->GetTiles().GetHeight(); y++)
			if (map->GetTiles().GetCell(x, y) == 1)
			{
				sf::RectangleShape rect;
				rect.setPosition((float)(x * CellWidth), (float)(y * CellHeight));
				rect.setSize(sf::Vector2f((float)CellWidth, (float)CellHeight));
				rect.setFillColor(solid);
				rw->draw(rect);
			}
};
