#include "Player.h"



Player::Player(int WorldX, int WorldY, int ScreenX, int ScreenY, SDL_Renderer* renderer, int TileSize, int BaseVel)
{
	this->WorldX = WorldX;
	this->WorldY = WorldY;

	this->ScreenX = ScreenX;
	this->ScreenY = ScreenY;
	

	this->dstR.w = TileSize;
	this->dstR.h = TileSize;
	this->dstR.x = ScreenX;
	this->dstR.y = ScreenY;

	Right = false;
	Left = false;
	Up = false;
	Down = false;

	VelocityX = 0;
	VelocityY = 0;
	this->BaseVel = BaseVel;

	SDL_Surface* tmpSurface = IMG_Load("Assets/boy_down_1.png");
	Down_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_down_2.png");
	Down_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_up_1.png");
	Up_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_up_2.png");
	Up_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_right_1.png");
	Right_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_right_2.png");
	Right_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_left_1.png");
	Left_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	tmpSurface = IMG_Load("Assets/boy_left_2.png");
	Left_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

	this->Maintexture = Up_1;

	SDL_FreeSurface(tmpSurface);

	this->w = 32;
	this->h = 32;
	FRAMES++;
}

Player::~Player()
{
	std::cout << "Player Destroyed\n";
}


void Player::update()
{
	
	
	if (Right) {
		
		if (FRAMES == 12) {
			FRAMES = 0;
		}

		if (FRAMES == 0) {
			this->Maintexture = Right_1;
		}
		if (FRAMES == 6) {
			this->Maintexture = Right_2;
		}
		
		

		FRAMES++;
		VelocityX = BaseVel;
	}
	if (Left) {
		
		if (FRAMES == 12) {
			FRAMES = 0;
		}

		if (FRAMES == 0) {
			this->Maintexture = Left_1;
		}
		if (FRAMES == 6) {
			this->Maintexture = Left_2;
		}



		FRAMES++;

		VelocityX = -BaseVel;
	}
	if (Up) {
		
		if (FRAMES == 12) {
			FRAMES = 0;
		}

		if (FRAMES == 0) {
			this->Maintexture = Up_1;
		}
		if (FRAMES == 6) {
			this->Maintexture = Up_2;
		}



		FRAMES++;

		VelocityY = -BaseVel;
	}
	if (Down) {
		
		if (FRAMES == 12) {
			FRAMES = 0;
		}

		if (FRAMES == 0) {
			this->Maintexture = Down_1;
		}
		if (FRAMES == 6) {
			this->Maintexture = Down_2;
		}



		FRAMES++;

		VelocityY = BaseVel;
	}

	if (!Right && !Left) {
		VelocityX = 0;
	}
	if (!Up && !Down) {
		VelocityY = 0;
	}

	this->WorldX += VelocityX;
	this->WorldY += VelocityY;

}
void Player::render(SDL_Renderer* renderer)
{
	
	SDL_RenderCopy(renderer, this->Maintexture, NULL, &dstR);
}

