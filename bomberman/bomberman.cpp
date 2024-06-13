// bomberman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include "Menu.h"
#include <SDL.h>

const std::string windowTitle = "Bomberman";
const int xPos = SDL_WINDOWPOS_CENTERED;
const int yPos = SDL_WINDOWPOS_CENTERED;
const int resolutionX = 1280;
const int resolutionY = 720;
const bool fullScreen = false;

//FPS
const int fps = 60;
const int frameDelay = 1000/fps;

// Engine
bool isEngineRunning;
SDL_Window* window;
SDL_Renderer* renderer;
Loader* loader;
SDL_Texture* pTexture;
SDL_Texture* tilemap;

//Delta time vars
Uint64 now = SDL_GetPerformanceCounter();
Uint64 last = 0;
float deltaTime = 0;

Game* game = nullptr;
Menu* menu = nullptr;

//Engine initialization
void Init(const std::string title, int xpos, int ypos, int width, int height, bool fullscreen)
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
		pTexture = loader->LoadTexture("assets/sprites/playerSpriteSheet.png");
		tilemap = loader->LoadTexture("assets/sprites/tilemap.png");

		//if everything goes ok set running to true
		isEngineRunning = true;
		std::cout << "Engine running: OK\n";
	}
	else
	{
		isEngineRunning = false;
		std::cout << "Engine running: ERR\n";
	}
}

void RunMainMenuLoop()
{
	//Set background color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	while (menu->Running())
	{
		last = now;

		menu->HandleEvents();
		menu->Update(deltaTime);
		menu->Render();

		now = SDL_GetPerformanceCounter();
		deltaTime = (now - last) * 1000 / (float)SDL_GetPerformanceFrequency();

		if (frameDelay > deltaTime)//apply delay
			SDL_Delay(frameDelay - deltaTime);
	}
}

void RunMainGameLoop()
{
	//Set background color to green
	SDL_SetRenderDrawColor(renderer, 16, 120, 48, 255);

	while (game->Running())
	{
		last = now;

		game->HandleEvents();
		game->Update(deltaTime);
		game->Render();

		now = SDL_GetPerformanceCounter();
		deltaTime = (now - last) * 1000 / (float)SDL_GetPerformanceFrequency();

		if (frameDelay > deltaTime)//apply delay
			SDL_Delay(frameDelay - deltaTime);
	}
}

int main(int argc, char *argv[])
{
	Init(windowTitle, xPos, yPos, resolutionX, resolutionY, fullScreen);

	menu = new Menu(window, renderer, loader, pTexture, tilemap);

	while (isEngineRunning)
	{
		//Start main menu
		RunMainMenuLoop();

		if (menu->GetSelectedOption() == 10)
		{
			menu->isRunning = true;
			
			game = new Game(window, renderer, loader, pTexture, tilemap);
			game->SetPlayerSkin(0, menu->GetPlayerSkinOffset(0)[0], menu->GetPlayerSkinOffset(0)[1]);
			game->SetPlayerSkin(1, menu->GetPlayerSkinOffset(1)[0], menu->GetPlayerSkinOffset(1)[1]);

			//Main Game loop
			RunMainGameLoop();
		}

		if (!menu->Running())
		{
			isEngineRunning = false;
		}
	}

	return 0;
}
