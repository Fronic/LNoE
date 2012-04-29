#include "scores.h"


//constructor
	ScoreScreen::ScoreScreen()
	{
			initiated = false;
	}
	//initiates other stuff
	void ScoreScreen::initiate()
	{

	pcBtm = *consoleInit( 0, 0, BgType_Text4bpp, BgSize_T_256x256, 0, 1, false,true );
			consoleSetWindow(&pcBtm, 6,2.5,20,22);
		lcdMainOnTop(); //switches screens; main is on bottom, sub on top
	bg1 = bgInitSub(2, BgType_Bmp8, BgSize_B8_256x256, 3,0);
	dmaCopy(scorescreenBitmap, bgGetGfxPtr(bg1), scorescreenBitmapLen);
	dmaCopy(scorescreenPal, BG_PALETTE_SUB, scorescreenPalLen);
	bgShow(bg1);

	consoleSelect( &pcBtm );
 if(fopen("LNoE.sav", "rb"))
	{
		FILE* save_file = fopen("fat:\LNoE.sav", "rb");
		fread(&scores, 1, sizeof(scores), save_file);
		fclose(save_file);	
	}

	std::cout << "\t ---Scores---" << std::endl;
	for(int i=0;i<10;i++)
	{
		std::cout <<"\t" << i+1 << "] \t" << scores.spot[i] << std::endl;
	}

	//std::cout<<"Bottom ScreenAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABottom ScreenAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABottom ScreenAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCDDDDDDDDDDDDDDDDDDDDEEEEEEEEEEEEEEEEEEEEFFFFFFFF" << std::endl;
	initiated = true;

	}
	int ScoreScreen::events()
	{
		touchRead(&touch);
	scanKeys();
	int keys = keysHeld();
	int pressed = keysDown(); 
	if(!(pressed & KEY_TOUCH)) return SCORESCREEN;
	if(touch.px>64 && touch.px < 192 && touch.py>60 && touch.py <85)
	{
		bgHide(bg1);
lcdMainOnBottom(); //switches screens; main is on bottom, sub on top
initiated = false;
vramSetBankC(VRAM_C_SUB_BG_0x06200000 );
		return MAINMENU;
	}
	if(touch.px>64 && touch.px < 192 && touch.py>100 && touch.py <124)
	{
	bgHide(bg1);
	oamClear(&oamMain,0,0);
	initiated = false;
		return MAINMENU;
	}
	return SCORESCREEN;
	}
	void ScoreScreen::processMain()
	{
		
	}
	void ScoreScreen::processSub()
	{
	}
	//renders
	void ScoreScreen::renderMain()
	{
		oamUpdate(&oamMain);
	}
	void ScoreScreen::renderSub()
	{
		oamUpdate(&oamSub);
	}

	bool ScoreScreen::getStatus()
	{
		return initiated;
	}
