#include "Projectile.h"
#include "TimeManager.h"
#include <coroutine>

namespace MomDra
{
	void ProjectileAttackState::Update(Projectile& projectile)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += timeManager.GetDeltaTime();

		if (time < moveTime)
		{
			const Vector2& pos{ projectile.GetPos() };
			const Vector2& initialDir{ projectile.GetInitialDir() };

			projectile.SetPos(pos + initialDir * speed * deltaTime);
		}
		else
		{
			projectile.ChangeToMovingState();
		}
	}

	inline void ProjectileAttackState::OnCollisionEnter(Projectile& projectile, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Monster:
			projectile.Destroy();
			break;
		}
	}

	void ProjectileMovingState::Update(Projectile& projectile)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += deltaTime;

		if (time < moveTime)
		{
			const Vector2& pos{ projectile.GetPos() };
			projectile.SetPos(pos + -Vector2::UnitY * speed * deltaTime);
		}
		else
		{
			projectile.Destroy();
		}
	}
}
