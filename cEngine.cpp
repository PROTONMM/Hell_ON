//####################################################################################################
//HELL-ON!
//PROTON 2017
//Mariusz Księżak
//####################################################################################################
#include "cEngine.h"
#include <algorithm>
#include <string>
#include <sstream>

static float pi = 3.14159265358979323846;

//####################################################################################################
//vector delete
//####################################################################################################
bool shootOut(shoot sh){
	return (sh.s_x < 0) || (sh.s_x > SCREEN_WIDTH) || (sh.s_y < 0) || (sh.s_y > SCREEN_HEIGHT);
}

bool explosionOut(explosion ex){
	return ex.frame >= ex.frames;
}

bool objectOut(object ob){
	return ob.energy <= 0;
}

//####################################################################################################
//constructor
//####################################################################################################
cEngine::cEngine(){
	SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	this->window = SDL_CreateWindow(
			"Hell-ON!",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

//####################################################################################################
//destructor
//####################################################################################################
cEngine::~cEngine(){
	for(unsigned int i=0; i<this->sounds.size();i++){
		Mix_FreeChunk(this->sounds[i]);
	}
	if(this->music != NULL){
		Mix_FreeMusic(this->music);
	}

	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	Mix_CloseAudio();
	SDL_Quit();
}

//####################################################################################################
//WINDOW
//####################################################################################################
void cEngine::windowClear(){
	SDL_RenderClear( this->renderer );
}

void cEngine::windowBackground(){
	int w,h;
	SDL_Rect background_texture_rect;
	background_texture_rect.w = BACKGROUND_TEXTURE_W;
	background_texture_rect.h = BACKGROUND_TEXTURE_H;

	SDL_GetWindowSize( this->window, &w, &h);

	for(int x = 0; x < w; x += BACKGROUND_TEXTURE_W){
		for(int y = 0; y < h; y += BACKGROUND_TEXTURE_H){
			background_texture_rect.x = x;
			background_texture_rect.y = y;
			SDL_RenderCopy(this->renderer, this->background_texture, NULL,
					&background_texture_rect);
		}
	}
}

void cEngine::windowPresent(){
	SDL_RenderPresent( this->renderer );
}

SDL_Window* cEngine::getWindow(){
	return this->window;
}

SDL_Renderer* cEngine::getRenderer(){
	return this->renderer;
}

void cEngine::windowFullscreen(bool full){
	if(full){
		SDL_SetWindowFullscreen( this->window, SDL_WINDOW_FULLSCREEN);
	}else{
		SDL_SetWindowFullscreen( this->window, 0);
	}
}

//####################################################################################################
//MUSIC
//####################################################################################################
bool cEngine::loadSound(const char* file){
	Mix_Chunk *sound = Mix_LoadWAV(file);
	if(sound == NULL) return false;
	this->sounds[this->sounds.size()] = sound;
	return true;
}

bool cEngine::loadMusic(const char* file){
	this->music = Mix_LoadMUS(file);
	if(this->music){
		Mix_PlayMusic(music, 99);
		return true;
	}
	return false;
}

void cEngine::playSound(int id){
	if((unsigned int)id<this->sounds.size()){
		Mix_PlayChannel( -1, this->sounds[id], 0);
	}
}
//####################################################################################################
//TEXTURE
//####################################################################################################
//bool cEngine::loadBackgroundTexture(const char* file){
//	if(this->background_texture != NULL) SDL_DestroyTexture(this->background_texture);
//	this->background_texture = IMG_LoadTexture(this->renderer, file);
//	if(this->background_texture == NULL)return false;
//	return true;
//}

void cEngine::setBackgroundTexture(int id){
	this->background_texture = this->textures[id]->texture;
}

bool cEngine::loadTexture( const char* file, int r, int c, int begin ){
	SDL_Surface* s = IMG_Load( file );
	if( s == NULL )return false;
	SDL_SetColorKey( s, SDL_TRUE, SDL_MapRGB( s->format, 0, 0, 0));
	//SDL_SetColorKey( s, SDL_TRUE, SDL_MapRGB( s->format, 0, 1, 20));
	sTexture *texture = new sTexture();
	texture->texture = SDL_CreateTextureFromSurface( this->renderer, s);
	texture->width = s->w;
	texture->height = s->h;
	texture->columns = c;
	texture->rows = r;
	texture->begin = begin;
	SDL_FreeSurface( s );
	this->textures[this->textures.size()] = texture;
	return true;
}

void cEngine::render(int t, int x, int y, int id){
	double angle = 0.0;
	this->renderAngle(t,x,y,angle, id);
}

void cEngine::renderAngle(int t, int x, int y, double angle, int id){
	if((this->textures[id]->rows * this->textures[id]->columns) < t)return; //test

	//texture quad
	int texture_width = this->textures[id]->width/this->textures[id]->columns;
	int texture_height = this->textures[id]->height/this->textures[id]->rows;
	int texture_x = (t%this->textures[id]->columns) * texture_width;
	int texture_y = (t/this->textures[id]->columns) * texture_height;
	SDL_Rect textureQuad = { texture_x, texture_y, texture_width,
			texture_height };

	//render quad
	SDL_Rect renderQuad={x-(texture_width/2), y-(texture_height/2), texture_width, texture_height};

	//double angle = 0.0;
	SDL_Point center = {texture_width/2,texture_height/2};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(this->renderer, this->textures[id]->texture, &textureQuad,
			&renderQuad, angle, &center, flip );

}

void cEngine::text(const char* txt, int x, int y, int id){
	int next = 0;
	int t_offset;
	for(int i=0; txt[i] != '\0'; i++){

		//Specjalnie dla pliku TT_Fontset_01.png

		//duże litery
		if(txt[i]>='A' && txt[i]<='Z')t_offset = txt[i] - 'A';

		//małe litery
		else if(txt[i]>='a' && txt[i]<='z')t_offset = txt[i] - 'a';

		//cyfry litery
		else if(txt[i]>='1' && txt[i]<='9')t_offset = txt[i] - '1' + 26;

		else if(txt[i]=='0')t_offset = 35;	//zero
		else if(txt[i]==' ')t_offset = 255; //space
		else if(txt[i]=='-')t_offset = 36; //minus
		else if(txt[i]=='=')t_offset = 37; //równa
		else if(txt[i]=='\\')t_offset = 38; //itd...
		else if(txt[i]=='[')t_offset = 39;
		else if(txt[i]==']')t_offset = 40;
		else if(txt[i]==';')t_offset = 41;
		else if(txt[i]=='\'')t_offset = 42;
		else if(txt[i]==',')t_offset = 43;
		else if(txt[i]=='.')t_offset = 44;
		else if(txt[i]=='/')t_offset = 45;
		else if(txt[i]=='!')t_offset = 46;
		else if(txt[i]=='@')t_offset = 47;
		else if(txt[i]=='#')t_offset = 48;
		else if(txt[i]=='$')t_offset = 49;
		else if(txt[i]=='%')t_offset = 50;
		else if(txt[i]=='^')t_offset = 51;
		else if(txt[i]=='&')t_offset = 52;
		else if(txt[i]=='*')t_offset = 53;
		else if(txt[i]=='(')t_offset = 54;
		else if(txt[i]==')')t_offset = 55;
		else if(txt[i]=='_')t_offset = 56;
		else if(txt[i]=='+')t_offset = 57;
		else if(txt[i]=='|')t_offset = 58;
		else if(txt[i]=='{')t_offset = 59;
		else if(txt[i]=='}')t_offset = 60;
		else if(txt[i]==':')t_offset = 61;
		else if(txt[i]=='"')t_offset = 62;
		else if(txt[i]=='<')t_offset = 63;

		if((t_offset <= (this->textures[id]->rows * this->textures[id]->columns)) && (t_offset >= 0)){
			this->render(t_offset, x+next, y, id);
		}
		next += (this->textures[id]->width/this->textures[id]->columns)-8;
	}

}

//####################################################################################################
//OBJECTS
//####################################################################################################
void cEngine::getEvents(){
	while(SDL_PollEvent( &this->e ) !=0){
		switch( e.type ){
		case SDL_QUIT:
			run = false;
			levelRun = false;
			break;

		default:
			break;
		}
	}

//		//zdarzenia okna
//		if(e.type == SDL_WINDOWEVENT){
//			switch(e.window.event){
//			case SDL_WINDOWEVENT_MAXIMIZED:
//				G->windowFullscreen(true);
//				break;
//			default:
//				break;
//			}
//		}

	//e.window.event

	//odczyt klawiatury
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_ESCAPE]) {
		maximize = !maximize;
		this->windowFullscreen(maximize);
	}
	if(keys[SDL_SCANCODE_LEFT]) angle -= 2;
	if(keys[SDL_SCANCODE_RIGHT]) angle += 2;

	if(keys[SDL_SCANCODE_SPACE]){
		if(shootEnable && !shipDestroyed){
			shoot s;
			s.angle = angle;
			s.s_x = st_x;
			s.s_y = st_y;
			s.v_x = v_x;
			s.v_y = v_y;
			shoots.push_back(s);
			playSound(0);
			shootEnable = false;
		}
		if(shipDestroyed && gameOverCounter > 200){
			levelRun = false;
		}
	}else{
		shootEnable = true;
	}

	if(keys[SDL_SCANCODE_UP]) {
		if(st<2)st++;
		//obliczenia fizyki
		v_x += sin(angle*pi/180)/15;
		v_y -= cos(angle*pi/180)/15;

		//std::cout<<"dx="<<sin(angle*pi/180)<<" dy="<<cos(angle*pi/180)<<std::endl;

	}else{
		st = 0;
	}

}


void cEngine::addObject(object o){
	this->objects.push_back(o);
}


void cEngine::mathPhysic(){
	//liczniki
	if(shipDestroyed) gameOverCounter++;
	if(objects.size() == 0) nextLevelCounter++;
	if(nextLevelCounter > 100){
		nextLevelCounter = 0;
		levelRun = 0;
		shoots.clear();
	}

	//obliczenie pozcji statku
	st_x += v_x;
	st_y += v_y;

	if(st_x>SCREEN_WIDTH)st_x -= SCREEN_WIDTH;
	if(st_x<0)st_x += SCREEN_WIDTH;
	if(st_y>SCREEN_HEIGHT)st_y -= SCREEN_HEIGHT;
	if(st_y<0)st_y += SCREEN_HEIGHT;

	//usuniecie strzałów znajdujących się poza ekranem
	shoots.erase(std::remove_if(shoots.begin(), shoots.end(), shootOut), shoots.end());

	//usunięcie pustych wybuchów
	explosions.erase(std::remove_if(explosions.begin(), explosions.end(), explosionOut), explosions.end());

	//usunęcie zniszczonych obiektów
	objects.erase(std::remove_if(objects.begin(), objects.end(), objectOut), objects.end());

	//ruch pocisków
	for (std::vector<shoot>::iterator sh = shoots.begin(); sh != shoots.end(); ++sh){
		sh->s_x += sin(sh->angle*pi/180) + sh->v_x;
		sh->s_y -= cos(sh->angle*pi/180) - sh->v_y;
	}

	//ruch obiektów
	for (std::vector<object>::iterator ob = objects.begin(); ob != objects.end(); ++ob){

		//fizyka obiektów.
		ob->angle += ob->v_angle;
		ob->s_x += ob->v_x;
		ob->s_y += ob->v_y;

		//przejście na drugą stronę ekranu
		if(ob->s_x > SCREEN_WIDTH)ob->s_x -= SCREEN_WIDTH;
		if(ob->s_x<0)ob->s_x += SCREEN_WIDTH;
		if(ob->s_y>SCREEN_HEIGHT)ob->s_y -= SCREEN_HEIGHT;
		if(ob->s_y<0)ob->s_y += SCREEN_HEIGHT;
	}

	//fizyka eksplozji
	for (std::vector<explosion>::iterator ex = explosions.begin(); ex != explosions.end(); ++ex){
		if(ex->frame == 8){
			//fala uderzeniowa
			//statek
			float dx = st_x - ex->s_x;
			float dy = st_y - ex->s_y;
			float dd = sqrt((dx*dx) + (dy*dy));
			if(dx != 0 && dy != 0) angle += (dx+dy)/(dd*10.0);
			if(dx != 0) v_x += ((dx/dd)/dd)*ex->frames/4;
			if(dy != 0) v_y += ((dy/dd)/dd)*ex->frames/4;
			//obiekty
			for (std::vector<object>::iterator ob = objects.begin(); ob != objects.end(); ++ob){
				float dx = ob->s_x - ex->s_x;
				float dy = ob->s_y - ex->s_y;
				float dd = sqrt((dx*dx) + (dy*dy));
				if(dx != 0 && dy != 0) ob->v_angle += (dx+dy)/(dd*10.0);
				if(dx != 0) ob->v_x += ((dx/dd)/dd)*ex->frames/4;
				if(dy != 0) ob->v_y += ((dy/dd)/dd)*ex->frames/4;
			}
		}
	}
}

void cEngine::renderFrame(){

	//czysczenie ekranu i ustawnienie tła.
	windowClear();
	windowBackground();

	//tekst
	text("HELL-ON! POZDROWIENIA OD MICROGEEK.EU", scrollCounter,25, 44);
	//text1->text("1410 !@#$%^&*()_+<< MICROGEEK.EU", 10,162);

	//renderowanie strzałów.
	for (std::vector<shoot>::iterator sh = shoots.begin(); sh != shoots.end(); ++sh){
		renderAngle(0, sh->s_x, sh->s_y, sh->angle, 1);
	}

	//renderowanie obiektów
	for (std::vector<object>::iterator ob = objects.begin(); ob != objects.end(); ++ob){
		//renderowanie
		renderAngle(ob->frame, ob->s_x, ob->s_y, ob->angle, ob->texture);
		if(animationCounter == 0)ob->frame++;
		if(ob->frame>=(textures[ob->texture]->columns * textures[ob->texture]->rows)){
			ob->frame = textures[ob->texture]->begin;
		}
	}

	//renderowanie statku
	if(!shipDestroyed) renderAngle(st, st_x, st_y, angle, 0);

	//renderowanie eksplozji
	for (std::vector<explosion>::iterator ex = explosions.begin(); ex != explosions.end(); ++ex){
		render(ex->frame, ex->s_x, ex->s_y, ex->id);
		if(animationCounter == 0)ex->frame++;

	}

	renderPoints(); //wyświetlanie punktów.

	//wyświetlenie GAME OVER
	if(gameOverCounter > 200) text("GAME OVER", 100, 300, 44);

	windowPresent();

	// w pętli.
	animationCounter++;
	if(animationCounter==5)	animationCounter=0;
	scrollCounter--;
	if(scrollCounter < -1200)scrollCounter = SCREEN_WIDTH;


}

void cEngine::collisionDetection(){

	//wykrywanie kolizji z pociskiem
	for (std::vector<shoot>::iterator sh = shoots.begin(); sh != shoots.end(); ++sh){
		for (std::vector<object>::iterator ob = objects.begin(); ob != objects.end(); ++ob){
			float dx = ob->s_x - sh->s_x;
			float dy = ob->s_y - sh->s_y;
			float dd = sqrt((dx*dx) + (dy*dy));
			if(dd<30){
				explosion ex;
				ex.frame = 0;
				ex.id = rocketExplosionTexture;
				ex.frames = textures[rocketExplosionTexture]->columns*textures[rocketExplosionTexture]->rows;
				ex.s_x = sh->s_x;
				ex.s_y = sh->s_y;
				explosions.push_back(ex);
				playSound(1);
				ob->energy = ob->energy - 25;
				points += 25;
				if(ob->energy <= 0){
					ex.frame = 0;
					ex.id = objectExplosionTexture;
					ex.frames = textures[objectExplosionTexture]->columns*textures[objectExplosionTexture]->rows;
					ex.s_x = ob->s_x;
					ex.s_y = ob->s_y;
					points += ob->points;
					playSound(2);
					explosions.push_back(ex);
				}

				//usunięcie strzału z ekranu;
				sh->s_x = -50000;
			}
		}
	}

	//wykrywanie kolizji obiektu ze statkiem.
	if(!shipDestroyed){
		for (std::vector<object>::iterator ob = objects.begin(); ob != objects.end(); ++ob){
			float dx = ob->s_x - st_x;
			float dy = ob->s_y - st_y;
			float dd = sqrt((dx*dx) + (dy*dy));
			if(dd<30){
				explosion ex;
				ex.frame = 0;
				ex.id = shipExplosionTexture;
				ex.frames = textures[shipExplosionTexture]->columns*textures[shipExplosionTexture]->rows;
				ex.s_x = st_x;
				ex.s_y = st_y;
				explosions.push_back(ex);
				playSound(1);
				shipDestroyed = true;

			}
		}
	}
	//wykrywanie kolizji pomiÄ™dzy obiektami
//		for (std::vector<object>::iterator ob1 = objects.begin(); ob1 != objects.end(); ++ob1){
//			for (std::vector<object>::iterator ob2 = ob1; ob2 != objects.end(); ++ob2){
//				if(ob1 != ob2){
//					float dx = ob1->s_x - ob2->s_x;
//					float dy = ob1->s_y - ob2->s_y;
//					float dd = sqrt((dx*dx) + (dy*dy));
//					if(dd<32){
//						std::cout<<"COLISION: "<<dd<<std::endl;
//						float dvx = ob1->v_x - ob2->v_x;
//						ob1->v_x += dvx/2.0;
//						ob2->v_x -= dvx/2.0;
//						float dvy = ob1->v_y - ob2->v_y;
//						ob1->v_y += dvy/2.0;
//						ob1->v_y -= dvy/2.0;
//					}
//				}
//			}
//		}

}

bool cEngine::runGame(){
	return run;
}

bool cEngine::runLevel(){
	return levelRun;
}

void cEngine::renderPoints(){
	std::stringstream s;
	s << points;
	text(s.str().c_str(), 50, 550, 44);
}

bool cEngine::resetShip(){
	//statek
	bool ship = shipDestroyed;
	if(shipDestroyed){
		points = 0;
		shoots.clear();
		objects.clear();
	}
	angle = 0.0;
	st = 0;
	st_x = SCREEN_WIDTH/2;
	st_y = SCREEN_HEIGHT/2;
	v_x = 0.0;
	v_y = 0.0;
	shootEnable = true;
	run = true;
	shipDestroyed = false;
	nextLevelCounter = 0;
	gameOverCounter = 0;
	levelRun = true;
	return ship;
}
