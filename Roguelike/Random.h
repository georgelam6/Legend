#pragma once

#include <ctime>
#include <cstdlib>

struct Random
{
	static int randint(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}
};