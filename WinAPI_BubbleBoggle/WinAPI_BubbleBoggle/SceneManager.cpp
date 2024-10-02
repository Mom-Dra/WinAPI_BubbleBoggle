#include "SceneManager.h"
#include "SceneStart.h"

SceneManager& SceneManager::GetInstance() noexcept
{
	static SceneManager instance;

	return instance;
}

void SceneManager::Initialize() noexcept
{
	// ¾À »ý¼º
	Scenes[static_cast<int> (SceneType::START)] = std::make_unique<SceneStart>();

	currScene = Scenes[static_cast<int> (SceneType::START)].get();
}
