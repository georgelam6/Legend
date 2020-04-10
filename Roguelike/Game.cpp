#include "Game.h"
#include "Player.h"
#include "Level.h"
#include "UI.h"

#include <fstream>

Player guy;
Level level;
UI hud;

bool turn;
bool useKey;
bool menu;
bool scores;
bool inv;

const char* startMessage = "A musty smell hits me as I enter the caves...";

void Game::Init()
{
	this->running = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	this->graphics.Init();

	level.GenerateLevel();
	guy = Player(level.playerStartPos, &hud);

	menu = true;
	scores = false;
}

void Game::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			this->running = false;
		}

		if (event.type == SDL_KEYDOWN && turn && !menu && !scores && !inv)
		{
			turn = false;
			useKey = false;
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				guy.MoveLeft(&level);
				break;
			case SDLK_RIGHT:
				guy.MoveRight(&level);
				break;
			case SDLK_UP:
				guy.MoveUp(&level);
				break;
			case SDLK_DOWN:
				guy.MoveDown(&level);
				break;

			case SDLK_q:
				if (guy.isDead)
				{
					menu = true;
				}
				break;
			case SDLK_ESCAPE:
				if (!guy.isDead)
				{
					menu = true;
				}
			case SDLK_r:
				if (guy.isDead)
				{
					level.GenerateLevel();
					guy = Player(level.playerStartPos, &hud);

					hud.printMessage(startMessage);

					guy.isDead = false;
				}
				break;
			case SDLK_e:
				if (!guy.isDead)
				{
					inv = true;
				}


			case SDLK_SPACE: // Next level!
				useKey = true;
				if (guy.position.x == level.doorPos.x && guy.position.y == level.doorPos.y)
				{
					level.GenerateLevel();
					guy.position = level.playerStartPos;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (menu && !inv) {
					switch (event.key.keysym.sym) {
					case SDLK_s:
						menu = false;
						level.GenerateLevel();
						guy = Player(level.playerStartPos, &hud);

						hud.printMessage(startMessage);

						guy.isDead = false;
						break;
					case SDLK_q:
						this->running = false;
						break;
					case SDLK_h:
						menu = false;
						scores = true;
					default:
						break;
					}
				}
				else if (scores && !inv)
				{
					switch (event.key.keysym.sym) {
					case SDLK_b:
						menu = true;
						scores = false;
						break;
					default:
						break;
					}
				}
				else if (inv)
				{
					switch (event.key.keysym.sym) {
					case SDLK_b:
						menu = false;
						scores = false;
						inv = false;
					default:
						break;
					}
				}
			}
		}

	}
}

void Game::Update()
{
	hud.Update(guy.health, guy.money, guy.attackDamage, guy.armour);
	if (!guy.isDead && !inv)
		guy.Update(&level, useKey);

	if (!turn)
	{
		turn = true;

		level.Update(&guy);
	}
}

void Game::Render()
{
	this->graphics.Clear();
	
	if (!menu && !scores && !inv) 
	{
		if (!guy.isDead)
		{
			// Add stuff to render
			level.Render(this->graphics.renderer, this->graphics.termSheet, guy.position, guy.lightSize);

			hud.Render(this->graphics.renderer, this->graphics.uiSheet);

			guy.Render(this->graphics.renderer, this->graphics.termSheet);
		}
		else
		{
			hud.RenderEndScreen(this->graphics.renderer, this->graphics.uiSheet, guy.monstersKilled, guy.money);
		}
	}
	else if (scores)
	{
		hud.RenderHighScore(this->graphics.renderer, this->graphics.uiSheet,  guy.highGold, guy.highMonster);
	}
	else if (inv)
	{
		hud.RenderInventory(this->graphics.renderer, this->graphics.uiSheet, guy.inventory);
	}
	else
	{
		hud.RenderMainMenu(this->graphics.renderer, this->graphics.uiSheet);
	}


	this->graphics.FlipBuffers();
}

void Game::Quit()
{
	this->graphics.Clean();
	SDL_Quit();
}