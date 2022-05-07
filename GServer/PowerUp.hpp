#pragma once
#include "Game.hpp"
#include "Tuple.hpp"
#include <string>
using std::string;

class PowerUp {

public:
    PowerUp(int type, int xpos, int ypos);
    ~PowerUp();

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
