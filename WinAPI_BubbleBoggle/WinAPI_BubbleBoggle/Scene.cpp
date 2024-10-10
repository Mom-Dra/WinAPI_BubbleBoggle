#include "Scene.h"
#include "Tile.h"
#include "Vector2.h"
#include "ResourceManager.h"

using namespace CK;

namespace MomDra
{
	Scene::Scene(const std::wstring& name) noexcept : sceneName{ name }
	{

	}

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

	void Scene::CreateTile(unsigned int xCount, unsigned int yCount)
	{
		tileXY.first = xCount;
		tileXY.second = yCount;

		// 타일 생성
		for (unsigned int i{ 0 }; i < yCount; ++i)
		{
			for (unsigned int j{ 0 }; j < xCount; ++j)
			{
				AddObject(new Tile{ Vector2{static_cast<int> (j * Tile::TILE_SIZE), static_cast<int>(i * Tile::TILE_SIZE)}, ResourceManager::GetInstance().LoadTexture(L"\\texture\\tileMap.bmp"), Layer::TILE });
			}
		}
	}
}
