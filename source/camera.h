#ifndef H_camera
#define H_camera

#include "constants.h"

class camera
{
public:
	//constructor
	//takes starting cord, then background IDs
	camera(int, int,int,int);
	//moves camera
	void panLeft();
	void panRight();
	void panUp();
	void panDown();
	//renders
	void update();
	//returns private values
	s16 getX();
	s16 getY();
private:
	s16 x;
	s16 y;
	int bg;
	int bg2;
};

#endif