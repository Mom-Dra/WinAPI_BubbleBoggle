#include "SceneTool.h"
#include "KeyManager.h"

namespace MomDra
{
	void SceneTool::Update() const noexcept
	{
		if (KeyManager::GetInstance().GetKeyDown(Key::ENTER))
		{
			EventManager::GetInstance().ChangeScene(SceneType::START);
		}
	}

	void SceneTool::Enter() noexcept
	{

	}

	void SceneTool::Exit() noexcept
	{

	}
}
