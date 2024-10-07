#include "Scene.h"

namespace MomDra
{
	void Scene::Update() const noexcept
	{
		for (const auto& objVec : objects)
		{
			for (const auto& obj : objVec)
			{
				if (!obj->IsDead())
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

	void Scene::Render(const HDC& hdc) noexcept
	{
		for (auto& objVec : objects)
		{
			std::vector<std::unique_ptr<Object>>::iterator it{ objVec.begin() };

			for (; it != objVec.end();)
			{
				if (!(*it)->IsDead())
				{
					(*it)->Render(hdc);
					++it;
				}
				else
				{
					it = objVec.erase(it);
				}
			}
		}
	}
}
