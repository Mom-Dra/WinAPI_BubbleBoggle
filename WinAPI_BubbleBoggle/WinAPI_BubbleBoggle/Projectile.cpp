#include "Projectile.h"
#include "TimeManager.h"
#include "Monster.h"
#include "Core.h"
#include "Pon.h"

namespace MomDra
{
	Projectile::Projectile(const Vector2& pos, const Vector2& scale, const Vector2& initialDir, const Layer& layer) : Object{ pos, scale, layer }, initialDir{ initialDir }, isExplode{ false }
	{
		CreateCollider(scale);
		CreateAnimator();
		CreateRigidbody();
		GetRigidBody()->SetGravity(false);

		Animator* animator{ GetAnimator() };

		animator->LoadAnimation(L"\\animation\\Projectile_Attack.anim");
		animator->LoadAnimation(L"\\animation\\Projectile_Move_1.anim");
		animator->LoadAnimation(L"\\animation\\Projectile_Move_2.anim");
		animator->LoadAnimation(L"\\animation\\Projectile_Move_3.anim");

		ChangeToAttackState();
	}

	inline void Projectile::Explode() noexcept
	{
		if (isExplode) return;

		isExplode = true;

		for (const auto& projectile : collidingProjectiles)
			projectile->Explode();

		EventManager::GetInstance().Instantiate(new Pon(GetPos(), GetScale(), Layer::Default));
		Destroy();
	}

	inline void Projectile::ExplodeSelf() noexcept
	{
		if (isExplode) return;

		isExplode = true;

		EventManager::GetInstance().Instantiate(new Pon(GetPos(), GetScale(), Layer::Default));
		Destroy();
	}

	void ProjectileAttackState::Enter(Projectile& projectile) noexcept
	{
		projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_ATTACK, true);
	}

	void ProjectileAttackState::Update(Projectile& projectile)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += deltaTime;

		if (time < ProjectileSetting::ATTACK_MOVE_TIME)
		{
			const Vector2& pos{ projectile.GetPos() };
			const Vector2& initialDir{ projectile.GetInitialDir() };

			projectile.SetPos(pos + initialDir * ProjectileSetting::ATTACK_SPEED * deltaTime);
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
		projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_MOVE_1, true);
	}

	void ProjectileMovingState::Update(Projectile& projectile)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		const Vector2& pos{ projectile.GetPos() };
		projectile.SetPos(pos + -Vector2::UnitY * ProjectileSetting::MOVE_SPEED * timeManager.GetDeltaTime());
	}

	inline void ProjectileMovingState::OnCollisionEnter(Projectile& projectile, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ other->GetObj()->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Wall:
			projectile.ChangeToHighReachedState();
			break;

		case Layer::Projectile:
		{
			Projectile* otherProjectile{ dynamic_cast<Projectile*>(otherObject) };
			projectile.AddCollidingProjectile(otherProjectile);
		}
		break;

		case Layer::Player:
			projectile.Explode();
			break;
		}
	}

	void ProjectileMovingState::OnCollisionStay(Projectile& projectile, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ other->GetObj()->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Projectile:
		{
			Projectile* otherProjectile{ dynamic_cast<Projectile*>(otherObject) };
			projectile.AddCollidingProjectile(otherProjectile);
		}
			break;
		}
	}

	void ProjectileMovingState::OnCollisionExit(Projectile& projectile, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ other->GetObj()->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Projectile:
		{
			Projectile* otherProjectile{ dynamic_cast<Projectile*>(otherObject) };
			projectile.RemoveCollidingProjectile(otherProjectile);
		}
		break;
		}
	}

	void ProjectileHighReachedState::Enter(Projectile& projectile) noexcept
	{
		targetYpos = projectile.GetPos().Y;
	}

	void ProjectileHighReachedState::Update(Projectile& projectile)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += deltaTime;

		if (time >= ProjectileSetting::PROJECTILE_1_TIME + ProjectileSetting::PROJECTILE_2_TIME + ProjectileSetting::PROJECTILE_3_TIME)
		{
			projectile.ExplodeSelf();
		}
		else if (time >= ProjectileSetting::PROJECTILE_1_TIME + ProjectileSetting::PROJECTILE_2_TIME)
		{
			projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_MOVE_3, true);
		}
		else if (time >= ProjectileSetting::PROJECTILE_1_TIME)
		{
			projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_MOVE_2, true);
		}

		static float halfWidth{ Core::WINDOW_WIDTH / 2 };
		Vector2 targetPos{ halfWidth, targetYpos };
		const Vector2& pos{ projectile.GetPos() };

		projectile.SetPos(pos + (targetPos - pos).GetNormalize() * MonsterSetting::HITTED_SPEED * deltaTime);
	}

	void ProjectileHighReachedState::OnCollisionEnter(Projectile& projectile, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };

		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Projectile:
		{
			RigidBody* otherRigid{ otherObject->GetRigidBody() };
			Vector2 dir{ otherObject->GetPos() - projectile.GetPos() };

			otherRigid->AddVelocity(dir.GetNormalize() * ProjectileSetting::PROJECTILE_POWER);
		}
		break;
		
		case Layer::Player:
			projectile.Explode();
			break;
		}
	}
}
