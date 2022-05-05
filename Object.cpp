#include "Object.hpp"
#include "TM.hpp"
#include "Map.hpp"
#include <iostream>
#include <string>
using namespace std;
using std::string;

Object::Object(const char* texturesheet, int x, int y) {
    xpos = x;
    ypos = y;
    frame = 0;
    velocity = 64;
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
    
    for(int i =0; i <5; i++)
    {
    inventoryItems[i] = "";
    }
}

// void Object::objMove(int dir, SDL_Rect b) {
//     switch (dir) {
//         case 1:
//             ypos -= velocity;
//             mCollider.y = ypos;
//             if (checkCollision(b)) {
//                 cout << "ok..." << endl;
//                 ypos += velocity;
//             }
//             break;
//         case 2:
//             ypos += velocity;
//             mCollider.y = ypos;
//             if (checkCollision(b)) {
//                 cout << "ok..." << endl;
//                 ypos -= velocity;
//             }
//             break;
//         case 3:
//             xpos -= velocity;
//             mCollider.x = xpos;
//             if (checkCollision(b)) {
//                 cout << "ok..." << endl;
//                 xpos += velocity;
//             }
//             break;
//         case 4:
//             xpos += velocity;
//             mCollider.x = xpos;
//             if (checkCollision(b)) {
//                 cout << "ok..." << endl;
//                 xpos -= velocity;
//             }
//             break;
//         default:
//             break;
//     }

//     srcRect.h = 32;
//     srcRect.w = 32;
//     srcRect.x = 0;
//     srcRect.y = 0;

//     destRect.x = xpos;
//     destRect.y = ypos;
//     destRect.w = 2*srcRect.w;
//     destRect.h = 2*srcRect.h;

//     mCollider.x = xpos;
//     mCollider.y = ypos;
//     mCollider.w = 2*srcRect.w;
//     mCollider.h = 2*srcRect.h;
// }

void Object::objMove(int dir, SDL_Rect b, Tuple* Colliders[]) {
    bool isTileCollision = false;
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
            if (checkCollision(b) || isTileCollision) {
                cout << "ok..." << endl;
                ypos += velocity;
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
            if (checkCollision(b) || isTileCollision) {
                cout << "ok..." << endl;
                ypos -= velocity;
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
            if (checkCollision(b) || isTileCollision) {
                cout << "ok..." << endl;
                xpos += velocity;
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
            if (checkCollision(b)|| isTileCollision) {
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

void Object::objRender(int camx, int camy) {
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

bool Object::checkTileCollision(int x, int y) {
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

SDL_Rect Object::getCollider() {
    return mCollider;
}

int Object::getx() {
    return xpos;
}

int Object::gety() {
    return ypos;
}

void Object::addItems( string str)

{
	for(int i =0; i < 5; i++)
	{
			if(inventoryItems[i] == "")
			{
			inventoryItems[i] = str;
			break;
			}
	}
}

    string Object::getIElem(string s[],int i)
    {
    return s[i];
    }


void Object::changeFrame(int dir) {
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