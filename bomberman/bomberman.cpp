// bomberman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
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
double deltaTime = 0;

Game* game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->Init(windowTitle, xPos, yPos, resolutionX, resolutionY, fullScreen);

	//Main Game loop

	while (game->Running())
	{
		last = now;

		game->HandleEvents();
		game->Update(deltaTime);
		game->Render();

		now = SDL_GetPerformanceCounter();
		deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

		if (frameDelay > deltaTime)//apply delay
			SDL_Delay(frameDelay - deltaTime);
	}

	game->Clean();

	return 0;
}

//std::cout << "Hello World!\n";