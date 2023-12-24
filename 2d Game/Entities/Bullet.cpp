#include "Bullet.h"




Bullet::Bullet()
{

}
Bullet::~Bullet()
{
    std::cout << "Bullet Destroyed\n";
}
Bullet::Bullet(int WorldX, int WorldY, int ScreenX, int ScreenY, SDL_Renderer* renderer)
{
	this->WorldX = WorldX;
	this->WorldY = WorldY;
	this->ScreenX = ScreenX;
	this->ScreenY = ScreenY;

	this->RightTex = SDL_CreateTextureFromSurface(renderer, this->RightSurface);
	this->LeftTex = SDL_CreateTextureFromSurface(renderer, this->LeftSurface);
	this->UpTex = SDL_CreateTextureFromSurface(renderer, this->UpSurface);
	this->DownTex = SDL_CreateTextureFromSurface(renderer, this->DownSurface);
    Visible = false;

    dstR.w = 32;
	dstR.h = 32;
}

void Bullet::update(int PlayerWorldX, int PlayerWorldY, int PlayerScreenX, int PlayerScreenY, int &direction)
{
    

    if (this->ScreenX >= 900 || this->ScreenX <= -100 || this->ScreenY >= 700 || this->ScreenY <= -100|| direction == -1) {

        //std::cout << "why?\n";
        
        this->WorldY = PlayerWorldY;
        this->ScreenY = PlayerScreenY;

        this->WorldX = PlayerWorldX;
        this->ScreenX = PlayerScreenX;

        dstR.x = ScreenX;
        dstR.y = ScreenY;

        this->Visible = false;
        

        direction = -1;
        
        
  
    }


    switch (direction)
    {

    case 0:
        this->WorldX += this->BaseVel;
        this->MainTexture = RightTex;

        this->Visible = true;
        break;

    case 1:
        this->WorldX -= this->BaseVel;
        this->MainTexture = LeftTex;
       

        this->Visible = true;
        break;

    case 2:
        this->WorldY -= this->BaseVel;
        this->MainTexture = UpTex;

        this->Visible = true;
        break;

    case 3:
        this->WorldY += this->BaseVel;
        this->MainTexture = DownTex;

        this->Visible = true;
        break;

    default:
        
        break;
    }


    

    this->ScreenX = this->WorldX - PlayerWorldX + PlayerScreenX;
    this->ScreenY = this->WorldY - PlayerWorldY + PlayerScreenY;

    dstR.x = ScreenX;
    dstR.y = ScreenY;

    
}


void Bullet::render(SDL_Renderer* renderer)
{ 
    if (this->Visible)
     SDL_RenderCopy(renderer, this->MainTexture, NULL, &dstR);
    
}