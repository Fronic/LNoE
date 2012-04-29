#ifndef H_game
#define H_game

#include "constants.h"


class mainGame
{
public:
	//constructor
	mainGame();
	//initiates other stuff; mainly for going from other states
	void initiate();
	//game logic
	int events();
	void processMain();
	void processSub();
	//renders
	void renderMain();
	void renderSub();
	//handles a zombie/hero fight(takes in zombie position in vector)
	void fight(int);
	//simple collision detection between zombie/hero
	bool detectCollision(int);
	//get and set functions
	bool getStatus();
	void setStatus(bool);
	int getScore();

private:
	//key input
	int keys;
	//checks if the vram and other stuff needs to be reinitiated
	bool initiated;
	unsigned int gameTimer;
	int score;
	int count; //delays stuff
	int hurtTimer; //delays getting hurt again
	int random;
	int bg2;
	int bg3;
	//make our hero
	heroType hero;
	//make a cam
	camera cam;
	//makes and holds zombies
	std::vector<zombieType> zombies;
};

#endif