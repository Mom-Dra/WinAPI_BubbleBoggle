#include "Player.h"
#include "Vector2.h"
#include "framework.h"
#include "TimeManager.h"
#include "KeyManager.h"

using namespace MomDra;

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

	moveVec.Normalize();
	moveVec *= 10;

	SetPos(currPos + moveVec * TimeManager::GetInstance().GetDeltaTime());
	//SetPos(currPos + moveVec);
}

void Player::Render(const HDC& hdc) const noexcept
{
	ImageObject::Render(hdc);

	const Vector2& pos{ GetPos() };
	const Vector2& scale{ GetScale() };

	Rectangle(hdc, static_cast<int>(pos.X - scale.X / 2), static_cast<int>(pos.Y - scale.Y / 2), static_cast<int> (pos.X + scale.X / 2), static_cast<int>(pos.Y + scale.Y / 2));
}
