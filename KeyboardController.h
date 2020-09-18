#pragma once

#include "Game.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* Transform;

	void Init() override
	{
		if (!Entity->HasComponent<TransformComponent>())
		{
			Entity->AddComponent<TransformComponent>();
		}

		Transform = &Entity->GetComponent<TransformComponent>();
	}

	void Update() override
	{
		if (Game::Event.type == SDL_KEYDOWN) 
		{
			switch (Game::Event.key.keysym.sym)
			{
			case SDLK_LEFT:
				Transform->Velocity.x = -1;
				break;

			case SDLK_RIGHT:
				Transform->Velocity.x = 1;
				break;

			default:
				break;
			}
		}

		if(Game::Event.type == SDL_KEYUP)
		{
			switch (Game::Event.key.keysym.sym)
			{
			case SDLK_LEFT:
				Transform->Velocity.x = 0;
				break;

			case SDLK_RIGHT:
				Transform->Velocity.x = 0;
				break;

			default:
				break;
			}
		}

	}
};

