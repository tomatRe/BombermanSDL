#include "Bomb.h"
#include "Blast.h"

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

	blastOriginSprite = new SDL_Rect{ 170, 528, 17, 17 };
	blastTopSprite = new SDL_Rect{ 170, 528, 17, 17 };
	blastBottomSprite = new SDL_Rect{ 170, 528, 17, 17 };
	blastLeftSprite = new SDL_Rect{ 170, 528, 17, 17 };
	blastRightSprite = new SDL_Rect{ 170, 528, 17, 17 };
}

void Bomb::Update(float delta)
{
	Animate(delta);

	//Alive time is in (s) and delta in (ms)
	aliveTime += (delta/1000);

	if (aliveTime >= timeToExplode)
	{
		if (!exploded)
		{
			Detonate();
		}

		//Update explosions
		for (size_t i = 0; i < blasts.size(); i++)
		{
			blasts[i]->Update(delta);
		}
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
	exploded = true;
	//Spawn explosions

	//Up Blast
	for (size_t i = 0; i < blastRadius; i++)
	{
		//Get spawn position
		int x = destRectangle.x;
		int y = destRectangle.y + destRectangle.h;

		Blast b = Blast(x, y, blastTopSprite);
		ownerPlayer->AddBlast(&b);
	}

	//Detach owning player
	ownerPlayer->DestroyBombReference(this);
	Bomb::~Bomb();
}

Player* Bomb::GetOwningPlayer()
{
	return ownerPlayer;
}

void Bomb::SetOwningPlayer(Player* p)
{
	this->ownerPlayer = p;
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
