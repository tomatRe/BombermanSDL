#pragma once
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "PowerUp.h"

class CollisionManager
{
public:

	//=========================Functions=========================

	//Constructors / Destructor
	CollisionManager(Map*);
	~CollisionManager();

	//Tick functions
	void CheckCollision();
	void UpdatePowerUps(float);

	std::vector<PowerUp*> GetPowerUps();
	std::vector<std::vector<SDL_Rect>> GetMapRect();
	void SetPlayers(std::vector<Player*>);
	void SetTileMap(SDL_Texture*);

private:
	//Private Functions
	void AddPowerUP(float, float);
	void DeletePowerUP(PowerUp*);
	bool IsOverlaping(SDL_Rect, SDL_Rect);

	//variables
	Map* map;
	std::vector<Player*> players;
	std::vector<PowerUp*> powerUps;
	std::vector<std::vector<int>> mapTiles;
	std::vector<std::vector<SDL_Rect>> mapRect;
	SDL_Texture* tilemap;
	int mapSizex = 0;
	int mapSizey = 0;
	const int tileSizex = 18;
	const int tileSizey = 18;
	const int blockSizex = 50;
	const int blockSizey = 50;
};

