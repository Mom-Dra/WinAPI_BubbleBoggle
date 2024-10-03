#pragma once

#include <list>
#include <memory>
#include "Object.h"

namespace MomDra
{
	class Core
	{
	private:
		POINT resolution;
		RECT rect;

		// Main
		HWND hWnd;
		HDC hdc;

		// Double를 위한
		HBITMAP hBit;
		HDC memDC;

	public:
		static Core& GetInstance() noexcept;

		// 화면 크기
		static constexpr int WINDOW_WIDTH{ 800 };
		static constexpr int WINDOW_HEIGHT{ 800 };

		void Initialize(const HWND& hWnd, const POINT& resolution) noexcept;
		void Progress() const noexcept;
		inline const HWND& GetMainHwnd() const noexcept
		{
			return hWnd;
		}

		inline const HDC& GetMainDC() const noexcept
		{
			return hdc;
		}

	private:
		explicit Core() noexcept = default;
		explicit Core(const Core& other) = delete;
		~Core() noexcept;

		Core& operator=(const Core& other) = delete;

		void Update() const noexcept;
		void Render(const HDC& hdc) const noexcept;
	};
}
