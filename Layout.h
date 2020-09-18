#pragma once
#include "Game.h"
#include "StandardIncludes.h"

class Layout
{
public:
	Layout() 
	{
		asignTextures();
		src.x = src.y = 0;

		src.h = 128;
		src.w = 384;

		dest.h = 25;
		dest.w = 50;

		dest.x = dest.y = 0;
	}

	~Layout(){}

	void LoadLayout(Level* level);
	void DrawLayout();

private:

	vector<vector<int>> layout;

	SDL_Rect src, dest;
	SDL_Texture* soft;
	SDL_Texture* medium;
	SDL_Texture* hard;
	SDL_Texture* impenetrable;

	LoaderTexture& loader = LoaderTexture::GetLoaderInstance();

	void asignTextures();

};

