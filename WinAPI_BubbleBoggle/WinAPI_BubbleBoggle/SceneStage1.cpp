#include "SceneStage1.h"
#include "CollisionManager.h"
#include "ImageObject.h"
#include "Core.h"
#include "ResourceManager.h"

namespace MomDra
{
	void SceneStage1::Enter() noexcept
	{
		AddObject(std::make_unique<ImageObject>(Core::GetInstance().GetResolution() / 2.0f, Core::GetInstance().GetResolution(), L"\\texture\\Stage1.bmp", Layer::Default));
	}

	void SceneStage1::Update() noexcept
	{
		Scene::Update();
	}

	void SceneStage1::Exit() noexcept
	{
		DeleteAllObject();

		CollisionManager::GetInstance().Reset();
	}
}