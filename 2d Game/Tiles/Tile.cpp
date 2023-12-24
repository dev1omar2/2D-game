#include "Tile.h"

Tile::Tile()
{

}
Tile::~Tile()
{

}

void Tile::init(int WorldX, int WorldY, SDL_Renderer* renderer, int TileSize, const char* filePath, bool isSolid) {

	this->WorldX = WorldX;
	this->WorldY = WorldY;
	this->renderer = renderer;

	SDL_Surface* tmpSurface = IMG_Load(filePath);
	this->texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	this->dstR.w = TileSize;
	this->dstR.h = TileSize;
	this->isSolid = isSolid;

}

void Tile::update(int PlayerScreenX, int PlayerScreenY, int PlayerWorldX, int PlayerWorldY)
{
	this->ScreenX = this->WorldX - PlayerWorldX + PlayerScreenX;
	this->ScreenY = this->WorldY - PlayerWorldY + PlayerScreenY;

	this->dstR.x = ScreenX;
	this->dstR.y = ScreenY;


}
void Tile::render(SDL_Renderer* renderer)
{
	if (this->ScreenX <= 816 && this->ScreenX >= -32 && this->ScreenY <= 656 && this->ScreenY >= -32)
		SDL_RenderCopy(renderer, this->texture, NULL, &dstR);
}