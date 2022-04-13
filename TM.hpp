#pragma once 
#include "Game.hpp"

class TM {

public:
    static SDL_Texture* LoadTexture(const char* file);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};