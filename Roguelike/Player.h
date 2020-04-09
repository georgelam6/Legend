#pragma once

#include <SDL2/SDL.h>

#include "Vector2.h"
#include "UI.h"

#include <fstream>

class Level;

class Player
{
public:
	Player();
	Player(Vector2 startPos, UI* ui);

	void Update(Level *level, bool isPickupKeyPressed);
	void Render(SDL_Renderer* renderer, SDL_Texture* image);

	void MoveLeft(Level* level);
	void MoveRight(Level* level);
	void MoveUp(Level* level);
	void MoveDown(Level* level);

	void KillEnemy(Level* level, int id, const char* type);
	void AttackEnemy(const char* type, int damage);

	void TakeDamage(const char* e, int amount);

	Vector2 position;
	int health, money, attackDamage, lightSize, monstersKilled;
	bool isDead;

	int highMonster;
	int highGold;

private:
	SDL_Rect srcRect, destRect;
	UI* hud;
	std::ifstream saveFileIn;
	std::ofstream saveFile;

};