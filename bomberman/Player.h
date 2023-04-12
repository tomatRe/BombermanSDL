#pragma once
#include "Entity.h"
#include <vector>

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

		void Move(float delta);
		void HandleEvents(SDL_Event& e);
		void CheckCollisions();

		//Constants
		const int playerW = 17;
		const int playerH = 24;

		//Movement
		const float moveSpeed = 0.05f;
		float mPosX, mPosY;
		float mVelX, mVelY;

		//Screen boundaries
		SDL_DisplayMode DM;

	private:
		void AnimatePlayer(float delta);

		int animationFrame = 0; // 3 frames per animation
		int playerDirection = 1; //0=Up, 1=Down... (same order as below)

		std::vector<SDL_Rect> upSpriteFrames;
		std::vector<SDL_Rect> downSpriteFrames;
		std::vector<SDL_Rect> leftSpriteFrames;
		std::vector<SDL_Rect> rightSpriteFrames;

		float animationDeltaTime = 1; // Current frame duration

		// Constants
		const float timePerAnimation = 1000.f; // 1 second per animation
};

