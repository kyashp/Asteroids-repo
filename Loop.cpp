#include "Loop.h"
#include<iostream>;
#include<random>
#include "SDL_ttf.h"
#include "sstream"

std::random_device rd;
std::uniform_int_distribution<int> y(0, 800);
std::uniform_int_distribution<int> x(0, 1000);
std::uniform_int_distribution<int> aX(0, 800);

SDL_Event evnt;

Loop::Loop()
{
}

void Loop::init(const char* title, int r, int g, int b)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL cannot be initialised! SDL ERROR:%s,", SDL_GetError());
		exit(0);
	}
	else {
		win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (win == nullptr) {
			printf("Windows cannot be initialised! SDL ERROR: %s", SDL_GetError());
			exit(0);
		}

		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		if (ren == nullptr) {
			printf("Renderer cannot be initialised! SDL ERROR: %s", SDL_GetError());
			exit(0);
		}

		if (TTF_Init() < 0) {
			printf("Fonts cannot be initialised! SDL_ttf ERROR: %s", TTF_GetError());
		}
		isRunning = true;
	}
	SDL_SetRenderDrawColor(ren, r, g, b, 255);
}

void Loop::handleEvents(SDL_Event& e)
{
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			SDL_Quit();
		}
		if (SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_r:
				isHit = false;
				asterYvel = ASTER_VEL;
				asterXvel = ASTER_VEL;
				points = 0;
				shipX = WINDOW_WIDTH / 2 - shipW / 2;
				shipY = 700;
				asterX = aX(rd);
				asterY = 0 - ASTER_SIZE;
				break;
			case SDLK_p:
				buttonPressed = true;
				break;
			case SDLK_RIGHT:
				if (shipX <= WINDOW_WIDTH - shipW && isHit == false && buttonPressed == true) {
					shipX += shipXvel;
				}
				break;
			case SDLK_LEFT:
				if (shipX >= 0 && isHit == false && buttonPressed==true) {
					shipX -= shipXvel;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Loop::pointsRender()
{
	TTF_Font* font;
	font = TTF_OpenFont("Nunito-Black.ttf", 36);
	if (font == NULL) {
		printf("Font cannot be retrieved! TTF ERROR: %s", TTF_GetError());
	}

	SDL_Surface* scoreHolder;
	std::stringstream strm;
	strm <<"SCORE: "<<points;
	SDL_Color color{ 255,255,255 };

	scoreHolder = TTF_RenderText_Solid(font, strm.str().c_str(), color);

	SDL_Texture* score;
	score = SDL_CreateTextureFromSurface(ren, scoreHolder);
	SDL_Rect scorePos{ WINDOW_WIDTH - scoreHolder->w,0,scoreHolder->w,scoreHolder->h };
	SDL_RenderCopy(ren, score, NULL, &scorePos);
	
}

void Loop::shipRender()
{
	SDL_Texture* ship = IMG_LoadTexture(ren, "ship.png");
	SDL_Rect shi{ shipX, shipY, shipW, shipH };
	SDL_RenderCopy(ren, ship, NULL, &shi);
}

void Loop::asteroidRender()
{
	SDL_Texture* asteroid = IMG_LoadTexture(ren, "asteroid.png");
	SDL_Rect aster{ asterX,asterY,ASTER_SIZE,ASTER_SIZE };
	asteroidMove();
	SDL_RenderCopy(ren, asteroid, NULL, &aster);
}

void Loop::asteroidMove()
{
	asterX += asterXvel;
	asterY += asterYvel;

	if (asterX<0 || asterX>WINDOW_WIDTH - ASTER_SIZE) {
		asterXvel = -asterXvel;
	}
	if (asterY >= WINDOW_HEIGHT) {
		asterX = aX(rd);
		asterY = 0 - ASTER_SIZE;
		points++;
	}
	if (asterY + ASTER_SIZE >= shipY + 10 && asterX + ASTER_SIZE >= shipX + 10 && asterX + ASTER_SIZE <= shipX + shipW + 10) {
		isHit = true;
		asterYvel = 0;
		asterXvel = 0;
	}
}

void Loop::starRender()
{
	
	SDL_Texture* stars = IMG_LoadTexture(ren, "stars.png");
	SDL_Rect star{ 0,0,starW,starH };
	for (int i = 0; i < 3; i++) {
		star.x = x(rd);
		star.y = y(rd);
		SDL_RenderCopy(ren, stars, NULL, &star);
	}
	
}

void Loop::render()
{
	SDL_RenderClear(ren);
	
	//Game Name
	SDL_Texture* name = IMG_LoadTexture(ren, "GameName.png");
	SDL_Rect gameName = { gameX, gameY, gameW, gameH };
	SDL_RenderCopy(ren, name, NULL, &gameName);

	if (!buttonPressed) {
		SDL_Texture* button = IMG_LoadTexture(ren, "PlayButton.png");
		SDL_Rect buttonPos = {buttonX,buttonY,buttonW,buttonH};
		SDL_RenderCopy(ren, button, NULL, &buttonPos);

		starRender();
	}
	if (buttonPressed == true && isHit == false) {
		//stars
		starRender();

		//ship
		shipRender();

		//asteroid
		asteroidRender();

		//Score
		pointsRender();
	}
	if (buttonPressed == true && isHit == true) {

		replay();

		SDL_Texture* GObutton = IMG_LoadTexture(ren, "GameOver.png");
		SDL_Rect GObuttonPos = { buttonX,buttonY,buttonW,buttonH };
		SDL_RenderCopy(ren, GObutton, NULL, &GObuttonPos);

		asteroidRender();

		shipRender();

		pointsRender();
		
	}
	SDL_RenderPresent(ren);
}

void Loop::clean()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	
	TTF_Quit();
	SDL_Quit();
	exit(0);
}

void Loop::replay()
{
	TTF_Font* rFont;
	rFont = TTF_OpenFont("Nunito-Black.ttf", 36);
	if (rFont == NULL) {
		printf("Font cannot be initialised. TTF ERROR: %s", TTF_GetError());
	}

	SDL_Surface* re;
	SDL_Color rColor{ 195,239,195 };
	re = TTF_RenderText_Solid(rFont, "Press R to Replay!", rColor);

	SDL_Texture* rMessage;
	rMessage = SDL_CreateTextureFromSurface(ren, re);
	SDL_Rect rPos{ WINDOW_WIDTH / 2 - re->w / 2,500,re->w,re->h};

	SDL_RenderCopy(ren, rMessage, NULL, &rPos);
}
