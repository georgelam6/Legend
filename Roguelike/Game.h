#pragma once

#include "Graphics.h"

class Game
{
public:
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Quit();

	bool running;
private:
	Graphics graphics;
};

