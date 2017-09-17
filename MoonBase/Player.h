#ifndef PLAYER_H
#define PLAYER_H

#include "Framework\Entities\Entity.h"

class Player : public Entity
{
public:

	Player(Level* lvl);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);


private:



};

#endif