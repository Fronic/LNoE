#ifndef H_zombieType
#define H_zombieType

#include "constants.h"
class camera; //so this class can access a camera object
//Hate using type in class names; forced to because gfx
class zombieType
{
public:
	//constructor sets starting location on screen
	zombieType();
	void startRandom();
	int getTime();
	//initualizes other stuff
	void init();
	//animates the hero
	void animate();
	void render(int, camera &came);
	void move(int, int);
	//all kinds of get and set functions
	int getX();
	int getY();
	int getFrame();
	void setFrame(int);
	void addFrame();
	void setState(int);
	u16* getGfx();
private:
	int x;
	int y;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;

	int state;
	int anim_frame;

	int frameDelay;
};

#endif