#include "Graphics.h"

#include <SDL2/SDL_image.h>

void Graphics::Init()
{
	SDL_CreateWindowAndRenderer(800, 624, NULL, &this->window, &this->renderer);
	SDL_SetWindowTitle(this->window, "Legend Of Cave");

	// Load the terminal spritesheet
	SDL_Surface* tmpSurf = IMG_Load("term16.asset");
	this->termSheet = SDL_CreateTextureFromSurface(this->renderer, tmpSurf);

	// Load the UI spritesheet
	tmpSurf = IMG_Load("MyTerm.asset");
	this->uiSheet = SDL_CreateTextureFromSurface(this->renderer, tmpSurf);

	// Load the Menu background
	tmpSurf = IMG_Load("menu.png");
	this->backgroundMenu = SDL_CreateTextureFromSurface(this->renderer, tmpSurf);

	SDL_FreeSurface(tmpSurf);

	this->isGraphicsMode = false;
}

void Graphics::Clean()
{
	SDL_DestroyTexture(this->termSheet);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

void Graphics::Clear()
{
	SDL_RenderClear(this->renderer);
}

void Graphics::FlipBuffers()
{
	SDL_RenderPresent(this->renderer);
}

void Graphics::ToggleGraphicsMode()
{
	isGraphicsMode = !isGraphicsMode;
	if (isGraphicsMode) {
		SDL_Surface* tmpSurf = IMG_Load("graphics.png");
		this->termSheet = SDL_CreateTextureFromSurface(this->renderer, tmpSurf);
		SDL_FreeSurface(tmpSurf);
	}
	else
	{
		SDL_Surface* tmpSurf = IMG_Load("term16.asset");
		this->termSheet = SDL_CreateTextureFromSurface(this->renderer, tmpSurf);
		SDL_FreeSurface(tmpSurf);
	}
}