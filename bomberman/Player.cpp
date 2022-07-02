#include "Player.h"

Player::Player()
{
	Entity::x = 0;
	Entity::y = 0;
}

Player::Player(int x, int y):Entity(x, y)
{
}

Player::Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY):Entity(x, y, sprite, textPosX, textPosY, textSizeX, textSizeY)
{
	std::cout << "Player created at " << x << ", " << y << "\n";
}

SDL_Texture * Player::GetSprite()
{
	return sprite;
}

SDL_Rect* Player::GetTextureRectangle()
{
	return &textureRectangle;
}

SDL_Rect* Player::GetScreenRectangle()
{
	return &screenRectangle;
}

Player::~Player()
{
}