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

using namespace std;

class Game
{
	public:
		Game();
		~Game();

		void Init(const std::string title, int xpos, int ypos, int width, int height, bool fullscreen);

		void HandleEvents();
		void Update(float delta);
		void Render();
		void CheckCollisions();
		void Clean();

		bool Running() { return isRunning; }

		Loader* loader;

	private:
		SDL_Texture* LoadMedia(std::string path);
		bool isRunning;
		SDL_Window *window;
		SDL_Renderer *renderer;

		//Media (HUD)
		//std::vector<SDL_Texture*> textures;

		//Map
		Map* map;

		//Player(s)
		std::vector<Player*> players;

		//Constants
		const int maxPlayers = 4;
};
