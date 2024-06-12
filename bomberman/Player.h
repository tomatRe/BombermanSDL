#pragma once
#include "Entity.h"
#include <vector>

class Blast;
class Bomb;
class Game;
class PowerUp;

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
		void DestroyBlastReference(Blast*);
		void AddBlast(Blast*);
		void LevelUp(PowerUp);
		void Die();

		//Getters
		std::vector<Bomb*> GetBombs();
		std::vector<Blast*> GetBlasts();
		SDL_Texture* GetSprite();
		SDL_Texture* GetBombSprite();
		SDL_Rect* GetSrcRectangle();
		SDL_Rect* GetDestRectangle();

		//Setters
		void SetGameReference(Game*);
		void SetBombTexture(SDL_Texture*);
		void SetBlasts(std::vector<Blast*>);
		void SetXSkinOffset(int offset);
		void SetYSkinOffset(int offset);

		//=========================Variables=========================

		//Constants
		const int playerW = 17;
		const int playerH = 24;

		//Movement
		float moveSpeed = 0.07f;
		float moveUpgradeIncrement = moveSpeed * 1.12f;
		float maxMoveSpeed = moveSpeed * 5;
		float mPosX, mPosY;
		float mVelX, mVelY;

		//Screen boundaries
		SDL_DisplayMode DM;

		//Collision
		float lastPosX;
		float lastPosY;

		//Gameplay / animations
		int playerNumber = 0;
		bool isAlive = true;

	private:
		void UpdateSkinOffset();

		//Gameplay variables
		int maxAmmo = 1;
		int ammo = 1;
		int blastRadius = 1;
		int animationFrame = 0; // 3 frames per animation
		int playerDirection = 1; //0=Up, 1=Down... (same order as below)
		Game* game;
		std::vector<Bomb*> placedBombs;
		std::vector<Blast*> blasts;

		//Animation variables
		int xSkinOffset = 0;
		int ySkinOffset = 0;

		bool isMoving = false;
		SDL_Texture* bombTexture;

		std::vector<SDL_Rect> upSpriteFrames = {
			{72 + xSkinOffset, 20 + ySkinOffset, playerW, playerH},
			{56 + xSkinOffset, 20 + ySkinOffset, playerW, playerH},
			{88 + xSkinOffset, 20 + ySkinOffset, playerW, playerH}
		};

		std::vector<SDL_Rect> downSpriteFrames = {
			{71 + xSkinOffset, 45 + ySkinOffset, playerW, playerH},
			{55 + xSkinOffset, 45 + ySkinOffset, playerW, playerH},
			{87 + xSkinOffset, 45 + ySkinOffset, playerW, playerH}
		};

		std::vector<SDL_Rect> leftSpriteFrames = {
			{2 + xSkinOffset, 44 + ySkinOffset, playerW, playerH},
			{19 + xSkinOffset, 44 + ySkinOffset, playerW, playerH},
			{35 + xSkinOffset, 44 + ySkinOffset, playerW, playerH}
		};

		std::vector<SDL_Rect> rightSpriteFrames = {
			{105 + xSkinOffset, 46 + ySkinOffset, playerW, playerH},
			{122 + xSkinOffset, 47 + ySkinOffset, playerW, playerH},
			{139 + xSkinOffset, 48 + ySkinOffset, playerW, playerH}
		};

		std::vector<SDL_Rect> dieSpriteFrames = {
			{29 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
			{48 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
			{65 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
			{82 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
			{99 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
			{117 + xSkinOffset, 74 + ySkinOffset, playerW, playerH}
		};

		float animationDeltaTime = 1; // Current frame duration

		// Constants
		const float timePerAnimation = 333.33333f; // 1 second to complete the animation set
};
