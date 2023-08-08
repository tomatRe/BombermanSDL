#include "Menu.h"

Menu::Menu()
{
}

Menu::Menu(SDL_Window* window, SDL_Renderer* renderer, Loader* loader)
{
	this->window = window;
	this->renderer = renderer;
	this->loader = loader;

	LoadUISprites();
	isRunning = true;
}

void Menu::Update(float)
{
	//TODO
}

void Menu::HandleEvents()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	//Handle system events
	switch (e.type)
	{
	case SDL_QUIT: isRunning = false; break;
	default: break;
	}

	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: /*TODO*/; break;
		case SDLK_DOWN: /*TODO*/; break;
		case SDLK_LEFT: /*TODO*/; break;
		case SDLK_RIGHT: /*TODO*/; break;
		case SDLK_SPACE: /*TODO*/; break;
		case SDLK_ESCAPE: /*TODO*/; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: /*TODO*/; break;
		case SDLK_DOWN: /*TODO*/; break;
		case SDLK_LEFT: /*TODO*/; break;
		case SDLK_RIGHT: /*TODO*/; break;
		}
	}
}

void Menu::Render()
{
	//Clear last frame
	SDL_RenderClear(renderer);

	//TODO: draw menu

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Menu::LoadUISprites()
{
	//TODO: load menu sprites
}

void Menu::Clean()
{
	std::cout << "Cleaning up...\n";

	//SDL_DestroyTexture(); HUD
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Quitting...\n";
}

Menu::~Menu()
{
}
