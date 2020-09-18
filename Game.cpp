#include "Game.h"
#include "LoaderXML.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Layout.h"

Manager manager;
SDL_Renderer* Game::Renderer = nullptr;
SDL_Event Game::Event;
Layout* layout;

auto& pad(manager.AddEntity());
auto& wall(manager.AddEntity());

void Game::Init(const char* levelName, vector<string>* levelFileNames, int width, int height) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		gameWindow = SDL_CreateWindow(levelName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);
		Renderer = SDL_CreateRenderer(gameWindow, -1, 0);

		LoaderXML& loader = LoaderXML::GetLoaderInstance();
		for (string fileName : *levelFileNames)
		{
			loader.SetFileName(fileName.c_str());

			Level* level = new Level();
			if (loader.LoadLevelXML(level))
				GameLevels->push_back(level);
		}
			
		if (GameLevels->empty()) IsRunning = false;
		else IsRunning = true;
	}




	pad.AddComponent<TransformComponent>(((1200/ 2 - 100/2)-100),(600 - (15 * 2)), 15, 100);
	pad.AddComponent<SpriteComponent>("Assets/Breakout/pad.jpg");
	pad.AddComponent<KeyboardController>();
	pad.AddComponent<ColliderComponent>("pad");

	//maknuti komentare za testiranje kolizije
	/*wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20);
	wall.AddComponent<SpriteComponent>("Assets/Breakout/wall.jpg");   
	wall.AddComponent<ColliderComponent>("wall");*/

	layout = new Layout();
	layout->LoadLayout(GameLevels->front());
}

void Game::HandleEvents()
{
	SDL_PollEvent(&Event);

	switch (Event.type)
	{
		case SDL_QUIT:
			IsRunning = false;
			break;

		case SDL_WINDOWEVENT:
			switch (Event.window.event)
			{
				case SDL_WINDOWEVENT_CLOSE:   // exit main game window
					IsRunning = false;
					break;
				default:
					break;
			}
			break;

		default:
			break;
	}

}

void Game::Update()
{
	manager.Refresh();
	manager.Update();

	if (pad.GetComponent<TransformComponent>().Position.x < 0)
		pad.GetComponent<TransformComponent>().Position.x = 0;

	if (pad.GetComponent<TransformComponent>().Position.x > (1200 - pad.GetComponent<TransformComponent>().Width))
		pad.GetComponent<TransformComponent>().Position.x = 1200 - pad.GetComponent<TransformComponent>().Width;

	//maknuti komentare za testiranje kolizije
	/*if (Collision::Collided(pad.GetComponent<ColliderComponent>().Collider,
		wall.GetComponent<ColliderComponent>().Collider)) {
		cout << "kolizija";
		pad.GetComponent<TransformComponent>().Position.x = wall.GetComponent<TransformComponent>().Position.x + wall.GetComponent<TransformComponent>().Width+1;
	}*/

}

void Game::Render()
{
	SDL_RenderClear(Renderer);

	//Add all textures to render
	layout->DrawLayout();

	manager.Draw();
	SDL_RenderPresent(Renderer);
}

void Game::Clear()
{
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
}

