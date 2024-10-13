#include "BtnUI.h"

namespace MomDra
{
	void BtnUI::MouseOn() noexcept
	{

	}

	void BtnUI::MouseLBtnDown() noexcept
	{

	}

	void BtnUI::MouseLBtnUp() noexcept
	{

	}

	void BtnUI::MouseLBtnClicked() noexcept
	{
		if (func)
		{
			func(param1, param2);
		}
	}
}