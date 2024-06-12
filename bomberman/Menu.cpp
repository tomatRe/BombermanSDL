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
	DrawBaseMenu();
	texts.reserve(50);
	textures.reserve(50);

	isRunning = true;
}

void Menu::Update(float)
{
	if (isRunning)
	{
		//Update cursor vertical position
		SDL_Rect* cursor = &texts[texts.size() - 1];
		cursor->x = cursorLocations[cursorPosition].x;
		cursor->y = cursorLocations[cursorPosition].y;
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
		case SDLK_UP: GoCursorUp(); break;
		case SDLK_DOWN: GoCursorDown(); break;
		case SDLK_LEFT: /*TODO*/; break;
		case SDLK_RIGHT: /*TODO*/; break;
		case SDLK_RETURN: isRunning = false; break;
		case SDLK_SPACE: SelectOption(); break;
		case SDLK_ESCAPE: isRunning = false; selectedOption = -1; break;
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

	for (size_t i = 0; i < texts.size(); i++)
	{
		SDL_RenderCopy(renderer, textures[i], NULL, &texts[i]);
	}

	//Draw next frame
	SDL_RenderPresent(renderer);
}

void Menu::LoadUISprites()
{
	//Load textures
	pTexture = loader->LoadTexture("assets/sprites/playerSpriteSheet.png");
	tilemap = loader->LoadTexture("assets/sprites/tilemap.png");

	//Load font
	TTF_Init();
	sansTitle = TTF_OpenFont("assets/fonts/font.ttf", 24);
	sansText = TTF_OpenFont("assets/fonts/font.ttf", 12);
	sansSubText = TTF_OpenFont("assets/fonts/font.ttf", 8);
	white = { 255, 255, 255 };
}

void Menu::DrawCursor()
{
	// Create Cursor Sprite + square
	white.r = 0;
	white.b = 0;

	surface = TTF_RenderText_Solid(sansTitle, "<-", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = cursorLocations[0].x;
	rectangle.y = cursorLocations[0].y;
	rectangle.w = 75;
	rectangle.h = 75;

	texts.push_back(rectangle);

	cursorPosition = 0;

	// set the white color back
	white.r = 255;
	white.b = 255;
}

void Menu::DrawBaseMenu()
{
	// Clear previous texts
	texts.clear();
	textures.clear();
	cursorLocations.clear();

	// GAME TITLE
	surface = TTF_RenderText_Solid(sansTitle, "Bomberman SDL", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = 20;
	rectangle.y = 20;
	rectangle.w = 750;
	rectangle.h = 125;

	texts.push_back(rectangle);

	//Create new game text + square
	surface = TTF_RenderText_Solid(sansText, "Local VS", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.y = 200; // controls the rect's y coordinte
	rectangle.w = 375; // controls the width of the rect
	rectangle.h = 75; // controls the height of the rect
	pos.x = rectangle.x;
	pos.y = rectangle.y;

	cursorLocations.push_back(pos);
	texts.push_back(rectangle);

	//Create quit text + square
	surface = TTF_RenderText_Solid(sansText, "Quit", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.y = 250;
	rectangle.w = 175;
	rectangle.h = 75;
	pos.x = rectangle.x;
	pos.y = rectangle.y;

	cursorLocations.push_back(pos);
	texts.push_back(rectangle);

	DrawCursor();

	isBaseMenuUp = true;
	isPlayerMenuUp = false;
}

void Menu::DrawPlayerSelection()
{
	// Clear previous texts
	texts.clear();
	textures.clear();
	cursorLocations.clear();

	//Section TITLE
	surface = TTF_RenderText_Solid(sansTitle, "player VS player", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = 20;
	rectangle.y = 20;
	rectangle.w = 750;
	rectangle.h = 125;

	texts.push_back(rectangle);

	//Player 1 texts + square
	surface = TTF_RenderText_Solid(sansText, "Player 1", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = 150; // controls the rect's x coordinte
	rectangle.y = 200; // controls the rect's y coordinte
	rectangle.w = 375; // controls the width of the rect
	rectangle.h = 75; // controls the height of the rect

	texts.push_back(rectangle);

	//Player 2 texts + square
	surface = TTF_RenderText_Solid(sansText, "Player 2", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = 725; // controls the rect's x coordinte
	rectangle.w = 375; // controls the width of the rect
	rectangle.h = 75; // controls the height of the rect

	texts.push_back(rectangle);

	//Play button + square
	surface = TTF_RenderText_Solid(sansText, "play!", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = 20;
	rectangle.y = 525;
	rectangle.w = 175;
	rectangle.h = 75;

	pos.x = rectangle.x;
	pos.y = rectangle.y;

	cursorLocations.push_back(pos);
	texts.push_back(rectangle);

	//Back button + square
	surface = TTF_RenderText_Solid(sansText, "Back", white);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	textures.push_back(texture);

	rectangle.x = 20;
	rectangle.y = 600;
	rectangle.w = 175;
	rectangle.h = 75;
	pos.x = rectangle.x;
	pos.y = rectangle.y;

	cursorLocations.push_back(pos);
	texts.push_back(rectangle);

	DrawCursor();

	isBaseMenuUp = false;
	isPlayerMenuUp = true;
}

void Menu::SelectOption()
{
	// Base menu [0 - 9 options
	// Player selection [10 - 19]

	switch (GetSelectedOption())
	{
	case -1:// force Quit
		isRunning = false;
		break;
	case 0:// play local vs game
		DrawPlayerSelection();
		break;
	case 1:// Quit
		isRunning = false;
		break;
	case 10:// Play
		isRunning = false;
		break;
	case 11:// Back
		DrawBaseMenu();
		break;

	default:
		// Failsafe -> quit the game
		isRunning = false;
		break;
	}
}

void Menu::GoCursorUp()
{
	if (cursorPosition >= 0)
	{
		cursorPosition--;
	}
	else 
	{
		cursorPosition = 0;
	}
}

void Menu::GoCursorDown()
{
	if (cursorPosition < cursorLocations.size()-1)
	{
		cursorPosition++;
	}
	else
	{
		cursorPosition = cursorLocations.size()-1;
	}
}

int Menu::GetSelectedOption()
{
	if (selectedOption != -1)
	{
		if (isBaseMenuUp)
			return cursorPosition;
		else if (isPlayerMenuUp)
			return (cursorPosition + 10);
	}
		

	return -1;
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
