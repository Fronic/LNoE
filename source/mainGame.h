#ifndef H_game
#define H_game

#include "constants.h"


class mainGame
{
public:
	//constructor
	//takes starting cord, then background IDs
	mainGame();
	void run();
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();
	void fight(int);

private:
	//vector<State*> states;
	int keys;
	bool game;
	bool pause;
	int count;
	int hurtTimer;
	int random;
	//make our hero
	heroType hero;
	camera cam;
	vector<zombieType> zombies;
};

#endif