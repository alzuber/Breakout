#pragma once
#include "StandardIncludes.h"

class Collision
{
public:
	static bool Collided(const SDL_Rect& recA, const SDL_Rect& recB);
};
