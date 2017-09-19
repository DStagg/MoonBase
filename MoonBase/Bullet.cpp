#include "Bullet.h"
#include "Level.h"

Bullet::Bullet(Level* lvl, PairFloat pos, PairFloat vel, PairFloat size) : Entity(lvl)
{
	GetPosition() = pos;
	GetSize() = size;
	GetVelocity() = vel;
};

void Bullet::Update(float dt)
{
	if (GetLevel()->GetMap().ResolveTileCollision(this, dt))
		Alive() = false;

	_Lifetime -= dt;
	if (_Lifetime <= 0.f)
		Alive() = false;
};

void Bullet::Draw(sf::RenderWindow* rw)
{
	if ( Alive() ) DebugDrawEntity(this, rw, sf::Color::White);
	else DebugDrawEntity(this, rw, sf::Color::Red);
};