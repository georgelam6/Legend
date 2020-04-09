#pragma once

#include <SDL2/SDL.h>

#include "Globals.h"
#include "Vector2.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"

#include <string>
#include <vector>

class Level
{
public:
	Level();
	Level(SDL_Texture* image);
	void GenerateLevel();
	void RandomFillMap();
	void SmoothMap();
	void FindPathToDoor();
	Vector2 createPlayerStartPos();
	Vector2 CreateDoorPos();
	int GetSurroundingWallCount(int gridX, int gridY);
	void KillEnemy(int id);
	void PickupItem(int id);
	void SpawnEnemies();
	void SpawnItems();


	void Render(SDL_Renderer* renderer, SDL_Texture* texture, Vector2 playerPos, int lightSize);
	void Update(Player* guy);

	Vector2 playerStartPos;
	Vector2 doorPos;
	int map[Globals::levelWidth][Globals::levelHeight];

	std::vector<Enemy> enemies;
	std::vector<Item> items;

private:
	SDL_Rect wallSrcRect;
	SDL_Rect floorSrcRect;
	SDL_Rect doorSrcRect;
	SDL_Rect corpseSrcRect;

	std::vector<std::string> enemyTypes;
	std::vector<std::string> itemTypes;


	// Procedual generation vars
	int randonmFillPercent;
	int randomGrassPercent;
	const char* seed;
};

