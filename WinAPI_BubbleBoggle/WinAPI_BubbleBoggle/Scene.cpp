#include "Scene.h"

namespace MomDra
{
	void Scene::Update() const noexcept
	{
		for (const auto& objVec : objects)
		{
			for (const auto& obj : objVec)
			{
				obj->Update();
			}
		}
	}

	void Scene::LateUpdate() const noexcept
	{
		for (const auto& objVec : objects)
		{
			for (const auto& obj : objVec)
			{
				obj->LateUpdate();
			}
		}
	}

	void Scene::Render(const HDC& hdc) const noexcept
	{
		for (const auto& objVec : objects)
		{
			for (const auto& obj : objVec)
			{
				obj->Render(hdc);
			}
		}
	}
}
