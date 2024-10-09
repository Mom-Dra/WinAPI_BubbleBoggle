#include "SceneTool.h"
#include "KeyManager.h"
#include "Tile.h"
#include "Core.h"
#include "Camera.h"
#include "ResourceManager.h"

namespace MomDra
{
	void SceneTool::Update() const noexcept
	{
		Scene::Update();

		if (KeyManager::GetInstance().GetKeyDown(Key::ENTER))
		{
			EventManager::GetInstance().ChangeScene(SceneType::START);
		}
	}

	void SceneTool::Enter() noexcept
	{
		// 타일 생성
		for (int i{ 0 }; i < 5; ++i)
		{
			for (int j{ 0 }; j < 5; ++j)
			{
				AddObject(new Tile{ Vector2{i * Tile::TILE_SIZE, j * Tile::TILE_SIZE}, ResourceManager::GetInstance().LoadTexture(L"\\texture\\tileMap.bmp"), Layer::TILE });
			}
		}

		// Camera Look At 지정
		Vector2 resolution{ Core::GetInstance().GetResolution() };
		Camera::GetInstance().SetLookAt(resolution / 2.0f);
	}

	void SceneTool::Exit() noexcept
	{

	}
}
