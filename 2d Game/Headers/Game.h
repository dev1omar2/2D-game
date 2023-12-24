#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <type_traits>
#include <string>
#include <vector>
#include <sstream>

#include "Tile.h"
#include "Player.h"
#include "Node.h"

#include "Mob.h"
#include "Grass.h"
#include "Bullet.h"


#include "PathFinder.h"






#ifndef GAME_H
#define GAME_H


class Game
{
public:


	int w;
	int h;
	int columns;
	int rows;
	int TileSize;

	bool running = false;
	bool Paused = false;

	SDL_Texture* PausedTex;
	SDL_Rect PausedR;

	PathFinder pathFinder;

	Game();
	~Game();
	void init(const char* title, int width, int height);

	void handleEvents();
	void update();
	void render();
	void clean();
	void LoadMap(const char* filePath);



private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event event;

	
};




#endif GAME_H


