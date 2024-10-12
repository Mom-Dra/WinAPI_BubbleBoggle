#pragma once
#include <memory>

namespace MomDra
{
	class UI;

	class UIManager
	{
	private:
		UI* focusedUI;

	public:
		static UIManager& GetInstance() noexcept;

		void Update() noexcept;

		void SetFocusedUI(UI* ui) noexcept;


	private:
		explicit UIManager() noexcept = default;
		explicit UIManager(const UIManager& other) = delete;
		UIManager& operator=(const UIManager& other) = delete;

		UI* GetFocusedUI() noexcept;
		UI* GetTargetUI(UI* parentUI) const noexcept;
	};
}
