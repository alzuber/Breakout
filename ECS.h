#pragma once
#include "StandardIncludes.h"
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr size_t maxComponents = 32;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component
{
public:
	Entity* Entity;
	
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component(){}

};

class Entity
{
public:

	void Update()
	{
		for (auto& component : components) component->Update();
	}

	void Draw()
	{
		for (auto& component : components) component->Draw();
	}

	bool IsActive() const { return active; }
	void Destroy() { active = false; }

	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* component(new T(forward<TArgs>(mArgs)...));
		component->Entity = this;
		unique_ptr<Component> compPtr{ component };
		components.emplace_back(move(compPtr));

		componentArray[GetComponentTypeID<T>()] = component;
		componentBitSet[GetComponentTypeID<T>()] = true;
		
		component->Init();
		return *component;
	}

	template<typename T> T& GetComponent() const
	{
		auto pointer(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(pointer);
	}

private:
	bool active = true;
	vector<unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};

class Manager
{
public:
	void Update()
	{
		for (auto& entity : entities) entity->Update();
	}

	void Draw()
	{
		for (auto& entity : entities) entity->Draw();
	}

	void Refresh() //remve inactive entities
	{
		entities.erase(remove_if(begin(entities), end(entities),
			[](const unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			end(entities));
	}

	Entity& AddEntity()
	{
		Entity* entity = new Entity();
		unique_ptr<Entity> pointer{ entity };
		entities.emplace_back(move(pointer));
		return *entity;
	}

private:
	vector<unique_ptr<Entity>> entities;
};


