#ifndef H_Mmenu
#define H_Mmenu

#include "constants.h"
#include "mainscreen.h"
#include "mainscreenBot.h"


class mainMenu
{
public:
	//constructor
	//takes starting cord, then background IDs
	mainMenu();
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();
	bool getStatus();

private:
	//vector<State*> states;
	bool initiated;
	touchPosition touch;
	int bg3;
	int bg2;
};

#endif