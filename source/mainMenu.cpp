#include "mainMenu.h"

mainMenu::mainMenu()
{
	initiated = false;

}
void mainMenu::initiate()
{
	lcdMainOnTop();

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D); 

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);	


	//sets up our backgrounds
	bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256,0,0);
	dmaCopy(mainscreenBitmap, bgGetGfxPtr(bg3), mainscreenBitmapLen);
	dmaCopy(mainscreenPal, BG_PALETTE, mainscreenPalLen);
	bg2 = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	dmaCopy(mainscreenBotBitmap, bgGetGfxPtr(bg2), mainscreenBotBitmapLen);
	dmaCopy(mainscreenBotPal, BG_PALETTE_SUB, mainscreenBotPalLen);
	initiated = true;
}

int mainMenu::events()
{
	touchRead(&touch);
	scanKeys();
	int keys = keysHeld();
	int pressed = keysDown(); 
	if(!(pressed & KEY_TOUCH)) return MAINMENU;
	if(touch.px < 64)
	{
		return MAINMENU;
	}

	else if(touch.px > 192)
	{
		return MAINMENU;
	}

	if(touch.py < 84)
	{
		return MAINMENU;
	}

	else if(touch.py > 109)
	{
		return MAINMENU;
	}

	bgHide(bg3);
	bgHide(bg2);
	vramDefault();
	initiated = false;
	return MAINGAME;
}

void mainMenu::processMain()
{
	
}
void mainMenu::processSub()
{
	
}
//renders
void mainMenu::renderMain()
{
	oamUpdate(&oamMain);
}
void mainMenu::renderSub()
{
	oamUpdate(&oamSub);
}
bool mainMenu::getStatus()
{
	return initiated;
}