#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, SDL_Texture* texture) :
	Entity(x, y, texture, srcRects[propertyNum][0], srcRects[propertyNum][1])
{
	srcRectangle.w = 17;
	srcRectangle.h = 17;

	destRectangle.w = 48;
	destRectangle.h = 48;

	mPosY = y;

	propertyNum = (std::rand() % (0 - 3));
	property[propertyNum] = true;

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
