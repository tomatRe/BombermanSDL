#include "Map.h"

Map::Map()
{
}

Map::Map(std::string mapName, SDL_Texture* tileSet)
{
	LoadMap(mapName);
	this->tileSet = tileSet;
}

void Map::LoadMap(std::string mapName)
{
	std::string line;
	mapTiles.reserve(180);

	// Read from the text file
	std::ifstream mapFile(mapName);

	if (mapFile.is_open())
	{
		size_t i = 0;
		while (std::getline(mapFile, line)) {
			// Output the text from the file

			mapTiles.push_back(std::vector<int>(180));

			for (size_t j = 0; j < line.length(); j++)
			{
				//Get tile position on the string
				const char sTile = line[j];
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

	if (mapTiles.size() != 0)
		std::cout << "Map " + mapName << " loaded\n";
	else 
		std::cout << "Map " + mapName << " failed to load\n";
}

std::vector<std::vector<int>> Map::GetMap() const
{
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