#include "Chance.hpp"
#include "TM.hpp"
#include "Map.hpp"
#include <iostream>
#include <string>
using namespace std;
using std::string;

Chance::Chance(int x, int y) {
    xpos = x;
    ypos = y;
    renderer = Game::gRenderer;
    objTexture = TM::LoadTexture("./assets/mysterybox.png");
    ID = 0;

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

void Chance::objUpdate() {
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

void Chance::objRender() {
    destRect.x = xpos - Game::gCamera.x;
    destRect.y = ypos - Game::gCamera.y;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    SDL_RenderCopy(renderer,objTexture,&srcRect,&destRect);
    // cout << "This is called..." << endl;

}

int Chance::getx() {
    return xpos;
}

int Chance::gety() {
    return ypos;
}

void Chance::setx(int x){
    xpos = x;
}

void Chance::sety(int y){
    ypos = y;
}

void Chance::onCollision(){
    xpos = 0;
    ypos = 0;
    cout << "Mystery Box Collected.";
    // Some logic for scoring here...
}

SDL_Rect Chance::getCollider() {
    return mCollider;
}
