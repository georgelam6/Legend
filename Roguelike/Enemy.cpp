#include "Enemy.h"

#include "Globals.h"

#include "Random.h"


Enemy::Enemy() {}
Enemy::Enemy(std::string name, Vector2 startPos, int id)
{
	this->id = id;

	this->type = name;
	this->position = startPos;

	if (this->type == "Ogre")
	{
		this->health = 40;
		this->attackDamage = 21;
		this->srcRect = { 240, 96, 16,16 };
	}
	else if (this->type == "Elf")
	{
		this->health = 10;
		this->attackDamage = 6;
		this->srcRect = { 80, 96, 16,16 };
	}
	else if (this->type == "Goblin")
	{
		this->health = 50;
		this->attackDamage = 21;
		this->srcRect = { 112, 64, 16,16 };
	}
	else if (this->type == "Troll")
	{
		this->health = 50;
		this->attackDamage = 31;
		this->srcRect = { 64, 80, 16,16 };
	}
}

void Enemy::Update(Player* guy, int map[Globals::levelWidth][Globals::levelHeight])
{
	if (guy->position.x < this->position.x)
	{
		this->MoveLeft(map, guy);
	}
	else if (guy->position.x > this->position.x)
	{
		this->MoveRight(map, guy);
	}
	else if (guy->position.y < this->position.y)
	{
		this->MoveUp(map, guy);
	}
	else if (guy->position.y > this->position.y)
	{
		this->MoveDown(map, guy);
	}
}

void Enemy::Render(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect destRect = { this->position.x * Globals::gridCellSize, this->position.y * Globals::gridCellSize, Globals::gridCellSize, Globals::gridCellSize };
	SDL_RenderCopy(renderer, texture, &this->srcRect, &destRect);
}


void Enemy::MoveDown(int map[Globals::levelWidth][Globals::levelHeight], Player* guy)
{
	int mv = this->position.y + 1;
	if (map[this->position.x][mv] != 1)
	{
		if (mv == guy->position.y && this->position.x == guy->position.x)
		{
			// Attack the guy
			guy->TakeDamage(this->type.c_str(), Random::randint(1, this->attackDamage));
			return;
		}
		this->position.y = mv;
	}
}

void Enemy::MoveUp(int map[Globals::levelWidth][Globals::levelHeight], Player* guy)
{
	int mv = this->position.y - 1;
	if (map[this->position.x][mv] != 1)
	{
		if (mv == guy->position.y && this->position.x == guy->position.x)
		{
			// Attack the guy
			guy->TakeDamage(this->type.c_str(), Random::randint(1, this->attackDamage));
			return;
		}
		this->position.y = mv;
	}
}

void Enemy::MoveLeft(int map[Globals::levelWidth][Globals::levelHeight], Player* guy)
{
	int mv = this->position.x - 1;
	if (map[mv][this->position.y] != 1)
	{
		if (mv == guy->position.x && this->position.y == guy->position.y)
		{
			// Attack the guy
			guy->TakeDamage(this->type.c_str(), Random::randint(1, this->attackDamage));
			return;
		}
		this->position.x = mv;
	}
}

void Enemy::MoveRight(int map[Globals::levelWidth][Globals::levelHeight], Player* guy)
{
	int mv = this->position.x + 1;
	if (map[mv][this->position.y] != 1)
	{
		if (mv == guy->position.x && this->position.y == guy->position.y)
		{
			// Attack the guy
			guy->TakeDamage(this->type.c_str(), Random::randint(1, this->attackDamage));
			return;
		}
		this->position.x = mv;
	}
}


bool Enemy::TakeDamage(int amount)
{
	this->health -= amount;
	if (this->health <= 0)
	{
		return true;
	}
	return false;
}