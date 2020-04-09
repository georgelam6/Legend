#include "Item.h"
#include "Globals.h"

Item::Item() {}
Item::Item(std::string type, Vector2 position, int id)
{
	this->type = type;
	this->position = position;
	this->id = id;

	if (this->type == "Sword")
	{
		this->srcRect = { 192, 80, 16, 16 };
	} 
	else if (this->type == "Lantern")
	{
		this->srcRect = { 240, 0, 16, 16 };
	}
	else if (this->type == "Axe")
	{
		this->srcRect = { 128, 80, 16, 16 };
	}
	else if (this->type == "Coin")
	{
		this->srcRect = { 144, 0, 16, 16 };
	}
	else if (this->type == "Food")
	{
		this->srcRect = { 192, 224, 16, 16 };
	}
}

void Item::Render(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_Rect destRect = { this->position.x * Globals::gridCellSize, this->position.y * Globals::gridCellSize, Globals::gridCellSize, Globals::gridCellSize};
	SDL_RenderCopy(renderer, texture, &this->srcRect, &destRect);
}