#include "Monster.h"
#include "Item.h"
#include "Random.h"
#include "Ray.h"
#include "Player.h"
#include "Projectile.h"
#include "ResourceManager.h"

namespace MomDra
{
	Monster::Monster(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
		CreateRigidbody();
		CreateAnimator();

		std::shared_ptr<Texture> enemyBmp{ ResourceManager::GetInstance().LoadTexture(L"\\texture\\Enemy.bmp") };
		std::shared_ptr<Texture> enemyRightBmp{ ResourceManager::GetInstance().LoadTexture(L"\\texture\\Enemy_Right.bmp") };

		Animator* animator{ GetAnimator() };
		/*animator->CreateAnimation(L"Monster_Walk_Left", ResourceManager::GetInstance().LoadTexture(L"\\texture\\Enemy.bmp"),
			Vector2{ 0.0f, 0.0f }, Vector2{ 72.0f / 4, 16.0f }, Vector2{ 72.0f / 4, 0.0f }, 0.1f, 4);*/

		// Walk Animation
		animator->LoadAnimation(L"\\animation\\Monster_Walk_Left.anim");
		animator->Play(L"Monster_Walk_Left", true);
		animator->FindAnimation(L"Monster_Walk_Left")->Save(L"\\animation\\Monster_Walk_Left.anim");


		animator->CreateAnimation(L"Monster_Walk_Right", enemyRightBmp, Vector2{ 516.0f, 0.0f }, Vector2{ 14.0f, 16.0f }, Vector2{ 19.0f, 0.0f }, 0.2f, 4);
		animator->Play(L"Monster_Walk_Right", true);
		animator->FindAnimation(L"Monster_Walk_Right")->Save(L"\\animation\\Monster_Walk_Right.anim");


		animator->CreateAnimation(L"Monster_Walk_Angry_Left", enemyBmp, Vector2{ 76.0f, 0.0f }, Vector2{ 14.0f, 16.0f }, Vector2{ 18.0f, 0.0f }, 0.2f, 4);
		animator->Play(L"Monster_Walk_Angry_Left", true);
		animator->FindAnimation(L"Monster_Walk_Angry_Left")->Save(L"\\animation\\Monster_Walk_Angry_Left.anim");


		animator->CreateAnimation(L"Monster_Walk_Angry_Right", enemyRightBmp, Vector2{ 444.0f, 0.0f }, Vector2{ 14.0f, 16.0f }, Vector2{ 18.0f, 0.0f }, 0.2f, 4);
		animator->Play(L"Monster_Walk_Angry_Right", true);
		animator->FindAnimation(L"Monster_Walk_Angry_Right")->Save(L"\\animation\\Monster_Walk_Angry_Right.anim");


		// InProjectile Animation
		animator->CreateAnimation(L"Monster_InProjectile_1", enemyBmp, Vector2{ 299.0f, 0.0f }, Vector2{ 13.0f, 16.0f }, Vector2{ 18.0f, 0.0f }, 0.3f, 3);
		animator->Play(L"Monster_InProjectile_1", true);
		//animator->FindAnimation(L"Monster_InProjectile_1")->Save(L"\\animation\\Monster_InProjectile_1.anim");


		animator->CreateAnimation(L"Monster_InProjectile_2", enemyBmp, Vector2{ 353.0f, 0.0f }, Vector2{ 13.0f, 16.0f }, Vector2{ 18.0f, 0.0f }, 0.3f, 3);
		animator->Play(L"Monster_InProjectile_2", true);
		//animator->FindAnimation(L"Monster_InProjectile_2")->Save(L"\\animation\\Monster_InProjectile_2.anim");


		animator->CreateAnimation(L"Monster_InProjectile_3", enemyBmp, Vector2{ 407.0f, 0.0f }, Vector2{ 13.0f, 16.0f }, Vector2{ 18.0f, 0.0f }, 0.3f, 3);
		animator->Play(L"Monster_InProjectile_3", true);
		//animator->FindAnimation(L"Monster_InProjectile_3")->Save(L"\\animation\\Monster_InProjectile_3.anim");


		animator->CreateAnimation(L"Monster_InProjectile_4", enemyBmp, Vector2{ 461.0f, 0.0f }, Vector2{ 13.0f, 16.0f }, Vector2{ 18.0f, 0.0f }, 0.3f, 3);
		animator->Play(L"Monster_InProjectile_4", true);
		//animator->FindAnimation(L"Monster_InProjectile_4")->Save(L"\\animation\\Monster_InProjectile_4.anim");


		// Jump
		animator->CreateAnimation(L"Monster_Jump_Left", enemyBmp, Vector2{ 38.0f, 0.0f }, Vector2{ 14.0f, 16.0f }, Vector2{ 19.0f, 0.0f }, { 0.5f, 0.5f }, 2);
		animator->Play(L"Monster_Jump_Left", true);
		animator->FindAnimation(L"Monster_Jump_Left")->Save(L"\\animation\\Monster_Jump_Left.anim");


		animator->CreateAnimation(L"Monster_Jump_Right", enemyRightBmp, { Vector2{536.0f, 0.0f }, Vector2{516.0f, 0.0f} }, Vector2{ 14.0f, 16.0f }, { 0.5f, 0.5f }, 2);
		animator->Play(L"Monster_Jump_Right", true);
		animator->FindAnimation(L"Monster_Jump_Right")->Save(L"\\animation\\Monster_Jump_Right.anim");


		animator->CreateAnimation(L"Monster_Jump_Angry_Left", enemyBmp, Vector2{ 112.0f, 0.0f }, Vector2{ 14.0f, 16.0f }, Vector2{ 17.0f, 0.0f }, { 0.5f, 0.5f }, 2);
		animator->Play(L"Monster_Jump_Angry_Left", true);
		animator->FindAnimation(L"Monster_Jump_Angry_Left")->Save(L"\\animation\\Monster_Jump_Angry_Left.anim");
 

		animator->CreateAnimation(L"Monster_Jump_Angry_Right", enemyRightBmp, { Vector2{ 462.0f, 0.0f }, Vector2{444.0f, 0.0f} }, Vector2{ 14.0f, 16.0f }, { 0.5f, 0.5f }, 2);
		animator->Play(L"Monster_Jump_Angry_Right", true);
		animator->FindAnimation(L"Monster_Jump_Angry_Right")->Save(L"\\animation\\Monster_Jump_Angry_Right.anim");

		ChangeState(&moveState);
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

	bool Monster::CanJump() const noexcept
	{
		Collider* collider;
		Ray::DebugRay(GetPos(), upDir * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE);
		return Ray::RayCast(GetPos(), upDir * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE, Layer::Ground, collider);
	}

	void Monster::ChangeState(MonsterState* state) noexcept
	{
		currState->Exit(*this);

		currState = state;

		currState->Enter(*this);
	}

	void Monster::OnCollisionEnter(const Collider* other)
	{
		currState->OnCollisionEnter(*this, other);
	}

	void Monster::OnCollisionExit(const Collider* other)
	{
		currState->OnCollisionExit(*this, other);
	}

	// 땅이 끝날 때 떨어질지, 앞으로 점프할지, 위로 점프할지 결정한다!!
	// 플레이어가 위에 있으면 점프, 아래 있으면 떨어지기, 같은 높이에 있으면 앞으로 점프 하자!
	// 그냥 걸어가다가도 위로 점프 가능하면 점프 한다!
	// 떨어질 때는 밑에 바닥이 나올 때까지 계속 떨어진다

	void MonsterMoveState::Enter(Monster& monster) noexcept
	{
		monster.GetAnimator()->Play(MonsterSetting::WALK_RIGHT, true);
	}

	// MoveState
	void MonsterMoveState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		float deltaTime{ timeManager.GetDeltaTime() };

		const Vector2& pos{ monster.GetPos() };

		changeDirTime += deltaTime;

		// Move
		Move(monster, deltaTime);

		if (changeDirTime >= MonsterSetting::CHANGE_DIR_TIME)
		{
			if (Random::GetPossibility(MonsterSetting::CHANGE_DIR_POSSIBILITY))
			{
				monster.ChangeDir();
			}

			changeDirTime = 0.0f;
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

	void MonsterMoveState::OnCollisionExit(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };
		
	}

	void MonsterMoveState::Move(Monster& monster, float deltaTime) noexcept
	{
		const Vector2& pos{ monster.GetPos() };

		//monster.SetPos(pos + dir * SPEED * deltaTime);
		static RigidBody* rigid{ monster.GetRigidBody() };

		monster.MoveForward(MonsterSetting::SPEED);
		// 내가 충돌하고 있는 Ground가 끝나려고 하면 일정 확률로 점프

		// Ground가 끝나는지..

		Ray::DebugRay(pos, monster.GetForwardDir() * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, monster.GetUpDir() * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, Vector2::UnitY * MonsterSetting::GROUND_RAY_DISTANCE);

		Collider* collider;
		if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE, Layer::Player, collider))
		{
			monster.SetPlayer(dynamic_cast<Player*>(collider->GetObj()));

			// trace 상태는 일단 없는걸로 해보자!
			//monster.ChangeToTraceState();
		}
		else if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::GROUND_RAY_DISTANCE, Layer::Wall, collider))
		{
			monster.ChangeDir();
		}

		jumpTime += deltaTime;
		if (monster.CanJump() && jumpTime >= MonsterSetting::JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(50))
			{
				// Jump 로직, 떨어지는 도중에 발생할 수도 있음
				jumpTime = 0.0f;
				monster.Jump();

				monster.GetAnimator()->Play(MonsterSetting::JUMP_LEFT, true);
			}
		}

		// JumpForward
		forwardJumpTime += deltaTime;
		if (!Ray::RayCast(pos, Vector2::UnitY * MonsterSetting::GROUND_RAY_DISTANCE, Layer::Ground, collider) && monster.GetOnGround() && forwardJumpTime >= MonsterSetting::JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(50))
			{
				forwardJumpTime = 0.0f;
				monster.JumpForward();

				monster.GetAnimator()->Play(MonsterSetting::JUMP_LEFT, true);
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
		rigid->AddForce(forward * MonsterSetting::SPEED);
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

	void MonsterHittedState::Enter(Monster& monster) noexcept
	{
		monster.GetAnimator()->Play(MonsterSetting::INPROJECTILE_1, true);
	}

	// HitState
	void MonsterHittedState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += deltaTime;

		RigidBody* rigid{ monster.GetRigidBody() };
		rigid->SetGravity(false);

		const Vector2& pos{ monster.GetPos() };

		monster.SetPos(pos - Vector2::UnitY * MonsterSetting::HITTED_SPEED * deltaTime);
		
		//rigid->AddForce(-Vector2::UnitY * MonsterSetting::HITTED_SPEED);

		if (time >= MonsterSetting::PROJECTILE_1_TIME + MonsterSetting::PROJECTILE_2_TIME + MonsterSetting::PROJECTILE_3_TIME)
		{
			monster.ChangeToAngryState();
		}
		else if (time >= MonsterSetting::PROJECTILE_1_TIME + MonsterSetting::PROJECTILE_2_TIME)
		{
			monster.GetAnimator()->Play(MonsterSetting::INPROJECTILE_4, true);
		}
		else if (time >= MonsterSetting::PROJECTILE_1_TIME)
		{
			monster.GetAnimator()->Play(MonsterSetting::INPROJECTILE_3, true);
		}
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

	void MonsterAngryState::Enter(Monster& monster) noexcept
	{
		monster.GetAnimator()->Play(MonsterSetting::WALK_ANGRY_LEFT, true);
		monster.GetRigidBody()->SetGravity(true);
	}

	void MonsterAngryState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		float deltaTime{ timeManager.GetDeltaTime() };

		const Vector2& pos{ monster.GetPos() };

		changeDirTime += deltaTime;

		// Move
		Move(monster, deltaTime);

		if (changeDirTime >= MonsterSetting::CHANGE_DIR_TIME)
		{
			if (Random::GetPossibility(MonsterSetting::CHANGE_DIR_POSSIBILITY))
			{
				monster.ChangeDir();
			}

			changeDirTime = 0.0f;
		}
	}

	void MonsterAngryState::OnCollisionEnter(Monster& monster, const Collider* other)
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

	void MonsterAngryState::OnCollisionExit(Monster& monster, const Collider* other)
	{

	}

	void MonsterAngryState::Exit(Monster& monster) noexcept
	{
		changeDirTime = 0.0f;
		jumpTime = 0.0f;
		forwardJumpTime = 0.0f;
	}

	void MonsterAngryState::Move(Monster& monster, float deltaTime) noexcept
	{
		const Vector2& pos{ monster.GetPos() };

		//monster.SetPos(pos + dir * SPEED * deltaTime);
		static RigidBody* rigid{ monster.GetRigidBody() };

		monster.MoveForward(MonsterSetting::ANGRY_SPEED);
		// 내가 충돌하고 있는 Ground가 끝나려고 하면 일정 확률로 점프

		// Ground가 끝나는지..

		Ray::DebugRay(pos, monster.GetForwardDir() * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, monster.GetUpDir() * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, Vector2::UnitY * MonsterSetting::GROUND_RAY_DISTANCE);

		Collider* collider;
		if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::PLAYER_FORWARD_RAY_DISTANCE, Layer::Player, collider))
		{
			monster.SetPlayer(dynamic_cast<Player*>(collider->GetObj()));

			// trace 상태는 일단 없는걸로 해보자!
			//monster.ChangeToTraceState();
		}
		else if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::GROUND_RAY_DISTANCE, Layer::Wall, collider))
		{
			monster.ChangeDir();
		}

		jumpTime += deltaTime;
		if (monster.CanJump() && jumpTime >= MonsterSetting::JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(50))
			{
				// Jump 로직, 떨어지는 도중에 발생할 수도 있음
				jumpTime = 0.0f;
				monster.Jump();

				monster.GetAnimator()->Play(MonsterSetting::JUMP_ANGRY_LEFT, true);
			}
		}

		// JumpForward
		forwardJumpTime += deltaTime;
		if (!Ray::RayCast(pos, Vector2::UnitY * MonsterSetting::GROUND_RAY_DISTANCE, Layer::Ground, collider) && monster.GetOnGround() && forwardJumpTime >= MonsterSetting::JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(50))
			{
				forwardJumpTime = 0.0f;
				monster.JumpForward();

				monster.GetAnimator()->Play(MonsterSetting::JUMP_ANGRY_LEFT, true);
			}
		}
	}
}