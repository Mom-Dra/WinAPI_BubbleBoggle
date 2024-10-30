#include "Pon.h"
#include "TimeManager.h"
#include "Projectile.h"

namespace MomDra
{
	Pon::Pon(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : Object{ pos, scale, layer }
	{
		CreateAnimator();

		Animator* animator{ GetAnimator() };

		animator->LoadAnimation(L"\\animation\\Projectile_Pon.anim");
		animator->Play(ProjectileSetting::PROJECTILE_PON, true);
	}

	void Pon::Update() noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if(time > DURATION)
		{
			Destroy();
		}
	}
}