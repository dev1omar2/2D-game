#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#ifndef BULLET_H
#define BULLET_H
class Bullet
{
public:
	int WorldX;
	int WorldY;

	int ScreenX;
	int ScreenY;

	SDL_Surface* UpSurface = IMG_Load("Assets/Bullet_up.png");
	SDL_Surface* DownSurface = IMG_Load("Assets/Bullet_down.png");
	SDL_Surface* RightSurface = IMG_Load("Assets/Bullet_right.png");
	SDL_Surface* LeftSurface = IMG_Load("Assets/Bullet_left.png");


	SDL_Texture* MainTexture;

	SDL_Texture* RightTex;
	SDL_Texture* LeftTex;
	SDL_Texture* UpTex;
	SDL_Texture* DownTex;

	SDL_Rect dstR;
	int BaseVel = 20;
	bool Visible;

	int Direction;

	Bullet();
	Bullet(int WorldX, int WorldY, int ScreenX, int ScreenY, SDL_Renderer* renderer);
	~Bullet();

	void update(int PlayerWorldX, int PlayerWorldY, int PlayerScreenX, int PlayerScreenY, int &direction);
	void render(SDL_Renderer* renderer);

};


#endif BULLET_H

