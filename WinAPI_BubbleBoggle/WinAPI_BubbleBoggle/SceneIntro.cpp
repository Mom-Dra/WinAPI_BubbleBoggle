#include "SceneIntro.h"
#include "ImageObject.h"
#include "Core.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "BackGround.h"
#include "KeyManager.h"

namespace MomDra
{
	void SceneIntro::Enter() noexcept
	{
		AddObject(std::make_unique<BackGround>());
		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Vector2::One * 200.0f, L"\\texture\\Title.bmp", Layer::Default));
	}

	void SceneIntro::Update() noexcept
	{
		Scene::Update();

		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		static const KeyManager& keyManager{ KeyManager::GetInstance() };

		if (!keyPressed)
		{
			if (keyManager.GetKeyDown(Key::A) || keyManager.GetKeyDown(Key::S) || keyManager.GetKeyDown(Key::SPACE))
			{
				ResourceManager::GetInstance().LoadSound(L"\\sound\\Main.wav")->PlayToBGM(true);
				keyPressed = true;
			}
			else return;
		}

		time += timeManager.GetDeltaTime();

		if (time >= INTRO_TIME)
			EventManager::GetInstance().ChangeScene(SceneType::Stage1);
	}

	void SceneIntro::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();

		time = 0.0f;
		keyPressed = false;
	}
}