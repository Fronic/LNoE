#include "gamecore.h"

gamecore::gamecore()
{
	currentState = MAINMENU;
	CUNT = true;
}
void gamecore::run()
{
	while(CUNT)
	{
		switch(currentState)
		{
		case MAINMENU:
			if(!menu.getStatus())
			{
				menu.initiate();
			}
			currentState = menu.events();
				menu.processMain();
				menu.renderMain();
				menu.processSub();
				menu.renderSub();
				swiWaitForVBlank();
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
				swiWaitForVBlank();
				break;
		case PAUSEMENU:
			break;
			case EXIT:
				CUNT = false;
				break;
		}
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