#include "gamecore.h"


gamecore::gamecore()
{
	currentState = SPLASHSCREEN;
	CUNT = true;
	scores.nextEmpty = 0;
	//empty struct
	fatInitDefault(); 
	//opens and reads file into struct
	 if(!fopen("fat:/LNoE.sav", "rb"))
	{
		for(int i=0; i<10; i++)
		{
			scores.spot[i] = 0;
	
		}
	}
	 else if(fopen("fat:/LNoE.sav", "rb"))
	{
		FILE* save_file = fopen("fat:/LNoE.sav", "rb");
		fread(&scores, 1, sizeof(scores), save_file);
		fclose(save_file);	
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
			case SCORESCREEN:
				if(!scoreScreen.getStatus())
				{
					scoreScreen.initiate();
				}
				currentState = scoreScreen.events();
				scoreScreen.processMain();
				scoreScreen.renderMain();
				scoreScreen.processSub();
				scoreScreen.renderSub();
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
	int tempInput; //when moving lower scores down
	//fatInitDefault(); 
	//opens and reads file into struct
	 if(fopen("fat:/LNoE.sav", "rb"))
	{
		FILE* save_file = fopen("fat:/LNoE.sav", "rb");
		fread(&scores, 1, sizeof(scores), save_file);
		fclose(save_file);	
	}
	 //puts input into its spot in struct
	 for(int i=0;i < 10;i++)
	 {
		 //if score is higher than a score in the middle of struct
		 if(input >= scores.spot[i])
		 {
			 //moves scores down
			 for(int j=i; j<10;j++)
			 {
				 tempInput = scores.spot[j];
				 scores.spot[j] = input;
				 input = tempInput;
			 }
			 scores.nextEmpty++;
			 i=10;
		 }
		 /*
		 //if score is lowest
		 else if(i==9 && input>scores.spot[9])
		 {
			 scores.spot[9] = input;
			 scores.nextEmpty++;
			 i=10;
		 }
		 */
	 }

	 //saves to file
	FILE* save_file = fopen("fat:/LNoE.sav", "wb");
	fwrite(&scores, 1, sizeof(scores), save_file);
	fclose(save_file);
}