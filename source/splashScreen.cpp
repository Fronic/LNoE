#include "splashScreen.h"

splashScreen::splashScreen()
{
	timer = 0;
	initiated = false;

}
void splashScreen::initiate()
{
	lcdMainOnTop();

	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D); 

	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);	


	//sets up our backgrounds
	bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256,0,0);
	dmaCopy(splashBitmap, bgGetGfxPtr(bg3), splashBitmapLen);
	dmaCopy(splashPal, BG_PALETTE, splashPalLen);
	bg2 = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	dmaCopy(splashBitmap, bgGetGfxPtr(bg2), splashBitmapLen);
	dmaCopy(splashPal, BG_PALETTE_SUB, splashPalLen);
	initiated = true;
}

int splashScreen::events()
{
	touchRead(&touch);
	scanKeys();
	int pressed = keysDown(); 
	if((pressed & KEY_TOUCH)) return MAINMENU;
	int keys = keysHeld();
			if(keys & KEY_START)
		{
			timer = 301;
		}
	if(timer<300)
	{
		return SPLASHSCREEN;
	}
	bgHide(bg3);
	bgHide(bg2);
	vramDefault();
	initiated = false;
	return MAINMENU;
}

void splashScreen::processMain()
{
timer++;
}
void splashScreen::processSub()
{
	
}
//renders
void splashScreen::renderMain()
{
	oamUpdate(&oamMain);
}
void splashScreen::renderSub()
{
	oamUpdate(&oamSub);
}
bool splashScreen::getStatus()
{
	return initiated;
}