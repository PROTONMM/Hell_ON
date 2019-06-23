//####################################################################################################
//HELL-ON!
//PROTON 2017
//Mariusz Księżak
//####################################################################################################
#include "cEngine.h"

class cGame{
public:
	cGame(cEngine* e);
	bool loadSounds();
	bool loadMusic();
	bool loadTexures();
	void loadLevel();
	void playGame();
	void intro();
	void gameOver();


private:
	cEngine* engine;
	int level = 1;

};

