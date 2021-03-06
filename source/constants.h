#ifndef H_const
#define H_const

//ndslib
#include <nds.h>

//regular c/c++ stuff
#include <stdio.h>
#include <iostream>
#include <vector>
#include "time.h"

//using namespace std;

//image includes
#include "grass.h"
#include "hero.h"
#include "zombie.h"
#include "life.h"

//classes

#include "heroType.h"
#include "zombieType.h"
#include "camera.h"

//defines
#define FRAMES_PER_ANIMATION 3
#define FRAMES_PER_ANIMATION_Z 4

//---------------------------------------------------------------------
// The state of the sprite (which way it is walking)
//---------------------------------------------------------------------
#define W_UP 0
#define W_RIGHT 1
#define W_DOWN 2
#define W_LEFT 3
//---------------------------------------------------------------------
// The state of the sprite (which way it is walking)
//---------------------------------------------------------------------
#define Z_UP 0
#define Z_RIGHT 3
#define Z_DOWN 1
#define Z_LEFT 2
//---------------------------------------------------------------------
// Screen dimentions
//---------------------------------------------------------------------
#define SCREEN_TOP 0
#define SCREEN_BOTTOM 160
#define SCREEN_LEFT 0
#define SCREEN_RIGHT 220
//---------------------------------------------------------------------
// Map dimentions
//---------------------------------------------------------------------
#define MAP_WIDTH 512
#define MAP_HEIGHT 1024
//---------------------------------------------------------------------
// Game States
//---------------------------------------------------------------------
#define MAINMENU 0
#define MAINGAME 1
#define PAUSEMENU 2
#define SPLASHSCREEN 3
#define SCORESCREEN 4
#define EXIT 5


	//struct for saving
struct Scores
{
	int spot[10], nextEmpty;
};
static Scores scores;

#endif