#ifndef GUN_H
#define GUN_H

#include "Framework\Entities\Entity.h"

class Gun : public Entity
{
public:

	Gun(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

private:

};

#endif