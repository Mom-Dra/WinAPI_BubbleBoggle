#include "SceneIntro.h"
#include "ImageObject.h"
#include "Core.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "BackGround.h"

namespace MomDra
{
	void SceneIntro::Enter() noexcept
	{
		AddObject(std::make_unique<BackGround>());
		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Vector2::One * 200.0f, L"\\texture\\Title.bmp", Layer::Default));

		// Sound
		ResourceManager::GetInstance().LoadSound(L"\\sound\\Main.wav")->PlayToBGM(true);
	}

	void SceneIntro::Update() noexcept
	{
		Scene::Update();

		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (time >= INTRO_TIME)
			EventManager::GetInstance().ChangeScene(SceneType::STAGE_1);
	}

	void SceneIntro::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();
	}
}