#ifndef HEALTH_H
#define HEALTH_H

class Health
{
public:

	Health(int hp, int max);

	void SetHP(int hp);
	void SetMaxHP(int max);
	int GetHP();
	int GetMaxHP();

	void Hurt(int dmg);
	virtual void OnHurt(int dmg) = 0;


private:

	int _HP, _MaxHP;
};

#endif