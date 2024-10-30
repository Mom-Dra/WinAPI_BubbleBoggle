#include "BackGround.h"
#include "SelectGDI.h"
#include "Core.h"

namespace MomDra
{
	void BackGround::Render(const HDC& hdc) const noexcept
	{
		Object::Render(hdc);

		SelectGDI color{ hdc, PenType::Red };
		
		static const Vector2& resolution{ Core::GetInstance().GetResolution() };
		static RECT rect{ 0, 0, static_cast<LONG>(resolution.X), static_cast<LONG>(resolution.Y) };

		FillRect(hdc, &rect, HBRUSH(color.GetPen()));
	}
}

