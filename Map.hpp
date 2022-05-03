#pragma once 
#include "Game.hpp"
#include "Object.hpp"
#include <vector>
#include "Tuple.hpp"
using std::vector;

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
    void setColliders();
    void Collisions(int camx, int camy, Object* player);

private: 

    SDL_Rect src,dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* campus;

    int map[MAP_X*MAP_Y];
};
