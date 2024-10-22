#include "Projectile.h"
#include "TimeManager.h"
#include "Monster.h"

namespace MomDra
{
	void ProjectileAttackState::Enter(Projectile& projectile) noexcept
	{

	}

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
		{
			Monster* monster{ dynamic_cast<Monster*>(otherObject) };

			projectile.Destroy();
		}
			break;
		}
	}

	void ProjectileMovingState::Enter(Projectile& projectile) noexcept
	{

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
