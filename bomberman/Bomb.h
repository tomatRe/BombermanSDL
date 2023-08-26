#pragma once
#include "Entity.h"
#include "Player.h"
#include "Blast.h"
#include "Map.h"


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
        float GetAliveTime();

        //Setters
        void SetBlastRadius(int);
        void SetOwningPlayer(Player*);
        void SetMap(Map*);

        //=========================Variables=========================
        Player* ownerPlayer;

    private:
        bool IsOverlaping(SDL_Rect rect1, SDL_Rect rect2);

        //Animation vars
        std::vector<SDL_Rect> animationFrames = {
            {170, 528, 17, 17},
            {187, 528, 17, 17},
            {204, 528, 17, 17}
        };

        float animationDeltaTime = 1;
        int animationFrame = 0;

        Map* map;

        //Gameplay vars
        bool exploded = false;
        float aliveTime = 0.f;
        float timeToExplode = 3.f;
        int blastRadius = 1;
};
