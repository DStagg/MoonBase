#ifndef MainScene_H
#define MainScene_H

#include <SFML\Graphics.hpp>
#include "Framework/Scene.h"

#include "Level.h"
#include "Player.h"

class MainScene : public Scene
{
public:

	MainScene(sf::RenderWindow* rw);
	~MainScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window = 0;
	Level* _Level = 0;

};

#endif