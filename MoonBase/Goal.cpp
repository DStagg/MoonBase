#include "Goal.h"

Goal::Goal(Level* lvl) : BaseEntity(lvl)
{

};

void Goal::Update(float dt)
{

};

void Goal::Draw(sf::RenderWindow* rw)
{
	DebugDrawEntity(this, rw, sf::Color::Red);
};