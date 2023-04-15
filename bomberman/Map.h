#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <SDL_image.h>
#include <vector>
#include "Player.h"

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
		void CheckCollision(Player* p);
	private:
		//variables
		SDL_Texture* tileSet;
		std::vector<std::vector<int>> mapTiles;
		int mapSizex = 0;
		int mapSizey = 0;
		const int tileSizex = 18;
		const int tileSizey = 18;
		const int blockSizex = 50;
		const int blockSizey = 50;

		void GetTexture(int tile, SDL_Rect* srcRectangle);
		bool IsOverlaping(SDL_Rect rect1, SDL_Rect rect2);
		void MoveOverlapingPlayer(Player* p, SDL_Rect* mapChunk);
};

