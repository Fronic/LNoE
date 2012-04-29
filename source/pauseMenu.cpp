#include "pauseMenu.h"

pauseMenu::pauseMenu()
{
	initiated = false;
}

void pauseMenu::initiate()
{
	lcdMainOnTop(); //switches screens; main is on bottom, sub on top
	bg1 = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	dmaCopy(pauseBitmap, bgGetGfxPtr(bg1), pauseBitmapLen);
	dmaCopy(pausePal, BG_PALETTE_SUB, pausePalLen);
	bgShow(bg1);
	initiated = true;
}

int pauseMenu::events()
{
	touchRead(&touch);
	scanKeys();
	int keys = keysHeld();
	int pressed = keysDown(); 
	if(!(pressed & KEY_TOUCH)) return PAUSEMENU;
	if(touch.px>64 && touch.px < 192 && touch.py>60 && touch.py <85)
	{
		bgHide(bg1);
lcdMainOnBottom(); //switches screens; main is on bottom, sub on top
initiated = false;
vramSetBankC(VRAM_C_SUB_BG_0x06200000 );
		return MAINGAME;
	}
	if(touch.px>64 && touch.px < 192 && touch.py>100 && touch.py <124)
	{
	bgHide(bg1);
	oamClear(&oamMain,0,0);
	initiated = false;

		return SCORESCREEN;
	}
	return PAUSEMENU;
}

void pauseMenu::processMain()
{

}
void pauseMenu::processSub()
{
	
}
//renders
void pauseMenu::renderMain()
{
	oamUpdate(&oamMain);
}
void pauseMenu::renderSub()
{
	oamUpdate(&oamSub);
}
bool pauseMenu::getStatus()
{
	return initiated;
}