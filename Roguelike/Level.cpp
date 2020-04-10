#include "Level.h"

#include "Random.h"
#include <string>
#include <iostream>

Level::Level()
{

	srand(time(NULL));
	this->wallSrcRect = { 48,   32, 16, 16 };
	this->floorSrcRect = { 160, 240, 16, 16 };
	this->doorSrcRect = { 224, 48,  16, 16 };
	this->corpseSrcRect = { 80, 32, 16, 16 };

	this->enemyTypes.clear();
	this->enemyTypes.push_back("Ogre");
	this->enemyTypes.push_back("Elf");
	this->enemyTypes.push_back("Goblin");
	this->enemyTypes.push_back("Troll");

	this->itemTypes.clear();
	this->itemTypes.push_back("Sword");
	this->itemTypes.push_back("Lantern");
	this->itemTypes.push_back("Axe");
	this->itemTypes.push_back("Coin");
	this->itemTypes.push_back("Food");
	this->itemTypes.push_back("Leather");
	this->itemTypes.push_back("Rust");
	this->itemTypes.push_back("Iron");

	this->randonmFillPercent = 50;
	this->randomGrassPercent = 10;
}


void Level::GenerateLevel()
{
	// Set the map to NULL
	for (int x = 0; x < Globals::levelWidth; x++)
	{
		for (int y = 0; y < Globals::levelHeight; y++)
		{
			map[x][y] = 0;
		}
	}
	this->enemies.clear();


	this->RandomFillMap();
	this->SmoothMap();
	
	this->playerStartPos = createPlayerStartPos();
	this->doorPos = CreateDoorPos();

	this->FindPathToDoor();

	this->SpawnEnemies();
	this->SpawnItems();

	
}

void Level::SpawnEnemies()
{
	int count = 1;
	for (int i = 0; i < Random::randint(15, 50); i++)
	{
		Vector2 r = Vector2(Random::randint(0, Globals::levelWidth), Random::randint(0, Globals::levelHeight));
		if (map[r.x][r.y] == 0 && GetSurroundingWallCount(r.x, r.y) == 0)
		{
			enemies.push_back(Enemy(this->enemyTypes.at(Random::randint(0, enemyTypes.size() - 1)), r, count));
			count += 1;
		}
	}
}

void Level::SpawnItems()
{
	int count = 1;
	for (int i = 0; i < Random::randint(15, 50); i++)
	{
		Vector2 r = Vector2(Random::randint(0, Globals::levelWidth), Random::randint(0, Globals::levelHeight));
		if (map[r.x][r.y] == 0 && GetSurroundingWallCount(r.x, r.y) == 0)
		{
			items.push_back(Item(this->itemTypes.at(Random::randint(0, itemTypes.size() - 1)), r, count));
			count += 1;
		}
	}
}

void Level::FindPathToDoor()
{
	bool foundPath = false;
	Vector2 currentPosition = this->doorPos;

	while (!foundPath) {


		for (int x = 0; x < Globals::levelWidth; x++)
		{
			for (int y = 0; y < Globals::levelHeight; y++)
			{
				if (this->playerStartPos.x < currentPosition.x)
				{
					currentPosition.x -= 1;
				}
				else if (this->playerStartPos.x > currentPosition.x)
				{
					currentPosition.x += 1;
				}
				else if (this->playerStartPos.y < currentPosition.y)
				{
					currentPosition.y -= 1;
				}
				else if (this->playerStartPos.y > currentPosition.y)
				{
					currentPosition.y += 1;
				}

				this->map[currentPosition.x][currentPosition.y] = 0;
				if (currentPosition.x == playerStartPos.x && currentPosition.y == playerStartPos.y)
				{
					foundPath = true;
				}
			}
		}
	}
}

void Level::RandomFillMap()
{
	for (int x = 0; x < Globals::levelWidth; x++)
	{
		for (int y = 0; y < Globals::levelHeight; y++)
		{
			if (x == 0 || x == Globals::levelWidth - 1 || y == 0 || y == Globals::levelHeight - 1)
			{
				map[x][y] = 1;
			}
			else
			{
				if (Random::randint(0, 100) < randonmFillPercent)
					map[x][y] = 1;
				else
					map[x][y] = 0;
			}
		}
	}
}

Vector2 Level::createPlayerStartPos()
{
	while (true)
	{
		Vector2 r = Vector2(Random::randint(0, Globals::levelWidth), Random::randint(0, Globals::levelHeight));
		if (map[r.x][r.y] == 0 && GetSurroundingWallCount(r.x, r.y) == 0)
		{
			return r;
		}
	}

	return Vector2(0, 0);
}

Vector2 Level::CreateDoorPos()
{
	while (true)
	{
		Vector2 r = Vector2(Random::randint(0, Globals::levelWidth), Random::randint(0, Globals::levelHeight));
		if (map[r.x][r.y] == 0 && r.x != this->playerStartPos.x && r.y != this->playerStartPos.y && GetSurroundingWallCount(r.x, r.y) == 0)
		{
			map[r.x][r.y] = 2;
			return r;
		}
	}

	return Vector2(0, 0);
}

void Level::SmoothMap()
{
	for (int x = 0; x < Globals::levelWidth; x++)
	{
		for (int y = 0; y < Globals::levelHeight; y++)
		{
			int neighbourWallTiles = this->GetSurroundingWallCount(x, y);

			if (neighbourWallTiles > 4)
			{
				map[x][y] = 1;
			}
			else if (neighbourWallTiles < 4)
			{
				map[x][y] = 0;
			}
		}
	}
}

int Level::GetSurroundingWallCount(int gridx, int gridy)
{
	int wallcount = 0;
	for (int neighbourx = gridx - 1; neighbourx <= gridx + 1; neighbourx++)
	{
		for (int neighboury = gridy - 1; neighboury <= gridy + 1; neighboury++)
		{
			if (neighbourx >= 0 && neighbourx < Globals::levelWidth && neighboury >= 0 && neighboury < Globals::levelHeight)
			{
				if (neighbourx != gridx || neighboury != gridy)
				{
					wallcount += map[neighbourx][neighboury];
				}
			}
			else
			{
				wallcount++;
			}
		}
	}

	return wallcount;
}


void Level::Render(SDL_Renderer *renderer, SDL_Texture* texture, Vector2 playerPos, int lightSize)
{
	bool render = false;

	for (int x = 0; x < Globals::levelWidth; x++)
	{
		for (int y = 0; y < Globals::levelHeight; y++)
		{
			int dist = sqrt(((playerPos.x - x) * (playerPos.x - x)) + ((playerPos.y - y) * (playerPos.y - y)));

			if (dist < lightSize) {
				if (this->map[x][y] == 0)
				{
					SDL_Rect destRect = { x * Globals::gridCellSize, y * Globals::gridCellSize, Globals::scaledSpriteSize, Globals::scaledSpriteSize };
					SDL_RenderCopy(renderer, texture, &this->floorSrcRect, &destRect);
				}

				if (this->map[x][y] == 1)
				{
					SDL_Rect destRect = { x * Globals::gridCellSize, y * Globals::gridCellSize, Globals::scaledSpriteSize, Globals::scaledSpriteSize };
					SDL_RenderCopy(renderer, texture, &this->wallSrcRect, &destRect);
				}

				if (this->map[x][y] == 2)
				{
					SDL_Rect destRect = { x * Globals::gridCellSize, y * Globals::gridCellSize, Globals::scaledSpriteSize, Globals::scaledSpriteSize };
					SDL_RenderCopy(renderer, texture, &this->doorSrcRect, &destRect);
				}

				if (this->map[x][y] == 3)
				{
					SDL_Rect destRect = { x * Globals::gridCellSize, y * Globals::gridCellSize, Globals::scaledSpriteSize, Globals::scaledSpriteSize };
					SDL_RenderCopy(renderer, texture, &this->corpseSrcRect, &destRect);
				}
			}
		}
	}


	for (auto& e : this->enemies)
	{
		int dist = sqrt(((playerPos.x - e.position.x) * (playerPos.x - e.position.x)) + ((playerPos.y - e.position.y) * (playerPos.y - e.position.y)));
		if (dist < lightSize) {
			e.Render(renderer, texture);
		}
	}

	for (auto& i : this->items)
	{
		int dist = sqrt(((playerPos.x - i.position.x) * (playerPos.x - i.position.x)) + ((playerPos.y - i.position.y) * (playerPos.y - i.position.y)));
		if (dist < lightSize) {
			i.Render(renderer, texture);
		}
	}
}

void Level::Update(Player* guy)
{
	for (auto& e : this->enemies)
	{
		e.Update(guy, this->map);
	}
}

void Level::KillEnemy(int id)
{
	std::vector<Enemy> tmpVec;
	
	for (auto& en : this->enemies)
	{
		if (en.id != id)
		{
			tmpVec.push_back(en);
		}
		else
		{
			if (map[en.position.x][en.position.y] != 2)
				this->map[en.position.x][en.position.y] = 3;
		}
	}

	this->enemies = tmpVec;
}


void Level::PickupItem(int id)
{
	std::vector<Item> tmpVec;

	for (auto& it : this->items)
	{
		if (it.id != id)
		{
			tmpVec.push_back(it);
		}
	}

	this->items = tmpVec;
}