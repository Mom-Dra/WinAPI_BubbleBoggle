#pragma once

#include <list>
#include <memory>
#include "Object.h"

namespace MomDra
{
	class GameManager
	{
	private:
		POINT resolution;
		RECT rect;

		HWND hWnd;
		HDC hdc;

		HBITMAP hBit;
		HDC memDC;

	public:
		static GameManager& GetInstance() noexcept;

		// 화면 크기
		static constexpr int WINDOW_WIDTH{ 800 };
		static constexpr int WINDOW_HEIGHT{ 800 };

		void Initialize(const HWND& hWnd, const POINT& resolution) noexcept;
		void Progress() const noexcept;
		const HWND& GetHwnd() const noexcept;

	private:
		explicit GameManager() noexcept;
		explicit GameManager(const GameManager& other) = delete;
		~GameManager() noexcept;

		GameManager& operator=(const GameManager& other) = delete;
		
		void Update() const noexcept;
		void Render(const HDC& hdc) const noexcept;
	};
}
