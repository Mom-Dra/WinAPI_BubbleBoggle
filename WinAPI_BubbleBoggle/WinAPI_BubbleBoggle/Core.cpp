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

        // �ػ󵵿� �°� ������ ũ�� ����
        // Title, �޴���, ������ ���� ���� ��
        // ���� ���ϴ� ũ�⸦ �����ϴ� �Լ�!
        // menu�� �����ؼ� �������! true�� �Ѱ��ش�!
        AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

        // ����� rt�� �޴���, �ȼ� ���� ������ �͵�..
        SetWindowPos(hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
        
        // Window�� ������ Release�� �����
        hdc = GetDC(hWnd);
        
        // Create�� ����� Delete�� �����
        hBit = CreateCompatibleBitmap(hdc, static_cast<int>(resolution.X), static_cast<int>(resolution.Y));
        memDC = CreateCompatibleDC(hdc);

        // �⺻���� 1px ¥�� bitMap�� �������
        // �̰� �Ⱦ��Ŵϱ� �ٷ� ���� ����
        HBITMAP hOldBit = static_cast<HBITMAP>(SelectObject(memDC, hBit));
        DeleteObject(hOldBit);

        // ���� ����� �� �� �귯��
        CreateBrushPen();

        // Manager �ʱ�ȭ
        //PathManager::GetInstance().Initialize();
        PathManager::Initialize();
        KeyManager::GetInstance().Initialize();
        TimeManager::GetInstance().Initialize();
        SceneManager::GetInstance().Initialize();
        //ResourceManager::GetInstance().
    }
}