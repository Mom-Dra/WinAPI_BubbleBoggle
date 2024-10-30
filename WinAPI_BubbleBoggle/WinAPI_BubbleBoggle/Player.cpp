#include "Player.h"
#include "Vector2.h"
#include "framework.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "EventManager.h"
#include "Projectile.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Ray.h"
#include "GameManager.h"

namespace MomDra
{
	Player::Player(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : Object{ pos, scale, layer }
	{
		CreateCollider(scale);

		CreateAnimator();
		CreateRigidbody();

		Animator* animator{ GetAnimator() };
		animator->LoadAnimation(L"\\animation\\Player_Walk_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Attack_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Idle_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Jump_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Fall_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Rotate_1_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Rotate_2_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Hit_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Destroy.anim");

		animator->LoadAnimation(L"\\animation\\Player_Walk_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Attack_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Idle_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Jump_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Fall_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Hit_Right.anim");

		ResourceManager::GetInstance().LoadSound(L"\\sound\\PlayerAttack.wav");
		ResourceManager::GetInstance().LoadSound(L"\\sound\\PlayerJump.wav");
		ResourceManager::GetInstance().LoadSound(L"\\sound\\PlayerDie.wav");

		ChangeState(&idleState);
	}

	void Player::Update() noexcept
	{
		currState->Update(*this);
	}

	void Player::Render(const HDC& hdc) const noexcept
	{
		const Vector2& pos{ GetPos() };
		const Vector2& scale{ GetScale() };
	
		Vector2 renderPos{ Camera::GetInstance().GetRenderPos(pos) };

		float halfScaleX{ scale.X / 2.0f };
		float halfScaleY{ scale.Y / 2.0f };

		Object::Render(hdc);
	}

	void Player::Die() noexcept
	{
		ChangeToDeadState();
	}

	void Player::OnCollisionEnter(const Collider* other)
	{
		currState->OnCollisionEnter(*this, other);
	}

	void Player::OnCollisionStay(const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer otherLayer{ otherObject->GetLayer() };
	}

	void Player::OnCollisionExit(const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer otherLayer{ otherObject->GetLayer() };
	}

	void Player::Attack() const noexcept
	{
		Animator* animator{ GetAnimator() };

		if (KeyManager::GetInstance().GetKeyDown(Key::A))
		{
			EventManager::GetInstance().Instantiate(new Projectile{ GetPos() + forward * 5.0f, Vector2{40.0f, 40.0f}, forward, Layer::Projectile });
			ResourceManager::GetInstance().FindSound(L"\\sound\\PlayerAttack.wav")->Play();

			if (IsRight())
				animator->PlayOneShot(PlayerSetting::ATTACK_RIGHT);
			else
				animator->PlayOneShot(PlayerSetting::ATTACK_LEFT);
		}
	}

	void Player::Move()
	{
		RigidBody* rigid{ GetRigidBody() };
		Animator* animator{ GetAnimator() };
		static const KeyManager& keyManager{ KeyManager::GetInstance() };

		bool leftPressed{ keyManager.GetKey(Key::LEFT) };
		bool RightPressed{ keyManager.GetKey(Key::RIGHT) };

		int move{ 0 };

		if (( !leftPressed || !RightPressed ) && !isCollideSideOfGround)
		{
			if (keyManager.GetKey(Key::LEFT))
			{
				rigid->AddVelocity(Vector2{ -PlayerSetting::MOVE_POWER, 0.0f });
				forward = -Vector2::UnitX;

				move = -1;
			}
			
			if (keyManager.GetKey(Key::RIGHT))
			{
				rigid->AddVelocity(Vector2{ PlayerSetting::MOVE_POWER, 0.0f });
				forward = Vector2::UnitX;

				move = 1;
			}
		}

		if (move == 1)
		{
			GetAnimator()->Play(PlayerSetting::WALK_RIGHT, true);
		}
		else if (move == -1)
		{
			GetAnimator()->Play(PlayerSetting::WALK_LEFT, true);
		}
		else
		{
			ChangeToIdleState();
		}
	}

	void Player::FallMove()
	{
		RigidBody* rigid{ GetRigidBody() };
		const KeyManager& keyManager{ KeyManager::GetInstance() };

		bool leftPressed{ keyManager.GetKey(Key::LEFT) };
		bool RightPressed{ keyManager.GetKey(Key::RIGHT) };

		if ((!leftPressed || !RightPressed) && !isCollideSideOfGround)
		{
			if (keyManager.GetKey(Key::LEFT))
			{
				rigid->AddVelocity(Vector2{ -PlayerSetting::FALL_MOVE_POWER, 0.0f });
				forward = -Vector2::UnitX;
			}

			if (keyManager.GetKey(Key::RIGHT))
			{
				rigid->AddVelocity(Vector2{ PlayerSetting::FALL_MOVE_POWER, 0.0f });
				forward = Vector2::UnitX;
			}
		}
	}

	void Player::Jump()
	{
		if (KeyManager::GetInstance().GetKeyDown(Key::S))
		{
			RigidBody* rigid{ GetRigidBody() };
			rigid->AddVelocity(Vector2{ 0.0f, -PlayerSetting::JUMP_POWER });

			ResourceManager::GetInstance().FindSound(L"\\sound\\PlayerJump.wav")->Play();

			ChangeToJumpState();
		}
	}

	void Player::CheckFall()
	{
		RigidBody* rigid{ GetRigidBody() };
		Animator* animator{ GetAnimator() };

		if (rigid->GetVelocity().Y > 0.0f)
			ChangeToFallState();
	}

	void Player::ReSpawn()
	{
		SetPos(PlayerSetting::SPAWN_POS);
		ChangeToIdleState();
	}

	void Player::ChangeState(PlayerState* state) noexcept
	{
		if (currState == state) return;

		if (currState)
			currState->Exit(*this);

		currState = state;

		currState->Enter(*this);
	}

	// IdleState

	void PlayerIdleState::Enter(Player& player)
	{
		if (player.IsRight())
			player.GetAnimator()->Play(PlayerSetting::IDLE_RIGHT, true);
		else
			player.GetAnimator()->Play(PlayerSetting::IDLE_LEFT, true);
	}

	void PlayerIdleState::Update(Player& player)
	{
		player.Move();
		player.Jump();
		player.Attack();
		player.CheckFall();
	}

	void PlayerIdleState::Exit(Player& player)
	{

	}

	// FallState

	void PlayerFallState::Enter(Player& player)
	{
		
	}

	void PlayerFallState::Update(Player& player)
	{
		player.FallMove();

		FallAnimation(player);

		player.Attack();
	}

	void PlayerFallState::Exit(Player& player)
	{

	}

	void PlayerFallState::OnCollisionEnter(Player& player, const Collider* other)
	{
		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Ground:
		{
			Collider* thisCollider{ player.GetCollider() };
			RigidBody* rigid{ player.GetRigidBody() };

			if (std::abs(other->GetFinalPos().X - thisCollider->GetFinalPos().X) >= other->GetScale().X / 2.0f + thisCollider->GetScale().X / 2.0f - 0.2f)
				return;

			// 아래에서 위로 올라가는 경우 무시!
			if (rigid->GetVelocity().Y < 0.0f && other->GetFinalPos().Y < thisCollider->GetFinalPos().Y) return;

			// 플레이어가 위에서 땅으로 떨어질 때

			player.ChangeToIdleState();
		}
		break;
		}
	}

	void PlayerFallState::FallAnimation(Player& player)
	{
		Animator* animator{ player.GetAnimator() };
		if (player.IsRight())
			animator->Play(PlayerSetting::FALL_RIGHT, true);
		else
			animator->Play(PlayerSetting::FALL_LEFT, true);
	}

	// JumpState

	void PlayerJumpState::Enter(Player& player)
	{
		
	}

	void PlayerJumpState::Update(Player& player)
	{
		player.FallMove();
		player.Attack();
		player.CheckFall();

		JumpAnimation(player);
	}

	void PlayerJumpState::Exit(Player& player)
	{

	}

	void PlayerJumpState::JumpAnimation(Player& player)
	{
		Animator* animator{ player.GetAnimator() };

		if (player.IsRight())
			animator->Play(PlayerSetting::JUMP_RIGHT, true);
		else
			animator->Play(PlayerSetting::JUMP_LEFT, true);
	}

	// DeadState

	void PlayerDeadState::Enter(Player& player)
	{
		ResourceManager::GetInstance().FindSound(L"\\sound\\PlayerDie.wav")->Play();
		player.GetRigidBody()->SetVelocity(Vector2::Zero);

		if (player.IsRight())
			player.GetAnimator()->Play(PlayerSetting::HIT_RIGHT, true);
		else
			player.GetAnimator()->Play(PlayerSetting::HIT_LEFT, true);

		GameManager::GetInstance().DecreasePlayerLife();
	}

	void PlayerDeadState::Update(Player& player)
	{
		static const TimeManager& timeManager{ TimeManager::GetInstance() };
		Animator* animator{ player.GetAnimator() };

		time += timeManager.GetDeltaTime();

		if (time >= PlayerSetting::HIT_TIME + PlayerSetting::ROTATE_1_TIME + PlayerSetting::ROTATE_2_TIME + PlayerSetting::DESTROY_TIME)
		{
			player.ReSpawn();
		}
		else if (time >= PlayerSetting::HIT_TIME + PlayerSetting::ROTATE_1_TIME + PlayerSetting::ROTATE_2_TIME)
		{
			if (isPlayedDestroyAnim) return;

			isPlayedDestroyAnim = true;

			animator->StopAndPlayOneShot(PlayerSetting::DESTROY);
		}
		else if (time >= PlayerSetting::HIT_TIME + PlayerSetting::ROTATE_1_TIME)
		{
			animator->Play(PlayerSetting::ROTATE_2, true);
		}
		else if (time >= PlayerSetting::HIT_TIME)
		{
			animator->Play(PlayerSetting::ROTATE_1, true);
		}
	}

	void PlayerDeadState::Exit(Player& player)
	{
		time = 0.0f;
		isPlayedDestroyAnim = false;
	}
}
