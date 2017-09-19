#ifndef GOAL_H
#define GOAL_H

#include "Framework\Entities\Entity.h"
#include "Health.h"
#include <iostream>

class Goal : public BaseEntity , public Health
{
public:

	Goal(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	void OnHurt(int dmg);

private:


};

#endif