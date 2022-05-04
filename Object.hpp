#pragma once
#include "Game.hpp"
#include "Tuple.hpp"
#include <string>

using std::string;
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
      string inventoryItems[5];
     void addItems(string str);
    int numInventoryItems;
    int getx();
    int gety();
    string getIElem(string s[], int i);
    SDL_Rect getCollider();
    void changeFrame(int dir);
    bool inMotion;

private:

    int xpos;
    int ypos;
    int velocity;
    int frame;

    SDL_Texture* objTexture;
    SDL_Rect textureSheet[16];
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    SDL_Rect mCollider;

};
