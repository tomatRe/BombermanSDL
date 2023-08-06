#pragma once
#include "Entity.h"
#include <vector>

class Blast;
class Bomb;
class Game;

class Player : public Entity
{
	public:
		Player();
		Player(int x, int y);
		Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY);
		~Player();

		void Update(float);
		void Move(float);
		void HandleEvents(SDL_Event&);
		void CheckCollisions();
		void SetBombTexture(SDL_Texture*);
		void SpawnBomb();
		void UpdateBombs(float);
		void SetGameReference(Game*);
		void DestroyBombReference(Bomb*);
		void UpdateBlasts(float);
		void AddBlast(Blast*);
		void SetBlasts(std::vector<Blast*>);

		std::vector<Bomb> GetBombs();
		SDL_Texture* GetSprite();
		SDL_Rect* GetSrcRectangle();
		SDL_Rect* GetDestRectangle();

		//Constants
		const int playerW = 17;
		const int playerH = 24;

		//Movement
		const float moveSpeed = 0.07f;
		float mPosX, mPosY;
		float mVelX, mVelY;

		//Screen boundaries
		SDL_DisplayMode DM;

		//Collision
		float lastPosX;
		float lastPosY;

	private:
		bool isMoving = false;
		void AnimatePlayer(float delta);

		int ammo = 1;
		int maxAmmo = 1;
		int animationFrame = 0; // 3 frames per animation
		int playerDirection = 1; //0=Up, 1=Down... (same order as below)
		Game* game;

		SDL_Texture* bombTexture;

		std::vector<Bomb> placedBombs;
		std::vector<Blast*> blasts;
		std::vector<SDL_Rect> upSpriteFrames;
		std::vector<SDL_Rect> downSpriteFrames;
		std::vector<SDL_Rect> leftSpriteFrames;
		std::vector<SDL_Rect> rightSpriteFrames;

		float animationDeltaTime = 1; // Current frame duration

		// Constants
		const float timePerAnimation = 333.33333f; // 1 second to complete the animation set
};
