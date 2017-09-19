#include "Goal.h"

Goal::Goal(Level* lvl) : BaseEntity(lvl), Health(20, 20)
{

};

void Goal::Update(float dt)
{

};

void Goal::Draw(sf::RenderWindow* rw)
{
	DebugDrawEntity(this, rw, sf::Color::Red);
};

void Goal::OnHurt(int dmg)
{
	if (dmg > 0)
		std::cout << "Core damaged: " << dmg << std::endl;
	else if (dmg < 0)
		std::cout << "Core healed: " << dmg << std::endl;
};