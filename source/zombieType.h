#ifndef H_zombieType
#define H_zombieType

#include "constants.h"
#include "camera.h"
class camera; //so this class can access a camera object
//Hate using type in class names; forced to because gfx
class zombieType
{
public:
	//constructor
	zombieType();
	//random
	void startRandom();
	int getTime();
	//initualizes other stuff
	void init();
	//animates the zombie
	void animate();
	void render(int, camera &);
	void render(int, camera &, bool);
	void move(int, int);
	//all kinds of get and set functions
	int getX();
	int getY();
	int getFrame();
	void setFrame(int);
	void addFrame();
	void setState(int);
	u16* getGfx();

	//checks if zombie is offScreen
	bool offScreen(camera &);
private:
	int x;
	int y;
	int health;

	//sprite stuff
	u16* sprite_gfx_mem;
	u8*  frame_gfx;
	int state;
	int anim_frame;

	//moves frames more naturally
	int frameDelay;
};

#endif