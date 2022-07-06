#include "Game.h"

Game::Game()
{}

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

		//Set background color to background green
		SDL_SetRenderDrawColor(renderer, 16, 120, 48, 255);

		//Initialize PNG loader
		int imgFlags = IMG_INIT_PNG;

		loader = new Loader(renderer);
		
		if (!(IMG_Init(imgFlags) & imgFlags))
			std::cout << "Error initializing SDL_image '" << IMG_GetError() << "'...\n";

		//Load everything
		SDL_Texture* pTexture = loader->LoadTexture("assets/sprites/playerSpriteSheet.png");
		SDL_Texture* tilemap = loader->LoadTexture("assets/sprites/tilemap.png");

		//Load map
		//map = new Map("assets/maps/map1.map", tilemap);

		//Initialize entities
		player = new Player(500, 200, pTexture, 56, 48);

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
	player->HandleEvents(event);

	//Handle system events
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update(float delta)
{
	player->Update(delta);
}

void Game::Render()
{
	//Clear last frame
	SDL_RenderClear(renderer);

	//Draw map
	//SDL_RenderCopy(renderer, -BACKGROUND TEXTURE-, NULL, NULL);

	//Draw player(s)
	SDL_RenderCopy(renderer, player->GetSprite(), player->GetSrcRectangle(), player->GetDestRectangle());

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	std::cout << "Cleaning up...\n";
	SDL_DestroyTexture(player->GetSprite());
	//SDL_DestroyTexture();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Quitting...\n";
}