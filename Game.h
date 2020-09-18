#pragma once

#include "StandardIncludes.h"
#include "Level.h"
#include "LoaderTexture.h"

using namespace std;

class Game
{
public:
	Game(const Game&) = delete;

	static Game& GetGameInstance() 
	{
		static unique_ptr<Game> gameInstance(new Game());
		return *gameInstance;
	}

	~Game(){}

	void Init(const char* levelName, vector<string>* levelFileNames, int width, int height);
	void HandleEvents();
	void Update();
	void Render();
	void Clear();

	bool IsRunning;
	vector<Level*>* GameLevels;

	static SDL_Renderer* Renderer;
	static SDL_Event Event;

private:
	Game()
	{
		GameLevels = new vector<Level*>();
		IsRunning = false;
	}

	SDL_Window* gameWindow = NULL;
	LoaderTexture& loader = LoaderTexture::GetLoaderInstance();

};

