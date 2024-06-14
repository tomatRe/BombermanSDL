#include "CollisionManager.h"

CollisionManager::CollisionManager(Map* map)
{
	this->mapTiles = map->GetMapTiles();
	this->mapRect = map->GetMapRects();
	this->mapSizex = map->GetMapSizeX();
	this->mapSizey = map->GetMapSizeY();
}

void CollisionManager::CheckCollision()
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
				if (playerBombs[j]->GetOwningPlayer() != players[i])
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
						<< " was killed by " << playerBlasts[k]->ownerPlayer << std::endl;
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
						bRect.x + 10, bRect.y + 10, bRect.h - 10, bRect.w - 10
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
			PowerUp* p = powerUps[j];
			SDL_Rect powerUpRect = p->destRectangle;
			//Upscale collision rectangle to account for the size reduction
			SDL_Rect upscaledCollision = {
						powerUpRect.x - 8, powerUpRect.y - 8, 48, 48
			};

			if (IsOverlaping(*pRect, upscaledCollision))
			{
				players[i]->LevelUp(*p);
				DeletePowerUP(p);
			}
		}
	}
}

void CollisionManager::UpdatePowerUps(float delta)
{
	for (size_t i = 0; i < powerUps.size(); i++)
	{
		PowerUp* p = powerUps[i];
		p->Update(delta);

		if (p->GetAliveTime() > p->GetMaxAliveTime())
			DeletePowerUP(p);
	}
}

void CollisionManager::AddPowerUP(float x , float y)
{
	PowerUp* p = new PowerUp(x, y, tilemap);
	powerUps.push_back(p);
}

void CollisionManager::DeletePowerUP(PowerUp* p)
{
	const auto& removed_iterator = std::find(powerUps.begin(), powerUps.end(), p);

	if (removed_iterator != powerUps.end())
	{
		powerUps.erase(removed_iterator);
	}
}

bool CollisionManager::IsOverlaping(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		(rect1.h / 2) + rect1.y > rect2.y)
	{
		// Collision detected!
		return true;
	}

	return false;
}

std::vector<PowerUp*> CollisionManager::GetPowerUps()
{
	return powerUps;
}

std::vector<std::vector<SDL_Rect>> CollisionManager::GetMapRect()
{
	return mapRect;
}

void CollisionManager::SetPlayers(std::vector<Player*> players)
{
	this->players = players;
}

void CollisionManager::SetTileMap(SDL_Texture* tileMap)
{
	this->tilemap = tileMap;
}

CollisionManager::~CollisionManager()
{
}
