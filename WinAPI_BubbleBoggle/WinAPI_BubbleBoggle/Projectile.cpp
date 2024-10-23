#include "Projectile.h"
#include "TimeManager.h"
#include "Monster.h"

namespace MomDra
{
	Projectile::Projectile(const Vector2& pos, const Vector2& scale, const Vector2& initialDir, const Layer& layer) : Object{ pos, scale, layer }, initialDir{ initialDir }
	{
		CreateCollider(scale);
		CreateAnimator();

		std::initializer_list<Vector2> leftTops{ Vector2{4.0f, 6.0f}, Vector2{20.0f, 5.0f }, Vector2{37.0f, 3.0f}, Vector2{55.0f, 2.0f}, Vector2{72.0f, 3.0f}, Vector2{90.0f, 2.0f} };
		std::initializer_list<Vector2> sliceSizes{ Vector2{5.0f, 7.0f}, Vector2{9.0f, 9.0f }, Vector2{11.0f, 13.0f}, Vector2{11.0f, 15.0f}, Vector2{13.0f, 13.0f}, Vector2{13.0f, 15.0f} };

		Animator* animator{ GetAnimator() };
		animator->CreateAnimation(L"Projectile_Attack", ResourceManager::GetInstance().LoadTexture(L"\\texture\\Projectile.bmp"), leftTops, sliceSizes, 0.05f, 6);
		animator->Play(L"Projectile_Attack", true);
		animator->FindAnimation(L"Projectile_Attack")->Save(L"\\texture\\animation\\Projectile_Attack.anim");

		std::initializer_list<Vector2> leftTops2{ Vector2{1.0f, 24.0f}, Vector2{19.0f, 25.0f }, Vector2{38.0f, 24.0f} };
		std::initializer_list<Vector2> sliceSizes2{ Vector2{14.0f, 16.0f}, Vector2{14.0f, 14.0f }, Vector2{12.0f, 16.0f} };

		animator->CreateAnimation(L"Projectile_Move_1", ResourceManager::GetInstance().LoadTexture(L"\\texture\\Projectile.bmp"), leftTops2, sliceSizes2, 0.1f, 3);
		animator->Play(L"Projectile_Move_1", true);
		animator->FindAnimation(L"Projectile_Move_1")->Save(L"\\texture\\animation\\Projectile_Move_1.anim");



		std::initializer_list<Vector2> leftTops3{ Vector2{0.0f, 0.0f}, Vector2{18.0f, 1.0f }, Vector2{37.0f, 0.0f} };
		std::initializer_list<Vector2> sliceSizes3{ Vector2{14.0f, 16.0f}, Vector2{14.0f, 14.0f }, Vector2{12.0f, 16.0f} };
		animator->CreateAnimation(L"Projectile_Move_2", ResourceManager::GetInstance().LoadTexture(L"\\texture\\Projectile2.bmp"), leftTops3, sliceSizes3, 0.1f, 3);
		animator->Play(L"Projectile_Move_2", true);
		animator->FindAnimation(L"Projectile_Move_2")->Save(L"\\texture\\animation\\Projectile_Move_2.anim");



		std::initializer_list<Vector2> leftTops4{ Vector2{54.0f, 0.0f}, Vector2{72.0f, 1.0f }, Vector2{91.0f, 0.0f} };
		std::initializer_list<Vector2> sliceSizes4{ Vector2{14.0f, 16.0f}, Vector2{14.0f, 14.0f }, Vector2{12.0f, 16.0f} };
		animator->CreateAnimation(L"Projectile_Move_3", ResourceManager::GetInstance().LoadTexture(L"\\texture\\Projectile2.bmp"), leftTops4, sliceSizes4, 0.1f, 3);
		animator->Play(L"Projectile_Move_3", true);
		animator->FindAnimation(L"Projectile_Move_3")->Save(L"\\texture\\animation\\Projectile_Move_3.anim");


		ChangeState(&attackState);
	}

	void ProjectileAttackState::Enter(Projectile& projectile) noexcept
	{
		projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_ATTACK, true);
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
		projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_MOVE_1, true);
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

	inline void ProjectileMovingState::OnCollisionEnter(Projectile& projectile, const Collider* other)
	{
		const Layer& otherLayer{ other->GetObj()->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Wall:
			projectile.ChangeToHighReachedState();
			break;
		}
	}

	void ProjectileHighReachedState::Enter(Projectile& projectile) noexcept
	{

	}

	void ProjectileHighReachedState::Update(Projectile& projectile)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (time >= ProjectileSetting::PROJECTILE_1_TIME + ProjectileSetting::PROJECTILE_2_TIME + ProjectileSetting::PROJECTILE_3_TIME)
		{
			projectile.Destroy();
		}
		else if (time >= ProjectileSetting::PROJECTILE_1_TIME + ProjectileSetting::PROJECTILE_2_TIME)
		{
			projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_MOVE_3, true);
		}
		else if (time >= ProjectileSetting::PROJECTILE_1_TIME)
		{
			projectile.GetAnimator()->Play(ProjectileSetting::PROJECTILE_MOVE_2, true);
		}
	}

	inline void ProjectileHighReachedState::OnCollisionEnter(Projectile& projectile, const Collider* other)
	{

	}
}
