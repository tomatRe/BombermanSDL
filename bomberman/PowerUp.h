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
    float srcRects[3][2] = {
        {321, 14},
        {321, 14},
        {321, 14}
    };

    //Movement
    const float moveSpeed = 0.07f;
    float mPosY;
    float mVelY;

    //Gameplay vars
    float aliveTime = 0.f;
    float maxAliveTime = 30.f;
};

