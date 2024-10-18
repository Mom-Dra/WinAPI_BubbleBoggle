#include "Core.h"
#include "framework.h"
#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"
#include <iostream>
#include "UIManager.h"
#include "Ray.h"

namespace MomDra
{
    Core& Core::GetInstance() noexcept
    {
        static Core instance;

        return instance;
    }

    void Core::Progress() const noexcept
    {
        // Update
        Update();

        // Render
        FillRect(memDC, &rect, (HBRUSH)((COLOR_WINDOW)+1));
        Render(hdc);
        BitBlt(hdc, 0, 0, static_cast<int>(resolution.X), static_cast<int>(resolution.Y), memDC, 0, 0, SRCCOPY);

        // Event
        EventManager::GetInstance().Update();
    }

    void Core::Update() const noexcept
    {
        TimeManager::GetInstance().Update();
        KeyManager::GetInstance().Update();
        Camera::GetInstance().Update();
        SceneManager::GetInstance().Update();
        CollisionManager::GetInstance().Update();
        UIManager::GetInstance().Update();
    }

    void Core::Render(const HDC& hdc) const noexcept
    {
        TimeManager::GetInstance().Render();
        SceneManager::GetInstance().Render(memDC);
        Ray::Render(hdc);
    }

    void Core::CreateBrushPen() noexcept
    {
        // hollow brush
        brushes[static_cast <int> (BrushType::HOLLOW)] = static_cast<HBRUSH> (GetStockObject(HOLLOW_BRUSH));

        // red pen
        pens[static_cast<int>(PenType::Red)] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        pens[static_cast<int>(PenType::Green)] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
        pens[static_cast<int>(PenType::Blue)] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
        pens[static_cast<int>(PenType::Orange)] = CreatePen(PS_SOLID, 1, RGB(255, 165, 0));
    }

    Core::~Core() noexcept
    {
        ReleaseDC(hWnd, hdc);

        DeleteDC(memDC);
        DeleteObject(hBit);

        for (HPEN pen : pens)
        {
            DeleteObject(pen);
        }
    }

    void Core::Initialize(const HWND& hWnd, const Vector2& resolution) noexcept
    {
        this->hWnd = hWnd;
        this->resolution = resolution;

        RECT rt{ 0, 0, static_cast<int>(resolution.X), static_cast<int>(resolution.Y) };
        rect = rt;

        // 해상도에 맞게 윈도우 크기 조정
        // Title, 메뉴바, 윈도우 옆에 얇은 띠
        // 내가 원하는 크기를 설정하는 함수!
        // menu를 감안해서 계산해줘! true를 넘겨준다!
        AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

        // 계산한 rt는 메뉴바, 픽셀 등을 감안한 것들..
        SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
        
        // Window로 얻은건 Release로 지운다
        hdc = GetDC(hWnd);
        
        // Create로 만든건 Delete로 지운다
        hBit = CreateCompatibleBitmap(hdc, static_cast<int>(resolution.X), static_cast<int>(resolution.Y));
        memDC = CreateCompatibleDC(hdc);

        // 기본으로 1px 짜리 bitMap이 만들어짐
        // 이거 안쓸거니까 바로 지워 버림
        HBITMAP hOldBit = static_cast<HBITMAP>(SelectObject(memDC, hBit));
        DeleteObject(hOldBit);

        // 자주 사용할 펜 및 브러쉬
        CreateBrushPen();

        // Manager 초기화
        //PathManager::GetInstance().Initialize();
        PathManager::Initialize();
        KeyManager::GetInstance().Initialize();
        TimeManager::GetInstance().Initialize();
        SceneManager::GetInstance().Initialize();
        //ResourceManager::GetInstance().
    }
}