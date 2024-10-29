#include "SceneManager.h"
#include "SceneStart.h"
#include "SceneTool.h"
#include "SceneStage1.h"
#include "SceneIntro.h"

namespace MomDra
{
	SceneManager& SceneManager::GetInstance() noexcept
	{
		static SceneManager instance;

		return instance;
	}

	void SceneManager::Initialize() noexcept
	{
		// ¾À »ý¼º
		Scenes[static_cast<int> (SceneType::START)] = std::make_unique<SceneStart>(L"StartScene");
		Scenes[static_cast<int>(SceneType::TOOL)] = std::make_unique<SceneTool>(L"ToolScene");
		Scenes[static_cast<int>(SceneType::Intro)] = std::make_unique<SceneIntro>(L"IntroScene");
		Scenes[static_cast<int>(SceneType::STAGE_1)] = std::make_unique<SceneStage1>(L"Stage1");

		currScene = Scenes[static_cast<int> (SceneType::Intro)].get();
		currScene->Enter();
	}

	void SceneManager::ChangeScene(const SceneType& sceneType) noexcept
	{
		// ¾À ÁøÀÔ, ¾À ºüÁ® ³ª°¥ ¶§
		currScene->Exit();

		currScene = Scenes[static_cast<int>(sceneType)].get();

		currScene->Enter();
	}
}
