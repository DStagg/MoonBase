#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Entities\Entity.h"
#include "Framework\Utility\Utility.h"
#include "Gun.h"

#define keyDown(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)

class Player : public Entity
{
public:

	Player(Level* lvl);

	void HandleInput(sf::Event e);
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	Gun* GetGun();
	void SetGun(Gun* g);

private:

	Gun* _Gun = 0;
	PairFloat _GunOffset = PairFloat(15.f, 15.f);
	
};

#endif