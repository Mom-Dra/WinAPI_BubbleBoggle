#pragma once

#include <list>
#include <memory>
#include "Object.h"

namespace MomDra
{
	class GameManager
	{
	private:
		std::list<std::unique_ptr<Object>> objects;

		POINT resolution;
		RECT rect;

		HWND hWnd;
		HDC hdc;

		HBITMAP hBit;
		HDC memDC;

	public:
		static GameManager& GetInstance() noexcept;

		// FPS
		static constexpr int FPS{ 60 };
		static constexpr float DELTATIME{ 1.0f / FPS };

		// 화면 크기
		static constexpr int WINDOW_WIDTH{ 800 };
		static constexpr int WINDOW_HEIGHT{ 800 };

		// Timer
		static constexpr int WM_TIMER_1{ 1 };

		void Initialize(const HWND& hWnd, const POINT& resolution) noexcept;
		void Progress() const noexcept;
		void AddImg() noexcept;
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
