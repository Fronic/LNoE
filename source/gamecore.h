#ifndef H_core
#define H_core

#include <iostream>
#include <fstream>
#include <nds.h>
#include <fat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "mainMenu.h"
#include "mainGame.h"
#include "splashScreen.h"
#include "pauseMenu.h"


class gamecore
{
public:
	//constructor
	gamecore();
	//runs the game
	void run();
	//saves the game's scores
	void saveScore(int);
	struct Scores
{
	int spot[10], nextEmpty;
}scores;

private:
	//instances of the objects that makeup the game
	mainGame game;
	mainMenu menu;
	splashScreen splash;
	pauseMenu pause;
	//holds the state of the game
	uint8 currentState;
	//keeps loop going
	bool CUNT;
};

#endif