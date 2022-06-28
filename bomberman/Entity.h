#pragma once

#include <iostream>
#include <SDL.h>

class Entity
{
	Entity(float spawnX, float spawnY, SDL_Texture *sprite);
	~Entity();

	public:
		SDL_Texture *texture;
		float x;
		float y;
};

