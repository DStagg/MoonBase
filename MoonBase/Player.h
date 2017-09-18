#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Entities\Entity.h"
#include "Framework\Utility\Utility.h"
#include "Gun.h"

class Player : public Entity
{
public:

	Player(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	Gun* GetGun();
	void SetGun(Gun* g);

private:

	Gun* _Gun = 0;
	PairFloat _GunOffset = PairFloat(15.f, 15.f);

};

#endif