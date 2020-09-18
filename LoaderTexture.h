#pragma once
#include "StandardIncludes.h"

class LoaderTexture
{
public:
	LoaderTexture(const LoaderTexture&) = delete;

	static LoaderTexture& GetLoaderInstance()
	{
		static unique_ptr<LoaderTexture> loaderTexture(new LoaderTexture());
		return *loaderTexture;
	}

	~LoaderTexture() {}

	SDL_Texture* LoadTexture(const char* fileName);
	void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);

private:
	LoaderTexture(){}
};

