#pragma once
#include "Entity.h"
#include "Player.h"
#include "Blast.h"


class Bomb : public Entity
{
    public:
        Bomb(Player*, SDL_Texture*);
        ~Bomb();
        void Update(float delta);
        void Detonate();
        Player* GetOwningPlayer();
        void SetOwningPlayer(Player*);

        SDL_Texture* GetSprite();
        SDL_Rect* GetSrcRectangle();
        SDL_Rect* GetDestRectangle();

        Player* ownerPlayer;

    private:
        void Animate(float delta);

        //Animation vars
        std::vector<SDL_Rect> animationFrames;
        SDL_Rect* blastOriginSprite;
        SDL_Rect* blastTopSprite;
        SDL_Rect* blastBottomSprite;
        SDL_Rect* blastLeftSprite;
        SDL_Rect* blastRightSprite;
        float animationDeltaTime = 1;
        int animationFrame = 0;

        //Gameplay vars
        bool exploded = false;
        float aliveTime = 0.f;
        float timeToExplode = 3.f;
        int blastRadius = 1;
        std::vector<Blast*> blasts;
};
