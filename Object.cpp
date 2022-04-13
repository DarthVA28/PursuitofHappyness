#include "Object.hpp"
#include "TM.hpp"
#include <iostream>
using namespace std;

Object::Object(const char* texturesheet, int x, int y) {
    xpos = x;
    ypos = y;
    velocity = 10;
    renderer = Game::gRenderer;
    objTexture = TM::LoadTexture(texturesheet);

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

void Object::objMove(int dir, SDL_Rect b) {
    switch (dir) {
        case 1:
            ypos -= velocity;
            mCollider.y = ypos;
            if (checkCollision(b)) {
                cout << "ok..." << endl;
                ypos += velocity;
            }
            break;
        case 2:
            ypos += velocity;
            mCollider.y = ypos;
            if (checkCollision(b)) {
                cout << "ok..." << endl;
                ypos -= velocity;
            }
            break;
        case 3:
            xpos -= velocity;
            mCollider.x = xpos;
            if (checkCollision(b)) {
                cout << "ok..." << endl;
                xpos += velocity;
            }
            break;
        case 4:
            xpos += velocity;
            mCollider.x = xpos;
            if (checkCollision(b)) {
                cout << "ok..." << endl;
                xpos -= velocity;
            }
            break;
        default:
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
}

void Object::objMove(int dir) {
    switch (dir) {
        case 1:
            ypos -= velocity;
            break;
        case 2:
            ypos += velocity;
            break;
        case 3:
            xpos -= velocity;
            break;
        case 4:
            xpos += velocity;
            break;
        default:
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
}

void Object::objUpdate() {
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;
}

void Object::objRender() {
    SDL_RenderCopy(renderer,objTexture,&srcRect,&destRect);
}

bool Object::checkCollision(SDL_Rect b) {
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
        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;

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
            cout << "Collision1" << endl;
            return true;
        }
}

SDL_Rect Object::getCollider() {
    return mCollider;
}