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
	std::string line;
	mapTiles = 0;
	mapTiles = new int*[180];

	// Read from the text file
	std::ifstream mapFile(mapName);

	if (mapFile.is_open())
	{
		int i = 0;
		while (std::getline(mapFile, line)) {
			// Output the text from the file

			mapTiles[i] = new int[320];

			for (int j = 0; j < line.length(); j++)
			{
				//Get tile position on the string
				char sTile = line[j];
				int tile = 0;

				//Convert char to int
				tile = sTile - '0';

				//save int to the array
				mapTiles[i][j] = tile;
			}

			i++;
		}
	}

	// Close the file
	mapFile.close();

	if (mapTiles != nullptr)
		std::cout << "Map " + mapName << " loaded\n";
	else 
		std::cout << "Map " + mapName << " failed to load\n";

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