#pragma once

#include <iostream>
#include <SDL.h>
#include "Loader.h"

class Entity
{
	public:
		Entity();
		Entity(int x, int y);
		Entity(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY);
		~Entity();

		bool AddTexture(SDL_Texture *sprite, int w, int h, int x, int y);

		SDL_Texture *sprite;
		SDL_Rect textureRectangle;
		SDL_Rect screenRectangle;

		int x;
		int y;
};

