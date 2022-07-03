#include "Player.h"

//Constants
const int playerW = 14;
const int playerH = 22;

//Constructors
Player::Player():Entity(0,0)
{}

Player::Player(int x, int y):Entity(x, y)
{}

Player::Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY):
	Entity(x, y, playerW*2, playerH*2, sprite, textPosX, textPosY, playerW, playerH)
{
	std::cout << "Player created at " << x << ", " << y << "\n";
}

//Gameplay functions
void Player::Update(float delta)
{
	
}

void Player::Move()
{
}

void Player::CheckInput()
{
}

void Player::CheckCollisions()
{
}

//Utils functions
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

//Destructor
Player::~Player()
{
}