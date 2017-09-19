#ifndef GUN_H
#define GUN_H

#include "Framework\Entities\Entity.h"
#include "Framework\Utility\Utility.h"

class Gun : public Entity
{
public:

	Gun(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

	bool Shoot();

	std::string CalcAnim();

	int& GetAim();
	enum Aim
	{
		Neutral = 0,
		Up,
		Down,
		DiagUp,
		DiagDown
	};

private:

	int _Aim = Neutral;

	float _ShootTimer = 0.f;
	float _ShootDelay = 0.2f;

};

#endif