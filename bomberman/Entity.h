#pragma once

#include <iostream>
#include <SDL.h>
#include "Loader.h"

class Entity
{
	public:
		Entity();
		Entity(int x, int y);
		Entity(int x, int y, SDL_Texture* sprite);
		Entity(int x, int y, SDL_Texture* sprite, int textPosX, int textPosY);
		Entity(int x, int y, int rectW, int rectH, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY);
		~Entity();

		void Update(float delta);
		bool AddTexture(SDL_Texture *sprite, int w, int h, int x, int y);
		void SetX(int x);
		void SetY(int y);

		SDL_Texture *sprite;
		SDL_Rect srcRectangle;
		SDL_Rect destRectangle;
};
