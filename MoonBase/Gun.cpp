#include "Gun.h"
#include "Level.h"

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
		PairFloat traj = CalcTrajectory();
		GetLevel()->GetBullets().AddEnt(new Bullet(GetLevel(), CalcMuzzle(), PairFloat(traj._X * 100.f, traj._Y * 100.f) , PairFloat(25.f, 25.f)));
		return true;
	}
	return false;
};

PairFloat Gun::CalcMuzzle()
{
	PairFloat traj = CalcTrajectory();

	return PairFloat( GetPosition()._X + (GetSize()._X * traj._X) , GetPosition()._Y + (GetSize()._X * traj._Y));
};

PairFloat Gun::CalcTrajectory()
{
	if (_Aim == Aim::Up)
		return PairFloat(0.f, -1.f);
	else if (_Aim == Aim::DiagUp)
		return (GetDirection() == Direction::West) ? PairFloat(sin(DegreeToRad(225.f)), cos(DegreeToRad(225.f))) : PairFloat(sin(DegreeToRad(135.f)), cos(DegreeToRad(135.f)));
	else if (_Aim == Aim::Neutral)
		return (GetDirection() == Direction::West) ? PairFloat(-1.f, 0.f) : PairFloat(1.f, 0.f);
	else if (_Aim == Aim::DiagDown)
		return (GetDirection() == Direction::West) ? PairFloat(sin(DegreeToRad(315.f)), cos(DegreeToRad(315.f))) : PairFloat(sin(DegreeToRad(45.f)), cos(DegreeToRad(45.f)));
	else if (_Aim == Aim::Down)
		return PairFloat(0.f, 1.f);

	return PairFloat(0.f, 0.f);
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