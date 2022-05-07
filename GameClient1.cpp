#include "Game.hpp"
#include "TM.hpp"
#include "Object.hpp"
#include "Map.hpp"
#include "NPC.hpp"
#include "PowerUp.hpp"
#include "Tuple.hpp"
#include "Chance.hpp"
// #include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <fstream>
#include<iostream>
#include <fcntl.h>
#include<errno.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8860

using std::string;

// Mix_Music *gMusic = nullptr;

// //The sound effects that will be used
// Mix_Chunk *gScratch = NULL;
// Mix_Chunk *gHigh = NULL;
// Mix_Chunk *gMedium = NULL;
// Mix_Chunk *gLow = NULL;

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

unsigned int tinit,t1,t2,t3,t4,t5,t6,t7,t8;
std::stringstream timeText;
Uint32 startTime = 0;
Uint32 dispTime = 0;
string display = "TRAVELLING...";
string Hunger;
string Money;
string TaskDone;

string messageForPopUp= " ";
bool toGivePopUp=false;

// Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 1;

bool firstScreen = true;
bool musicOn = true;
bool play = true;
bool openInventory = false;
bool openTaskSchedule = false;
bool openMenu1 = false;
bool openMenu2 = false;
bool loc1eat = false;
bool loc2eat = false;
bool openTaskSheet = false;
bool Game ::firstCheck = true;
bool fixKey = false;
bool bringLaptop= false;
bool bringCSCrefreshments = false;
bool clothesCSC = false;
bool sponsorCash = false;
bool faccheForSponsor = false;
bool cameraForBRCA = false;
bool refreshmentsForBRCA = false;
bool cameraForRedSq = false;
bool waterForRedSq = false;
bool shoesForNalanda = false;
bool conesForNalanda = false;
bool pendantForPronite = false;
bool passesForPronite = false;
bool lunch = false;
bool openTeleportMenu = false;


SDL_Renderer *Game::gRenderer = nullptr;

int posIndex = 0;
Tuple* posArray[20];

int cIndex1 = 0;
int cIndex2 = 0;
Tuple* cArray[20]; // Increase this later

int pIndex = 0;
Tuple* pArray[50]; // Increase this later

// for text
TTF_Font *gFont = NULL;
TTF_Font *gFont1 = NULL;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};
enum musicSprite
{
	musicOnSpriteV = 0,
	musicOffSpriteV = 1,

	BUTTON_SPRITE_TOTALS = 2
};

// Texture wrapper class
class LTexture
{
public:
	// Initializes variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);
	SDL_Texture *loadFromFile1(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	bool loadFromRenderedText1(std::string textureText, SDL_Color textColor);
#endif

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture *mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};

// The mouse button
class LButton
{
public:
	// Initializes internal variables
	LButton();

	// Sets top left position
	void setPosition(int x, int y, int length, int height);

	// Handles mouse event
	void handleEvent(SDL_Event *e);

	// Shows button sprite
	void renderStart();
	void renderMusic();

private:
	// Top left position
	SDL_Point mPosition;
	int mlength;
	int mheight;
	// Currently used global sprite
	LButtonSprite mCurrentSprite;
	musicSprite mmusicSprite;
};

// Mouse button sprites
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
SDL_Rect musicOffSprite;
SDL_Rect musicOnSprite;
SDL_Rect musicOffSpritedest;
SDL_Rect musicOnSpritedest;
LTexture gButtonSpriteSheetTexture;
LTexture pauseSpriteSheetTexture;
LTexture playSpriteSheetTexture;
LTexture musicOnSpriteSheetTexture;
LTexture musicOffSpriteSheetTexture;
LTexture gTimeTextTexture;
LTexture gPopUpTextTexture;
LTexture gTaskTextTexture;
LTexture gTeleportTextTexture;

// Buttons objects
LButton gButtons[TOTAL_BUTTONS];
LButton musicOnButton;
LButton musicOffButton;

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}
LTexture gbtexture1;
bool LTexture::loadFromFile(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
SDL_Texture *LTexture::loadFromFile1(std::string path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Game::gRenderer, loadedSurface);

		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	// Return success
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText1(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface1 = TTF_RenderText_Solid(gFont1, textureText.c_str(), textColor);
	if (textSurface1 == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(Game::gRenderer, textSurface1);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface1->w;
			mHeight = textSurface1->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface1);
	}

	// Return success
	return mTexture != NULL;
}

#endif

void LTexture::free()
{
	// Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(Game::gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
	mlength = 0;
	mheight = 0;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	mmusicSprite = musicOnSpriteV;
}

void LButton::setPosition(int x, int y, int length, int height)
{
	mPosition.x = x;
	mPosition.y = y;
	mlength = length;
	mheight = height;
}

void LButton::handleEvent(SDL_Event *e)
{
	// If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Check if mouse is in button
		bool inside = true;

		// Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		// Mouse is right of the button
		else if (x > mPosition.x + mlength)
		{
			inside = false;
		}
		// Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		// Mouse below the button
		else if (y > mPosition.y + mheight)
		{
			inside = false;
		}

		// Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		// Mouse is inside button
		else
		{
			// Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:

				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				firstScreen = false;
				Game ::firstCheck = false;
				// if(musicOn)
				// {
				// printf("1");
				// mmusicSprite = musicOffSpriteV;
				// musicOn = false;
				// }
				// if(!musicOn)
				// {
				// mmusicSprite = musicOnSpriteV;
				// musicOn = true;
				// }
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

void LButton::renderStart()
{
	// Show current button sprite
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
void LButton::renderMusic()
{
	if (musicOn)

	{
		SDL_RenderCopyEx(Game::gRenderer, musicOnSpriteSheetTexture.loadFromFile1("assets/musicOn.png"), &musicOnSprite, &musicOnSpritedest, 0.0, NULL, SDL_FLIP_NONE);
	}
	if (!musicOn)

	{
		SDL_RenderCopyEx(Game::gRenderer, musicOffSpriteSheetTexture.loadFromFile1("assets/musicOff.png"), &musicOffSprite, &musicOffSpritedest, 0.0, NULL, SDL_FLIP_NONE);
	}
}
/*	if(play)
	{
		playSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
	}
	if(!play)
	{
		pauseSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
	} */

//------------------------------------------------------------------------------- MUSIC---------------------------------------------------------------------------------------------
LTexture gPromptTexture;

// bool loadMusicMedia()
// {
// 	//Loading success flag
// 	bool success = true;

// 	//Load prompt texture

// 	//Load music
// 	gMusic = Mix_LoadMUS( "assets/beat.wav" );
// 	if( gMusic == NULL )
// 	{
// 		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	//Load sound effects
// 	gScratch = Mix_LoadWAV( "assets/scratch.wav" );
// 	if( gScratch == NULL )
// 	{
// 		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gHigh = Mix_LoadWAV( "assets/high.wav" );
// 	if( gHigh == NULL )
// 	{
// 		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gMedium = Mix_LoadWAV( "assets/medium.wav" );
// 	if( gMedium == NULL )
// 	{
// 		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	gLow = Mix_LoadWAV( "assets/low.wav" );
// 	if( gLow == NULL )
// 	{
// 		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
// 		success = false;
// 	}

// 	return success;

// }

/*void musicClose()
{
	//Free loaded images
	gPromptTexture.free();

	//Free the sound effects
	Mix_FreeChunk( gScratch );
	Mix_FreeChunk( gHigh );
	Mix_FreeChunk( gMedium );
	Mix_FreeChunk( gLow );
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;

	//Destroy window
	SDL_DestroyRenderer( Game::gRenderer );
	SDL_DestroyWindow( Game::gWindow );
	//gWindow = NULL;
	//gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
} */
//-----------------------------------TEXT AT TASK BAR ---------------------------------------
// Globally used font

// Rendered texture
LTexture gTextTexture;
LTexture gHungerTexture;
LTexture gMoneyTexture;
LTexture gTaskCompletedTexture;
bool loadTextMedia()
{
	// Loading success flag
	bool success = true;

	// Render text
	SDL_Color textColor = {0, 0, 0};
	if (!gTextTexture.loadFromRenderedText(display, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}
	if (!gHungerTexture.loadFromRenderedText1("HUNGER: " + Hunger, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}if (!gMoneyTexture.loadFromRenderedText1("MONEY: "+ Money, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}if (!gTaskCompletedTexture.loadFromRenderedText1("TASKS DONE: " + TaskDone, textColor))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}


	return success;
}

//-----------------------------------START SCREEN---------------------------------------------
bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load sprites
	if (!gbtexture1.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!gButtonSpriteSheetTexture.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!pauseSpriteSheetTexture.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!playSpriteSheetTexture.loadFromFile("assets/button.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!musicOnSpriteSheetTexture.loadFromFile("assets/musicOn.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else if (!musicOffSpriteSheetTexture.loadFromFile("assets/musicOff.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else
	{
		// Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * 200;
			gSpriteClips[i].w = BUTTON_WIDTH;
			gSpriteClips[i].h = BUTTON_HEIGHT;
		}

		// Set buttons in corners
		gButtons[0].setPosition(300, 350, BUTTON_WIDTH, BUTTON_HEIGHT);

		musicOnSprite.x = 0;
		musicOnSprite.y = 0;
		musicOnSprite.w = 381;
		musicOnSprite.h = 365;
		musicOffSprite.x = 0;
		musicOffSprite.y = 0;
		musicOffSprite.w = 367;
		musicOffSprite.h = 362;
		musicOnSpritedest.x = 700;
		musicOnSpritedest.y = 530;
		musicOnSpritedest.w = 50;
		musicOnSpritedest.h = 50;
		musicOffSpritedest.x = 700;
		musicOffSpritedest.y = 530;
		musicOffSpritedest.w = 50;
		musicOffSpritedest.h = 50;
		musicOnButton.setPosition(700, 530, 50, 50);
		musicOffButton.setPosition(700, 530, 50, 50);
	}

	return success;
}

/*void close()
{
	//Free loaded images
	gButtonSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
} */

SDL_Rect srcR, destR;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

Object *player;
Object *player2;
NPC* activeNPC[10];
NPC *professor;
Map *map;
int sock = 0, valread;
char buffer[64] = { 0 };
char parameters[1025];

int NUM_ACTIVE_NPC = 0;
const int NUM_ACTIVE_CHANCE = 2;
const int NUM_ACTIVE_PUPS = 5;

Chance* activeChance[NUM_ACTIVE_CHANCE];
PowerUp* activePUPS[NUM_ACTIVE_PUPS];

SDL_Rect Game::gCamera = {0, 0, 800, 600};

Game::Game() {}

Game::~Game() {}

void Game::init(const char *win_title, int xpos, int ypos, int h, int w, bool fs)
{
	// Initialization flag
	bool success = true;
	struct sockaddr_in serv_addr;
for (int i = 0; i <1024; i++){
parameters[i] = '0';
}
parameters[1025] = '\0';
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		success = false;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		success = false;
		printf(
			"\nInvalid address/ Address not supported \n");
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		success = false;
		printf("\nConnection Failed \n");
	}
	fcntl(sock,F_SETFL,O_NONBLOCK);

	int flags = 0;
	cnt = w - 128;
	tinit = SDL_GetTicks();
	if (fs)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{ //Create window
		gWindow = SDL_CreateWindow(win_title, xpos, ypos, h, w, flags);
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// Get window surface
			//  gScreenSurface = SDL_GetWindowSurface( gWindow );
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			}
			// Initialize SDL_mixer
			// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
			// {
			// 	printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			// 	success = false;
			// }

			else
			{
				if (!loadMedia())
				{
					printf("Failed to load media!\n");
				}
				// if( !loadMusicMedia() )
				// {
				// 	printf( "Failed to load music media!\n" );
				// }

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				// {
				//     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
				//     success = false;
				// }
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				gFont = TTF_OpenFont("assets/lazy.ttf", 28);
				gFont1 = TTF_OpenFont("assets/lazy.ttf", 22);
				if (gFont == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				}
				if (gFont1 == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
				}

				if (!loadTextMedia())
				{
					printf("Failed to load text media for taskbar!\n");
				}
			}
		}
	}

	if (success)
	{
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	player = new Object("assets/player.png", 12376, 2048);
	player2 = new Object("assets/player2.png", 9032,4272);

	string taskarray[16];
	taskarray[0] = "SAC MEETING: Bring laptop from hostel.";
	taskarray[1] = "SAC MEETING: Fix rec room key at Rajdhani.";
	taskarray[2] = "CSC FASHION SHOW: Bring snacks from Metro Gate.";
	taskarray[3] = "CSC FASHION SHOW: Get clothes from Himadri Circle";
	taskarray[4] = "LHC SPONSOR EVENT: Get cash from SBI";
	taskarray[5] = "LHC SPONSOR EVENT: Call freshers from Library";
	taskarray[6] = "RED SQUARE: Bring camera from SAC";
	taskarray[7] = "RED SQUARE: Fetch water from Amul";
	taskarray[8] = "MECH LAWN BRCA: Get snacks from Main Gate";
	taskarray[9] = "MECH LAWN BRCA: Bring camera from SAC";
	taskarray[10] = "NALANDA BIKING: Get cones from sports ground";
	taskarray[11] = "NALANDA BIKING: Borrow shoes from Satpura";
	taskarray[12] = "PRONITE: Get passes from LHC";
	taskarray[13] = "PRONITE: Fix pendant at Dep. of Design";
	taskarray[14] = "EAT LUNCH";
	taskarray[15] = "EAT LUNCH";

	int min = 0;
	int max = 15;
	int range = max - min + 1;

	int assigned1[5];
	int assigned2[5];

	for(int i=0; i<4; i++) {
		int idx = 0;
		bool unique = false;
		while (!unique){
			idx = rand()%range + min;
			unique = true;
			for(int j = 0; j<i; j++) {
				if (assigned1[j] == idx){
					unique = false;
				}
			}
		}
		assigned1[i] = idx;
		player->addTasks(taskarray[idx]);
	}

	player->addTasks(taskarray[14]);

	for(int i=0; i<4; i++) {
		int idx = 0;
		bool unique = false;
		while (!unique){
			idx = rand()%range + min;
			unique = true;
			for(int j = 0; j<i; j++) {
				if (assigned2[j] == idx){
					unique = false;
				}
			}
			for(int k=0; k<5; k++){
				if (assigned1[k] == idx){
					unique = false;
				}
			}
		}
		assigned2[i] = idx;
		player2->addTasks(taskarray[idx]);
	}
		
	player2->addTasks(taskarray[15]);


	
	
	// player-> addPowerUps("hammer");
	//player-> addPowerUps("hammer");
	professor = new NPC("assets/prof.png", 12350, 1950,"PROF");
	activeNPC[0] = professor;
	NUM_ACTIVE_NPC ++;
	
	map = new Map();

	posArray[0] = new Tuple(12504,5248);
	posArray[1] = new Tuple(9032,4272);
	posArray[2] = new Tuple(12504,2880);
	posArray[3] = new Tuple(5652, 4432);
	posArray[4] = new Tuple(11472, 4412);
	posArray[5] = new Tuple(3072, 6932);
	posArray[6] = new Tuple(7352, 3132);
	posArray[7] = new Tuple(10112, 3572);
	posArray[8] = new Tuple(10572, 952);
	posArray[9] = new Tuple(12412, 4632);
	posArray[10] = new Tuple(5472, 6872);
	posArray[11] = new Tuple(12504,5248);
	posArray[12] = new Tuple(11552, 4632);
	posArray[13] = new Tuple(7312, 3832);
	posArray[14] = new Tuple(6072, 4492);
	posArray[15] = new Tuple(7172, 3852);
	posArray[16] = new Tuple(5332, 3632);
	posArray[17] = new Tuple(5372, 1852);
	posArray[18] = new Tuple(6572, 4592);
	posArray[19] = new Tuple(8372, 3132);
	t3 = SDL_GetTicks();

	activeChance[0] = new Chance(12312, 2048);
	activeChance[1] = new Chance(12350, 1950);

	cArray[0] = new Tuple(12504,5248);
	cArray[1] = new Tuple(9032,4272);
	cArray[2] = new Tuple(12504,2880);
	cArray[3] = new Tuple(5652, 4432);
	cArray[4] = new Tuple(11472, 4412);
	cArray[5] = new Tuple(3072, 6932);
	cArray[6] = new Tuple(7352, 3132);
	cArray[7] = new Tuple(10112, 3572);
	cArray[8] = new Tuple(10572, 952);
	cArray[9] = new Tuple(12412, 4632);
	cArray[10] = new Tuple(5472, 6872);
	cArray[11] = new Tuple(12504,5248);
	cArray[12] = new Tuple(11552, 4632);
	cArray[13] = new Tuple(7312, 3832);
	cArray[14] = new Tuple(6072, 4492);
	cArray[15] = new Tuple(7172, 3852);
	cArray[16] = new Tuple(5332, 3632);
	cArray[17] = new Tuple(5372, 1852);
	cArray[18] = new Tuple(6572, 4592);
	cArray[19] = new Tuple(8372, 3132);
	t5 = SDL_GetTicks();

	activePUPS[0] = new PowerUp(2,12312, 2016);
	activePUPS[1] = new PowerUp(0, 5332, 3632);
	activePUPS[2] = new PowerUp(1, 8372, 3132);
	activePUPS[3] = new PowerUp(1, 3072, 6932);
	activePUPS[4] = new PowerUp(2, 5332, 3632);

	pArray[0] = new Tuple(12504,5248);
	pArray[1] = new Tuple(9032,4272);
	pArray[2] = new Tuple(12504,2880);
	pArray[3] = new Tuple(5652, 4432);
	pArray[4] = new Tuple(11472, 4412);
	pArray[5] = new Tuple(3072, 6932);
	pArray[6] = new Tuple(7352, 3132);
	pArray[7] = new Tuple(10112, 3572);
	pArray[8] = new Tuple(10572, 952);
	pArray[9] = new Tuple(12412, 4632);
	pArray[10] = new Tuple(5472, 6872);
	pArray[11] = new Tuple(12504,5248);
	pArray[12] = new Tuple(11552, 4632);
	pArray[13] = new Tuple(7312, 3832);
	pArray[14] = new Tuple(6072, 4492);
	pArray[15] = new Tuple(7172, 3852);
	pArray[16] = new Tuple(5332, 3632);
	pArray[17] = new Tuple(5372, 1852);
	pArray[18] = new Tuple(6572, 4592);
	pArray[19] = new Tuple(8372, 3132);
	for(int r=20; r<50; r++) {
		pArray[r] = new Tuple(0,0);
	}
	t7 = SDL_GetTicks();
	
	for(int i = 0; i<5 ; i++)
	{
	player->inventoryItems[i] = "";
	}
	player->hunger = "00";
	player->money = "1000";
	player->taskDone = "00";
	Hunger = player->hunger;
	Money = player->money;
	TaskDone = player->taskDone;
}

void Game::handleEvent()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	bool quit = false;
	while (!quit && firstScreen)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				// switch (e.key.keysym.sym)
				// { // Play high sound effect
				// case SDLK_1:
				// 	Mix_PlayChannel(-1, gHigh, 0);
				// 	break;

				// // Play medium sound effect
				// case SDLK_2:
				// 	Mix_PlayChannel(-1, gMedium, 0);
				// 	break;
				// case SDLK_9:
				// 	// If there is no music playing
				// 	if (Mix_PlayingMusic() == 0)
				// 	{
				// 		// Play the music
				// 		Mix_PlayMusic(gMusic, -1);
				// 	}
				// 	// If music is being played
				// 	else
				// 	{
				// 		// If the music is paused
				// 		if (Mix_PausedMusic() == 1)
				// 		{
				// 			// Resume the music
				// 			Mix_ResumeMusic();
				// 		}
				// 		// If the music is playing
				// 		else
				// 		{
				// 			// Pause the music
				// 			Mix_PauseMusic();
				// 		}
				// 	}
				// 	break;

				// case SDLK_0:
				// 	// Stop the music
				// 	Mix_HaltMusic();
				// 	break;
				// }
			}

			// Handle button events
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				gButtons[i].handleEvent(&e);
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		SDL_RenderClear(gRenderer);

		SDL_Rect cm = {0, 0, 50, 50};
		gbtexture1.render(40, 40, &cm);
		gPromptTexture.render(0, 0);
		// Render buttons
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			gButtons[i].renderStart();
		}

		// Update screen
		SDL_RenderPresent(gRenderer);
	}


    
    // printf("Here1");
    // player2->setx(std::stoi(p2x));
    // printf("Here2");
    // player2->sety(std::stoi(p2y));
    // printf("Here3");
    // player2->setFrame(std::stoi(curFrame));

	SDL_Color textColor1 = {255, 0, 0};
	timeText.str( "" );
	timeText <<  SDL_GetTicks() -startTime ; 
	string temp = timeText.str();
	int temp1 = std::stoi(temp)/1000;
	string temp2 = std::to_string(temp1);
	if( !gTimeTextTexture.loadFromRenderedText( temp2.c_str(), textColor1 ) )
			{
				printf( "Unable to render time texture!\n" );
			}
	if( !(gPopUpTextTexture.loadFromRenderedText( messageForPopUp, textColor1 ))  )
			{
				printf( "Unable to render time texture!\n" );
			}
			


	switch (e.type)
	{
	case SDL_QUIT:
	{
		isRunning = false;
		break;
	}

	case SDL_KEYDOWN:
	{
		SDL_Rect b = (player2->getCollider());
		switch( e.key.keysym.sym ) {
                case SDLK_UP:
                    player->objMove(KEY_PRESS_SURFACE_UP,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC,activeChance,activePUPS);
					player->changeFrame(KEY_PRESS_SURFACE_UP);
					t1 = SDL_GetTicks();
                    break;

                case SDLK_DOWN:
                    player->objMove(KEY_PRESS_SURFACE_DOWN,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC,activeChance,activePUPS);
                    player->changeFrame(KEY_PRESS_SURFACE_DOWN);
					t1 = SDL_GetTicks();
					break;

                case SDLK_LEFT:
                    player->objMove(KEY_PRESS_SURFACE_LEFT,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC,activeChance,activePUPS);
					player->changeFrame(KEY_PRESS_SURFACE_LEFT);
					t1 = SDL_GetTicks();
                    break;

                case SDLK_RIGHT:
                    player->objMove(KEY_PRESS_SURFACE_RIGHT,b,map->Colliders,activeNPC,NUM_ACTIVE_NPC,activeChance,activePUPS);
					player->changeFrame(KEY_PRESS_SURFACE_RIGHT);
					t1 = SDL_GetTicks();
                    break;
				case SDLK_i:

					openInventory = true;

					break;
	
				case SDLK_m:

					if(loc1eat)
					{
					openMenu1 = true;
					loc1eat= false;
					}
					if(loc2eat)
					
					{
					openMenu2 = true;
					loc2eat= false;
					}

					break;
				case SDLK_t:
					printf("6");
					openTaskSchedule = true;

					break;
				case SDLK_o:

					openInventory = false;
					openTaskSchedule = false;
					openTeleportMenu = false;
					openMenu1 = false;
					openMenu2 = false;
					break;
				case SDLK_y:
				if(display == "YULU STAND")
				{
					player->Yulu = true;
					player->toggleYulu();
					
				}
				break;
				case SDLK_q:
				if(display == "YULU STAND")
				{
					player->Yulu = false;
					player->toggleYulu();
					
				}
				break;
			
				
				case SDLK_c:
				if(display == "HIMADRI CIRCLE")     //himadri circle clothes done
				{
				player-> addItems("clothes");
				player->numInventoryItems++;
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "clothes in inventory";	

				break;
				}
				if(display == "JWALAMUKHI")  //hostel done
				{
				player-> addItems("laptop");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "laptop in inventory";


				break;
				}
				if(display == "SAC")      //sac done
				{
				player-> addItems("camera");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "camera in inventory";				



				break;
				}
				if(display == "NEW LHC")  
				{
				
				player-> addItems("passes");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "passes in inventory";


				break;
				}
				if(display == "SATPURA")  //shoes done
				{
				player-> addItems("shoes");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "shoes in inventory";


				break;
				}
				if(display == "RAJDHANI")  //lock
				{
				player-> addItems("key");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "key in inventory";


				break;
				}
				if(display == "METRO GATE")
				{
				player-> addItems("refreshments");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "refreshments in inventory";

				break;
				}
				if(display == "MAIN GATE")
				{
				player-> addItems("refreshmentsmain");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "refreshments in inventory";

				break;
				}
				if(display == "CENTRAL LIBRARY")
				{
				player-> addItems("facche");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "captured newbies in inventory";

				break;
				}
			
				if(display == "SBI")
				{
				player-> addItems("cash");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "cash in inventory";
				break;
				}
				
				if(display == "Dept Of Design")
				{
				player-> addItems("pendant");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "pendant in inventory";
				break;

				}
				if(display == "AMUL")
				{
				player-> addItems("water");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "water in inventory";
				break;

				}
				if(display == "SPORTS GROUNDS")
				{
				player-> addItems("cones");
				toGivePopUp= true;
				dispTime= SDL_GetTicks();
				messageForPopUp = "cones in inventory";
				break;

				}
				
				
				
				
				case SDLK_d:
			
		
				
				
				if(display == "SAC")      //sac done
				{
				if(player-> removeItems("laptop"))
				{
				bringLaptop = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				if(player-> removeItems("key")){
				fixKey = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				
				}
				break;
				}
				
				
				if(display == "NEW LHC")  
				{
				
				if(player-> removeItems("facche"))
				{
				faccheForSponsor = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				if(player-> removeItems("cash"))
				{
				sponsorCash = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				break;
				}
				
				
				if(display == "MECH LAWNS")
				{
					if(player-> removeItems("camera"))
					
				{
				cameraForBRCA = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
					if(player-> removeItems("refreshmentsmain"))
				{
				refreshmentsForBRCA = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				
				if(display == "RED SQUARE")
				{
					if(player-> removeItems("camera"))
				{
				cameraForRedSq = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
					if(player-> removeItems("water"))
				{
				waterForRedSq = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}	
				break;
				}
		
				if(display == "NALNADA")
				{
					if(player-> removeItems("cones"))
				{
				conesForNalanda = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
					if(player-> removeItems("shoes"))
				{
				shoesForNalanda = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}	
				break;
				}
			
				
				if(display == "SPORTS GROUNDS")
				{
				if(player-> removeItems("passes"))
				{
				passesForPronite = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				if(player-> removeItems("pendant"))
				{
				pendantForPronite = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				break;

				}
				
				
				if(display == "CSC")
				{
				if(player-> removeItems("refreshments"))
				{
				bringCSCrefreshments = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				if(player-> removeItems("clothes"))
				{
				clothesCSC = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				break;
				}
				
				if(display == "STAFF CANTEEN")
				{
				lunch = true;
				int i = std::stoi(player->taskDone );
				i++;
				player->taskDone = std::to_string(i);
				}
				break;
				
				case SDLK_x:
					if (display=="BHARTI BUILDING"){
						openTeleportMenu = true;
					}
				break;

				case SDLK_0:
					if (display=="BHARTI BUILDING"){
						openTeleportMenu = false;
						player->objTeleport(0);
					}
					break;

				case SDLK_1:
					if (display=="BHARTI BUILDING"){
						openTeleportMenu = false;
						player->objTeleport(1);
					}
					break;

				case SDLK_2:
					if (display=="BHARTI BUILDING"){
						openTeleportMenu = false;
						player->objTeleport(2);
					}
					break;

				case SDLK_3:
					if (display=="BHARTI BUILDING"){
						openTeleportMenu = false;
						player->objTeleport(3);
					}
					break;
				
		// Play high sound effect
		// case SDLK_1:

		// 	Mix_PlayChannel(-1, gHigh, 0);
		// 	break;

		// // Play medium sound effect
		// case SDLK_2:
		// 	Mix_PlayChannel(-1, gMedium, 0);
		// 	break;
		// case SDLK_9:
		// 	// If there is no music playing
		// 	if (Mix_PlayingMusic() == 0)
		// 	{
		// 		// Play the music
		// 		Mix_PlayMusic(gMusic, -1);
		// 	}
		// 	// If music is being played
		// 	else
		// 	{
		// 		// If the music is paused
		// 		if (Mix_PausedMusic() == 1)
		// 		{
		// 			// Resume the music
		// 			Mix_ResumeMusic();
		// 		}
		// 		// If the music is playing
		// 		else
		// 		{
		// 			// Pause the music
		// 			Mix_PauseMusic();
		// 		}
		// 	}
		// 	break;

		// case SDLK_0:
		// 	// Stop the music
		// 	Mix_HaltMusic();
		// 	break;

		default:
			break;
		}

		break;
	}

	break;
	}
	musicOnButton.handleEvent(&e);
	musicOffButton.handleEvent(&e);
}
}

void Game::update()
{
    /*parameters = (char*) (std::to_string(player->getHappyness()) + std::to_string(player->getx()) + std::to_string(player->gety()) + std::to_string(player->hasHammer) + std::to_string(player->usedTeleport) + std::to_string(player->usedHammer) + std::to_string(player->frame)).c_str(); */
    parameters[0] = (char)player->getHappyness() / 100;
    parameters[1] = (char) ((player->getHappyness()/10) % 10);
    parameters[2] = (char) player->getHappyness() % 10;
    parameters[3] = (char) player->getx()/10000;
    parameters[4] = (char) (player->getx()/1000 %10);
    parameters[5] = (char) (((player->getx()/100) %100)%10);
    parameters[6] = (char) ((player->getx()%100 )/10);
    parameters[7] = (char) (player->getx()%10);
    parameters[8] = (char) player->gety()/10000;
    parameters[9] = (char) (player->gety()/1000 %10);
    parameters[10] = (char) (((player->gety()/100) %100)%10);
    parameters[11] = (char) ((player->gety()%100 )/10);
    parameters[12] = (char) (player->gety()%10);
    parameters[13] = (char) player->hasHammer;
    parameters[14] = (char) player->usedTeleport;
    parameters[15] = (char) player->usedHammer;
    parameters[16] = (char) (player->frame /10);
    parameters[17] = (char) (player->frame %10);   
    player->hasHammer = 0;
    player->usedTeleport = 0;
    player->usedHammer = 0;
    send(sock, parameters, 64, 0);
    
     valread = read(sock, buffer, 64); //SEE THIS
     printf(std::to_string(valread).c_str());
    printf(strerror(errno));
    string p2score = std::to_string(buffer[0]) + std::to_string(buffer[1]) + std::to_string(buffer[2]);
    string p2x = std::to_string(buffer[3])+std::to_string(buffer[4])+std::to_string(buffer[5])+std::to_string(buffer[6])+std::to_string(buffer[7]);
    string p2y = std::to_string(buffer[8])+std::to_string(buffer[9])+std::to_string(buffer[10])+std::to_string(buffer[11])+std::to_string(buffer[12]);
    string hasHam = std::to_string(buffer[13]);
    string usedTel = std::to_string(buffer[14]); 
    string usedHam = std::to_string(buffer[15]);
    string curFrame = std::to_string(buffer[16]) + std::to_string(buffer[17]); 
    
	player->objUpdate();
	player2->objUpdate();
	display = (string) (map->getRegion(player->getx(),player->gety()));
	
	
	
	if (!loadTextMedia())
				{
					printf("Failed to load text media for taskbar!\n");
				}

	t4 = SDL_GetTicks();
	if (t4-t3 > 10000){
		t3 = t4;
		posIndex++;
		if (posIndex>19){
			posIndex =0;
		}
		professor->setx(posArray[posIndex]->fst);
		professor->sety(posArray[posIndex]->snd);
	}

	professor->NPCMove(map->Colliders,player->getx(),player->gety());

	t6 = SDL_GetTicks();
	if (t6-t5>8000){
		t5 = t6;
		int min = 0;
		int max = 19;
		int range = max - min + 1;

		for(int i=0; i<NUM_ACTIVE_CHANCE; i++) {
			cIndex1 = rand()%range + min;
			activeChance[i]->setx(cArray[cIndex1]->fst);
			activeChance[i]->sety(cArray[cIndex1]->snd);
		}
		
	}

	t8 = SDL_GetTicks();
	if (t8-t7>8000){
		t7 = t8;
		int min = 0;
		int max = 49;
		int range = max - min + 1;

		for(int i=0; i<NUM_ACTIVE_PUPS; i++) {
			pIndex = rand()%range + min;
			activePUPS[i]->setx(pArray[pIndex]->fst);
			activePUPS[i]->sety(pArray[pIndex]->snd);
		}
		
	}

	professor->objUpdate();

	for(int i=0; i<NUM_ACTIVE_CHANCE; i++) {
		activeChance[i]->objUpdate();
	}

	for(int i=0; i<NUM_ACTIVE_PUPS; i++) {
		activePUPS[i]->objUpdate();
	}


	gCamera.x = (player->getx() - 400);
	gCamera.y = (player->gety() - 300);

	if (player->inMotion == false) {
		t2 = SDL_GetTicks();
		if (t2-t1 > 100){
			if (!(player->Yulu)) {
				player->frame = 0;
			} else {
				player->frame = 18;
			}
		}
	} 

	player->inMotion = false;

	// if( gCamera.x < 0 ) {
	//     gCamera.x = 0;
	// }
	// if( gCamera.y < 0 ) {
	//     gCamera.y = 0;
	// }
	// if( gCamera.x > 32*(map->MAP_X) - gCamera.w ){
	//     gCamera.x = (map->MAP_X) - gCamera.w;
	// }
	// if( gCamera.y > 32*(map->MAP_Y) - gCamera.h ) {
	//     gCamera.y = (map->MAP_Y) - gCamera.h;
	// }
	string temp = timeText.str();
	int temp1 = std::stoi(temp)/10;
	//string temp2 = std::to_string(temp1);
	if(temp1 % 600 ==0)
	{
	int i = std::stoi(player->hunger);
	i+=1;
	player->hunger = std::to_string( i);
	Hunger = player->hunger;
	TaskDone = player->taskDone;
	player -> updateHappyness();

	}
	
	if(player->Yulu)
	{
	int temp1 = std::stoi(temp)/20;
	if(temp1 % 100 ==0)
	{
	int mon = std:: stoi(player->money);
	mon -= 10;
	player->money = std::to_string(mon);
	Money = player->money;
	player-> updateHappyness();
	}
	}
}

void Game::render()
{
	SDL_RenderClear(gRenderer);
	map->DrawMap(gCamera.x, gCamera.y);		 // draw map
	player->objRender(gCamera.x, gCamera.y); // players over map
	// player->objRender();
	player2->objRender(gCamera.x, gCamera.y);
	professor->objRender();
	for(int i=0; i<NUM_ACTIVE_CHANCE; i++) {
		activeChance[i]->objRender();
	}

	for(int i=0; i<NUM_ACTIVE_PUPS; i++) {
		activePUPS[i]->objRender();
	}

	if(player->activePowerUp != -1) {
		if (player->activePowerUp == 0) {
			player->addPowerUps("hammer");
		} else if (player->activePowerUp == 1) {
			player->addPowerUps("phone");
		} else {
			player->addPowerUps("teleporter");
		}
		// Logic for any rendering and stuff ADD HERE
		player->activePowerUp = -1;
	} 

	if(player->gotChance == true) {
		// Logic for any rendering and stuff ADD HERE
		player->gotChance = false;
	} 

	map->DrawplayerOneScore(); // scoreboard over map
	map->DrawHappinessBarU();
	map->DrawHappinessBarO(player->getHappyness());

	SDL_Rect fillRect = {0, 500, 800, 100}; // task bar over map
	SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);

	// Render black outlined quad
	SDL_Rect outlineRect = {0, 500, 800, 103};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0000, 0x00, 0xFF);
	SDL_RenderDrawRect(gRenderer, &outlineRect);
	if (openInventory)
	{

		SDL_Rect fillRect1 = {0, 200, 800, 100}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect1);
		for (int i = 0; i < 5; i++)
		{

			string s = player->getIElem(player->inventoryItems, i);
			map->Drawitems(s, i);
		}
	}
		if (openTaskSchedule)
	{

		SDL_Rect fillRect2 = {250, 200, 300, 300}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect2);
		SDL_Color textColor2 = {255, 0, 0};
		for (int i = 0; i < 5; i++)
		{

			string s = player->getIElem(player->tasks, i);
				if( !(gTaskTextTexture.loadFromRenderedText( s, textColor2 ))  )
			{
				printf( "Unable to render time texture!\n" );
			}
			gTaskTextTexture.render(270, 240 +40*i);
		}
	}

		if (openMenu1)
	{

		SDL_Rect fillRect3 = {200, 200, 300, 300}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect3);
		
		

						map->DrawMenu("menu1");
		
	}
		if (openMenu2)
	{

		SDL_Rect fillRect4 = {200, 200, 300, 300}; // task bar over map
		SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect4);
		
		


			map->DrawMenu("menu2");
		
	}

	if (openTeleportMenu){
			SDL_Rect fillRect5 = {250, 200, 300, 300}; // task bar over map
			SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect5);
			SDL_Color textColor2 = {255, 0, 0};
			for (int i = 0; i < 4; i++)
			{
				string s;
				if (i==0){
					s = "Press 0 for Jwalamukhi";
				} else if (i==1){
					s = "Press 1 for SAC";
				} else if (i==2){
					s = "Press 2 for Himadri";
				} else {
					s = "Press 3 for Rajdhani";
				}
					if( !(gTeleportTextTexture.loadFromRenderedText( s, textColor2 ))  )
				{
					printf( "Unable to render teleport texture!\n" );
				}
				gTeleportTextTexture.render(270, 240 +40*i);
			}
		}
	gTextTexture.render(300, 530); // text over task bar
	gHungerTexture.render(580, 90); // text over task bar
	gMoneyTexture.render(580, 115); // text over task bar
	gTaskCompletedTexture.render(580, 140); // text over task bar
	for (int i =0; i<2;i++)
	{
	string s =player->getIElem(player->powerUps,i);
	map->DrawPowerUps(s,i);
	
	}
	

	gTimeTextTexture.render( 300,50 );
	if(toGivePopUp)
	{
	gPopUpTextTexture.render( 300,300 );
	if(SDL_GetTicks()- dispTime > 3000)
	{
	toGivePopUp= false;;
	}
	
	}
	if (musicOn)
	{
		musicOnButton.renderMusic();
	}
	if (!musicOn)
	{
		printf("5");
		musicOffButton.renderMusic();
	}
	SDL_RenderPresent(gRenderer);
}

void Game::clean()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
	gbtexture1.free();
}

bool Game::running()
{
	if (isRunning)
	{
		return true;
	}
	else
	{
		return false;
	}
}
