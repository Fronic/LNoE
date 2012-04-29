#ifndef H_ScoreScreen
#define H_ScoreScreen

#include "constants.h"
#include "scorescreen.h"

class ScoreScreen
{
public:
	//constructor
	ScoreScreen();
	//initiates other stuff
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();

	bool getStatus();

private:
	touchPosition touch; //touch
	int keys;
	bool initiated;
	int bg1;
	PrintConsole pcBtm;
};

#endif