#include "gamecore.h"


gamecore::gamecore()
{
	currentState = SPLASHSCREEN;
	CUNT = true;
	scores.nextEmpty = 0;
	for(int i=0; i<10; i++)
	{
		scores.spot[i] = 0;
	}
}
void gamecore::run()
{
	while(CUNT)
	{
			switch(currentState)
			{
			case MAINMENU:
				if(game.getStatus())
				{
					game.setStatus(false);
				}
				if(!menu.getStatus())
				{
					menu.initiate();
				}
				currentState = menu.events();
				menu.processMain();
				menu.renderMain();
				menu.processSub();
				menu.renderSub();
				break;
			case MAINGAME:
				if(!game.getStatus())
				{
					game.initiate();
				}
				currentState = game.events();
				game.processMain();
				game.renderMain();
				game.processSub();
				game.renderSub();
				if(!game.getStatus())
				{
					saveScore(game.getScore());
				}
				break;
			case PAUSEMENU:
				if(!pause.getStatus())
				{
					pause.initiate();
				}
				currentState = pause.events();
				pause.processMain();
				game.renderMain();
				pause.processSub();
				pause.renderSub();
				if(menu.getStatus())
				{
					game.setStatus(false);
					saveScore(game.getScore());
				}
				break;
			case SPLASHSCREEN:
				if(!splash.getStatus())
				{
					splash.initiate();
				}
				currentState = splash.events();
				splash.processMain();
				splash.renderMain();
				splash.processSub();
				splash.renderSub();
				break;
			case EXIT:
				CUNT = false;
				break;
			}
		
		swiWaitForVBlank();
	}
}

void gamecore::saveScore(int input)
{
	int tempInput;
	fatInitDefault();
	 if(fopen("LNoE/scores.sav", "rb"))
	{
		FILE* save_file = fopen("scores.txt", "rb");
		fread(&scores, 1, sizeof(scores), save_file);
		fclose(save_file);	
	}
	 for(int i=0;i < 10;i++)
	 {
		 if(input >= scores.spot[i] && scores.nextEmpty < 10)
		 {
			 for(int j=i; j<9 && scores.nextEmpty !=j;j++)
			 {
				 tempInput = scores.spot[j];
				 scores.spot[j] = input;
				 input = tempInput;
			 }
			 scores.nextEmpty++;
			 i=10;
		 }
		 else if(scores.nextEmpty==i)
		 {
			 scores.spot[scores.nextEmpty] = input;
		 }
	 }


	FILE* save_file = fopen("LNoE/scores.sav", "wb");
	fwrite(&scores, 1, sizeof(scores), save_file);
	fclose(save_file);
}