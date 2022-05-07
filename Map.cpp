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

int score=100;

int map1[Map::MAP_X*Map::MAP_Y] = MAP_WT;  

Map::Map() {
    dirt = TM::LoadTexture("assets/dirt.png");
    grass = TM::LoadTexture("assets/grass.png");
    
    campus = TM::LoadTexture("assets/campusv3.png");
    if(campus == NULL)
    {
    printf("ERROR cant load image of campus");
    }
    HappinessBarU = TM::LoadTexture("assets/healthBarUnder.png");
    if(HappinessBarU == NULL)
    {
    printf("ERROR cant load image of happiness bar");
    }
    
    HappinessBarO = TM::LoadTexture("assets/healthBarOver.png");
    if(HappinessBarO == NULL)
    {
    printf("ERROR cant load background of happiness bar");
    }
     playerOneScore = TM::LoadTexture("assets/playerOneScore.png");
    if(playerOneScore == NULL)
    {
    printf("ERROR cant load background of happiness bar");
    }
      item1 = TM::LoadTexture("assets/item1.png");
    if(item1 == NULL)
    {
    printf("ERROR cant load item1");
    }
      item2 = TM::LoadTexture("assets/item2.png");
    if(item2 == NULL)
    {
    printf("ERROR cant load item2");
    }
      item3 = TM::LoadTexture("assets/item3.png");
    if(item3 == NULL)
    {
    printf("ERROR cant load item");
    }
      item4 = TM::LoadTexture("assets/item4.png");
    if(item4 == NULL)
    {
    printf("ERROR cant load item4");
    }
      item5 = TM::LoadTexture("assets/item5.png");
    if(item5 == NULL)
    {
    printf("ERROR cant load item5");
    }
              menu1 = TM::LoadTexture("assets/menu1.png");
    if(menu1 == NULL)
    {
    printf("ERROR cant load menu");
    }
          menu2 = TM::LoadTexture("assets/menu2.png");
    if(menu2 == NULL)
    {
    printf("ERROR cant load menu");
    }
              hammer = TM::LoadTexture("assets/hammer.png");
    if(hammer == NULL)
    {
    printf("ERROR cant load hammer");
    }
              phone = TM::LoadTexture("assets/phone.png");
    if(phone == NULL)
    {
    printf("ERROR cant load phone");
    }
              teleport = TM::LoadTexture("assets/teleporter.png");
    if(teleport == NULL)
    {
    printf("ERROR cant load teleport");
    }
                  camera = TM::LoadTexture("assets/camera.png");
    if((camera == NULL))
    {
    printf("ERROR cant load camera");
    }
                  shoes = TM::LoadTexture("assets/shoes.png");
     if(shoes == NULL)
    {
    printf("ERROR cant load shoes");
    }
                  pendant = TM::LoadTexture("assets/pendant.png");
     if(pendant== NULL)
    {
    printf("ERROR cant load pendant");
    }
                  key = TM::LoadTexture("assets/key.png");
     if(key == NULL)
    {
    printf("ERROR cant load key");
    }
                  refreshments = TM::LoadTexture("assets/snacks.png");
     if(refreshments == NULL)
    {
    printf("ERROR cant load snack");
    }
                  refreshmentsmain = TM::LoadTexture("assets/snack2.png");
         if(refreshmentsmain == NULL)
    {
    printf("ERROR cant load snack");
    }
                  clothes = TM::LoadTexture("assets/dress.png");
         if(clothes == NULL)
    {
    printf("ERROR cant load clothes");
    }
                  cash = TM::LoadTexture("assets/cash.png");
         if(cash == NULL)
    {
    printf("ERROR cant load cash");
    }
                  facche = TM::LoadTexture("assets/freshers.png");
         if(facche == NULL)
    {
    printf("ERROR cant load freshers");
    }
                  water = TM::LoadTexture("assets/waterbottle.png");
         if(water == NULL)
    {
    printf("ERROR cant load water");
    }
                  laptop = TM::LoadTexture("assets/laptop.png");
         if(laptop == NULL)
    {
    printf("ERROR cant load laptop");
    }
                  passes = TM::LoadTexture("assets/pass.png");
         if(passes == NULL)
    {
    printf("ERROR cant load pass");
    }
                  cones = TM::LoadTexture("assets/cone.png");
         if(cones == NULL)
    {
    printf("ERROR cant load cones");
    }
    
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

void Map::DrawMenu( string item) {
    menusrc.x = 0;
    menusrc.y = 0;
    menusrc.w = 216;
    menusrc.h = 233;
    menudest.x = 250;   
    menudest.y =230;
    menudest.w = 250;
    menudest.h = 250;
    if((item == "menu1"))
    {
    TM::Draw(menu1,itemsrc,itemdest);
    }
     if(item == "menu2")
    {
    TM::Draw(menu2,itemsrc,itemdest);
    }
     
    
}

//load happinessBars


void Map::DrawHappinessBarU() {
    Happysrc.x = 0;
    Happysrc.y = 0;
    Happysrc.w = 796;
    Happysrc.h = 71;
    Happydest.x = 570;
    
    Happydest.y =50;
    Happydest.w = 180;
    Happydest.h = 20;
    TM::Draw(HappinessBarU,Happysrc,Happydest);
}
void Map::DrawHappinessBarO(int score) {
    Happysrc.x = 0;
    Happysrc.y = 0;
    Happysrc.w = 796;
    Happysrc.h = 71;
    Happydest.x = 570;
    
    Happydest.y =50;
    Happydest.w = score;
    Happydest.h = 20;
    TM::Draw(HappinessBarO,Happysrc,Happydest);
    
}


void Map::Drawitems( string item, int i) {
    itemsrc.x = 0;
    itemsrc.y = 0;
    itemsrc.w = 216;
    itemsrc.h = 233;
    itemdest.x = 250 + 70*i;   
    itemdest.y =230;
    itemdest.w = 64;
    itemdest.h = 64;
    if((item == "camera"))
    {
    TM::Draw(camera,itemsrc,itemdest);
    }
     if(item == "shoes")
    {
    TM::Draw(shoes,itemsrc,itemdest);
    }
     if(item == "pendant")
    {
    TM::Draw(pendant,itemsrc,itemdest);
    }
     if(item == "key")
    {
    TM::Draw(key,itemsrc,itemdest);
    }
     if(item == "refreshments")
    {
    TM::Draw(refreshments,itemsrc,itemdest);
    }
         if(item == "refreshmentsmain")
    {
    TM::Draw(refreshmentsmain,itemsrc,itemdest);
    }
         if(item == "clothes")
    {
    TM::Draw(clothes,itemsrc,itemdest);
    }
         if(item == "cash")
    {
    TM::Draw(cash,itemsrc,itemdest);
    }
         if(item == "facche")
    {
    TM::Draw(facche,itemsrc,itemdest);
    }
         if(item == "water")
    {
    TM::Draw(water,itemsrc,itemdest);
    }
         if(item == "laptop")
    {
    TM::Draw(laptop,itemsrc,itemdest);
    }
         if(item == "passes")
    {
    TM::Draw(passes,itemsrc,itemdest);
    }
         if(item == "cones")
    {
    TM::Draw(cones,itemsrc,itemdest);
    }
    
    
}


void Map::DrawPowerUps( string powerUp, int i) {
    powerUpsrc.x = 0;
    powerUpsrc.y = 0;
    powerUpsrc.w = 216;
    powerUpsrc.h = 233;
    powerUpdest.x = 0 + 74*i;   
    powerUpdest.y =518;
    powerUpdest.w = 64;
    powerUpdest.h = 64;
if((powerUp == "phone"))
    {
    TM::Draw(phone,powerUpsrc,powerUpdest);
    }
     if(powerUp == "hammer")
    {
    TM::Draw(hammer,powerUpsrc,powerUpdest);
    }
     if(powerUp == "teleporter")
    {
    TM::Draw(teleport,powerUpsrc,powerUpdest);
    }
    
    
}

void Map::DrawplayerOneScore() {
    Happysrc.x = 0;
    Happysrc.y = 0;
    Happysrc.w = 648;
    Happysrc.h = 412;
    Happydest.x = 560;
    
    Happydest.y =5;
    Happydest.w = 240;
    Happydest.h = 160;
    TM::Draw(playerOneScore,Happysrc,Happydest);
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


const char* Map::getRegion(int x, int y) {
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
    LRect *RedSq = new LRect(7306, 3828,8226, 4908);
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
    
    
    Rect *MetroGate = new Rect(12326, 5278, 12526, 5278);
    Rect *MainGate = new Rect(5406, 7598,5566, 7598);

    //YULU STANDS
    Sq *YMainGate = new Sq(5666, 7598);
    LRect *YLHC = new LRect(5056, 5008,5366, 5238);
    LRect *YHos = new LRect(9746, 2818, 9976, 3008);
    Rect *YSac = new Rect(11576, 2388,11576, 2498);
    Rect *YSat = new Rect(9416, 4168, 9536, 4168);
    LRect *YHim = new LRect(3096, 7528, 3246, 7608); 

    Rect *LHC1 = new Rect(4026, 5268, 4026, 6148);
    LRect *LHC2 = new LRect(1986, 5988, 4066, 6188);
    LRect *LHC3 = new LRect(1986, 5188,2546, 6188);

    const char* jwala = "JWALAMUKHI";
    const char* nil = "NILGIRI";
    const char* ara = "ARAVALI";
    const char* kara = "KARAKORAM";
    const char* araNM = "HOLISTIC";
    const char* Himadri = "HIMADRI";
    const char* kailash = "KAILASH";
    const char* girnar = "GIRNAR";
    const char* udaigiri = "UDAIGIRI";
    const char* shivalik = "SHIVALIK";
    const char* vindy = "VINDYANCHAL";
    const char* satpura = "SATPURA";
    const char* Zansy = "ZANSKAR";
    const char* cumaon = "KUMAON";
    const char* cJwala = "JWALA CIRCLE";
    const char* cSAC = "SAC CIRCLE";
    const char* cVindy = "VINDY CIRCLE";
    const char* cHim = "HIMADRI CIRCLE";
    const char* csc = "CSC";
    const char* NewLHC = "NEW LHC";
    const char* sac = "SAC";
    const char* dod = "Dept Of Design";
    const char* textile = "TEXTILE DEPT";
    const char* nal = "NALANDA";
    const char* staff = "STAFF CANTEEN";
    const char* cLib = "CENTRAL LIBRARY";
    const char* Libent = "LIBRARY ENTRANCE";
    const char* parking = "VISITOR PARKING";
    const char* grounds = "SPORTS GROUNDS";
    const char* nescafe = "NESCAFE";
    const char* shiru = "SHIRU CAFE";
    const char* amul1 = "AMUL";
    const char* sit = "SCHOOL OF IT";
    const char* chayoos = "CHAAYOS";
    const char* rajdhani = "RAJDHANI";
    const char* MM = "MASALA MIX";
    const char* sbi= "SBI";
    const char* exhall = "EXHALL";
    const char* bhartiB = "BHARTI BUILDING";
    const char* redSq = "RED SQUARE";
    const char* mainBuild = "MAIN BUILDING";
    const char* BBLAWN = " BIOTECH LAWNS";
    const char* sapt = "SAPTAGIRI";
    const char* hospital = "IITD HOSPITAL";
    const char* ML = "MECH LAWN";
     const char* lechall = "LHC";
    const char* yulu = "YULU STAND";
    const char* maingate = "MAIN GATE";
    const char* metrogate = "METRO GATE";
    const char* travel = "TRAVELLING...";

    if (Jwala->inside(x,y)) {
        return jwala;
    } else if (Ara->inside(x,y)){
        return ara;
    } else if (Kara->inside(x,y)){
        return kara;
    } else if (Nilgiri->inside(x,y)){
        return nil;
    } else if (AraNM->inside(x,y)){
        return araNM;
    } else if (Satpura1->inside(x,y) || Satpura2->inside(x,y) || Satpura3->inside(x,y)) {
        return satpura;
    } else if (Kum1->inside(x,y) || Kum2->inside(x,y)) {
        return cumaon;
    } else if (Vindy1->inside(x,y) || Vindy2->inside(x,y)) {
        return vindy;
    } else if (Shiva->inside(x,y)) {
        return shivalik;
    } else if (Zan1->inside(x,y) || Zan2->inside(x,y)){
        return Zansy;
    } else if (Girnar->inside(x,y)){
        return girnar;
    } else if (Udai->inside(x,y)){
        return udaigiri;
    } else if (Sapt->inside(x,y)){
        return sapt;
    } else if (Kailash->inside(x,y)){
        return kailash;
    } else if (Him->inside(x,y)){
        return Himadri;
    } else if (NewLHC1->inside(x,y) || NewLHC2->inside(x,y)){
        return NewLHC;
    } else if (Textile->inside(x,y)){
        return textile;
    } else if (DOD->inside(x,y)){
        return dod;
    } else if (SBI->inside(x,y)){
        return sbi;
    } else if (Nal->inside(x,y)){
        return nal;
    } else if (Staff->inside(x,y)){
        return staff;
    } else if (Lib1->inside(x,y) || Lib2->inside(x,y)){
        return cLib;
    } else if (LibEnt->inside(x,y)){
        return Libent;
    } else if (Nescafe->inside(x,y)){
        return nescafe;
    } else if (Amul1->inside(x,y) || Amul2->inside(x,y)){
        return amul1;
    } else if (Shiru->inside(x,y)){
        return shiru;
    } else if (Exhall->inside(x,y)){
        return exhall;
    } else if (SIT->inside(x,y)){
        return sit;
    } else if (Bharti2->inside(x,y) || Bharti1->inside(x,y)){
        return bhartiB;
    } else if (Hospital->inside(x,y)){
        return hospital;
    } else if (MasalaMix->inside(x,y)){
        return MM;
    } else if (Chaayos->inside(x,y)){
        return chayoos;
    } else if (Rajdhani->inside(x,y)){
        return rajdhani;
    } else if (RedSq->inside(x,y)){
        return redSq;
    } else if (MainB->inside(x,y)){
        return mainBuild;
    } else if (Biotech->inside(x,y)){
        return BBLAWN;
    } else if (MLawn->inside(x,y)){
        return ML;
    } else if (CSC->inside(x,y)){
        return csc;
    } else if (SAC->inside(x,y)){
        return sac;
    } else if (Parking->inside(x,y)){
        return parking;
    } else if (Grounds->inside(x,y)){
        return grounds;
    } else if (CVin->inside(x,y)){
        return cVindy;
    } else if (CHim->inside(x,y)){
        return cHim;
    } else if (CSac->inside(x,y)){
        return cSAC;
    } else if (CJwl->inside(x,y)){
        return cJwala;
} else if (LHC1->inside(x,y) || LHC2->inside(x,y) || LHC3->inside(x,y)) {
        return lechall;
    } else if (MainGate->inside(x,y)) {
        return maingate;
    } else if (MetroGate->inside(x,y)) {
        return metrogate;
    } else if (YHim->inside(x,y) || YHos->inside(x,y) || YLHC->inside(x,y) || YMainGate->inside(x,y) || YSac->inside(x,y) || YSat->inside(x,y)) {
        return yulu;
    } else {
        return travel;
    } 
   

}
