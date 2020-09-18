#include "LoaderTexture.h"
#include "Game.h"

SDL_Texture*  LoaderTexture::LoadTexture(const char* fileName)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	cout << IMG_GetError() << endl;
	SDL_Texture* image = SDL_CreateTextureFromSurface(Game::Renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return image;
}

void LoaderTexture::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::Renderer, texture, &src, &dest);
}
