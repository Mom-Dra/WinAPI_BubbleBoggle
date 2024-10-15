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

namespace MomDra
{	
	void SceneStart::Enter() noexcept
	{
		std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player.bmp");

		AddObject(std::make_unique<Player>(Vector2{ 640.0f, 384.0f }, Vector2{ 100.0f, 100.0f }, Layer::PLAYER));
		AddObject(std::make_unique<Monster>(Vector2{ 200.0f, 200.0f }, Vector2{ 100.0f, 100.0f }, Layer::MONSTER));

		// 몬스터에 AI 연결해야 함
		/*std::unique_ptr<AI> ai{ std::make_unique<AI>() };
		ai->AddState(std::make_unique<IdleState>());*/

		// 땅 생성
		AddObject(std::make_unique<Ground>(Vector2{ 300.0f, 300.0f }, Vector2{ 200.0f, 50.0f }, Layer::GROUND));

		// 충돌 지정
		CollisionManager::GetInstance().CheckLayer(Layer::PLAYER, Layer::MONSTER);
		CollisionManager::GetInstance().CheckLayer(Layer::MONSTER, Layer::PROJECTILE);
		CollisionManager::GetInstance().CheckLayer(Layer::PLAYER, Layer::GROUND);

		// Camera Look 지점
		Vector2 resolution{ Core::GetInstance().GetResolution() };
		Camera::GetInstance().SetLookAt(resolution / 2.0f);

		Start();
	}

	void SceneStart::Update() noexcept
	{
		Scene::Update();

		if (KeyManager::GetInstance().GetKeyDown(Key::LBUTTON))
		{
			const Vector2& mousePos{ KeyManager::GetInstance().GetMousePos() };
			const Vector2& lookAt{ Camera::GetInstance().GetRealPos(mousePos) };
			Camera::GetInstance().SetLookAt(lookAt);
		}

		/*if (KeyManager::GetInstance().GetKeyDown(Key::LSHIFT))
		{
			EventManager::GetInstance().ChangeScene(SceneType::TOOL);
		}*/
	}

	void SceneStart::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();
	}
}
