#pragma once
#include "Game.hpp"

class Object {

public:
    Object(const char* texturesheet, int xpos, int ypos);
    ~Object();

    void objUpdate();
    void objRender();
    void objRender(int camx, int camy);
    void objMove(int dir);
    void objMove(int dir, SDL_Rect b);
    bool checkCollision(SDL_Rect b);
    int getx();
    int gety();
    SDL_Rect getCollider();

private:

    int xpos;
    int ypos;
    int velocity;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    SDL_Rect mCollider;

};