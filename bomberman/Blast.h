#pragma once
#include "Entity.h"

class Blast : Entity
{
public:
    Blast();
    Blast(int x, int y, SDL_Rect* sprite);
    void Update(float delta);

    SDL_Rect* sprite;
};
