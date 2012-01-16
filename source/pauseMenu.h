#ifndef H_pause
#define H_pause

#include "constants.h"
#include "pause.h"

class pauseMenu
{
public:
	//constructor
	pauseMenu();
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
};

#endif