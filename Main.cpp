#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include "tinyxml2.h"
#include "Game.h"
#include "StandardIncludes.h"

//Kretanje: strelice lijevo i desno

int main(int argc, char* args[]) 
{
	Game& game = Game::GetGameInstance();

	vector<string> levelFileNames;
	levelFileNames.push_back("XML/Level1.xml");

	game.Init("Level1", &levelFileNames, 1200, 600);

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	int frameStart;
	int frameTimeDone;

	while (game.IsRunning) 
	{
		frameStart = SDL_GetTicks();

		game.HandleEvents();
		game.Update();
		game.Render();

		frameTimeDone = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTimeDone) 
		{
			SDL_Delay(frameDelay - frameTimeDone);
		}
	}

	game.Clear();

	system("pause");
	return 0;
}
