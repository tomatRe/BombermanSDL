#pragma once
#include "Entity.h"
#include "Player.h"
#include "Blast.h"


class Bomb : public Entity
{
    public:
        //=========================Functions=========================

        //Constructor / Destructor
        Bomb();
        Bomb(Player*, SDL_Texture*);
        ~Bomb();

        //Tick functions
        void Update(float);
        void Animate(float);

        void Detonate();

        //Getters
        SDL_Rect* GetSrcRectangle();
        SDL_Rect* GetDestRectangle();
        Player* GetOwningPlayer();

        //Setters
        void SetOwningPlayer(Player*);

        //=========================Variables=========================
        Player* ownerPlayer;

    private:

        //Animation vars
        std::vector<SDL_Rect> animationFrames = {
            {170, 528, 17, 17},
            {187, 528, 17, 17},
            {204, 528, 17, 17}
        };

        SDL_Rect* blastOriginSprite = new SDL_Rect{ 170, 528, 17, 17 };
        SDL_Rect* blastTopSprite = new SDL_Rect{ 170, 528, 17, 17 };
        SDL_Rect* blastBottomSprite = new SDL_Rect{ 170, 528, 17, 17 };
        SDL_Rect* blastLeftSprite = new SDL_Rect{ 170, 528, 17, 17 };
        SDL_Rect* blastRightSprite = new SDL_Rect{ 170, 528, 17, 17 };

        float animationDeltaTime = 1;
        int animationFrame = 0;

        //Gameplay vars
        bool exploded = false;
        float aliveTime = 0.f;
        float timeToExplode = 3.f;
        int blastRadius = 1;
};
