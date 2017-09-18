#include "Gun.h"

Gun::Gun(Level* lvl) : Entity(lvl)
{

};

void Gun::Update(float dt)
{



};

void Gun::Draw(sf::RenderWindow* rw)
{
	DebugDrawEntity(this, rw, sf::Color::Green);

};