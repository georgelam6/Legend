#include "Player.h"

#include "Globals.h"
#include "Level.h"

#include "Random.h"

#include <sstream>
#include <string>

Player::Player() {}
Player::Player(Vector2 startPos, UI* ui) :
	position(startPos)
{
	this->srcRect = { 0, 64, 16, 16 };
	this->destRect = { this->position.x * Globals::gridCellSize, this->position.y * Globals::gridCellSize, Globals::scaledSpriteSize, Globals::scaledSpriteSize };

	this->health = 100;
	this->money = 0;
	this->attackDamage = 15;
	this->lightSize = 6;
	this->monstersKilled = 0;

	this->hud = ui;

	this->isDead = false;
	this->saveFileIn.open("game.save");

	std::string line;
	int count = 0;
	while (std::getline(this->saveFileIn, line))
	{
		count++;
		if (count == 1) this->highMonster = std::stoi(line);
		else this->highGold = std::stoi(line);
		std::cout << this->highMonster << std::endl << this->highGold << std::endl;
	}

	this->saveFile.open("game.save");

	this->saveFile << this->highMonster << std::endl << this->highGold << std::endl;
}

void Player::Update(Level* level, bool isPickupKeyPressed)
{
	this->destRect.x = this->position.x * Globals::gridCellSize;
	this->destRect.y = this->position.y * Globals::gridCellSize;

	if (this->health <= 0)
	{
		this->isDead = true;

		if (this->money > this->highGold && this->monstersKilled > this->highMonster) {
			this->highGold = this->money; 
			this->highMonster = this->monstersKilled;
			this->saveFile << this->monstersKilled << std::endl << this->money << std::endl;
		}
		else {
			this->saveFile << this->highMonster << std::endl << this->highGold << std::endl;
		}
	}

	for (auto& i : level->items)
	{
		if (i.position.x == this->position.x && i.position.y == this->position.y && isPickupKeyPressed)
		{
			std::stringstream ss;
			if (i.type == "Sword")
			{
				this->attackDamage = 25;
				ss << "I found a " << i.type;
			}
			else if (i.type == "Axe")
			{
				this->attackDamage = 32;
				ss << "I found an " << i.type;
			}
			else if (i.type == "Lantern")
			{
				this->lightSize = 10;
				ss << "I found a " << i.type;
			}
			else if (i.type == "Coin")
			{
				int amount = Random::randint(2, 10);
				this->money += amount;
				ss << "I found " << amount << " gold coins.";
			}
			else if (i.type == "Food")
			{
				int amount = Random::randint(2, 40);
				if (health < 100)
				{
					this->health += amount;
					if (health > 100)
					{
						health = 100;
					}
					ss << "I ate something off the floor.";
				}
				else
				{
					this->health -= amount;
					ss << "I ate too much, becoming fat and unhealthy";
				}
			}
			
			hud->printMessage(ss.str().c_str());
			level->PickupItem(i.id);
		}
	}
}

void Player::Render(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, &this->srcRect, &this->destRect);
}

void Player::MoveDown(Level* level)
{
	int mv = this->position.y + 1;
	if (level->map[this->position.x][mv] != 1)
	{
		for (auto& e : level->enemies)
		{
			if (mv == e.position.y && this->position.x == e.position.x)
			{
				if (e.TakeDamage(this->attackDamage))
				{
					this->KillEnemy(level, e.id, e.type.c_str());
				}
				else
				{
					this->AttackEnemy(e.type.c_str(), this->attackDamage);
				}
				return;
			}
		}
		this->position.y = mv;
	}
}

void Player::MoveUp(Level* level)
{
	int mv = this->position.y - 1;
	if (level->map[this->position.x][mv] != 1)
	{
		for (auto& e : level->enemies)
		{
			if (mv == e.position.y && this->position.x == e.position.x)
			{
				if (e.TakeDamage(this->attackDamage))
				{
					this->KillEnemy(level, e.id, e.type.c_str());
				}
				else
				{
					this->AttackEnemy(e.type.c_str(), this->attackDamage);
				}
				return;
			}
		}
		this->position.y = mv;
	}
}

void Player::MoveLeft(Level* level)
{
	int mv = this->position.x - 1;
	if (level->map[mv][this->position.y] != 1)
	{
		for (auto& e : level->enemies)
		{
			if (mv == e.position.x && this->position.y == e.position.y)
			{
				if (e.TakeDamage(this->attackDamage))
				{
					this->KillEnemy(level, e.id, e.type.c_str());
				}
				else
				{
					this->AttackEnemy(e.type.c_str(), this->attackDamage);
				}
				return;
			}
		}
		this->position.x = mv;
	}
}

void Player::MoveRight(Level* level)
{
	int mv = this->position.x + 1;
	if (level->map[mv][this->position.y] != 1)
	{
		for (auto& e : level->enemies)
		{
			if (mv == e.position.x && this->position.y == e.position.y)
			{
				if (e.TakeDamage(this->attackDamage)) 
				{
					this->KillEnemy(level, e.id, e.type.c_str());
				}
				else
				{
					this->AttackEnemy(e.type.c_str(), this->attackDamage);
				}
				
				return;
			}
		}
		this->position.x = mv;
	}
}

void Player::AttackEnemy(const char* type, int damage)
{
	std::stringstream ss;

	ss << "I swung at the " << type << " dealing " << damage;

	hud->printMessage(ss.str().c_str());
}

void Player::KillEnemy(Level* level, int id, const char *type)
{
	std::stringstream ss;

	ss << "I slayed the " << type;
	level->KillEnemy(id);

	hud->printMessage(ss.str().c_str());

	this->monstersKilled++;
}

void Player::TakeDamage(const char* e, int amount)
{
	this->health -= amount;
	std::stringstream ss;
	ss << "A " << e << " attacked me, dealing " << std::to_string(amount) << " damage!";
	hud->printMessage(ss.str().c_str());
}