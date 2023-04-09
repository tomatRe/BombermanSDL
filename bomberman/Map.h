#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <SDL_image.h>
#include <vector>
//#include <json.hpp>

class Map
{
	//Every tile are 4 pixels on screen
	public:
		Map();
		Map(std::string mapName, SDL_Texture* tileSet);
		~Map();

		void LoadMap(std::string mapName);
		std::vector<std::vector<int>> GetMap() const;
		SDL_Texture* GetSpriteAtLocation(int x, int y);
		void SetSpriteAtLocation(int x, int y);
		void DrawMap(SDL_Renderer* renderer);
	private:
		void GetTexture(int tile, SDL_Rect* srcRectangle);
		SDL_Texture* tileSet;
		std::vector<std::vector<int>> mapTiles;
		int mapSizex = 180;
		int mapSizey = 180;
		const int tileSizex = 20;
		const int tileSizey = 20;
		const int blockSizex = 25;
		const int blockSizey = 25;
		//using json = nlohmann::json;
};

