#include "SceneWin.h"
#include "BackGround.h"
#include "ImageObject.h"
#include "Core.h"
#include "ResourceManager.h"

namespace MomDra
{
	void SceneWin::Enter() noexcept
	{
		AddObject(std::make_unique<BackGround>());
		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Vector2::One * 200.0f, L"\\texture\\Title.bmp", Layer::Default));

		ResourceManager::GetInstance().LoadSound(L"\\sound\\GameWin.wav")->PlayToBGM(false);
	}

	void SceneWin::Update() noexcept
	{
		Scene::Update();

		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (time >= GAME_WIN_BGM_LENGTH)
		{
			EventManager::GetInstance().ChangeScene(SceneType::Intro);
		}
	}
}