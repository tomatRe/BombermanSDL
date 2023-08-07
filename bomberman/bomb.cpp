#include "Bomb.h"
#include "Blast.h"

Bomb::Bomb()
{
}

//Constructor
Bomb::Bomb(Player* p, SDL_Texture* texture) : 
	Entity(p->lastPosX-10, p->lastPosY, texture, 170, 528)
{
	ownerPlayer = p;

	srcRectangle.w = 17;
	srcRectangle.h = 17;

	destRectangle.w = 48;
	destRectangle.h = 48;

	std::cout << "Created bomb at: " << p->lastPosX - 10 << ", " << p->lastPosY << "\n";
}

//Tick functions
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
}


void Bomb::Detonate()
{
	exploded = true;
	//Spawn explosions
	Blast* b;

	//Center blast
	b = new Blast(destRectangle.x, destRectangle.y, blastOriginSprite);
	b->SetOwnerPlayer(ownerPlayer);
	ownerPlayer->AddBlast(b);

	//Up Blast
	for (size_t i = 1; i < blastRadius+1; i++)
	{
		//Get spawn position
		int x = destRectangle.x;
		int y = destRectangle.y - destRectangle.h*i;

		b = new Blast(x, y, blastTopSprite);
		b->SetOwnerPlayer(ownerPlayer);
		ownerPlayer->AddBlast(b);
	}

	//Up Down
	for (size_t i = 1; i < blastRadius+1; i++)
	{
		//Get spawn position
		int x = destRectangle.x;
		int y = destRectangle.y + destRectangle.h*i;

		b = new Blast(x, y, blastTopSprite);
		b->SetOwnerPlayer(ownerPlayer);
		ownerPlayer->AddBlast(b);
	}

	//Left Blast
	for (size_t i = 1; i < blastRadius + 1; i++)
	{
		//Get spawn position
		int x = destRectangle.x - destRectangle.w*i;
		int y = destRectangle.y;

		b = new Blast(x, y, blastTopSprite);
		b->SetOwnerPlayer(ownerPlayer);
		ownerPlayer->AddBlast(b);
	}

	//Right Blast
	for (size_t i = 1; i < blastRadius + 1; i++)
	{
		//Get spawn position
		int x = destRectangle.x + destRectangle.w*i;
		int y = destRectangle.y;

		b = new Blast(x, y, blastTopSprite);
		b->SetOwnerPlayer(ownerPlayer);
		ownerPlayer->AddBlast(b);
	}

	//Detach owning player
	ownerPlayer->DestroyBombReference(this);
}

//Getters
Player* Bomb::GetOwningPlayer()
{
	return ownerPlayer;
}

SDL_Rect* Bomb::GetSrcRectangle()
{
	return &srcRectangle;
}

SDL_Rect* Bomb::GetDestRectangle()
{
	return &destRectangle;
}

//Setters
void Bomb::SetOwningPlayer(Player* p)
{
	this->ownerPlayer = p;
}

Bomb::~Bomb()
{
	std::cout << "Bomb destroyed" << "\n";
}
