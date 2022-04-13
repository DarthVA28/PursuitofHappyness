#include "Map.hpp"
#include "TM.hpp"

int map1[20][25] = { 0 };

Map::Map() {
    dirt = TM::LoadTexture("assets/dirt.png");
    grass = TM::LoadTexture("assets/grass.png");
    LoadMap(map1);

    src.x = 0;
    src.y = 0;
    src.h = dest.h = 32;
    src.w = dest.w = 32;
    dest.x = 0;
    dest.y = 0;
}

Map::~Map() {

}

void Map::DrawMap(){
    int type = 0;
    for (int i=0; i<20; i++) {
        for (int j=0; j<25; j++) {
            
            dest.x = 32*j;
            dest.y = 32*i;

            type = map[i][j];
            switch(type) {
                case 0: 
                    TM::Draw(dirt,src,dest);
                    break;
                case 1: 
                    TM::Draw(grass,src,dest);
                    break;
                default:
                    break;
            }
        }
    }
}

void Map::LoadMap(int arr[20][25]) {
    for (int i=0; i<20; i++) {
        for (int j=0; j<25; j++) {
            map[i][j] = arr[i][j];
        }
    }
}