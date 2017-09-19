#ifndef BULLET_H
#define BULLET_H

#include "Framework\Entities\Entity.h"

class Bullet : public Entity
{
public:

	Bullet(Level* lvl, PairFloat pos, PairFloat vel, PairFloat size);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

private:

	float _Lifetime = 5.f;
};

#endif