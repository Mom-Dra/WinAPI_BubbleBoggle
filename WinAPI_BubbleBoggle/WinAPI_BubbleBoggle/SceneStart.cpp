#include "SceneStart.h"
#include "Player.h"
#include "Monster.h"
#include "Texture.h"
#include "PathManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Core.h"
#include "Camera.h"
#include "IdleState.h"
#include "Ground.h"
#include "ResourceManager.h"

namespace MomDra
{	
	void SceneStart::Enter() noexcept
	{
		LoadTileData();
		//LoadTile(L"\\tile\\test2.tile");
		LoadGround();

		std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player.bmp");

		AddObject(std::make_unique<Player>(Vector2{ 640.0f, 384.0f }, Vector2{ 40.0f, 40.0f }, Layer::PLAYER));
		AddObject(std::make_unique<Monster>(Vector2{ 200.0f, 200.0f }, Vector2{ 40.0f, 40.0f }, Layer::MONSTER));

		// 땅 생성
		AddObject(std::make_unique<Ground>(Vector2{ 300.0f, 300.0f }, Vector2{ 200.0f, 50.0f }, Layer::GROUND));

		// 충돌 지정
		CollisionManager::GetInstance().CheckLayer(Layer::PLAYER, Layer::MONSTER);
		CollisionManager::GetInstance().CheckLayer(Layer::MONSTER, Layer::PROJECTILE);
		CollisionManager::GetInstance().CheckLayer(Layer::PLAYER, Layer::GROUND);
		CollisionManager::GetInstance().CheckLayer(Layer::MONSTER, Layer::GROUND);
		CollisionManager::GetInstance().CheckLayer(Layer::ITEM, Layer::GROUND);
		CollisionManager::GetInstance().CheckLayer(Layer::ITEM, Layer::PLAYER);
		CollisionManager::GetInstance().CheckLayer(Layer::PLAYER, Layer::WALL);
		CollisionManager::GetInstance().CheckLayer(Layer::PROJECTILE, Layer::WALL);
		CollisionManager::GetInstance().CheckLayer(Layer::MONSTER, Layer::WALL);
		CollisionManager::GetInstance().CheckLayer(Layer::PLAYER, Layer::PROJECTILE);
		CollisionManager::GetInstance().CheckLayer(Layer::PROJECTILE, Layer::PROJECTILE);

		// Camera Look 지점
		Vector2 resolution{ Core::GetInstance().GetResolution() };
		Camera::GetInstance().SetLookAt(resolution / 2.0f);

		Start();
	}

	void SceneStart::Update() noexcept
	{
		Scene::Update();
	}

	void SceneStart::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();
	}
}
