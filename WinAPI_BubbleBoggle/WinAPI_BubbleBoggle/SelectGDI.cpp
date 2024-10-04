#include "SelectGDI.h"
#include "Core.h"

namespace MomDra
{
	SelectGDI::SelectGDI(HDC hdc, PenType penType) noexcept : hdc{ hdc }, hDefaultPen{ nullptr }, hDefaultBrush{ nullptr }
	{
		HPEN hPen = Core::GetInstance().GetPen(penType);
		hDefaultPen = static_cast<HPEN>(SelectObject(hdc, hPen));
	}

	SelectGDI::SelectGDI(HDC hdc, BrushType brushType) noexcept : hdc{ hdc }, hDefaultPen{ nullptr }, hDefaultBrush{ nullptr }
	{
		HBRUSH hBrush = Core::GetInstance().GetBrush(brushType);
		hDefaultBrush = static_cast<HBRUSH>(SelectObject(hdc, hBrush));
	}

	SelectGDI::~SelectGDI()
	{
		SelectObject(hdc, hDefaultPen);
		SelectObject(hdc, hDefaultBrush);
	}
}
