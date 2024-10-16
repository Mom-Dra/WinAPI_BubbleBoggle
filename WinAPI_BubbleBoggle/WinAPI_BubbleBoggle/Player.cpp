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

namespace MomDra
{
	Player::Player(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(scale);

		CreateAnimator();
		CreateRigidbody();

		/*std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player2.bmp");*/

		/*GetAnimator()->CreateAnimation(L"WALK", ResourceManager::GetInstance().LoadTexture(filePath), Vector2{ 0.0f, 710.0f / 8.0f * 4.0f }, Vector2{ 820.0f / 10.0f, 710.0f / 8.0f }, Vector2{ 820.0f / 10.0f, 0.0f }, 0.1f, 10);
		GetAnimator()->Play(L"WALK", true);*/

		// ���⼭ �ִϸ��̼� ������ �Ѵ�
		Animator* animator{ GetAnimator() };
		animator->CreateAnimation(L"WALK", ResourceManager::GetInstance().LoadTexture(L"\\texture\\player.bmp"), Vector2{ 0.0f, 0.0f }, Vector2{ 312.0f / 15.0f, 74.0f / 3.0f }, Vector2{ 312.0f / 15.0f, 0.0f }, 0.2f, 7);
		animator->Play(L"WALK", true);

		Animation* animation{ animator->FindAnimation(L"WALK") };
		for (unsigned int i{ 0 }; i < animation->GetMaxFrame(); ++i)
		{
			animation->GetFrame(i).offSet = Vector2{ 0.0f, -20.0f };
		}
	}

	void Player::Update() noexcept
	{
		Move();
		Jump();
		Attack();

		UpdateState();

		prevState = currState;
	}

	void Player::Render(const HDC& hdc) const noexcept
	{
		const Vector2& pos{ GetPos() };
		const Vector2& scale{ GetScale() };
	
		Vector2 renderPos{ Camera::GetInstance().GetRenderPos(pos) };

		// ���⿡ RenderPos ������Ʈ!

		Rectangle(hdc, static_cast<int>(renderPos.X - scale.X / 2), static_cast<int>(renderPos.Y - scale.Y / 2), static_cast<int> (renderPos.X + scale.X / 2), static_cast<int>(renderPos.Y + scale.Y / 2));

		Object::Render(hdc);
	}

	void Player::Attack() const noexcept
	{
		// Projectile ����!
		// EventManager�� ���� ���!!

		if (KeyManager::GetInstance().GetKeyDown(Key::CTRL))
		{
			EventManager::GetInstance().Instantiate(new Projectile{ Vector2{500.0f, 200.0f}, Vector2{50.0f, 50.0f}, Layer::PROJECTILE });
		}
	}

	void Player::Move()
	{
		RigidBody* rigid{ GetRigidBody() };
		const KeyManager& keyManager{ KeyManager::GetInstance() };

		static constexpr float AddPower{ 200.0f };

		if (keyManager.GetKeyDown(Key::LEFT))
		{
			rigid->AddVelocity(Vector2(-AddPower, 0.0f));
		}
		else if (keyManager.GetKey(Key::LEFT))
		{
			rigid->AddForce(Vector2(-AddPower, 0.0f));
		}

		if (keyManager.GetKeyDown(Key::RIGHT))
		{
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

		// Ư�� Ű�� ��������
		// Ư�� ���¿��� ���� �����Ѵ�?
		// �� �̷� ����?

		// �ƹ�Ű�� ������ �ʾ��� �� Idle�� �����ؾ���!
		// �ӵ��� ���� �ִϸ��̼ǵ� ���⼭ �غ���!
	}

	void Player::UpdateAnimation()
	{
		if (prevState == currState)
			return;

		switch (currState)
		{
		case MomDra::PlayerState::IDLE:
			break;
		case MomDra::PlayerState::WALK:
			break;
		case MomDra::PlayerState::ATTACK:
			break;
		case MomDra::PlayerState::HIT:
			break;
		case MomDra::PlayerState::DEAD:
			break;
		}
	}
}
