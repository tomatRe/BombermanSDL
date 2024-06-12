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
#include "CollisionManager.h"
#include "Bomb.h"
#include <vector>

using namespace std;

class Game
{
	public:
		Game();
		Game(SDL_Window*, SDL_Renderer*, Loader*, SDL_Texture*, SDL_Texture*);
		~Game();

		void HandleEvents();
		void Update(float delta);
		void Render();
		void CheckCollisions();
		void SetPlayerSkin(int pIndex, int offsetX, int offsetY);
		void Clean();

		bool Running() { return isRunning; }

		Loader* loader;

	private:
		void SpawnPlayers();

		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* pTexture;
		SDL_Texture* tilemap;

		//Media (HUD)
		//std::vector<SDL_Texture*> textures;

		//Map
		Map* map;

		//Collision manager
		CollisionManager* cm;

		//Player(s)
		std::vector<Player*> players;
		int playersAlive;

		//PowerUps
		std::vector<PowerUp*> powerUps;

		//Constants
		const int maxPlayers = 4;
};
