#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Tile.h"
#include <vector>

#ifndef GRASS_H
#define GRASS_H

class Grass
{
public:

	Grass();
	~Grass();

	void init(int WorldX, int WorldY, SDL_Renderer* renderer, int TileSize, const char* filePath);
	void update(int PlayerScreenX, int PlayerScreenY, int PlayerWorldX, int PlayerWorldY);
	void render(SDL_Renderer* renderer);

	int WorldX;
	int WorldY;
	int ScreenX;
	int ScreenY;
	SDL_Texture* texture;

private:
	SDL_Renderer* renderer;
	SDL_Rect dstR;
	
};


#endif GRASS_H


