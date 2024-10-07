#include "Player.h"
#include "Vector2.h"
#include "framework.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "EventManager.h"
#include "Projectile.h"
#include "PathManager.h"

namespace MomDra
{
	Player::Player(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer) : ImageObject{ pos, scale, imgPath, layer }
	{
		CreateCollider(Vector2{ 100.0f, 100.0f });
	}

	void Player::Update() noexcept
	{
		ImageObject::Update();

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

		ImageObject::Render(hdc);
	}

	void Player::Attack() const noexcept
	{
		// Projectile 积己!
		std::wstring filePath{ PathManager::GetContentPath() };
		filePath.append(L"\\texture\\player.bmp");

		// EventManager俊 积己 殿废!!
		EventManager::GetInstance().Instantiate(new Projectile{ Vector2{500.0f, 200.0f}, Vector2{50.0f, 50.0f}, filePath, Layer::PROJECTILE });
	}
}
