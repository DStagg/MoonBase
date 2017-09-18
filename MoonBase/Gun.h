#ifndef GUN_H
#define GUN_H

#include "Framework\Entities\Entity.h"
#include "Framework\Utility\Utility.h"

enum Aim
{
	Neutral = 0,
	Up,
	Down,
	DiagUp,
	DiagDown
};

class Gun : public Entity
{
public:

	Gun(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	int _Aim = Neutral;

private:

};

#endif