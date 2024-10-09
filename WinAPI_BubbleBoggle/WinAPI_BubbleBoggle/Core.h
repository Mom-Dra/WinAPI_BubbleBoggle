#pragma once

#include <list>
#include <memory>
#include <array>
#include "Object.h"
#include "Tag.h"

namespace MomDra
{
	class Core
	{
	private:
		Vector2 resolution;
		RECT rect;

		// Main
		HWND hWnd;
		HDC hdc;

		// Double를 위한
		HBITMAP hBit;
		HDC memDC;

		// 자주 사용하는 GDI Object
		std::array<HBRUSH, static_cast<int>(BrushType::LAST)> brushes;
		std::array<HPEN, static_cast<int>(PenType::LAST)> pens;

	public:
		static Core& GetInstance() noexcept;

		// 화면 크기
		static constexpr int WINDOW_WIDTH{ 800 };
		static constexpr int WINDOW_HEIGHT{ 800 };

		void Initialize(const HWND& hWnd, const Vector2& resolution) noexcept;
		void Progress() const noexcept;

		inline const Vector2& GetResolution() const noexcept { return resolution; }
		inline const HWND& GetMainHwnd() const noexcept { return hWnd; }
		inline const HDC& GetMainDC() const noexcept { return hdc; }
		inline const HBRUSH& GetBrush(BrushType brushType) { return brushes[static_cast<int>(brushType)]; }
		inline const HPEN& GetPen(PenType penType) { return pens[static_cast<int>(penType)]; }

	private:
		explicit Core() noexcept = default;
		explicit Core(const Core& other) = delete;
		~Core() noexcept;

		Core& operator=(const Core& other) = delete;

		void Update() const noexcept;
		void Render(const HDC& hdc) const noexcept;

		void CreateBrushPen() noexcept;
	};
}
