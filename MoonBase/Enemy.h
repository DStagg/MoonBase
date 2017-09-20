#ifndef ENEMY_H
#define ENEMY_H

#include "Framework\Entities\Entity.h"
#include "Health.h"

class Enemy : public Entity, public Health
{
public:

	enum Type
	{
		Walker,
		Seeker
	};

	Enemy(Level* lvl, int type);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);
	void OnHurt(int dmg);


private:

	int _Type;
};

#endif