#include "Gun.h"

Gun::Gun(Level* lvl) : Entity(lvl)
{

};

void Gun::Update(float dt)
{
	if (_Aim == Aim::Up)
		GetGraphic().Swap("Gun0");
	else if (_Aim == Aim::DiagUp)
		GetGraphic().Swap("Gun1");
	else if (_Aim == Aim::Neutral)
		GetGraphic().Swap("Gun2");
	else if (_Aim == Aim::DiagDown)
		GetGraphic().Swap("Gun3");
	else if (_Aim == Aim::Down)
		GetGraphic().Swap("Gun4");

	GetGraphic().Play(dt);
	
	_ShootTimer += dt;
};

bool Gun::Shoot()
{
	if (_ShootTimer >= _ShootDelay)
	{
		_ShootTimer = 0.f;
		//	Shoot
		return true;
	}
	return false;
};

void Gun::Draw(sf::RenderWindow* rw)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(32.f, 16.f));
	rect.setOrigin(1.f, 8.f);
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(floor(GetPosition()._X), floor(GetPosition()._Y));
	
	if (_Aim == Aim::Up)
		rect.setRotation(270.f);
	else if (_Aim == Aim::DiagUp)
		rect.setRotation((GetDirection() == Direction::East) ? -45.f : 225.f);
	else if (_Aim == Aim::Neutral)
		rect.setRotation((GetDirection() == Direction::East) ? 0.f : 180.f);
	else if (_Aim == Aim::DiagDown)
		rect.setRotation((GetDirection() == Direction::East) ? 45.f : 135.f);
	else if (_Aim == Aim::Down)
		rect.setRotation(90.f);
	rw->draw(rect);

	//GetGraphic().GetSprPntr()->setPosition(floor(GetPosition()._X), floor(GetPosition()._Y));
	//rw->draw(*GetGraphic().GetSprPntr());
	//DebugDrawEntity(this, rw, sf::Color::Green);
};

std::string Gun::CalcAnim()
{
	if (_Aim == Aim::Up)
		return (GetDirection() == Direction::West) ? "LUp" : "RUp";
	else if (_Aim == Aim::DiagUp)
		return (GetDirection() == Direction::West) ? "LDiagUp" : "RDiagUp";
	else if (_Aim == Aim::Neutral)
		return (GetDirection() == Direction::West) ? "LNeutral" : "RNeutral";
	else if (_Aim == Aim::DiagDown)
		return (GetDirection() == Direction::West) ? "LDiagDown" : "RDiagDown";
	else if (_Aim == Aim::Down)
		return (GetDirection() == Direction::West) ? "LDown" : "RDown";

	return "Default";
};

int& Gun::GetAim()
{
	return _Aim;
};