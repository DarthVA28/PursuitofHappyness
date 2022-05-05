#pragma once
#include "Game.hpp"
#include "Tuple.hpp"
#include <string>
using std::string;

class NPC {

public:
    NPC(const char* texturesheet, int xpos, int ypos, string npc_id);
    ~NPC();

    bool inMotion;
    int frame;

    void objUpdate();
    void objRender();
    void NPCMove(Tuple* Colliders[], int xtarget, int ytarget);
    bool objMove(int dir, Tuple* Colliders[]);
    void changeFrame(int dir);
    void onCollision();

    bool checkCollision(SDL_Rect b);
    bool checkTileCollision(int x, int y);

    int getx();
    int gety();
    string getID();

    SDL_Rect getCollider();

private:

    int xpos;
    int ypos;
    int velocity;
    string ID;

    SDL_Texture* objTexture;
    SDL_Rect textureSheet[16];
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    SDL_Rect mCollider;

};
