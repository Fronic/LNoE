//============================================================================
//
//	Author: Devlin Richberger
//	Description: Revisioning of the board game Last Night on Earth for DS
//	Version: 0.0.20
//	----
//	TODO
//	----
//	Short-Term: better collision between zombies and the player, player/zombie fights and health, game menu
//	Long-Term:saving 
//	Distant-Term: hero abilities, weapons, zombie abilities, multiplayer
//
//============================================================================

#include "gamecore.h" //has all includes, consts and other stuffs

//void initualize(); //initualizes VRAM and other stuffs
//void events(heroType &,camera &); //checks for key events and handles them


int main(void)
{
	gamecore core;
	core.run();
}