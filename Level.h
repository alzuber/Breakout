#include "StandardIncludes.h"
#include "Brick.h"
#pragma once

using namespace std;

class Level
{
public:
	Level()
	{
		BrickTypes = new vector<Brick>();
		Bricks = new vector<string>();
	}
	~Level()
	{
		delete BrickTypes;
		delete Bricks;
	}

	int RowCount = 0;
	int ColumnCount = 0;
	int RowSpacing = 0;
	int ColumnSpacing = 0;
	string BackgroundTexture = "";

	vector<Brick>* BrickTypes;
	vector<string>* Bricks;
};

