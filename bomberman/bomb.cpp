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
	Blast* b;
	Blast::blastDirection dirSprite;
	const int offset = 4;

	//Center blast
	b = new Blast(destRectangle.x, destRectangle.y, dirSprite.center[0]);
	b->SetOwnerPlayer(ownerPlayer);
	b->SetAnimation(dirSprite.center);
	ownerPlayer->AddBlast(b);

	//Up Blast
	for (size_t i = 1; i < blastRadius+1; i++)
	{
		//Get spawn position
		int x = destRectangle.x;
		int y = destRectangle.y - destRectangle.h*i + (i * offset);

		b = new Blast(x, y, dirSprite.up[0]);
		b->SetOwnerPlayer(ownerPlayer);
		SDL_Rect rect = *b->GetDestRectangle();

		if (i == blastRadius)
			b->SetAnimation(dirSprite.up);
		else
			b->SetAnimation(dirSprite.verticalBody);

		if (IsOverlapingWithWorld(rect))
		{
			b->SetAnimation(dirSprite.invisible);
			
			// break the loop
			i = blastRadius + 1;
		}

		ownerPlayer->AddBlast(b);
	}

	//Down Blast
	for (size_t i = 1; i < blastRadius+1; i++)
	{
		//Get spawn position
		int x = destRectangle.x;
		int y = destRectangle.y + destRectangle.h*i - (i * offset);

		b = new Blast(x, y, dirSprite.down[0]);
		b->SetOwnerPlayer(ownerPlayer);

		SDL_Rect rect = *b->GetDestRectangle();

		if (i == blastRadius)
			b->SetAnimation(dirSprite.down);
		else
			b->SetAnimation(dirSprite.verticalBody);

		if (IsOverlapingWithWorld(rect))
		{
			b->SetAnimation(dirSprite.invisible);

			// break the loop
			i = blastRadius + 1;
		}

		ownerPlayer->AddBlast(b);
	}

	//Left Blast
	for (size_t i = 1; i < blastRadius + 1; i++)
	{
		//Get spawn position
		int x = destRectangle.x - destRectangle.w*i + (i * offset);
		int y = destRectangle.y;

		b = new Blast(x, y, dirSprite.left[0]);
		b->SetOwnerPlayer(ownerPlayer);

		SDL_Rect rect = *b->GetDestRectangle();

		if (i == blastRadius)
			b->SetAnimation(dirSprite.left);
		else
			b->SetAnimation(dirSprite.horizontalBody);

		if (IsOverlapingWithWorld(rect))
		{
			b->SetAnimation(dirSprite.invisible);

			// break the loop
			i = blastRadius + 1;
		}

		ownerPlayer->AddBlast(b);
	}

	//Right Blast
	for (size_t i = 1; i < blastRadius + 1; i++)
	{
		//Get spawn position
		int x = destRectangle.x + destRectangle.w*i - (i * offset);
		int y = destRectangle.y;

		b = new Blast(x, y, dirSprite.right[0]);
		b->SetOwnerPlayer(ownerPlayer);

		SDL_Rect rect = *b->GetDestRectangle();

		if (i == blastRadius)
			b->SetAnimation(dirSprite.right);
		else
			b->SetAnimation(dirSprite.horizontalBody);

		if (IsOverlapingWithWorld(rect))
		{
			b->SetAnimation(dirSprite.invisible);

			// break the loop
			i = blastRadius + 1;
		}

		ownerPlayer->AddBlast(b);
	}

	//Detach owning player
	ownerPlayer->DestroyBombReference(this);
}

bool Bomb::IsOverlapingWithWorld(SDL_Rect rect)
{
	//Blasts to map collisions
	for (size_t x = 0; x < mapSizex; x++)
	{
		for (size_t y = 0; y < mapSizey; y++)
		{
			//Created a small reduction in the blast collision so it wont break unexpected walls
			SDL_Rect reducedCollision = {
				rect.x + 10, rect.y + 10, rect.h - 10, rect.w - 10
			};

			if (IsOverlaping(mapRect[y][x], reducedCollision))
			{
				return true;
			}
		}
	}

	return false;
}

bool Bomb::IsOverlaping(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		(rect1.h / 2) + rect1.y > rect2.y)
	{
		// Collision detected!
		return true;
	}

	return false;
}

void Bomb::UpdateGrid()
{
	this->mapTiles = map->GetMapTiles();
	this->mapRect = map->GetMapRects();
	this->mapSizex = map->GetMapSizeX();
	this->mapSizey = map->GetMapSizeY();
}

//Getters
Player* Bomb::GetOwningPlayer()
{
	return ownerPlayer;
}

float Bomb::GetAliveTime()
{
	return aliveTime;
}

SDL_Rect* Bomb::GetSrcRectangle()
{
	return &srcRectangle;
}

SDL_Rect* Bomb::GetDestRectangle()
{
	return &destRectangle;
}

void Bomb::SetBlastRadius(int newRadius)
{
	this->blastRadius = newRadius;
}

//Setters
void Bomb::SetOwningPlayer(Player* p)
{
	this->ownerPlayer = p;
}

void Bomb::SetMapReference(Map* map)
{
	this->map = map;
	UpdateGrid();
}

Bomb::~Bomb()
{
}
