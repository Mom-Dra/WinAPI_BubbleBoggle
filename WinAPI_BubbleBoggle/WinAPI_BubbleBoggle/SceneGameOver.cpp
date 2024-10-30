#include "SceneGameOver.h"
#include "BackGround.h"
#include "ImageObject.h"
#include "Core.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "SceneManager.h"

namespace MomDra
{
	void SceneGameOver::Enter() noexcept
	{
		AddObject(std::make_unique<BackGround>());
		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Vector2::One * 200.0f, L"\\texture\\Title.bmp", Layer::DEFAULT));

		// Sound
		ResourceManager::GetInstance().LoadSound(L"\\sound\\GameOver.wav")->PlayToBGM(false);
	}

	void SceneGameOver::Update() noexcept
	{
		Scene::Update();

		const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (time >= GAME_OVER_BGM_LENGTH)
		{
			EventManager::GetInstance().ChangeScene(SceneType::INTRO);
		}
	}

	void SceneGameOver::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();

		time = 0.0f;
	}
}
