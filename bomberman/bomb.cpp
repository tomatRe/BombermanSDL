#include "Bomb.h"

Bomb::Bomb(Player* p, SDL_Texture* texture) : 
	Entity(p->lastPosX, p->lastPosX, texture, 20, 20)
{
	ownerPlayer = p;
}

void Bomb::Update(float delta)
{
	aliveTime += (delta/1000);

	if (aliveTime >= timeToExplode)
	{
		Detonate();
	}
}

void Bomb::Detonate()
{
	ownerPlayer->DestroyBombReference(this);
	Bomb::~Bomb();
}

Player* Bomb::GetOwningPlayer()
{
	return nullptr;
}

Player* Bomb::SetOwningPlayer(Player*)
{
	return nullptr;
}

SDL_Texture* Bomb::GetSprite()
{
	return sprite;
}

SDL_Rect* Bomb::GetSrcRectangle()
{
	return &srcRectangle;
}

SDL_Rect* Bomb::GetDestRectangle()
{
	return &destRectangle;
}

Bomb::~Bomb()
{
}
