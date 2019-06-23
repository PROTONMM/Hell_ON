//####################################################################################################
//HELL-ON!
//PROTON 2017
//Mariusz Księżak
//####################################################################################################
#include "cGame.h"

struct textureFile{
	std::string filename;
	int r,c,begin;
};

cGame::cGame(cEngine* e){
	this->engine = e;
}

bool cGame::loadSounds(){
	if(!engine->loadSound("sound/Arrow1.wav"))return false;
	if(!engine->loadSound("sound/Explosion1.wav"))return false;
	if(!engine->loadSound("sound/Explosion4.wav"))return false;
	return true;
}

bool cGame::loadMusic(){
	if(!engine->loadMusic("sound/Electropop-eighties-music.mp3"))
		return false;
	return true;
}

bool cGame::loadTexures(){
	textureFile texFiles[]=
		{{"images/AAA_Player_ship.png", 1,3,0},			//0
		{"images/AAA_Player_bullets.png", 1,1,0},		//1
		{"images/AAA_Explosion_missiles.png", 1,9,0},	//2
		{"images/AAA_Explosion.png", 1,9,0},			//3
		{"images/Krystal_OB_01.png", 1,25,10},			//4
		{"images/Krystal_OB_02.png", 1,25,10},			//5
		{"images/Krystal_OB_02a.png", 1,25,10},			//6
		{"images/Krystal_OB_02b.png", 1,25,10},			//7
		{"images/Krystal_OB_03a.png", 1,25,10},			//8
		{"images/Krystal_OB_03b.png", 1,25,10},			//9
		{"images/Krystal_OB_04a.png", 1,25,10},			//10
		{"images/Krystal_OB_04b.png", 1,25,10},			//11
		{"images/Krystal_OB_05a.png", 1,25,10},			//12
		{"images/Krystal_OB_05b.png", 1,25,10},			//13
		{"images/Krystal_OB_06a.png", 1,25,10},			//14
		{"images/Krystal_OB_06b.png", 1,25,10},			//15
		{"images/Krystal_OB_07a.png", 1,25,10},			//16
		{"images/Krystal_OB_07b.png", 1,25,10},			//17
		{"images/Krystal_OB_08a.png", 1,25,10},			//18
		{"images/Krystal_OB_08b.png", 1,25,10},			//19
		{"images/Krystal_OB_09a.png", 1,25,10},			//20
		{"images/Krystal_OB_09b.png", 1,25,10},			//21
		{"images/Krystal_OB_10a.png", 1,25,10},			//22
		{"images/Krystal_OB_10b.png", 1,25,10},			//23
		{"images/Krystal_OB_11a.png", 1,25,10},			//24
		{"images/Krystal_OB_11b.png", 1,25,10},			//25
		{"images/Krystal_OB_12a.png", 1,25,10},			//26
		{"images/Krystal_OB_12b.png", 1,25,10},			//27
		{"images/Krystal_OB_13a.png", 1,25,10},			//28
		{"images/Krystal_OB_13b.png", 1,25,10},			//29
		{"images/Krystal_OB_14a.png", 1,25,10},			//30
		{"images/Krystal_OB_14b.png", 1,25,10},			//31
		{"images/Krystal_OB_15a.png", 1,25,10},			//32
		{"images/Krystal_OB_15b.png", 1,25,10},			//33
		{"images/Krystal_OB_16a.png", 1,25,10},			//34
		{"images/Krystal_OB_16b.png", 1,25,10},			//35
		{"images/Krystal_OB_17a.png", 1,25,10},			//36
		{"images/Krystal_OB_17b.png", 1,25,10},			//37
		{"images/Krystal_OB_18a.png", 1,25,10},			//38
		{"images/Krystal_OB_18b.png", 1,25,10},			//39
		{"images/Krystal_OB_19a.png", 1,25,10},			//40
		{"images/Krystal_OB_19b.png", 1,25,10},			//41
		{"images/Krystal_OB_20a.png", 1,25,10},			//42
		{"images/Krystal_OB_20b.png", 1,25,10},			//43
		{"images/TT_Fontset_01.png", 1, 66,0},			//44
		{"images/Kystal_BackTile001.png", 1, 1, 0},		//45
		{"images/Kystal_BackTile002.png", 1, 1, 0},		//46
		{"images/Kystal_BackTile003.png", 1, 1, 0},		//47
		{"images/Kystal_BackTile004.png", 1, 1, 0},		//48
		{"images/Kystal_BackTile005.png", 1, 1, 0},		//49
		{"images/Kystal_BackTile006.png", 1, 1, 0},		//50
		{"images/Kystal_BackTile007.png", 1, 1, 0},		//51
		{"images/Kystal_BackTile008.png", 1, 1, 0},		//52
		{"images/Kystal_BackTile009.png", 1, 1, 0},		//53
		{"images/Kystal_BackTile010.png", 1, 1, 0},		//54
		{"images/Kystal_BackTile011.png", 1, 1, 0},		//55
		{"images/Kystal_BackTile012.png", 1, 1, 0},		//56
		{"images/Kystal_BackTile013.png", 1, 1, 0},		//57
		{"images/Kystal_BackTile014.png", 1, 1, 0},		//58
		{"images/Kystal_BackTile015.png", 1, 1, 0},		//59
		{"images/Kystal_BackTile016.png", 1, 1, 0},		//60
		{"images/Kystal_BackTile017.png", 1, 1, 0},		//61
		{"images/Kystal_BackTile018.png", 1, 1, 0},		//62
		{"images/Kystal_BackTile019.png", 1, 1, 0},		//63
		{"images/Kystal_BackTile020.png", 1, 1, 0},		//64
		{"images/Kystal_BackTile021.png", 1, 1, 0},		//65
		{"images/Kystal_BackTile022.png", 1, 1, 0},		//66
		{"images/Kystal_BackTile023.png", 1, 1, 0},		//67
		{"images/Kystal_BackTile024.png", 1, 1, 0},		//68
		{"images/Kystal_BackTile025.png", 1, 1, 0},		//69
		{"images/TT_Fontset_01.png", 1, 66, 0},			//70
		{"images/Explosion.png", 5, 5, 0},				//71
		{"images/spritesheet.png", 9, 9, 0}				//72
		};				//71


	for(int i = 0; i<73; i++){
		if(!engine->loadTexture(texFiles[i].filename.c_str(), texFiles[i].r, texFiles[i].c, texFiles[i].begin))
			return false;

		std::cout<<texFiles[i].filename.c_str()<<std::endl;
	}
	return true;
}

void cGame::loadLevel(){
	//frame - wyświetlana ramka
	//texture - numer tekstury
	//energy - energia
	//points - liczba punktów za zniszczenie
	//v_x -	prędkośc X
	//v_y - prędkośc Y
	//angle - kąt
	//v_angle - prędkośc obrotu
	//s_x - pozycja X
	//s_y - pozycja Y

	//frame, texture, points, v_x, v_y, angle, v_angle, s_x, s_y
	//    0,       5,    100, 0.0, 0.0,   0.0,     0.0, 100, 100

	if(level>6)level=6; //zabezpieczenie

	object l1[24] = {
			{0, 5, 100, 100, 0.0, 0.0, 0.0, 0.0, 100, 100},
			{0, 5, 100, 100, 0.0, 0.0, 0.0, 0.0, 150, 100},
			{0, 5, 100, 100, 0.0, 0.0, 0.0, 0.0, 150, 150},
			{0, 5, 100, 100, 0.0, 0.0, 0.0, 0.0, 100, 150},
			{0, 9, 100, 100, 0.0, 0.0, 0.0, 0.0, 200, 100},
			{0, 9, 100, 100, 0.0, 0.0, 0.0, 0.0, 250, 100},
			{0, 9, 100, 100, 0.0, 0.0, 0.0, 0.0, 250, 150},
			{0, 9, 100, 100, 0.0, 0.0, 0.0, 0.0, 200, 150},
			{0,11, 100, 100, 0.0, 0.0, 0.0, 0.0, 300, 100},
			{0,11, 100, 100, 0.0, 0.0, 0.0, 0.0, 350, 100},
			{0,11, 100, 100, 0.0, 0.0, 0.0, 0.0, 350, 150},
			{0,11, 100, 100, 0.0, 0.0, 0.0, 0.0, 300, 150},
			{0,13, 100, 100, 0.0, 0.0, 0.0, 0.0, 400, 100},
			{0,13, 100, 100, 0.0, 0.0, 0.0, 0.0, 450, 100},
			{0,13, 100, 100, 0.0, 0.0, 0.0, 0.0, 450, 150},
			{0,13, 100, 100, 0.0, 0.0, 0.0, 0.0, 400, 150},
			{0,15, 100, 100, 0.0, 0.0, 0.0, 0.0, 500, 100},
			{0,15, 100, 100, 0.0, 0.0, 0.0, 0.0, 550, 100},
			{0,15, 100, 100, 0.0, 0.0, 0.0, 0.0, 550, 150},
			{0,15, 100, 100, 0.0, 0.0, 0.0, 0.0, 500, 150},
			{0,17, 100, 100, 0.0, 0.0, 0.0, 0.0, 600, 100},
			{0,17, 100, 100, 0.0, 0.0, 0.0, 0.0, 650, 100},
			{0,17, 100, 100, 0.0, 0.0, 0.0, 0.0, 650, 150},
			{0,17, 100, 100, 0.0, 0.0, 0.0, 0.0, 600, 150}
	};

	if(engine->resetShip()) level = 1;
	engine->setBackgroundTexture(44 + level);
	engine->windowBackground();
	engine->windowPresent();
	SDL_Delay(1000);

	for(int i=0;i<level*4;i++){
		engine->addObject(l1[i]);
	}
}

void cGame::playGame(){
	while(engine->runLevel()){
		engine->renderFrame();
		engine->collisionDetection();
		engine->mathPhysic();
		engine->getEvents();
		SDL_Delay(10);
	}
	level++;
}
