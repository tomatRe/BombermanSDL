#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, SDL_Texture* texture) :
	Entity(x, y, texture)
{
	propertyNum = (std::rand() % (0 - 3));
	property[propertyNum] = true;

	srcRects sprites;

	switch (propertyNum)
	{
		case 0: srcRectangle = sprites.blastUpgrade; break;
		case 1: srcRectangle = sprites.speedUpgrade; break;
		case 2: srcRectangle = sprites.ammoUpgrade; break;
	}

	destRectangle.w = 32;
	destRectangle.h = 32;

	//Accounting possition for the size reduction
	destRectangle.x += 8;
	destRectangle.y += 8;

	mPosY = y;

	std::cout << "PowerUP created at: " << x << ", " << y << "\n";
}

void PowerUp::Update(float delta)
{
	//Alive time is in (s) and delta in (ms)
	aliveTime += (delta / 1000);

	mVelY = std::sin(mPosY);

	//Move the powerup up or down
	mPosY = mVelY * delta;

	//Apply movement
	//Entity::SetY((int)mPosY);
}

int PowerUp::GetProperty()
{
	return propertyNum;
}

float PowerUp::GetAliveTime()
{
	return aliveTime;
}

float PowerUp::GetMaxAliveTime()
{
	return maxAliveTime;
}

void PowerUp::SetProperty(std::vector<bool> property)
{
	this->property = property;
}

PowerUp::~PowerUp()
{
}
