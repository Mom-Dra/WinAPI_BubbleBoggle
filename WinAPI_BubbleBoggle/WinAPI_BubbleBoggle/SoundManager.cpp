#include "SoundManager.h"
#include "Core.h"
#include "Sound.h"

namespace MomDra
{
    int SoundManager::Initialize()
    {
        if (FAILED(DirectSoundCreate8(nullptr, &sound, nullptr)))
        {
            MessageBox(nullptr, L"사운드디바이스생성실패", L"SYSTEM ERROR", MB_OK);
            return false;
        }

        HWND hWnd{ Core::GetInstance().GetMainHwnd() };
        if (FAILED(sound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag 값 정리
        {
            MessageBox(nullptr, L"사운드디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
            return false;
        }

        return true;
    }

    void SoundManager::RegisterToBGM(std::shared_ptr<Sound> sound)
    {
        if (this->bgm)
            this->bgm->Stop(true);

        this->bgm = sound;
    }
}
