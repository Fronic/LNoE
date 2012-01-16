#ifndef H_heroType
#define H_heroType

#include "constants.h"

//Hate using type in class names; forced to because gfx
class heroType
{
public:
	heroType();
	//constructor sets starting location on screen
	heroType(int tempX, int tempY);
	//initualizes other stuff
	void init(heroType *sprite, u8* gfx);
	void init(int tempX, int tempY,heroType *sprite, u8* gfx);
	//animates the hero
	void animate();
	void moveHero(int direction);
	//all kinds of get and set functions
	int getX();
	int getY();
	int getFrame();
	void setFrame(int);
	void addFrame();
	void setState(int);
	u16* getGfx();
	void setLife(int);
	void addLife(int);
	int getLife();
	//displays the hero's health
	void displayHealth();

private:
	//x and y position on the actual screen
	int x;
	int y;
	//health stuff
	int health;
	int maxHealth;

	//graphics stuff for the hero and his health
	u16* sprite_gfx_mem;
	u8*  frame_gfx;
	//health is a vector to be able to display dynamic amounts of life
	std::vector<u16*> heart_gfx_mem;
	std::vector<u8*>  heart_frame_gfx;

	//finds the direction and frame in that direction the hero is facing
	int state;
	int anim_frame;

	//used to make the sprite move more natural speeds
	int frameDelay;
};

#endif