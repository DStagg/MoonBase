#include "Player.h"
#include "Level.h"

Player::Player(Level* lvl) : Entity(lvl)
{
	GetDirection() = Direction::East;
};

void Player::HandleInput(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Space:
			// Shoot
			break;
		default:
			break;
		};
	}
	else if (e.type == sf::Event::KeyReleased)
	{

	}
};

void Player::Update(float dt)
{
	//	Set variables
	float WalkSpeed = 100.f;
	float Jump = 100.f;

	//	Handle input
	if (keyDown(MoveLeftKey) && !keyDown(MoveRightKey))
	{
		GetVelocity()._X = -WalkSpeed;
		GetDirection() = Direction::West;
		GetGun()->GetDirection() = Direction::West;
	}
	else if (keyDown(MoveRightKey) && !keyDown(MoveLeftKey))
	{
		GetVelocity()._X = WalkSpeed;
		GetDirection() = Direction::East;
		GetGun()->GetDirection() = Direction::East;
	}
	else
		GetVelocity()._X = 0.f;

	if (keyDown(JumpKey) && (GetLevel()->GetMap().GetTileFromWorld(GetPosition()._X + (GetSize()._X / 2.f),GetPosition()._Y + GetSize()._Y) == 1))
		GetVelocity()._Y = -Jump;
	
	if ((GetGun()->GetAim() == Gun::Aim::Up) && (!keyDown(AimUpKey)))
		GetGun()->GetAim() = Gun::Aim::Neutral;
	else if ((GetGun()->GetAim() == Gun::Aim::Down) && (!keyDown(AimDownKey)))
		GetGun()->GetAim() = Gun::Aim::Neutral;
	else if (GetGun()->GetAim() == Gun::Aim::Neutral)
	{
		if (keyDown(ToggleAimKey))
			GetGun()->GetAim() = Gun::Aim::DiagUp;
		else if (keyDown(AimUpKey))
			GetGun()->GetAim() = Gun::Aim::Up;
	}
	else if (GetGun()->GetAim() == Gun::Aim::DiagUp)
	{
		if (!keyDown(ToggleAimKey))
			GetGun()->GetAim() = Gun::Aim::Neutral;
		else if (keyDown(AimDownKey))
			GetGun()->GetAim() = Gun::Aim::DiagDown;
	}
	else if (GetGun()->GetAim() == Gun::Aim::DiagDown)
	{
		if (!keyDown(ToggleAimKey))
			GetGun()->GetAim() = Gun::Aim::Neutral;
		else if (keyDown(AimUpKey))
			GetGun()->GetAim() = Gun::Aim::DiagUp;
	}

	if (keyDown(ShootKey))
		GetGun()->Shoot();

	//	Update physics
	GetVelocity()._Y += dt * Gravity;
	GetLevel()->GetMap().ResolveTileCollision(this, dt);

	//	Update Components
	_Gun->GetPosition().Set(GetPosition()._X + _GunOffset._X, GetPosition()._Y + _GunOffset._Y);
	_Gun->Update(dt);
	GetGraphic().Swap("Player" + IntToString(GetDirection()));
	GetGraphic().Play(dt);
};

void Player::Draw(sf::RenderWindow* rw)
{
	GetGraphic().GetSprPntr()->setPosition(floor(GetPosition()._X), floor(GetPosition()._Y));
	if (GetDirection() == Direction::East)
	{
		rw->draw(*GetGraphic().GetSprPntr());
		if (GetGun() != 0) GetGun()->Draw(rw);
	}
	else
	{
		if (GetGun() != 0) GetGun()->Draw(rw);
		rw->draw(*GetGraphic().GetSprPntr());
	}

	//DebugDrawEntity(this, rw, sf::Color::Blue);
};

void Player::SetGun(Gun* g)
{
	_Gun = g;
};
Gun* Player::GetGun()
{
	return _Gun;
};