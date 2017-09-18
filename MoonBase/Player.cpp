#include "Player.h"
#include "Level.h"

Player::Player(Level* lvl) : Entity(lvl)
{

};

void Player::Update(float dt)
{
	float WalkSpeed = 100.f;
	float Jump = 100.f;

	GetVelocity()._Y += dt * Gravity;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		GetVelocity()._X = -WalkSpeed;
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		GetVelocity()._X = WalkSpeed;
	else
		GetVelocity()._X = 0.f;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (GetVelocity()._Y == dt * Gravity))
		GetVelocity()._Y = -Jump;

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
	bounds = GenBoundBox(this);
	//	Resolve y-coordinate movement
	if (GetVelocity()._Y != 0.f)
	{
		int forwardY = (GetVelocity()._Y < 0.f) ? bounds._Y : bounds.Bottom();
		int movedY = (int)(GetPosition()._Y + (dt * GetVelocity()._Y));
		if (GetVelocity()._Y > 0.f) movedY += (int)(GetSize()._Y - 1.f);
		int forwardRow = GetLevel()->GetMap().CalcRow(forwardY);
		int movedRow = GetLevel()->GetMap().CalcRow(movedY);
		int leftCol = GetLevel()->GetMap().CalcCol(bounds._X);
		int rightCol = GetLevel()->GetMap().CalcCol(bounds.Right());

		if (forwardRow != movedRow)
		{
			int blockedRow = -1;
			if (GetVelocity()._Y < 0.f)
			{
				for (int row = forwardRow; row >= movedRow; row--)
					for (int col = leftCol; col <= rightCol; col++)
					{
						if (blockedRow != -1)
							break;
						if (GetLevel()->GetMap().GetTiles().GetCell(col, row) == 1)
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
						if (GetLevel()->GetMap().GetTiles().GetCell(col, row) == 1)
						{
							blockedRow = row;
							break;
						}
					}

			}

			if (blockedRow == -1)
				GetPosition()._Y += dt * GetVelocity()._Y;
			else
			{
				if (GetVelocity()._Y < 0.f)
					GetPosition()._Y = (float)((blockedRow + 1) * CellHeight);
				else
					GetPosition()._Y = ((float)(blockedRow * CellHeight) - GetSize()._Y);
				GetVelocity()._Y = 0.f;
			}
		}
		else
			GetPosition()._Y += dt * GetVelocity()._Y;
	}

	_Gun->GetPosition().Set(GetPosition()._X + _GunOffset._X, GetPosition()._Y + _GunOffset._Y);
	_Gun->Update(dt);
};

void Player::Draw(sf::RenderWindow* rw)
{
	DebugDrawEntity(this, rw, sf::Color::Blue);
	if (GetGun() != 0)
		GetGun()->Draw(rw);
};

void Player::SetGun(Gun* g)
{
	_Gun = g;
};
Gun* Player::GetGun()
{
	return _Gun;
};