#pragma once

#include <iostream>
#include <SDL.h>

class Game
{
	public:
		Game();
		~Game();

		void Init(const std::string title, int xpos, int ypos, int width, int height, bool fullscreen);

		void HandleEvents();
		void Update();
		void Render();
		void Clean();

		bool Running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
};

