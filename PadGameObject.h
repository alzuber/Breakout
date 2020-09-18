#pragma once
#include "StandardIncludes.h"
#include "LoaderTexture.h"
#include "Components.h"

class PadGameObject : public Component
{
public:
	PadGameObject(){}
	PadGameObject(const char* textureFileName);
	~PadGameObject(){}

	/*void Update();
	void Render();*/

private:
	int xpos = 0;
	int ypos = 0;

	SDL_Texture* padTexture;
	SDL_Rect sourceR;
	SDL_Rect destinationR;

	LoaderTexture& loader = LoaderTexture::GetLoaderInstance();
};

