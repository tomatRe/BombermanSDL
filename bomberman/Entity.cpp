#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(int x, int y)
{
	destRectangle.x = x;
	destRectangle.y = y;
	destRectangle.w = 34;
	destRectangle.h = 48;
}

Entity::Entity(int x, int y, SDL_Texture* sprite)
{
	this->sprite = sprite;

	destRectangle.x = x;
	destRectangle.y = y;
	destRectangle.w = 34;
	destRectangle.h = 48;
}

Entity::Entity(int x, int y, SDL_Texture* sprite, int textPosX, int textPosY)
{
	this->sprite = sprite;

	destRectangle.x = x;
	destRectangle.y = y;
	destRectangle.w = 34;
	destRectangle.h = 48;

	srcRectangle.x = textPosX;
	srcRectangle.y = textPosY;
	srcRectangle.w = 34;
	srcRectangle.h = 48;
}

Entity::Entity(int x, int y, int rectW, int rectH, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY)
{
	this->sprite = sprite;

	destRectangle.x = x;
	destRectangle.y = y;
	destRectangle.w = rectW;
	destRectangle.h = rectH;

	srcRectangle.x = textPosX;
	srcRectangle.y = textPosY;
	srcRectangle.w = textSizeX;
	srcRectangle.h = textSizeY;
}

void Entity::Update(float delta)
{
}

bool Entity::AddTexture(SDL_Texture * sprite, int w, int h, int x, int y)
{
	bool result = true;

	this->sprite = sprite;

	srcRectangle.h = h;
	srcRectangle.w = w;
	srcRectangle.x = x;
	srcRectangle.y = y;

	return result;
}

void Entity::SetX(int x)
{
	destRectangle.x = x;
}

void Entity::SetY(int y)
{
	destRectangle.y = y;
}

Entity::~Entity()
{}
