#include "Entity.h"

Entity::Entity(Level* lvl)
{
	SetAlive(true);
	SetLevel(lvl);
};
Entity::~Entity()
{

};

//	Components	//
PairFloat& Entity::GetPosition()
{
	return _Position;
};
PairFloat& Entity::GetVelocity()
{
	return _Velocity;
};
PairFloat& Entity::GetSize()
{
	return _Size;
};
float& Entity::GetHeading()
{
	return _Heading;
};
int& Entity::GetDirection()
{
	return _Direction;
};
//////////////////

Graphic& Entity::GetGraphic()
{
	return _Graphic;
};

Stats& Entity::GetStats()
{
	return _Stats;
};

void Entity::SetAlive(bool b)
{
	_Alive = b;
};
bool Entity::GetAlive()
{
	return _Alive;
};

void Entity::SetLevel(Level* lvl)
{
	_Level = lvl;
};
Level* Entity::GetLevel()
{
	return _Level;
};

/////


//	BasicEnt	//

BasicEnt::BasicEnt(Level* lvl) : Entity(lvl)
{

};

void BasicEnt::Update(float dt)
{
	GetPosition()._X = GetPosition()._X + (dt * GetVelocity()._X);
	GetPosition()._Y = GetPosition()._Y + (dt * GetVelocity()._Y);
	GetGraphic().Play(dt);
	GetSize().Set((float)GetGraphic().GetCurrentFrame()._Width, (float)GetGraphic().GetCurrentFrame()._Height);
};

void BasicEnt::Draw(sf::RenderWindow* rw)
{
	GetGraphic().GetSprPntr()->setPosition(floor(GetPosition()._X) , floor(GetPosition()._Y));
	rw->draw(*GetGraphic().GetSprPntr());
};


//	SFXEnt		//

SFXEnt::SFXEnt(Level* lvl) : BasicEnt(lvl)
{

};

void SFXEnt::Update(float dt)
{
	BasicEnt::Update(dt);
	if ((GetGraphic().GetCurrentAnim()._CurrentFrame == (int)GetGraphic().GetCurrentAnim()._Frames.size() - 1) && (GetGraphic().GetCurrentAnim()._Time > GetGraphic().GetCurrentFrame()._FrameTime))
		SetAlive(false);
};

//////////

AABB GenBoundBox(Entity* ent)
{
	return AABB((int)ent->GetPosition()._X, (int)ent->GetPosition()._Y, (int)ent->GetSize()._X, (int)ent->GetSize()._Y);
};

/////

EntList::EntList()
{

};
EntList::~EntList()
{
	Cull(0);
};

void EntList::AddEnt(Entity* ent)
{
	if (ent == 0)
		return;
	if (std::find(_Entities.begin(), _Entities.end(), ent) != _Entities.end())
		return;
	_Entities.push_back(ent);
};
void EntList::DelEnt(Entity* ent)
{
	if (ent == 0)
		return;
	if (std::find(_Entities.begin(), _Entities.end(), ent) != _Entities.end())
	{
		delete ent;
		_Entities.erase(std::find(_Entities.begin(), _Entities.end(), ent));
	}
};
void EntList::Cull(int limit)
{
	if (limit < 0)
		return;

	while (CountEnts() > limit)
	{
		delete GetEnt(0);
		_Entities.erase(_Entities.begin());
	}

	for (int i = 0; i < CountEnts(); i++)
	{
		if (!GetEnt(i)->GetAlive())
		{
			delete GetEnt(i);
			_Entities.erase(_Entities.begin() + i);
			i--;
		}
	}
};

int EntList::CountEnts()
{
	return (int)_Entities.size();
};
Entity* EntList::GetEnt(int i)
{
	if (i < 0)
		i = 0;
	if (i >= CountEnts())
		i = CountEnts() - 1;

	return _Entities[i];
};

//////////////////////////////

void DebugDrawEntity(Entity* ent, sf::RenderWindow* target, sf::Color col)
{
	sf::RectangleShape rect;
	rect.setPosition(floor(ent->GetPosition()._X), floor(ent->GetPosition()._Y));
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(col);
	rect.setOutlineThickness(1.f);
	rect.setSize(sf::Vector2f(ent->GetSize()._X , ent->GetSize()._Y));
	target->draw(rect);
};