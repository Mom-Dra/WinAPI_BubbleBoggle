#pragma once
#include "framework.h"
#include "Tag.h"

namespace MomDra
{
	class SelectGDI
	{
	private:
		HDC hdc;
		HPEN hDefaultPen;
		HBRUSH hDefaultBrush;

	public: 
		explicit SelectGDI(HDC hdc, PenType penType) noexcept;
		explicit SelectGDI(HDC hdc, BrushType brushType) noexcept;
		~SelectGDI();
	};
}
