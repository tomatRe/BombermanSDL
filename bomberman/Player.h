#pragma once
#include "Entity.h"
#include <vector>

class Blast;
class Bomb;
class Game;

class Player : public Entity
{
	public:
		//=========================Functions=========================

		//Constructors / Destructor
		Player();
		Player(int x, int y);
		Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY);
		~Player();

		//Tick functions
		void Update(float);
		void Move(float);
		void AnimatePlayer(float);
		void UpdateBombs(float);
		void UpdateBlasts(float);

		void HandleEvents(SDL_Event&);
		void CheckCollisions();
		void SpawnBomb();
		void DestroyBombReference(Bomb*);
		void AddBlast(Blast*);

		//Getters
		std::vector<Bomb> GetBombs();
		SDL_Texture* GetSprite();
		SDL_Rect* GetSrcRectangle();
		SDL_Rect* GetDestRectangle();

		//Setters
		void SetGameReference(Game*);
		void SetBombTexture(SDL_Texture*);
		void SetBlasts(std::vector<Blast*>);

		//=========================Variables=========================

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

		int ammo = 1;
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
		const int maxAmmo = 1;
		const float timePerAnimation = 333.33333f; // 1 second to complete the animation set
};
