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

	// ���� ���� �� ��������, ������ ��������, ���� �������� �����Ѵ�!!
	// �÷��̾ ���� ������ ����, �Ʒ� ������ ��������, ���� ���̿� ������ ������ ���� ����!
	// �׳� �ɾ�ٰ��� ���� ���� �����ϸ� ���� �Ѵ�!
	// ������ ���� �ؿ� �ٴ��� ���� ������ ��� ��������

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
		// ���� �浹�ϰ� �ִ� Ground�� �������� �ϸ� ���� Ȯ���� ����

		// Ground�� ��������..

		Ray::DebugRay(pos, monster.GetForwardDir() * MonsterSetting::playerForwardRayDistance);
		Ray::DebugRay(pos, monster.GetUpDir() * MonsterSetting::playerForwardRayDistance);

		Collider* collider;
		if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::playerForwardRayDistance, Layer::Player, collider))
		{
			monster.SetPlayer(dynamic_cast<Player*>(collider->GetObj()));

			// trace ���´� �ϴ� ���°ɷ� �غ���!
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
				// Jump ����, �������� ���߿� �߻��� ���� ����
				
				monster.Jump();

				//rigid->AddVelocity(Vector2(0.0f, -300.0f));
			}
		}
	}

	// TraceState
	void MonsterTraceState::Update(Monster& monster) noexcept
	{
		// ������ �ž�!
		static RigidBody* rigid{ monster.GetRigidBody() };

		// �÷��̾�� ������ �Ÿ��� ���� �Ÿ� �̻� ��������
		// �ٽ� MoveState
		// Player�� Follow �Ұž�
		Player* player{ monster.GetPlayer() };

		const Vector2& playerPos{ player->GetPos() };
		const Vector2& monsterPos{ monster.GetPos() };
		const Vector2& forwardDir{ monster.GetForwardDir() };

		bool playerIsRight{ monsterPos.X < playerPos.X };
		bool facingRight{ forwardDir == Vector2::UnitX };

		// ���� �� �����ʿ� ������?
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
			// ������ ����!
			EventManager::GetInstance().Instantiate(new Item{ monster.GetPos() });

			// ���� ����
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