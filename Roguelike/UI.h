#pragma once

#include <vector>
#include <SDL2/SDL.h>

class UI
{
public:
	void printMessage(const char* message);

	std::vector<SDL_Rect> createMessage(const char* message);

	void Update(int playerHealth, int playerMoney, int attackDamage);
	void Render(SDL_Renderer* renderer, SDL_Texture* texture);
	void RenderEndScreen(SDL_Renderer* renderer, SDL_Texture* texture, int monstersKilled, int money);
	void RenderHighScore(SDL_Renderer* renderer, SDL_Texture* texture, int highmoney, int highmonster);
	void RenderMainMenu(SDL_Renderer* renderer, SDL_Texture* texture);

private:
	std::vector<SDL_Rect> currentMessage;
	std::vector<SDL_Rect> hud;
};

