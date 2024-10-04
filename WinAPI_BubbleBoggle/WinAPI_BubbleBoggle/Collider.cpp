#include "Collider.h"
#include "Core.h"
#include "SelectGDI.h"

namespace MomDra
{
	Collider::Collider(Object* owner) noexcept : owner{ owner }
	{

	}

	void Collider::LateUpdate() noexcept
	{
		Vector2 objectPos = owner->GetPos();
		finalPos = objectPos + offSetPos;
	}

	void Collider::Render(const HDC& hdc) noexcept
	{
		SelectGDI pen{ hdc, PenType::GREEN };
		SelectGDI brush{ hdc, BrushType::HOLLOW };

		Rectangle(hdc, static_cast<int>(finalPos.X - scale.X / 2), static_cast<int>(finalPos.Y - scale.Y / 2),
			static_cast<int>(finalPos.X + scale.X / 2), static_cast<int>(finalPos.Y + scale.Y / 2));
	}
}
