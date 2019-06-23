//####################################################################################################
//HELL-ON!
//PROTON 2017
//Mariusz Księżak
//####################################################################################################
#include "cGame.h"

//##############################################################

//##############################################################

int main(int argc, char **argv) {

	cEngine *engine = new cEngine();
	cGame *game = new cGame(engine); //dependency injection

	game->loadMusic();
	game->loadSounds();
	game->loadTexures();

	while(engine->runGame()){
		game->loadLevel();
		game->playGame();
	}

	delete(game);
	delete(engine);

	return 0;
}
