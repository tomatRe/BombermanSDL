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

		for (size_t i = 0; i < powerUps.size(); i++)
		{
			SDL_RenderCopy(
				renderer,
				tileSet,
				&powerUps[i]->srcRectangle,
				&powerUps[i]->destRectangle);
		}
	}
}

void Map::UpdatePowerUps(float delta)
{
	for (size_t i = 0; i < powerUps.size(); i++)
	{
		PowerUp* p = powerUps[i];
		p->Update(delta);

		if (p->GetAliveTime() > p->GetMaxAliveTime())
			DeletePowerUP(p);
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
				if (IsOverlaping(*pRect, players[j]->destRectangle)
					&& players[j]->isAlive)
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

		//Blasts collisions
		for (size_t k = 0; k < playerBlasts.size(); k++)
		{
			//Blasts to player collisions
			for (size_t z = 0; z < players.size(); z++)
			{
				SDL_Rect pRect = *playerBlasts[k]->GetDestRectangle();

				//Created a small reduction in bomb collision so it wont break unexpected walls
				SDL_Rect reducedCollision = {
					pRect.x + 10, pRect.y + 10, pRect.h - 10, pRect.w - 10
				};

				if (players[z]->isAlive &&
					IsOverlaping(reducedCollision, players[z]->destRectangle))
				{
					players[z]->Die();
					std::cout << "Player " << players[z]->playerNumber
						<< " was killed by "<< playerBlasts[k]->ownerPlayer << std::endl;
				}
			}

			//Blasts to map collisions
			for (size_t x = 0; x < mapSizex; x++)
			{
				for (size_t y = 0; y < mapSizey; y++)
				{
					SDL_Rect bRect = *playerBlasts[k]->GetDestRectangle();

					//Created a small reduction in the blast collision so it wont break unexpected walls
					SDL_Rect reducedCollision = { 
						bRect.x+10, bRect.y+10, bRect.h-10, bRect.w-10
					};

					if (IsOverlaping(mapRect[y][x], reducedCollision))
					{
						if (mapTiles[x][y] == 9)
						{
							// Spawn a powerUp at random 50/50
							if (std::rand() % 100 < 50)
							{
								AddPowerUP(mapRect[y][x].x, mapRect[y][x].y);
							}

							mapRect[y][x] = SDL_Rect{};
						}
					}
				}
			}

			//Blasts to powerUps collisions
			for (size_t j = 0; j < powerUps.size(); j++)
			{
				SDL_Rect bRect = *playerBlasts[k]->GetDestRectangle();

				if (powerUps[j]->GetAliveTime() > 0.75f &&
					IsOverlaping(bRect, powerUps[j]->destRectangle))
				{
					DeletePowerUP(powerUps[j]);
				}
			}
		}

		// PowerUp pickups
		for (size_t j = 0; j < powerUps.size(); j++)
		{
			if (IsOverlaping(*pRect, powerUps[j]->destRectangle))
			{
				players[i]->LevelUp(*powerUps[j]);
				DeletePowerUP(powerUps[j]);
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

void Map::SetPlayers(std::vector<Player*> players)
{
	this->players = players;
}

std::vector<float> Map::GetSpawnPoint(int pNumber)
{
	std::vector<float> coords = {
		spawnPoints[pNumber][0],
		spawnPoints[pNumber][1]
	};

	return coords;
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

void Map::AddPowerUP(float x, float y)
{
	PowerUp* p = new PowerUp(x, y, tileSet);
	powerUps.push_back(p);
}

void Map::DeletePowerUP(PowerUp* p)
{
	const auto& removed_iterator = std::find(powerUps.begin(), powerUps.end(), p);

	if (removed_iterator != powerUps.end())
	{
		powerUps.erase(removed_iterator);
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
