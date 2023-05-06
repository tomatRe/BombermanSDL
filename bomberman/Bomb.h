#pragma once
#include "Entity.h"
#include "Player.h"

class Bomb : public Entity
{
    public:
        Bomb(Player*, SDL_Texture*);
        ~Bomb();
        void Update(float delta);
        void Detonate();
        Player* GetOwningPlayer();
        Player* SetOwningPlayer(Player*);

        SDL_Texture* GetSprite();
        SDL_Rect* GetSrcRectangle();
        SDL_Rect* GetDestRectangle();

        Player* ownerPlayer;

    private:
        float aliveTime = 0.f;
        float timeToExplode = 3.0f;
        int blastRadius = 1;
};

