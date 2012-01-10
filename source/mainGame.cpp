#include "mainGame.h"

mainGame::mainGame()
{
	game = true;
	pause = false;
	count=0;

	//initualize vram, oam, console, and switch the screens
	initiate();

	//further initualizes what our hero needs to blit
	hero.init(112,80,&hero, (u8*)heroTiles);
	//sets up our backgrounds
	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_512x512,0,0);
	dmaCopy(grassBitmap, bgGetGfxPtr(bg3), grassBitmapLen);
	dmaCopy(grassPal, BG_PALETTE, grassPalLen);
	int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_512x512, 0,0);
	dmaCopy(grassBitmap, bgGetGfxPtr(bg2), grassBitmapLen);
	dmaCopy(grassPal, BG_PALETTE, grassPalLen);

	//initualizes our "camera" it starts at (0,0) and takes the backgrounds' IDs
	cam.init(0,0,bg3,bg2);
	hero.animate();	//ensures our hero is blitted at least once
	//vector<zombieType> zombies(1);

}
/*void mainGame::run()
{
while(game)
{
events();
processMain();
renderMain();
}
}*/
void mainGame::initiate()
{
	lcdMainOnBottom(); //switches screens; main is on bottom, sub on top

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_0_2D); 
	vramSetBankH(VRAM_H_SUB_BG );
	consoleDemoInit();

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);	
	vramSetBankE(VRAM_E_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_256, true);
	vramSetBankF(VRAM_F_LCD);

	dmaCopy(heroPal, VRAM_F_EXT_SPR_PALETTE[1], 512);
	dmaCopy(zombiePal, VRAM_F_EXT_SPR_PALETTE[0], 512);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
}

int mainGame::events()
{
	scanKeys();

	int keys = keysHeld();

	if(keys & KEY_START)
	{
		return EXIT;
	}

	//following if statements handle movement and camera movement
	if(keys && count%2==0)
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
	return MAINGAME;
}

void mainGame::processMain()
{
	count++;
	if (count>600 && zombies.size()<12)
	{
		zombieType * another = new zombieType;
		zombies.push_back(*another);
		delete another;
		count = 0;
	}
	//checks key inputs; also a break out of the game
	/*if(count%2==0)
	{
		events();
	}*/
	int keys = keysHeld();

	if(keys & KEY_START) game = false;

	//updates camera movements
	cam.update();

	//wait for VBlank and update the OAM
	if(count%6==0)
	{
		for(int i=0;i < zombies.size();i++)
		{
			zombies[i].move(hero.getX()+cam.getX() +8,hero.getY()+cam.getY()+9);
			zombies[i].render(i+1, cam);
		}
	}
	for(int i=0;i < zombies.size();i++)
	{
		if(zombies[i].getX() == (hero.getX()+cam.getX() +8) && zombies[i].getY() == (hero.getY()+cam.getY()+9))
		{
			game = false;
			cout << "GAME OVER" << endl;
		}
	}
}
void mainGame::processSub()
{
	//couts some nice info
	cout << "\x1b[2J";
	cout << "scrollX: " << cam.getX() << endl;
	cout << "scrollY: " << cam.getY() << endl;
	cout << "hero.x: " << hero.getX() << endl;
	cout << "hero.y: " << hero.getY() << endl;
	cout << "Hero's actual Location: " << hero.getX()+cam.getX() +8 << " " << hero.getY()+cam.getY()+9 << endl;
	cout << "Key Pressed: " << keys <<endl;
	cout << "zombie 1: " << zombies[0].getX() << " " << zombies[0].getY() << endl
		<< zombies[0].getX()-cam.getX() << " " << zombies[0].getY()-cam.getY() << endl;
	cout << "zombie 2: " << zombies[1].getX() << " " << zombies[1].getY() << endl
		<< zombies[1].getX()-cam.getX() << " " << zombies[1].getY()-cam.getY() << endl;
	cout << "TIME " << zombies[0].getTime() << endl;
	cout << "TIME2 " << time(NULL) << endl;
}
//renders
void mainGame::renderMain()
{
	oamUpdate(&oamMain);
}
void mainGame::renderSub()
{
	oamUpdate(&oamSub);
}