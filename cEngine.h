//####################################################################################################
//HELL-ON!
//PROTON 2017
//Mariusz Księżak
//####################################################################################################
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <map>
#include <math.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int BACKGROUND_TEXTURE_W = 128;
const int BACKGROUND_TEXTURE_H = 128;

//####################################################
//STRUCTURES
//####################################################
struct sTexture{
	SDL_Texture* texture;
	int rows, columns, width, height, begin;
};

struct shoot{
	float v_x, v_y, angle, s_x, s_y;
};

struct object{
	int frame, texture, points, energy;
	float v_x, v_y, angle, v_angle, s_x, s_y;
};

struct explosion{
	int frame, id, frames;
	float s_x, s_y;
};

//####################################################
//CLASS
//####################################################
class cEngine{
public:
	cEngine();
	~cEngine();

	//window
	void windowClear();							//czyszcenie okna
	void windowBackground();					//generuje tło
	void windowPresent();						//odświerza okno
	SDL_Window* getWindow();					//pobiera uchwyt okna
	SDL_Renderer* getRenderer();				//pobiera uchwyt renderera
	void windowFullscreen(bool full);
	void renderPoints();

	//sound
	bool loadSound(const char* file);
	bool loadMusic(const char* file);
	void playSound(int id);

	//texture
	void setBackgroundTexture(int id);//ustaw nową teksturę tła
	bool loadTexture( const char* file, int r, int c, int begin ); //ładuje teksturę
	void render(int t, int x, int y, int id);					//renderuje teksturę
	void renderAngle(int t, int x, int y, double angle, int id);//renderuje teksturę
	void text( const char* txt, int x, int y, int id);			//wypisuje tekst

	//objects
	void addObject(object o);

	//events
	void getEvents();

	//
	void mathPhysic();
	void renderFrame();
	void collisionDetection();
	bool runGame();
	bool runLevel();
	bool resetShip();



private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* background_texture = NULL;
	bool maximize = false;


	int scrollCounter = SCREEN_WIDTH;
	int rocketExplosionTexture = 2;
	int objectExplosionTexture = 71;
	int shipExplosionTexture = 72;

	int animationCounter = 0;
	int points = 0;
	int gameOverCounter = 0;
	int nextLevelCounter = 0;
	std::map<int, sTexture*> textures;
	std::map<int, Mix_Chunk*>sounds;
	Mix_Music* music = NULL;
	SDL_Event e;

	//wektor przechowujący poruszające się pociski
	std::vector <shoot>shoots;

	//wektor przechowujący obiekty na planszy
	std::vector<object> objects;

	//wektor przechowujący eksplozje
	std::vector<explosion> explosions;

	//statek
	float angle = 0.0;
	int st = 0;
	float st_x = SCREEN_WIDTH/2;
	float st_y = SCREEN_HEIGHT/2;
	float v_x = 0.0;
	float v_y = 0.0;
	bool shootEnable = true;
	bool run = true;
	bool levelRun = true;
	bool shipDestroyed = false;



};


