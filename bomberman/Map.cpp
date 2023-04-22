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
	mapTiles.reserve(165);

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

void Map::DrawMap(SDL_Renderer* renderer)
{
	SDL_Rect srcRectangle;
	SDL_Rect destRectangle;

	//size on the spritesheet
	srcRectangle.w = tileSizex;
	srcRectangle.h = tileSizey;
	
	//size on the world
	destRectangle.w = blockSizex;
	destRectangle.h = blockSizey;

	if (mapTiles.size() != 0)
	{
		int tilePositionx = -3;
		int tilePositiony = -2;

		for (size_t i = 0; i < mapSizex; i++)
		{
			for (size_t j = 0; j < mapSizey; j++)
			{
				if (mapTiles[i][j] != 0) // 0 Means nodraw
				{
					//Set texture
					GetTexture(mapTiles[i][j], &srcRectangle);

					//world position
					destRectangle.x = tilePositionx;
					destRectangle.y = tilePositiony;

					SDL_RenderCopy(renderer, tileSet, &srcRectangle, &destRectangle);
				}

				tilePositionx += blockSizex-6;
			}
			tilePositionx = -6;
			tilePositiony += blockSizey-6;
		}
	}
}

void Map::GetTexture(int tile, SDL_Rect* srcRectangle)
{
	switch (tile)
	{
	case 1: // Brick
		srcRectangle->x = 310;
		srcRectangle->y = 460;
		break;
	case 2: // Brick 2
		srcRectangle->x = 293;
		srcRectangle->y = 460;
		break;

	default: // Ground texture
		srcRectangle->x = 327;
		srcRectangle->y = 460;
		break;
	}
}

void Map::CheckCollision(Player* p)
{
	SDL_Rect pRect = *p->GetDestRectangle();

	for (size_t i = 0; i < mapSizex; i++)
	{
		for (size_t j = 0; j < mapSizey; j++)
		{
			SDL_Rect mapRect = {i, j, Map::blockSizex, Map::blockSizey};

			if (IsOverlaping(mapRect, pRect))
			{
				MoveOverlapingPlayer(p, &mapRect);
			}
		}
	}
}

bool Map::IsOverlaping(SDL_Rect rect1, SDL_Rect rect2)
{
	// If one rectangle is on left side of other
	if (rect1.x > rect2.x || rect2.x + rect2.w > rect1.x + rect1.w)
		return false;

	// If one rectangle is above other
	if (rect1.y + rect1.h > rect2.y || rect2.y > rect1.y)
		return false;

	return true;
}

void Map::MoveOverlapingPlayer(Player* p, SDL_Rect* mapChunk)
{
	//Move player to closest non-overlaping chunk
	SDL_Rect pRect = *p->GetDestRectangle();

	int dir = 0;
	int force = 1;

	while (IsOverlaping(*mapChunk, pRect))
	{
		switch (dir)
		{
		case 0:
			p->mPosY += force;
			break;

		case 1:
			p->mPosY -= force;
			break;

		case 2:
			p->mPosX -= force;
			break;

		case 3:
			p->mPosX += force;
			break;

		default:
			p->mPosY += force;
			dir = 1;
			break;
		}
		force++;
		dir++;
	}
}

Map::~Map()
{
}