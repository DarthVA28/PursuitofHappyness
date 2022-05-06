#pragma once
#include "Game.hpp"
#include "Tuple.hpp"
#include "NPC.hpp"
#include "PowerUp.hpp"
#include "Chance.hpp"
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
    void objMove(int dir, SDL_Rect b, Tuple* Colliders[], NPC* activeNPC[], int num_NPC, Chance* activeChance[], PowerUp* activePUPS[]);
    void addItems(string str);
    void addPowerUps(string str);
    bool removeItems(string str);
    void removeTasks(string str);
    void removePowerUps(string str);
    void addTasks(string str);
    void changeFrame(int dir);
    void toggleYulu();
    void updateHappyness();
    void objTeleport(int location);
    void randomTeleport(int location);

    bool inMotion;
    bool gotChance;
    bool Yulu;
    bool checkCollision(SDL_Rect b);
    bool checkTileCollision(int x, int y);

    string inventoryItems[5];
    string powerUps[2];
    string tasks[5];

    int frame;
    int numInventoryItems;
    int getx();
    int gety();
    int getHappyness();
    string hunger ;
    string money ;
    string taskDone ;
    int activePowerUp;

    string getIElem(string s[], int i);
    SDL_Rect getCollider();

private:

    int xpos;
    int ypos;
    int velocity;
    int happyness; //from pursuit of Happyness

    SDL_Texture* objTexture;
    SDL_Rect textureSheet[24];
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

    SDL_Rect mCollider;

};
