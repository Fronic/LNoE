#include "gamecore.h"

gamecore::gamecore()
{
	currentState = MAINGAME;
	CUNT = true;
}
void gamecore::run()
{
	while(CUNT)
	{
		switch(currentState)
		{
		case MAINMENU:
			break;
		case MAINGAME:
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