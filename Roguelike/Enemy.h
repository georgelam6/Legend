#pragma once

#include <SDL2/SDL.h>

#include "Vector2.h"

#include "Globals.h"
#include "Player.h"

#include <string>

class Enemy
{
public:
	Enemy();
	Enemy(std::string type, Vector2 startPos, int id);
	void Update(Player* guy, int map[Globals::levelWidth][Globals::levelHeight]);
	void Render(SDL_Renderer* renderer, SDL_Texture* texture);

	void MoveLeft(int map[Globals::levelWidth][Globals::levelHeight], Player* guy);
	void MoveRight(int map[Globals::levelWidth][Globals::levelHeight], Player* guy);
	void MoveUp(int map[Globals::levelWidth][Globals::levelHeight], Player* guy);
	void MoveDown(int map[Globals::levelWidth][Globals::levelHeight], Player* guy);

	bool TakeDamage(int amount);

	std::string type;
	char character;
	int attackDamage, health;
	Vector2 position;

	int id;
private:
	SDL_Rect srcRect;
};

