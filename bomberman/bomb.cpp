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
	animationFrames = {
		{170, 528, 17, 17},
		{187, 528, 17, 17},
		{204, 528, 17, 17}
	};
}

void Bomb::Update(float delta)
{
	Animate(delta);

	//Alive time is in (s) and delta in (ms)
	aliveTime += (delta/1000);

	if (aliveTime >= timeToExplode)
	{
		Detonate();
	}
}

void Bomb::Animate(float delta)
{
	float timePerAnimation = (timeToExplode*1000) / animationFrames.size();
	animationDeltaTime += delta;

	if (animationDeltaTime >= timePerAnimation)
	{
		animationDeltaTime = animationDeltaTime-1000;
		srcRectangle = animationFrames[animationFrame];

		if (animationFrame < animationFrames.size())
			animationFrame++;
	}

	std::cout << "Delta: " << animationDeltaTime << " - " << animationFrame << "\n";
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
