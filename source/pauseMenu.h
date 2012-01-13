#ifndef H_pause
#define H_pause

#include "constants.h"
#include "pause.h"

class pauseMenu
{
public:
	//constructor
	//takes starting cord, then background IDs
	pauseMenu();
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();
	bool getStatus();

private:
	touchPosition touch;
	int keys;
	bool game;
	bool pause;
	bool initiated;
	int count;
	int hurtTimer;
	int random;
	int bg1;
};

#endif