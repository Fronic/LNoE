#include "gamecore.h"

gamecore::gamecore()
{
	playing = true;
	initiate();
}
	void gamecore::run()
	{
		while(playing)
		{
			//events();
			process();
			render();
		}
	}
	void gamecore::initiate()
	{
	lcdMainOnBottom(); //switches screens; main is on bottom, sub on top

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_0_2D); 
	vramSetBankH(VRAM_H_SUB_BG );
	consoleDemoInit();

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);	
	vramSetBankE(VRAM_E_MAIN_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_128, false);
	}
	/*
	void events(heroType &hero,camera &cam)
{
	scanKeys();

	int keys = keysHeld();

	//following if statements handle movement and camera movement
	if(keys)
	{

		if(keys & KEY_UP)
		{
			if(hero.getY() <= SCREEN_TOP-9) //hero is going up not at top of map
			{
				hero.moveHero(W_UP); //move hero down
			}
			cam.panUp(); //move cam up; it stops itself from going over the map
			if(hero.getY() > SCREEN_BOTTOM - 80) //hero is at the bottom of the screen
			{
				hero.moveHero(W_DOWN); //move hero up
				cam.panDown(); //keeps cam centered
			}
			else if(cam.getY() <1) //cam is at the top of the map
			{
				hero.moveHero(W_DOWN); //move hero up
			}

			hero.setState(W_UP); //hero is facing up
		}
		//the rest follow the same format
		if(keys & KEY_LEFT)
		{
			if(hero.getX() <= SCREEN_LEFT-8) hero.moveHero(W_LEFT);
			cam.panLeft();

			if(hero.getX() > SCREEN_RIGHT-108)
			{
				hero.moveHero(W_RIGHT);
				cam.panRight();
			}
			else if(cam.getX() < 1)
			{
				hero.moveHero(W_RIGHT);
			}

			hero.setState(W_LEFT);
		}
		if(keys & KEY_RIGHT)
		{
			if(hero.getX() >= SCREEN_RIGHT+12) hero.moveHero(W_RIGHT);
			cam.panRight();

			if(hero.getX() < SCREEN_LEFT+112)
			{
				hero.moveHero(W_LEFT);
				cam.panLeft();
			}
			else if(cam.getX() > 767) //if cam is on the right edge
			{
				hero.moveHero(W_LEFT);
			}

			hero.setState(W_RIGHT);
		}
		if(keys & KEY_DOWN)
		{
			if(hero.getY() >= SCREEN_BOTTOM) hero.moveHero(W_DOWN);
			cam.panDown();
			if(hero.getY() < SCREEN_TOP + 80)
			{
				hero.moveHero(W_UP);
				cam.panUp();
			}
			else if(cam.getY() >319)
			{
				hero.moveHero(W_UP);
			}


			hero.setState(W_DOWN);
		}

		hero.addFrame(); //changes hero's frame to the next one

		if(hero.getFrame() >= FRAMES_PER_ANIMATION) hero.setFrame(0); //resets frame to initual one
		hero.animate(); //render it
	}
}
*/
	void gamecore::process()
	{

	}
	//renders
	void gamecore::render()
	{

	}