#include "PowerUp.hpp"
#include "TM.hpp"
#include "Map.hpp"
#include <iostream>
#include <string>
using namespace std;
using std::string;

PowerUp::PowerUp(int type, int x, int y) {
    ID = type;
    xpos = x;
    ypos = y;
    renderer = Game::gRenderer;
    if (type == 0){
        objTexture = TM::LoadTexture("./assets/hammer.png");
    } else if (type == 1) {
        objTexture = TM::LoadTexture("./assets/phone.png");
    } else if (type == 2) {
        objTexture = TM::LoadTexture("./assets/teleporter.png");
    }

    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    mCollider.x = xpos;
    mCollider.y = ypos;
    mCollider.w = srcRect.w;
    mCollider.h = srcRect.h;
    
}

void PowerUp::objUpdate() {
    srcRect.h = 64;
    srcRect.w = 64;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;

    mCollider.x = xpos;
    mCollider.y = ypos;
    mCollider.w = srcRect.w;
    mCollider.h = srcRect.h;
}

void PowerUp::objRender() {
    destRect.x = xpos - Game::gCamera.x;
    destRect.y = ypos - Game::gCamera.y;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    SDL_RenderCopy(renderer,objTexture,&srcRect,&destRect);
    // cout << "This is called..." << endl;

}

int PowerUp::getx() {
    return xpos;
}

int PowerUp::gety() {
    return ypos;
}

void PowerUp::setx(int x){
    xpos = x;
}

void PowerUp::sety(int y){
    ypos = y;
}

int PowerUp::getID(){
    return ID;
}

void PowerUp::onCollision(){
    xpos = 0;
    ypos = 0;
    cout << "Power Up Collected.";
    // Some logic for scoring here...
}

SDL_Rect PowerUp::getCollider() {
    return mCollider;
}
