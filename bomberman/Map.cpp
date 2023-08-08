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

void Map::CheckCollision()
{	
	for (size_t i = 0; i < players.size(); i++)
	{
		SDL_Rect* pRect = players[i]->GetDestRectangle();

		//Player to map collisions
		for (size_t x = 0; x < mapSizex; x++)
		{
			for (size_t y = 0; y < mapSizey; y++)
			{
				if (IsOverlaping(mapRect[y][x], *pRect))
				{
					players[i]->mPosX = players[i]->lastPosX;
					players[i]->mPosY = players[i]->lastPosY;
				}
			}
		}

		//Player to player collisions
		for (size_t j = 0; j < players.size(); j++)
		{
			if (players[i] != players[j])
			{
				if (IsOverlaping(*pRect, players[j]->destRectangle))
				{
					players[i]->mPosX = players[i]->lastPosX;
					players[i]->mPosY = players[i]->lastPosY;
				}
			}
		}

		//Bombs to player collisions
		std::vector<Bomb*> playerBombs = players[i]->GetBombs();
		std::vector<Blast*> playerBlasts = players[i]->GetBlasts();

		for (size_t j = 0; j < playerBombs.size(); j++)
		{
			for (size_t z = 0; z < players.size(); z++)
			{
				if (playerBombs[j]->GetOwningPlayer() != players[i] ||
					playerBombs[j]->GetAliveTime() > 1.f)
				{
					if (IsOverlaping(playerBombs[j]->destRectangle, players[z]->destRectangle))
					{
						players[z]->mPosX = players[z]->lastPosX;
						players[z]->mPosY = players[z]->lastPosY;
					}
				}
			}
		}

		//Blasts to player collisions
		for (size_t k = 0; k < playerBlasts.size(); k++)
		{
			for (size_t z = 0; z < players.size(); z++)
			{
				if (IsOverlaping(*playerBlasts[k]->GetDestRectangle(),
					players[z]->destRectangle))
				{
					//kill
					std::cout << "Player " << players[z]->playerNumber << " is dead \n";
				}

			}
		}
	}

	//Blasts to map collisions (TODO)
}

void Map::LoadMap(std::string mapName)
{
	std::string line;
	mapTiles.reserve(165);
	mapRect.reserve(165);

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

	//Parse tiles to rect
	ParseTilesToRect();

	if (mapTiles.size() != 0)
		std::cout << "Map " + mapName << " loaded\n";
	else 
		std::cout << "Map " + mapName << " failed to load\n";
}

void Map::SetPlayers(std::vector<Player*> players)
{
	this->players = players;
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
				if (mapTiles[x][y] != 0) // 0 Means nodraw
				{
					//Get screen tile position
					SDL_Rect destRectangle = GetRectAtPosition(x, y);

					mapRect[y][x] = destRectangle;
				}
			}
		}
	}
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
	case 1: // Brick TL
		srcRectangle->x = 34;
		srcRectangle->y = 237;
		break;
	case 8: // Brick TR
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

	default: // Ground texture
		srcRectangle->x = 327;
		srcRectangle->y = 460;
		break;
	}
}

bool Map::IsOverlaping(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		(rect1.h/2) + rect1.y > rect2.y) 
	{
		// Collision detected!
		return true;
	}

	return false;
}

Map::~Map()
{
	SDL_DestroyTexture(tileSet);
}
