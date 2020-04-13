#pragma once

#include <SDL2/SDL.h>


class Graphics
{
public:
	void Init();
	void Clean();
	void Clear();
	void FlipBuffers();
	void ToggleGraphicsMode();

	SDL_Renderer* renderer;
	SDL_Texture* termSheet;
	SDL_Texture* uiSheet;
	SDL_Texture* backgroundMenu;
private:
	SDL_Window* window;
	bool isGraphicsMode;
};

