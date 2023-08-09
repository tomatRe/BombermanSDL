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
	texts.reserve(50);
	textures.reserve(50);

	isRunning = true;
}

void Menu::Update(float)
{
	if (isRunning)
	{
		//TODO
	}
	else
	{
		//Clean();
	}
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
		case SDLK_ESCAPE: isRunning = false; break;
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
	for (size_t i = 0; i < texts.size(); i++)
	{
		SDL_RenderCopy(renderer, textures[i], NULL, &texts[i]);
	}

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Menu::LoadUISprites()
{
	//TODO: load menu sprites

	//Draw menu
	TTF_Init();
	TTF_Font* sans = TTF_OpenFont("assets/fonts/font.ttf", 24);
	SDL_Color white = { 255, 255, 255 };

	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(sans, "Menu to cutre to wapo ahi pim pam", white);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	textures.push_back(Message);

	SDL_Rect message_rect; //create a rect
	message_rect.x = 20;  //controls the rect's x coordinate 
	message_rect.y = 20; // controls the rect's y coordinte
	message_rect.w = 1000; // controls the width of the rect
	message_rect.h = 150; // controls the height of the rect

	texts.push_back(message_rect);
}

void Menu::Clean()
{
	std::cout << "Cleaning up...\n";

	//SDL_DestroyTexture(); HUD
	//SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	//SDL_Quit();
	std::cout << "Quitting menu...\n";
}

void Menu::Quit()
{
	Clean();
}

Menu::~Menu()
{
}
