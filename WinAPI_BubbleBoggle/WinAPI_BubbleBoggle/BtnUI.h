#pragma once
#include "UI.h"
#include <functional>

namespace MomDra
{
	class Scene;

	class BtnUI : public UI
	{
	private:
		// ��ư�� ������ �� ������ �� �ٸ���
		// ��ư�� ������ �� �ش� �Լ��� ȣ������ ���̴�.
		// �̷��� �ϸ� �پ��� ��ư�� ���� Ŭ������ �� ������� �ʿ䰡 ����.
		using BTN_FUNC = std::function<void(DWORD_PTR, DWORD_PTR)>;
		using FUNC = std::function<void()>;
		using OBJECT_BTN_FUNC = std::function<void(const Object&)>;

		BTN_FUNC func;
		DWORD_PTR param1;
		DWORD_PTR param2;

		FUNC sceneFunc;

	public:
		using UI::UI;

		virtual void MouseOn() noexcept override;
		virtual void MouseLBtnDown() noexcept override;
		virtual void MouseLBtnUp() noexcept override;
		virtual void MouseLBtnClicked() noexcept override;

		inline void SetClickedCallBack(BTN_FUNC func, DWORD_PTR param1, DWORD_PTR param2)
		{
			this->func = func;
			this->param1 = param1;
			this->param2 = param2;
		}

		inline void SetClickedCallBack(FUNC sceneFunc)
		{
			this->sceneFunc = sceneFunc;
		}

		inline virtual std::unique_ptr<Object> Clone() const override
		{
			return std::make_unique<BtnUI>(*this);
		}
	};
}
