#include "Object.hpp"
#include "TM.hpp"
#include "Map.hpp"
#include "NPC.hpp"
#include "PowerUp.hpp"
#include <iostream>
#include <string>
using namespace std;
using std::string;

Object::Object(const char* texturesheet, int x, int y) {
    xpos = x;
    ypos = y;
    frame = 0;
    velocity = 10;
    happyness= 180;
    Yulu = false;
    gotChance = false;
    profColl = false;
    activePowerUp = -1;
    hasHammer = 0;
    usedTeleport = 0;
    usedHammer = 0;
    usedPhone = 0;
    chanceRender = "";
    money = "1000";
    taskIndex = 0;
    renderer = Game::gRenderer;
    objTexture = TM::LoadTexture(texturesheet);

    for(int i=0;i<24;i++){
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

    textureSheet[11].x = 96;
    textureSheet[11].y = 64;
    textureSheet[11].w = 32;
    textureSheet[11].h = 32;

    textureSheet[12].x = 0;
    textureSheet[12].y = 32*3;
    textureSheet[12].w = 32;
    textureSheet[12].h = 32;

    textureSheet[13].x = 32;
    textureSheet[13].y = 32*3;
    textureSheet[13].w = 32;
    textureSheet[13].h = 32;

    textureSheet[14].x = 64;
    textureSheet[14].y = 32*3;
    textureSheet[14].w = 32;
    textureSheet[14].h = 32;

    textureSheet[15].x = 0;
    textureSheet[15].y = 32*4;
    textureSheet[15].w = 32;
    textureSheet[15].h = 32;

    textureSheet[16].x = 32;
    textureSheet[16].y = 32*4;
    textureSheet[16].w = 32;
    textureSheet[16].h = 32;

    textureSheet[17].x = 64;
    textureSheet[17].y = 32*4;
    textureSheet[17].w = 32;
    textureSheet[17].h = 32;

    textureSheet[18].x = 0;
    textureSheet[18].y = 32*5;
    textureSheet[18].w = 32;
    textureSheet[18].h = 32;

    textureSheet[19].x = 32;
    textureSheet[19].y = 32*5;
    textureSheet[19].w = 32;
    textureSheet[19].h = 32;

    textureSheet[20].x = 64;
    textureSheet[20].y = 32*5;
    textureSheet[20].w = 32;
    textureSheet[20].h = 32;

    textureSheet[21].x = 0;
    textureSheet[21].y = 32*6;
    textureSheet[21].w = 32;
    textureSheet[21].h = 32;

    textureSheet[22].x = 32;
    textureSheet[22].y = 32*6;
    textureSheet[22].w = 32;
    textureSheet[22].h = 32;

    textureSheet[23].x = 64;
    textureSheet[23].y = 32*6;
    textureSheet[23].w = 32;
    textureSheet[23].h = 32;

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
                // cout << "ok..." << endl;
//                 ypos += velocity;
//             }
//             break;
//         case 2:
//             ypos += velocity;
//             mCollider.y = ypos;
//             if (checkCollision(b)) {
                // cout << "ok..." << endl;
//                 ypos -= velocity;
//             }
//             break;
//         case 3:
//             xpos -= velocity;
//             mCollider.x = xpos;
//             if (checkCollision(b)) {
                // cout << "ok..." << endl;
//                 xpos += velocity;
//             }
//             break;
//         case 4:
//             xpos += velocity;
//             mCollider.x = xpos;
//             if (checkCollision(b)) {
                // cout << "ok..." << endl;
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

void Object::objMove(int dir, SDL_Rect b, Tuple* Colliders[], NPC* activeNPC[], int num_NPC, Chance* activeChance[], PowerUp* activePUPS[]) {
    inMotion = true;
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

            for(int j=0;j<num_NPC;j++){
                SDL_Rect c = (activeNPC[j]->getCollider());
                if (checkCollision(c)) {
                    profColl = true;
                    activeNPC[j]->onCollision();
                    collisionNPC();
                }
            }

            for(int k=0;k<2;k++){
                SDL_Rect d = (activeChance[k]->getCollider());
                if (checkCollision(d)) {
                    gotChance = true;
                    activeChance[k]->onCollision();
                    collisionChance();
                }
            }

            for(int l=0;l<5;l++){
                SDL_Rect e = (activePUPS[l]->getCollider());
                if (checkCollision(e)) {
                    activePowerUp = (activePUPS[l]->getID());
                    activePUPS[l]->onCollision();
                }
            }

            if (checkCollision(b) || isTileCollision) {
                // cout << "ok..." << endl;
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

            for(int j=0;j<num_NPC;j++){
                SDL_Rect c = (activeNPC[j]->getCollider());
                if (checkCollision(c)) {
                    profColl = true;
                    activeNPC[j]->onCollision();
                    collisionNPC();
                }
            }

            for(int k=0;k<2;k++){
                SDL_Rect d = (activeChance[k]->getCollider());
                if (checkCollision(d)) {
                    gotChance = true;
                    activeChance[k]->onCollision();
                    collisionChance();
                }
            }

            for(int l=0;l<5;l++){
                SDL_Rect e = (activePUPS[l]->getCollider());
                if (checkCollision(e)) {
                    activePowerUp = (activePUPS[l]->getID());
                    activePUPS[l]->onCollision();
                }
            }

            if (checkCollision(b) || isTileCollision) {
                // cout << "ok..." << endl;
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
            for(int j=0;j<num_NPC;j++){
                SDL_Rect c = (activeNPC[j]->getCollider());
                if (checkCollision(c)) {
                    profColl = true;
                    activeNPC[j]->onCollision();
                    collisionNPC();
                }
            }

            for(int k=0;k<2;k++){
                SDL_Rect d = (activeChance[k]->getCollider());
                if (checkCollision(d)) {
                    gotChance = true;
                    activeChance[k]->onCollision();
                    collisionChance();
                }
            }

            for(int l=0;l<5;l++){
                SDL_Rect e = (activePUPS[l]->getCollider());
                if (checkCollision(e)) {
                    activePowerUp = (activePUPS[l]->getID());
                    activePUPS[l]->onCollision();
                }
            }

            if (checkCollision(b) || isTileCollision) {
                // cout << "ok..." << endl;
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
            for(int j=0;j<num_NPC;j++){
                SDL_Rect c = (activeNPC[j]->getCollider());
                if (checkCollision(c)) {
                    profColl = true;
                    activeNPC[j]->onCollision();
                    collisionNPC();
                }
            }

            for(int k=0;k<2;k++){
                SDL_Rect d = (activeChance[k]->getCollider());
                if (checkCollision(d)) {
                    gotChance = true;
                    activeChance[k]->onCollision();
                    collisionChance();
                }
            }

            for(int l=0;l<5;l++){
                SDL_Rect e = (activePUPS[l]->getCollider());
                if (checkCollision(e)) {
                    activePowerUp = (activePUPS[l]->getID());
                    activePUPS[l]->onCollision();
                }
            }

            if (checkCollision(b) || isTileCollision) {
                // cout << "ok..." << endl;
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

    int m = std::stoi(money);
    if(m<0 && Yulu){
        m = 0;
        money = to_string(m);
        Yulu = false;
        toggleYulu();
    }
}

void Object::objRender() {
    SDL_RenderCopy(renderer,objTexture,&srcRect,&destRect);
}

void Object::objRender(int camx, int camy) {
    destRect.x = xpos - Game::gCamera.x;
    destRect.y = ypos - Game::gCamera.y;
    destRect.w = 2*srcRect.w;
    destRect.h = 2*srcRect.h;
    if (!Yulu) {
        if (frame>=0 && frame <=10){
            SDL_RenderCopy(renderer,objTexture,&textureSheet[frame],&destRect);
        } else {
            cout << "ERROR: " << "The value of the frame is " << frame << endl;
        } 
    } else {
        if (frame>=12 && frame <=23){
            SDL_RenderCopy(renderer,objTexture,&textureSheet[frame],&destRect);
        } else {
            cout << "ERROR: " << "The value of the frame is " << frame << endl;
        } 
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
            // cout << "Collision2" << endl;
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
void Object::addTasks(Task* t)

{
	tasks[taskIndex] = t;
    taskIndex ++;
}

void Object::addPowerUps( string str)
{
	for(int i =0; i < 2; i++)
	{
			if(powerUps[i] == "")
			{
			powerUps[i] = str;
            if (str=="hammer"){
                hasHammer=1;
            }
			break;
			}
	}
}

bool Object::removePowerUps()
{
    bool success = false;
	for(int i =0; i < 2; i++)
	{
            if (powerUps[i] != "") {
                
                if (powerUps[i] == "hammer"){
                    handlePowerUp(0);
                    usedHammer = 1;
                }
                else if (powerUps[i] == "teleporter"){
                    handlePowerUp(1);
                    usedTeleport = 1;
                } else {
                    handlePowerUp(2);
                    usedPhone = 1;
                }
                powerUps[i] = "";
                success = true;
                break;
            }

	}
	return success;
}

void Object::handlePowerUp(int pid){
    if (pid == 0) {
    } else if (pid == 1) {}
    else {
        for(int i =0; i<5; i++){
            if (tasks[i]->taskDone == false){
                tasks[i]->taskDone = true;
                int j = stoi(taskDone);
                j++;
                taskDone = to_string(j);
                powerupRender = "Phone: A friend did your task for you!";
                break;
            }
        }

    }
}

string Object::getIElem(string s[],int i)
{
return s[i];
}
bool Object::removeItems( string str)

{
bool success = false;
	for(int i =0; i < 5; i++)
	{
			if(inventoryItems[i] == str)
			{
			inventoryItems[i] = "";
			success = true;
			break;
			}
	}
	return success;
}


void Object::changeFrame(int dir) {
    if (!Yulu){
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
    } else {
        if (dir==2) {
            if (frame>=18 && frame<20){
                frame++;
            } else {
                frame = 18;
            }
        } else if (dir==1){
            if (frame>=21 && frame<23){
                frame++;
            } else {
                frame = 21;
            }
        } else if (dir==3){
            if (frame>=12 && frame<14){
                frame++;
            } else {
                frame = 12;
            }
        } else if (dir==4){
            if (frame>=15 && frame<17){
                frame++;
            } else {
                frame = 15;
            }
        } else {
            frame = 18;
        }
    }
}

void Object::setx(int x){
    xpos = x;
}

void Object::sety(int y){
    ypos = y;
}

void Object::setFrame(int f){
    frame = f;
}

void Object::toggleYulu(){
    if (Yulu) {
        cout << "Yulu activated!" << endl;
        velocity = 40;
        frame = 18;
    } else {
        cout << "Yulu deactivated!" << endl;
        velocity = 10;
        frame = 0;
    }
}

void Object::objTeleport(int location){
    switch(location){
        case 0: //Jwala
            xpos = 12504;
            ypos = 5248;
            break;
        case 1:
            xpos = 11576;
            ypos = 2388;
            break;
        case 2:
            xpos = 3072;
            ypos = 6932;
            break;
        case 3:
            xpos = 10112;
            ypos = 3572;
            break;
        default:
            break;
    }
}

void Object::randomTeleport(){
    int min = 0;
    int max = 8;
    int range = max-min+1;
    int location = rand()%range + min;
    
    switch(location){
        case 0:
            xpos = 4432;
            ypos = 6792;
            break;
        case 1:
            xpos = 5292;
            ypos = 6172;
            break;
        case 2:
            xpos = 6072;
            ypos = 4492;
            break;
        case 3:
            xpos = 8372;
            ypos = 3132;
            break;
        case 4:
            xpos = 11212;
            ypos = 3332;
            break;
        case 5:
            xpos = 9972;
            ypos = 2772;
            break;
        case 6:
            xpos = 11472;
            ypos = 4532;
            break;
        case 7:
            xpos = 3072;
            ypos = 7492;
            break;
        case 8:
            xpos = 5406;
            ypos = 7598;
            break;
        default:
            break;
    }
}

int Object::getHappyness()
{
return happyness;
}

void Object::updateHappyness()
{
int h = std::stoi(hunger);
int m = std::stoi(money);
int td = std::stoi(taskDone);
happyness = 180 -((3*h+1 +((1000-m)/20))/(td+1));
if(happyness >180){
happyness = 180;
}

}

void Object::collisionNPC(){
    happyness -= 10;
}

void Object::collisionChance(){
    int min = 0;
    int max = 10;
    int range = max-min+1;
    int idx = rand()%range + min;

    int i = 0;

    switch(idx){
        case 0:
            chanceRender = "Mystery Box: Happiness increased by 5";
            happyness += 5;
            if(happyness >180){
                happyness = 180;
            }
            break;
        case 1:
            chanceRender = "Mystery Box: Hunger reduced by 10";
            i = std::stoi(hunger);
	        i-=10;
            if(i<0){
                i =0;
            }
	        hunger = std::to_string(i);
            break;
        case 2:
            chanceRender = "Mystery Box: Received 100 Money";
            i = std::stoi(money);
	        i+=100;
	        money = std::to_string(i);
            break;
        case 3:
            chanceRender = "Mystery Box: Received 200 Money";
            i = std::stoi(money);
	        i+=200;
	        money = std::to_string(i);
            break;
        case 4:
            chanceRender = "Mystery Box: Happiness decreased by 5";
            happyness += 5;
            break;
        case 5:
            chanceRender = "Mystery Box: Happiness decreased by 5";
            happyness -= 5;
            if(happyness < 0){
                happyness = 0;
            }
            break;
        case 6:
            chanceRender = "Mystery Box: Teleported to Random Location";
            randomTeleport();
            break;
        case 7:
            chanceRender = "Mystery Box: Teleported to Jwala";
            objTeleport(0);
            break;
        case 8:
            chanceRender = "Mystery Box: Teleported to Rajdhani";
            objTeleport(3);
            break;
        case 9:
            chanceRender = "Mystery Box: Income Tax -100 Money";
            i = std::stoi(money);
	        i-=100;
            if(i<0){
                i =0;
            }
	        money = std::to_string(i);
            break;
        case 10:
            chanceRender = "Mystery Box: Feeling Hungry";        
            i = std::stoi(hunger);
	        i+=40;
	        hunger = std::to_string(i);
            break;
        default:
            break;
    }
}