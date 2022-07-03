#pragma once
#include "Entity.h"

class Player : public Entity
{
	public:
		Player();
		Player(int x, int y);
		Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY);
		~Player();

		void Update(float delta);

		SDL_Texture* GetSprite();
		SDL_Rect* GetSrcRectangle();
		SDL_Rect* GetDestRectangle();

	private:
		void Move();
		void CheckInput();
		void CheckCollisions();
};

