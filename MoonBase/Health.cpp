#include "Health.h"

Health::Health(int hp, int max)
{
	_HP = hp;
	_MaxHP = max;
};

void Health::Hurt(int dmg)
{
	_HP = _HP - dmg;
	OnHurt(dmg);
};

void Health::SetHP(int hp)
{
	_HP = hp;
};
void Health::SetMaxHP(int max)
{
	_MaxHP = max;
};
int Health::GetHP()
{
	return _HP;
};
int Health::GetMaxHP()
{
	return _MaxHP;
};