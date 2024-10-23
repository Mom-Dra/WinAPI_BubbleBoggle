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
		Animator* animator{ GetAnimator() };
		animator->CreateAnimation(L"WALK", ResourceManager::GetInstance().LoadTexture(L"\\texture\\player.bmp"), Vector2{ 0.0f, 0.0f }, Vector2{ 312.0f / 15.0f, 74.0f / 3.0f }, Vector2{ 312.0f / 15.0f, 0.0f }, 0.2f, 7);
	
		animator->FindAnimation(L"WALK")->Save(L"\\animation\\Player_Walk.anim");

		//animator->LoadAnimation(L"\\animation\\Player_Walk.anim");
		animator->Play(L"WALK", true);

		/*Animation* animation{ animator->FindAnimation(L"WALK") };
		for (unsigned int i{ 0 }; i < animation->GetMaxFrame(); ++i)
		{
			animation->GetFrame(i).offSet = Vector2{ 0.0f, 20.0f };
		}*/

		
	}

	void Player::Update() noexcept
	{
		Move();
		Jump();
		Attack();

		UpdateState();
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
		Object* otherObject{ other->GetObj() };
		const Layer otherLayer{ otherObject->GetLayer() };
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
		// Projectile 생성!
		// EventManager에 생성 등록!!

		if (KeyManager::GetInstance().GetKeyDown(Key::CTRL))
		{
			EventManager::GetInstance().Instantiate(new Projectile{ GetPos() + forward * 5.0f, Vector2{10.0f, 10.0f}, forward, Layer::Projectile });
		}
	}

	void Player::Move()
	{
		RigidBody* rigid{ GetRigidBody() };
		const KeyManager& keyManager{ KeyManager::GetInstance() };

		static constexpr float AddPower{ 200.0f };

		if (keyManager.GetKeyDown(Key::LEFT))
		{
			forward = -Vector2::UnitX;
			rigid->AddVelocity(Vector2(-AddPower, 0.0f));
		}
		else if (keyManager.GetKey(Key::LEFT))
		{
			rigid->AddForce(Vector2(-AddPower, 0.0f));
		}

		if (keyManager.GetKeyDown(Key::RIGHT))
		{
			forward = Vector2::UnitX;
			rigid->AddVelocity(Vector2(AddPower, 0.0f));
		}
		else if (keyManager.GetKey(Key::RIGHT))
		{
			rigid->AddForce(Vector2(AddPower, 0.0f));
		}
	}

	void Player::Jump()
	{
		if (KeyManager::GetInstance().GetKeyDown(Key::SPACE))
		{
			RigidBody* rigid{ GetRigidBody() };
			rigid->AddVelocity(Vector2(0.0f, -300.0f));
		}
	}

	void Player::UpdateState()
	{
		const KeyManager& keyManager{ KeyManager::GetInstance() };

		// 특정 키가 눌렸을때
		// 특정 상태였을 때는 무시한다?
		// 뭐 이런 로직?

		// 아무키가 눌리지 않았을 때 Idle로 변경해야지!
		// 속도에 따른 애니메이션도 여기서 해보자!
	}
}
