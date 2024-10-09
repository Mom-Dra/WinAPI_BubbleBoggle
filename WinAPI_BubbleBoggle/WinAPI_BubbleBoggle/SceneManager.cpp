#include "SceneManager.h"
#include "SceneStart.h"
#include "SceneTool.h"

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
		Scenes[static_cast<int> (SceneType::TOOL)] = std::make_unique<SceneStart>(L"StartScene");
		Scenes[static_cast<int>(SceneType::TOOL)] = std::make_unique<SceneTool>(L"ToolScene");

		currScene = Scenes[static_cast<int> (SceneType::TOOL)].get();
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
