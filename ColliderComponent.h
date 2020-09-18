#pragma once

#include "StandardIncludes.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect Collider;
	string Tag;

	TransformComponent* Transform;

	ColliderComponent(string tag)
	{
		Tag = tag;
	}

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
		Collider.x = static_cast<int>(Transform->Position.x);
		Collider.y = static_cast<int>(Transform->Position.y);
		Collider.w = Transform->Width;
		Collider.h = Transform->Height;
	}
};

