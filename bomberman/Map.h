#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SDL_image.h>

class Map
{
	//Every tile are 4 pixels on screen
	public:
		Map();
		Map(std::string mapName, SDL_Texture* tileSet);
		~Map();

		int** LoadMap(std::string mapName);
		SDL_Texture* GetSpriteAtLocation(int x, int y);
		void SetSpriteAtLocation(int x, int y);
	private:
		void ReadMap(std::string mapName);

		SDL_Texture* tileSet;
		int** mapTiles;
};

