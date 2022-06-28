// bomberman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include <SDL.h>

const std::string windowTitle = "Bomberman";
const int xPos = SDL_WINDOWPOS_CENTERED;
const int yPos = SDL_WINDOWPOS_CENTERED;
const int resolutionX = 1240;
const int resolutionY = 720;
const bool fullScreen = false;

Game* game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->Init(windowTitle, xPos, yPos, resolutionX, resolutionY, fullScreen);

	//Main Game loop

	while (game->Running())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->Clean();

	return 0;
}

//std::cout << "Hello World!\n";