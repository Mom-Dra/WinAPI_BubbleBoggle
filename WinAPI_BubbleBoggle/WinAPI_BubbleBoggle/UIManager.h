#pragma once
#include <memory>

namespace MomDra
{
	class UI;

	class UIManager
	{
	private:

	public:
		static UIManager& GetInstance() noexcept;

		void Update() const noexcept;

	private:
		explicit UIManager() noexcept = default;
		explicit UIManager(const UIManager& other) = delete;
		UIManager& operator=(const UIManager& other) = delete;

		UI* GetTargetUI(UI* parentUI) const noexcept;
	};
}
