#include "Game.h"

#include "PathFinder.h"
#include "Mob.h"

std::vector<std::vector<Tile>> tiles;


Player* player;
std::vector<Bullet*> bullets;
std::vector<int> directions;

int BULLETSINDEX = 0;



enum DIRECTION {
	NOTHING = -1,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

int BulletDirection = NOTHING;
Mob *mob1;




std::vector<int> getDimensions(const std::string& filePath) {
	std::ifstream file(filePath);
	std::vector<int> dimensions(2, 0);

	if (file.is_open()) {
		std::string line;
		int rowCount = 0;
		int colCount = 0;

		// Read each line in the file
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			int value;

			// Count the number of elements in each line
			while (iss >> value) {
				colCount++;
			}

			rowCount++;
		}

		// Update dimensions vector
		dimensions[0] = colCount / rowCount;
		dimensions[1] = rowCount;

		file.close();
	}
	else {
		std::cerr << "Unable to open the file: " << filePath << std::endl;
	}

	return dimensions;
}


bool Collision(Player* player, std::vector<std::vector<Tile>> tiles)
{

	for (int i = 0; i < 25; i++) {
		for (int k = 0; k < 25; k++) {

			if (tiles[i][k].isSolid)
			{
				if (
					player->WorldX + 1 < tiles[i][k].WorldX + 32 &&
					player->WorldX + 1 + 10 > tiles[i][k].WorldX &&
					player->WorldY + 9 < tiles[i][k].WorldY + 32 &&
					player->WorldY + 9 + 5 > tiles[i][k].WorldY
					)
				{
					return true;
				}
			}

		}
	}


	return false;
}

Game::Game()
{
	
	

}
Game::~Game()
{

}
void Game::init(const char* title, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && IMG_Init(IMG_INIT_PNG) != 0) {
		this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		this->renderer = SDL_CreateRenderer(window, -1, 0);
		running = true;
	}
	
	this->TileSize = 32;
	this->w = width;
	this->h = height;
	
	this->columns = getDimensions("Maps/Map2.txt")[0];
	this->rows = getDimensions("Maps/Map2.txt")[1];

	

	this->LoadMap("Maps/Map2.txt");
	std::cout << tiles.data() << std::endl;

	SDL_Surface* tmpSurface = IMG_Load("Assets/Paused.png");

	this->PausedTex = SDL_CreateTextureFromSurface(this->renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	PausedR.w = 400;
	PausedR.h = 400;
	PausedR.x = 200;
	PausedR.y = 200;
	
	player = new Player(400, 320, 400, 320, this->renderer, 32, 7);
	
	pathFinder = new PathFinder(this, tiles);

	for (int i = 0; i < 10; i++)
	{

		bullets.push_back(new Bullet(player->WorldX, player->WorldY, player->ScreenX, player->ScreenY, this->renderer));
		directions.push_back(DIRECTION::NOTHING);
	}
	mob1 = new Mob(500, 300, TileSize, renderer, this);
	
	
}
void Game::handleEvents()
{
	float prevX = player->WorldX;
	float prevY = player->WorldY;

	while (SDL_PollEvent(&this->event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}

		if (event.type == SDL_KEYDOWN) {
			// Handle movement based on collision results
			if (event.key.keysym.sym == SDLK_w && !Paused) {
				player->Up = !Collision(player, tiles);
			}


			if (event.key.keysym.sym == SDLK_s && !Paused) {
				player->Down = !Collision(player, tiles);
			}

			if (event.key.keysym.sym == SDLK_d && !Paused) {
				player->Right = !Collision(player, tiles);
			}

			if (event.key.keysym.sym == SDLK_a && !Paused) {
				player->Left = !Collision(player, tiles);
			}

			// cheking if not clicking to prevent moving in both axis
			
				if (event.key.keysym.sym != SDLK_w)
					player->Up = false;

				if (event.key.keysym.sym != SDLK_s)
					player->Down = false;

				if (event.key.keysym.sym != SDLK_d)
					player->Right = false;

				if (event.key.keysym.sym != SDLK_a)
					player->Left = false;
			
			


			// Pausing
			if (event.key.keysym.sym == SDLK_SPACE && !Paused) {
				Paused = true;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE && Paused) {
				Paused = false;
			}

			// bullet stuff
			if (event.key.keysym.sym == SDLK_e && bullets[BULLETSINDEX]->WorldX == player->WorldX && bullets[BULLETSINDEX]->WorldY == player->WorldY)
			{
				if (player->Maintexture == player->Right_1 || player->Maintexture == player->Right_2)
				{
					directions[BULLETSINDEX] = RIGHT;
					BULLETSINDEX++;

					if (BULLETSINDEX == 10) {
						BULLETSINDEX = 0;
					}

				}

				if (player->Maintexture == player->Left_1 || player->Maintexture == player->Left_2)
				{
					directions[BULLETSINDEX] = LEFT;
					BULLETSINDEX++;

					if (BULLETSINDEX == 10) {
						BULLETSINDEX = 0;
					}
				}

				if (player->Maintexture == player->Up_1 || player->Maintexture == player->Up_2)
				{
					directions[BULLETSINDEX] = UP;
					BULLETSINDEX++;

					if (BULLETSINDEX == 10) {
						BULLETSINDEX = 0;
					}
				}
				if (player->Maintexture == player->Down_1 || player->Maintexture == player->Down_2)
				{
					directions[BULLETSINDEX] = DOWN;
					BULLETSINDEX++;

					if (BULLETSINDEX == 10) {
						BULLETSINDEX = 0;
					}
				}
			}

		}

	}

		if (event.type == SDL_KEYUP) {
			
			
			if (event.key.keysym.sym == SDLK_w) {
					player->Up = false;
			}

			if (event.key.keysym.sym == SDLK_s) {
				player->Down = false;
			}

			if (event.key.keysym.sym == SDLK_d) {

				player->Right = false;
			}

			if (event.key.keysym.sym == SDLK_a) {
				player->Left = false;
			}
			
			
			
		}
	

	// Update player position based on movement flags
	if (!Paused) {
		player->update();
	}

	// If a collision is detected, move the player back to the previous position
	if (Collision(player, tiles) && !Paused) {
		player->WorldX = prevX;
		player->WorldY = prevY;
	}

	
}



void Game::update()
{
	if (!Paused)
	{
		
		
		
		
			
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->update(player->WorldX, player->WorldY, player->ScreenX, player->ScreenY, directions[i]);
		}
			
		
		for (std::vector<Tile>& VectorTile : tiles)
		{
			for (Tile& tile : VectorTile)
			{
				tile.update(player->ScreenX, player->ScreenY, player->WorldX, player->WorldY);
			}
		}
		mob1->update(player->WorldX, player->WorldY, player->ScreenX, player->ScreenY, tiles, player);
		
	}
}

void Game::render()
{
	
		SDL_SetRenderDrawColor(renderer, 255, 178, 96, 255);
		SDL_RenderClear(renderer);

		
		for (std::vector<Tile>& VectorTile : tiles)
		{
			for (Tile& tile : VectorTile)
			{
				tile.render(renderer);
			}
		}
		
		
		

		
		for (Bullet* bullet : bullets)
		{
			bullet->render(renderer);
		}

		mob1->render(renderer);
		
		player->render(this->renderer);
	
		if (Paused)
		{
			SDL_RenderCopy(renderer, PausedTex, NULL, &PausedR);
		}


	SDL_RenderPresent(renderer);

	
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}



void Game::LoadMap(const char* filePath)
{
	std::fstream MapFile(filePath);

	char character;

	

	if (MapFile.is_open())
	{
		int i = 0;
		int k = 0;

		std::vector<Tile> tiles1;

		tiles.push_back(tiles1);

		while (MapFile.get(character))
		{
			
			if (character == '1') {
				Tile grass = Tile();
				grass.init(i * TileSize, k * TileSize, renderer, TileSize, "Assets/grass.png", false);
				tiles[i].push_back(grass);

				if (k >= 25) {
					std::cout << "Loaded" << std::endl;
				}
				
				continue;
			}
			if (character == '2') {
				Tile earth = Tile();
				earth.init(i * TileSize, k * TileSize, renderer, TileSize, "Assets/earth.png", false);
				tiles[i].push_back(earth);

				if (k >= 25) {
					std::cout << "Loaded" << std::endl;
				}

				continue;
			}

			if (character == '3') {
				Tile tree = Tile();
				tree.init(i * TileSize, k * TileSize, renderer, TileSize, "Assets/tree.png", true);
				tiles[i].push_back(tree);

				if (k >= 25) {
					std::cout << "Loaded" << std::endl;
				}

				continue;
			}

			if (character == ' ') {
				k++;
				continue;
			}
			if (character == '\n') {
				k = 0;
				i++;
				std::vector<Tile> TileVector;
				tiles.push_back(TileVector);
				continue;
			}
		}
	}
}