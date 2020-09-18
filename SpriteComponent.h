#pragma once

#include "Components.h"
#include "StandardIncludes.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* fileName)
	{
		texture = loader.LoadTexture(fileName);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void Init() override
	{
		if (!Entity->HasComponent<TransformComponent>())
		{
			Entity->AddComponent<TransformComponent>();
		}

		transform = &Entity->GetComponent<TransformComponent>();

		sourceR.x = sourceR.y = 0;
		sourceR.w = transform->Width;
		sourceR.h = transform->Height;
		destinationR.w = transform->Width;
		destinationR.h = transform->Height;
	}

	void Update() override
	{
		destinationR.x = (int)transform->Position.x;
		destinationR.y = (int)transform->Position.y;
	}

	void Draw() override
	{
		loader.Draw(texture, sourceR, destinationR);
	}

private:
	TransformComponent* transform;
	SDL_Texture *texture;
	SDL_Rect sourceR, destinationR;

	LoaderTexture& loader = LoaderTexture::GetLoaderInstance();
};
