#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_audio.h>

class Loader
{
	public:
		Loader(SDL_Renderer* renderer);
		~Loader();
		SDL_Texture* LoadTexture(std::string path);

	private:
		bool isRunning;
		SDL_Window *window;
		SDL_Renderer *renderer;
};

