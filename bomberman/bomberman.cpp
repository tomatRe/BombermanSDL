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

//Delta time vars
Uint64 now = SDL_GetPerformanceCounter();
Uint64 last = 0;
float deltaTime = 0;

Game* game = nullptr;
Menu* menu = nullptr;

void RunMainMenuLoop()
{
	//Set background color to black
	SDL_SetRenderDrawColor(game->GetRenderer(), 0, 0, 0, 255);

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
	SDL_SetRenderDrawColor(game->GetRenderer(), 16, 120, 48, 255);

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
	bool isRunning = true;
	game = new Game();

	game->Init(windowTitle, xPos, yPos, resolutionX, resolutionY, fullScreen);
	menu = new Menu(game->GetWindow(), game->GetRenderer(), game->GetLoader());

	while (isRunning)
	{
		//Start main menu
		RunMainMenuLoop();

		if (menu->GetSelectedOption() == 10)
		{
			menu->isRunning = true;
			//Main Game loop
			RunMainGameLoop();
		}

		if (!menu->Running())
		{
			isRunning = false;
		}
	}

	game->Clean();

	return 0;
}
