#pragma once
#include "Game.hpp"
#include "Tuple.hpp"
#include <string>
using std::string;

class Chance {

public:
    Chance(int xpos, int ypos);
    ~Chance();

    void objUpdate();
    void objRender();
    void onCollision();

    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
    int getID();

    SDL_Rect getCollider();


private:

    int xpos;
    int ypos;
    int ID;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    SDL_Rect mCollider;

};
