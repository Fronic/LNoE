#ifndef H_splash
#define H_splash

#include "constants.h"
#include "splash.h"


class splashScreen
{
public:
	//constructor
	//takes starting cord, then background IDs
	splashScreen();
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();
	bool getStatus();

private:
	bool initiated;
	int timer;
	touchPosition touch;
	int bg3;
	int bg2;
};

#endif