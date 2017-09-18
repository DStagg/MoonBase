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
};

void Gun::Draw(sf::RenderWindow* rw)
{
	GetGraphic().GetSprPntr()->setPosition(floor(GetPosition()._X), floor(GetPosition()._Y));
	rw->draw(*GetGraphic().GetSprPntr());
	DebugDrawEntity(this, rw, sf::Color::Green);
};