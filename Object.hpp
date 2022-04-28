#pragma once
#include "Game.hpp"
#include "Tuple.hpp"

class Object {

public:
    Object(const char* texturesheet, int xpos, int ypos);
    ~Object();

    void objUpdate();
    void objRender();
    void objRender(int camx, int camy);
    void objMove(int dir);
    void objMove(int dir, SDL_Rect b, Tuple* Colliders[]);
    bool checkCollision(SDL_Rect b);
    bool checkTileCollision(int x, int y);
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