#include "Bomb.h"

Bomb::Bomb(Player* p, SDL_Texture* texture) : 
	Entity(p->lastPosX-10, p->lastPosY, texture, 170, 528)
{
	ownerPlayer = p;

	srcRectangle.w = 17;
	srcRectangle.h = 17;

	destRectangle.w = 48;
	destRectangle.h = 48;

	// Load animation frames
	/*
	animationFrames = {
		{170, 528, destRectangle.w, destRectangle.h},
		{170, 528, destRectangle.w, destRectangle.h},
		{170, 528, destRectangle.w, destRectangle.h}
	};*/
}

void Bomb::Update(float delta)
{
	//Animate(delta);
	aliveTime += (delta/1000);

	if (aliveTime >= timeToExplode)
	{
		Detonate();
	}
}

void Bomb::Animate(float delta)
{
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
