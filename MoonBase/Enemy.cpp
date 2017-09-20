#include "Enemy.h"
#include "Level.h"

Enemy::Enemy(Level* lvl, int type) : Entity(lvl), Health(10, 10)
{
	GetSize().Set(50.f, 50.f);
	_Type = type;
};

void Enemy::Update(float dt)
{
	GetVelocity()._Y += dt * Gravity;

	if (GetVelocity()._X == 0.f)
		GetVelocity()._X = -100.f;
	float vel = GetVelocity()._X;
	if (GetLevel()->GetMap().ResolveTileCollision(this, dt))
		GetVelocity()._X = -vel;
};

void Enemy::Draw(sf::RenderWindow* rw)
{
	DebugDrawEntity(this, rw, sf::Color::Magenta);

};

void Enemy::OnHurt(int dmg)
{


};