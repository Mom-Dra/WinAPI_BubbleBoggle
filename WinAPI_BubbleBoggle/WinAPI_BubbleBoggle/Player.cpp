#include "Player.h"
#include "Vector2.h"
#include "framework.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "EventManager.h"
#include "Projectile.h"
#include "PathManager.h"
#include "ResourceManager.h"

namespace MomDra
{
	Player::Player(const Vector2& pos, const Vector2& scale, const Layer& layer) : Object{ pos, scale, layer }
	{
		CreateCollider(Vector2{ 100.0f, 100.0f });


		CreateAnimator();

		std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player2.bmp");

		GetAnimator()->CreateAnimation(L"WALK", ResourceManager::GetInstance().LoadTexture(filePath), Vector2{ 0.0f, 710.0f / 8.0f * 4.0f }, Vector2{ 820.0f / 10.0f, 710.0f / 8.0f }, Vector2{ 820.0f / 10.0f, 0.0f }, 0.1f, 10);
		GetAnimator()->Play(L"WALK", true);
	}

	void Player::Update() noexcept
	{
		const Vector2& currPos{ GetPos() };
		Vector2 moveVec{ Vector2::Zero };

		if (KeyManager::GetInstance().GetKey(Key::A))
		{
			moveVec -= Vector2::UnitX;
		}

		if (KeyManager::GetInstance().GetKey(Key::D))
		{
			moveVec += Vector2::UnitX;
		}

		if (KeyManager::GetInstance().GetKey(Key::S))
		{
			moveVec += Vector2::UnitY;
		}

		if (KeyManager::GetInstance().GetKey(Key::W))
		{
			moveVec -= Vector2::UnitY;
		}

		if (KeyManager::GetInstance().GetKeyDown(Key::SPACE))
		{
			Attack();
		}

		moveVec.Normalize();
		moveVec *= 100;

		SetPos(currPos + moveVec * TimeManager::GetInstance().GetDeltaTime());
	}

	void Player::Render(const HDC& hdc) const noexcept
	{
		const Vector2& pos{ GetPos() };
		const Vector2& scale{ GetScale() };

		Rectangle(hdc, static_cast<int>(pos.X - scale.X / 2), static_cast<int>(pos.Y - scale.Y / 2), static_cast<int> (pos.X + scale.X / 2), static_cast<int>(pos.Y + scale.Y / 2));

		Object::Render(hdc);
	}

	void Player::Attack() const noexcept
	{
		// Projectile 생성!
		std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player.bmp");

		// EventManager에 생성 등록!!
		EventManager::GetInstance().Instantiate(new Projectile{ Vector2{500.0f, 200.0f}, Vector2{50.0f, 50.0f}, Layer::PROJECTILE });
	}
}
