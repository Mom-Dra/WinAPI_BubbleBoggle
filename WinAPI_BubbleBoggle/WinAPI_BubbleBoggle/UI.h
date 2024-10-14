#pragma once
#include <vector>
#include <memory>
#include "Object.h"

namespace MomDra
{
	// �θ� UI�� ���� ������ ���� ����
	// �θ� ���� Rendering ���ְ�, �ڽ��� Rendering ���־�� ��!
	class UI : public Object
	{
	private:
		std::vector<std::shared_ptr<UI>> children;
		//std::weak_ptr<UI> parent;
		UI* parent;

		Vector2 finalPos;

		bool affectedByCam; // UI�� ī�޶� ������ �޴���
		bool isMouseOn; // UI ���� ���콺�� �ִ���
		bool isLBtnDown; // UI�� ���ʹ�ư�� �������� �ִ���

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
