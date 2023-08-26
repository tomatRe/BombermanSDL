#pragma once
#include "Entity.h"
#include "Player.h"

class PowerUp : public Entity
{
public:
    //=========================Functions=========================

    //Constructor / Destructor
    PowerUp(float, float, SDL_Texture*);
    ~PowerUp();

    //Tick functions
    void Update(float);

    //Getters / setters
    int GetProperty();
    float GetAliveTime();
    float GetMaxAliveTime();
    void SetProperty(std::vector<bool>);

    //=========================Variables=========================
    int propertyNum = 0;
    std::vector<bool> property
    {
        false, // IncreaseBlast
        false, // IncreaseSpeed
        false, // IncreaseAmmo
    };

private:
    struct srcRects
    {
        SDL_Rect blastUpgrade = SDL_Rect{ 299, 322, 17, 17 };
        SDL_Rect speedUpgrade = SDL_Rect{ 350, 322, 17, 17 };
        SDL_Rect ammoUpgrade = SDL_Rect{ 367, 322, 17, 17 };
    };

    //Movement
    const float moveSpeed = 0.07f;
    float mPosY;
    float mVelY;

    //Gameplay vars
    float aliveTime = 0.f;
    float maxAliveTime = 30.f;
};

