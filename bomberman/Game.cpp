#include "Game.h"

Game::Game()
{
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

		//Set background color to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		//if everything goes ok set running to true
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}
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
}

void Game::Render()
{
	//Clear last frame
	SDL_RenderClear(renderer);

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	std::cout << "Cleaning up...\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Quitting...\n";
}
