#include "GameManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

namespace MomDra
{
	void GameManager::Update()
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (time >= HURRY_UP_TIME)
		{
			HurryUp();
		}
	}

	void GameManager::HurryUp()
	{

	}
}