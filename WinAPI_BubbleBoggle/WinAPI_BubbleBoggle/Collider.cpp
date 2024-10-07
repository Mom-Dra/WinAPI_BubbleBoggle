#include "Collider.h"
#include "Core.h"
#include "SelectGDI.h"
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
		Vector2 objectPos = owner->GetPos();
		finalPos = objectPos + offSetPos;
	}

	void Collider::Render(const HDC& hdc) noexcept
	{
		PenType penType{ PenType::GREEN };

		if (colCount)
			penType = PenType::RED;

		SelectGDI pen{ hdc, penType };
		SelectGDI brush{ hdc, BrushType::HOLLOW };

		Rectangle(hdc, static_cast<int>(finalPos.X - scale.X / 2), static_cast<int>(finalPos.Y - scale.Y / 2),
			static_cast<int>(finalPos.X + scale.X / 2), static_cast<int>(finalPos.Y + scale.Y / 2));
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
