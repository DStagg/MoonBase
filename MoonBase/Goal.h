#ifndef GOAL_H
#define GOAL_H

#include "Framework\Entities\Entity.h"

class Goal : public BaseEntity
{
public:

	Goal(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

private:


};

#endif