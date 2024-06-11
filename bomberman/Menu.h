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
		Menu(SDL_Window*, SDL_Renderer*, Loader*);
		~Menu();

		void Update(float);
		void HandleEvents();
		void Render();
		bool Running() { return isRunning; }
		int GetSelectedOption();

		Loader* loader;
		SDL_Window* window;
		SDL_Renderer* renderer;
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
		void Clean();
		void Quit();

		bool isRunning = false;
		int selectedOption = 1; // 1 = new game
		int cursorPosition = 1;
		
		// Textures
		SDL_Texture* pTexture;
		SDL_Texture* tilemap;

		// Texts and menus
		std::vector <SDL_Texture*> textures;
		std::vector<SDL_Rect> texts;

		SDL_Surface* surface;
		SDL_Texture* texture;
		SDL_Rect rectangle;

		TTF_Font* sansTitle;
		TTF_Font* sansText;
		TTF_Font* sansSubText;
		SDL_Color white;
};

