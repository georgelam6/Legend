#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <string>

class UI
{
public:
	void printMessage(const char* message);

	std::vector<SDL_Rect> createMessage(const char* message);

	void Update(int playerHealth, int playerMoney, int attackDamage, int armour);
	void Render(SDL_Renderer* renderer, SDL_Texture* texture);
	void RenderEndScreen(SDL_Renderer* renderer, SDL_Texture* texture, int monstersKilled, int money);
	void RenderHighScore(SDL_Renderer* renderer, SDL_Texture* texture, int highmoney, int highmonster);
	void RenderMainMenu(SDL_Renderer* renderer, SDL_Texture* texture);
	void RenderInventory(SDL_Renderer* renderer, SDL_Texture* texture, std::string inventory[3]);

private:
	std::vector<SDL_Rect> currentMessage;
	std::vector<SDL_Rect> hud;
};

