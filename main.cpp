#include "SDL.h"
#include "Loop.h"

Loop* Game = nullptr;
int main(int argc, char* argv[]) {

	Game = new Loop();
	SDL_Event e;

	const int frameRate = 20;
	const int frameDelay = 1000 / frameRate;

	Game->init("Asteroids", 0, 0, 0);
	while (Game->running()) {

		Uint32 frameStart = SDL_GetTicks();

		Game->handleEvents(e);
		
		Game->render();

		int frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	Game->clean();
	return 0;
}