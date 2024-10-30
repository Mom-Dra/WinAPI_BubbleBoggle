#include "SceneStage1.h"
#include "CollisionManager.h"
#include "ImageObject.h"
#include "Core.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Monster.h"
#include "Camera.h"
#include "GameManager.h"

namespace MomDra
{
	void SceneStage1::Enter() noexcept
	{
		LoadTile(L"\\tile\\Stage1.tile");
		LoadGround();

		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Core::GetInstance().GetResolution(), L"\\texture\\Stage1.bmp", Layer::DEFAULT));

		AddObject(std::make_unique<Player>(Vector2{ 640.0f, 384.0f }, Vector2{ 40.0f, 40.0f }, Layer::PLAYER));

		for (int i{ 0 }; i < NUM_OF_MONSTER; ++i)
		{
			AddObject(std::make_unique<Monster>(Vector2{ 200.0f, 200.0f }, Vector2{ 40.0f, 40.0f }, Layer::MONSTER));
		}
		
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

		Camera::GetInstance().SetLookAt(Core::GetInstance().GetResolution() / 2.0f);

		GameManager::GetInstance().SetNumOfMonster(NUM_OF_MONSTER);
		//GameManager::GetInstance().SetPlayerLife();

		Start();
	}

	void SceneStage1::Update() noexcept
	{
		Scene::Update();
	}

	void SceneStage1::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();
	}
}