#include "Map.h"
#include "Bomb.h"

Map::Map()
{
}

Map::Map(std::string mapName, SDL_Texture* tileSet)
{
	LoadMap(mapName);
	this->tileSet = tileSet;
}

void Map::DrawMap(SDL_Renderer* renderer)
{
	if (mapTiles.size() != 0)
	{
		for (size_t y = 0; y < mapSizey; y++)
		{
			for (size_t x = 0; x < mapSizex; x++)
			{
				//Get texture
				SDL_Rect srcRectangle = { 0, 0, tileSizex, tileSizey };
				GetTexture(mapTiles[x][y], &srcRectangle);

				//Get screen tile position
				SDL_Rect destRectangle = mapRect[y][x];

				//Draw
				SDL_RenderCopy(renderer, tileSet, &srcRectangle, &destRectangle);
			}
		}
	}
}

void Map::LoadMap(std::string mapName)
{
	std::string line;
	mapTiles.reserve(165);
	mapRect.reserve(165);
	std::srand(std::time(nullptr));

	// Read from the text file
	std::ifstream mapFile(mapName);

	if (mapFile.is_open())
	{
		size_t i = 0;
		while (std::getline(mapFile, line)) {
			// Output the text from the file

			mapTiles.push_back(std::vector<int>(line.length()));

			for (size_t j = 0; j < line.length(); j++)
			{
				//Get tile position on the string
				const char sTile = line[j];
				int tile = 0;

				//Convert char to int
				tile = sTile - '0';

				// Spawn a breakable wall at random 50/50
				if (tile == -16 && std::rand()%100 < 50)
				{
					tile = 9;
				}

				// leave this chunk empty for the player to spawn
				if (sTile == 'p')
				{
					tile = -16;
				}

				//save int to the array
				mapTiles[i][j] = tile;
			}
			mapSizey = line.length();
			i++;
		}

		mapSizex = i;
	}

	// Close the file
	mapFile.close();

	//Parse tiles to rect
	ParseTilesToRect();

	if (mapTiles.size() != 0)
		std::cout << "Map " + mapName << " loaded\n";
	else 
		std::cout << "Map " + mapName << " failed to load\n";
}

void Map::ParseTilesToRect()
{
	if (mapTiles.size() != 0)
	{
		for (size_t y = 0; y < mapSizey; y++)
		{
			mapRect.push_back(std::vector<SDL_Rect>(mapSizex));

			for (size_t x = 0; x < mapSizex; x++)
			{
				if (mapTiles[x][y] != -16) // Blank
				{
					//Get screen tile position
					SDL_Rect destRectangle = GetRectAtPosition(x, y);

					mapRect[y][x] = destRectangle;
				}
			}
		}
	}
}

std::vector<std::vector<int>> Map::GetMapTiles()
{
	return mapTiles;
}

std::vector<std::vector<SDL_Rect>> Map::GetMapRects()
{
	return mapRect;
}

SDL_Texture* Map::GetTileSet()
{
	return this->tileSet;
}

int Map::GetMapSizeX()
{
	return mapSizex;
}

int Map::GetMapSizeY()
{
	return mapSizey;
}

std::vector<float> Map::GetSpawnPoint(int pNumber)
{
	std::vector<float> coords = {
		spawnPoints[pNumber][0],
		spawnPoints[pNumber][1]
	};

	return coords;
}

void Map::SetMapRect(std::vector<std::vector<SDL_Rect>> nRects)
{
	this->mapRect = nRects;
}

SDL_Rect Map::GetRectAtPosition(int x, int y)
{
	SDL_Rect destRectangle;

	//size on the world
	destRectangle.w = blockSizex;
	destRectangle.h = blockSizey;

	//world position
	destRectangle.x = ((blockSizey-6) * y-2);
	destRectangle.y = ((blockSizex-6) * x-3);
	
	return destRectangle;
}

void Map::GetTexture(int tile, SDL_Rect* srcRectangle)
{
	switch (tile)
	{
	case 1: // Brick Top
		srcRectangle->x = 34;
		srcRectangle->y = 237;
		break;
	case 8: // Brick bott
		srcRectangle->x = 68;
		srcRectangle->y = 237;
		break;
	case 3: // Brick L
		srcRectangle->x = 17;
		srcRectangle->y = 254;
		break;
	case 4: // Brick R
		srcRectangle->x = 68;
		srcRectangle->y = 272;
		break;
	case 2: // Brick TL corner
		srcRectangle->x = 17;
		srcRectangle->y = 237;
		break;
	case 5: // Brick TR corner
		srcRectangle->x = 102;
		srcRectangle->y = 271;
		break;
	case 6: // Brick BL corner
		srcRectangle->x = 85;
		srcRectangle->y = 271;
		break;
	case 7: // Brick BR corner
		srcRectangle->x = 119;
		srcRectangle->y = 272;
		break;
	case 9: // breakable wall
		srcRectangle->x = 34;
		srcRectangle->y = 254;
		break;
	case 0: // unbreakable wall
		srcRectangle->x = 821;
		srcRectangle->y = 288;
		break;

	default: // Ground texture
		srcRectangle->x = 327;
		srcRectangle->y = 460;
		break;
	}
}

Map::~Map()
{
	SDL_DestroyTexture(tileSet);
}
