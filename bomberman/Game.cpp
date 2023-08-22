#include "Game.h"

Game::Game()
{
	players.reserve(maxPlayers);
}

Game::~Game()
{
	Clean();
}

//Engine initialization
void Game::Init(const std::string title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	//Check Flags
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	//Start everything
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Started!\n";

		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);

		if (window)
			std::cout << "Window Created...\n";

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
			std::cout << "Renderer Created...\n";

		//Initialize PNG loader
		int imgFlags = IMG_INIT_PNG;

		loader = new Loader(renderer);
		
		if (!(IMG_Init(imgFlags) & imgFlags))
			std::cout << "Error initializing SDL_image '" << IMG_GetError() << "'...\n";

		//Load everything
		SDL_Texture* pTexture = loader->LoadTexture("assets/sprites/playerSpriteSheet.png");
		SDL_Texture* tilemap = loader->LoadTexture("assets/sprites/tilemap.png");

		//Load map
		map = new Map("assets/maps/map1.map", tilemap);

		//Initialize players
		std::vector<float> spawnPoint = map->GetSpawnPoint(0);

		Player* player0 = new Player(spawnPoint[0], spawnPoint[1], pTexture, 56, 48);
		player0->SetBombTexture(tilemap);
		player0->SetGameReference(this);
		player0->playerNumber = 0;
		players.push_back(player0);

		spawnPoint = map->GetSpawnPoint(1);

		Player* player1 = new Player(spawnPoint[0], spawnPoint[1], pTexture, 56, 48);
		player1->SetBombTexture(tilemap);
		player1->SetGameReference(this);
		player0->playerNumber = 1;
		players.push_back(player1);

		map->SetPlayers(players);

		//if everything goes ok set running to true
		isRunning = true;
		std::cout << "Engine running: OK\n";
	}
	else 
	{
		isRunning = false;
		std::cout << "Engine running: ERR\n";
	}
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
}

void Game::Update(float delta)
{
	for (size_t i = 0; i < players.size(); i++)
		players[i]->Update(delta);

	map->UpdatePowerUps(delta);
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

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Game::CheckCollisions()
{
	map->CheckCollision();
}

SDL_Renderer* Game::GetRenderer()
{
	return renderer;
}

SDL_Window* Game::GetWindow()
{
	return window;
}

Loader* Game::GetLoader()
{
	return loader;
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
