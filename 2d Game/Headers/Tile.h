#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "iostream"


#ifndef TILE_H
#define TILE_H


class Tile
{
public:

	Tile();
	~Tile();

	int WorldX;
	int WorldY;
	int ScreenX;
	int ScreenY;
	SDL_Texture* texture;
	bool isSolid;

	void init(int WorldX, int WorldY, SDL_Renderer* renderer, int TileSize, const char* filePath, bool isSolid);
	void update(int PlayerScreenX, int PlayerScreenY, int PlayerWorldX, int PlayerWorldY);
	void render(SDL_Renderer* renderer);

	std::pair<int, int> getCordinates(Tile tile)
	{
		return std::pair<int, int>(tile.WorldX, tile.WorldY);
	}


private:
	SDL_Renderer* renderer;
	SDL_Rect dstR;
	
};

#endif TILE_H

