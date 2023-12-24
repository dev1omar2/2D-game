#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>



#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	int WorldX;
	int WorldY;
	int ScreenX;
	int ScreenY;
	int FRAMES;

	bool Right;
	bool Left;
	bool Up;
	bool Down;

	int w;
	int h;

	int BaseVel;

	int VelocityX;
	int VelocityY;

	SDL_Texture* Maintexture;
	SDL_Texture* Down_1;
	SDL_Texture* Down_2;
	SDL_Texture* Up_1;
	SDL_Texture* Up_2;
	SDL_Texture* Right_1;
	SDL_Texture* Right_2;
	SDL_Texture* Left_1;
	SDL_Texture* Left_2;
	


	Player(int WorldX, int WorldY, int ScreenX, int ScreenY, SDL_Renderer* renderer, int TileSize, int BaseVel);
	Player() {}
	~Player();

	void update();
	void render(SDL_Renderer* renderer);

	int getCol()
	{
		return this->WorldX / 32;
	}
	int getRow()
	{
		return this->WorldY / 32;
	}

private:
	SDL_Rect dstR;
};

#endif