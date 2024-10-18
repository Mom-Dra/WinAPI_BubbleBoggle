#include "Collider.h"
#include "Core.h"
#include "SelectGDI.h"
#include "Camera.h"
#include <iostream>

namespace MomDra
{
	Collider::Collider(Object* owner) noexcept : owner{ owner }, id{ sID++ }, colCount{ 0 }
	{

	}

	Collider::Collider(Object* owner, const Vector2& scale) noexcept : owner{ owner }, scale{ scale }, id{ sID++ }, colCount{ 0 }
	{

	}

	Collider::Collider(const Collider& other) noexcept : owner{ nullptr }, offSetPos{ other.offSetPos }, scale{ other.scale }, id{ sID++ }, colCount{ 0 }
	{

	}

	void Collider::LateUpdate() noexcept
	{
		const Vector2& objectPos = owner->GetPos();
		finalPos = objectPos + offSetPos;
	}

	void Collider::Render(const HDC& hdc) noexcept
	{
		PenType penType{ PenType::Green };

		if (colCount)
			penType = PenType::Red;

		SelectGDI pen{ hdc, penType };
		SelectGDI brush{ hdc, BrushType::HOLLOW };

		Vector2 renderPos{ Camera::GetInstance().GetRenderPos(finalPos) };

		float halfScaleX{ scale.X / 2.0f };
		float halfScaleY{ scale.Y / 2.0f };

		Rectangle(hdc, static_cast<int>(renderPos.X - halfScaleX), static_cast<int>(renderPos.Y - halfScaleY),
			static_cast<int>(renderPos.X + halfScaleX), static_cast<int>(renderPos.Y + halfScaleY));
	}

	void Collider::OnCollisionStay(const Collider* other) noexcept
	{
		owner->OnCollisionStay(other);
	}

	void Collider::OnCollisionEnter(const Collider* other) noexcept
	{
		++colCount;

		owner->OnCollisionEnter(other);
	}

	void Collider::OnCollisionExit(const Collider* other) noexcept
	{
		--colCount;

		owner->OnCollisionExit(other);
	}
}
