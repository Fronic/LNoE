#ifndef H_Mmenu
#define H_Mmenu

#include "constants.h"
#include "mainscreen.h"
#include "mainscreenBot.h"


class mainMenu
{
public:
	//constructor
	mainMenu();
		//initiates other stuff; mainly for going from other states
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();

	bool getStatus();

private:
	//if the vram and other stuff needs to be reinitiated
	bool initiated;
	//touch
	touchPosition touch;
	int bg3;
	int bg2;
};

#endif