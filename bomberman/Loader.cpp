#include "Loader.h"

SDL_Texture* Loader::LoadTexture(std::string path)
{
	SDL_Texture* texture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		std::cout << "Error loading surface of image '" << path.c_str() << "'...\n";
	}
	else 
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (texture == NULL)
		{
			std::cout << "Error appliying texture '" << path.c_str() << "'...\n";
		}

		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}
