#include "Player.h"
#include "Bomb.h"
#include "Game.h"

//Constructors
Player::Player():Entity(0,0)
{
	mPosX = 0.f;
	mPosY = 0.f;
	mVelX = 0.f;
	mVelY = 0.f;

    SDL_GetCurrentDisplayMode(0, &DM);

	// Reserve bombs memory space
	placedBombs.reserve(20);
	//blasts = std::vector<Blast>(80);
}

Player::Player(int x, int y):Entity(x, y)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0.f;
	mVelY = 0.f;

    SDL_GetCurrentDisplayMode(0, &DM);

	// Reserve bombs memory space
	placedBombs.reserve(20);
	//blasts = std::vector<Blast>(80);
}

Player::Player(int x, int y, SDL_Texture *sprite, int textPosX, int textPosY):
	Entity(x, y, sprite, textPosX, textPosY)
{
	mPosX = x;
	mPosY = y;
	mVelX = 0.f;
	mVelY = 0.f;

    SDL_GetCurrentDisplayMode(0, &DM);

	// Reserve bombs memory space
	placedBombs.reserve(20);
	//blasts = std::vector<Blast>(80);

	// Load animation frames

	upSpriteFrames = {
		{72, 20, playerW, playerH},
		{56, 20, playerW, playerH},
		{88, 20, playerW, playerH}
	};
	downSpriteFrames = {
		{71, 45, playerW, playerH},
		{55, 45, playerW, playerH},
		{87, 45, playerW, playerH}
	};
	leftSpriteFrames = {
		{2, 44, playerW, playerH},
		{19, 44, playerW, playerH},
		{35, 44, playerW, playerH}
	};
	rightSpriteFrames = {
		{105, 46, playerW, playerH},
		{121, 47, playerW, playerH},
		{139, 48, playerW, playerH}
	};

	std::cout << "Player created at " << x << ", " << y << "\n";
}

//Gameplay functions
void Player::Update(float delta)
{
	Move(delta);
	AnimatePlayer(delta);
	UpdateBombs(delta);
	UpdateBlasts(delta);
}

void Player::Move(float delta)
{
	lastPosX = mPosX;
	lastPosY = mPosY;

    //Move the player left or right
    mPosX += mVelX * delta;

	//Animate direction x
	if (mVelX > 0)
		playerDirection = 3;
	else if (mVelX < 0)
		playerDirection = 2;

    //Move the player up or down
    mPosY += mVelY * delta;

	//Animate direction y
	if (mVelY > 0)
		playerDirection = 1;
	else if (mVelY < 0)
		playerDirection = 0;

	//Check collisions before moving
	CheckCollisions();

	if (lastPosX != mPosX || lastPosY != mPosY)
	{
		isMoving = true;

		//Apply movement
		Entity::SetX((int)mPosX);
		Entity::SetY((int)mPosY);
	}
	else 
	{
		isMoving = false;
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
			case SDLK_SPACE: SpawnBomb(); break;
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
	//Screen boundaries collision
	//Left - Right
	if (mPosX < 0)
	{
		mPosX = 0;
	}
	else if (mPosX > DM.w - playerW)
	{
		mPosX = DM.w - playerW;
	}

	//Up - Down
	if (mPosY < 0)
	{
		mPosY = 0;
	}
	else if (mPosY > DM.h - playerH)
	{
		mPosY = DM.h - playerH;
	}
}

void Player::SpawnBomb()
{
	if (ammo > 0)
	{
		ammo--;
		Bomb b = Bomb(this, bombTexture);
		placedBombs.push_back(b);
	}
}

void Player::UpdateBombs(float delta)
{
	int bombsSize = placedBombs.size();

	if (bombsSize > 0)
	{
		for (size_t i = 0; i < bombsSize; i++)
			placedBombs[i].Update(delta);
	}
}

void Player::SetGameReference(Game* game)
{
	this->game = game;
}

void Player::DestroyBombReference(Bomb* b)
{
	std::vector<Bomb> newBombs;
	newBombs.reserve(placedBombs.size());
	bool found = false;

	for (size_t i = 0; i < placedBombs.size(); i++)
	{
		if (&placedBombs[i] == b)
		{
			b = nullptr;
			found = true;
		}
		else 
		{
			newBombs.push_back(placedBombs[i]);
		}
	}

	if (found)
	{
		placedBombs = newBombs;
		ammo++;
	}		
}

void Player::UpdateBlasts(float delta)
{
	int explosions = blasts.size();

	if (explosions > 0)
	{
		for (size_t i = 0; i < explosions; i++)
			blasts[i]->Update(delta);
	}
}

void Player::AddBlast(Blast* b)
{
	this->blasts.push_back(b);
}

void Player::SetBlasts(std::vector<Blast*> b)
{
	this->blasts = b;
}

void Player::AnimatePlayer(float delta)
{

	if (isMoving) // Play moving animation
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

			if (animationFrame < 2)
				animationFrame++;
			else
				animationFrame = 1;
		}
	}
	else // Play Idle frame
	{
		switch (playerDirection)
		{
		case 0:
			srcRectangle = upSpriteFrames[0];
			break;

		case 1:
			srcRectangle = downSpriteFrames[0];
			break;

		case 2:
			srcRectangle = leftSpriteFrames[0];
			break;

		case 3:
			srcRectangle = rightSpriteFrames[0];
			break;
		}

		//Reset animation
		animationFrame = 1;
	}

	animationDeltaTime += delta;
}

//Utils functions
std::vector<Bomb> Player::GetBombs()
{
	return placedBombs;
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

void Player::SetBombTexture(SDL_Texture* texture)
{
	bombTexture = texture;
}

//Destructor
Player::~Player()
{
	SDL_DestroyTexture(GetSprite());
}
