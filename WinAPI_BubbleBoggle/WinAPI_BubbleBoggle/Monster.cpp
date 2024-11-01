#include "Monster.h"
#include "Item.h"
#include "Random.h"
#include "Ray.h"
#include "Player.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "RigidBody.h"
#include "Core.h"
#include "GameManager.h"

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

		animator->LoadAnimation(L"\\animation\\Monster_Walk_Left.anim");
		animator->LoadAnimation(L"\\animation\\Monster_Walk_Right.anim");
		animator->LoadAnimation(L"\\animation\\Monster_Walk_Angry_Left.anim");
		animator->LoadAnimation(L"\\animation\\Monster_Walk_Angry_Right.anim");
		animator->LoadAnimation(L"\\animation\\Monster_InProjectile_1.anim");
		animator->LoadAnimation(L"\\animation\\Monster_InProjectile_2.anim");
		animator->LoadAnimation(L"\\animation\\Monster_InProjectile_3.anim");
		animator->LoadAnimation(L"\\animation\\Monster_InProjectile_4.anim");
		animator->LoadAnimation(L"\\animation\\Monster_Rotate.anim");

		ResourceManager::GetInstance().LoadSound(L"\\sound\\AttackMonster.wav");

		ChangeToMoveState();
	}

	void Monster::ChangeDir() noexcept
	{
		RigidBody* rigid{ GetRigidBody() };
		Vector2 velocity{ rigid->GetVelocity() };
		velocity.X = -velocity.X;
		rigid->SetVelocity(velocity);

		forwardDir = -forwardDir;
	}

	void Monster::GetintoProjectile() noexcept
	{
		RigidBody* rigid{ GetRigidBody() };
		rigid->SetGravity(false);
		rigid->SetVelocity(Vector2::Zero);
		ChangeToHittedState();
	}

	void Monster::Die() noexcept
	{
		EventManager::GetInstance().Instantiate(new Item{ GetPos(), L"\\texture\\ItemBanana.bmp" });

		Destroy();

		GameManager::GetInstance().DecreaseNumOfMonster();
	}

	bool Monster::CanJump() const noexcept
	{
		Collider* collider;
		Ray::DebugRay(GetPos(), upDir * MonsterSetting::UP_RAY_DISTANCE);
		return Ray::RayCast(GetPos(), upDir * MonsterSetting::UP_RAY_DISTANCE, Layer::Ground, collider);
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

	void MonsterMoveState::Enter(Monster& monster) noexcept
	{
		WalkAnimation(monster);
	}

	// PlayerFallState
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
				WalkAnimation(monster);
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
		break;

		case Layer::Player:
		{
			Player* player{ dynamic_cast<Player*>(otherObject) };
			player->Die();
		}
			break;
		}
	}

	void MonsterMoveState::OnCollisionExit(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };
	}

	void MonsterMoveState::Exit(Monster& monster) noexcept
	{
		changeDirTime = 0.0f;
		jumpTime = 0.0f;
		//forwardJumpTime = 0.0f;
	}

	void MonsterMoveState::Move(Monster& monster, float deltaTime) noexcept
	{
		const Vector2& pos{ monster.GetPos() };

		RigidBody* rigid{ monster.GetRigidBody() };

		if (monster.CheckFall())
			monster.MoveForward(MonsterSetting::FALL_SPEED);
		else
			monster.MoveForward(MonsterSetting::SPEED);

		Ray::DebugRay(pos, monster.GetForwardDir() * MonsterSetting::FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, monster.GetUpDir() * MonsterSetting::UP_RAY_DISTANCE);
		Ray::DebugRay(pos, Vector2::UnitY * MonsterSetting::DOWN_RAY_DISTANCE);

		Collider* collider;
		
		// ChageDir
		if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::DOWN_RAY_DISTANCE, Layer::Wall, collider))
		{
			monster.ChangeDir();
			WalkAnimation(monster);
		}

		// Jump
		jumpTime += deltaTime;
		if (monster.CanJump() && jumpTime >= MonsterSetting::JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(MonsterSetting::JUMP_POSSIBILITY))
			{
				jumpTime = 0.0f;
				monster.Jump();
			}
		}

		// JumpForward
		forwardJumpTime += deltaTime;
		if (!Ray::RayCast(pos, Vector2::UnitY * MonsterSetting::DOWN_RAY_DISTANCE, Layer::Ground, collider) && monster.GetOnGround() && forwardJumpTime >= MonsterSetting::JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(MonsterSetting::FORWARD_JUMP_POSSIBILITY))
			{
				forwardJumpTime = 0.0f;
				monster.JumpForward();
			}
		}
	}

	void MonsterMoveState::WalkAnimation(Monster& monster)
	{
		Animator* animator{ monster.GetAnimator() };

		if (monster.IsRight())
			animator->Play(MonsterSetting::WALK_RIGHT, true);
		else
			animator->Play(MonsterSetting::WALK_LEFT, true);
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

		monster.SetPos(pos + monster.GetUpDir() * MonsterSetting::HITTED_SPEED * deltaTime);
	}

	void MonsterHittedState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Player:
		{
			monster.ChangeDeadState();
		}
		break;
		case Layer::Wall:
			monster.ChangeToHighState();
			break;
		}
	}

	void MonsterAngryState::Enter(Monster& monster) noexcept
	{
		WalkAnimation(monster);
		
		RigidBody* rigid{ monster.GetRigidBody() };
		rigid->SetGravity(true);
		
		const Vector2& maxVelocity{ rigid->GetMaxVelocity() };

		rigid->SetMaxVelocity(Vector2{ maxVelocity.X * 2.0f, maxVelocity.Y });
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
				WalkAnimation(monster);
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
		break;
		
		case Layer::Player:
		{
			Player* player{ dynamic_cast<Player*>(otherObject) };
			player->Die();
		}
			break;
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

		RigidBody* rigid{ monster.GetRigidBody() };

		if (monster.CheckFall())
			monster.MoveForward(MonsterSetting::FALL_SPEED);
		else
			monster.MoveForward(MonsterSetting::ANGRY_SPEED);

		Ray::DebugRay(pos, monster.GetForwardDir() * MonsterSetting::FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, monster.GetUpDir() * MonsterSetting::FORWARD_RAY_DISTANCE);
		Ray::DebugRay(pos, Vector2::UnitY * MonsterSetting::DOWN_RAY_DISTANCE);

		Collider* collider;
		
		if (Ray::RayCast(pos, monster.GetForwardDir() * MonsterSetting::DOWN_RAY_DISTANCE, Layer::Wall, collider))
		{
			monster.ChangeDir();
			WalkAnimation(monster);
		}

		// Jump
		jumpTime += deltaTime;
		if (monster.CanJump() && jumpTime >= MonsterSetting::ANGRY_JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(MonsterSetting::JUMP_POSSIBILITY))
			{
				jumpTime = 0.0f;
				monster.Jump();
			}
		}

		// JumpForward
		forwardJumpTime += deltaTime;
		if (!Ray::RayCast(pos, Vector2::UnitY * MonsterSetting::DOWN_RAY_DISTANCE, Layer::Ground, collider) && monster.GetOnGround() && forwardJumpTime >= MonsterSetting::ANGRY_JUMP_COOL_DOWN)
		{
			if (Random::GetPossibility(MonsterSetting::FORWARD_JUMP_POSSIBILITY))
			{
				forwardJumpTime = 0.0f;
				monster.JumpForward();
			}
		}
	}

	void MonsterAngryState::WalkAnimation(Monster& monster)
	{
		Animator* animator{ monster.GetAnimator() };

		if (monster.IsRight())
			animator->Play(MonsterSetting::WALK_ANGRY_RIGHT, true);
		else
			animator->Play(MonsterSetting::WALK_ANGRY_LEFT, true);
	}

	void MonsterHighState::Enter(Monster& monster) noexcept
	{
		targetYpos = monster.GetPos().Y;
	}

	void MonsterHighState::Update(Monster& monster) noexcept
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		float deltaTime{ timeManager.GetDeltaTime() };

		time += deltaTime;

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

		static float halfWidth{ Core::WINDOW_WIDTH / 2 };
		Vector2 targetPos{ halfWidth, targetYpos };
		const Vector2& pos{ monster.GetPos() };

		monster.SetPos(pos + (targetPos - pos).GetNormalize() * MonsterSetting::HITTED_SPEED * deltaTime);
	}

	void MonsterHighState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Player:
			monster.ChangeDeadState();
			break;
		}
	}

	void MonsterDeadState::Enter(Monster& monster) noexcept
	{
		ResourceManager::GetInstance().FindSound(L"\\sound\\AttackMonster.wav")->Play();
		monster.GetAnimator()->Play(MonsterSetting::ROTATE, true);
		monster.GetRigidBody()->SetGravity(true);
	}

	void MonsterDeadState::Update(Monster& monster) noexcept
	{

	}

	void MonsterDeadState::OnCollisionEnter(Monster& monster, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };

		switch (const Layer& otherLayer{ otherObject->GetLayer() })
		{
		case Layer::Ground:
			monster.Die();
			break;
		}
	}
}
