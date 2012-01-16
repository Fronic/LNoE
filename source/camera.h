#ifndef H_camera
#define H_camera

#include "constants.h"

class camera
{
public:
	//constructors
	camera();
	//takes starting cord, then background IDs
	camera(int, int,int,int);
	void init(int, int , int, int);
	//moves camera
	void panLeft();
	void panRight();
	void panUp();
	void panDown();
	//renders changes
	void update();
	//returns private values
	s16 getX();
	s16 getY();
private:
	//top left cords
	s16 x;
	s16 y;
	//bg's used by this game
	int bg;
	int bg2;
};

#endif