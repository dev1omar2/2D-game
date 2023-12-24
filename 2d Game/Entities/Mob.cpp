#include "Mob.h"


Mob::Mob() {}


Mob::Mob(int WorldX, int WorldY, int TileSize, SDL_Renderer* renderer, Game *game) {
    this->WorldX = WorldX;
    this->WorldY = WorldY;
    this->game = game;

    dstR.w = TileSize;
    dstR.h = TileSize;

    SDL_Surface* tmpSurface = IMG_Load("Assets/skeletonlord_down_1.png");
    Down_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_down_2.png");
    Down_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_up_1.png");
    Up_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_up_2.png");
    Up_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_right_1.png");
    Right_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_right_2.png");
    Right_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_left_1.png");
    Left_1 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    tmpSurface = IMG_Load("Assets/skeletonlord_left_2.png");
    Left_2 = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    SDL_FreeSurface(tmpSurface);
}

Mob::~Mob() { std::cout << "Mob DEstroyed\n"; }

void Mob::update(int PlayerWorldX, int PlayerWorldY, int PlayerScreenX, int PlayerScreenY, std::vector<std::vector<Tile>> tiles, Player *player) {

    int goalCol = player->getCol();
    int goalRow = player->getRow();

    searchPath(goalCol, goalRow, tiles);

    // Reset texture and frames if not moving

    
    // Movement logic
    switch (direction) {
    case 0:
    {
        VelocityX = 0;
        VelocityY = 0;

        std::cout << "0\n";

        break;
    }


    case 1: // right
        if (FRAMES == 12) {
            FRAMES = 0;
        }
        if (FRAMES == 0) {
            Maintexture = Right_1;
        }
        if (FRAMES == 6) {
            Maintexture = Right_2;
        }


        FRAMES++;
        VelocityX = BaseVel;
        VelocityY = 0;

        
        break;

    case 2: // left
        
        if (FRAMES == 12) {
            FRAMES = 0;
        }
        if (FRAMES == 0) {
            Maintexture = Left_1;
        }
        if (FRAMES == 6) {
            Maintexture = Left_2;
        }

        FRAMES++;
        VelocityX = -BaseVel;
        VelocityY = 0;

        if (FRAMES == 11) {
            FRAMES = 0;
        }

        break;

    case 3: // up
        
        if (FRAMES == 12) {
            FRAMES = 0;
        }
        if (FRAMES == 0) {
            Maintexture = Up_1;
        }
        if (FRAMES == 6) {
            Maintexture = Up_2;
        }

        FRAMES++;
        VelocityX = 0;
        VelocityY = -BaseVel;

        if (FRAMES == 11) {
            FRAMES = 0;
        }

        break;

    case 4: // down
        
        if (FRAMES == 12) {
            FRAMES = 0;
        }
        if (FRAMES == 0) {
            Maintexture = Down_1;
        }
        if (FRAMES == 6) {
            Maintexture = Down_2;
        }

        FRAMES++;
        VelocityX = 0;
        VelocityY = BaseVel;

        if (FRAMES == 11) {
            FRAMES = 0;
        }

        break;

    default:
        // Invalid move, stop the mob
        VelocityX = 0;
        VelocityY = 0;
        break;
    }

    // Update position based on velocity
    this->WorldX += VelocityX;
    this->WorldY += VelocityY;

    // Update screen position
    this->ScreenX = this->WorldX - PlayerWorldX + PlayerScreenX * 32;
    this->ScreenY = this->WorldY - PlayerWorldY + PlayerScreenY * 32;

    dstR.x = ScreenX;
    dstR.y = ScreenY;
}

void Mob::render(SDL_Renderer* renderer) {
    if (Visible && this->ScreenX > -32 && this->ScreenX < 832 && this->ScreenY > -32 && this->ScreenY < 672)
        SDL_RenderCopy(renderer, this->Maintexture, nullptr, &dstR);
}

bool Collision(Mob* mob, std::vector<std::vector<Tile>> tiles)
{

    for (int i = 0; i < 25; i++) {
        for (int k = 0; k < 25; k++) {

            if (tiles[i][k].isSolid)
            {
                if (
                    mob->WorldX + 1 < tiles[i][k].WorldX + 32 &&
                    mob->WorldX + 1 + 10 > tiles[i][k].WorldX &&
                    mob->WorldY + 9 < tiles[i][k].WorldY + 32 &&
                    mob->WorldY + 9 + 5 > tiles[i][k].WorldY
                    )
                {
                    return true;
                }
            }

        }
    }


    return false;
}

void Mob::searchPath(int col, int row, std::vector<std::vector<Tile>> tiles)
{
    int startCol = this->WorldX / 32;
    int startRow = this->WorldY / 32;

    game->pathFinder.setNode(startCol, startRow, col, row);

    if (game->pathFinder.search())
    {
        int nextX = game->pathFinder.pathList[0].col * 32;
        int nextY = game->pathFinder.pathList[0].row * 32;

        int enLeftX = WorldX + 11;
        int enRightX = WorldX + 11 + 10;
        int enTopY = WorldY + 11;
        int enBottomY = WorldY + 11 + 9;

        if (enTopY > nextY && enLeftX >= nextX && enRightX < nextX + 32)
        {
            direction = 3;
        }
        else if (enTopY < nextY && enLeftX >= nextX && enRightX < nextX + 32)
        {
            direction = 4;
        }
        else if (enTopY >= nextY && enBottomY < nextY + 32)
        {
            if (enLeftX > nextX) {
                direction = 2;
            }
            if (enLeftX < nextX)
            {
                direction = 1;
            }

        }
        else if (enTopY > nextY && enLeftX > nextX)
        {
            direction = 3;
            if (Collision(this, tiles)) {
                direction = 2;
            }
        }
        else if (enTopY > nextY && enLeftX < nextX)
        {
            direction = 3;
            if (Collision(this, tiles))
            {
                direction = 1;

            }
        }
        else if (enTopY < nextY && enLeftX > nextX)
        {
            direction = 4;
            if (Collision(this, tiles))
            {
                direction = 2;
            }

        }

        else if (enTopY < nextY && enLeftX < nextX)
        {
            direction = 4;
            if (Collision(this, tiles))
            {
                direction = 1;
            }

        }

        
    }
}