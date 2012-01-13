#ifndef H_core
#define H_core

#include "constants.h"
#include "mainMenu.h"
#include "mainGame.h"
#include "splashScreen.h"
#include "pauseMenu.h"


class gamecore
{
public:
	//constructor
	//takes starting cord, then background IDs
	gamecore();
	void run();
	void initiate();
	//void events(heroType, camera);
	void process();
	//renders
	void render();
	

private:
	mainGame game;
	mainMenu menu;
	splashScreen splash;
	pauseMenu pause;
	uint8 currentState;
	bool CUNT;
};

#endif