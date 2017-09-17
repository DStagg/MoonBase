#include "Player.h"
#include "Level.h"

Player::Player(Level* lvl) : Entity(lvl)
{

};

void Player::Update(float dt)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		GetVelocity()._X = -100.f;
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		GetVelocity()._X = 100.f;
	else
		GetVelocity()._X = 0.f;

	AABB bounds = GenBoundBox(this);
	//	Resolve x-coordinate movement
	if (GetVelocity()._X != 0.f)
	{
		int forwardX = (GetVelocity()._X < 0.f) ? bounds._X : bounds.Right();
		int movedX = (int)(GetPosition()._X + (dt * GetVelocity()._X));
		if (GetVelocity()._X > 0.f) movedX += (int)(GetSize()._X - 1.f);
		int forwardCol = GetLevel()->GetMap().CalcCol(forwardX);
		int movedCol = GetLevel()->GetMap().CalcCol(movedX);
		int topRow = GetLevel()->GetMap().CalcRow(bounds._Y);
		int botRow = GetLevel()->GetMap().CalcRow(bounds.Bottom());

		if (forwardCol != movedCol)
		{
			int blockedCol = -1;
			if (GetVelocity()._X < 0.f)
			{
				for (int col = forwardCol; col >= movedCol; col--)
					for (int row = topRow; row <= botRow; row++)
					{
						if (blockedCol != -1)
							break;
						if (GetLevel()->GetMap().GetTiles().GetCell(col, row) == 1)
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
						if (GetLevel()->GetMap().GetTiles().GetCell(col, row) == 1)
						{
							blockedCol = col;
							break;
						}
					}

			}

			if (blockedCol == -1)
				GetPosition()._X += dt * GetVelocity()._X;
			else
			{
				if (GetVelocity()._X < 0.f)
					GetPosition()._X = (float)((blockedCol + 1) * CellWidth);
				else
					GetPosition()._X = ((float)(blockedCol * CellWidth) - GetSize()._X);
				GetVelocity()._X = 0.f;
			}
		}
		else
			GetPosition()._X += dt * GetVelocity()._X;

	}
};

void Player::Draw(sf::RenderWindow* rw)
{


};