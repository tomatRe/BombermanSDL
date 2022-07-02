#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include "SDL_image.h"
#include "Loader.h"
#include <vector>

using namespace std;

class Game
{
	public:
		Game();
		~Game();

		void Init(const std::string title, int xpos, int ypos, int width, int height, bool fullscreen);

		void HandleEvents();
		void Update();
		void Render();
		void Clean();

		bool Running() { return isRunning; }

		Loader* loader;

	private:
		bool LoadMedia(std::string path);
		bool isRunning;
		SDL_Window *window;
		SDL_Renderer *renderer;

		//Media
		SDL_Texture* player_t;
		//std::vector<SDL_Texture*> textures;
};

