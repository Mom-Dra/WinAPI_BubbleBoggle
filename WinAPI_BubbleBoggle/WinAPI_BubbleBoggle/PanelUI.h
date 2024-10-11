#pragma once
#include "UI.h"
#include "Vector2.h"

using namespace CK;

namespace MomDra
{
	class PanelUI : public UI
	{
	private:
		Vector2 dragStart;

	public:
		using UI::UI;

		virtual void Render(const HDC& hdc) const noexcept override;

	private:
		virtual void MouseOn() noexcept override;
		virtual void MouseLBtnDown() noexcept override;
		virtual void MouseLBtnUp() noexcept override;
	};
}
