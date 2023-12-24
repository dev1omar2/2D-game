#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Game.h"



#ifndef MOB_H
#define MOB_H



class Mob
{
public:
	int WorldX;
	int WorldY;

	int ScreenX;
	int ScreenY;

	int HP = 100;

	int BaseVel = 1;
	int VelocityX;
	int VelocityY;

	bool Visible = true;

	bool Right;
	bool Left;
	bool Up;
	bool Down;

	int FRAMES = 0;

	SDL_Texture* Maintexture;

	SDL_Texture* Right_1;
	SDL_Texture* Left_1;
	SDL_Texture* Up_1;
	SDL_Texture* Down_1;

	SDL_Texture* Right_2;
	SDL_Texture* Left_2;
	SDL_Texture* Up_2;
	SDL_Texture* Down_2;

	std::vector<int> m_path;
	std::vector<int> coasts;
	Game *game;

	int direction;

	SDL_Rect dstR;

	Mob();
	~Mob();
	Mob(int WorldX, int WorldY, int TileSize, SDL_Renderer* renderer, Game game);
	void update(int PlayerWorldX, int PlayerWorldY, int PlayerScreenX, int PlayerScreenY, std::vector<std::vector<Tile>> tiles, Player *player);
	void render(SDL_Renderer* renderer);

	
	void searchPath(int col, int row, std::vector<std::vector<Tile>> tiles);
};


#endif MOB_H