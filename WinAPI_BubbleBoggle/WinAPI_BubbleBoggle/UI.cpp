#include "UI.h"

namespace MomDra
{
	UI::UI(const Layer& layer) noexcept : UI{ Vector2::Zero, Vector2::Zero, layer }
	{

	}

	UI::UI(const Vector2& pos, const Vector2& scale, const Layer& layer) noexcept : Object{ pos, scale, layer }
	{

	}

	void UI::Update() noexcept
	{
		
	}

	void UI::Render(const HDC& hdc) const noexcept
	{
		const Vector2& pos{ GetPos() };
		const Vector2& scale{ GetScale() };
		
		Rectangle(hdc, static_cast<int>(pos.X), static_cast<int>(pos.Y), static_cast<int>(pos.X + scale.X), static_cast<int>(pos.Y + scale.Y));
	}
}
