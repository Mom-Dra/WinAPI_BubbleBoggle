#include "Monster.h"
#include "Item.h"
#include "Random.h"
#include "Ray.h"
#include "Player.h"
#include "Projectile.h"

namespace MomDra
{
	Monster::Monster(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
		CreateRigidbody();
	}

	void Monster::ChangeDir() noexcept
	{
		RigidBody* rigid{ GetRigidBody() };
		Vector2 velocity{ rigid->GetVelocity() };
		velocity.X = -velocity.X;
		rigid->SetVelocity(velocity);

		forwardDir = -forwardDir;
		//upDir.X = -upDir.X;
		//dir = -dir;
	}

	void Monster::GetintoProjectile() noexcept
	{
		RigidBody* rigid{ GetRigidBody() };
		rigid->SetGravity(false);
		rigid->SetVelocity(Vector2::Zero);
		ChangeToHittedState();
	}

	// 땅이 끝날 때 떨어질지, 앞으로 점프할지, 위로 점프할지 결정한다!!
	// 플레이어가 위에 있으면 점프, 아래 있으면 떨어지기, 같은 높이에 있으면 앞으로 점프 하자!
	// 그냥 걸어가다가도 위로 점프 가능하면 점프 한다!
	// 떨어질 때는 밑에 바닥이 나올 때까지 계속 떨어진다

	// MoveState
	void MonsterMoveState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		const Vector2& pos{ monster.GetPos() };

		time += deltaTime;

		// Move
		Move(monster, deltaTime);

		if (time >= MonsterSetting::ChangeDirTime)
		{
			if (Random::GetPossibility(MonsterSetting::ChangeDirPossibility))
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
			Projectile* projectile{ dynamic_cast<Projectile*>(otherObject) };

			if (projectile->IsAttackState())
			{
				monster.GetintoProjectile();
			}
		}
		}
	}

	void MonsterMoveState::Move(Monster& monster, float deltaTime) const noexcept
	{
		const Vector2& pos{ monster.GetPos() };

		//monster.SetPos(pos + dir * speed * deltaTime);
		static RigidBody* rigid{ monster.GetRigidBody() };

		monster.MoveForward(MonsterSetting::speed);
		// 내가 충돌하고 있는 Ground가 끝나려고 하면 일정 확률로 점프

		// Ground가 끝나는지..

		Ray::DebugRay(pos, monster.GetForwardDir() * MonsterSetting::playerForwardRayDistance);
		Ray::DebugRay(pos, monster.GetUpDir() * MonsterSetting::playerForwardRayDistance);

		Collider* collider;
		if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::playerForwardRayDistance, Layer::Player, collider))
		{
			monster.SetPlayer(dynamic_cast<Player*>(collider->GetObj()));

			// trace 상태는 일단 없는걸로 해보자!
			//monster.ChangeToTraceState();
		}
		else if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::groundRayDistance, Layer::Ground, collider))
		{
			monster.ChangeDir();
		}

		if (Ray::RayCast(pos, monster.GetUpDir() * MonsterSetting::playerForwardRayDistance, Layer::Ground, collider))
		{
			if (Random::GetPossibility(0))
			{
				// Jump 로직, 떨어지는 도중에 발생할 수도 있음
				
				monster.Jump();

				//rigid->AddVelocity(Vector2(0.0f, -300.0f));
			}
		}
	}

	// TraceState
	void MonsterTraceState::Update(Monster& monster) noexcept
	{
		// 움직일 거야!
		static RigidBody* rigid{ monster.GetRigidBody() };

		// 플레이어와 몬스터의 거리가 일정 거리 이상 떨어지면
		// 다시 MoveState
		// Player를 Follow 할거야
		Player* player{ monster.GetPlayer() };

		const Vector2& playerPos{ player->GetPos() };
		const Vector2& monsterPos{ monster.GetPos() };
		const Vector2& forwardDir{ monster.GetForwardDir() };

		bool playerIsRight{ monsterPos.X < playerPos.X };
		bool facingRight{ forwardDir == Vector2::UnitX };

		// 누가 더 오른쪽에 있을까?
		if ((playerIsRight && !facingRight) || (!playerIsRight && facingRight))
			monster.ChangeDir();

		const Vector2& forward{ monster.GetForwardDir() };
		rigid->AddForce(forward * MonsterSetting::speed);
	}

	void MonsterTraceState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Projectile:
		{
			Projectile* projectile{ dynamic_cast<Projectile*>(otherObject) };

			if (projectile->IsAttackState())
			{
				monster.GetintoProjectile();
			}
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

		monster.SetPos(pos - Vector2::UnitY * MonsterSetting::hittedSpeed * deltaTime);

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