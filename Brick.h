#include "StandardIncludes.h"
#pragma once

class Brick
{
public:
	Brick(){}
	Brick(string id, string texture, int hitPoints, string hitSound, string breakSound, int breakScore)
	{
		Id = id;
		Texture = texture;
		HitPoints = hitPoints;
		HitSound = hitSound;
		BreakSound = breakSound;
		BreakScore = breakScore;
	}
	~Brick(){}

	string Id = "";
	string Texture = "";
	int HitPoints = 0;
	string HitSound = "";
	string BreakSound = "";
	int BreakScore = 0;
};

