#include "Player.h"

const int playerW = 14;
const int playerH = 22;

Player::Player():Entity(0,0)
{}

Player::Player(int x, int y):Entity(x, y)
{}

Player::Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY, int textSizeX, int textSizeY):
	Entity(x, y, playerW, playerH, sprite, textPosX, textPosY, textSizeX, textSizeY)
{
	std::cout << "Player created at " << x << ", " << y << "\n";
}

SDL_Texture * Player::GetSprite()
{
	return sprite;
}

SDL_Rect* Player::GetSrcRectangle()
{
	return &srcRectangle;
}

SDL_Rect* Player::GetDestRectangle()
{
	return &destRectangle;
}

Player::~Player()
{
}