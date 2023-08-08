#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include "SDL_image.h"
#include "Entity.h"
#include "Player.h"
#include "Loader.h"
#include "Map.h"
#include "Bomb.h"
#include <vector>

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
		void Clean();
		bool Running() { return isRunning; }

		Loader* loader;
		SDL_Window* window;
		SDL_Renderer* renderer;
	private:
		void LoadUISprites();

		bool isRunning = false;
};

