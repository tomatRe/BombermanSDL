// bomberman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>

int main(int args, char *arv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(5000);

	return 0;
}

//std::cout << "Hello World!\n";