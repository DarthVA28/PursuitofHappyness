#pragma once 
#include "Game.hpp"
#include "Object.hpp"
#include <vector>
#include "Tuple.hpp"
#include <string>

using std::vector;
using std::string;

class Map {

public:
    static const int MAP_X = 220;
    static const int MAP_Y = 130;
    static const int BARRIERS = 2639;
    Tuple* Colliders[2639];

    Map();
    ~Map();

   void LoadMap(int arr[MAP_X*MAP_Y]);
    void DrawMap();
    void DrawMap(int camx, int camy);
    
    void DrawHappinessBarU();
    void DrawHappinessBarO(int score); 
    void DrawplayerOneScore();
    void Drawitems(string item, int i);
    void DrawMenu(string menu);
    void DrawPowerUps( string powerUp, int i) ;
   
    void setColliders();
    void Collisions(int camx, int camy, Object* player);
    const char* getRegion(int x, int y);
private: 

SDL_Rect src,dest;
    SDL_Rect Happysrc,Happydest;
    SDL_Rect itemsrc,itemdest;
    SDL_Rect powerUpsrc,powerUpdest;
    SDL_Rect menusrc,menudest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* campus;
    SDL_Texture* HappinessBarU;
    SDL_Texture* HappinessBarO;
    SDL_Texture* playerOneScore;
    SDL_Texture* item1;
    SDL_Texture* item2;
    SDL_Texture* item3;
    SDL_Texture* item4;
    SDL_Texture* item5;
    SDL_Texture* menu1;
    SDL_Texture* menu2;
    SDL_Texture* hammer;
    SDL_Texture* teleport;
    SDL_Texture* phone;
    SDL_Texture* shoes;
    SDL_Texture* camera;
    SDL_Texture* pendant;
    SDL_Texture* passes;
    SDL_Texture* cones;
    SDL_Texture* water;
    SDL_Texture* facche;
    SDL_Texture* key;
    SDL_Texture* laptop;
    SDL_Texture* refreshments;
    SDL_Texture* refreshmentsmain;
    SDL_Texture* cash;
    SDL_Texture* clothes;


    int map[MAP_X*MAP_Y];
};
