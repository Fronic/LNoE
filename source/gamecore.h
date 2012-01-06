#ifndef H_game
#define H_game

#include "constants.h"

class State;

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
	//vector<State*> states;
	int keys;
	bool playing;
};

#endif