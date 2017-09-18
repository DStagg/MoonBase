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
	if (keyDown(A) && !keyDown(D))
	{
		GetVelocity()._X = -WalkSpeed;
		GetDirection() = Direction::West;
		GetGun()->GetDirection() = Direction::West;
	}
	else if (keyDown(D) && !keyDown(A))
	{
		GetVelocity()._X = WalkSpeed;
		GetDirection() = Direction::East;
		GetGun()->GetDirection() = Direction::East;
	}
	else
		GetVelocity()._X = 0.f;

	if (keyDown(W) && (GetLevel()->GetMap().GetTileFromWorld(GetPosition()._X + (GetSize()._X / 2.f),GetPosition()._Y + GetSize()._Y) == 1))
		GetVelocity()._Y = -Jump;
	
	//	Update physics
	GetVelocity()._Y += dt * Gravity;
	GetLevel()->GetMap().ResolveTileCollision(this, dt);

	if ((GetGun()->_Aim == Aim::Up) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		GetGun()->_Aim = Aim::Neutral;
	else if ((GetGun()->_Aim == Aim::Down) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		GetGun()->_Aim = Aim::Neutral;
	else if (GetGun()->_Aim == Aim::Neutral)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			GetGun()->_Aim = Aim::DiagUp;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			GetGun()->_Aim = Aim::Up;
	}
	else if (GetGun()->_Aim == Aim::DiagUp)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			GetGun()->_Aim = Aim::Neutral;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			GetGun()->_Aim = Aim::DiagDown;
	}
	else if (GetGun()->_Aim == Aim::DiagDown)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			GetGun()->_Aim = Aim::Neutral;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			GetGun()->_Aim = Aim::DiagUp;
	}

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

	DebugDrawEntity(this, rw, sf::Color::Blue);
};

void Player::SetGun(Gun* g)
{
	_Gun = g;
};
Gun* Player::GetGun()
{
	return _Gun;
};