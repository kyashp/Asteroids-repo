#include "SDL.h"
#include "SDL_image.h"


class Loop {
private:
	//Window,Renderer information
	bool isRunning = false;
	bool buttonPressed = false;
	bool isHit = false;
	int points = 0;
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 800;

	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	
	//Button Information
	const int buttonW = 300;
	const int buttonH = 152;
	const int buttonX = WINDOW_WIDTH/2-buttonW/2;
	const int buttonY = WINDOW_HEIGHT/2-buttonH/2;

	//Game Name
	const int gameW = 302;
	const int gameH = 100;
	int gameX= WINDOW_WIDTH / 2 - gameW / 2;
	int gameY = WINDOW_HEIGHT / 5 - gameH / 5;

	//Asteroids
	const int ASTER_SIZE = 250;
	int asterX = 0;
	int asterY = 0;

	const int ASTER_VEL = 25;
	int asterXvel = ASTER_VEL;
	int asterYvel = ASTER_VEL;

	//star
	const int starW = 30;
	const int starH = 30;

	//ship
	const int shipW = 144;
	const int shipH = 75;
	int shipX = WINDOW_WIDTH / 2 - shipW / 2;
	int shipY = 700;

	const int SHIP_VEL = 75;
	int shipXvel = SHIP_VEL;
	int shipYvel = SHIP_VEL;

public:
	Loop();
	void init(const char* title, int r, int g, int b);
	bool running() {
		return isRunning;
	}
	void handleEvents(SDL_Event& e);
	void pointsRender();
	void shipRender();
	void asteroidRender();
	void asteroidMove();
	void starRender();
	void render();
	void clean();
	void replay();
};
