#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Entities\Entity.h"
#include "Framework\Utility\Utility.h"
#include "Gun.h"
#include "Health.h"

#define ShootKey Space
#define MoveLeftKey A
#define MoveRightKey D
#define AimUpKey W
#define AimDownKey S
#define ToggleAimKey LShift
#define JumpKey Up

#define keyDown(x) sf::Keyboard::isKeyPressed(sf::Keyboard::x)

class Player : public Entity, public Health
{
public:

	Player(Level* lvl);

	void HandleInput(sf::Event e);
	void Update(float dt);
	void Draw(sf::RenderWindow* rw);
	void OnHurt(int dmg);

	Gun* GetGun();
	void SetGun(Gun* g);

private:

	Gun* _Gun = 0;
	PairFloat _GunOffset = PairFloat(15.f, 15.f);
	
};

#endif