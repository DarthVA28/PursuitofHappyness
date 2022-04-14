#pragma once 
#include "Game.hpp"

class Map {

public:

    static const int MAP_X = 20;
    static const int MAP_Y = 25;

    Map();
    ~Map();

    void LoadMap(int arr[MAP_X][MAP_Y]);
    void DrawMap();
    void DrawMap(int camx, int camy);

private: 

    SDL_Rect src,dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;

    int map[MAP_X][MAP_Y];

};
