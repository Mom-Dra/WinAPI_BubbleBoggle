#include "UI.h"
#include "Camera.h"
#include <iostream>
#include "KeyManager.h"
#include "SelectGDI.h"

namespace MomDra
{
	UI::UI(bool affectedByCam, const Layer& layer) noexcept : UI{ Vector2::Zero, Vector2::Zero, affectedByCam, layer }
	{

	}

	UI::UI(const Vector2& pos, const Vector2& scale, bool affectedByCam, const Layer& layer) noexcept : Object{ pos, scale, layer }, parent{ nullptr }, affectedByCam{ affectedByCam }, isMouseOn{ false }, isLBtnDown{ false }
	{

	}

	UI::UI(const UI& other) noexcept : Object{ other }, parent{ nullptr }, affectedByCam{ other.affectedByCam }, isMouseOn{ false }, isLBtnDown{ false }
	{
		for (const auto& child : other.children)
		{
			std::unique_ptr<Object> cloned{ std::move(child->Clone()) };
			Object* clonedObjectPtr{ cloned.release() };
			UI* clonedUIPtr{ dynamic_cast<UI*>(clonedObjectPtr) };

			std::shared_ptr<UI> clonedUI = std::shared_ptr<UI>(clonedUIPtr);
			//std::shared_ptr<UI> childClone{ std::make_shared<UI>(*child) };
			AddChild(clonedUI);
		}
	}

	void UI::Update() noexcept
	{
		UpdateChild();
	}

	void UI::LateUpdate() noexcept
	{
		Object::LateUpdate();

		//std::shared_ptr<UI> parent{ GetParent().lock() };
		UI* parent{ GetParent() };

		finalPos = GetPos();

		// UI의 최종 좌표를 구한다
		if (parent)
		{
			Vector2 parentPos{ parent->GetFinalPos() };
			finalPos += parentPos;
		}

		// UI Mouse 체크
		MouseOnCheck();

		LateUpdateChild();
	}

	void UI::Render(const HDC& hdc) const noexcept
	{
		Vector2 pos{ GetFinalPos() };
		const Vector2& scale{ GetScale() };

		if (affectedByCam)
		{
			pos = Camera::GetInstance().GetRenderPos(pos);
		}

		if (isLBtnDown)
		{
			SelectGDI gdi{ hdc, PenType::Green };

			Rectangle(hdc, static_cast<int>(pos.X), static_cast<int>(pos.Y), static_cast<int>(pos.X + scale.X), static_cast<int>(pos.Y + scale.Y));
		}
		else
		{
			Rectangle(hdc, static_cast<int>(pos.X), static_cast<int>(pos.Y), static_cast<int>(pos.X + scale.X), static_cast<int>(pos.Y + scale.Y));
		}

		RenderChild(hdc);
	}

	void UI::MouseOn() noexcept
	{

	}

	void UI::MouseLBtnDown() noexcept
	{

	}

	void UI::MouseLBtnUp() noexcept
	{

	}

	void UI::MouseLBtnClicked() noexcept
	{

	}

	void UI::UpdateChild() noexcept
	{
		for (const auto& child : children)
		{
			child->Update();
		}
	}

	void UI::LateUpdateChild() noexcept
	{
		for (const auto& child : children)
		{
			child->LateUpdate();
		}
	}

	void UI::RenderChild(const HDC& hdc) const noexcept
	{
		for (const auto& child : children)
		{
			child->Render(hdc);
		}
	}

	void UI::MouseOnCheck()
	{
		Vector2 mousePos{ KeyManager::GetInstance().GetMousePos() };
		Vector2 scale{ GetScale() };

		if (affectedByCam)
		{
			mousePos = Camera::GetInstance().GetRealPos(mousePos);
		}

		if (finalPos.X <= mousePos.X && mousePos.X <= finalPos.X + scale.X && finalPos.Y <= mousePos.Y && mousePos.Y <= finalPos.Y + scale.Y)
		{
			isMouseOn = true;
		}
		else
		{
			isMouseOn = false;
		}
	}
}
