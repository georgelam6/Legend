#pragma once

#include <SDL2/SDL.h>


class Graphics
{
public:
	void Init();
	void Clean();
	void Clear();
	void FlipBuffers();

	SDL_Renderer* renderer;
	SDL_Texture* termSheet;
	SDL_Texture* uiSheet;
private:
	SDL_Window* window;
};

