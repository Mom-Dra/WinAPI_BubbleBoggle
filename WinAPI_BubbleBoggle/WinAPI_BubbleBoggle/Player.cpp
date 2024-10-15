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
		CreateCollider(Vector2{ 100.0f, 100.0f });

		CreateAnimator();
		CreateRigidbody();

		/*std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player2.bmp");*/

		/*GetAnimator()->CreateAnimation(L"WALK", ResourceManager::GetInstance().LoadTexture(filePath), Vector2{ 0.0f, 710.0f / 8.0f * 4.0f }, Vector2{ 820.0f / 10.0f, 710.0f / 8.0f }, Vector2{ 820.0f / 10.0f, 0.0f }, 0.1f, 10);
		GetAnimator()->Play(L"WALK", true);*/

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
		RigidBody* rigid{ GetRigidBody() };

		if (KeyManager::GetInstance().GetKeyDown(Key::LEFT))
		{
			rigid->AddVelocity(Vector2(-100.0f, 0.0f));
		}
		else if (KeyManager::GetInstance().GetKey(Key::LEFT))
		{
			rigid->AddForce(Vector2(-200.0f, 0.0f));
		}

		if (KeyManager::GetInstance().GetKeyDown(Key::RIGHT))
		{
			rigid->AddVelocity(Vector2(100.0f, 0.0f));
		}
		else if (KeyManager::GetInstance().GetKey(Key::RIGHT))
		{
			rigid->AddForce(Vector2(200.0f, 0.0f));
		}

		if (KeyManager::GetInstance().GetKeyDown(Key::DOWN))
		{
			rigid->AddVelocity(Vector2(0.0f, 100.0f));
		}
		else if (KeyManager::GetInstance().GetKey(Key::DOWN))
		{
			rigid->AddForce(Vector2(0.0f, 200.0f));
		}

		if (KeyManager::GetInstance().GetKeyDown(Key::UP))
		{
			rigid->AddVelocity(Vector2(0.0f, -100.0f));
		}
		else if (KeyManager::GetInstance().GetKey(Key::UP))
		{
			rigid->AddForce(Vector2(0.0f, -200.0f));
		}

		if (KeyManager::GetInstance().GetKeyDown(Key::SPACE))
		{
			Attack();
		}
	}

	void Player::Render(const HDC& hdc) const noexcept
	{
		const Vector2& pos{ GetPos() };
		const Vector2& scale{ GetScale() };
	
		Vector2 renderPos{ Camera::GetInstance().GetRenderPos(pos) };

		// 여기에 RenderPos 업데이트!

		Rectangle(hdc, static_cast<int>(renderPos.X - scale.X / 2), static_cast<int>(renderPos.Y - scale.Y / 2), static_cast<int> (renderPos.X + scale.X / 2), static_cast<int>(renderPos.Y + scale.Y / 2));

		Object::Render(hdc);
	}

	void Player::Attack() const noexcept
	{
		// Projectile 생성!
		// EventManager에 생성 등록!!
		EventManager::GetInstance().Instantiate(new Projectile{ Vector2{500.0f, 200.0f}, Vector2{50.0f, 50.0f}, Layer::PROJECTILE });
	}
}
