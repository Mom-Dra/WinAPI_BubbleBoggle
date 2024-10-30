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

		AddObject(std::make_unique<Player>(Vector2{ 640.0f, 384.0f }, Vector2{ 40.0f, 40.0f }, Layer::Player));
		AddObject(std::make_unique<Monster>(Vector2{ 200.0f, 200.0f }, Vector2{ 40.0f, 40.0f }, Layer::Monster));

		// 땅 생성
		AddObject(std::make_unique<Ground>(Vector2{ 300.0f, 300.0f }, Vector2{ 200.0f, 50.0f }, Layer::Ground));

		// 충돌 지정
		CollisionManager::GetInstance().CheckLayer(Layer::Player, Layer::Monster);
		CollisionManager::GetInstance().CheckLayer(Layer::Monster, Layer::Projectile);
		CollisionManager::GetInstance().CheckLayer(Layer::Player, Layer::Ground);
		CollisionManager::GetInstance().CheckLayer(Layer::Monster, Layer::Ground);
		CollisionManager::GetInstance().CheckLayer(Layer::Item, Layer::Ground);
		CollisionManager::GetInstance().CheckLayer(Layer::Item, Layer::Player);
		CollisionManager::GetInstance().CheckLayer(Layer::Player, Layer::Wall);
		CollisionManager::GetInstance().CheckLayer(Layer::Projectile, Layer::Wall);
		CollisionManager::GetInstance().CheckLayer(Layer::Monster, Layer::Wall);
		CollisionManager::GetInstance().CheckLayer(Layer::Player, Layer::Projectile);
		CollisionManager::GetInstance().CheckLayer(Layer::Projectile, Layer::Projectile);

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
