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
		//std::weak_ptr<UI> parent;
		UI* parent;

		Vector2 finalPos;

		bool affectedByCam; // UI가 카메라에 영향을 받는지
		bool isMouseOn; // UI 위에 마우스가 있는지
		bool isLBtnDown; // UI에 왼쪽버튼이 눌린적이 있는지

	public:
		explicit UI(bool affectedByCam, const Layer& layer = Layer::UI) noexcept;
		explicit UI(const Vector2& pos, const Vector2& scale, bool affectedByCam, const Layer& layer = Layer::UI) noexcept;
		explicit UI(const UI& other) noexcept;
		virtual ~UI() = default;

		virtual void Update() noexcept override;
		virtual void LateUpdate() noexcept override;
		virtual void Render(const HDC& hdc) const noexcept override;

		//inline std::weak_ptr<UI> GetParent() const noexcept { return parent; }
		inline UI* GetParent() const noexcept { return parent; }
		inline const std::vector<std::shared_ptr<UI>>& GetChildren() const noexcept { return children; }
		inline const Vector2& GetFinalPos() const noexcept { return finalPos; }
		inline bool IsMouseOn() const noexcept { return isMouseOn; }
		inline bool IsLBtnDown() const noexcept { return isLBtnDown; }

		inline void AddChild(std::shared_ptr<UI> childUI) { children.emplace_back(childUI); childUI->parent = this; }
		inline void SetIsLBtnDown(bool isLBtnDown) noexcept { this->isLBtnDown = isLBtnDown; }

		virtual void MouseOn() noexcept;
		virtual void MouseLBtnDown() noexcept;
		virtual void MouseLBtnUp() noexcept;
		virtual void MouseLBtnClicked() noexcept;

		inline virtual std::unique_ptr<Object> Clone() const override { return std::make_unique<UI>(*this); }

	private:
		void UpdateChild() noexcept;
		void LateUpdateChild() noexcept;
		void RenderChild(const HDC& hdc) const noexcept;

		void MouseOnCheck();
	};
}
