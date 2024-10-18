#include "Monster.h"
#include "Item.h"
#include "Random.h"
#include "Ray.h"
#include "Player.h"

namespace MomDra
{
	Monster::Monster(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
		CreateRigidbody();
	}

	// MoveState
	void MonsterMoveState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		const Vector2& pos{ monster.GetPos() };

		time += deltaTime;

		// Move
		Move(monster, deltaTime);

		if (time >= ChangeDirTime)
		{
			if (Random::GetPossibility(ChangeDirPossibility))
			{
				monster.ChangeDir();
			}

			time = 0.0f;
		}
	}

	void MonsterMoveState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Projectile:
		{
			RigidBody* rigid{ monster.GetRigidBody() };
			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2::Zero);
			monster.ChangeToHittedState();
		}
		}
	}

	void MonsterMoveState::Move(Monster& monster, float deltaTime) const noexcept
	{
		const Vector2& pos{ monster.GetPos() };

		//monster.SetPos(pos + dir * speed * deltaTime);
		static RigidBody* rigid{ monster.GetRigidBody() };

		const Vector2& forward{ monster.GetForwardDir() };

		rigid->AddForce(forward * speed);

		// 내가 충돌하고 있는 Ground가 끝나려고 하면 일정 확률로 점프

		// Ground가 끝나는지..

		Ray::DebugRay(pos, forward * playerForwardRayDistance);
		Ray::DebugRay(pos, monster.GetUpDir() * playerForwardRayDistance);

		Collider* collider;
		if (Ray::RayCast(pos, forward * playerForwardRayDistance, Layer::Player, collider))
		{
			monster.SetPlayer(dynamic_cast<Player*>(collider->GetObj()));
			monster.ChangeToTraceState();
		}
		else if (Ray::RayCast(pos, forward * groundRayDistance, Layer::Ground, collider))
		{
			monster.ChangeDir();
		}

		if (Ray::RayCast(pos, monster.GetUpDir() * playerForwardRayDistance, Layer::Ground, collider))
		{
			if (Random::GetPossibility(50))
			{
				//rigid->AddVelocity(Vector2(0.0f, -300.0f));
			}
		}
	}

	// TraceState
	void MonsterTraceState::Update(Monster& monster) noexcept
	{

	}

	void MonsterTraceState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Projectile:
		{
			RigidBody* rigid{ monster.GetRigidBody() };
			rigid->SetGravity(false);
			rigid->SetVelocity(Vector2::Zero);
			monster.ChangeToHittedState();
		}
			break;
		}
	}

	// HitState
	void MonsterHittedState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		RigidBody* rigid{ monster.GetRigidBody() };
		rigid->SetGravity(false);

		const Vector2& pos{ monster.GetPos() };

		monster.SetPos(pos - Vector2::UnitY * speed * deltaTime);

		//rigid->AddForce(-Vector2::UnitY * speed);
	}

	void MonsterHittedState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Player:
		{
			// 아이템 생성!
			EventManager::GetInstance().Instantiate(new Item{ monster.GetPos() });

			// 몬스터 삭제
			monster.Destroy();
		}
		break;
		}
	}

	void MonsterAngryState::Update(Monster& monster) noexcept
	{

	}

	void MonsterAngryState::OnCollisionEnter(Monster& monster, const Collider* other)
	{

	}
}