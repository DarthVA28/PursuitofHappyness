#pragma once
#include "Game.hpp"

class Object {

public:
    Object(const char* texturesheet, int xpos, int ypos);
    ~Object();

    void objUpdate();
    void objRender();
    void objMove(int dir);
    void objMove(int dir, SDL_Rect b);
    bool checkCollision(SDL_Rect b);
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