#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>

#include "Entity.h"
#include "Player.h"
#include "Loader.h"
#include "Map.h"
#include "Bomb.h"

class Menu
{
	//=========================Functions=========================
	public:
		//Constructors / Destructor
		Menu();
		Menu(SDL_Window*, SDL_Renderer*, Loader*, SDL_Texture*, SDL_Texture*);
		~Menu();

		void Update(float);
		void HandleEvents();
		void Render();
		bool Running() { return isRunning; }
		int GetSelectedOption();

		std::vector<int> GetPlayerSkinOffset(int pIndex);

		Loader* loader;
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool isRunning = false;
	private:
		void SelectOption();
		void GoCursorUp();
		void GoCursorDown();
		void LoadUISprites();
		void DrawCursor();
		void DrawBaseMenu();
		void DrawPlayerSelection();
		void DrawMultiplayerClient();
		void DrawMultiplayerHost();
		void DrawOptions();
		void P1SkinNext();
		void P1SkinPrev();
		void P2SkinNext();
		void P2SkinPrev();
		void AnimatePlayer(float);
		void Clean();
		void Quit();

		//Variables

		// Cursor
		struct position2D
		{
			int x, y;
		};

		int selectedOption = 0; // 1 = new game
		int cursorPosition = 0;
		std::vector<position2D> cursorLocations;
		
		// Textures
		SDL_Texture* pTexture;
		SDL_Texture* tilemap;

		// Texts and menus
		std::vector<SDL_Texture*> textures;
		std::vector<SDL_Rect> texts;

		position2D pos;
		SDL_Surface* surface;
		SDL_Texture* texture;
		SDL_Rect rectangle;

		TTF_Font* sansTitle;
		TTF_Font* sansText;
		TTF_Font* sansSubText;
		SDL_Color white;

		bool isBaseMenuUp = false;
		bool isPlayerMenuUp = false;

		// Player sprites
		SDL_Rect srcRectangleP1;
		SDL_Rect destRectangleP1;

		SDL_Rect srcRectangleP2;
		SDL_Rect destRectangleP2;

		int skinP1 = 0;
		int skinP2 = 0;

		const int xOriginalOffset = 155;
		const int yOriginalOffset = 113;

		position2D offsetP1 = {0, 0};
		position2D offsetP2 = {0, 0};

		float animationDeltaTime = 1; // Current frame duration
		int animationFrame = 0; // 3 frames per animation
		const float timePerAnimation = 333.33333f; // 1 second to complete the animation set

		std::vector<position2D> textureOffsets =
		{
			{0, 0},
			{0, yOriginalOffset},
			{xOriginalOffset, 0},
			{xOriginalOffset, yOriginalOffset}
		};

		std::vector<SDL_Rect> downSpriteFrames = {
			{71, 45, 17, 24},
			{55, 45, 17, 24},
			{87, 45, 17, 24}
		};
};

