#pragma once
#include "Entity.h"

class Player : public Entity
{
	public:
		Player();
		Player(int x, int y);
		Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY);
		~Player();

		SDL_Texture* GetSprite();
		SDL_Rect* GetTextureRectangle();
		SDL_Rect* GetScreenRectangle();

		float x;
		float y;
};

