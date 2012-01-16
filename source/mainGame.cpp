#include "mainGame.h"

mainGame::mainGame()
{
	count=0;
	hurtTimer = 600;
	initiated = false;
	score = 0;
	consoleDemoInit();

}

void mainGame::initiate()
{
	lcdMainOnBottom(); //switches screens; main is on bottom, sub on top

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D); 
	vramSetBankC(VRAM_C_SUB_BG_0x06200000 );
	//consoleDemoInit();
	//PrintConsole *main;
	//consoleInit(0, 1, BgType_Text4bpp, BgSize_T_256x256, 21, 0, false, true);

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);	
	vramSetBankE(VRAM_E_MAIN_SPRITE);
	vramSetBankG(VRAM_G_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_256, true);
	vramSetBankF(VRAM_F_LCD);

	dmaCopy(heroPal, VRAM_F_EXT_SPR_PALETTE[1], 512);
	dmaCopy(zombiePal, VRAM_F_EXT_SPR_PALETTE[0], 512);
	dmaCopy(lifePal, VRAM_F_EXT_SPR_PALETTE[2], 512);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

	//sets up our backgrounds
	bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_512x512,0,0);
	dmaCopy(grassBitmap, bgGetGfxPtr(bg3), grassBitmapLen);
	dmaCopy(grassPal, BG_PALETTE, grassPalLen);
	bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_512x512, 0,0);
	dmaCopy(grassBitmap, bgGetGfxPtr(bg2), grassBitmapLen);
	dmaCopy(grassPal, BG_PALETTE, grassPalLen);
//initualizes our "camera" it starts at (0,0) and takes the backgrounds' IDs	
	cam.init(0,0,bg3,bg2);

	//further initualizes what our hero needs to blit
	hero.init(112,80,&hero, (u8*)heroTiles);
	

	hero.animate();	//ensures our hero is blitted at least once
	std::vector<zombieType> zombies(1);

	initiated = true;
}

int mainGame::events()
{
	scanKeys();

	int keys = keysHeld();

	//following if statements handle movement and camera movement
	if(keys && count%2==0)
	{
		if(keys & KEY_L)
		{
			lcdSwap(); 
		}
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
	if(hero.getLife() == 0)
	{
		bgHide(bg3);
	bgHide(bg2);
	vramDefault();
	oamClear(&oamMain,0,0);
	initiated = false;
		return MAINMENU;
	}
		if(keys & KEY_START)
	{
		//lcdMainOnTop();
		return PAUSEMENU;
	}
	return MAINGAME;
}

void mainGame::processMain()
{
	count++;
	hurtTimer++;
	if(random< 100000)
	{
		random++;
		random++;
	}
	else if (random %2 ==0)
	{
		random--;
	}
	else
	{
		random--;
		random--;
	}
	if (count>600 && zombies.size()<12)
	{
		zombieType * another = new zombieType;
		zombies.push_back(*another);
		delete another;
		count = 0;
	}
	//checks key inputs; also a break out of the game
	int keys = keysHeld();

	//updates camera movements
	cam.update();

	if(count%6==0)
	{
		for(int i=0;i < zombies.size();i++)
		{
			for(int j=0;j < zombies.size();j++)
			{
				if(i != j)
				{
					if(zombies[i].getX() == zombies[j].getX()+16)
					{
						zombies[i].move(zombies[i].getX()+1,zombies[i].getY());
					}
					else if(zombies[i].getX()+16 == zombies[j].getX())
					{
						zombies[i].move(zombies[i].getX()-1,zombies[i].getY());
					}
					if(zombies[i].getY() == zombies[j].getY()+16)
					{
						zombies[i].move(zombies[i].getX(),zombies[i].getY()+1);
					}
					else if(zombies[i].getY()+16 == zombies[j].getY())
					{
						zombies[i].move(zombies[i].getX(),zombies[i].getY()-1);
					}
				}
			}
			zombies[i].move(hero.getX()+cam.getX() +8,hero.getY()+cam.getY()+9);
			zombies[i].render(i, cam);
		}
	}
		for(int i=0;i < zombies.size();i++)
	{
		if(detectCollision(i))
		{
				fight(i);
		}
	}
}
void mainGame::processSub()
{
	//std::couts some nice info
	std::cout << "\x1b[2J";
	std::cout << "scrollX: " << cam.getX() << std::endl;
	std::cout << "scrollY: " << cam.getY() << std::endl;
	std::cout << "hero.x: " << hero.getX() << std::endl;
	std::cout << "hero.y: " << hero.getY() << std::endl;
	std::cout << "Hero's actual Location: " << hero.getX()+cam.getX() +8 << " " << hero.getY()+cam.getY()+9 << std::endl;
	std::cout << "Key Pressed: " << keys <<std::endl;
	std::cout << "Zombies: " << zombies.size() << std::endl;
	std::cout << "zombie 1: " << zombies[0].getX() << " " << zombies[0].getY() << std::endl
		<< zombies[0].getX()-cam.getX() << " " << zombies[0].getY()-cam.getY() << std::endl;
	std::cout << "zombie 2: " << zombies[1].getX() << " " << zombies[1].getY() << std::endl
		<< zombies[1].getX()-cam.getX() << " " << zombies[1].getY()-cam.getY() << std::endl;
	std::cout << "hurtTimer: " << hurtTimer << std::endl;
	std::cout << "random: " << random << std::endl;
		std::cout << "score: " << score << std::endl;
	std::cout << "TIME " << zombies[0].getTime() << std::endl;
	std::cout << "TIME2 " << time(NULL) << std::endl;
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
void mainGame::fight(int i)
{
	srand(time(NULL));
	int win = rand()%3;


	if(hurtTimer >= 300)
	{
		if(win)
		{
			oamClear (&oamMain,i+9,zombies.size()+1) ;
			zombies.erase(zombies.begin()+i);
			score += 10;
		}
		else
		{
			hero.setLife(hero.getLife()-1);
			hurtTimer = 0;
			score -= 20 * 3;
		}
		}
}

bool mainGame::detectCollision(int i)
{
		if(hero.getY()+cam.getY()+9 > (zombies[i].getY() + 24))
		{
			return false;
		}
		else if(hero.getX()+cam.getX() +8 > (zombies[i].getX() + 20))
		{
			return false;
		}
		else if((hero.getY()+cam.getY()+9 + 24) < zombies[i].getY())
		{
			return false;
		}
		else if((hero.getX()+cam.getX() +8 + 20) < zombies[i].getX())
		{
			return false;
		}
		return true;

}
bool mainGame::getStatus()
{
	return initiated;
}
void mainGame::setStatus(bool set)
{
	initiated = set;
}
int mainGame::getScore()
{
	return score;
}