#include "Core.h"
#include "framework.h"
#include "Player.h"
#include "ImageCache.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"

namespace MomDra
{
    Core& Core::GetInstance() noexcept
    {
        static Core instance;

        return instance;
    }

    void Core::Progress() const noexcept
    {
        Update();

        FillRect(memDC, &rect, (HBRUSH)((COLOR_WINDOW)+1));
        Render(hdc);
        BitBlt(hdc, 0, 0, resolution.x, resolution.y, memDC, 0, 0, SRCCOPY);
    }

    void Core::Update() const noexcept
    {
        TimeManager::GetInstance().Update();
        KeyManager::GetInstance().Update();
        SceneManager::GetInstance().Update();
    }

    void Core::Render(const HDC& hdc) const noexcept
    {
        SceneManager::GetInstance().Render(memDC);
    }

    Core::~Core() noexcept
    {
        ReleaseDC(hWnd, hdc);

        DeleteDC(memDC);
        DeleteObject(hBit);
    }

    void Core::Initialize(const HWND& hWnd, const POINT& resolution) noexcept
    {
        this->hWnd = hWnd;
        this->resolution = resolution;

        RECT rt{ 0, 0, resolution.x, resolution.y };
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
        hBit = CreateCompatibleBitmap(hdc, resolution.x, resolution.y);
        memDC = CreateCompatibleDC(hdc);

        // �⺻���� 1px ¥�� bitMap�� �������
        // �̰� �Ⱦ��Ŵϱ� �ٷ� ���� ����
        HBITMAP hOldBit = static_cast<HBITMAP>(SelectObject(memDC, hBit));
        DeleteObject(hOldBit);

        // Manager �ʱ�ȭ
        //PathManager::GetInstance().Initialize();
        PathManager::Initialize();
        KeyManager::GetInstance().Initialize();
        TimeManager::GetInstance().Initialize();
        SceneManager::GetInstance().Initialize();
        ImageCache::InitGDIPlus();
    }
}