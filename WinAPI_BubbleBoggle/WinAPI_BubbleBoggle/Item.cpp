#include "Item.h"
#include "SelectGDI.h"
#include "Camera.h"

namespace MomDra
{
	Item::Item(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : Object{ pos, scale, layer }
	{
		CreateCollider(scale);
		CreateRigidbody();
	}

	void Item::Update() noexcept
	{
		if (canCollision) return;

		static const TimeManager& timeManager{ TimeManager::GetInstance() };

		time += timeManager.GetDeltaTime();

		if (time >= canCollisionTime)
			canCollision = true;
	}

	inline void Item::Render(const HDC& hdc) const noexcept
	{
		SelectGDI pen{ hdc, PenType::Orange };

		const Vector2& pos{ GetPos() };
		const Vector2& scale{ GetScale() };

		Vector2 renderPos{ Camera::GetInstance().GetRenderPos(pos) };

		float halfScaleX{ scale.X / 2.0f };
		float halfScaleY{ scale.Y / 2.0f };

		Rectangle(hdc, static_cast<int>(renderPos.X - halfScaleX), static_cast<int>(renderPos.Y - halfScaleY), static_cast<int> (renderPos.X + halfScaleX), static_cast<int>(renderPos.Y + halfScaleY));

		//Object::Render(hdc);
	}

	void Item::OnCollisionEnter(const Collider* other)
	{
		if (!canCollision)	return;

		Object* otherObject{ other->GetObj() };
		const Layer& otherLayer{ otherObject->GetLayer() };

		switch (otherLayer)
		{
		case Layer::Player:
			Destroy();
			break;
		}
	}
}