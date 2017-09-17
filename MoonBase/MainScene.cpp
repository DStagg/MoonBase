#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	_Level = new Level();
	_Level->SetPlayer(new Player(_Level));
	_Level->GetPlayer()->GetSize().Set(32.f, 64.f);
	_Level->GetPlayer()->GetPosition().Set(100.f, 200.f);
};
void MainScene::End()
{
	
};
void MainScene::Pause()
{

};
void MainScene::Resume()
{

};
void MainScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			SetRunning(false);
				
	}

	if ((_Level != 0) && (_Level->GetPlayer() != 0))
		_Level->GetPlayer()->Update(dt);
};
void MainScene::DrawScreen()
{
	if ((_Level != 0) && (_Level->GetPlayer() != 0))
		DebugDrawEntity(_Level->GetPlayer(), _Window, sf::Color::Blue);
};
