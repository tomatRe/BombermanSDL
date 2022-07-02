#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(int x, int y)
{
	this->x = x;
	this->y = y;

	screenRectangle.x = x;
	screenRectangle.y = y;
}

Entity::Entity(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY)
{
	this->x = x;
	this->y = y;
	this->sprite = sprite;

	screenRectangle.x = x;
	screenRectangle.y = y;
	screenRectangle.w = textSizeX;
	screenRectangle.h = textSizeY;

	textureRectangle.x = textPosX;
	textureRectangle.y = textPosY;
	textureRectangle.w = textSizeX;
	textureRectangle.h = textSizeY;
}

bool Entity::AddTexture(SDL_Texture * sprite, int w, int h, int x, int y)
{
	bool result = true;

	this->sprite = sprite;

	textureRectangle.h = h;
	textureRectangle.w = w;
	textureRectangle.x = x;
	textureRectangle.y = y;

	return result;
}

Entity::~Entity()
{}