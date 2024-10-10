#pragma once
#include <vector>
#include <memory>
#include "Object.h"

namespace MomDra
{
	// 부모 UI는 계층 적으로 만들 것임
	// 부모 먼저 Rendering 해주고, 자식을 Rendering 해주어야 함!
	class UI : public Object
	{
	private:
		std::vector<std::shared_ptr<UI>> children;
		std::weak_ptr<UI> parent;

	public:
		explicit UI(const Layer& layer = Layer::UI) noexcept;
		explicit UI(const Vector2& pos, const Vector2& scale, const Layer& layer = Layer::UI) noexcept;

		virtual void Update() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		std::weak_ptr<UI> GetParent() const noexcept { return parent; }

		void AddChild(std::shared_ptr<UI> ui) { children.emplace_back(ui); }
	};
}
