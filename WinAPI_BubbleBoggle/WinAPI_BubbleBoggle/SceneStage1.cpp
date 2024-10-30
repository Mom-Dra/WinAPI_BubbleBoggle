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
		
		const Vector2& resolution{ Core::GetInstance().GetResolution() };

		AddObject(std::make_unique<ImageObject>(resolution / 2.0f, resolution, L"\\texture\\Stage1.bmp", Layer::Default));

		AddObject(std::make_unique<Player>(PlayerSetting::SPAWN_POS, PlayerSetting::SIZE, Layer::Player));

		for (int i{ 0 }; i < NUM_OF_MONSTER; ++i)
		{
			AddObject(std::make_unique<Monster>(Vector2{ MonsterSetting::SPAWN_POS + Vector2::UnitX * 50 * i }, PlayerSetting::SIZE, Layer::Monster));
		}

		for (int i{ 0 }; i < PlayerSetting::LIFE - 1; ++i)
		{
			AddObject(std::make_unique<ImageObject>(Vector2{ 10.0f + 20.0f * i, resolution.Y - 20.0f }, Vector2{ 20.0f, 20.0f }, L"\\texture\\PlayerHP.bmp", Layer::UI));
		}
		
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

		Camera::GetInstance().SetLookAt(Core::GetInstance().GetResolution() / 2.0f);

		GameManager::GetInstance().SetNumOfMonster(NUM_OF_MONSTER);
		GameManager::GetInstance().SetPlayerLife(PlayerSetting::LIFE);

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