#include "Player.h"

//Constructors
Player::Player():Entity(0,0)
{
	mPosX = 0.f;
	mPosY = 0.f;
	mVelX = 0.f;
	mVelY = 0.f;

    SDL_GetCurrentDisplayMode(0, &DM);
}

Player::Player(int x, int y):Entity(x, y)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0.f;
	mVelY = 0.f;

    SDL_GetCurrentDisplayMode(0, &DM);
}

Player::Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY):
	Entity(x, y, sprite, textPosX, textPosY)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0.f;
	mVelY = 0.f;

    SDL_GetCurrentDisplayMode(0, &DM);

	// Load animation frames

	upSpriteFrames = {
		{56, 20, playerH, playerW},
		{73, 20, playerH, playerW},
		{88, 20, playerH, playerW}
	};
	downSpriteFrames = {
		{55, 45, playerH, playerW},
		{71, 45, playerH, playerW},
		{86, 45, playerH, playerW}
	};
	leftSpriteFrames = {
		{2, 44, playerH, playerW},
		{19, 44, playerH, playerW},
		{35, 44, playerH, playerW}
	};
	rightSpriteFrames = {
		{105, 46, playerH, playerW},
		{122, 47, playerH, playerW},
		{137, 48, playerH, playerW}
	};

	std::cout << "Player created at " << x << ", " << y << "\n";
}

//Gameplay functions
void Player::Update(float delta)
{
	Move(delta);
	AnimatePlayer(delta);
    Entity::SetX((int)mPosX);
    Entity::SetY((int)mPosY);
}

void Player::Move(float delta)
{
    //Move the player left or right
    mPosX += mVelX/* * delta*/;

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
    mPosY += mVelY/* * delta*/;

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
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: mVelY -= moveSpeed; break;
			case SDLK_DOWN: mVelY += moveSpeed; break;
			case SDLK_LEFT: mVelX -= moveSpeed; break;
			case SDLK_RIGHT: mVelX += moveSpeed; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += moveSpeed; break;
		case SDLK_DOWN: mVelY -= moveSpeed; break;
		case SDLK_LEFT: mVelX += moveSpeed; break;
		case SDLK_RIGHT: mVelX -= moveSpeed; break;
		}
	}
}

void Player::CheckCollisions()
{
}

void Player::AnimatePlayer(float delta)
{

	if (animationDeltaTime >= timePerAnimation)
	{
		animationDeltaTime = 0;

		switch (playerDirection)
		{
		case 0:
			srcRectangle = upSpriteFrames[animationFrame];
			break;

		case 1:
			srcRectangle = downSpriteFrames[animationFrame];
			break;

		case 2:
			srcRectangle = leftSpriteFrames[animationFrame];
			break;

		case 3:
			srcRectangle = rightSpriteFrames[animationFrame];
			break;
		}
	}

	animationDeltaTime += delta;

	if (animationFrame != 2)
		animationFrame++;
	else
		animationFrame = 0;
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