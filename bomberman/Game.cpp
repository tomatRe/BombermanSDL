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

		//Set background color to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		//Initialize PNG loader
		int imgFlags = IMG_INIT_PNG;

		loader = new Loader(renderer);
		
		if (!(IMG_Init(imgFlags) & imgFlags))
			std::cout << "Error initializing SDL_image '" << IMG_GetError() << "'...\n";

		//Load everything
		player = new Player(500, 200, LoadMedia("assets/sprites/playerSpriteSheet.png"), 56, 48);

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

//TODO:
//retrieve list of textures from /textures
//add all textures to the vector
//Check if load ok and show according message
SDL_Texture* Game::LoadMedia(std::string path)
{
	//int textureCount = textures.size();

	//Load PNG texture
	SDL_Texture* result = loader->LoadTexture(path);
	//textures.push_back(loader->LoadTexture("/texture.png"));

	//int textureAddedCount = textures.size();

	//if (textureCount == textureAddedCount)
	//	success = false;

	return result;
}



void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update()
{
	player->Update(NULL);
}

void Game::Render()
{
	//Clear last frame
	SDL_RenderClear(renderer);

	//Draw texture(s)
	//SDL_RenderCopy(renderer, -BACKGROUND-, NULL, NULL);
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