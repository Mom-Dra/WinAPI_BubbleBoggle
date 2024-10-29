#include "ImageObject.h"
#include "ResourceManager.h"
#include "KeyManager.h"

namespace MomDra
{
    ImageObject::ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer) : Object{ pos, scale, layer }
    {
        texture = ResourceManager::GetInstance().LoadTexture(imgPath);
    }

    void ImageObject::Render(const HDC& hdc) const noexcept
    {
        // 텍스쳐의 가로 세로 길이를 알아야 함
        int iWidth{ texture->GetWidth() };
        int iHeight{ texture->GetHeight() };

        const Vector2& pos{ GetPos() };
        const Vector2& scale{ GetScale() };

        //BitBlt(hdc, pos.X - (iWidth / 2), pos.Y - (iHeight / 2), iWidth, iHeight, texture->GetDC(), 0, 0, SRCCOPY);

        // 무시해야 할 색상을 마지막에 넣어준다
        TransparentBlt(hdc, static_cast<int>(pos.X - (scale.X / 2.0f)), static_cast<int>(pos.Y - (scale.Y / 2.0f)),
            scale.X, scale.Y, texture->GetDC(), 0, 0, iWidth, iHeight, RGB(255, 0, 255));

        Object::Render(hdc);
    }

    void ImageObject::Update() noexcept
    {
        
    }
}
