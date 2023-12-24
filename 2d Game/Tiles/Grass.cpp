#include "Grass.h"



Grass::Grass()
{

}
Grass::~Grass()
{

}
void Grass::init(int WorldX, int WorldY, SDL_Renderer* renderer, int TileSize, const char*  filePath) {
	
	this->WorldX = WorldX;
	this->WorldY = WorldY;

	SDL_Surface* tmpSurface = IMG_Load(filePath);
	this->texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	this->dstR.w = TileSize;
	this->dstR.h = TileSize;
	
}

void Grass::update(int PlayerScreenX, int PlayerScreenY, int PlayerWorldX, int PlayerWorldY)
{
	this->ScreenX = this->WorldX - PlayerWorldX + PlayerScreenX;
	this->ScreenY = this->WorldY - PlayerWorldY + PlayerScreenY;

	this->dstR.x = ScreenX;
	this->dstR.y = ScreenY;

}
void Grass::render(SDL_Renderer* renderer)
{

	SDL_RenderCopy(renderer, this->texture, NULL, &dstR);

	
}
