#include "SceneManager.h"
#include "SceneStart.h"

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
		Scenes[static_cast<int> (SceneType::START)] = std::make_unique<SceneStart>();
		Scenes[static_cast<int> (SceneType::START)]->SetName(L"StartScene");

		currScene = Scenes[static_cast<int> (SceneType::START)].get();
		currScene->Enter();
	}

	void SceneManager::ChangeScene(const SceneType& sceneType) noexcept
	{
		// ¾À ÁøÀÔ, ¾À ºüÁ® ³ª°¥ ¶§
		currScene->Exit();

		currScene = Scenes[static_cast<int>(sceneType)].get();
	}
}
