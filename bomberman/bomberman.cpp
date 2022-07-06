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

Uint32 frameStart;
int frameTime;

Game* game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->Init(windowTitle, xPos, yPos, resolutionX, resolutionY, fullScreen);

	//Main Game loop

	while (game->Running())
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update(((SDL_GetTicks() - frameStart)* 1000) / (float)SDL_GetPerformanceFrequency());
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;//ms of how much it took the frame

		if (frameDelay > frameTime)//apply delay
			SDL_Delay(frameDelay - frameTime);
	}

	game->Clean();

	return 0;
}

//std::cout << "Hello World!\n";