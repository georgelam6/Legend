#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "Vector2.h"

class Item
{
public:
	Item();
	Item(std::string type, Vector2 position, int id);

	void Render(SDL_Renderer* renderer, SDL_Texture* texture);

	std::string type;
	Vector2 position;
	int id;
private:
	SDL_Rect srcRect;
};