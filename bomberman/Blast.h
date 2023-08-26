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
        float GetAliveTime();

        //Setters
        void SetOwnerPlayer(Player*);
        void SetAnimation(std::vector<SDL_Rect*>);

        //=========================Variables=========================

        struct blastDirection
        {
            std::vector<SDL_Rect*> center = {
                new SDL_Rect{ 282, 373, 17, 17 },
                new SDL_Rect{ 333, 356, 17, 17 },
                new SDL_Rect{ 316, 356, 17, 17 },
                new SDL_Rect{ 299, 356, 17, 17 },
                new SDL_Rect{ 282, 356, 17, 17 }
            };

            std::vector<SDL_Rect*> up = { 
                new SDL_Rect{ 282, 339, 17, 17 },
                new SDL_Rect{ 299, 339, 17, 17 },
                new SDL_Rect{ 316, 339, 17, 17 },
                new SDL_Rect{ 333, 339, 17, 17 },
                new SDL_Rect{ 333, 322, 17, 17 }
            };

            std::vector<SDL_Rect*> down = { 
                new SDL_Rect{ 265, 339, 17, 17 },
                new SDL_Rect{ 282, 390, 17, 17 },
                new SDL_Rect{ 299, 390, 17, 17 },
                new SDL_Rect{ 316, 390, 17, 17 },
                new SDL_Rect{ 333, 390, 17, 17 }
            };

            std::vector<SDL_Rect*> left = { 
                new SDL_Rect{ 214, 322, 17, 17 },
                new SDL_Rect{ 231, 322, 17, 17 },
                new SDL_Rect{ 248, 322, 17, 17 },
                new SDL_Rect{ 265, 322, 17, 17 },
                new SDL_Rect{ 282, 322, 17, 17 }
            };

            std::vector<SDL_Rect*> right = { 
                new SDL_Rect{ 265, 373, 17, 17 },
                new SDL_Rect{ 265, 356, 17, 17 },
                new SDL_Rect{ 231, 390, 17, 17 },
                new SDL_Rect{ 231, 373, 17, 17 },
                new SDL_Rect{ 231, 356, 17, 17 }
            };

            std::vector<SDL_Rect*> horizontalBody = {
                new SDL_Rect{ 248, 373, 17, 17 },
                new SDL_Rect{ 248, 356, 17, 17 },
                new SDL_Rect{ 214, 390, 17, 17 },
                new SDL_Rect{ 214, 373, 17, 17 },
                new SDL_Rect{ 214, 356, 17, 17 }
            };

            std::vector<SDL_Rect*> verticalBody = {
                new SDL_Rect{ 265, 390, 17, 17 },
                new SDL_Rect{ 248, 390, 17, 17 },
                new SDL_Rect{ 333, 373, 17, 17 },
                new SDL_Rect{ 316, 373, 17, 17 },
                new SDL_Rect{ 299, 373, 17, 17 }
            };
        };

        Player* ownerPlayer;
    private:
        SDL_Rect* sprite;
        std::vector<SDL_Rect*> animationSet;

        float aliveTime = 0.f;
        float timeToDisapear = 0.5f;

        int animationFrame = 0;
        float animationDeltaTime = 0.f;
};
