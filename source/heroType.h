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
	void displayHealth();

private:
	int x;
	int y;
	int health;
	int maxHealth;

	u16* sprite_gfx_mem;
	u8*  frame_gfx;
	vector<u16*> heart_gfx_mem;
	vector<u8*>  heart_frame_gfx;

	int state;
	int anim_frame;
	vector<int> heart_state;
	vector<int> heart_anim_frame;

	int frameDelay;
};

#endif