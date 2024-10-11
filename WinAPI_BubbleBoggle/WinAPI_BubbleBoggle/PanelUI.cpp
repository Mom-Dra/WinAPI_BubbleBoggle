#include "PanelUI.h"
#include "KeyManager.h"

namespace MomDra
{
	void PanelUI::Render(const HDC& hdc) const noexcept
	{
		UI::Render(hdc);
	}

	void PanelUI::MouseOn() noexcept
	{
		if (IsLBtnDown())
		{
			Vector2 mousePos{ KeyManager::GetInstance().GetMousePos() };
			Vector2 diff{ mousePos - dragStart };
			Vector2 currPos{ GetPos() };

			SetPos(currPos + diff);
			dragStart = mousePos;
		}
	}

	void PanelUI::MouseLBtnDown() noexcept
	{
		if (KeyManager::GetInstance().GetKeyDown(Key::LBUTTON))
		{
			dragStart = KeyManager::GetInstance().GetMousePos();
		}
	}

	void PanelUI::MouseLBtnUp() noexcept
	{

	}
}