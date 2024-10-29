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

namespace MomDra
{
	Player::Player(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : Object{ pos, scale, layer }
	{
		CreateCollider(scale);

		CreateAnimator();
		CreateRigidbody();

		/*std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player2.bmp");*/

		/*GetAnimator()->CreateAnimation(L"WALK", ResourceManager::GetInstance().LoadTexture(filePath), Vector2{ 0.0f, 710.0f / 8.0f * 4.0f }, Vector2{ 820.0f / 10.0f, 710.0f / 8.0f }, Vector2{ 820.0f / 10.0f, 0.0f }, 0.1f, 10);
		GetAnimator()->Play(L"WALK", true);*/

		// 여기서 애니메이션 만들어야 한다
		std::shared_ptr<Texture> player_Left{ ResourceManager::GetInstance().LoadTexture(L"\\texture\\player.bmp") };

		Animator* animator{ GetAnimator() };
		//animator->CreateAnimation(L"Player_Walk_Left", player_Left, Vector2{ 1.0f, 0.0f }, Vector2{ 16.0f, 18.0f }, Vector2{ 22.0f, 0.0f }, 0.2f, 5);

		/*std::initializer_list<Vector2> leftTops{ Vector2{1.0f, 2.0f}, Vector2{22.0f, 2.0f}, Vector2{43.0f, 2.0f }, Vector2{64.0f, 2.0f }, Vector2{85.0f, 2.0f} };
		std::initializer_list<Vector2> sliceSizes{ Vector2{16.0f,16.0f}, Vector2{16.0f, 16.0f}, Vector2{16.0f, 16.0f}, Vector2{16.0f, 16.0f}, Vector2{16.0f, 16.0f} };*/

		//animator->CreateAnimation(L"Player_Walk_Left", player_Left, leftTops, sliceSizes, 0.2f, 5);
		//animator->FindAnimation(L"Player_Walk_Left")->Save(L"\\animation\\Player_Walk_Left.anim");
		//animator->Play(L"Player_Walk_Left", true);

		/*animator->CreateAnimation(L"Player_Attack_Left", player_Left, Vector2{ 145.0f, 0.0f }, Vector2{ 312.0f / 15.0f, 18.0f }, Vector2{ 312.0f / 15.0f, 0.0f }, 0.2f, 4);
		animator->FindAnimation(L"Player_Attack_Left")->Save(L"\\animation\\Player_Attack_Left.anim");*/
		
		//animator->Play(L"Player_Attack_Left", true);

		animator->LoadAnimation(L"\\animation\\Player_Walk_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Attack_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Idle_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Jump_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Fall_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Rotate_2_Left.anim");
		animator->LoadAnimation(L"\\animation\\Player_Hit_Left.anim");

		animator->LoadAnimation(L"\\animation\\Player_Walk_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Attack_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Idle_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Jump_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Fall_Right.anim");
		animator->LoadAnimation(L"\\animation\\Player_Hit_Right.anim");
		

		/*std::initializer_list<Vector2> leftTops2{ Vector2{1.0f, 2.0f}, Vector2{22.0f, 2.0f}, Vector2{43.0f, 2.0f }, Vector2{64.0f, 2.0f }, Vector2{85.0f, 2.0f} };
		std::initializer_list<Vector2> sliceSizes2{ Vector2{16.0f,16.0f}, Vector2{16.0f, 16.0f}, Vector2{16.0f, 16.0f}, Vector2{16.0f, 16.0f}, Vector2{16.0f, 16.0f} };*/

		//animator->CreateAnimation(L"Player_Falling_Left", player_Left, )
		//animator->CreateAnimation(L"Player_Walk")

		/*Animation* animation{ animator->FindAnimation(L"WALK") };
		for (unsigned int i{ 0 }; i < animation->GetMaxFrame(); ++i)
		{
			animation->GetFrame(i).offSet = Vector2{ 0.0f, 20.0f };
		}*/

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

		//Rectangle(hdc, static_cast<int>(renderPos.X - halfScaleX), static_cast<int>(renderPos.Y - halfScaleY), static_cast<int> (renderPos.X + halfScaleX), static_cast<int>(renderPos.Y + halfScaleY));

		Object::Render(hdc);
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
		static Animator* animator{ GetAnimator() };

		// Projectile 생성!
		// EventManager에 생성 등록!!

		if (KeyManager::GetInstance().GetKeyDown(Key::A))
		{
			EventManager::GetInstance().Instantiate(new Projectile{ GetPos() + forward * 5.0f, Vector2{40.0f, 40.0f}, forward, Layer::Projectile });

			if (isRight())
				//animator->PlayOneShot(PlayerSetting::ATTACK_RIGHT);
				animator->PlayOneShot(PlayerSetting::ATTACK_RIGHT);
			else
				animator->PlayOneShot(PlayerSetting::ATTACK_LEFT);
		}
	}

	void Player::Move()
	{
		static RigidBody* rigid{ GetRigidBody() };
		const KeyManager& keyManager{ KeyManager::GetInstance() };

		bool leftPressed{ keyManager.GetKey(Key::LEFT) };
		bool RightPressed{ keyManager.GetKey(Key::RIGHT) };

		int move{ 0 };

		if (!leftPressed || !RightPressed)
		{
			if (keyManager.GetKey(Key::LEFT))
			{
				rigid->AddVelocity(Vector2{ -PlayerSetting::MovePower, 0.0f });
				forward = -Vector2::UnitX;

				move = -1;
			}
			
			if (keyManager.GetKey(Key::RIGHT))
			{
				rigid->AddVelocity(Vector2{ PlayerSetting::MovePower, 0.0f });
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
	}

	void Player::FallMove()
	{
		static RigidBody* rigid{ GetRigidBody() };
		const KeyManager& keyManager{ KeyManager::GetInstance() };

		bool leftPressed{ keyManager.GetKey(Key::LEFT) };
		bool RightPressed{ keyManager.GetKey(Key::RIGHT) };

		if (!leftPressed || !RightPressed)
		{
			if (keyManager.GetKey(Key::LEFT))
			{
				rigid->AddVelocity(Vector2{ -PlayerSetting::FallMovePower, 0.0f });
				forward = -Vector2::UnitX;
			}

			if (keyManager.GetKey(Key::RIGHT))
			{
				rigid->AddVelocity(Vector2{ PlayerSetting::FallMovePower, 0.0f });
				forward = Vector2::UnitX;
			}
		}
	}

	void Player::Jump()
	{
		if (KeyManager::GetInstance().GetKeyDown(Key::S))
		{
			RigidBody* rigid{ GetRigidBody() };
			rigid->AddVelocity(Vector2{ 0.0f, -300.0f });

			ChangeToJumpState();
		}
	}

	void Player::CheckFall()
	{
		static RigidBody* rigid{ GetRigidBody() };
		static Animator* animator{ GetAnimator() };

		if (rigid->GetVelocity().Y > 0.0f)
			ChangeToFallState();
	}

	void Player::ChangeState(PlayerState* state) noexcept
	{
		currState->Exit(*this);

		currState = state;

		currState->Enter(*this);
	}

	// IdleState

	void PlayerIdleState::Enter(Player& player)
	{
		if (player.isRight())
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
		static Animator* animator{ player.GetAnimator() };
		if (player.isRight())
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
		static Animator* animator{ player.GetAnimator() };

		if (player.isRight())
			animator->Play(PlayerSetting::JUMP_RIGHT, true);
		else
			animator->Play(PlayerSetting::JUMP_LEFT, true);
	}

	// DeadState

	void PlayerDeadState::Enter(Player& player)
	{

	}

	void PlayerDeadState::Update(Player& player)
	{

	}

	void PlayerDeadState::Exit(Player& player)
	{

	}
}
