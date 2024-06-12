#include "Game.h"

Game::Game()
{
}

Game::Game(SDL_Window* window, SDL_Renderer* renderer, Loader* loader, SDL_Texture* pTexture, SDL_Texture* tilemap)
{
	this->window = window;
	this->renderer = renderer;
	this->loader = loader;
	this->pTexture = pTexture;
	this->tilemap = tilemap;

	players.reserve(maxPlayers);

	//Load map
 	map = new Map("assets/maps/map1.map", tilemap);

	//Initialize players
	std::vector<float> spawnPoint = map->GetSpawnPoint(2);

	Player* player0 = new Player(spawnPoint[0], spawnPoint[1], pTexture, 56, 48);
	player0->SetBombTexture(tilemap);
	player0->SetGameReference(this);
	player0->playerNumber = 0;
	players.push_back(player0);

	spawnPoint = map->GetSpawnPoint(1);

	Player* player1 = new Player(spawnPoint[0], spawnPoint[1], pTexture, 56, 48);
	player1->SetBombTexture(tilemap);
	player1->SetGameReference(this);
	player1->playerNumber = 1;
	players.push_back(player1);

	//Load Collision manager
	cm = new CollisionManager(map);
	cm->SetTileMap(tilemap);
	cm->SetPlayers(players);

	//if everything goes ok set running to true
	isRunning = true;
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	//Handle player events
	for (size_t i = 0; i < players.size(); i++)
 		players[i]->HandleEvents(event);

	//Handle system events
	switch (event.type)
	{
		case SDL_QUIT: isRunning = false; break;
		default: break;
	}

	// press space to quit to menu on all players dead
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		//Adjust the velocity
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE: if (playersAlive <= 1) isRunning = false; break;
		case SDLK_ESCAPE: isRunning = false; break;
		}
	}
}

void Game::Update(float delta)
{
	playersAlive = players.size();

	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->Update(delta);

		if (!players[i]->isAlive)
		{
			playersAlive--;
		}
	}

	cm->UpdatePowerUps(delta);
	powerUps = cm->GetPowerUps();
	map->SetMapRect(cm->GetMapRect());
	CheckCollisions();
}

void Game::Render()
{
	//Clear last frame
	SDL_RenderClear(renderer);

	//Draw map
	map->DrawMap(renderer);

	//Draw player(s)
	for (size_t i = 0; i < players.size(); i++)
	{
		Player* p = players[i];
		SDL_Texture* spritesheet = p->GetBombSprite();
		std::vector<Bomb*> bombs = p->GetBombs();
		std::vector<Blast*> blasts = p->GetBlasts();

		//Draw bomb(s) for this player
		for (size_t i = 0; i < bombs.size(); i++)
		{
			SDL_RenderCopy(
				renderer,
				spritesheet,
				bombs[i]->GetSrcRectangle(),
				bombs[i]->GetDestRectangle());
		}

		//Draw player after bomb
		SDL_RenderCopy(
			renderer,
			p->GetSprite(),
			p->GetSrcRectangle(),
			p->GetDestRectangle());

		//Draw blast(s) for this player
		for (size_t i = 0; i < blasts.size(); i++)
		{
			SDL_RenderCopy(
				renderer,
				spritesheet,
				blasts[i]->GetSrcRectangle(),
				blasts[i]->GetDestRectangle());
		}
	}

	//Draw PowerUps
	for (size_t i = 0; i < powerUps.size(); i++)
	{
		SDL_RenderCopy(
			renderer,
			tilemap,
			&powerUps[i]->srcRectangle,
			&powerUps[i]->destRectangle);
	}

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Game::CheckCollisions()
{
	cm->CheckCollision();
}

void Game::Clean()
{
	std::cout << "Cleaning up...\n";
	delete map;

	for (size_t i = 0; i < players.size(); i++)
		delete players[i];

	//SDL_DestroyTexture(); HUD
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Quitting...\n";
}

Game::~Game()
{
	Clean();
}
