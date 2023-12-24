#include "Game.h"

Game* game = nullptr;

int main(int argc, char * argv[])
{
	game = new Game();

	game->init("title", 800, 640);

	Uint32 frameStart;
	int frameTime = 0;
	int frames = 0;

	int FPS = 60;
	int FrameDelay = 1000 / FPS;

	

	while (game->running) {
		frameStart = SDL_GetTicks();
		

		
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		frames++;

		

		if (frameTime < FrameDelay) {
			SDL_Delay(FrameDelay - frameTime);
		}
	
	}

	game->clean();
	delete game;


	return 0;
}