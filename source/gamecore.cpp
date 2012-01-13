#include "gamecore.h"

gamecore::gamecore()
{
	currentState = SPLASHSCREEN;
	CUNT = true;
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
void gamecore::initiate()
{

}
void gamecore::process()
{

}
//renders
void gamecore::render()
{

}