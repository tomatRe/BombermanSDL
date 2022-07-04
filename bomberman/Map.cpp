#include "Map.h"

Map::Map()
{
}

Map::Map(std::string mapName, SDL_Texture* tileSet)
{
	LoadMap(mapName);
	this->tileSet = tileSet;
}

int ** Map::LoadMap(std::string mapName)
{
	std::stringstream ss;
	std::string line;

	// Read from the text file
	std::ifstream mapFile(mapName);

	int i = 0;
	while (std::getline(mapFile, line)) {
		// Output the text from the file

		for (int j = 0; j < line.length(); j++)
		{
			//Get tile position on the string
			char sTile = line.at(j);
			int tile;

			//Convert char to string
			ss << sTile;
			//Convert string to int
			ss >> tile;

			//save int to the array
			mapTiles[i][j] = tile;
		}

		i++;
	}

	// Close the file
	mapFile.close();

	return mapTiles;
}

SDL_Texture * Map::GetSpriteAtLocation(int x, int y)
{
	return nullptr;
}

void Map::SetSpriteAtLocation(int x, int y)
{
}

void Map::ReadMap(std::string mapName)
{
}

Map::~Map()
{
}