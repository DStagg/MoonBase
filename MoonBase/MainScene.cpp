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

	_Level->GetPlayer()->SetGun(new Gun(_Level));
	_Level->GetPlayer()->GetGun()->GetSize().Set(32.f, 16.f);

	Enemy* e = new Enemy(_Level, Enemy::Type::Walker);
	e->GetPosition().Set(300.f, 200.f);
	_Level->GetEnemies().AddEnt(e);

	Goal* g = new Goal(_Level);
	g->GetPosition().Set(100.f, 100.f);
	g->GetSize().Set(50.f, 50.f);
	_Level->SetGoal(g);

	_ImgMan.LoadTextureFromFile("Player", "Player.png");
	_ImgMan.LoadTextureFromFile("Gun", "Gun.png");
	GenPlayerAnims(_ImgMan);
	_Level->GetPlayer()->GetGraphic().SetSprite(sf::Sprite(*_ImgMan.GetTexturePntr("Player")));
	_Level->GetPlayer()->GetGun()->GetGraphic().SetSprite(sf::Sprite(*_ImgMan.GetTexturePntr("Gun")));
	
	for (int i = Direction::North; i <= Direction::NorthWest; i++)
	{
		_Level->GetPlayer()->GetGraphic().AddAnimation("Player" + IntToString(i), _ImgMan.GetAnimation("Player" + IntToString(i)));
		_Level->GetPlayer()->GetGun()->GetGraphic().AddAnimation("Gun" + IntToString(i), _ImgMan.GetAnimation("Gun" + IntToString(i)));
	}

	
	DebugGenMap(&_Level->GetMap(), 20, 10);
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
		else if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
			_Level->GetPlayer()->GetPosition().Set(sf::Mouse::getPosition(*_Window).x, sf::Mouse::getPosition(*_Window).y);
		else if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Right))
		{
			int col = _Level->GetMap().CalcCol(sf::Mouse::getPosition(*_Window).x);
			int row = _Level->GetMap().CalcRow(sf::Mouse::getPosition(*_Window).y);
			if (_Level->GetMap().GetTiles().GetCell(col, row) == 0)
				_Level->GetMap().GetTiles().SetCell(col, row, 1);
			else
				_Level->GetMap().GetTiles().SetCell(col, row, 0);
		}
				
	}

	_Level->GetGoal()->Update(dt);

	if ((_Level != 0) && (_Level->GetPlayer() != 0))
		_Level->GetPlayer()->Update(dt);

	for (int i = 0; i < _Level->GetBullets().CountEnts(); i++)
		_Level->GetBullets().GetEnt(i)->Update(dt);

	for (int i = 0; i < _Level->GetEnemies().CountEnts(); i++)
		_Level->GetEnemies().GetEnt(i)->Update(dt);

	_Level->GetBullets().Cull(50);
};
void MainScene::DrawScreen()
{
	if (_Level != 0)
	{
		DebugDrawMap(&_Level->GetMap(), _Window, sf::Color::Magenta);
		if (_Level->GetPlayer() != 0)
			_Level->GetPlayer()->Draw(_Window);
		for (int i = 0; i < _Level->GetBullets().CountEnts(); i++)
			_Level->GetBullets().GetEnt(i)->Draw(_Window);
		for (int i = 0; i < _Level->GetEnemies().CountEnts(); i++)
			_Level->GetEnemies().GetEnt(i)->Draw(_Window);
		_Level->GetGoal()->Draw(_Window);

		sf::Font f;
		f.loadFromFile("Roboto-Regular.ttf");

		sf::Text t1;
		t1.setString("Player Health: " + IntToString(_Level->GetPlayer()->GetHP()) + " of " + IntToString(_Level->GetPlayer()->GetMaxHP()));
		t1.setFont(f);
		t1.setPosition(0.f, 0.f);
		_Window->draw(t1);

		sf::Text t2;
		t2.setString("Core Health: " + IntToString(_Level->GetGoal()->GetHP()) + " of " + IntToString(_Level->GetGoal()->GetMaxHP()));
		t2.setFont(f);
		t2.setPosition(0.f, 50.f);
		_Window->draw(t2);

	}

};

void GenPlayerAnims(ImageManager& img)
{
	for (int i = Direction::North; i <= Direction::NorthWest; i++)
	{
		AnimationFrame frame(i * 32.f, 0.f, 32.f, 64.f, 1.f);
		Animation anim;
		anim._Frames.push_back(frame);
		img.AddAnimation("Player" + IntToString(i), anim);

		AnimationFrame gframe(i * 32.f, 0.f, 32.f, 16.f, 1.f);
		Animation ganim;
		ganim._Frames.push_back(gframe);
		img.AddAnimation("Gun" + IntToString(i), ganim);
	}
};