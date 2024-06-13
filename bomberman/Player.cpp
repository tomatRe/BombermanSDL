#include "Player.h"
#include "Bomb.h"
#include "Game.h"
#include "PowerUp.h"

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
	blasts.reserve(200);

	std::cout << "Player created at " << x << ", " << y << "\n";
}


//Tick functions
void Player::Update(float delta)
{
	if (isAlive)
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

void Player::AnimatePlayer(float delta)
{

	if (isAlive && isMoving) // Play moving animation
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
	else if (!isMoving && isAlive) // Play Idle frame
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
	else 
	{
		if (animationDeltaTime >= timePerAnimation)
		{
			animationDeltaTime = 0;
			srcRectangle = dieSpriteFrames[animationFrame];

			if (animationFrame < dieSpriteFrames.size()-1)
				animationFrame++;
		}
	}

	animationDeltaTime += delta;
}

void Player::UpdateBombs(float delta)
{
	if (placedBombs.size() > 0)
	{
		for (size_t i = 0; i < placedBombs.size(); i++)
			placedBombs[i]->Update(delta);
	}
}

void Player::UpdateBlasts(float delta)
{
	if (blasts.size() > 0)
	{
		for (size_t i = 0; i < blasts.size(); i++)
		{
			blasts[i]->Update(delta);
		}
	}
}

void Player::HandleEvents(SDL_Event& e)
{
	if (isAlive && playerNumber == 0)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{ 
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w:	 mVelY = -moveSpeed; break;
			case SDLK_s:	 mVelY =  moveSpeed; break;
			case SDLK_a:     mVelX = -moveSpeed; break;
			case SDLK_d:     mVelX =  moveSpeed; break;
			case SDLK_SPACE: SpawnBomb();	     break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY = 0; break;
			case SDLK_s: mVelY = 0; break;
			case SDLK_a: mVelX = 0; break;
			case SDLK_d: mVelX = 0; break;
			}
		}
	}

	if (isAlive && playerNumber == 1)
	{
		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:	 mVelY = -moveSpeed; break;
			case SDLK_DOWN:  mVelY = moveSpeed;  break;
			case SDLK_LEFT:  mVelX = -moveSpeed; break;
			case SDLK_RIGHT: mVelX = moveSpeed;  break;
			case SDLK_RCTRL: SpawnBomb();		 break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:	 mVelY = 0; break;
			case SDLK_DOWN:  mVelY = 0; break;
			case SDLK_LEFT:  mVelX = 0; break;
			case SDLK_RIGHT: mVelX = 0; break;
			}
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
	//TODO Fit to grid system
	if (ammo > 0)
	{
		ammo--;
		Bomb* b = new Bomb(this, bombTexture);
		b->SetBlastRadius(blastRadius);
		placedBombs.push_back(b);
	}
}

void Player::DestroyBombReference(Bomb* b)
{
	const auto& removed_iterator = std::find(placedBombs.begin(), placedBombs.end(), b);

	if (removed_iterator != placedBombs.end())
	{
		placedBombs.erase(removed_iterator);
		ammo++;
		delete b;
	}
}

void Player::DestroyBlastReference(Blast* b)
{
	const auto& removed_iterator = std::find(blasts.begin(), blasts.end(), b);

	if (removed_iterator != blasts.end())
	{
		blasts.erase(removed_iterator);
		delete b;
	}
}

void Player::AddBlast(Blast* b)
{
	this->blasts.push_back(b);
}

void Player::LevelUp(PowerUp p)
{
	if (p.GetProperty() == 0)
	{
		blastRadius++;
	}
	else if (p.GetProperty() == 1 && moveSpeed < maxMoveSpeed)
	{
		moveSpeed += moveUpgradeIncrement;
	}
	else
	{
		maxAmmo++;
		ammo++;
	}
}

void Player::Die()
{
	isAlive = false;
	isMoving = false;
	animationFrame = 0;
	animationDeltaTime = 0;
}


//Getters
std::vector<Bomb*> Player::GetBombs()
{
	return placedBombs;
}

std::vector<Blast*> Player::GetBlasts()
{
	return blasts;
}

SDL_Texture * Player::GetSprite()
{
	return sprite;
}

SDL_Texture* Player::GetBombSprite()
{
	return bombTexture;
}

SDL_Rect* Player::GetSrcRectangle()
{
	return &srcRectangle;
}

SDL_Rect* Player::GetDestRectangle()
{
	return &destRectangle;
}


//Setters
void Player::SetGameReference(Game* game)
{
	this->game = game;
}

void Player::SetBombTexture(SDL_Texture* texture)
{
	bombTexture = texture;
}

void Player::SetBlasts(std::vector<Blast*> b)
{
	this->blasts = b;
}

void Player::SetSkinOffset(int x, int y)
{
	this->xSkinOffset = x;
	this->ySkinOffset = y;
	UpdateSkinOffset();
}

void Player::UpdateSkinOffset()
{
	this->upSpriteFrames = {
		{72 + xSkinOffset, 20 + ySkinOffset, playerW, playerH},
		{56 + xSkinOffset, 20 + ySkinOffset, playerW, playerH},
		{88 + xSkinOffset, 20 + ySkinOffset, playerW, playerH}
	};

	this->downSpriteFrames = {
		{71 + xSkinOffset, 45 + ySkinOffset, playerW, playerH},
		{55 + xSkinOffset, 45 + ySkinOffset, playerW, playerH},
		{87 + xSkinOffset, 45 + ySkinOffset, playerW, playerH}
	};

	this->leftSpriteFrames = {
		{2 + xSkinOffset, 44 + ySkinOffset, playerW, playerH},
		{19 + xSkinOffset, 44 + ySkinOffset, playerW, playerH},
		{35 + xSkinOffset, 44 + ySkinOffset, playerW, playerH}
	};

	this->rightSpriteFrames = {
		{105 + xSkinOffset, 46 + ySkinOffset, playerW, playerH},
		{122 + xSkinOffset, 47 + ySkinOffset, playerW, playerH},
		{139 + xSkinOffset, 48 + ySkinOffset, playerW, playerH}
	};

	this->dieSpriteFrames = {
		{29 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
		{48 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
		{65 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
		{82 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
		{99 + xSkinOffset, 74 + ySkinOffset, playerW, playerH},
		{117 + xSkinOffset, 74 + ySkinOffset, playerW, playerH}
	};
}

//Destructor
Player::~Player()
{
	SDL_DestroyTexture(GetSprite());
}
