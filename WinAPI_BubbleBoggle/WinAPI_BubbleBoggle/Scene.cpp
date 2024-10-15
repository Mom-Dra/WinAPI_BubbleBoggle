#include "Scene.h"
#include "Tile.h"
#include "Vector2.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include <fstream>
#include <iostream>

using namespace CK;

namespace MomDra
{
	Scene::Scene(const std::wstring& name) noexcept : sceneName{ name }
	{

	}

	void Scene::Start() noexcept
	{
		for (const auto& objVec : objects)
		{
			for (const auto& obj : objVec)
			{
				obj->Start();
			}
		}
	}

	void Scene::Update() noexcept
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
		DeleteLayerObject(Layer::TILE);

		tileXY.first = xCount;
		tileXY.second = yCount;

		// 타일 생성
		for (unsigned int i{ 0 }; i < yCount; ++i)
		{
			for (unsigned int j{ 0 }; j < xCount; ++j)
			{
				AddObject(std::make_unique<Tile>(Vector2{ static_cast<int> (j * Tile::TILE_SIZE), static_cast<int>(i * Tile::TILE_SIZE) }, ResourceManager::GetInstance().LoadTexture(L"\\texture\\tileMap.bmp"), Layer::TILE));
			}
		}
	}

	void Scene::LoadTile(const std::wstring& relativePath)
	{
		std::wstring path{ PathManager::GetContentPath() };
		path.append(relativePath);

		std::wifstream wIn{ path };

		if (!wIn.is_open())
		{
			std::wcout << "Can Not Open File Path: " << path << std::endl;
		}

		unsigned int xCount;
		unsigned int yCount;

		// 타일 개수 읽어오기
		wIn >> xCount >> yCount;

		CreateTile(xCount, yCount);

		const std::vector<std::unique_ptr<Object>>& tiles{ GetLayerObject(Layer::TILE) };

		// 각 타일 데이터 읽어오기
		for (const auto& tile : tiles)
		{
			Tile* tilePtr{ dynamic_cast<Tile*>(tile.get()) };
			tilePtr->LoadFile(wIn);
		}

		std::cout << "Load File Complete - xCount: " << xCount << ", yCount: " << yCount << std::endl;
	}
}
