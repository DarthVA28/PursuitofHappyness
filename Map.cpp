#include "Map.hpp"
#include "TM.hpp"
#include <vector>
#include "assets/mapwt.h"
#include <iostream>
using namespace std;

int map1[Map::MAP_X*Map::MAP_Y] = MAP_WT;  

Map::Map() {
    dirt = TM::LoadTexture("assets/dirt.png");
    grass = TM::LoadTexture("assets/grass.png");
    campus = TM::LoadTexture("assets/campusv2.png");
    LoadMap(map1);
    setColliders();

    src.x = 0;
    src.y = 0;
    src.h = dest.h = 32;
    src.w = dest.w = 32;
    dest.x = 0;
    dest.y = 0;
}

Map::~Map() {

}

// void Map::DrawMap(){
//     int type = 0;
//     for (int i=0; i<20; i++) {
//         for (int j=0; j<25; j++) {
            
//             dest.x = 32*j;
//             dest.y = 32*i;

//             type = map[i*j];
//             switch(type) {
//                 case 0: 
//                     TM::Draw(dirt,src,dest);
//                     break;
//                 case 1: 
//                     TM::Draw(grass,src,dest);
//                     break;
//                 default:
//                     break;
//             }
//         }
//     }
// }

void Map::DrawMap(int camx, int camy){
    src.x = 0;
    src.y = 0;
    dest.x = -camx;
    dest.y = -camy;
    src.h = Map::MAP_Y*32;
    src.w = Map::MAP_X*32;
    dest.h = src.h*2;
    dest.w = src.w*2;   
    TM::Draw(campus,src,dest);
}

void Map::LoadMap(int arr[Map::MAP_X*Map::MAP_Y]) {
    for (int i=0; i<Map::MAP_X*Map::MAP_Y; i++) {
            map[i] = arr[i];
    }
}

void Map::setColliders() {
    int count = 0;
    for (int j = 0; j<Map::MAP_X; j++) {
        for (int i=0; i<Map::MAP_Y; i++) {
            if (map[Map::MAP_X*i + j] == 30) {
                Map::Colliders[count] = new Tuple(j,i);
                cout << "Set" << j << ", " << i << " " << std::endl;
                count++;
            }
        }
    }
}

void Map::Collisions(int camx, int camy, Object* player){
    
}