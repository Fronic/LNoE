#ifndef H_game
#define H_game

#include "constants.h"


class mainGame
{
public:
	//constructor
	//takes starting cord, then background IDs
	mainGame();
	void initiate();
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();
	void fight(int);
	bool detectCollision(int);
	bool getStatus();
	void setStatus(bool);

private:
	int keys;
	bool game;
	bool pause;
	bool initiated;
	int count;
	int hurtTimer;
	int random;
	int bg2;
	int bg3;
	//make our hero
	heroType hero;
	camera cam;
	vector<zombieType> zombies;
};

#endif