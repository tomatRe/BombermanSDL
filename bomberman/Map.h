#pragma once

#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Player.h"

class Map
{
	public:

		//=========================Functions=========================

		//Constructors / Destructor
		Map();
		Map(std::string mapName, SDL_Texture* tileSet);
		~Map();

		//Tick functions
		void DrawMap(SDL_Renderer* renderer);
		void CheckCollision();

		//Public functions
		void LoadMap(std::string mapName);

		//Getters/setters
		void SetPlayers(std::vector<Player*>);

	private:
		//Private Functions
		void ParseTilesToRect();
		SDL_Rect GetRectAtPosition(int x, int y);
		void GetTexture(int tile, SDL_Rect* srcRectangle);
		bool IsOverlaping(SDL_Rect rect1, SDL_Rect rect2);

		//variables
		SDL_Texture* tileSet;
		std::vector<Player*> players;
		std::vector<std::vector<int>> mapTiles;
		std::vector<std::vector<SDL_Rect>> mapRect;
		int mapSizex = 0;
		int mapSizey = 0;
		const int tileSizex = 18;
		const int tileSizey = 18;
		const int blockSizex = 50;
		const int blockSizey = 50;
};
