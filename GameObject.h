#pragma once
#include "Component.h"
class GameObject
{
public:

	GameObject()
	{
	}

	~GameObject()
	{
		for (Component* pComponent : mComponents)
		{
			pComponent->Destroy();

			delete pComponent;
		}
	}

	void Initialize()
	{
		for (Component* pComponent : mComponents)
		{
			pComponent->Initialize();
		}
	}

	void AddComponent(Component* pComponent)
	{
		mComponents.push_back(pComponent);
	}

	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}

		return nullptr;
	}

private:
	std::vector<Component*> mComponents;

};