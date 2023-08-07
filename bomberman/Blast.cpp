#include "Blast.h"

Blast::Blast()
{
}

Blast::Blast(int x, int y, SDL_Rect* sprite) :
	Entity(x, y)
{
	this->sprite = sprite;

	srcRectangle.x = sprite->x;
	srcRectangle.y = sprite->y;
	srcRectangle.w = sprite->w;
	srcRectangle.h = sprite->h;

	destRectangle.x = x;
	destRectangle.y = y;
	destRectangle.w = 48;
	destRectangle.h = 48;

	std::cout << "Created blast at: " << x << ", " << y << "\n";
}

void Blast::Update(float delta)
{
	Animate(delta);

	//Alive time is in (s) and delta in (ms)
	aliveTime += (delta / 1000);

	if (aliveTime >= timeToDisapear)
	{
		//Detach owning player
		ownerPlayer->DestroyBlastReference(this);
	}
}

void Blast::Animate(float delta)
{
	float timePerAnimation = (timeToDisapear * 1000) / animationSet.size();
	animationDeltaTime += delta;

	if (animationDeltaTime >= timePerAnimation)
	{
		animationDeltaTime = 0;
		srcRectangle = *animationSet[animationFrame];

		if (animationFrame < animationSet.size())
			animationFrame++;
	}
}

SDL_Rect* Blast::GetSrcRectangle()
{
	return &srcRectangle;
}

SDL_Rect* Blast::GetDestRectangle()
{
	return &destRectangle;
}

void Blast::SetOwnerPlayer(Player* p)
{
	this->ownerPlayer = p;
}

void Blast::SetAnimation(std::vector<SDL_Rect*> animationSet)
{
	this->animationSet = animationSet;
	srcRectangle = *animationSet[animationFrame];
}

Blast::~Blast()
{
	std::cout << "Blast destroyed" << "\n";
}