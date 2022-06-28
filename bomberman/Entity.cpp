#include "Entity.h"

Entity::Entity(float spawnX, float spawnY, SDL_Texture *sprite)
{
	x = spawnX;
	y = spawnY;
	texture = sprite;
}

Entity::~Entity()
{}