#include "Player.h"

//Constants
const int playerW = 14;
const int playerH = 22;

//Movement
static const int moveSpeed = 300;
float mPosX, mPosY;
float mVelX, mVelY;

//Screen boundaries
SDL_DisplayMode DM;

//Constructors
Player::Player():Entity(0,0)
{
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;

    SDL_GetCurrentDisplayMode(0, &DM);
}

Player::Player(int x, int y):Entity(x, y)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0;
	mVelY = 0;

    SDL_GetCurrentDisplayMode(0, &DM);
}

Player::Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY):
	Entity(x, y, playerW*2, playerH*2, sprite, textPosX, textPosY, playerW, playerH)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0;
	mVelY = 0;

    SDL_GetCurrentDisplayMode(0, &DM);

	std::cout << "Player created at " << x << ", " << y << "\n";
}

//Gameplay functions
void Player::Update(float delta)
{
    Entity::SetX((int)mPosX);
    Entity::SetY((int)mPosY);
}

void Player::Move(float delta)
{
    //Move the player left or right
    mPosX += mVelX * delta;

    //If the player went too far to the left or right
    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX > DM.w - playerW)
    {
        mPosX = DM.w - playerW;
    }

    //Move the player up or down
    mPosY += mVelY * delta;

    //If the player went too far up or down
    if (mPosY < 0)
    {
        mPosY = 0;
    }
    else if (mPosY > DM.h - playerH)
    {
        mPosY = DM.h - playerH;
    }
}

void Player::HandleEvents(SDL_Event& e)
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