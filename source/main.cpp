//============================================================================
//
//	Author: Devlin Richberger
//	Description: Revisioning of the board game Last Night on Earth for DS
//	Version: 0.0.11
//	----
//	TODO
//	----
//	Short-Term: make lose conditions, run game as an object
//	Long-Term: let player fight back/win conditions, game menu, saving 
//	Distant-Term: hero abilities, weapons, zombie abilities, multiplayer
//
//============================================================================

#include "constants.h" //has all includes, consts and other stuffs

void initualize(); //initualizes VRAM and other stuffs
void events(heroType &,camera &); //checks for key events and handles them


int main(void)
{
	int count=0;
	//make our hero
	heroType hero(112,80);

	//initualize vram, oam, console, and switch the screens
	initualize();

	//further initualizes what our hero needs to blit
	hero.init(&hero, (u8*)heroTiles);
	dmaCopy(heroPal, SPRITE_PALETTE, 512);

	//sets up our backgrounds
	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_512x512,0,0);
	dmaCopy(grassBitmap, bgGetGfxPtr(bg3), grassBitmapLen);
	dmaCopy(grassPal, BG_PALETTE, grassPalLen);
	int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_512x512, 0,0);
	dmaCopy(grassBitmap, bgGetGfxPtr(bg2), grassBitmapLen);
	dmaCopy(grassPal, BG_PALETTE, grassPalLen);

	//initualizes our "camera" it starts at (0,0) and takes the backgrounds' IDs
	camera cam(0,0,bg3,bg2);
	hero.animate();	//insures our hero is blitted at least once
	vector<zombieType> zombies(1);

	while(1) { 
		count++;
		if (count>600 && zombies.size()<12)
		{
			zombieType * another = new zombieType;
			zombies.push_back(*another);
			delete another;
			count = 0;
		}
		//checks key inputs; also a break out of the game
		if(count%2==0)
		{
		events(hero, cam);
		}
		int keys = keysHeld();

		if(keys & KEY_START) break;

		//updates camera movements
		cam.update();

		//wait for VBlank and update the OAM
		if(count%6==0)
		{
			for(int i=0;i < zombies.size();i++)
			{
				zombies[i].move(hero.getX()+cam.getX() +8,hero.getY()+cam.getY()+9);
				if(zombies[i].getX() > cam.getX() && zombies[i].getX() < cam.getX() + SCREEN_RIGHT && zombies[i].getY() > cam.getY() && zombies[i].getY() < cam.getY() + SCREEN_BOTTOM)
				{
					/*oamSet(&oamMain, i+1, zombies[i].getX()-cam.getX(), zombies[i].getY()-cam.getY(), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
						zombies[i].getGfx(), -1, false, false, false, false, false);*/
					zombies[i].render(i+1, cam);
				}
				else
				{
					oamSet(&oamMain, i+1, zombies[i].getX()-cam.getX(), zombies[i].getY()-cam.getY(), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
						zombies[i].getGfx(), -1, false, true, false, false, false);
				}
			}
		}
		swiWaitForVBlank();
		oamUpdate(&oamMain);
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

	return 0;
}

//---------------------------------------------------------------------
// initualizes all the starting crap for this game
//---------------------------------------------------------------------
void initualize()
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

	oamInit(&oamMain, SpriteMapping_1D_128, false);
}

//---------------------------------------------------------------------
// gets key events and processes them
//---------------------------------------------------------------------
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
