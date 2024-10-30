#include "ImageObject.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "Camera.h"

namespace MomDra
{
    ImageObject::ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer) : Object{ pos, scale, layer }
    {
        texture = ResourceManager::GetInstance().LoadTexture(imgPath);
    }

    void ImageObject::Render(const HDC& hdc) const noexcept
    {
        const Vector2& pos{ GetPos() };
        const Vector2& scale{ GetScale() };

        Vector2 renderPos{ Camera::GetInstance().GetRenderPos(pos) };

        TransparentBlt(hdc, static_cast<int>(renderPos.X - (scale.X / 2.0f)), static_cast<int>(renderPos.Y - (scale.Y / 2.0f)),
            scale.X, scale.Y, texture->GetDC(), 0, 0, texture->GetWidth(), texture->GetHeight(), RGB(255, 0, 255));

        Object::Render(hdc);
    }
}
