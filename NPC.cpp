#include "NPC.hpp"
#include "TM.hpp"
#include "Map.hpp"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

NPC::NPC(const char* texturesheet, int x, int y, string npc_id){
    xpos = x;
    ypos = y;
    ID = npc_id;
    frame = 0;
    velocity = 2;
    renderer = Game::gRenderer;
    objTexture = TM::LoadTexture(texturesheet);

    for(int i=0;i<11;i++){
        SDL_Rect* a = new SDL_Rect;
        textureSheet[i] = *a;
    }

    textureSheet[0].x = 0;
    textureSheet[0].y = 0;
    textureSheet[0].w = 32;
    textureSheet[0].h = 32;

    textureSheet[1].x = 32;
    textureSheet[1].y = 0;
    textureSheet[1].w = 32;
    textureSheet[1].h = 32;

    textureSheet[2].x = 64;
    textureSheet[2].y = 0;
    textureSheet[2].w = 32;
    textureSheet[2].h = 32;

    textureSheet[3].x = 0;
    textureSheet[3].y = 32;
    textureSheet[3].w = 32;
    textureSheet[3].h = 32;

    textureSheet[4].x = 32;
    textureSheet[4].y = 32;
    textureSheet[4].w = 32;
    textureSheet[4].h = 32;

    textureSheet[5].x = 64;
    textureSheet[5].y = 32;
    textureSheet[5].w = 32;
    textureSheet[5].h = 32;

    textureSheet[6].x = 96;
    textureSheet[6].y = 32;
    textureSheet[6].w = 32;
    textureSheet[6].h = 32;

    textureSheet[7].x = 0;
    textureSheet[7].y = 64;
    textureSheet[7].w = 32;
    textureSheet[7].h = 32;

    textureSheet[8].x = 32;
    textureSheet[8].y = 64;
    textureSheet[8].w = 32;
    textureSheet[8].h = 32;

    textureSheet[9].x = 64;
    textureSheet[9].y = 64;
    textureSheet[9].w = 32;
    textureSheet[9].h = 32;

    textureSheet[10].x = 96;
    textureSheet[10].y = 64;
    textureSheet[10].w = 32;
    textureSheet[10].h = 32;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;

    // Generalize this later 
    mCollider.x = xpos;
    mCollider.y = ypos;
    mCollider.w = 2*srcRect.w;
    mCollider.h = 2*srcRect.h;
}

void NPC::NPCMove(Tuple* Colliders[], int xt, int yt){
    int direction = 0;
    bool moved = false;

    if (ypos>yt+32){
        direction = 1;
    } else if (ypos+32<yt) {
        direction = 2;
    } 

    moved = objMove(direction, Colliders);

    if (!moved) {
        if (xpos > xt) {
        direction = 3;
        } else {
        direction = 4;
        }
        moved = objMove(direction, Colliders);
        if (moved) {
            changeFrame(direction);
        }
    } else {
        changeFrame(direction);
    }
    

    if (!moved) {
        direction = 0;
    }

    while (!moved && direction <4){
        direction++;
        moved = objMove(direction, Colliders);
        if (moved) {
            changeFrame(direction);
        }
    }
}

void NPC::objUpdate() {
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;
}

bool NPC::objMove(int dir, Tuple* Colliders[]) {
    inMotion = true;
    bool isTileCollision = false;
    bool msuccess = true;
    Tuple* tup = new Tuple(0,0);
    switch (dir) {
        case 1:
            ypos -= velocity;
            mCollider.y = ypos;
            for(int i=0; i<Map::BARRIERS; i++) {
                tup = Colliders[i];
                if (checkTileCollision(tup->fst,tup->snd)) {
                    isTileCollision = true;
                    break;
                }
            } 
            if (isTileCollision) {
                ypos += velocity;
                msuccess = false;
            }
            break;
        case 2:
            ypos += velocity;
            mCollider.y = ypos;
            for(int i=0; i<Map::BARRIERS; i++) {
                tup = Colliders[i];
                if (checkTileCollision(tup->fst,tup->snd)) {
                    isTileCollision = true;
                    break;
                }
            } 
            if (isTileCollision) {
                ypos -= velocity;
                msuccess = false;
            }
            break;
        case 3:
            xpos -= velocity;
            mCollider.x = xpos;
            for(int i=0; i<Map::BARRIERS; i++) {
                tup = Colliders[i];
                if (checkTileCollision(tup->fst,tup->snd)) {
                    isTileCollision = true;
                    break;
                }
            } 
            if (isTileCollision) {
                xpos += velocity;
                msuccess = false;
            }
            break;
        case 4:
            xpos += velocity;
            mCollider.x = xpos;
            for(int i=0; i<Map::BARRIERS; i++) {
                tup = Colliders[i];
                if (checkTileCollision(tup->fst,tup->snd)) {
                    isTileCollision = true;
                    break;
                }
            } 
            if (isTileCollision) {
                xpos -= velocity;
                msuccess = false;
            }
            break;
        default:
            msuccess = false;
            break;
    }

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;

    mCollider.x = xpos;
    mCollider.y = ypos;
    mCollider.w = 2*srcRect.w;
    mCollider.h = 2*srcRect.h;

    return msuccess;
}

void NPC::objRender() {
    destRect.x = xpos - Game::gCamera.x;
    destRect.y = ypos - Game::gCamera.y;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;
    if (frame>=0 && frame <=10){
        SDL_RenderCopy(renderer,objTexture,&textureSheet[frame],&destRect);
    } else {
        cout << "ERROR: " << "The value of the frame is " << frame << endl;
    }
}

bool NPC::checkTileCollision(int x, int y) {
        //The sides of the rectangles
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;

        //Calculate the sides of rect A
        leftA = mCollider.x;
        rightA = mCollider.x + mCollider.w;
        topA = mCollider.y;
        bottomA = mCollider.y + mCollider.h;

        //Calculate the sides of rect B
        // leftB = -Game::gCamera.x + 64*x;
        // rightB = 64*x + 64 - Game::gCamera.x;
        // topB = 64*y - Game::gCamera.y;
        // bottomB = 64*y + 64 - Game::gCamera.y;

        leftB = 64*x;
        rightB = 64*x + 64;
        topB = 64*y;
        bottomB = 64*y + 64;

            //If any of the sides from A are outside of B
        if(bottomA <= topB) {
            return false;
        } else if ( topA >= bottomB ) {
            return false;
        } else if( rightA <= leftB ) {
            return false;
        } else if( leftA >= rightB ) {
            return false;
        } else {
            cout << "Collision2" << endl;
            return true;
        }
}

void NPC::changeFrame(int dir) {
    if (dir==1) {
        if (frame<2){
            frame++;
        } else {
            frame = 0;
        }
    } else if (dir==2){
        if (frame<2){
            frame++;
        } else {
            frame = 0;
        }
    } else if (dir==3){
        if (frame>=7 && frame<10){
            frame++;
        } else {
            frame = 7;
        }
    } else if (dir==4){
        if (frame>=3 && frame<6){
            frame++;
        } else {
            frame = 3;
        }
    } else {
        if (frame<2){
            frame++;
        } else {
            frame = 0;
        }
    }
}

SDL_Rect NPC::getCollider() {
    return mCollider;
}

int NPC::getx() {
    return xpos;
}

int NPC::gety() {
    return ypos;
}

string NPC::getID() {
    return ID;
}

void NPC::setx(int x){
    xpos = x;
}

void NPC::sety(int y){
    ypos = y;
}


