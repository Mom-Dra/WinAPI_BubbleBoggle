#include "Scene.h"
#include "TileRectangle.h"
#include "Vector2.h"
#include "ResourceManager.h"
#include "PathManager.h"
#include <fstream>
#include <iostream>
#include "Ground.h"
#include "CommandManager.h"
#include <commdlg.h>
#include "Core.h"

#ifdef max
#undef max
#endif // min


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
		DeleteLayerObject(Layer::Tile);

		tileXY.first = xCount;
		tileXY.second = yCount;

		// 타일 생성
		for (unsigned int i{ 0 }; i < yCount; ++i)
		{
			for (unsigned int j{ 0 }; j < xCount; ++j)
			{
				AddObject(std::make_unique<TileRectangle>(Vector2{ static_cast<int> (j * TileRectangle::TILE_SIZE_X), static_cast<int>(i * TileRectangle::TILE_SIZE_Y) }, Vector2{ TileRectangle::TILE_SIZE_X, TileRectangle::TILE_SIZE_Y }, Layer::Tile));
			}
		}
	}

	void Scene::CreateTileAtMousePos(unsigned int xPos, unsigned int yPos)
	{
		Vector2 pos{ static_cast<float>(xPos), static_cast<float>(yPos) };
		TileRectangle::AddTile(pos, TileRectangle::TILE_SIZE);

		AddObject(std::make_unique<TileRectangle>(TileRectangle::GetRealTilePos(xPos, yPos), TileRectangle::TILE_SIZE, Layer::Tile));
	}

	void Scene::CreateTileAtMouseDrag(unsigned int startXPos, unsigned int startYPos, unsigned int endXPos, unsigned int endYPos)
	{
		Vector2 pos{ static_cast<float> ((startXPos + endXPos) / 2.0f), static_cast<float> ((startYPos + endYPos) / 2.0f) };

		float scaleX{ static_cast<float>((endXPos - startXPos + 1) * TileRectangle::TILE_SIZE_X) };
		float scaleY{ static_cast<float>((endYPos - startYPos + 1) * TileRectangle::TILE_SIZE_Y) };

		Vector2 scale{ scaleX, scaleY };

		TileRectangle::AddTile(pos, scale);

		//AddObject(std::make_unique<TileRectangle>(TileRectangle::GetRealTilePos(pos), scale, Layer::TILE));

		CommandManager::Execute(std::make_unique<AddTileCommand>(this, TileRectangle::TileInfo{ pos, scale }));
	}

	void Scene::LoadTile(const std::wstring& relativePath)
	{
		std::wstring path{ PathManager::GetContentPath() };
		path.append(relativePath);

		std::wifstream in{ path, std::ios::binary };

		if (!in.is_open())
		{
			std::wcout << "Can Not Open File Path: " << path << std::endl;
			return;
		}

		//unsigned int xCount;
		//unsigned int yCount;

		//// 타일 개수 읽어오기
		//in >> xCount >> yCount;

		//CreateTile(xCount, yCount);

		//const std::vector<std::unique_ptr<Object>>& tiles{ GetLayerObject(Layer::TILE) };

		// 각 타일 데이터 읽어오기
		/*for (const auto& tile : tiles)
		{
			TileRectangle* tilePtr{ dynamic_cast<TileRectangle*>(tile.get()) };
			tilePtr->LoadFile(in);
		}*/

		TileRectangle::LoadFile(in);
		const TileRectangle::TileVec& tileVec{ TileRectangle::GetTileVec() };

		for (const TileRectangle::TileInfo& tileInfo : tileVec)
		{
			AddObject(std::make_unique<TileRectangle>(TileRectangle::GetRealTilePos(tileInfo.pos), tileInfo.scale, Layer::Tile));
			std::cout << "Add Tile: " << tileInfo << std::endl;
		}

		std::wcout << "Load Tile Complete: " << relativePath << std::endl;
	}

	void Scene::LoadGround()
	{
		const TileRectangle::TileVec& tileVec{ TileRectangle::GetTileVec() };

		for (const TileRectangle::TileInfo& tileInfo : tileVec)
		{
			AddObject(std::make_unique<Ground>(TileRectangle::GetRealTilePos(tileInfo.pos), tileInfo.scale, Layer::Ground));
		}
	}

	void Scene::LoadTileData()
	{
		OPENFILENAME ofn = {};

		std::wstring name;
		name.resize(256);

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = Core::GetInstance().GetMainHwnd();
		ofn.lpstrFile = &name[0];
		ofn.nMaxFile = static_cast<DWORD>(name.size());
		ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
		ofn.nFilterIndex = 0;
		ofn.lpstrFileTitle = nullptr;
		ofn.nMaxFileTitle = 0;

		std::wstring tilePath{ PathManager::GetContentPath() };
		tilePath.append(L"\\tile");

		ofn.lpstrInitialDir = tilePath.data();
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		// Modal 방식
		// 그 해당 창이 포커싱이 되고, 나머지는 동작하지 않는다
		if (GetOpenFileName(&ofn))
		{
			std::wstring relativePath{ PathManager::GetRelativePath(name) };
			LoadTile(relativePath);

			std::wcout << "Load File Complete: " << name << std::endl;
		}
	}
}
