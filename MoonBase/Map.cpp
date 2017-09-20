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

int Map::GetTileFromWorld(float x, float y)
{
	return GetTiles().GetCell(CalcCol(x), CalcRow(y));
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

bool Map::ResolveTileCollision(Entity* ent, float dt)
{
	if (ResolveTileCollisionX(ent, dt))
	{
		ResolveTileCollisionY(ent, dt);
		return true;
	}
	return ResolveTileCollisionY(ent, dt);
};

bool Map::ResolveTileCollisionX(Entity* ent, float dt)
{
	bool result = false;
	AABB bounds = GenBoundBox(ent);
	//	Resolve x-coordinate movement
	if (ent->GetVelocity()._X != 0.f)
	{
		int forwardX = (ent->GetVelocity()._X < 0.f) ? bounds._X : bounds.Right();
		int movedX = (int)(ent->GetPosition()._X + (dt * ent->GetVelocity()._X));
		if (ent->GetVelocity()._X > 0.f) movedX += (int)(ent->GetSize()._X - 1.f);
		int forwardCol = CalcCol(forwardX);
		int movedCol = CalcCol(movedX);
		int topRow = CalcRow(bounds._Y);
		int botRow = CalcRow(bounds.Bottom());

		if (forwardCol != movedCol)
		{
			int blockedCol = -1;
			if (ent->GetVelocity()._X < 0.f)
			{
				for (int col = forwardCol; col >= movedCol; col--)
					for (int row = topRow; row <= botRow; row++)
					{
						if (blockedCol != -1)
							break;
						if (GetTiles().GetCell(col, row) == 1)
						{
							blockedCol = col;
							break;
						}
					}
			}
			else
			{
				for (int col = forwardCol; col <= movedCol; col++)
					for (int row = topRow; row <= botRow; row++)
					{
						if (blockedCol != -1)
							break;
						if (GetTiles().GetCell(col, row) == 1)
						{
							blockedCol = col;
							break;
						}
					}

			}

			if (blockedCol == -1)
				ent->GetPosition()._X += dt * ent->GetVelocity()._X;
			else
			{
				if (ent->GetVelocity()._X < 0.f)
					ent->GetPosition()._X = (float)((blockedCol + 1) * CellWidth);
				else
					ent->GetPosition()._X = ((float)(blockedCol * CellWidth) - ent->GetSize()._X);
				ent->GetVelocity()._X = 0.f;
				result = true;
			}
		}
		else
			ent->GetPosition()._X += dt * ent->GetVelocity()._X;
	}
	return result;
};
bool Map::ResolveTileCollisionY(Entity* ent, float dt)
{
	bool result = false;
	AABB bounds = GenBoundBox(ent);
	//	Resolve y-coordinate movement
	if (ent->GetVelocity()._Y != 0.f)
	{
		int forwardY = (ent->GetVelocity()._Y < 0.f) ? bounds._Y : bounds.Bottom();
		int movedY = (int)(ent->GetPosition()._Y + (dt * ent->GetVelocity()._Y));
		if (ent->GetVelocity()._Y > 0.f) movedY += (int)(ent->GetSize()._Y - 1.f);
		int forwardRow = CalcRow(forwardY);
		int movedRow = CalcRow(movedY);
		int leftCol = CalcCol(bounds._X);
		int rightCol = CalcCol(bounds.Right());

		if (forwardRow != movedRow)
		{
			int blockedRow = -1;
			if (ent->GetVelocity()._Y < 0.f)
			{
				for (int row = forwardRow; row >= movedRow; row--)
					for (int col = leftCol; col <= rightCol; col++)
					{
						if (blockedRow != -1)
							break;
						if (GetTiles().GetCell(col, row) == 1)
						{
							blockedRow = row;
							break;
						}
					}
			}
			else
			{
				for (int row = forwardRow; row <= movedRow; row++)
					for (int col = leftCol; col <= rightCol; col++)
					{
						if (blockedRow != -1)
							break;
						if (GetTiles().GetCell(col, row) == 1)
						{
							blockedRow = row;
							break;
						}
					}

			}

			if (blockedRow == -1)
				ent->GetPosition()._Y += dt * ent->GetVelocity()._Y;
			else
			{
				if (ent->GetVelocity()._Y < 0.f)
					ent->GetPosition()._Y = (float)((blockedRow + 1) * CellHeight);
				else
					ent->GetPosition()._Y = ((float)(blockedRow * CellHeight) - ent->GetSize()._Y);
				ent->GetVelocity()._Y = 0.f;
				result = true;
			}
		}
		else
			ent->GetPosition()._Y += dt * ent->GetVelocity()._Y;
	}
	return result;
};