#include "Score.h"
#include "TimeManager.h"

namespace MomDra
{
	void Score::Update() noexcept
	{
		const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += deltaTime;

		if (time <= MOVE_TIME)
		{
			const Vector2& pos{ GetPos() };

			SetPos(pos - Vector2::UnitY * SPEED * deltaTime);
		}
		else
		{
			Destroy();
		}
	}
}