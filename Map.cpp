#include "Map.hpp"
#include "TM.hpp"
#include <vector>
#include "assets/mapwt.h"
#include <iostream>
#include <string>
#include "Rect.hpp"
#include "LRect.hpp"
#include "Sq.hpp"
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
                // cout << "Set" << j << ", " << i << " " << std::endl;
                count++;
            }
        }
    }
    Map::Colliders[count] = new Tuple(47,123);
    count++;
    Map::Colliders[count] = new Tuple(48,123);
    count++;
    cout << count << endl;
}

void Map::Collisions(int camx, int camy, Object* player){
    
}

string Map::getRegion(int x, int y) {
    /* Region cases */

    // HOSTELS
    Rect *Jwala = new Rect(12504,5248,12504,4736);
    Rect *Ara = new Rect(12504,4544,12504,3840);
    Rect *Kara = new Rect(12504,3584,12504,3008);
    Rect *Nilgiri = new Rect(12504,2880,12504,2240);
    Rect *Nal = new Rect(12312,2880,12312,2560);
    Rect *AraNM = new Rect(12752,3712,12752,3776);
    Rect *Satpura1 = new Rect(9032,4272,9412,4272);
    Rect *Satpura2 = new Rect(9412,4272,9412,4532);
    Rect *Satpura3 = new Rect(9412,4532,9772,4532);
    Rect *Kum1 = new Rect(12292, 5172,12292, 4672);
    Rect *Kum2 = new Rect(12292, 4672, 11732, 4672);
    Rect *Vindy1 = new Rect(11472, 4732, 11472, 4532);
    Rect *Vindy2 = new Rect(11472, 4532, 10872, 4532);
    Rect *Shiva = new Rect(11472, 4412, 11472, 4032);
    Rect *Zan1 = new Rect(11292, 3332, 11292, 3712);
    Rect *Zan2 = new Rect(11212, 3332, 11212, 3392);
    Rect *Girnar = new Rect(8972, 4212, 8972, 3812);
    Rect *Udai = new Rect(8972, 3692, 8972, 3552);
    Rect *Sapt = new Rect(9992, 3332,9992, 3952);
    Rect *Kailash = new Rect(3072, 6932, 3072, 7492);
    Rect *Him = new Rect(3072, 7652,3072, 7792);

    // BUILDINGS 
    Rect *NewLHC1 = new Rect(4432, 6792,5312, 6792);
    Rect *NewLHC2 = new Rect(5312, 6792,5312, 6272);
    Rect *Textile = new Rect(5292, 6172,5292, 5492);
    Rect *DOD = new Rect(5072, 4612,5072, 4492);
    Rect *SBI = new Rect(4432, 5312,4992, 5312);
    Rect *Staff = new Rect(5332, 3632,5332, 2432);
    Rect *Lib1 = new Rect(5652, 4432,6012, 4432);
    Rect *Lib2 = new Rect(6232, 4432, 6972, 4432);
    Rect *LibEnt = new Rect(6452, 4492, 6572, 4492);
    Rect *Nescafe = new Rect(6072, 4492,6192, 4492);
    Rect *Amul1 = new Rect(7032, 4432, 7192, 4432);
    Rect *Amul2 = new Rect(7232, 4492, 7232, 3972);
    Rect *Shiru = new Rect(7172, 3852, 7172, 3712);
    Rect *Exhall = new Rect(7292, 4912, 7292, 5512);
    Rect *SIT = new Rect(7752, 3792, 8132, 3792);
    Rect *Bharti2 = new Rect(7352, 3132, 8152, 3132);
    Rect *Hospital = new Rect(8372, 3132, 8912, 3132);
    Rect *MasalaMix = new Rect(10112, 3192, 10112, 3452);
    Rect *Chaayos = new Rect(10112, 3492, 10112, 3552);
    Rect *Rajdhani = new Rect(10112, 3572, 10112, 3752);

    // LARGE BUILDINGS 
    LRect *RedSq = new LRect(7312, 3832,8192, 4852);
    LRect *MainB = new LRect(5552, 4872,7232, 5552);
    LRect *Biotech = new LRect(5572, 5652,7212, 6832);
    LRect *MLawn = new LRect(7752, 5572, 8125, 6132);
    LRect *CSC = new LRect(6572, 4592,7232, 4872);
    LRect *Bharti1 = new LRect(7312, 3132, 7712, 3792);
    LRect *SAC = new LRect(10572, 952, 11512, 2432);
    LRect *Parking = new LRect(9732, 1472, 9972, 2772);
    LRect *Grounds = new LRect(5372, 1852, 9692, 2932);

    // YULU STANDS 
    // Rect *YHim = new Rect(3072, 7592, 3072, 7612);
    // Rect *YLHC = new Rect(5052, 5252,5332, 5252);
    // Rect *YHos = new Rect(9772, 3032, 9992, 3032);
    // Rect *YSac = new Rect(11572, 2412, 11572, 2492);

    // Circles 
    Sq *CVin = new Sq(11552, 4632);
    Sq *CHim = new Sq(5472, 6872);
    Sq *CSac = new Sq(11552, 3092);
    Sq *CJwl = new Sq(12412, 4632);

    if (Jwala->inside(x,y)) {
        return "JWALAMUKHI";
    } else if (Ara->inside(x,y)){
        return "ARAVALI";
    } else if (Kara->inside(x,y)){
        return "KARAKORAM";
    } else if (Nilgiri->inside(x,y)){
        return "NILGIRI";
    } else if (AraNM->inside(x,y)){
        return "ARAVALI NIGHT MESS";
    } else if (Satpura1->inside(x,y) || Satpura2->inside(x,y) || Satpura3->inside(x,y)) {
        return "SATPURA";
    } else if (Kum1->inside(x,y) || Kum2->inside(x,y)) {
        return "KUMAON";
    } else if (Vindy1->inside(x,y) || Vindy2->inside(x,y)) {
        return "VINDYANCHAL";
    } else if (Shiva->inside(x,y)) {
        return "SHIVALIK";
    } else if (Zan1->inside(x,y) || Zan2->inside(x,y)){
        return "ZANSKAR";
    } else if (Girnar->inside(x,y)){
        return "GIRNAR";
    } else if (Udai->inside(x,y)){
        return "UDAIGIRI";
    } else if (Sapt->inside(x,y)){
        return "SAPTAGIRI";
    } else if (Kailash->inside(x,y)){
        return "KAILASH";
    } else if (Him->inside(x,y)){
        return "HIMADRI";
    } else if (NewLHC1->inside(x,y) || NewLHC2->inside(x,y)){
        return "NEW LHC";
    } else if (Textile->inside(x,y)){
        return "TEXTILE DEPT.";
    } else if (DOD->inside(x,y)){
        return "DEPT. OF DESIGN";
    } else if (SBI->inside(x,y)){
        return "SBI";
    } else if (Nal->inside(x,y)){
        return "NALANDA APARTMENTS";
    } else if (Staff->inside(x,y)){
        return "STAFF CANTEEN";
    } else if (Lib1->inside(x,y) || Lib2->inside(x,y)){
        return "CENTRAL LIBRARY";
    } else if (LibEnt->inside(x,y)){
        return "LIBRARY ENTRANCE";
    } else if (Nescafe->inside(x,y)){
        return "NESCAFE";
    } else if (Amul1->inside(x,y) || Amul2->inside(x,y)){
        return "AMUL";
    } else if (Shiru->inside(x,y)){
        return "SHIRU CAFE";
    } else if (Exhall->inside(x,y)){
        return "EXHALL";
    } else if (SIT->inside(x,y)){
        return "SCHOOL OF IT";
    } else if (Bharti2->inside(x,y) || Bharti1->inside(x,y)){
        return "BHARTI BUILDING";
    } else if (Hospital->inside(x,y)){
        return "IITD HOSPITAL";
    } else if (MasalaMix->inside(x,y)){
        return "MASALA MIX";
    } else if (Chaayos->inside(x,y)){
        return "CHAAYOS";
    } else if (Rajdhani->inside(x,y)){
        return "RAJDHANI";
    } else if (RedSq->inside(x,y)){
        return "RED SQUARE";
    } else if (MainB->inside(x,y)){
        return "MAIN BUILDING";
    } else if (Biotech->inside(x,y)){
        return "BIOTECH LAWNS";
    } else if (MLawn->inside(x,y)){
        return "MECH LAWN";
    } else if (CSC->inside(x,y)){
        return "IITD CSC";
    } else if (SAC->inside(x,y)){
        return "SAC";
    } else if (Parking->inside(x,y)){
        return "VISITOR PARKING";
    } else if (Grounds->inside(x,y)){
        return "SPORTS GROUNDS";
    } else if (CVin->inside(x,y)){
        return "VINDY CIRCLE";
    } else if (CHim->inside(x,y)){
        return "HIMADRI CIRCLE";
    } else if (CSac->inside(x,y)){
        return "SAC CIRCLE";
    } else if (CJwl->inside(x,y)){
        return "JWALA CIRCLE";
    } else {
        return "";
    }

}