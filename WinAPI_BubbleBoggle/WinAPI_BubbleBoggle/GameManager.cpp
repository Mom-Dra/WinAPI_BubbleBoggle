#include "GameManager.h"
#include "framework.h"
#include "Player.h"
#include "ImageCache.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

namespace MomDra
{
    GameManager& GameManager::GetInstance() noexcept
    {
        static GameManager instance;

        return instance;
    }

    void GameManager::Progress() const noexcept
    {
        Update();
        Render(hdc);
    }

    void GameManager::Update() const noexcept
    {
        TimeManager::GetInstance().Update();
        KeyManager::GetInstance().Update();

        for (const auto& object : objects)
        {
            object->Update();
        }
    }

    void GameManager::Render(const HDC& hdc) const noexcept
    {
        // 화면 Clear
        //Rectangle(memDC, -1, -1, resolution.x + 1, resolution.y + 1);

        FillRect(memDC, &rect, (HBRUSH)((COLOR_WINDOW)+1));

        // 그리기
        for (const auto& object : objects)
        {
            object->Render(memDC);
        }

        BitBlt(hdc, 0, 0, resolution.x, resolution.y, memDC, 0, 0, SRCCOPY);
    }

    void GameManager::AddImg() noexcept
    {
        objects.emplace_back(std::make_unique<Player>(Vector2{ 100, 100 }, Vector2{ 20, 20 }, ImageCache::LoadImg(ImageCache::playerImgPath)));
    }

    const HWND& GameManager::GetHwnd() const noexcept
    {
        return hWnd;
    }

    GameManager::GameManager() noexcept : resolution{ 0, 0 }, rect{ 0, 0, 0, 0 }, hWnd{ 0 }, hdc{ 0 }, hBit{ 0 }, memDC{ 0 }
    {
        
    }

    GameManager::~GameManager() noexcept
    {
        ReleaseDC(hWnd, hdc);

        DeleteDC(memDC);
        DeleteObject(hBit);
    }

    void GameManager::Initialize(const HWND& hWnd, const POINT& resolution) noexcept
    {
        this->hWnd = hWnd;
        this->resolution = resolution;

        RECT rt{ 0, 0, resolution.x, resolution.y };
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
        hBit = CreateCompatibleBitmap(hdc, resolution.x, resolution.y);
        memDC = CreateCompatibleDC(hdc);

        // 기본으로 1px 짜리 bitMap이 만들어짐
        // 이거 안쓸거니까 바로 지워 버림
        HBITMAP hOldBit = static_cast<HBITMAP>(SelectObject(memDC, hBit));
        DeleteObject(hOldBit);

        // Manager 초기화
        TimeManager::GetInstance().Initialize();
        SceneManager::GetInstance().Initialize();
        KeyManager::GetInstance().Initialize();
        ImageCache::InitGDIPlus();
        
        AddImg();
    }
}