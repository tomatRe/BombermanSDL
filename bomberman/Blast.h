#pragma once
#include "Entity.h"
#include "Player.h"

class Blast : Entity
{
    public:
        //=========================Functions=========================

        //Constructors / Destructor
        Blast();
        ~Blast();
        Blast(int x, int y, SDL_Rect* sprite);

        //Tick functions
        void Update(float);
        void Animate(float);

        //Getters
        SDL_Rect* GetSrcRectangle();
        SDL_Rect* GetDestRectangle();

        //Setters
        void SetOwnerPlayer(Player*);

        //=========================Variables=========================

        Player* ownerPlayer;
    private:
        SDL_Rect* sprite;
        float aliveTime = 0.f;
        float timeToDisapear = 1.f;
};
